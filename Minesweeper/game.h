#pragma once
#include "cell.h"

//// Расставляем N мин случайным образом
//for (unsigned int i = 0; i < N; ++i) {
//	int position;
//	do {
//		position = distrib(gen); // Генерируем случайное местоположение для мины
//	} while (field[position]); // Повторяем, пока не найдем пустую ячейку
//
//	field[position] = true; // Устанавливаем мину в найденной ячейке
//}

class Game
{
public:
	enum CellType_
	{
		CellType_Empty,
		CellType_NumericBegin,
		CellType_NumericEnd = CellType_NumericBegin + 8,
		CellType_Flagged = CellType_NumericEnd,
		CellType_Mine,
		CellType_Closed,
		CellType_Max
	};

	typedef BYTE CellType;

public:
	Game();
	~Game();
	void Start(USHORT x, USHORT y, USHORT mines);
	void PlaceMines();
	void OpenCell(USHORT x, USHORT y);
	inline void ToggleFlag(USHORT x, USHORT y)
	{
		GetCell(x, y).ToggleFlag();
	}
	void Draw();
	bool ToIndexed(const POINT& frst_pnt, POINT& secd_pnt) const;

private:
	CellType GetCellType(USHORT x, USHORT y) const;
	inline Cell& GetCell(USHORT x, USHORT y)
	{
		return (m_cells[y * m_height + x]);
	}
	inline const Cell& GetCell(USHORT x, USHORT y) const
	{
		return (m_cells[y * m_height + x]);
	}

private:
	POINT m_position;
	USHORT m_width;
	USHORT m_height;
	USHORT m_mines;
	std::vector<Cell> m_cells;
	std::vector<HBITMAP> m_bitmaps;
};

extern Game* g_game;