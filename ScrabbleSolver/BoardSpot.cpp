// BoardSpot.cpp : implementation file
//

#include "stdafx.h"
#include "ScrabbleSolver.h"
#include "BoardSpot.h"
#include "Piece.h"


// CBoardSpot

CBoardSpot::CBoardSpot(SpotType type, const RectF& rect):
				m_type(type), m_piece(NULL)
{
	m_rect = rect;
}

CBoardSpot::~CBoardSpot()
{
}


// CBoardSpot member functions

CBoardSpot::SpotType CBoardSpot::GetType()
{
	return m_type;
}

void CBoardSpot::SetType(CBoardSpot::SpotType type)
{
	m_type = type;
}

CPiece* CBoardSpot::GetPiece()
{
	return m_piece;
}

void CBoardSpot::SetPiece(CPiece* piece)
{
	ASSERT(m_piece == NULL);
	m_piece = piece;
}

const RectF& CBoardSpot::GetRect()
{
	return m_rect;
}

void CBoardSpot::SetRect(const RectF& rect)
{
	m_rect = rect;
}