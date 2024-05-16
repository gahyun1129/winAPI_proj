#include "stdafx.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Inversus";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
GameFramework Framework;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;

	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1100, 900, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	Framework.prevFrameTime = Framework.curFrameTime = clock();

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	Framework.Clear();
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC mainDC, memDC, easyDC;
	HBITMAP hBitmap;
	RECT rt;

	switch (uMsg) {
	case WM_CREATE:
		Framework.Create(hWnd);
		SetTimer(hWnd, MAIN_TIMER, MAIN_TIMER_FRAME, NULL);
		SetTimer(hWnd, MENU_TIMER, MENU_TIMER_FRAME, NULL);
		break;
	case WM_PAINT:
	{
		GetClientRect(hWnd, &rt);
		mainDC = BeginPaint(hWnd, &ps);

		if (Framework.SceneIndex == LOBBY) {
			memDC = CreateCompatibleDC(mainDC);
			hBitmap = CreateCompatibleBitmap(mainDC, rt.right, rt.bottom);

			SelectObject(memDC, (HBITMAP)hBitmap);

			SetBkColor(memDC, RGB(0, 0, 0));
			Rectangle(memDC, 0, 0, rt.right, rt.bottom);

			Framework.OnDraw(memDC);

			BitBlt(mainDC, 0, 0, rt.right, rt.bottom, memDC, 0, 0, SRCCOPY);
			DeleteDC(memDC);
			DeleteObject(hBitmap);
		}
		else if (Framework.SceneIndex == EASY) {
			easyDC = CreateCompatibleDC(mainDC);
			hBitmap = CreateCompatibleBitmap(mainDC, rt.right, rt.bottom);

			SelectObject(easyDC, (HBITMAP)hBitmap);

			SetBkColor(easyDC, RGB(0, 0, 0));
			Rectangle(easyDC, 0, 0, rt.right, rt.bottom);

			Framework.OnDraw(easyDC);

			BitBlt(mainDC, 0, 0, rt.right, rt.bottom, easyDC, 0, 0, SRCCOPY);
			DeleteDC(easyDC);
			DeleteObject(hBitmap);
		}

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
			if (Framework.SceneIndex == EASY) {
				Framework.curFrameTime = clock();
				Framework.OnUpdate(Framework.GetTick());
				Framework.prevFrameTime = Framework.curFrameTime;
				InvalidateRect(hWnd, NULL, FALSE);
			}
			else
				break;
			break;
		case 2:
			if (Framework.SceneIndex == LOBBY) {
				Framework.curFrameTime = clock();
				Framework.OnUpdate(Framework.GetTick());
				Framework.prevFrameTime = Framework.curFrameTime;
				InvalidateRect(hWnd, NULL, FALSE);
			}
			else
				break;
			break;
		}
		break;
	}
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		Framework.KeyBoard(uMsg, wParam, lParam);
	}
	break;
	case WM_DESTROY:
		Framework.Clear();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}