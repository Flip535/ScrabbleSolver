#pragma once

// CPiece command target

class CPiece : public CObject
{
public:
	CPiece();
	virtual ~CPiece();

protected:
	TCHAR m_cLetter;
	short m_iPoints;
};


