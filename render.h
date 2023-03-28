#pragma once

#include <Windows.h>
#include <d2d1.h>

#ifndef RENDER_H
#define RENDER_H

class Render
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
public:
	Render();
	~Render();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget()
	{
		return renderTarget;
	}


	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);


};

#endif