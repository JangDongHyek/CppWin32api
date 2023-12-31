#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"


CCore::CCore() 
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{

}

CCore::~CCore() 
{
	ReleaseDC(m_hWnd, m_hDC); // 커널 오브젝트 DC 종료

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	//해상도에 맞게 윈도우 크기 조정
	//윈도우 버전에 맞게 크기를 조정하는 함수 * 윈도우의 타이틀바 메뉴바 크기가있기때문에 원하는 해상도를 넣으면 작업영역이 원하는 해상도만큼 생긴다 작업영역 + 다른크기까지구하기위함
	RECT rt = {0,0, m_ptResolution.x,m_ptResolution.y}; // 함수가 rect 구조체의 포인터를 요구하기떄문에 rect 구조체 생성
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW,true); // rt 구조체에 값이 채워짐
	// 윈도우 크기 변경
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// 프로그램의 작업영역을 비트맵이라 칭한다
	// 이중 버퍼링 용도의 비트맵과 DC 를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // DC를 호환할 비트맵 생성
	m_memDC = CreateCompatibleDC(m_hDC); // 호환할 비트맵에 적용시킬 DC 생성

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // 반환되는 값으로 DC가 생성시 가지고있던 1픽셀크기의 비트맵이 반환된다
	DeleteObject(hOldBit); // 쓸모없는 더미 비트맵 커널 오브젝트 삭제

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();


	return S_OK;
}


void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();

	//=========
	//Rendering
	//=========
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);
}

