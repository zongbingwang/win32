#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <WinInet.h>
#include <process.h>
#include "resource.h"

#pragma comment(lib, "wininet.lib")

#define WM_USER_CHECKFILES (WM_USER + 1)
#define WM_USER_GETFILES (WM_USER + 2)

#define FTPSERVER TEXT ("ftp.microsoft.com")
#define DIRECTORY TEXT ("microsoft.com/developr/")
#define TEMPLATE TEXT ("??????.txt")

typedef struct
{
	TCHAR * szFilename;
	char * szContents;
}FILEINFO;
typedef struct
{
	int iNum;
	FILEINFO info[1];
}FILELIST;
typedef struct
{
	BOOL bContinue;
	HWND hwnd;
}PARAMS;

LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

void FtpThread(PVOID);
void ButtonSwitch(HWND, HWND, TCHAR*);
FILELIST * GetFileList(void);
int Compare(const void* pinfo1, const void* pinfo2);

HINSTANCE hInst;
TCHAR szAppName[] = TEXT("FTPDemo");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR nCmdLine, int nCmdShow)
{
	HWND  hwnd;
	MSG msg;
	RECT rect;
	WNDCLASS wc;
	hInst = hInstance;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = wndProc;
	wc.lpszClassName = szAppName;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hwnd = CreateWindow(szAppName, TEXT("app"), WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static FILELIST *plist;
	static int cxClient, cyClient, cxChar, cyChar;
	HDC hdc;
	int i;
	PAINTSTRUCT ps;
	SCROLLINFO si;
	SYSTEMTIME st;
	TCHAR szFilename[MAX_PATH];

	switch (msg)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lparam);
		cyClient = HIWORD(lparam);
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nPage = cyClient / cyChar;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
		return 0;
	case WM_VSCROLL:
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS | SIF_RANGE | SIF_PAGE;
		GetScrollInfo(hwnd, SB_VERT, &si);
		switch (LOWORD(wparam))
		{
		case SB_LINEDOWN:
			si.nPos += 1;
			break;
		case SB_LINEUP:
			si.nPos -= 1;
			break;
		case SB_PAGEDOWN:
			si.nPos += si.nPage;
			break;
		case SB_PAGEUP:
			si.nPos -= si.nPage;
			break;
		case SB_THUMBPOSITION:
			si.nPos = HIWORD(wparam);
			break;
		}
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	case WM_USER_CHECKFILES:
		GetSystemTime(&st);
		wsprintf(szFilename, TEXT("readme.txt"));
		if (GetFileAttributes(szFilename) != (DWORD)-1)
		{
			SendMessage(hwnd, WM_USER_GETFILES, 0, 0);
			return 0;
		}
		if (GetDriveType(NULL) == DRIVE_CDROM)
		{
			MessageBox(hwnd, TEXT("cannot run from CD-ROM"), szAppName, MB_OK | MB_ICONEXCLAMATION);
			return 0;
		}
		if (IDYES == MessageBox(hwnd, TEXT("update from internet?"),
			szAppName, MB_YESNO | MB_ICONQUESTION))
			DialogBox(hInst, szAppName, hwnd, DlgProc);
		SendMessage(hwnd, WM_USER_GETFILES, 0, 0);
		return 0;
	case WM_USER_GETFILES:
		SetCursor(LoadCursor(NULL, IDC_WAIT));
		ShowCursor(TRUE);
		plist = GetFileList();
		ShowCursor(FALSE);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		SendMessage(hwnd, WM_SIZE, 0, MAKELONG(cxClient, cyClient));
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SetTextAlign(hdc, TA_UPDATECP);
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		GetScrollInfo(hwnd, SB_VERT, &si);
		if (plist)
		{
			for (i = 0; i < plist->iNum; i++)
			{
				MoveToEx(hdc, cxChar, (i - si.nPos) * cyChar, NULL);
				TextOut(hdc, 0, 0, plist->info[i].szFilename,
					lstrlen(plist->info[i].szFilename));
				TextOut(hdc, 0, 0, TEXT(": "), 2);
				TextOutA(hdc, 0, 0, plist->info[i].szContents,
					strlen(plist->info[i].szContents));
			}
		}
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PARAMS params;

	switch (message)
	{
	case WM_INITDIALOG:
		params.bContinue = TRUE;
		params.hwnd = hwnd;

		_beginthread(FtpThread, 0, &params);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:           // button for user to abort download
			params.bContinue = FALSE;
			return TRUE;

		case IDOK:               // button to make dialog box go away
			EndDialog(hwnd, 0);
			return TRUE;
		}
	}
	return FALSE;
}

