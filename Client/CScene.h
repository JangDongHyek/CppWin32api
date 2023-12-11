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

	// ��ӹ��� �ֵ� ��� update,render�� ����Ұű� ������ �θ��ʿ��� ����
	void update();
	void render(HDC _dc);

	virtual void Enter() = 0; // = 0 �̰Ÿ� ������ ���������Լ� (�߻�ȭŬ����) �� �ǰ� �ش� �θ� ����ϴ¾ֵ��� ���������Լ��� ������ �������̵��ؾߵȴ�
	virtual void Exit() = 0;

public:
	// �θ��� ������ ����ϱ����� protected�� ����Ҽ������� ������ ���뼺�� �������� �Լ�ȭ�� ���� *����st
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) 
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

public:
	CScene();
	virtual ~CScene();
};

