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
	//오브젝트들은 부모가 관리하기때문에 자식에서 삭제할필요없다
}

void CScene_Start::Enter()
{
	// 자식 Player Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::DEFAULT);


	// 해상도 가져오기 * 생성자로 해당 구조체가 대입됐을때 반환되게 상황 추가 
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMonsterObj = nullptr;
	
	int iMonCount = 16;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;
	// (해상도 x  - (몬스터의 이동반경 + 자신의 크기 절반)) / 몬스터의 개체수
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
