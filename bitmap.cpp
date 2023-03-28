#include "bitmap.h"
#include "render.h"


Bitmap::Bitmap(const wchar_t* filename, Render* rnd)
{
	// Init
	this->rnd = rnd;
	bmp = NULL;
	HRESULT hr;

	IWICImagingFactory* wicFactory = NULL;
	IWICBitmapDecoder* wicDecoder = NULL;
	IWICBitmapFrameDecode* wicFrame = NULL;
	IWICFormatConverter* wicConverter = NULL;


	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	// Create the decoder
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	// Read frame from the image
	hr = wicDecoder->GetFrame(0, &wicFrame);

	// Create a converter
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	// Setup the converter
	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);

	// Use the converter to create a D2D1Bitmap
	rnd->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	bitmapWidth = bmp->GetSize().width;
	bitmapHeight = bmp->GetSize().height;
	bitmapAccross = 1;
}

Bitmap::Bitmap(const wchar_t* filename, Render* rnd, int bitmapWidth, int bitmapHeight) :
	Bitmap(filename, rnd)
{
	this->bitmapWidth = bitmapWidth;
	this->bitmapHeight = bitmapHeight;
	this->bitmapAccross = bmp->GetSize().width / bitmapWidth;
}

Bitmap::~Bitmap()
{
	if (bmp) bmp->Release();
}

void Bitmap::Draw()
{
	rnd->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height));
}

void Bitmap::Draw(int index, int x, int y)
{
	D2D1_RECT_F src =  D2D1::RectF(
		(float)((index % bitmapAccross) * bitmapWidth),
		(float)((index / bitmapAccross) * bitmapHeight),
		(float)((index % bitmapAccross) * bitmapWidth) + bitmapWidth,
		(float)((index / bitmapAccross) * bitmapHeight) + bitmapHeight);

	D2D1_RECT_F dest = D2D1::RectF(x, y, x + bitmapWidth, y + bitmapHeight);

	rnd->GetRenderTarget()->DrawBitmap(bmp, dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, src);
}
