
#include "pch.h"

#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q', 'W', 'E', 'R', 'T',
	'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G',
	'Z', 'X', 'C', 'V', 'B',
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update()
{
	// 윈도우 포커싱 알아내기
	HWND hMainWnd = CCore::GetInst()->GetMainHwnd(); // 우리의 메인 윈도우 핸들 값 (지금은 안 씀)
	HWND hFocusWnd = GetFocus(); // 현재 포커싱된 윈도우 핸들 값 반환
	// 포커싱된 윈도우가 하나도 없으면 null이 반환된다.

	// 만약 현재 Main Window가 포커싱 된 상태라면 (강의랑 조금 다른 코드)
	//if (hMainWnd == hFocusWnd)
	if (nullptr != hFocusWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].ePrevPush)
				{
					m_vecKey[i].estate = KEY_STATE::HOLD;
				}
				else
				{
					m_vecKey[i].estate = KEY_STATE::TAP;
				}

				m_vecKey[i].ePrevPush = true;
			}
			else
			{
				if (m_vecKey[i].ePrevPush)
				{
					m_vecKey[i].estate = KEY_STATE::AWAY;
				}
				else
				{
					m_vecKey[i].estate = KEY_STATE::NONE;
				}

				m_vecKey[i].ePrevPush = false;
			}
		}
	}
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// 이전 키 상태를 false로 변경 (state를 위해)
			m_vecKey[i].ePrevPush = false;

			// TAP이나 HOLD 상태인 경우, 프레임 두 번에 걸쳐서 NONE으로 바뀌도록 한 것.
			if (KEY_STATE::TAP == m_vecKey[i].estate)
			{
				m_vecKey[i].estate = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::HOLD == m_vecKey[i].estate)
			{
				m_vecKey[i].estate = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].estate)
			{
				m_vecKey[i].estate = KEY_STATE::NONE;
			}
			// NONE은 그대로 NONE이므로, 별도 코드 X
		}
	}
}
