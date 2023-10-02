#include "pch.h"
#include "window.h"
#include "render.h"
#include "game.h"

//DO margin


int main()
{
	g_wnd = new Window(640, 480, TEXT("title"));
	g_render = new Render(g_wnd->GetHwnd());
	g_game = new Game();
	g_game->Start(8, 8, 9);
	//HBITMAP hbt = (HBITMAP)LoadImage(NULL, TEXT("test.bmp"), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	//assert(hbt);
	//DIBSECTION dib;
	//GetObject(hbt, sizeof(dib), &dib);

	while(!g_wnd->IsClosed())
	{
		g_wnd->HandleMessages();
		if (!g_wnd->IsClosed())
		{ 
			g_render->RestoreIfLost();
			if (g_render->IsLost())
			{
				continue;
			}
			g_render->Clear(RGB(0, 0, 0));
			g_game->Draw();
			//g_render->SetPixel(100, 100, RGB(255, 255, 255));
			//g_render->DrawImage(&dib.dsBm, 100, 100);

			g_render->Flip();
			Sleep(15);
		}
	}

	//if (hbt)
	//{
	//	DeleteBitmap(hbt);
	//	hbt = NULL;
	//}
	delete g_game;
	g_game = NULL;
	delete g_render;
	g_render = NULL;
	delete g_wnd;
	g_wnd = NULL;
}