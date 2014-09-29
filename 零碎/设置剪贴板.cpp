#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;
void SetClipText(const string & str)
{
	//或取控制台句柄
	TCHAR Tmp_Title[1024];
	GetConsoleTitle(Tmp_Title, 1024);
	SetConsoleTitle(TEXT("_ADKLJ_ALKD_mx"));
	Sleep(10);
	HWND Hwnd_Of_Console = FindWindow(NULL, TEXT("_ADKLJ_ALKD_mx"));
	SetConsoleTitle(Tmp_Title);

	//分配内存块
	HGLOBAL hGlo_Mem = GlobalAlloc(GHND | GMEM_SHARE, str.size() + 1);
	hGlo_Mem = GlobalLock(hGlo_Mem);
	strcpy((char*)hGlo_Mem, str.c_str());
	GlobalUnlock(hGlo_Mem);

	//设置剪切板
	OpenClipboard(Hwnd_Of_Console);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hGlo_Mem);
	CloseClipboard();
}
int main()
{
	SetClipText("ablkadjlasfja");
	return 0;
}