// Win32_ASTR_youtube_lec_5.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Win32_ASTR_youtube_lec_5.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// timer를 위해 hWnd를 전역으로 관리
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32ASTRYOUTUBELEC5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32ASTRYOUTUBELEC5));

    MSG msg;

    // case WM_TIME: 호출됨
    //SetTimer(g_hWnd, 777, 0, nullptr); // 지연시간 0 (최대 프레임)
    // -> 다만 매우 느리고 비효율적이라서 frame을 이렇게 짜지는 않는다. (테스트만)

    //while (GetMessage(&msg, nullptr, 0, 0)) -> 메세지가 있어야만 true (게임에 부적합)
    // msg.message == WM_QUIT 인 경우 false를 반환 -> 프로그램 종료

    // 메세지가 있는 동안 / 없는 동안 [비율] 확인해보기 -> PeekMessage()를 사용하는 이유 파악
    int iExistCnt = 0;
    int iNoExistCnt = 0;

    while (true) // 메세지 유무와 관계없이 반환
    { // PM_REMOVE 옵션을 추가로 줘야 -> 읽은 메시지는 지운다. (이렇게 해야 GetMessage와 비슷)
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // PeekMessage의 message가 WM_QUIT인 경우 (종료)
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            ++iExistCnt;
        }
        // 메세지가 발생하지 않는, 대부분의 시간
        else
        {
            ++iNoExistCnt;

            // Game 코드 수행
            // 디자인 패턴 (설계 유형)
            // (다른 패턴들은 천천히 알아가도 되지만, Singleton 패턴은 필수적으로 숙지해야 한다.)
            {

            }
        }
        float fRatio = (float)iExistCnt / iNoExistCnt * 100;
        WCHAR szBuff[50] = {};
        //wsprintf(szBuff, L"비율 : %f", fRatio); // 실수 출력 못함
        swprintf_s(szBuff, L"비율 : %f", fRatio);
        SetWindowText(g_hWnd, szBuff);
        if (iNoExistCnt > 10000)
        {
            iExistCnt = 0;
            iNoExistCnt = 0;
        }
    }

    // timer도 커널 오브젝트이므로, 사용 후 제거해줘야 한다.
    //KillTimer(g_hWnd, 777); // id가 777인 timer 해제

    return (int) msg.wParam;
}

//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32ASTRYOUTUBELEC5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32ASTRYOUTUBELEC5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.

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

//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.

#include <vector>
using std::vector;

struct tObjInfo
{
    POINT g_ptObjPos;
    POINT g_ptObjScale;
};

vector<tObjInfo> g_vecInfo;

POINT g_ptLT; // 좌상단
POINT g_ptRB; // 우하단
bool bLBtnDown = false;

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

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
        HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
        HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

        /*Rectangle(hdc,
            g_ptObjPos.x - g_ptObjScale.x / 2,
            g_ptObjPos.y - g_ptObjScale.y / 2,
            g_ptObjPos.x + g_ptObjScale.x / 2,
            g_ptObjPos.y + g_ptObjScale.y / 2);*/
        
        // 그려질 사각형 모습 미리보기
        if (bLBtnDown)
        {
            Rectangle(hdc,
                g_ptLT.x, g_ptLT.y, g_ptRB.x, g_ptRB.y);
        }

        // 최종 저장된 그림들(범위) 출력하는 반복문
        for (auto it = g_vecInfo.begin(); it != g_vecInfo.end(); ++it)
        {
            Rectangle(hdc,
                it->g_ptObjPos.x - (it->g_ptObjScale.x / 2),
                it->g_ptObjPos.y - (it->g_ptObjScale.y / 2),
                it->g_ptObjPos.x + (it->g_ptObjScale.x / 2),
                it->g_ptObjPos.y + (it->g_ptObjScale.y / 2) );
        }

        SelectObject(hdc, hDefaultPen);     DeleteObject(hRedPen);
        SelectObject(hdc, hDefaultBrush);   DeleteObject(hBlueBrush);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_KEYDOWN:
    {
        //switch (wParam)
        //{
        //    /*case VK_UP:
        //        break; */
        //case 'W':
        //    g_ptObjPos.y -= 15;
        //    break;
        //case 'A':
        //    g_ptObjPos.x -= 15;
        //    break;
        //case 'S':
        //    g_ptObjPos.y += 15;
        //    break;
        //case 'D':
        //    g_ptObjPos.x += 15;
        //    break;
        //}
        InvalidateRect(hWnd, nullptr, true);
    }
    break;

    case WM_LBUTTONDOWN:
    {
        g_ptLT.x = LOWORD(lParam); // word의 상위 8바이트는 클릭된 x 좌표
        g_ptLT.y = HIWORD(lParam); // word의 하위 8바이트는 클릭된 y 좌표
        bLBtnDown = true;
    }
    break;

    case WM_MOUSEMOVE:
    {
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
        //-> 이게 엄청 느린 작업이라서, fRatio 값 비율이 그나마 올랐단 것이었고,
        //  매우 비효율적이라 이제 안쓸거라 주석했더니, 그나마 올랐던 것도 1% 대로 떨어졌다.
        //  (강사 컴퓨터에서는 0% 만 찍혔다.)
    }
    break;

    case WM_LBUTTONUP:
    {
        tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptRB.x + g_ptLT.x) / 2;
        info.g_ptObjPos.y = (g_ptRB.y + g_ptLT.y) / 2;
        info.g_ptObjScale.x = abs(g_ptRB.x - g_ptLT.x); // abs 안해도 음수 자동 양수화
        info.g_ptObjScale.y = abs(g_ptRB.y - g_ptLT.y);

        g_vecInfo.push_back(info);
        bLBtnDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }
    break;

    // SetTimer의 지연시간 설정에 따른 호출됨
    case WM_TIMER:
    {
        int a = 0;
    }

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
