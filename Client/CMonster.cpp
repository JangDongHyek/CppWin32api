#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f,0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos(); // 부모에 있는 함수

	//진행 방향으로 시단강 스피드 만큼 이동
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	// 배회 거리 기준량을 넘었는지 확인100 200 100
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	if (0.f < fDist)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}