#include "pch.h"
#include "CCore.h"
#include "CObject.h"

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

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100,100 };

	return S_OK;
}


void CCore::progress()
{
	static int callcount = 0; // ���α׷����� ȣ��Ǵ� ī��Ʈ
	++callcount;

	static int iPrevCount = GetTickCount(); // ���� ��� ������ ������ �ѹ��� �ʱ�ȭ ��
	int iCurCount = GetTickCount();
	if (iCurCount - iPrevCount > 1000) // 1�ʰ� �������� ��� ȣ��ƴ��� Ȯ���ϱ����� ����
	{
		iPrevCount = iCurCount;
		callcount = 0;
	}
	
	update();

	render();
	
}

void CCore::update()
{
	// Ű�� ���°��� �������� �Լ� * ������ ���ȴ� �������ִ� ���α׷� ������ ���ȴ� ��� ��Ʈ������ ��ȯ
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // �׳� Ű�� ���ȳ� Ȯ���غ�������� 0x8000 ��Ʈ���� and �����ڷ� Ȯ��
	{
		g_obj.m_ptPos.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
}

void CCore::render()
{
	// �׸���
	Rectangle(m_hDC,
			g_obj.m_ptPos.x- g_obj.m_ptScale.x / 2,
			g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2,
			g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2, 
			g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}
