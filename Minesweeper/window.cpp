#include "pch.h"
#include "window.h"
#include "resource.h"

Window* g_wnd = NULL;

LRESULT CALLBACK wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if(message == WM_CLOSE)
	{
		g_wnd->RequestClose();
	}
	else if (message == WM_COMMAND)
	{
		switch (LOWORD(wparam))
		{
		case ID_40001 :
		{
			break;
		}
		case ID_40002 :
		{
			break;
		}
		case ID_40003 :
		{
			break;
		}
		case ID_40004 :
		{
			g_wnd->RequestClose();
			break;
		}
		}
	}
	else if (message == WM_LBUTTONUP)
	{
		int x = GET_X_LPARAM(lparam);
		int y = GET_Y_LPARAM(lparam);

	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}

Window::Window(size_t width, size_t height, const wchar_t* title) : m_hwnd(NULL)
{
	WNDCLASSEX wndclsex;
	ZeroMemory(&wndclsex, sizeof(wndclsex));
	wndclsex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclsex.cbSize = sizeof(wndclsex);
	wndclsex.lpszClassName = TEXT("wnd");
	wndclsex.hInstance = GetModuleHandle(NULL);
	wndclsex.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wndclsex.lpfnWndProc = &wndproc;
	wndclsex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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

