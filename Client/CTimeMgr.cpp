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
	// 1�ʸ� õ������ ���� �Լ�
	QueryPerformanceCounter(&m_llCurCount);
	// 1�ʿ� �󸶳� ī���� �Ǵ��� üũ�ϴ� �Լ�
	QueryPerformanceFrequency(&m_llFrequency);

}
