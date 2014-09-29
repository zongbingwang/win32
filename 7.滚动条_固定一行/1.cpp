#include<windows.h>

#define NUMLINES int(sizeof(sysmetrics)/sizeof(sysmetrics[0]))
struct			//显示系统信息的结构
{
	int iIndex;
	TCHAR * szLable;
	TCHAR * szDesc;
}
sysmetrics [] =
{
	SM_CXSCREEN,	TEXT ("SM_CXSCREEN"),	TEXT ("屏幕宽度"),
	SM_CYSCREEN,	TEXT ("SM_CYSCREEN"),	TEXT ("屏幕高度"),
	SM_CXVSCROLL, TEXT ("SM_CXVSCROLL"),           
        
                          TEXT ("Vertical scroll width"),
        
    SM_CYHSCROLL,  TEXT ("SM_CYHSCROLL"),           
        
                          TEXT ("Horizontal scroll height"),
        
    SM_CYCAPTION, TEXT ("SM_CYCAPTION"),           
        
                             TEXT ("Caption bar height"),
        
    SM_CXBORDER, TEXT ("SM_CXBORDER"),            
        
                          TEXT ("Window border width"),
        
    SM_CYBORDER,  TEXT ("SM_CYBORDER"),            
        
                          TEXT ("Window border height"),
        
    SM_CXFIXEDFRAME,TEXT ("SM_CXFIXEDFRAME"),        
        
                          TEXT ("Dialog window frame width"),
        
    SM_CYFIXEDFRAME,TEXT ("SM_CYFIXEDFRAME"),        
        
                          TEXT ("Dialog window frame height"),
        
    SM_CYVTHUMB,  TEXT ("SM_CYVTHUMB"),            
        
                         TEXT ("Vertical scroll thumb height"),
        
    SM_CXHTHUMB,    TEXT ("SM_CXHTHUMB"),            
        
                             TEXT ("Horizontal scroll thumb width"),
        
    SM_CXICON,       TEXT ("SM_CXICON"),             
        
                          TEXT ("Icon width"),
        
    SM_CYICON,       TEXT ("SM_CYICON"),              
        
                        TEXT ("Icon height"),
        
    SM_CXCURSOR,  TEXT ("SM_CXCURSOR"),            
        
                          TEXT ("Cursor width"),
        
    SM_CYCURSOR,    TEXT ("SM_CYCURSOR"),           
        
                          TEXT ("Cursor height"),
        
    SM_CYMENU,       TEXT ("SM_CYMENU"),              
        
                          TEXT ("Menu bar height"),
        
    SM_CXFULLSCREEN,TEXT ("SM_CXFULLSCREEN"),        
        
                          TEXT ("Full screen client area width"),
        
    SM_CYFULLSCREEN,TEXT ("SM_CYFULLSCREEN"),        
        
                          TEXT ("Full screen client area height"),
        
    SM_CYKANJIWINDOW,TEXT ("SM_CYKANJIWINDOW"),       
        
                           TEXT ("Kanji window height"),
        
    SM_MOUSEPRESENT, TEXT ("SM_MOUSEPRESENT"),        
        
                           TEXT ("Mouse present flag"),
        
    SM_CYVSCROLL,TEXT ("SM_CYVSCROLL"),           
        
                           TEXT ("Vertical scroll arrow height"),
        
    SM_CXHSCROLL,TEXT ("SM_CXHSCROLL"),           
        
                          TEXT ("Horizontal scroll arrow width"),
        
    SM_DEBUG,         TEXT ("SM_DEBUG"),               
        
                           TEXT ("Debug version flag"),
        
    SM_SWAPBUTTON,TEXT ("SM_SWAPBUTTON"),          
        
                           TEXT ("Mouse buttons swapped flag"),
        
    SM_CXMIN,         TEXT ("SM_CXMIN"),               
        
                           TEXT ("Minimum window width"),
        
    SM_CYMIN,         TEXT ("SM_CYMIN"),               
        
                           TEXT ("Minimum window height"),
        
    SM_CXSIZE,        TEXT ("SM_CXSIZE"),              
        
                           TEXT ("Min/Max/Close button width"),
        
    SM_CYSIZE,       TEXT ("SM_CYSIZE"),             
        
                           TEXT ("Min/Max/Close button height"),
        
    SM_CXSIZEFRAME,TEXT ("SM_CXSIZEFRAME"),         
        
                           TEXT ("Window sizing frame width"),
        
    SM_CYSIZEFRAME,TEXT ("SM_CYSIZEFRAME"),         
        
                           TEXT ("Window sizing frame height"),
        
    SM_CXMINTRACK,TEXT ("SM_CXMINTRACK"),          
        
                           TEXT ("Minimum window tracking width"),
        
    SM_CYMINTRACK,TEXT ("SM_CYMINTRACK"),          
        
                           TEXT ("Minimum window tracking height"),
        
    SM_CXDOUBLECLK,TEXT ("SM_CXDOUBLECLK"),         
        
                           TEXT ("Double click x tolerance"),
        
    SM_CYDOUBLECLK,TEXT ("SM_CYDOUBLECLK"),         
        
                           TEXT ("Double click y tolerance"),
        
    SM_CXICONSPACING,TEXT ("SM_CXICONSPACING"),       
        
                           TEXT ("Horizontal icon spacing"),
        
    SM_CYICONSPACING,TEXT ("SM_CYICONSPACING"),       
        
                           TEXT ("Vertical icon spacing"),
        
    SM_MENUDROPALIGNMENT,TEXT ("SM_MENUDROPALIGNMENT"),   
        
                                  TEXT ("Left or right menu drop"),
        
    SM_PENWINDOWS,       TEXT ("SM_PENWINDOWS"),          
        
                                  TEXT ("Pen extensions installed"),
        
    SM_DBCSENABLED,       TEXT ("SM_DBCSENABLED"),         
        
                                  TEXT ("Double-Byte Char Set enabled"),
        
    SM_CMOUSEBUTTONS,        TEXT ("SM_CMOUSEBUTTONS"),       
        
                                 TEXT ("Number of mouse buttons"),
        
    SM_SECURE,               TEXT ("SM_SECURE"),              
        
                                  TEXT ("Security present flag"),
        
    SM_CXEDGE,               TEXT ("SM_CXEDGE"),              
        
                                  TEXT ("3-D border width"),
        
    SM_CYEDGE,               TEXT ("SM_CYEDGE"),              
        
                                  TEXT ("3-D border height"),
        
    SM_CXMINSPACING,         TEXT ("SM_CXMINSPACING"),        
        
                                  TEXT ("Minimized window spacing width"),
        
    SM_CYMINSPACING,         TEXT ("SM_CYMINSPACING"),        
        
                                  TEXT ("Minimized window spacing height"),
        
    SM_CXSMICON,         TEXT ("SM_CXSMICON"),            
        
                                  TEXT ("Small icon width"),
        
    SM_CYSMICON,        TEXT ("SM_CYSMICON"),            
        
                                  TEXT ("Small icon height"),
        
    SM_CYSMCAPTION,       TEXT ("SM_CYSMCAPTION"),         
        
                                  TEXT ("Small caption height"),
        
    SM_CXSMSIZE,         TEXT ("SM_CXSMSIZE"),            
        
                                 TEXT ("Small caption button width"),
        
    SM_CYSMSIZE,         TEXT ("SM_CYSMSIZE"),            
        
                                  TEXT ("Small caption button height"),
        
    SM_CXMENUSIZE,       TEXT ("SM_CXMENUSIZE"),          
        
                                  TEXT ("Menu bar button width"),
        
    SM_CYMENUSIZE,       TEXT ("SM_CYMENUSIZE"),          
        
                                TEXT ("Menu bar button height"),
        
    SM_ARRANGE,              TEXT ("SM_ARRANGE"),             
        
                                  TEXT ("How minimized windows arranged"),
        
    SM_CXMINIMIZED,      TEXT ("SM_CXMINIMIZED"),         
        
                                  TEXT ("Minimized window width"),
        
    SM_CYMINIMIZED,       TEXT ("SM_CYMINIMIZED"),         
        
                                  TEXT ("Minimized window height"),
        
    SM_CXMAXTRACK,       TEXT ("SM_CXMAXTRACK"),         
        
                                  TEXT ("Maximum draggable width"),
        
    SM_CYMAXTRACK,       TEXT ("SM_CYMAXTRACK"),          
        
                                 TEXT ("Maximum draggable height"),
        
    SM_CXMAXIMIZED,       TEXT ("SM_CXMAXIMIZED"),         
        
                                  TEXT ("Width of maximized window"),
        
    SM_CYMAXIMIZED,       TEXT ("SM_CYMAXIMIZED"),         
        
                                  TEXT ("Height of maximized window"),
        
    SM_NETWORK,          TEXT ("SM_NETWORK"),             
        
                                  TEXT ("Network present flag"),
        
    SM_CLEANBOOT,         TEXT ("SM_CLEANBOOT"),           
        
                                  TEXT ("How system was booted"),
        
    SM_CXDRAG,               TEXT ("SM_CXDRAG"),              
        
                                  TEXT ("Avoid drag x tolerance"),
        
    SM_CYDRAG,               TEXT ("SM_CYDRAG"),              
        
                                  TEXT ("Avoid drag y tolerance"),
        
    SM_SHOWSOUNDS,        TEXT ("SM_SHOWSOUNDS"),          
        
                                  TEXT ("Present sounds visually"),
        
    SM_CXMENUCHECK,       TEXT ("SM_CXMENUCHECK"),         
        
                                 TEXT ("Menu check-mark width"),
        
    SM_CYMENUCHECK,       TEXT ("SM_CYMENUCHECK"),         
        
                                 TEXT ("Menu check-mark height"),
        
    SM_SLOWMACHINE,       TEXT ("SM_SLOWMACHINE"),         
        
                                  TEXT ("Slow processor flag"),
        
    SM_MIDEASTENABLED,       TEXT ("SM_MIDEASTENABLED"),      
        
                                  TEXT ("Hebrew and Arabic enabled flag"),



};
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
						WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,	//包含垂直滚动条WS_VSCROLL，水平为WS_HSCROLL
						CW_USEDEFAULT, CW_USEDEFAULT,
						722, 411,
						NULL, NULL, hInstance, NULL);
	
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
	SCROLLINFO si;		//滚动条信息
	TCHAR szBuffer[40];
	static int cxChar, cyChar, cxCaps, cxClient, cyClient, iMaxWidth;
	
	int i, x, y, t, iVertPos, iHorzPos, iPaintBeg, iPaintEnd;
	
	switch(message)
	{
	case WM_CREATE:
		//获取系统字体的宽度和高度
		hdc = GetDC (hwnd);		//获取客户区句柄

		GetTextMetrics (hdc, &tm);		//获取文本尺寸
		cxChar = tm.tmAveCharWidth;			//平均字符宽度
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3:2) * cxChar/2;  //大写字母平均宽度，等宽字体等于cxChar，变宽字体为其1.5倍
		cyChar = tm.tmHeight + tm.tmExternalLeading;	//字符高度+建议间距
	
		ReleaseDC (hwnd, hdc);	//释放设备环境句柄

		iMaxWidth =  40 * cxChar + 20 * cxCaps;
		return 0;

	case WM_SIZE:
		cxClient = LOWORD (lParam);
		cyClient = HIWORD (lParam);

		si.cbSize	= sizeof (si);
		si.fMask	= SIF_RANGE | SIF_PAGE | SIF_DISABLENOSCROLL;		//设置的信息
		si.nMin		= 0;
		si.nMax		= NUMLINES;
		si.nPage	= cyClient / cyChar;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE); //滚动条最大值会设为nMain-nPage

		si.cbSize	= sizeof (si);
		si.fMask	= SIF_RANGE | SIF_PAGE;
		si.nMin		= 0;
		si.nMax		= 2 + iMaxWidth / cxChar;
		si.nPage	= cxClient / cxChar;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);

		return 0;
	case WM_VSCROLL:
		
		si.cbSize	= sizeof (si);
		si.fMask	= SIF_ALL;
		GetScrollInfo (hwnd, SB_VERT, &si);
		iVertPos  = si.nPos;

		switch (LOWORD (wParam))
		{
		case SB_LINEUP:
			si.nPos -= 1;
			break;
		case SB_LINEDOWN:
			si.nPos += 1;
			break;
		case SB_PAGEUP:
			si.nPos -= si.nPage;
			break;
		case SB_PAGEDOWN:
			si.nPos += si.nPage;
			break;
		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;
		default :
			break;
		}
		
		si.fMask = SIF_POS;
		SetScrollInfo (hwnd, SB_VERT, &si,TRUE);
		GetScrollInfo (hwnd, SB_VERT, &si);
		
		if (si.nPos != iVertPos)
		{
			ScrollWindow (hwnd, 0,cyClient,NULL,NULL);
			ScrollWindow (hwnd, 0,-cyClient,NULL,NULL);
			UpdateWindow (hwnd);
		}
		return 0;

	case WM_HSCROLL:
        si.cbSize = sizeof (si) ;
        si.fMask  = SIF_ALL ;
        GetScrollInfo (hwnd, SB_HORZ, &si) ;
        iHorzPos = si.nPos ;
        switch (LOWORD (wParam))
        {      
			case SB_LINELEFT:      
					si.nPos -= 1 ;     
					break ;     
			case SB_LINERIGHT:     
					si.nPos += 1 ;    
					break ;     
			case SB_PAGELEFT:     
					si.nPos -= si.nPage ;     
					break ;     
			case SB_PAGERIGHT:   
					si.nPos += si.nPage ;    
					break ;
			case SB_THUMBTRACK:
					si.nPos = si.nTrackPos ;
					break ;    
			default :
					break ;   
		}
        si.fMask = SIF_POS ;
        SetScrollInfo (hwnd, SB_HORZ, &si, TRUE) ;
        GetScrollInfo (hwnd, SB_HORZ, &si) ;

		if (si.nPos != iHorzPos)     
		{
			ScrollWindow (hwnd, 0,cxClient,NULL,NULL);
			ScrollWindow (hwnd, 0,-cxClient,NULL,NULL);
		}       
		return 0 ;

	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		GetClientRect(hwnd,&rect);

		si.cbSize = sizeof (si);
		si.fMask  = SIF_POS;
		GetScrollInfo (hwnd, SB_VERT, &si);
		iVertPos = si.nPos;
		GetScrollInfo (hwnd, SB_HORZ, &si);
		iHorzPos = si.nPos;

		iPaintBeg = iVertPos;
		iPaintEnd = iVertPos + cyClient / cyChar;


		TextOut(hdc,0,0, szBuffer,
				wsprintf(szBuffer,TEXT("当前窗口 %d * %d       %d"), cxClient, cyClient,iVertPos));

		//wsprintf(szBuffer,TEXT("pos=%d"), iVertPos);
		//MessageBox(hwnd, szBuffer,"1",0);

		for (i = 1; i <= cyClient / cyChar -1; i++)
		{
			x = cxChar * (1 - iHorzPos);
			y = cyChar * i;
			TextOut(hdc,x, y, sysmetrics[iPaintBeg].szLable, lstrlen(sysmetrics[iPaintBeg].szLable));
			TextOut(hdc,x + 20 * cxCaps, y, 
					sysmetrics[iPaintBeg].szDesc, lstrlen(sysmetrics[iPaintBeg].szDesc));
			SetTextAlign (hdc, TA_RIGHT | TA_TOP);
			TextOut(hdc,x + 20 * cxCaps + 40 * cxChar, y, szBuffer,
					wsprintf(szBuffer,TEXT("%d"), GetSystemMetrics(sysmetrics[iPaintBeg].iIndex)));
			iPaintBeg++;
			SetTextAlign (hdc, TA_LEFT | TA_TOP);
		}
		

		
       
		EndPaint(hwnd,&ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(message);
		return 0;

	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
