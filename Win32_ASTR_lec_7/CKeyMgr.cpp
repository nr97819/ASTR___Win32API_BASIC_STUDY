
#include "pch.h"
#include "CKeyMgr.h"

// �ݵ�� cpp ���Ͽ� �������� �����ؾ� �ϴ� �� ����
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
	VK_MENU, // ALT Ű
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
	// Key ��/���� vector �ʱ�ȭ
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// ó������ ��� {None, ������ ����} ���� �ʱ�ȭ
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// �ش� Ű�� [����] �����ִٸ�
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) // ��Ʈ �������ε� ����
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
		// �ش� Ű�� [����] �ȴ����ִٸ�
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
