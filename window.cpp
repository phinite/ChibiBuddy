#include "window.h"


LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		PostMessage(hWnd, WM_NCLBUTTONDOWN, 2, 0);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

Window::Window()
{
	ZeroMemory(&this->wc, sizeof(WNDCLASSEXW));
}


int Window::Init(HINSTANCE hInst, const wchar_t* szWindowClass, int windWidth, int windHeight)
{
	this->wc.cbSize = sizeof(WNDCLASSEXW);
	this->wc.style = CS_HREDRAW | CS_VREDRAW;
	this->wc.lpfnWndProc = Window::WndProc;
	this->wc.cbClsExtra = 0;
	this->wc.cbWndExtra = 0;
	this->wc.hInstance = hInst;
	this->wc.hIcon = NULL;
	this->wc.hCursor = NULL;
	this->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	this->wc.lpszMenuName = NULL;
	this->wc.lpszClassName = szWindowClass;
	this->wc.hIconSm = NULL;

	
	if (!RegisterClassEx(&wc)) 
		return -1;

	windowHandle = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOPMOST,
		szWindowClass, NULL,
		WS_POPUP | WS_OVERLAPPED | WS_POPUP,
		100, 100, windWidth, windHeight,
		NULL, NULL, hInst, NULL);

	if (!windowHandle) 
		return -1;

	if (!SetLayeredWindowAttributes(windowHandle, RGB(1, 0, 0), 0, LWA_COLORKEY)) 
		return -1;
	return true;
}