/*----------------------------------------------------------------------
FtpThread: Reads files from FTP server and copies them to local disk
----------------------------------------------------------------------*/

void FtpThread(PVOID parg)
{
	BOOL            bSuccess;
	HINTERNET       hIntSession, hFtpSession, hFind;
	HWND            hwndStatus, hwndButton;
	PARAMS        * pparams;
	TCHAR           szBuffer[64];
	WIN32_FIND_DATA finddata;

	pparams = (PARAMS*)parg;
	hwndStatus = GetDlgItem(pparams->hwnd, IDC_STATUS);
	hwndButton = GetDlgItem(pparams->hwnd, IDCANCEL);

	// Open an internet session

	hIntSession = InternetOpen(szAppName, INTERNET_OPEN_TYPE_PRECONFIG,
		NULL, NULL, INTERNET_FLAG_ASYNC);

	if (hIntSession == NULL)
	{
		wsprintf(szBuffer, TEXT("InternetOpen error %i"), GetLastError());
		ButtonSwitch(hwndStatus, hwndButton, szBuffer);
		_endthread();
	}

	SetWindowText(hwndStatus, TEXT("Internet session opened..."));

	// Check if user has pressed Cancel

	if (!pparams->bContinue)
	{
		InternetCloseHandle(hIntSession);
		ButtonSwitch(hwndStatus, hwndButton, NULL);
		_endthread();
	}

	// Open an FTP session.

	hFtpSession = InternetConnect(hIntSession, FTPSERVER,
		INTERNET_DEFAULT_FTP_PORT,
		NULL, NULL, INTERNET_SERVICE_FTP, 0, 0);
	if (hFtpSession == NULL)
	{
		InternetCloseHandle(hIntSession);
		wsprintf(szBuffer, TEXT("InternetConnect error %i"),
			GetLastError());
		ButtonSwitch(hwndStatus, hwndButton, szBuffer);
		_endthread();
	}

	SetWindowText(hwndStatus, TEXT("FTP Session opened..."));

	// Check if user has pressed Cancel

	if (!pparams->bContinue)
	{
		InternetCloseHandle(hFtpSession);
		InternetCloseHandle(hIntSession);
		ButtonSwitch(hwndStatus, hwndButton, NULL);
		_endthread();
	}

	// Set the directory

	bSuccess = FtpSetCurrentDirectory(hFtpSession, DIRECTORY);

	if (!bSuccess)
	{
		InternetCloseHandle(hFtpSession);
		InternetCloseHandle(hIntSession);
		wsprintf(szBuffer, TEXT("Cannot set directory to %s"),
			DIRECTORY);
		ButtonSwitch(hwndStatus, hwndButton, szBuffer);
		_endthread();
	}

	SetWindowText(hwndStatus, TEXT("Directory found..."));

	// Check if user has pressed Cancel

	if (!pparams->bContinue)
	{
		InternetCloseHandle(hFtpSession);
		InternetCloseHandle(hIntSession);
		ButtonSwitch(hwndStatus, hwndButton, NULL);
		_endthread();
	}

	// Get the first file fitting the template

	hFind = FtpFindFirstFile(hFtpSession, TEMPLATE,
		&finddata, 0, 0);

	if (hFind == NULL)
	{
		InternetCloseHandle(hFtpSession);
		InternetCloseHandle(hIntSession);
		ButtonSwitch(hwndStatus, hwndButton, TEXT("Cannot find files"));
		_endthread();
	}

	do
	{
		// Check if user has pressed Cancel

		if (!pparams->bContinue)
		{
			InternetCloseHandle(hFind);
			InternetCloseHandle(hFtpSession);
			InternetCloseHandle(hIntSession);
			ButtonSwitch(hwndStatus, hwndButton, NULL);
			_endthread();
		}
		// Copy file from internet to local hard disk, but fail
		// if the file already exists locally

		wsprintf(szBuffer, TEXT("Reading file %s..."), finddata.cFileName);
		SetWindowText(hwndStatus, szBuffer);

		FtpGetFile(hFtpSession,
			finddata.cFileName, finddata.cFileName, TRUE,
			FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY, 0);
	} while (InternetFindNextFile(hFind, &finddata));

	InternetCloseHandle(hFind);
	InternetCloseHandle(hFtpSession);
	InternetCloseHandle(hIntSession);

	ButtonSwitch(hwndStatus, hwndButton, TEXT("Internet Download Complete"));
}

