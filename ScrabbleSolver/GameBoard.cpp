// GameBoard.cpp : implementation file
//

#include "stdafx.h"
#include "ScrabbleSolver.h"
#include "GameBoard.h"


// CGameBoard

CGameBoard::CGameBoard(int rows, int cols):
				CMatrix(rows,cols)
{

}

CGameBoard::~CGameBoard()
{
	for( int i=0; i<this->GetCount(); i++ )
	{
		CObArray* row = (CObArray*)CObArray::GetAt(i);
		for( int j=0; j<row->GetCount(); j++ )
		{
			delete this->GetAt(i,j);
		}
	}
}


// CGameBoard member functions

void CGameBoard::AddBoardSpot( int row, CBoardSpot::SpotType type, const RectF& rect)
{
	this->AddBoardSpot( row, -1, type, rect );
}

void CGameBoard::AddBoardSpot( int row, int col, CBoardSpot::SpotType type, const RectF& rect)
{
	CBoardSpot* boardSpot = new CBoardSpot(type,rect);

	if( col == -1 )
		this->Add(row, boardSpot);
	else
		this->Add(row, col, boardSpot);
}