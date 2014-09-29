#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>

int main()
{
	int x, y;
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc;
	hdc = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	//hdc = GetWindowDC(NULL);
	SelectObject(hdc, GetStockObject(WHITE_PEN));

	for (int x = 10; x < cx * 1.4; x += 10)
	{
		MoveToEx(hdc, x, 0, NULL);
		LineTo(hdc, 0, x);
		MoveToEx(hdc, 0, cy - x, NULL);
		LineTo(hdc, x, cy);
	}
	
	ReleaseDC(NULL, hdc);
	//InvalidateRect(NULL, NULL, TRUE);
	std::cin.get();
	return 0;
}
