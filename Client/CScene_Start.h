#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{

public:
	virtual void Enter(); // virtual을 안붙여도 순수가상함수로 인식되지만 명시적 표현을 위해 virtual을 적어준다
	virtual void Exit();

public:
	CScene_Start();
	~CScene_Start();
};

