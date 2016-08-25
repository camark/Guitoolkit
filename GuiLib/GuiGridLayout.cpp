// GuiGridLayout.cpp : implementation file
//

#include "stdafx.h"
#include "GuiLib.h"
#include "GuiGridLayout.h"
#include "GuiDrawLayer.h"

// CGuiGridLayout

CControl::CControl(int nRow, int nCol, CWnd* pWnd)
{
	ASSERT_VALID(pWnd);
	m_nRow=nRow;
	m_nCol=nCol;
	m_pWnd=pWnd;
}

~CControl::CControl()
{

}

int CControl::GetRows()
{
	return m_nRow;
}

int CControl::GetCols()
{
	return m_nCol;
}

CWnd* CControl::GetCWnd(int nRows,int nCol)
{
	if (nRows==m_nRow && nCol == m_nCol)
		return m_pWnd;
}



IMPLEMENT_DYNAMIC(CGuiGridLayout, CWnd)
CGuiGridLayout::CGuiGridLayout()
{
	m_NumRows=0;
	m_NumCols=0;
	m_nInsets=1;
	m_GridBorder=GRIDNORMAL;
	m_pArray.RemoveAll();	
	m_clr=GuiDrawLayer::GetRGBColorFace();
	m_NumRowsAc=0;
	m_NumColsAc=0;
	nNumItems=0;
}

CGuiGridLayout::~CGuiGridLayout()
{
}


BEGIN_MESSAGE_MAP(CGuiGridLayout, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CGuiGridLayout message handlers


BOOL CGuiGridLayout::Create(CWnd* pParentWnd,int nNumRows, int nNumCols)
{
	// TODO: Add your specialized code here and/or call the base class
	m_NumRows=nNumRows;
	m_NumCols=nNumCols;
	return CWnd::Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(0,0,0,0), pParentWnd, 0x9999);
}

void CGuiGridLayout::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
		
	// TODO: Add your message handler code here
}


void CGuiGridLayout::SetBorders(GRIDBORDER GridBorder)
{
	m_GridBorder=GridBorder;
}

void CGuiGridLayout::SetColors(COLORREF m_clrColor)
{
	m_clr=m_clrColor;
}
void CGuiGridLayout::SetInsets(int nInsets)
{
	m_nInsets=nInsets;
}
void CGuiGridLayout::Add(CWnd* pWnd)
{
	m_NumColsAc++;
	if (m_NumColsAc >= nCol)
		if (m_NumRowsAc+1 < nRow)
		{
			m_NumColsAc=0;
			m_NumRowsAc++;
		}else
		{
			return ;
		}

	if (m_NumRowsAc < nRow)	
		if (m_NumColsAc < nCol)
		{
			m_pArray.SetAtGrow(nNumItems, new CControl(m_NumRowsAc, m_NumColsAc,pWnd);
		}
	RecalLayout();
}
void CGuiGridLayout::Add(int nRow,int nCol, CWnd* pWnd)
{	
	ASSERT_VALID(pWnd);
	if (nRow> m_NumRows || nCol >m_NumCols)
		return ;
	m_NumRowsAc=nRow;
	m_NumColsAc=nCol;
	m_pArray.SetAtGrow(nNumItems, new CControl(nRow, nCol,pWnd);
	RecalLayout();
}
void CGuiGridLayout::RecalLayout()
{
		
}


void CGuiGridLayout::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
}

void CGuiGridLayout::OnDestroy()
{
	for( int i=0; i<m_NumRows+m_NumCols; i++ )
    {
    CControl *pArr = (CControl*)m_pArray.GetAt(i);
    if( pArr )
        delete pArr;
    }
	
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
}
