// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND      g_hWnd; // 메인 윈도우핸들 전역변수화
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 지역
// 전역
// 정적 (데이터 영역)
// 1. 함수안에
// 2. 파일
// 3. 클래스
// 외부

class CClass {
    private :
        int m_i;
    public :
        static int m_iStatic; // 정적 멤버 (데이터영역)
        
    public : 
        // this가 약어로 있기때문에 객체로만 접근가능
        void func() {
            m_i = 0; // this가 약어로 있다
            m_iStatic = 0; // this가 약어로 없다
        }

        //정적 멤버함수, 객체없이 호출가능, this가 없다 (멤버 전급불가), 정적 멤버는 접근가능
        static void FUNC() {
            m_iStatic = 0;
        }
};

int CClass::m_iStatic = 0; // 정적멤버변수는 데이터영역에 올라갈거기때문에 꼭 초기화를 해줘야한다 안해주면 링크에러가 뜬다

//매크로 함수는 함수가아니라 전처리기때문에 그 부분을 정확히 인지해야한다
// int a = ADD(10,10) * 3 을했을때 10 + 10 * 3 으로 치환되기때문이다
#define ADD(a,b) a + b;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CClass a;
    a.func();

    CClass::FUNC();
    CClass::m_iStatic = 0;



    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //Core 초기화
    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{1280,768}))) {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // Get Message
    // 메세지큐에서 메세지 확인 될 때까지 대기
    // msg.message == WM_QUIT 일때 False 를 반환 -> 프로그램 종료
    // 게임으로 만들기에는 부적합

    // PeekMessage
    // 메세지 유무와 관계없이 항상 반환
    // 메세지큐에 메세지가있을경우 true 없을경우 false를 반환

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (WM_QUIT == msg.message) break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
      
        }
        else { // 메세지가 없는동안 호출

            // Game 코드 수행
            // 디자인 패턴 (설계 유형)
            // 싱글톤 패턴
            CCore::GetInst()->progress();
        }
        
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
// 이벤트가 발생하면넘어오는 message에서 wParam = 키보드 lParam = 마우스이다


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:  // 무효화 영역(Invalidate)이 발생한 경우 WM_PAINT 실행 
                    //옛날에는 창을 가린만큼 무효화영역이 일어졌지만 업데이트후 최소화 영역후 무효화 영역이 실행됌
        {
            //커널 오브젝트 : 윈도우가 관리하는 객체
            PAINTSTRUCT ps;

            // Device Context 커널 오브젝트를 만들어서 ID를 반환 HDC 관련 구조체 변수에 담음
            // HDC,HWND 이런 구조체의 자료는 int밖에없지만 구분을 위해 구조체를 만들어서 변수를 최소화 할려는 의도
            HDC hdc = BeginPaint(hWnd, &ps); // Device Context (그리기 관련 커널 오브젝트)

    
            //Rectangle(hdc, 1180, 0 , 1280, 100);
      

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN :
    {
    }
        break;

    case WM_LBUTTONDOWN : // 마우스 왼쪽버튼이 다운됐을때 실행되는 이벤트
    {
     
    }
        break;

    case WM_MOUSEMOVE : 

        break;

    case WM_LBUTTONUP: 
   
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
