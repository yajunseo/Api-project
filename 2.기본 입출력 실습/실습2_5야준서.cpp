#include <windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Windows program 2-5";

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1200, 800, NULL, (HMENU)NULL, hInstance, NULL);

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
	static TCHAR str[10][100];
	HDC hdc;
	SIZE size;


	static int enter = 0;
	static int Cpos = 0;
	static int count = 0;

	static bool isCAP = false;

	static int cx = 0;


	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 3, 15);
		ShowCaret(hWnd);
		break;
	case WM_KEYDOWN:

		if (GetAsyncKeyState(VK_LEFT) & 0x8000 != 0)
		{
			cx -= 5;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 != 0)
		{
			cx += 5;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000 != 0)
		{
			if (Cpos > 0)
				Cpos -= 1;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000 != 0)
		{
			if (Cpos < 10)
				Cpos += 1;
		}

		if (GetAsyncKeyState(VK_CAPITAL) & 0x8001)
		{
			isCAP = !isCAP;
		}

		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_CHAR:




		if (wParam == VK_RETURN || count >= 80)
		{
			if (enter == 9)
			{
				MessageBox(hWnd, _T("범위초과"), _T("에러"), MB_OK);
			}
			else
			{
				enter++;
				Cpos++;
				count = 0;
			}
		}

		else if (wParam == VK_BACK)
		{
			if (count == 0)
			{
				if (enter != 0)
				{
					enter--;
					Cpos--;
					count = wcslen(str[enter]);
				}
			}
			else
			{
				str[enter][--count] = '\0';
			}
		}

		else if (wParam == VK_ESCAPE)
		{
			count = 0;
			enter = 0;
			Cpos = 0;
			cx = 0;
			for (int i = 0; i < 10; i++)
				str[i][count] = '\0';
		}

		else if (wParam == VK_TAB)
		{

			for (int i = count; i < count + 4; i++)
			{
				str[enter][i] = ' ';
			}
			count += 4;
			str[enter][count] = '\0';
		}


		else
		{
			if (!isCAP)
			{
				if (wParam >= 65 && wParam <= 90)
					wParam += 32;
			}
			else
			{
				if (wParam >= 97 && wParam <= 122)
					wParam -= 32;
			}
			str[enter][count++] = wParam;
			str[enter][count] = '\0';
		}



		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);

		GetTextExtentPoint32(hdc, str[enter], wcslen(str[enter]), &size);
		for (int i = 0; i < 10; i++)
			TextOut(hdc, 0, i * 20, str[i], wcslen(str[i]));
		SetCaretPos(size.cx + cx, Cpos * 20);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

