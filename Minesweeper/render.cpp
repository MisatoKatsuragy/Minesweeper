#include "pch.h"
#include "render.h"

Render* g_render = NULL;

Render::Render(HWND hwnd) : m_hwnd(hwnd)
{
	HRESULT hr;
	hr = DirectDrawCreate(NULL, &m_factory, NULL); //создание фактории
	assert(SUCCEEDED(hr));
	hr = m_factory->SetCooperativeLevel(hwnd, DDSCL_NORMAL); //задание режима работы фактории
	assert(SUCCEEDED(hr));

	DDSURFACEDESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.dwSize = sizeof(desc);
	desc.dwFlags = DDSD_CAPS;
	desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	hr = m_factory->CreateSurface(&desc, &m_primary, NULL);
	assert(SUCCEEDED(hr));

	desc.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

	RECT rect;
	GetClientRect(hwnd, &rect);
	desc.dwWidth = rect.right - rect.left;
	desc.dwHeight = rect.bottom - rect.top;
	hr = m_factory->CreateSurface(&desc, &m_secondary, NULL);
	assert(SUCCEEDED(hr));

	hr = m_factory->CreateClipper(0, &m_clipper, NULL);
	assert(SUCCEEDED(hr));
	hr = m_clipper->SetHWnd(0, hwnd);
	assert(SUCCEEDED(hr));
	hr = m_primary->SetClipper(m_clipper);
	assert(SUCCEEDED(hr));
}

Render::~Render()
{
	if (m_factory)
	{
		if (m_primary)
		{
			m_primary->Release();
			m_primary = NULL;
		}
		if (m_secondary)
		{
			m_secondary->Release();
			m_secondary = NULL;
		}
		if (m_clipper)
		{
			m_clipper->Release();
			m_clipper = NULL;
		}
		m_factory->Release();
		m_factory = NULL;
	}
}

void Render::SetPixel(int x, int y, COLORREF color)
{
	HRESULT hr;
	DDBLTFX dd;
	RECT rct;

	ZeroMemory(&dd, sizeof(dd));

	dd.dwSize = sizeof(dd);
	dd.dwFillColor = color;
	SetRect(&rct, x, y, x + 1, y + 1);

	hr = m_secondary->Blt(&rct, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &dd);
	assert(SUCCEEDED(hr));
}

void Render::Clear(COLORREF color)
{
	HRESULT hr;
	DDBLTFX dd;
	RECT rct;

	ZeroMemory(&dd, sizeof(dd));

	dd.dwSize = sizeof(dd);
	dd.dwFillColor = color;
	GetClientRect(m_hwnd, &rct);

	hr = m_secondary->Blt(&rct, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &dd);
	assert(SUCCEEDED(hr));
}

void Render::Flip()
{
	HRESULT hr;
	RECT rctDst;
	RECT rctSrc;
	POINT p = { 0, 0 };

	GetClientRect(m_hwnd, &rctSrc);

	ClientToScreen(m_hwnd, &p);
	GetClientRect(m_hwnd, &rctDst);
	OffsetRect(&rctDst, p.x, p.y);

	hr = m_primary->Blt(&rctDst, m_secondary, &rctSrc, DDBLT_WAIT, NULL);
	assert(SUCCEEDED(hr));
}

bool Render::IsLost()
{
	return (m_primary->IsLost() == DDERR_SURFACELOST || 
		m_secondary->IsLost() == DDERR_SURFACELOST);
}

void Render::RestoreIfLost()
{
	if (m_primary->IsLost() == DDERR_SURFACELOST)
		m_primary->Restore();
	if (m_secondary->IsLost() == DDERR_SURFACELOST)
		m_secondary->Restore();
}
void  Render::DrawImage(LPBITMAP bitmap, int x, int y)
{
	HRESULT hr;
	DDBLTFX ddbltfx;
	RECT rct;
	assert(bitmap->bmBitsPixel >= 24);
	ZeroMemory(&ddbltfx, sizeof(ddbltfx));
	ddbltfx.dwSize = sizeof(ddbltfx);

	BYTE * pxl = static_cast<BYTE*>(bitmap->bmBits);
	for (long s = 0; s < bitmap->bmHeight; ++s)
	{
		BYTE * scanline = &pxl[((bitmap->bmHeight - 1) - s) * bitmap->bmWidthBytes];
		for (long p = 0; p < bitmap->bmWidth; ++p, scanline += 3)
		{
			ddbltfx.dwFillColor = RGB(scanline[0], scanline[1], scanline[2]);
			SetRect(&rct, x + p, y + s, x + p + 1, y + s + 1);
			hr = m_secondary->Blt(&rct, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx);
			assert(SUCCEEDED(hr));
		}
	}

	/*DWORD* pxl = static_cast<DWORD*>(bitmap->bmBits);
	for (long r = 0; r < bitmap->bmHeight; ++r)
	{
		for (long c = 0; c < bitmap->bmWidth; ++c)
		{
			long index = (((bitmap->bmHeight - 1) - r) * bitmap->bmHeight) + c;
			ddbltfx.dwFillColor = pxl[index];
			SetRect(&rct, x + c, y + r, x + c + 1, y + r + 1);
			hr = m_secondary->Blt(&rct, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddbltfx);
			assert(SUCCEEDED(hr));
		}
	 }*/
}

void Render::DrawString(LPCTSTR str, int x, int y, HFONT font)
{
	HDC hdc;
	m_secondary->GetDC(&hdc);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255));
	if (font)
		SelectObject(hdc, font);
	TextOut(hdc, x, y, str, wcslen(str));
	m_secondary->ReleaseDC(hdc);
}
