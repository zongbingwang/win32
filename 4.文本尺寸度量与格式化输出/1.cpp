#include<windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	static TCHAR szAppName[] = TEXT("窗口程序");
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
						"The Windows!",
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL);
	
	ShowWindow(hwnd,nCmdShow);		//显示窗口
	UpdateWindow(hwnd);		

	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);		//转换消息
		DispatchMessage(&msg);		//投递消息
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	TEXTMETRIC tm;		//文本信息结构
	static int cxChar, cyChar;		//存放字符尺寸信息
	int iLength;		//存放文本长度
	TCHAR szBuffer [40];	
	switch(message)
	{
	case WM_CREATE:
		//获取系统字体的宽度和高度
		hdc = GetDC (hwnd);		//获取客户区句柄
		GetTextMetrics (hdc, &tm);		//获取文本尺寸
		cxChar = tm.tmAveCharWidth;			//平均字符宽度
		cyChar = tm.tmHeight + tm.tmExternalLeading;	//字符高度+建议间距
		ReleaseDC (hwnd, hdc);	//释放设备环境句柄
		//播放波形声音文件，project->setting->linking模块中加入winmm.lib
		PlaySound (TEXT ("1.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		GetClientRect(hwnd,&rect);
		DrawText(hdc,TEXT("一些示例"),-1, &rect, DT_CENTER);
		/* TextOut()第一种例子 */
		TextOut(hdc,cxChar ,cyChar,TEXT("第一个示例"),sizeof(TEXT("第一个示例"))-1);
		/* TextOut()第二种例子 */
		iLength = wsprintf (szBuffer, TEXT ("第二个示例%d+%d=%d"),1,2, 1+2);
		TextOut(hdc, cxChar, cyChar * 2, szBuffer, iLength);
		/* TextOut()第三种例子 */
		TextOut(hdc, cxChar, cyChar * 3, szBuffer,
			wsprintf (szBuffer, TEXT ("第三个示例%d+%d=%d"), 2, 4, 2+4));

		EndPaint(hwnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(message);
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
