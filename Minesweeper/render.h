#pragma once

class Render
{
public:
	Render(HWND hwnd);
	~Render();
	void SetPixel(int x, int y, COLORREF color);
	void Clear(COLORREF color);
	void DrawImage(LPBITMAP bitmap, int x, int y);
	void DrawString(LPCTSTR str, int x, int y, HFONT font);
	void Flip();
	bool IsLost();
	void RestoreIfLost();

private:
	HWND m_hwnd;
	LPDIRECTDRAW m_factory;
	LPDIRECTDRAWSURFACE m_primary;
	LPDIRECTDRAWSURFACE m_secondary;
	LPDIRECTDRAWCLIPPER m_clipper;
};

extern Render* g_render;