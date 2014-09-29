#include <stdio.h>
#include <Windows.h>

int main()
{
	HWND hwnd = FindWindow(NULL, TEXT("É¨À×"));
	int x = 100, y = 100;
	scanf("%*d");
	for (int i = 0; i < 10; i++)
	{
		if (hwnd)
		{
			printf("finded\n");
			POINT pnt;
			x += 10;
			y += 10;
			pnt.x = x;
			pnt.y = y;
			ClientToScreen(hwnd, &pnt);
			SetCursorPos(pnt.x, pnt.y);
			SendMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(x, y));
			Sleep(10);
			SendMessage(hwnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(x, y));
		}
		else
			printf("failed");
	}
	while (1);
	return 0;
}