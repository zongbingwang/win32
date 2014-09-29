#include<windows.h>
#include<stdio.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	static TCHAR szAppName[] = TEXT("wndclass by lxy");
	HWND		hwnd;
	MSG			msg;
	WNDCLASS	wndclass;
	//窗口类初始化
	wndclass.style			= CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.hCursor		= LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hInstance		= hInstance;
	wndclass.lpszClassName	= szAppName;
	wndclass.lpszMenuName	= NULL;
	//注册窗口类
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL,TEXT("分配窗口类失败!"),szAppName,MB_ICONERROR);
		return 0;
	}
	//创建窗口
	hwnd = CreateWindow(szAppName,
						TEXT("信息显示"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT,
						CW_USEDEFAULT, CW_USEDEFAULT,
						NULL, NULL, hInstance, NULL);
	
	ShowWindow(hwnd,nCmdShow);	
	UpdateWindow(hwnd);		

	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);	
		DispatchMessage(&msg);	
	}

	return msg.wParam;
}

void DrawBezier (HDC hdc, POINT apt[])
{
	PolyBezier (hdc, apt, 4);
	MoveToEx (hdc, apt[0].x, apt[0].y, NULL);
	LineTo	 (hdc, apt[1].x, apt[1].y);

	MoveToEx  (hdc, apt[2].x, apt[2].y, NULL);
	LineTo   (hdc, apt[3].x, apt[3].y);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static POINT apt[4];
	int cxClient, cyClient;
	int sin;

	switch(message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		apt[0].x = cxClient / 4;
		apt[0].y = cyClient / 2;

		apt[1].x = cxClient / 2;
		apt[1].y = cyClient / 4;

		apt[2].x = cxClient / 2;
		apt[2].y = 3 * cyClient / 4;

		apt[3].x = 3 * cxClient / 4;
		apt[3].y = cyClient / 2;

		return 0;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
		{
			hdc = GetDC (hwnd);

			SelectObject (hdc, GetStockObject (WHITE_PEN));
			DrawBezier (hdc, apt);
			if (wParam & MK_LBUTTON)
			{
				apt[1].x = LOWORD (lParam);
				apt[1].y = HIWORD (lParam);
			}

			if (wParam & MK_RBUTTON)
			{
				apt[2].x = LOWORD (lParam);
				apt[2].y = HIWORD (lParam);
			}

			SelectObject (hdc, GetStockObject(BLACK_PEN));
			DrawBezier (hdc, apt);
			ReleaseDC (hwnd, hdc);
		}
		return 0;

	case WM_PAINT:
		InvalidateRect (hwnd, NULL, TRUE) ;

		hdc = BeginPaint (hwnd, &ps) ;

		DrawBezier (hdc, apt) ;

		EndPaint (hwnd, &ps) ;
		return 0 ;


	case WM_DESTROY:
		PostQuitMessage(message);
		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
