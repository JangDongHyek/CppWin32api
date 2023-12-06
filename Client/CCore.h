#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능하게 해야함

class CCore {
	private :
		static CCore* g_pInst;

	public :
		// 정적 멤버함수
		static CCore* GetInstance() {
			// 정적 멤버변수 초기화는 딱 한번만 실행되기때문에 만약 여러번의 new가 실행되도 한번만 유지된다

			// 최초 호출 된 경우
			if (nullptr == g_pInst) {
				g_pInst = new CCore;
			}

			return g_pInst;
		}

		static void Release() {
			if (nullptr != g_pInst) {
				delete g_pInst;
				//g_pInst 를 힙메모리에서 삭제하면 g_pInst의 값은 삭제된 주소값을 들고있기떄문에 널값으로로 초기화
				g_pInst = nullptr;
			}
		}
	private:
		CCore();
		~CCore();
};

