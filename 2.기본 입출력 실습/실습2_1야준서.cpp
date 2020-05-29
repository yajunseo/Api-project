#include <windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Windows program 2-1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 300, 200, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;


	switch (uMsg) {
	case WM_CREATE:
		break;
	
	case WM_PAINT:
		GetClientRect(hWnd, &rect);

		hdc = BeginPaint(hWnd, &ps);
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(159, 201, 60));
		DrawText(hdc, _T("Left-top"), wcslen(_T("Left-top")), &rect, NULL);

		SetTextColor(hdc, RGB(1, 0, 255));
		SetBkColor(hdc, RGB(153, 0, 133));
		DrawText(hdc, _T("Right-top"), wcslen(_T("Right-top")), &rect, DT_RIGHT);

		SetTextColor(hdc, RGB(255, 0, 221));
		SetBkColor(hdc, RGB(140, 140, 140));
		DrawText(hdc, _T("Center"), wcslen(_T("Center")), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		SetTextColor(hdc, RGB(250, 244, 192));
		SetBkColor(hdc, RGB(0, 130, 153));
		DrawText(hdc, _T("Left-bottom"), wcslen(_T("Left-bottom")), &rect, DT_SINGLELINE | DT_BOTTOM);

		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(255, 187, 0));
		DrawText(hdc, _T("Right-bottom"), wcslen(_T("Right-bottom")), &rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);


		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

