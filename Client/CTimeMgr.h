#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	//FPS
	// 1 프레임당 시간 Delta Time 이라 칭한다
	// 2 FPS를 구하는 이유는 컴퓨터의 성능에 따라 이동량이 달라지면 안되기때문 시간 동기화로 벡터를 고정시킨다
public:
	void init();
};

