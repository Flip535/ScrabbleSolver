// Matrix.cpp : implementation file
//

#include "stdafx.h"
#include "ScrabbleSolver.h"
#include "Matrix.h"


// CMatrix

CMatrix::CMatrix(int rows, int cols)
{
	//this->SetSize(rows);
	for(int i=0; i<rows; i++)
	{
		CObArray* row = new CObArray();
		//row->SetSize(cols);
		CObArray::Add( row );
	}
}

CMatrix::~CMatrix()
{
	for(int i=0; i<this->GetCount(); i++)
	{
		delete (*this)[i];
	}
}

void CMatrix::Add(int row, int col, CObject* obj)
{
	((CObArray*)(CObArray::GetAt(row)))->InsertAt(col, obj);
}

void CMatrix::Add(int row, CObject* obj)
{
	((CObArray*)(CObArray::GetAt(row)))->Add(obj);
}

CObject* CMatrix::GetAt(int row, int col)
{
	return ((CObArray*)((*this)[row]))->GetAt(col);
}


// CMatrix member functions
