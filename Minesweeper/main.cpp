#include "pch.h"
#include "window.h"

int main()
{
	g_wnd = new Window(640, 480, TEXT("title"));

	while(!g_wnd->IsClosed())
	{
		g_wnd->HandleMessages();
		Sleep(15);
	}
	delete g_wnd;
	g_wnd = NULL;
}