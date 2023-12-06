#include "pch.h"
#include "CCore.h"


//CCore* CCore::g_pInst = nullptr; // 전역변수기때문에 초기화 한번





CCore::CCore() {

}

CCore::~CCore() {

}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	return S_OK;
}

void CCore::progress()
{
}

