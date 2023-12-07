#pragma once

class CObject; // ���漱��� ����Ÿ������ �𸣱⶧���� Ŭ����Ÿ���� �������� �׷��� ������ Ÿ���� ���

class CScene
{
private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

public:
	CScene();
	virtual ~CScene();
};

