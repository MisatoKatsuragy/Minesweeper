#pragma once

class Cell
{
	enum state
	{
		ISMINED = 1 << 0,
		ISFLAGGED = 1 << 1,
		ISOPEN = 1 << 2
	};

public:
	inline Cell(bool isMined) : m_st(0)
	{
		if (isMined)
		{
			m_st |= ISMINED;
		}
	}
	inline void ToggleFlag()
	{
		if (IsFlagged())
		{
			m_st &= ~ISFLAGGED;
		}
		else
		{
			m_st |= ISFLAGGED;
		}
	}
	inline void Show()
	{
		m_st |= ISOPEN;
	}
	inline bool IsMine() const
	{
		return (m_st & ISMINED);
	}
	inline bool IsFlagged() const
	{
		return (m_st & ISFLAGGED);
	}
	inline bool IsOpen() const
	{
		return (m_st & ISOPEN);
	}


private:
	UINT m_st;
};