#include "pch.h"
#include "render.h"

Render::Render(HWND hwnd)
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
}