
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
		return 0;
	}

	hwnd = CreateWindow(szName, TEXT("123"), WS_OVERLAPPEDWINDOW,
		100, 100, 400, 600,
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
void FillList(HWND hwndList)
{
	TCHAR *pVarBlock;
	pVarBlock = GetEnvironmentStrings();
	SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)pVarBlock);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static HBITMAP hBitmap;
	static int cxClient, cyClient, cxSource, cySource;
	static double _Scale = 2.0;
	BITMAP bitmap;
	HDC hdc, hdcMem;
	static HINSTANCE hInstance;
	int x, y;
	PAINTSTRUCT ps;
	TCHAR szBuffer[40];

	switch (message)
	{
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lparam)->hInstance;
		hBitmap = LoadBitmap(hInstance, TEXT("Bpm"));
		GetObject(hBitmap, sizeof (BITMAP), &bitmap);
		cxSource = bitmap.bmWidth;
		cySource = bitmap.bmHeight;
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lparam);
		cyClient = HIWORD(lparam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, hBitmap);
		for (y = 0; y < cyClient; y += cySource * _Scale)
		{
			for (x = 0; x < cxClient; x += (cxSource *_Scale))
				StretchBlt(hdc, x, y, x + cxSource *_Scale, y + cySource *_Scale,
				hdcMem, 0, 0, cxSource, cySource, SRCCOPY);
		}

		DeleteDC(hdcMem);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_CLOSE:
		if (MessageBox(hwnd, TEXT("quit?"), TEXT("quit?"), MB_YESNO | MB_ICONASTERISK) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}

