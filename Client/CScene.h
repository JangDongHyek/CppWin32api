#pragma once

class CObject; // 전방선언시 무슨타입인지 모르기때문에 클래스타입은 쓸수없다 그래서 포인터 타입을 사용

class CScene
{
private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring				m_strName;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	// 상속받은 애들 모두 update,render를 사용할거기 떄문에 부모쪽에서 선언
	void update();
	void render(HDC _dc);

	virtual void Enter() = 0; // = 0 이거를 넣으면 순수가상함수 (추상화클래스) 가 되고 해당 부모를 상속하는애들은 순수가상함수를 무조건 오버라이드해야된다
	virtual void Exit() = 0;

public:
	// 부모의 변수를 사용하기위해 protected를 사용할수있지만 에러의 범용성을 갖기위해 함수화로 진행 *교수st
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) 
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

public:
	CScene();
	virtual ~CScene();
};

