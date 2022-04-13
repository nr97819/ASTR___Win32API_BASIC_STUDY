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
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution; // 메인 윈도우 해상도
	HDC		m_hDC;			// 메인 윈도우에 Draw 할 DC

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }

};

// - [지역]
// - [전역]
// - [정적 멤버 변수] (데이터 영역)
//		1. 함수 안에 -> 함수를 통해서만 접근 가능		(@ 헷갈렸음 @)
//		2. 파일 안에 (전역) -> 선언된 파일 내에서만 접근 가능 (다른 파일에서 이름 중복되어도 됨)
//		3. 클래스 안에 -> 클래스 안에서는 누구나 접근 가능 CClass::FUNC()		(@ 헷갈렸음 @)
//		-> 일반 멤버 함수도, static 멤버 변수에 접근이 가능하다. (역시 클래스 안에 있는 멤버 변수라서..)
//		-> 즉, 속한 클래스 안에서만 접근이 가능한, 데이터 영역에 존재하는 변수이다.
// - [외부]


// Core 클래스는 : 내가 만든 프로그램 그 자체라고 생각하면 된다.
// (핵심 로직들이 담겨있는 곳이다.)

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능 (extern으로 구현하게 되면, 특정 객체만 extern이고, 여러개의 객체가 생기는 것은 역시 방지 불가능 - 해결방안 X))