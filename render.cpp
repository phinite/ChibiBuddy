#include "render.h"

Render::Render()
{
	factory = NULL;
	renderTarget = NULL;
}

Render::~Render()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
}

bool Render::Init(HWND windowHandle)
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (hr != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	hr = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_UNKNOWN)),
		D2D1::HwndRenderTargetProperties(
			windowHandle, 
			D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (hr != S_OK) return false;
	return true;
}

void Render::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}
