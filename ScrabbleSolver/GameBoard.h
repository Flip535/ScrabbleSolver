#pragma once
#include "Matrix.h"
#include "BoardSpot.h"

// CGameBoard command target

class CGameBoard : public CMatrix
{
public:
	CGameBoard(int rows, int cols);
	virtual ~CGameBoard();
	void AddBoardSpot( int row, CBoardSpot::SpotType type, const RectF& rect ); 
	void AddBoardSpot( int row, int col, CBoardSpot::SpotType type, const RectF& rect ); 
};


