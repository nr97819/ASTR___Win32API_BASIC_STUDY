#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"

// 정젹 멤버 변수는 -> 반드시 전역 스코프에서 특정 값으로 초기화 해줘야 한다.
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

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // _Inout_ RECT*, 모든걸 포함한 기본 창 모양, 메뉴 고려 여부
	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);  // 창 생성 위치, 창 생성 크기 (위 참고)

	m_hDC = GetDC(m_hWnd);

	// Manager 클래스들 일괄 초기화
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();

	g_obj.SetPos(Vec2(_ptResolution.x / 2.f, _ptResolution.y / 2.f));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

// 메시지 처리하지 않을 때, 호출될 함수 (상시 호출 점유 최상)
void CCore::progress()
{
	static int callCount = 0;
	++callCount;

	static int iPrevCount = GetTickCount64();
	int iCurCount = GetTickCount64();
	if (iCurCount - iPrevCount > 1000) // 1초 경과시 진입
	{
		iPrevCount = iCurCount;

		callCount = 0;
	}

	// Manager 클래스들 일괄 Update
	CTimeMgr::GetInst()->Update(); // 매 프레임마다 TimerMgr이 업데이트 되도록


	update();

	// Manager 클래스들 일괄 Render
	render();
}

// [1] update()는 그리기 작업을 하는 곳이 아니라, 물체들의 변경점(좌표, 등)들을 체크하는 곳이다.
void CCore::update()
{
	// 비동기 키 입력 함수를 써보자
	// return되는 SHORT 값은, 단순 눌림 여부가 아닌, 눌린 상태(tab, hold, release)도 알려준다.
	// 이순간 눌렸는지만 체크하려면, & 0x8000 비트만 보면 된다.(가장 상위 비트)

	// 새로 바꾼 Vec2로 수정
	Vec2 vPos = g_obj.GetPos();

	// 해당 키가 눌린 경우에만 진입

	// Frame Per a Secound (FPS)
	// = (1 / Delta Time)

	// Time Per a Frame (Delta Time)
	// = (1 / FPS)

	// 100의 거리를 이동하기 위해서
	// 100fps의 경우 : frame당 1(거리 / FPS)씩 이동하면 됨
	// (distance(100) / FPS(100)) == (distance(100) * Delta Time(1 / 100) == 1

	// 200fps의 경우 : frame당 0.5(거리 / FPS)씩 이동하면 됨
	// (distance(100) / FPS(200)) == (distance(100) * Delta Time(1 / 200)) == 0.5

	// FPS는 매순간 변동이 있기 때문에,
	// 항상 FPS는 어딘가에서 계산이 되고 있어야 한다.
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

	// 데이터 관리는 float으로 하되,
	// 어차피 rendering할 때는 int로 변환되므로, float으로 미세 조정하는 것이 효과적
	// (107 + 0.1 * 7 = 107.7픽셀의 위치에 있지만, rendering시에는 107픽셀의 위치로 잡힐 것이다.)
	// *POINT 구조체는 int좌표를 갖으므로, float X, float Y를 갖을 우리만의 구조체를 만들자. ( Vec2 )
}

// [2] update 함수에서, 변경점들이 적용되고, FIX된 상태가 되면, render()에서 최종적으로 그리기를 맡는다.
void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// 그리기
	Rectangle(m_hDC	, (int)(vPos.x - vScale.x / 2.f)
					, (int)(vPos.y - vScale.y / 2.f)
					, (int)(vPos.x + vScale.x / 2.f)
					, (int)(vPos.y + vScale.y / 2.f));
}