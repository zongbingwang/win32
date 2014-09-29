#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <winsock.h>
#include "resource.h"

#pragma comment(lib, "wsock32.lib")

#define WM_GET_SOCKET (WM_USER + 1)

#define ID_TIMER 1

LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MainDlg(HWND, UINT, WPARAM, LPARAM);

void EditPrint(HWND edit, TCHAR* szStr, ...);

HWND hwndModeless;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR nCmdLine, int nCmdShow)
{
	const TCHAR Class_Name[] = TEXT("XYCLASS");
	HWND  hwnd;
	MSG msg;
	RECT rect;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = wndProc;
	wc.lpszClassName = Class_Name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);
	
	hwnd = CreateWindow(Class_Name, TEXT("app"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	hwndModeless = CreateDialog(hInstance, TEXT("MAINDLG"), hwnd, MainDlg);

	GetWindowRect(hwndModeless, &rect);
	AdjustWindowRect(&rect, WS_CAPTION | WS_BORDER, FALSE);

	SetWindowPos(hwnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE);
	
	ShowWindow(hwndModeless, SW_SHOW);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (0 == hwndModeless || !IsDialogMessage(hwndModeless, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_SETFOCUS:
		SetFocus(hwndModeless);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

BOOL CALLBACK MainDlg(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static char szIPAddr[32] = "64.250.229.100";
	static HWND hwndButton, hwndEdit;
	static SOCKET sock;
	static struct sockaddr_in sa;
	static TCHAR szOKLabel[32];
	int iError, iSize;
	unsigned long ulTime;
	WORD wEvent, wError;
	WSADATA WSAData;

	switch (msg)
	{
	case WM_INITDIALOG:
		hwndButton = GetDlgItem(hwnd, IDOK);
		hwndEdit = GetDlgItem(hwnd, IDC_EDIT);
		return true;
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case IDOK:
			WSAStartup(MAKEWORD(2, 0), &WSAData);
			sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			//EditPrint(hwndEdit, TEXT("\nsock:%i."), sock);
			WSAAsyncSelect(sock, hwnd, WM_GET_SOCKET, FD_CONNECT | FD_READ);
			sa.sin_family = AF_INET;
			sa.sin_port = htons(37);
			sa.sin_addr.S_un.S_addr = inet_addr(szIPAddr);
			connect(sock, (SOCKADDR*)&sa, sizeof(sa));
			if (WSAEWOULDBLOCK != (iError = WSAGetLastError()))
			{
				EditPrint(hwndEdit, TEXT("\nConnect error #%i."),
					iError);
				closesocket(sock);
				WSACleanup();
				return TRUE;
			}
			EditPrint(hwndEdit, TEXT("\r\n正在链接：%hs"), szIPAddr);

			SetTimer(hwnd, ID_TIMER, 1000, NULL);
			
			return true;
		case IDCANCEL:
			DestroyWindow(GetParent(hwnd));
			return true;
		}
		return false;
	case WM_TIMER:
		EditPrint(hwndEdit, TEXT("."));
		return true;
	case WM_GET_SOCKET:
		wEvent = LOWORD(lparam);
		wError = HIWORD(lparam);
		switch (wEvent)
		{
		case FD_CONNECT:
			if (wError)
			{
				EditPrint(hwndEdit, TEXT("\r\n连接错误！"));
				return true;
			}
			EditPrint(hwndEdit, TEXT("\r\n连接到：%hs"), szIPAddr);
			recv(sock, (char *)&ulTime, 4, MSG_PEEK);
			EditPrint(hwndEdit, TEXT("\r\n开始接收"));
			return true;
		case FD_READ:
			KillTimer(hwnd, ID_TIMER);
			if (wError)
			{
				EditPrint(hwndEdit, TEXT("FD_READ error #%i."),
					wError);
				return TRUE;
			}
			iSize = recv(sock, (char*)&ulTime, 4, 0);
			EditPrint(hwndEdit, TEXT("\r\n获得：%u"), ulTime);
			return true;
		}
		return false;
	}
	return false;
}

void EditPrint(HWND edit, TCHAR * szStr, ...)
{
	TCHAR szBuff[1024];
	va_list argList;

	va_start(argList, szStr);
	wvsprintf(szBuff, szStr, argList);
	va_end(argList);

	SendMessage(edit, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
	SendMessage(edit, EM_REPLACESEL, FALSE, (LPARAM)szBuff);
	SendMessage(edit, EM_SCROLLCARET, 0, 0);
}