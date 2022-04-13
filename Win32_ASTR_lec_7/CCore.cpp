#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"

// ���� ��� ������ -> �ݵ�� ���� ���������� Ư�� ������ �ʱ�ȭ ����� �Ѵ�.
//CCore* CCore::g_pInst = nullptr;

CObject g_obj;

CCore::CCore() 
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // _Inout_ RECT*, ���� ������ �⺻ â ���, �޴� ��� ����
	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);  // â ���� ��ġ, â ���� ũ�� (�� ����)

	m_hDC = GetDC(m_hWnd);

	// Manager Ŭ������ �ϰ� �ʱ�ȭ
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();

	g_obj.SetPos(Vec2(_ptResolution.x / 2.f, _ptResolution.y / 2.f));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

// �޽��� ó������ ���� ��, ȣ��� �Լ� (��� ȣ�� ���� �ֻ�)
void CCore::progress()
{
	static int callCount = 0;
	++callCount;

	static int iPrevCount = GetTickCount64();
	int iCurCount = GetTickCount64();
	if (iCurCount - iPrevCount > 1000) // 1�� ����� ����
	{
		iPrevCount = iCurCount;

		callCount = 0;
	}

	// Manager Ŭ������ �ϰ� Update
	CTimeMgr::GetInst()->Update(); // �� �����Ӹ��� TimerMgr�� ������Ʈ �ǵ���


	update();

	// Manager Ŭ������ �ϰ� Render
	render();
}

// [1] update()�� �׸��� �۾��� �ϴ� ���� �ƴ϶�, ��ü���� ������(��ǥ, ��)���� üũ�ϴ� ���̴�.
void CCore::update()
{
	// �񵿱� Ű �Է� �Լ��� �Ẹ��
	// return�Ǵ� SHORT ����, �ܼ� ���� ���ΰ� �ƴ�, ���� ����(tab, hold, release)�� �˷��ش�.
	// �̼��� ���ȴ����� üũ�Ϸ���, & 0x8000 ��Ʈ�� ���� �ȴ�.(���� ���� ��Ʈ)

	// ���� �ٲ� Vec2�� ����
	Vec2 vPos = g_obj.GetPos();

	// �ش� Ű�� ���� ��쿡�� ����

	// Frame Per a Secound (FPS)
	// = (1 / Delta Time)

	// Time Per a Frame (Delta Time)
	// = (1 / FPS)

	// 100�� �Ÿ��� �̵��ϱ� ���ؼ�
	// 100fps�� ��� : frame�� 1(�Ÿ� / FPS)�� �̵��ϸ� ��
	// (distance(100) / FPS(100)) == (distance(100) * Delta Time(1 / 100) == 1

	// 200fps�� ��� : frame�� 0.5(�Ÿ� / FPS)�� �̵��ϸ� ��
	// (distance(100) / FPS(200)) == (distance(100) * Delta Time(1 / 200)) == 0.5

	// FPS�� �ż��� ������ �ֱ� ������,
	// �׻� FPS�� ��򰡿��� ����� �ǰ� �־�� �Ѵ�.
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 300.f * CTimeMgr::GetInst()->GetfDT();
	}
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

	// ������ ������ float���� �ϵ�,
	// ������ rendering�� ���� int�� ��ȯ�ǹǷ�, float���� �̼� �����ϴ� ���� ȿ����
	// (107 + 0.1 * 7 = 107.7�ȼ��� ��ġ�� ������, rendering�ÿ��� 107�ȼ��� ��ġ�� ���� ���̴�.)
	// *POINT ����ü�� int��ǥ�� �����Ƿ�, float X, float Y�� ���� �츮���� ����ü�� ������. ( Vec2 )
}

// [2] update �Լ�����, ���������� ����ǰ�, FIX�� ���°� �Ǹ�, render()���� ���������� �׸��⸦ �ô´�.
void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// �׸���
	Rectangle(m_hDC	, (int)(vPos.x - vScale.x / 2.f)
					, (int)(vPos.y - vScale.y / 2.f)
					, (int)(vPos.x + vScale.x / 2.f)
					, (int)(vPos.y + vScale.y / 2.f));
}