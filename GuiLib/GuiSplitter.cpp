/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *							 (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software;so you are free to use it any of your		*
 * applications (Freeware, Shareware, Commercial),but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

#include "stdafx.h"
#include "guisplitter.h"
#include "guiDrawlayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CGuiSplitter

IMPLEMENT_DYNAMIC(CGuiSplitter, CWnd)

CGuiSplitter::CGuiSplitter()
{
	TypeAling=ALINGHORZ;
	m_nSizePix=4;
	mStyleSeparator=STYLE3D;
	bIniciaArrastre=FALSE;
	clrBg=GuiDrawLayer::GetRGBColorFace();
	mclrLeftTop=GuiDrawLayer::GetRGBColorBTNHigh();
	mclrBottomRight=GuiDrawLayer::GetRGBColorShadow();
	m_rectLeft=CRect(0,0,0,0);
	m_rectRight=CRect(0,0,0,0);
}

CGuiSplitter::~CGuiSplitter()
{
}


BEGIN_MESSAGE_MAP(CGuiSplitter, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


void CGuiSplitter::SeTypeALing(TYPEALING typeAling)
{
	TypeAling=typeAling;
	m_rcSpplitter=CRect(0,0,0,0);
	Invalidate();
	UpdateWindow();
}
// CGuiSplitter message handlers
void CGuiSplitter::SetColor(COLORREF m_clrface)
{
	clrBg=m_clrface;
}

int CGuiSplitter::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


BOOL CGuiSplitter::Create(CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	return CWnd::Create(NULL,NULL, WS_VISIBLE|WS_CHILD, CRect(0,0,0,0), pParentWnd, 0xffff);
}

void CGuiSplitter::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBrush cbr;
	CRect rcClient;
	GetClientRect(&rcClient);
	cbr.CreateSolidBrush(clrBg);
	
	CDC			MemDC;
	CBitmap		m_BitmapMemDC;
	MemDC.CreateCompatibleDC(&dc);
	m_BitmapMemDC.CreateCompatibleBitmap(&dc,
				  rcClient.Width(),rcClient.Height());	

	CBitmap* m_bitmapOld=MemDC.SelectObject(&m_BitmapMemDC);
	MemDC.FillRect(&rcClient,&cbr);
	DrawSplitter(m_rcSpplitter,m_rectLeft,m_rectRight,&MemDC);
	
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&MemDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();
}

void CGuiSplitter::SetPixelWidht(int nSizePix)
{
	m_nSizePix=nSizePix;
}

void  CGuiSplitter::AddLeftCtrl(CWnd* pWnd,long MinSize)
{
	ASSERT_VALID(pWnd);
	pWndLeft=pWnd;
}

void  CGuiSplitter::AddRightCtrl(CWnd* pWnd,long MinSize)
{
	ASSERT_VALID(pWnd);
    pWndRight=pWnd;
	RecalLayout();
}

void CGuiSplitter::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_rcSpplitter.PtInRect(point) && !bIniciaArrastre)
		{
			bIniciaArrastre=TRUE;		
			SetCapture ();
			InvalidateRect(m_rcSpplitter,TRUE);
		}
	else
		CWnd::OnLButtonDown(nFlags, point);
}

void CGuiSplitter::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (bIniciaArrastre==TRUE)
		{
			bIniciaArrastre=FALSE;
			RecalLayout();
			ReleaseCapture ();	
			Invalidate();
		}
	CWnd::OnLButtonUp(nFlags, point);
}



void CGuiSplitter::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect m_rectCli;
	GetClientRect(m_rectCli);
    if (bIniciaArrastre==TRUE)
    {
		m_rcSpplitterOld=m_rcSpplitter;
		if (TypeAling==ALINGHORZ)
		{
			if (point.x < m_rectCli.left) 
				m_rcSpplitter.left=m_rectCli.left+m_nSizePix;
			else if (point.x >m_rectCli.right)
				m_rcSpplitter.left=m_rectCli.right-m_nSizePix;
			else 
			{
				m_rcSpplitter.left=	point.x;
				m_rcSpplitter.right=point.x+m_nSizePix;
			}
		}
		else
		{
			if (point.y < m_rectCli.top) 
				m_rcSpplitter.top=m_rectCli.top+m_nSizePix;
			else if (point.y >m_rectCli.bottom)
				m_rcSpplitter.bottom=m_rectCli.top-m_nSizePix;
			else 
			{
				m_rcSpplitter.top=point.y;
				m_rcSpplitter.bottom=point.y+m_nSizePix;
			}	
		}
		CClientDC dc(this);
		InvalidateRect(m_rcSpplitterOld);
		RecalLayout();
	}
	else
		CWnd::OnMouseMove(nFlags, point);
}