/*-----------------------------------------------------------------------
ButtonSwitch:  Displays final status message and changes Cancel to OK
-----------------------------------------------------------------------*/

VOID ButtonSwitch(HWND hwndStatus, HWND hwndButton, TCHAR * szText)
{
	if (szText)
		SetWindowText(hwndStatus, szText);
	else
		SetWindowText(hwndStatus, TEXT("Internet Session Cancelled"));

	SetWindowText(hwndButton, TEXT("OK"));
	SetWindowLong(hwndButton, GWL_ID, IDOK);
}

/*-----------------------------------------------------------------------
GetFileList: Reads files from disk and saves their names and contents
-----------------------------------------------------------------------*/

FILELIST * GetFileList(void)
{
	DWORD           dwRead;
	FILELIST      * plist;
	HANDLE          hFile, hFind;
	int             iSize, iNum;
	WIN32_FIND_DATA finddata;

	hFind = FindFirstFile(TEMPLATE, &finddata);

	if (hFind == INVALID_HANDLE_VALUE)
		return NULL;

	plist = NULL;
	iNum = 0;

	do
	{
		// Open the file and get the size

		hFile = CreateFile(finddata.cFileName, GENERIC_READ, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, 0, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
			continue;

		iSize = GetFileSize(hFile, NULL);

		if (iSize == (DWORD)-1)
		{
			CloseHandle(hFile);
			continue;
		}
		// Realloc the FILELIST structure for a new entry 

		plist = (FILELIST*)realloc(plist, sizeof (FILELIST)+iNum * sizeof (FILEINFO));

		// Allocate space and save the filename 

		plist->info[iNum].szFilename =(TCHAR*) malloc(lstrlen(finddata.cFileName) +
			sizeof (TCHAR));
		lstrcpy(plist->info[iNum].szFilename, finddata.cFileName);

		// Allocate space and save the contents

		plist->info[iNum].szContents = (char*)malloc(iSize + 1);
		ReadFile(hFile, plist->info[iNum].szContents, iSize, &dwRead, NULL);
		plist->info[iNum].szContents[iSize] = 0;

		CloseHandle(hFile);
		iNum++;
	} while (FindNextFile(hFind, &finddata));

	FindClose(hFind);

	// Sort the files by filename

	qsort(plist->info, iNum, sizeof (FILEINFO), Compare);

	plist->iNum = iNum;

	return plist;
}

/*----------------------------
Compare function for qsort
----------------------------*/

int Compare(const void* pinfo1, const void* pinfo2)
{
	return lstrcmp(((FILEINFO *)pinfo2)->szFilename, ((FILEINFO *)pinfo1)->szFilename);
}
