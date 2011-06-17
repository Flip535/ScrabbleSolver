// WndGameBoard.cpp : implementation file
//

#include "stdafx.h"
#include "ScrabbleSolver.h"
#include "WndGameBoard.h"
#include "BoardSpot.h"


// CWndGameBoard

IMPLEMENT_DYNAMIC(CWndGameBoard, CWnd)

CWndGameBoard::CWndGameBoard(int rows, int cols, DWORD gameboardid):
m_rows(rows), m_cols(cols), m_gameBoardImg(gameboardid,RT_RCDATA,::AfxGetResourceHandle()), m_spotPos(-1,-1), m_gameBoard(rows,cols)
{
	if(!RegisterWndClass())
		ASSERT(FALSE);

	RectF boardRect(0,0,m_gameBoardImg.GetWidth(),m_gameBoardImg.GetHeight());
	RectF spotRect(0,0,((float)m_gameBoardImg.GetWidth())/m_rows,((float)m_gameBoardImg.GetHeight())/m_cols);
	for(int i=0; i<m_rows; i++)
	{
		for(int j=0; j<m_cols; j++)
		{
			RectF rect = spotRect;
			rect.Inflate(-3,-3);
			rect.Offset( PointF( i*spotRect.Width, j*spotRect.Height ) );
			m_gameBoard.AddBoardSpot(i, CBoardSpot::BOARDSPOT_NORMAL, rect);
		}
	}
}

CWndGameBoard::~CWndGameBoard()
{
	while(m_arrRects.GetCount())
	{
		delete (RectF*)m_arrRects[m_arrRects.GetCount()-1];
		m_arrRects.RemoveAt(m_arrRects.GetCount()-1);
	}
}


BEGIN_MESSAGE_MAP(CWndGameBoard, CWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CWndGameBoard message handlers



int CWndGameBoard::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


BOOL CWndGameBoard::RegisterWndClass()
{
    WNDCLASS windowclass;
	memset(&windowclass, 0, sizeof(WNDCLASS));   // start with NULL defaults

    HINSTANCE hInst = AfxGetInstanceHandle();

    //Check weather the class is registerd already

    if (!(::GetClassInfo(hInst, WNDGAMEBOARD, &windowclass)))
    {
        //If not then we have to register the new class

        windowclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

        windowclass.lpfnWndProc = ::DefWindowProc;
        windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
        windowclass.hInstance = hInst;
        windowclass.hIcon = NULL;
        windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
        windowclass.lpszMenuName = NULL;
        windowclass.lpszClassName = WNDGAMEBOARD;

        if (!AfxRegisterClass(&windowclass))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}

BOOL CWndGameBoard::OnEraseBkgnd(CDC* pDC)
{
	//if(	!CWnd::OnEraseBkgnd(pDC) )
		//return FALSE;

	Graphics g(pDC->m_hDC);
	g.DrawImage(m_gameBoardImg,0,0);

	SolidBrush br(Color(255,255,0));

	if(m_spotPos.x !=-1 )
	{
		CBoardSpot* spot = (CBoardSpot*)m_gameBoard.GetAt( m_spotPos.x, m_spotPos.y );
		RectF rect = spot->GetRect();
		g.FillRectangle(&br,rect.X,rect.Y,rect.Width,rect.Height);
	}

	return TRUE;
}

void CWndGameBoard::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	for(int i=0; i<this->m_gameBoard.GetCount(); i++)
	{
		CObArray* row = (CObArray*)m_gameBoard[i];
		for(int j=0; j<row->GetCount(); j++)
		{
			CBoardSpot* spot = (CBoardSpot*)row->GetAt(j);
			if(spot->GetRect().IntersectsWith(RectF(point.x,point.y,1,1)))
			{
				m_spotPos.x = i;
				m_spotPos.y = j;
			}
		}
	}

	Invalidate();

	CWnd::OnMouseMove(nFlags, point);
}

HBRUSH CWndGameBoard::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}
