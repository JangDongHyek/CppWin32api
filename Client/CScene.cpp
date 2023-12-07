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
		for (size_t j = 0; j < m_arrObj[i].size(); ++j) // m_arrObj[i] 그룹 벡터의 오브젝트들 삭제
		{
			
			delete m_arrObj[i][j];
		}
	}

	// Scene이 갖고있는 벡터의 삭제는 벡터 클래스가 알아서 해준다 고로 벡터쪽 메모리는 신경쓸 필요없음
	// 위에 코드를 진행하는이유는 벡터안의 데이터가 오브젝트 자체가아니라 오브젝트의 주소를 들고있기때문에 주소에 따라들어가 힙메모리에있는 공간을 삭제하기 위함
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