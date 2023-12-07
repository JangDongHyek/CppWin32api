#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
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

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();



	g_obj.SetPos(Vec2((float) (m_ptResolution.x / 2), (float) (m_ptResolution.y / 2 )));
	g_obj.SetScale(Vec2( 100,100 ));

	return S_OK;
}


void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();

	update();

	render();
	
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	// 키의 상태값을 가져오는 함수 * 이전에 눌렸다 눌리고있다 프로그램 실행중 눌렸다 등등 비트값으로 반환
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 그냥 키가 눌렸나 확인해보고싶으면 0x8000 비트값을 and 연사자로 확인
	{
		//구해온 DT값으로 초당 이동량을 고정 시킨다
		vPos.x -= 100.f * CTimeMgr::GetInst()->GetfDT();
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 100.f * CTimeMgr::GetInst()->GetfDT();
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// 그리기
	Rectangle(m_hDC,
			int(vPos.x - vScale.x / 2.f),
			int(vPos.y - vScale.y / 2.f),
			int(vPos.x + vScale.x / 2.f), 
			int(vPos.y + vScale.y / 2.f));
}
