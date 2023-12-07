#include "pch.h"
#include "CScene.h"
#include "CObject.h"


CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) 
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // m_arrObj[i] �׷� ������ ������Ʈ�� ����
		{
			
			delete m_arrObj[i][j];
		}
	}

	// Scene�� �����ִ� ������ ������ ���� Ŭ������ �˾Ƽ� ���ش� ��� ������ �޸𸮴� �Ű澵 �ʿ����
	// ���� �ڵ带 �����ϴ������� ���;��� �����Ͱ� ������Ʈ ��ü���ƴ϶� ������Ʈ�� �ּҸ� ����ֱ⶧���� �ּҿ� ����� ���޸𸮿��ִ� ������ �����ϱ� ����
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) {
			m_arrObj[i][j]->update();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) {
			m_arrObj[i][j]->render(_dc);
		}
	}
}