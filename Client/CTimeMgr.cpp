#include "pch.h"
#include "CTimeMgr.h"


CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llFrequency{}
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 1초를 천만으로 나눈 함수
	QueryPerformanceCounter(&m_llCurCount);
	// 1초에 얼마나 카운팅 되는지 체크하는 함수
	QueryPerformanceFrequency(&m_llFrequency);

}
