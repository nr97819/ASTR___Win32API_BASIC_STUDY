
#include "pch.h"
#include "CKeyMgr.h"

// 반드시 cpp 파일에 전역으로 생성해야 하는 것 주의
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
	VK_MENU, // ALT 키
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
	// Key 값/상태 vector 초기화
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// 처음에는 모두 {None, 눌린적 없음} 으로 초기화
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// 해당 키가 [지금] 눌려있다면
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) // 비트 연산으로도 가능
		{
			if (m_vecKey[i].ePrevPush)	
			{	// prev:O, now:O
				m_vecKey[i].estate = KEY_STATE::HOLD;
			}
			else						
			{	// prev:X, now:O
				m_vecKey[i].estate = KEY_STATE::TAP;
			}

			m_vecKey[i].ePrevPush = true;
		}
		// 해당 키가 [지금] 안눌려있다면
		else
		{
			if (m_vecKey[i].ePrevPush)	
			{	// prev:O, now:X
				m_vecKey[i].estate = KEY_STATE::AWAY;
			}
			else						
			{	// prev:X, now:X
				m_vecKey[i].estate = KEY_STATE::NONE;
			}

			m_vecKey[i].ePrevPush = false;
		}
	}
}
