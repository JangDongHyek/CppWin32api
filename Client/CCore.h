#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능하게 해야함

//class CCore {
//	private :
//		static CCore* g_pInst;
//
//	public :
//		// 정적 멤버함수
//		static CCore* GetInstance() {
//			// 정적 멤버변수 초기화는 딱 한번만 실행되기때문에 만약 여러번의 new가 실행되도 한번만 유지된다
//
//			// 최초 호출 된 경우
//			if (nullptr == g_pInst) {
//				g_pInst = new CCore;
//			}
//
//			return g_pInst;
//		}
//
//		static void Release() {
//			if (nullptr != g_pInst) {
//				delete g_pInst;
//				//g_pInst 를 힙메모리에서 삭제하면 g_pInst의 값은 삭제된 주소값을 들고있기떄문에 널값으로로 초기화
//				g_pInst = nullptr;
//			}
//		}
//	private:
//		CCore();
//		~CCore();
//};

#include "define.h";
class CCore {
	SINGLE(CCore);
		//static CCore* GetInst() {
			//정적 멤버는 초기화가 한번만 일어나기때문에 한번만 생성이됌 즉 같은 core를 계속 반환해준다
			// 클래스 내부이므로 생성자를 사용할수있기때문에 생성자로 객체생성 *정적멤버기때문에 데이터영역에 생성된다
			//static CCore core;

			//반환을 주소로주기떄문에 해당 객체에 접근해서 수정을 할수있다
			//데이터 영역에 생성되기때문에 내가 일일히 삭제를 해줄필요가없다
			//return &core;
		//}
	private : 
		HWND	m_hWnd; //메인 윈도우 핸들
		POINT	m_ptResolution; // 메인 윈도우 해상도
	public:
		int init(HWND _hWnd, POINT _ptResolution);
		void progress();

	private:
		CCore();
		~CCore();
};