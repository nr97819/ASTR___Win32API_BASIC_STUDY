#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"

CObject g_obj;

CCore::CCore() 
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);


	m_hDC = GetDC(m_hWnd);

	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);


	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();

	g_obj.SetPos(Vec2(_ptResolution.x / 2.f, _ptResolution.y / 2.f));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update(); // KeyMgr 역시 매 프레임마다 update하며, 키 눌림 체크

	update();
	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::TAP)
	{
		vPos.x -= 300.f;
	}
	/*if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 300.f * CTimeMgr::GetInst()->GetfDT();
	}*/
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 300.f * CTimeMgr::GetInst()->GetfDT();
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		vPos.y -= 300.f * CTimeMgr::GetInst()->GetfDT();
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		vPos.y += 300.f * CTimeMgr::GetInst()->GetfDT();
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memDC, (int)(vPos.x - vScale.x / 2.f)
					, (int)(vPos.y - vScale.y / 2.f)
					, (int)(vPos.x + vScale.x / 2.f)
					, (int)(vPos.y + vScale.y / 2.f));

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);
}