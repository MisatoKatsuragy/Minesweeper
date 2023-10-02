#include "pch.h"
#include "game.h"
#include "render.h"

#define CELL_SIZE 16

Game* g_game = NULL;

Game::Game()
{
	m_position.x = 20;
	m_position.y = 20;
	TCHAR buff[16];
	DIBSECTION dib;
	m_bitmaps.resize(CellType_Max);
	for (size_t i = 0; i < CellType_Max; ++i)
	{
		wsprintf(buff, TEXT("Cells\\%i.bmp"), i);
		m_bitmaps[i] = (HBITMAP)LoadImage(NULL, buff, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		assert(m_bitmaps[i] != NULL);
		GetObject(m_bitmaps[i], sizeof(dib), &dib);
	}
}

Game::~Game()
{
	size_t i = 0;
	for (; i < CellType_Max; ++i)
	{
		DeleteBitmap(m_bitmaps[i]);
	}
}

void Game::Start(USHORT x, USHORT y, USHORT mines)
{
	m_mines = mines;
	m_width = x;
	m_height = y;
	m_cells.assign(m_width * m_height, Cell(false));
}

void Game::PlaceMines()
{
	for (USHORT i = 0; i < m_mines; ++i) {
		size_t position;
		do {
			position = rand() % m_cells.size(); // √енерируем случайное местоположение дл€ мины
		} while (m_cells[position].IsMine() || m_cells[position].IsOpen()); // ѕовтор€ем, пока не найдем пустую €чейку

		m_cells[position] = Cell(true); // ”станавливаем мину в найденной €чейке
	}
}

void Game::Draw()
{
	for (USHORT y = 0; y < m_height; ++y)
	{
		for (USHORT x = 0; x < m_width; ++x)
		{
			/*DIBSECTION dib;
			GetObject(m_bitmaps[11], sizeof(dib), &dib);
			g_render->DrawImage	(&dib.dsBm, 
								(m_position.x + CELL_SIZE * x), 
								(m_position.y + CELL_SIZE * y));*/
			CellType cellType = GetCellType(x, y);
			DIBSECTION dib;
			GetObject(m_bitmaps[cellType], sizeof(dib), &dib);
			g_render->DrawImage	(&dib.dsBm,
								m_position.x + CELL_SIZE * x,
								m_position.y + CELL_SIZE * y);
		}
	}
}

Game::CellType Game::GetCellType(USHORT x, USHORT y) const
{
	CellType cellType;

	const Cell& cell = GetCell(x, y);
	if (!cell.IsOpen())
	{
		cellType = CellType_Closed;
		if (cell.IsFlagged())
		{
			cellType = CellType_Flagged;
		}
	}
	else
	{
		BYTE mineCount = 0;
		if (x > 0 && GetCell(x - 1, y).IsMine())
		{
			++mineCount;
		}
		if (y > 0 && GetCell(x, y - 1).IsMine())
		{
			++mineCount;
		}
		if (y > 0 && x > 0 && GetCell(x - 1, y - 1).IsMine())
		{
			++mineCount;
		}
		if (x < m_width && y > 0 && GetCell(x + 1, y - 1).IsMine())
		{
			++mineCount;
		}
		if (x < m_width && GetCell(x + 1, y).IsMine())
		{
			++mineCount;
		}
		if (x < m_width && y < m_height && GetCell(x + 1, y + 1).IsMine())
		{
			++mineCount;
		}
		if (y < m_height && GetCell(x, y + 1).IsMine())
		{
			++mineCount;
		}
		if (x > 0 && y < m_height && GetCell(x - 1, y + 1).IsMine())
		{
			++mineCount;
		}
		cellType = mineCount;
	}

	return (cellType);
}

bool Game::ToIndexed(const POINT& frst_pnt, POINT& secd_pnt) const
{
	if (frst_pnt.x <= m_position.x || frst_pnt.y <= m_position.y)
	{
		return (false);
	}

	
}