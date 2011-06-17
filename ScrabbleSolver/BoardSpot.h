#pragma once

class CPiece;

// CBoardSpot command target

class CBoardSpot : public CObject
{
public:

	enum SpotType
	{
		BOARDSPOT_NORMAL,
		BOARDSPOT_DOUBLELETTER,
		BOARDSPOT_TRIPLELETTER,
		BOARDSPOT_DOUBLEWORD,
		BOARDSPOT_TRIPLEWORD
	};

	CBoardSpot( SpotType type, const RectF& rect );
	virtual ~CBoardSpot();

	SpotType GetType();
	void SetType(SpotType);

	CPiece* GetPiece();
	void SetPiece(CPiece* piece);

	const RectF& GetRect();
	void SetRect(const RectF& rect);

protected:
	SpotType m_type;
	CPiece* m_piece;
	RectF m_rect;
};


