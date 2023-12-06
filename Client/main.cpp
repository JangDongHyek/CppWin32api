// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Client.h"
#include "CCore.h";

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

#include <vector>
using std::vector;

// 오브젝트 구조체 생성
struct tObjInfo {
    POINT g_ptObjPos;
    POINT g_ptObjScale;
};
// 오브젝트를 관리할 벡터
vector<tObjInfo> g_vecInfo;

// 마우스 왼쪽상단
POINT g_ptLT;
// 마우스 오른쪽 하단
POINT g_ptRB;
// 마우스 클릭 이벤트 체크용 불
bool bLbtnDown = false;

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
            // DC 의 목적지는 hWnd
            // DC 의 펜은 기본펜 (Black)
            // DC 의 브러쉬는 기본 브러쉬 (White)

            //직접 펜을 만들어서 DC 에 지급
            HPEN hRedPen = CreatePen(PS_SOLID,1,RGB(255,0,0));

            // SelectObject 함수는 범용적인 함수이기때문에 반환되는 값 HGDIOBJ는 보이드타입이다 그래서 HPEN으로 캐스팅후 받아준다
            // 돌아오는 값은 전에 적용되어있던 오브젝트값이 반환된다 즉 지금은 펜을 바꿔줬으니 DefaultPen값인 커널 오브젝트가 반환된다
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);

            // 자주 사용하는 색이나 코드들은 사용하기 편하게 ms에서 제공해준다 그게 해당 함수 GetStockObject이다 
            // docsMS 들어가서 확인하여 사용하면 간편하다
            HBRUSH hDkGray = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hDkGray);

            
            
            //윈도우 핸들
            //윈도우 좌표 // pixcel 단위 pixcel 은 RGB로 이루어져 3바이트다
            // HDC?
            
            // 마우스 왼쪽이 클릭한 상태면
            if (bLbtnDown) {
                Rectangle(hdc, g_ptLT.x, g_ptLT.y,
                    g_ptRB.x, g_ptRB.y);
            }

            // 마우스 이벤트로 생성된 오브젝트들 화면에 생성
            for (size_t i = 0; i < g_vecInfo.size(); ++i) {
                Rectangle(hdc,
                        g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2,
                        g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2,
                        g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2,
                        g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
            }
            

            //기본 펜으로 다시 돌려준다
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);
            
            //빨간펜은 역확을 다 해서 삭제해준다
            // 여기서 delete 함수를 쓰지않고 DeleteObject를 사용하는 이유는 os가 관리하는 커널오브젝트이기때문에 os함수를 사용해 객체를 삭제
            DeleteObject(hRedPen);
            DeleteObject(hDkGray);

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN :
    {
        switch (wParam) {
        case VK_UP :
            //g_ptObjPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true); // 무효화영역을 강제로 발생 시키는 함수 (윈도우핸들,영역 *널값을 넣어주면 전체영억으로 지정,화면을 클리어할지안할지)
            break;

        case VK_DOWN :
            //g_ptObjPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_LEFT:
            //g_ptObjPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_RIGHT:
            //g_ptObjPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case 'W' : // 키보드의 영문쪽에 들어오는 애들은 아스키코드로 들어온다 즉 w랑 W랑 다르기때문에 해당 애들은 대문자로 구분한다

            break;
        }
    }
        break;

    case WM_LBUTTONDOWN : // 마우스 왼쪽버튼이 다운됐을때 실행되는 이벤트
    {
        //lParam 에 들어오는 정보는 마우스좌표이다 해당구조체는 int64로 아마 아키텍쳐의 정보를 따라가는듯하다 32비트면 int32
        //x좌표y좌표 반반씩 자리를 차지하며 64비트일땐 8바이트로 4바이트씩 자리를 차지하는것같다
        g_ptLT.x = LOWORD(lParam); // 매크로함수로 인해 x 좌표를 알수있다
        g_ptLT.y = HIWORD(lParam); // ''
        bLbtnDown = true;
    }
        break;

    case WM_MOUSEMOVE : 
    {
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
    }
        break;

    case WM_LBUTTONUP: 
    {
        // 마우스이벤트가 끝날떄 실행되는 부분
        tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbtnDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_TIMER : // SetTimer 함수로 들어오는 정해진 시간마다 들어오는 콜백 이벤트 부분
    {

    }
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
