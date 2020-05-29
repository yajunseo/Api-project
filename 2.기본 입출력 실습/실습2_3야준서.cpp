#include <windows.h>
#include <tchar.h>
#include <time.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Windows program 2-3";

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

void DrawObject(HDC hdc, RECT rc)
{
	srand((DWORD)GetTickCount());
	int w = rand() % 26;
	TCHAR str[1];
	str[0] = w + 97;
	int width = (rc.right - rc.left) < (rc.bottom - rc.top) ? (rc.right - rc.left) : (rc.bottom - rc.top);
	TextOut(hdc, rc.left, rc.top, str, 1);
	int n = rand() % 5;

	switch (n)
	{
	case 0:
		for (int i = 0; i < width / 2; i += 13)
		{
			for (int j = 0; j < width; j += 13)
			{
				if (i <= j && j < width - i)
					TextOut(hdc, j + rc.left, i + rc.top, str, 1);

			}

		}
		break;
	
	case 1:
		for (int i = 0; i < width / 4; i+=13)
		{
			for (int j = 0; j < width; j += 13)
			{
				if (j >= i * 2 && j < width - i * 2)
					TextOut(hdc, j + rc.left, i + rc.top, str, 1);

			}

		}

		for (int i = width / 4 + 1; i <= width / 2; i += 13)
		{
			for (int j = 0; j < width; j += 13)
			{
				if (j < i * 2 && j >= width - i * 2)
					TextOut(hdc, j + rc.left, i + rc.top, str, 1);

			}

		}
		break;
		
	case 2:
		for (int i = 0; i < width / 4; i+=13)
		{
			for (int j = 0; j < width; j+= 13)
			{
				if (j < (1 + i * 2) || j >(width - 2 - (i * 2)))
					TextOut(hdc, j + rc.left, i + rc.top, str, 1);

			}

		}

		if (width % 4 == 0)
		{
			for (int j = 0; j < width; j+= 13)
				TextOut(hdc, j + rc.left, width/2 + rc.top, str, 1);

		}

		for (int i = width / 4; i < width / 2; i++)
		{
			for (int j = 0; j < width; j+= 13)
			{

				if (j >= (1 + i * 2) || j <= (width - 2 - (i * 2)))
					TextOut(hdc, j + rc.left, i + rc.top, str, 1);


			}

		}
		break;
		
	case 3:
		if (width % 4 != 0)
		{
			for (int i = 1; i < width + 1; i += 26)
			{
				for (int j = 1; j < width + 1; j += 13)
				{
					if (i < width / 2)
					{
						if (width / 2 + 1 - i <= j && width / 2 + i >= j)
							TextOut(hdc, j + rc.left, i + rc.top, str, 1);

					}

					else
					{
						int k = i - (width / 2);
						if (k < j && width - k >= j)
							TextOut(hdc, j + rc.left, i + rc.top, str, 1);

					}
				}

			}
		}
		else
		{
			for (int i = 1; i < width + 1; i += 26)
			{
				if (i == 1)
					for (int j = 1; j < width + 1; j += 13)
					{
						if (j == width / 2 + 1)
							TextOut(hdc, j + rc.left, i + rc.top, str, 1);

					}
				else
				{
					for (int j = 1; j < width + 1; j += 13)
					{
						if (i < width / 2)
						{
							if (width / 2 + 1 - i < j && width / 2 + i > j)
								TextOut(hdc, j + rc.left, i + rc.top, str, 1);

						}

						else
						{
							int k = i - (width / 2);
							if (k <= j && width - k + 2 > j)
								TextOut(hdc, j + rc.left, i + rc.top, str, 1);

						}
					}
				}

			}
			for (int j = 1; j < width + 1; j += 13)
			{
				if (j == width / 2 + 1)
					TextOut(hdc, j + rc.left, width / 2 + rc.top, str, 1);

			}

		}
		break;
	
	case 4:
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (i % 2 == 0)
				{
					if (i == width / 2 - 1)
					{
						for (int k = 0; k < width; k++)
						{
							if (k == width / 2)
								TextOut(hdc, j + rc.left, i + rc.top, str, 1);

						}
						break;
					}

					else {
						if (i < width / 2)
						{
							if (j == i || j == (width - i) - 1)
								TextOut(hdc, j + rc.left, i + rc.top, str, 1);

						}
						else
						{
							if (j == i + 1 || j == (width - i) - 2)
								TextOut(hdc, j + rc.left, i + rc.top, str, 1);

						}
					}
				}
			}
		}
		break;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	srand((DWORD)GetTickCount());
	int row = rand() % 9 + 2;
	int line = rand() % 9 + 2;
	RECT rc;
	GetClientRect(hWnd, &rc);
	int width = rc.right / row;
	int height = rc.bottom / line;
	int r, g, b;
	int rb, gb, bb;

	HDC hdc;
	switch (uMsg) {
	case WM_CREATE:
		break;

	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < line; j++)
			{
				rc = { i * width, j * height, (i + 1) * width, (j + 1) * height };
				
				r = rand() % 256;
				g = rand() % 256;
				b = rand() % 256;
				rb = rand() % 256;
				gb = rand() % 256;
				bb = rand() % 256;

				SetTextColor(hdc, RGB(r, g, b));
				SetBkColor(hdc, RGB(rb, gb, bb));

				DrawObject(hdc, rc);
				Sleep(50);
			}
		}


		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

