#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{

public:
	virtual void Enter(); // virtual�� �Ⱥٿ��� ���������Լ��� �νĵ����� ����� ǥ���� ���� virtual�� �����ش�
	virtual void Exit();

public:
	CScene_Start();
	~CScene_Start();
};

