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
	POINT pt;
	static POINT apt[4];
	static int cxClient, cyClient;
	char szBuffer[30];

	switch(message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:

		hdc = BeginPaint (hwnd, &ps) ;
		
		/*青画笔，无画刷*/
		SelectObject (hdc, CreatePen(PS_SOLID, 0, RGB(0,255,255)));
		SelectObject (hdc, GetStockObject (NULL_BRUSH));
		
		SetTextColor (hdc, RGB(0,0,255));

		MoveToEx (hdc, 0, 0, NULL);
		LineTo (hdc, 100, 100);

		Ellipse(hdc, 0, 0, 200, 200);

		/*改变映射模式*/
		SetMapMode (hdc, MM_LOENGLISH);
		SetViewportOrgEx (hdc, 0, cyClient, NULL);
		GetWindowOrgEx (hdc, &pt);
		//TextOut (hdc, 0, 30, szBuffer, wsprintf (szBuffer, "坐标原点 %d,%d", pt.x, pt.y));

		MoveToEx (hdc, 0, 0, NULL);
		LineTo (hdc, 100, 100);

		Ellipse(hdc, 0, 0, 200, 200);

		EndPaint (hwnd, &ps) ;
		return 0 ;

	case WM_DESTROY:
		PostQuitMessage(message);
		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
