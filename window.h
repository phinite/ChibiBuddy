#pragma once
#include <Windows.h>


class Window
{

public:
	WNDCLASSEXW wc;
	HWND windowHandle;
	Window();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	int Init(HINSTANCE hInst, const wchar_t* szWindowClass, int windWidth, int windHeight);

};