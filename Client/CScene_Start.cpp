#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
	//������Ʈ���� �θ� �����ϱ⶧���� �ڽĿ��� �������ʿ����
}

void CScene_Start::Enter()
{
	// Object �߰�
	CObject* pObj = new CObject;

	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100, 100));

	AddObject(pObj, GROUP_TYPE::DEFAULT);
}

void CScene_Start::Exit()
{
}
