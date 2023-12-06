#pragma once

// �̱��� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� �����ϰ� �ؾ���

class CCore {
	private :
		static CCore* g_pInst;

	public :
		// ���� ����Լ�
		static CCore* GetInstance() {
			// ���� ������� �ʱ�ȭ�� �� �ѹ��� ����Ǳ⶧���� ���� �������� new�� ����ǵ� �ѹ��� �����ȴ�

			// ���� ȣ�� �� ���
			if (nullptr == g_pInst) {
				g_pInst = new CCore;
			}

			return g_pInst;
		}

		static void Release() {
			if (nullptr != g_pInst) {
				delete g_pInst;
				//g_pInst �� ���޸𸮿��� �����ϸ� g_pInst�� ���� ������ �ּҰ��� ����ֱ⋚���� �ΰ����η� �ʱ�ȭ
				g_pInst = nullptr;
			}
		}
	private:
		CCore();
		~CCore();
};

