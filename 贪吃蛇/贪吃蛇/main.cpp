#include <Windows.h>
#include "resource.h"
HINSTANCE hBmpInstance;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define ID_TIMER 1


#define Map_Orgx 10
#define Map_Orgy 10
#define Map_X 20
#define Map_Y 20
#define Snake_Node_Width 20
#define Snake_Node_Height 20
typedef struct _node
{
	int x, y;
	_node* next;
}Node;
Node *head;

int direct = 0;
int game_speed = 1000;
void init(HDC hdc)
{
	head = new Node;
	head->x = Map_X / 2;
	head->y = Map_Y / 2;
	head->next = NULL;
}
void DrawMap(HDC hdc)
{
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, Map_Orgx - 1, Map_Orgy - 1, Map_Orgx + Map_X * Snake_Node_Width + 1, Map_Orgy + Map_Y * Snake_Node_Height + 1);
}
void DrawSnake(HDC hdc)
{
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	Node *p = head;
	while (p)
	{
		Rectangle(hdc, Map_Orgx + p->x * Snake_Node_Width, Map_Orgy + p->y * Snake_Node_Height, 
			Map_Orgx + p->x * Snake_Node_Width + Snake_Node_Width, 
			Map_Orgy + p->y * Snake_Node_Height + Snake_Node_Height);
		p = p->next;
	}
}
void snake_move()
{
	Node *p = head;
	int x = head->x;
	int y = head->y;
	switch (direct)
	{
	case 0:
		head->x++;
		head->x %= Map_X;
		break;
	case 1:
		head->y++;
		head->y %= Map_Y;
		break;
	case 2:
		head->x--;
		if (head->x < 0)
			head->x = Map_X - 1;
		break;
	case 3:
		head->y--;
		if (head->y < 0)
			head->y = Map_Y - 1;
	}
	
	
	while (p->next)
	{
		x = p->next->x;
		y = p->next->y;
		p->next->x = p->x;
		p->next->y = p->y;
		p = p->next;
	}
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	


	static TCHAR szAppName[] = TEXT("tanchishe");
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;

	hBmpInstance = hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	
	RegisterClass(&wc);

	hwnd = CreateWindow(szAppName, TEXT("Ã∞≥‘…ﬂ"), WS_OVERLAPPEDWINDOW, 200, 60, 800, 600,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, CmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	static HBITMAP game_map;
	static BITMAP Bmp;
	static HDC hdc, hMemdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_CREATE:
		init(GetDC(hwnd));
		SetTimer(hwnd, ID_TIMER, game_speed, NULL);
		return 0;
	case WM_TIMER:
		snake_move();
		SendMessage(hwnd, WM_PAINT, wParam, lParam);
		DrawMap(GetDC(hwnd));
		DrawSnake(GetDC(hwnd));
		
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			direct = 2;
			break;
		case VK_UP:
			direct = 3;
			break;
		case VK_RIGHT:
			direct = 0;
			break;
		case VK_DOWN:
			direct = 1;

		}
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		hMemdc = CreateCompatibleDC(hdc);
		game_map = LoadBitmap(hBmpInstance, MAKEINTRESOURCE(IDB_MAP));
		GetObject(game_map, sizeof(BITMAP), &Bmp);
		SelectObject(hMemdc, game_map);
		SetStretchBltMode(GetDC(hwnd), COLORONCOLOR);
		SetBrushOrgEx(GetDC(hwnd), 0, 0, NULL);
		StretchBlt(GetDC(hwnd), 0, 0, cxClient, cyClient, hMemdc, 0, 0, Bmp.bmWidth, Bmp.bmHeight, SRCCOPY);
		
		DrawMap(hdc);
		DrawSnake(hdc);

		EndPaint(hwnd, &ps);
		return 0;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(msg);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}