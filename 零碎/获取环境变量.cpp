
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
		100, 50, 800, 700,
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
void FillList(HWND hwndList, HWND hwndEdit)
{
	int iLength;
	TCHAR *p ,*pVarBlock, *pVarBeg, *pVarEnd, *pVarName;
	p = pVarBlock = GetEnvironmentStrings();
	
	while (*pVarBlock)
	{
		if (*pVarBlock != '=')
		{
			pVarBeg = pVarBlock;
			while (*pVarBlock++ != '=');
			pVarEnd = pVarBlock - 1;
			iLength = pVarEnd - pVarBeg;

			pVarName = new TCHAR[iLength + 1];
			CopyMemory(pVarName, pVarBeg, iLength * sizeof(TCHAR));
			pVarName[iLength] = '\0';

			SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)pVarName);
			delete[] pVarName;
		}
		while (*pVarBlock++ != '\0');
	}
	FreeEnvironmentStrings(p);
	
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxDisplay, cyDisplay;
	static HWND hwndList, hwndEdit;
	int i, iLength;
	TCHAR * pVarName, *pValue;
	switch (message)
	{
	case WM_CREATE:
		hwndEdit = CreateWindow(TEXT("edit"), NULL,  WS_BORDER | WS_VISIBLE| ES_MULTILINE | WS_CHILD,
			0, 0, 100, 500, hwnd, (HMENU)1, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		
		hwndList = CreateWindow(TEXT("listbox"), NULL, WS_VISIBLE | WS_CHILD | 
			LBS_STANDARD |  LBS_NOTIFY,
			100, 100, 300, 500, hwnd, (HMENU)2, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		FillList(hwndList, hwndEdit);
		SendMessage(hwndList, LB_DIR, 0,(LPARAM) "*.*");
		return 0;
	
	case WM_COMMAND:
		if (LOWORD(wparam) == 2 && HIWORD(wparam) == LBN_SELCHANGE)
		{
			i = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			iLength = SendMessage(hwndList, LB_GETTEXTLEN, i, 0);
			pVarName = new TCHAR[iLength + 1];
			SendMessage(hwndList, LB_GETTEXT, i, (LPARAM)pVarName);

			iLength = GetEnvironmentVariable(pVarName, NULL, 0);
			pValue = new TCHAR[iLength + 1];
			GetEnvironmentVariable(pVarName, pValue, iLength);

			SetWindowText(hwndEdit, pValue);
			delete[] pVarName;
			delete[] pValue;
		}
		return 0;
	case WM_CLOSE:
		if (MessageBox(hwnd, TEXT("quit?"), TEXT("quit?"), MB_YESNO | MB_ICONASTERISK) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}

