// Blocked32.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Blocked32.h"
#include "time.h"
#include "Resource.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

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
    LoadStringW(hInstance, IDC_BLOCKED32, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BLOCKED32));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLOCKED32));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BLOCKED32);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 1200, 800, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
    srand(DWORD(GetTickCount()));
    HDC memdc;
    RECT rc;
    GetClientRect(hWnd, &rc);
    float width = rc.right - rc.left;
    float height = rc.bottom - rc.top;
    float blockWidth = height / 6;
    int x, y;
    static int chanceClickNumber = 0;
    static bool isChanceClick = false;
    static int chanceNum = 0;
    static int chanceCount = 0;

    RECT chance1 = { blockWidth  * 6 + 50,blockWidth * 2, blockWidth * 7 + 50 ,blockWidth * 3 };
    RECT chance2 = { chance1.right, blockWidth * 2, chance1.right + blockWidth ,blockWidth * 3 };
    RECT chance3 = { chance2.right, blockWidth * 2, chance2.right + blockWidth ,blockWidth * 3 };

    HBITMAP hBitmap;
    BITMAP bmp;
    TCHAR str[100];

    static bool isStart = false;
    static int obstacleCnt = 2;
    static int goal = 32;

    static int arr[6][6][2] = { 0, };  // 0: 없음  1:장애물  2:숫자블럭 //  숫자
    int obstacleX, obstacleY;
    switch (message)
    {
    case WM_CREATE:
        chanceNum = rand() % 3 + 1;
        wsprintf(str,_T("찬스 횟수: %d 번"), chanceCount);
        obstacleX = rand() % 6;
        obstacleY = rand() % 6;
        arr[obstacleX][obstacleY][1] = 1;
        obstacleX = rand() % 6;
        obstacleY = rand() % 6;
        arr[obstacleX][obstacleY][1] = 1;
        obstacleX = rand() % 6;
        obstacleY = rand() % 6;
        arr[obstacleX][obstacleY][1] = 2;
        arr[obstacleX][obstacleY][2] = 2;
        obstacleX = rand() % 6;
        obstacleY = rand() % 6;
        arr[obstacleX][obstacleY][1] = 2;
        arr[obstacleX][obstacleY][2] = 2;
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_START:
                break;
            case ID_32771:
                isStart = true;
                break;
            case ID_32772:
                DestroyWindow(hWnd);
                break;
            case IDM_ABOUT:
                obstacleCnt = 2;
                isStart = false;
                break;
            case ID_32773:
                obstacleCnt = 3;
                isStart = false;
                break;
            case ID_32774:
                obstacleCnt = 4;
                isStart = false;
                break;
            case ID_32775:
                goal = 32;
                isStart = false;
                break;
            case ID_32776:
                goal = 64;
                isStart = false;
                break;
            case ID_32777:
                goal = 128;
                isStart = false;
                break;
            case ID_32778:
                goal = 256;
                isStart = false;
                break;
            case IDM_EXIT:
  
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        if (!isStart && !isChanceClick)
        {
            if(chance1.left<= x && x<=chance1.right && chance1.top <= y && y <= chance1.bottom)
                chanceClickNumber = 1;
            else if (chance2.left <= x && x <= chance2.right && chance2.top <= y && y <= chance2.bottom)
                chanceClickNumber = 2;
            else if (chance3.left <= x && x <= chance3.right && chance3.top <= y && y <= chance3.bottom)
                chanceClickNumber = 3;
      
            isChanceClick = true;
        }
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            memdc = CreateCompatibleDC(hdc);
            hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP11));
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            for (int i = 0; i <= 6; i++)
            {
                MoveToEx(hdc, rc.left, i * blockWidth, NULL);
                LineTo(hdc, blockWidth * 6, i * blockWidth);
                MoveToEx(hdc, i * blockWidth, rc.top, NULL);
                LineTo(hdc, i * blockWidth, rc.bottom);
            }
            Rectangle(hdc, chance1.left, chance1.top, chance1.right, chance1.bottom);
            Rectangle(hdc, chance2.left, chance2.top, chance2.right, chance2.bottom);
            Rectangle(hdc, chance3.left, chance3.top, chance3.right, chance3.bottom);

            if (!isStart)
            {
                if (chanceNum == 1)
                {
                    DeleteObject(hBitmap);
                    hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
                }
                else if (chanceNum == 2)
                {
                    DeleteObject(hBitmap);
                    hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
                }
                else if (chanceNum == 3)
                {
                    DeleteObject(hBitmap);
                    hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
                }
                if (chanceCount == 0)
                {
                    chanceCount = chanceNum;
                }
             
                
                SelectObject(memdc, hBitmap);
                GetObject(hBitmap, sizeof(BITMAP), &bmp);
                if (chanceClickNumber != 0)
                {
                    if (chanceClickNumber == 1)
                        StretchBlt(hdc, chance1.left + 5, chance1.top + 5, blockWidth - 10, blockWidth - 10, memdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
                    else if (chanceClickNumber == 2)
                        StretchBlt(hdc, chance2.left + 5, chance2.top + 5, blockWidth - 10, blockWidth - 10, memdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
                    else if (chanceClickNumber == 3)
                        StretchBlt(hdc, chance3.left + 5, chance3.top + 5, blockWidth - 10, blockWidth - 10, memdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

                }
            /*    DeleteObject(hBitmap);
                DeleteDC(memdc);*/
            }
            else if(isStart)
            {
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        if (arr[i][j][1] == 1)
                        {
                            hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP12));
                            GetObject(hBitmap, sizeof(BITMAP), &bmp);
                            SelectObject(memdc, hBitmap);
                            StretchBlt(hdc, j* blockWidth , i * blockWidth , blockWidth + 1 , blockWidth +1,  memdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
                        }
                        else if (arr[i][j][1] == 2)
                        {
                            if (arr[i][j][2] == 2)
                                hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));

                            GetObject(hBitmap, sizeof(BITMAP), &bmp);
                            SelectObject(memdc, hBitmap);
                            StretchBlt(hdc, j* blockWidth + 5, i* blockWidth + 5, blockWidth - 10, blockWidth - 10, memdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

                        }
                    }
                }
              
            }


            wsprintf(str, _T("찬스 횟수: %d 번"), chanceCount);
            TextOut(hdc, rc.right - 120, rc.top + 5, str, wcslen(str));

            DeleteObject(hBitmap);
            DeleteDC(memdc);
            EndPaint(hWnd, &ps);
        }
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
