#include "pch.h"
#include "CCore.h"
#include "CObject.h"

//CCore* CCore::g_pInst = nullptr; // 전역변수기때문에 초기화 한번



CObject g_obj;


CCore::CCore() 
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{

}

CCore::~CCore() 
{
	ReleaseDC(m_hWnd, m_hDC); // 커널 오브젝트 DC 종료
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

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100,100 };

	return S_OK;
}


void CCore::progress()
{
	static int callcount = 0; // 프로그래스가 호출되는 카운트
	++callcount;

	static int iPrevCount = GetTickCount(); // 정적 멤버 변수기 떄문에 한번만 초기화 됌
	int iCurCount = GetTickCount();
	if (iCurCount - iPrevCount > 1000) // 1초가 지났을때 몇번 호출됐는지 확인하기위한 조건
	{
		iPrevCount = iCurCount;
		callcount = 0;
	}
	
	update();

	render();
	
}

void CCore::update()
{
	// 키의 상태값을 가져오는 함수 * 이전에 눌렸다 눌리고있다 프로그램 실행중 눌렸다 등등 비트값으로 반환
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 그냥 키가 눌렸나 확인해보고싶으면 0x8000 비트값을 and 연사자로 확인
	{
		g_obj.m_ptPos.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
}

void CCore::render()
{
	// 그리기
	Rectangle(m_hDC,
			g_obj.m_ptPos.x- g_obj.m_ptScale.x / 2,
			g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2,
			g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2, 
			g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}
