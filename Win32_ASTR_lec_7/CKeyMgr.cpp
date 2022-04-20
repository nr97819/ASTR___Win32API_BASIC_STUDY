
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
	// ������ ��Ŀ�� �˾Ƴ���
	HWND hMainWnd = CCore::GetInst()->GetMainHwnd(); // �츮�� ���� ������ �ڵ� �� (������ �� ��)
	HWND hFocusWnd = GetFocus(); // ���� ��Ŀ�̵� ������ �ڵ� �� ��ȯ
	// ��Ŀ�̵� �����찡 �ϳ��� ������ null�� ��ȯ�ȴ�.

	// ���� ���� Main Window�� ��Ŀ�� �� ���¶�� (���Ƕ� ���� �ٸ� �ڵ�)
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
			// ���� Ű ���¸� false�� ���� (state�� ����)
			m_vecKey[i].ePrevPush = false;

			// TAP�̳� HOLD ������ ���, ������ �� ���� ���ļ� NONE���� �ٲ�� �� ��.
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
			// NONE�� �״�� NONE�̹Ƿ�, ���� �ڵ� X
		}
	}
}
