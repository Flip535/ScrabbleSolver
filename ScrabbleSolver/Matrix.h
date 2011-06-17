#pragma once

// CMatrix command target

class CMatrix : public CObArray
{
public:
	CMatrix(int rows, int cols);
	virtual ~CMatrix();
	void Add( int row, int col, CObject* obj ); // Add an item to the end of a specified row
	void Add( int row, CObject* obj ); // Add an item to the end of a specified row
	CObject* GetAt(int row, int col);
};


