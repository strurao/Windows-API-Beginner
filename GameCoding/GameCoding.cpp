#include "pch.h"
#include "framework.h"
#include "GameCoding.h"
#include "Game.h"

#define MAX_LOADSTRING 100

int mousePosX;
int mousePosY;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 프로그램의 시작점
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // *****별 다섯개 (1) 윈도우 창 정보 등록
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다: *****별 다섯개 (2) 윈도우 창 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    Game game;
    game.Init(g_hWnd);

    MSG msg = {};
    uint64 prevTick = 0;

    // 기본 메시지 루프입니다: ****별 다섯개 (3) 메인 루프
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            ::TranslateMessage(&msg); // msg 추가
            ::DispatchMessage(&msg); // msg 처리하는 부분
        }
        else
        {
            uint64 now = GetTickCount64();

            // if (now - prevTick >= 30)
            {
                game.Update();
                game.Render();

                prevTick = now;
            }

            // 게임로직
            game.Update();
            game.Render();
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
    wcex.lpfnWndProc    = WndProc; // 콜백함수. msg 처리 시 첫번째로 호출됨.
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMECODING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    // wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAMECODING);
    // wcex.lpszClassName  = szWindowClass;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"Onsenhyo";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); // 끝에 W가 붙어
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

   RECT windowRect = { 0, 0, 800, 600 };
   ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

   HWND hWnd = CreateWindowW(L"Onsenhyo", L"Onsenhyo's Game", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, nullptr);

   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ::ShowWindow(hWnd, nCmdShow);
   ::UpdateWindow(hWnd);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 메시지 처리기
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps); // 구별을 위한 식별 int
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // 문자
            WCHAR buffer[100];
            ::wsprintf(buffer, L"(%d, %d)", mousePosX, mousePosY);
            ::TextOut(hdc, 100, 100, buffer, ::wcslen(buffer));
            //hdc 라는 도화지의 100,100 좌표에 TEST라는 문자열을 출력하고, 문자열 길이는 4이다

            // 사각형
            ::Rectangle(hdc, 200, 200, 400, 400);

            // 원
            ::Ellipse(hdc, 200, 200, 400, 400);

            // 선
            ::MoveToEx(hdc, 300, 300, nullptr);
            ::LineTo(hdc, 400, 400);
            ::LineTo(hdc, 600, 300);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_MOUSEMOVE:
        // 정수긴 정수인데
        
        mousePosX = LOWORD(lParam);
        mousePosY = HIWORD(lParam);
        ::InvalidateRect(hWnd, nullptr, TRUE);

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
