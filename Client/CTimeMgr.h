#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	//FPS
	// 1 �����Ӵ� �ð� Delta Time �̶� Ī�Ѵ�
	// 2 FPS�� ���ϴ� ������ ��ǻ���� ���ɿ� ���� �̵����� �޶����� �ȵǱ⶧�� �ð� ����ȭ�� ���͸� ������Ų��
public:
	void init();
};

