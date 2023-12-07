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

public:
	CScene();
	virtual ~CScene();
};

