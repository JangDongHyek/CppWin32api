#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"


CCore::CCore() 
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{

}

CCore::~CCore() 
{
	ReleaseDC(m_hWnd, m_hDC); // Ŀ�� ������Ʈ DC ����

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
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

	// ���α׷��� �۾������� ��Ʈ���̶� Ī�Ѵ�
	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC �� �����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // DC�� ȣȯ�� ��Ʈ�� ����
	m_memDC = CreateCompatibleDC(m_hDC); // ȣȯ�� ��Ʈ�ʿ� �����ų DC ����

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // ��ȯ�Ǵ� ������ DC�� ������ �������ִ� 1�ȼ�ũ���� ��Ʈ���� ��ȯ�ȴ�
	DeleteObject(hOldBit); // ������� ���� ��Ʈ�� Ŀ�� ������Ʈ ����

	// Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();


	return S_OK;
}


void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();

	//=========
	//Rendering
	//=========
	// ȭ�� Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);
}

