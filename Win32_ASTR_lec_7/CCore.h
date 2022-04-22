#pragma once

#include "define.h"

class CCore
{
	SINGLE(CCore);
private:
	HWND		m_hWnd;
	POINT		m_ptResolution;
	HDC			m_hDC;

	HBITMAP		m_hBit;
	HDC			m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
};