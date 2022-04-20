#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CObject.h"

CObject g_obj;
// 이제 Scene 안에 Object 들을 넣어놓고, 그걸 가져다가 출력하도록 정석적인 코드로 수정

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

	// Manager Init
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();

	g_obj.SetPos(Vec2(_ptResolution.x / 2.f, _ptResolution.y / 2.f));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update();
	CSceneMgr::GetInst()->Update(); // (@) 현재 Scene의 모든 Obejct들을 update해준다.
	// (모든 포지션들 변경 반영 (값만))

	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 렌더링
	// (2) 변경된 좌표들을 모두 memDC에 실제로 그린다.
	CSceneMgr::GetInst()->Render(m_memDC);

	// (3) memDC에 그려진 것들을 한번에 m_hDC(메인DC)로 한번에 가져온다.(double buffering)
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	//update();
}

void CCore::update()
{
	
}

void CCore::render()
{

}