void CGuiSplitter::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	RecalLayout();
	// TODO: Add your message handler code here
}

void  CGuiSplitter::RecalLayout()
{
	CRect m_rectCli;
	CRect m_rctemp;
	
	if (pWndLeft== NULL || pWndRight==NULL) return ;
	GetClientRect(m_rectCli);
	if (m_rectCli.IsRectEmpty()) return;
	
	if (m_rcSpplitter.left < m_rectCli.left ) m_rcSpplitter.left=m_rectCli.left+1;
	if (m_rcSpplitter.right > m_rectCli.right) m_rcSpplitter.right=m_rectCli.right-1;
	if (m_rcSpplitter.bottom > m_rectCli.bottom) m_rcSpplitter.bottom=m_rectCli.bottom-1;
	if (m_rcSpplitter.top < m_rectCli.top) m_rcSpplitter.top=m_rectCli.top+1;
	if (m_rcSpplitter.IsRectEmpty() || m_rcSpplitter.bottom >=5000 )
	{
		m_rcSpplitter=m_rectCli;
		if (TypeAling==ALINGHORZ)	
		{
			m_rcSpplitter.right=m_rectCli.Width()/2;
			m_rcSpplitter.left=m_rcSpplitter.right-m_nSizePix;	
		}
		else
		{
			m_rcSpplitter.bottom=m_rectCli.Height()/2;
			m_rcSpplitter.top=m_rcSpplitter.bottom-m_nSizePix;	
		}
	}
	
	if (TypeAling==ALINGHORZ)
	{
		m_rcSpplitter.right=m_rcSpplitter.left+m_nSizePix;
		m_rcSpplitter.bottom=m_rectCli.bottom;
	}
	else
	{
		m_rcSpplitter.bottom=m_rcSpplitter.top+m_nSizePix;	
		m_rcSpplitter.right=m_rectCli.right;
	}

	m_rctemp=m_rectCli;
	if (TypeAling==ALINGHORZ)
		m_rctemp.right=m_rcSpplitter.left-1;
	else
		m_rctemp.bottom=m_rcSpplitter.top-1;
	m_rectLeft=m_rctemp;
	m_rctemp.DeflateRect(1,1);
	pWndLeft->MoveWindow(m_rctemp);
	m_rctemp=m_rectCli;
	if (TypeAling==ALINGHORZ)
		m_rctemp.left=m_rcSpplitter.right+1;
	else
		m_rctemp.top=m_rcSpplitter.bottom+1;
	m_rectRight=m_rctemp;
	m_rctemp.DeflateRect(1,1);
	pWndRight->MoveWindow(m_rctemp);

}

void CGuiSplitter::OnSysColorChange()
{
	CWnd::OnSysColorChange();
	// TODO: Add your message handler code here
}

BOOL CGuiSplitter::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptCurPos;
	GetCursorPos (&ptCurPos);
	ScreenToClient (&ptCurPos);

	if (m_rcSpplitter.PtInRect (ptCurPos))
	{
		if(TypeAling==ALINGHORZ)
			SetCursor(AfxGetApp ()->LoadCursor (AFX_IDC_HSPLITBAR));
		else if(TypeAling==ALINGVERT)
			SetCursor(AfxGetApp ()->LoadCursor (AFX_IDC_VSPLITBAR));
		return TRUE;
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CGuiSplitter::SetStyleSeparator(STYLESEPARATOR StyleSeparator,COLORREF clrLeftTop,COLORREF clrBottomRight)
	
{
	mStyleSeparator=StyleSeparator;
	mclrLeftTop=clrLeftTop;
	mclrBottomRight=clrBottomRight;
}

void CGuiSplitter::DrawSplitter(CRect rcSeparator,CRect rcLeft,CRect rcRight,CDC* pDC)
{
	if (mStyleSeparator == STYLE3D)
	{
		pDC->Draw3dRect(rcLeft,mclrLeftTop,mclrBottomRight);
		pDC->Draw3dRect(rcRight,mclrLeftTop,mclrBottomRight);
	}
	

}

