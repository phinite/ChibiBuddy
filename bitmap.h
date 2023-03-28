#pragma once

#include <wincodec.h>
#include "render.h"

class Bitmap
{
	Render* rnd;
	int bitmapWidth, bitmapHeight;
	int bitmapAccross;

public:
	ID2D1Bitmap* bmp;
	Bitmap(const wchar_t* filename, Render* rnd);
	Bitmap(const wchar_t* filename, Render* rnd, int bitmapWidth, int bitmapHeight);

	~Bitmap();

	void Draw();
	void Draw(int index, int x, int y);
};