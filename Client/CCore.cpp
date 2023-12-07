#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
//CCore* CCore::g_pInst = nullptr; // ���������⶧���� �ʱ�ȭ �ѹ�



CObject g_obj;


CCore::CCore() 
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{

}

CCore::~CCore() 
{
	ReleaseDC(m_hWnd, m_hDC); // Ŀ�� ������Ʈ DC ����
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	//�ػ󵵿� �°� ������ ũ�� ����
	//������ ������ �°� ũ�⸦ �����ϴ� �Լ� * �������� Ÿ��Ʋ�� �޴��� ũ�Ⱑ�ֱ⶧���� ���ϴ� �ػ󵵸� ������ �۾������� ���ϴ� �ػ󵵸�ŭ ����� �۾����� + �ٸ�ũ��������ϱ�����
	RECT rt = {0,0, m_ptResolution.x,m_ptResolution.y}; // �Լ��� rect ����ü�� �����͸� �䱸�ϱ⋚���� rect ����ü ����
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW,true); // rt ����ü�� ���� ä����
	// ������ ũ�� ����
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();



	g_obj.SetPos(Vec2((float) (m_ptResolution.x / 2), (float) (m_ptResolution.y / 2 )));
	g_obj.SetScale(Vec2( 100,100 ));

	return S_OK;
}


void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();

	update();

	render();
	
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	// Ű�� ���°��� �������� �Լ� * ������ ���ȴ� �������ִ� ���α׷� ������ ���ȴ� ��� ��Ʈ������ ��ȯ
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // �׳� Ű�� ���ȳ� Ȯ���غ�������� 0x8000 ��Ʈ���� and �����ڷ� Ȯ��
	{
		//���ؿ� DT������ �ʴ� �̵����� ���� ��Ų��
		vPos.x -= 100.f * CTimeMgr::GetInst()->GetfDT();
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 100.f * CTimeMgr::GetInst()->GetfDT();
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// �׸���
	Rectangle(m_hDC,
			int(vPos.x - vScale.x / 2.f),
			int(vPos.y - vScale.y / 2.f),
			int(vPos.x + vScale.x / 2.f), 
			int(vPos.y + vScale.y / 2.f));
}
