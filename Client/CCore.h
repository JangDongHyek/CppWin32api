#pragma once

#include "define.h"
class CCore {
SINGLE(CCore)

private : 
	HWND	m_hWnd; //메인 윈도우 핸들
	POINT	m_ptResolution; // 메인 윈도우 해상도
	HDC		m_hDC; // 메인 윈도우에 Draw 할 DC

	HBITMAP	m_hBit;
	HDC		m_memDC;
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