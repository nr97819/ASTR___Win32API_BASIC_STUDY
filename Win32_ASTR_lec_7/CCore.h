#pragma once

//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	static CCore* GetInstance()
//	{
//		if (!g_pInst)
//			g_pInst = new CCore();
//
//		return g_pInst;
//	}
//
//	static void ReleaseInstance()
//	{
//		if (!g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//private:
//	CCore();
//	~CCore();
//};

#include "define.h"

class CCore
{
	SINGLE(CCore);
private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution; // ���� ������ �ػ�
	HDC		m_hDC;			// ���� �����쿡 Draw �� DC

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }

};

// - [����]
// - [����]
// - [���� ��� ����] (������ ����)
//		1. �Լ� �ȿ� -> �Լ��� ���ؼ��� ���� ����		(@ �򰥷��� @)
//		2. ���� �ȿ� (����) -> ����� ���� �������� ���� ���� (�ٸ� ���Ͽ��� �̸� �ߺ��Ǿ ��)
//		3. Ŭ���� �ȿ� -> Ŭ���� �ȿ����� ������ ���� ���� CClass::FUNC()		(@ �򰥷��� @)
//		-> �Ϲ� ��� �Լ���, static ��� ������ ������ �����ϴ�. (���� Ŭ���� �ȿ� �ִ� ��� ������..)
//		-> ��, ���� Ŭ���� �ȿ����� ������ ������, ������ ������ �����ϴ� �����̴�.
// - [�ܺ�]


// Core Ŭ������ : ���� ���� ���α׷� �� ��ü��� �����ϸ� �ȴ�.
// (�ٽ� �������� ����ִ� ���̴�.)

// �̱��� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ���� (extern���� �����ϰ� �Ǹ�, Ư�� ��ü�� extern�̰�, �������� ��ü�� ����� ���� ���� ���� �Ұ��� - �ذ��� X))