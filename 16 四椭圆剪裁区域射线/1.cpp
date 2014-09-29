
#include<windows.h>
#include<math.h>

#define TWO_PI (2 * 3.14159)

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

	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);	
		DispatchMessage(&msg);	
	}

	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	HRGN hRgnTemp[6];
	HCURSOR  hCursor;
	PAINTSTRUCT ps;
	HDC hdc;
	double fAngle, fRadius;
	int i;
	static int cxClient, cyClient;
	static HRGN hRgnClip;

	switch(message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		hCursor = SetCursor (LoadCursor (NULL, IDC_WAIT));
		ShowCursor (FALSE);
		
		if (hRgnClip)
			DeleteObject (hRgnClip);
		hRgnTemp[0] = CreateEllipticRgn (0, cyClient / 3, cxClient / 2, 2 * cyClient / 3);
		hRgnTemp[1] = CreateEllipticRgn (cxClient / 2, cyClient / 3, cxClient, 2* cyClient / 3);
		hRgnTemp[2] = CreateEllipticRgn (cxClient / 3, 0, 2 * cxClient / 3, cyClient / 2);
		hRgnTemp[3] = CreateEllipticRgn (cxClient / 3, cyClient / 2, 2 * cxClient / 3, cyClient);

		hRgnTemp[4] = CreateRectRgn (0, 0, 1, 1);
		hRgnTemp[5] = CreateRectRgn (0, 0, 1, 1);
		hRgnClip = CreateRectRgn (0, 0, 1, 1);

		CombineRgn (hRgnTemp[4], hRgnTemp[0], hRgnTemp[1], RGN_OR);
		CombineRgn (hRgnTemp[5], hRgnTemp[2], hRgnTemp[3], RGN_OR);
		CombineRgn (hRgnClip, hRgnTemp[4], hRgnTemp[5], RGN_XOR);

		for (i = 0; i < 6; i++)
			DeleteObject (hRgnTemp[i]);
		SetCursor (hCursor);
		ShowCursor (TRUE);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;
		

		SetViewportOrgEx (hdc, cxClient / 2, cyClient / 2, NULL);
		SelectClipRgn (hdc, hRgnClip);

		fRadius = hypot (cxClient / 2 , cyClient / 2);

		for (fAngle = 0.0; fAngle < TWO_PI ; fAngle += TWO_PI / 200)
		{
			MoveToEx (hdc, 0, 0, NULL);
			LineTo (hdc, (int) (fRadius * cos (fAngle) + 0.5),
						(int) (-fRadius * sin (fAngle) + 0.5));
		}

		EndPaint (hwnd, &ps);

		return 0;

	case WM_DESTROY:
		DeleteObject (hRgnClip);
		PostQuitMessage(message);

		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
