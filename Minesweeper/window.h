#pragma once

class Window
{
public:
	Window(size_t width, size_t height, const wchar_t* title); 
	inline ~Window()
	{
		Close();
	}
	void Resize(size_t height, size_t width);
	void Close();
	void Hide();
	void Show();
	inline void RequestClose()
	{
		m_closed = true;
	}

	inline bool IsClosed() const
	{
		return(m_closed);
	}

	void HandleMessages();

private:
	HWND m_hwnd;
	bool m_closed;
};

extern Window* g_wnd;