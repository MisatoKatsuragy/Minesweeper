#include "pch.h"
#include "window.h"

LRESULT CALLBACK wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if(message == WM_CLOSE)
	{
		g_wnd->RequestClose();
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}

Window::Window(size_t width, size_t height, const wchar_t* title) : m_hwnd(NULL)
{
	WNDCLASSEX wndclsex;
	ZeroMemory(&wndclsex, sizeof(wndclsex));
	wndclsex.cbSize = sizeof(wndclsex);
	wndclsex.lpszClassName = TEXT("wnd");
	wndclsex.hInstance = GetModuleHandle(NULL);
	wndclsex.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wndclsex.lpfnWndProc = &wndproc;
	assert(RegisterClassEx(&wndclsex));

	m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, wndclsex.lpszClassName, title, WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, wndclsex.hInstance, NULL);
	assert(m_hwnd != NULL);

	ShowWindow(m_hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_hwnd);

	m_closed = false;
}

void Window::Close()
{
	if(m_hwnd)
	{
		CloseWindow(m_hwnd);
		m_hwnd = NULL;
	}
}

void Window::Hide()
{
	ShowWindow(m_hwnd, SW_HIDE);
}

void Window::Show()
{
	ShowWindow(m_hwnd, SW_SHOW);
}

void Window::HandleMessages()
{
	MSG msg;
	while(PeekMessage(&msg, m_hwnd, 0, 0, PM_NOREMOVE))
	{
		if(GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

}

Window* g_wnd;