#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
	//������Ʈ���� �θ� �����ϱ⶧���� �ڽĿ��� �������ʿ����
}

void CScene_Start::Enter()
{
	// �ڽ� Player Object �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);

	// 1. �θ� Object �߰� * �����Լ��� ������Ʈ�� �������� Ȯ���ϱ� ���� ����
	// 2. update �Լ��� ���� �����Լ��� �ٲ��� �߻� Ŭ������ �Ʊ⶧���� ���� �����Ҵ��� �Ұ�������
	//pObj = new CObject;
	//pObj->SetPos(Vec2(640.f, 384.f));
	//pObj->SetScale(Vec2(100, 100));
	//AddObject(pObj, GROUP_TYPE::DEFAULT);
	
	//�ڽ� Monster Object �߰�
	// 1. �ڽ��� �ִ� �Լ��� �����Ұű⶧���� �ڽ�Ÿ������ ����
	//CMonster* pMonsterObj = new CMonster;
	//pMonsterObj->SetPos(Vec2(640.f, 50.f));
	//pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
	//pMonsterObj->SetScale(Vec2(50.f, 50.f));
	//AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);

	// �������� ���� �������� ��ġ

	// �ػ� �������� * �����ڷ� �ش� ����ü�� ���Ե����� ��ȯ�ǰ� ��Ȳ �߰� 
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonsterObj = nullptr;
	
	int iMonCount = 16;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;
	// (�ػ� x  - (������ �̵��ݰ� + �ڽ��� ũ�� ����)) / ������ ��ü��
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount -1);

	for (int i = 0; i < iMonCount; ++i)
	{
		pMonsterObj = new CMonster;
		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
	}
}

void CScene_Start::Exit()
{
}
