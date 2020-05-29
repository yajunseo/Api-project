#include <windows.h>
#include <tchar.h>
#include <string>



HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Windows program 2-4";

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
	HDC hdc;
	static TCHAR str[100];
	static TCHAR xpos[100];
	static TCHAR ypos[100];
	static TCHAR num[100];

	static int count = 0;
	static int Xcount = 0;
	static int Ycount = 0;
	static int Ncount = 0;

	static int space = 0;
	SIZE size;

	static int x, y, n;

	static TCHAR nine[9][100];
	static int row = 1;

	bool isResult = false;
	bool isOver = false;

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 3, 15);
		ShowCaret(hWnd);
		break;

	case WM_CHAR:


		if (wParam == VK_SPACE || wParam == VK_RETURN)
		{
			space++;
			str[count++] = ' ';
			str[count] = '\0';
		}
		else
		{
			str[count++] = wParam;
			str[count] = '\0';
			if (space == 0)
				Xcount++;
			else if (space == 1)
				Ycount++;
			else if (space == 2)
			{
				Ncount++;
				isOver = false;
			}
		}

		if (space >= 3)
			isResult = true;

		if (isResult)
		{
			int c = 0;
			for (int i = 0; i < count; i++)
				xpos[i] = str[i];

			for (int i = Xcount + 1; i < Xcount + 1 + Ycount; i++)
			{
				ypos[c] = str[i];
				c++;
			}
			c = 0;

			for (int i = Xcount + Ycount + 2; i < count; i++)
			{
				num[c] = str[i];
				c++;
			}

			x = _ttoi(xpos);
			y = _ttoi(ypos);
			n = _ttoi(num);
			if (n == 0)
				DestroyWindow(hWnd);

			else if (n < 2 || n>9)
			{
				str[0] = '\0';
				count = 0;
				Xcount = 0;
				Ycount = 0;
				Ncount = 0;
				space = 0;
				MessageBox(hWnd, _T("잘못된 숫자 입력"), _T("에러"), MB_OK);
				isOver = true;

			}


			if (!isOver)
			{
				for (int i = 1; i < 10; i++)
				{
					wsprintf(nine[i], _T("%d*%d = %d"), n, i, n * i);

				}

				str[0] = '\0';
				count = 0;
				Xcount = 0;
				Ycount = 0;
				Ncount = 0;
				space = 0;
			}
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);

		GetTextExtentPoint32(hdc, str, wcslen(str), &size);
		TextOut(hdc, 0, 0, str, wcslen(str));
		SetCaretPos(size.cx, 0);


		for (int i = 1; i < 10; i++)
		{
			TextOut(hdc, x, y + (i - 1) * 13, nine[i], wcslen(nine[i]));
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

