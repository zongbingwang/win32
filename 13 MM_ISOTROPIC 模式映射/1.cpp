#include<windows.h>

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


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SIZE lp;
	TEXTMETRIC tm;
	static POINT apt[4];
	static int cxClient, cyClient, cxChar, cyChar;
	char szBuffer[30];

	switch(message)
	{
	case WM_CREATE:
		hdc = GetDC (hwnd);
		GetTextMetrics (hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		ReleaseDC (hwnd, hdc);

		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		return 0;

	case WM_PAINT:

		hdc = BeginPaint (hwnd, &ps) ;
		
		/*青画笔，无画刷*/
		SelectObject (hdc, GetStockObject (NULL_BRUSH));
		
		SetTextColor (hdc, RGB(0,0,255));

		/* MM_ISOTROPIC 模式映射   windows会调整比例*/
		/*改变映射模式*/
		
		SetMapMode (hdc, MM_ISOTROPIC);     
		SetWindowExtEx (hdc, cxClient, cyClient, NULL);    //每英寸逻辑单位的个数
		SetViewportExtEx (hdc, cxClient, -cyClient, NULL);  //每英寸物理单位(像素)的个数
		SetViewportOrgEx (hdc, cxClient/2, cyClient/2, NULL);  //设置原点
		
		SelectObject (hdc, GetStockObject (BLACK_PEN));
		MoveToEx (hdc, 0, -cyClient / 2, NULL);
		LineTo (hdc, 0, cyClient / 2);

		MoveToEx (hdc, -cxClient / 2, 0, NULL);
		LineTo (hdc, cxClient / 2, 0);

		SelectObject (hdc, CreatePen(PS_SOLID, 0, RGB(0,255,255)));
		MoveToEx (hdc, 0, 0, NULL);
		LineTo (hdc, cyClient / 2 * 0.4, cyClient / 2 * 0.4);

		Ellipse (hdc, 0, cyClient / 2 * 0.8, cyClient / 2 * 0.8, 0);
		
		GetWindowExtEx (hdc, &lp);
		TextOut (hdc, 10, -1, szBuffer, wsprintf (szBuffer, ": %d*%d", lp.cx, lp.cy));
		
		GetViewportExtEx (hdc, &lp);
		TextOut (hdc, 10, -20, szBuffer, wsprintf (szBuffer, ": %d*%d", lp.cx, lp.cy));
		
		EndPaint (hwnd, &ps) ;
		return 0 ;

	case WM_DESTROY:
		PostQuitMessage(message);
		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
