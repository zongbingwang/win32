
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(	//程序入口，WINAPI是一种函数调用约定，用于表明如何生成在堆栈中放置调用参数的机器代码
	HINSTANCE hInstance  //实例句柄，标识该程序
	, HINSTANCE hPreInstance  //16位中用于标识该程序前一实例，32位中不再采用，参数为NULL
	, LPSTR szCmdLine  //调用时的命令行
	, int iCmdShow)   //窗口显示方式
{
	static TCHAR szName[] = TEXT("HIYUN");
	HWND hwnd;
	MSG msg;
	WNDCLASS wc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szName;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("注册失败！"), TEXT("失败"), MB_OK | MB_ICONERROR);
	}

	hwnd = CreateWindow(szName, TEXT("别踩白块儿之禅模式 - 闲云野鹤制作，QQ群116920287"), WS_OVERLAPPEDWINDOW,
		400, 100, 400, 600,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	TCHAR szBuff[50];
	static HBRUSH brushPass = CreateSolidBrush(RGB(223, 223, 223));
	static int i, j, x, y, tx, ty;
	static int runing, cxChar, cyChar, cxClient, cyClient, cxSquare, cySquare;
	static TCHAR PlayName[] = TEXT("YUN");
	static ULONG score = 0, t;
	static int Loc[20];

	switch (message)
	{
	case WM_CREATE:
		runing = 0;
		hdc = GetDC(hwnd);
		TEXTMETRIC tm;
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lparam);
		cyClient = HIWORD(lparam);
		cxSquare = cxClient / 4;
		cySquare = (int)(cxSquare * 1.5);
		for (i = 0; i <= cyClient / cySquare + 2; ++i)
		{
			Loc[i] = rand() % 4;
		}
		return 0;
	case WM_LBUTTONDOWN:
		tx = x = LOWORD(lparam);
		ty = y = HIWORD(lparam);
		x /= cxSquare;
		y = (cyClient - y) / cySquare;
		if (Loc[0] == x && y == 0 && !runing)
		{
			runing = 1;
			InvalidateRect(hwnd, NULL, true);
		}
		else if (Loc[1] == x && y == 1 && runing)
		{
			score++;
			for (i = 0; i <= cyClient / cySquare + 1; ++i)
			{
				Loc[i] = Loc[i + 1];
			}
			Loc[i] = rand() % 4;
			InvalidateRect(hwnd, NULL, true);
		}

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 0, 0));

		for (i = 1; i < 4; ++i)
		{
			MoveToEx(hdc, cxSquare * i, 0, NULL);
			LineTo(hdc, cxSquare * i, cyClient);
		}
		for (i = 0; i <= cyClient / cySquare + 1; ++i)
		{
			MoveToEx(hdc, 0, cyClient - cySquare * i, NULL);
			LineTo(hdc, cxClient, cyClient - cySquare * i);
			j = Loc[i];
			if (i == 0 && runing)
				SelectObject(hdc, brushPass);
			else
				SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			Rectangle(hdc, j * cxSquare, cyClient - cySquare * (i + 1),
				cxSquare * (j + 1) + 1, cyClient - cySquare * i + 1);
			if (!runing && i == 0)
			{
				TextOut(hdc, j * cxSquare + cxSquare / 2 - cxChar * 1.5, cyClient - cySquare / 2,
					szBuff, wsprintf(szBuff, TEXT("开始")));
			}
		}

		TextOut(hdc, cxChar, cyChar, szBuff,
			wsprintf(szBuff, TEXT("Player:%s"), PlayName));
		t = wsprintf(szBuff, TEXT("Score: %ld"), score);
		TextOut(hdc, cxClient - (t + 2) * cxChar, cyChar, szBuff, t);

		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}
