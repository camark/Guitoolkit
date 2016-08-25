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
#include "GuiMiniSplitter.h"
#include "GuiDrawLayer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiMiniSplitter

CGuiMiniSplitter::CGuiMiniSplitter()
{
	bIniciaArrastre=FALSE;
	m_clrface=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	m_clrborder=GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style);	
	m_ToolLeft=NULL;
	m_ToolRight=NULL;

}

CGuiMiniSplitter::~CGuiMiniSplitter()
{
}


BEGIN_MESSAGE_MAP(CGuiMiniSplitter, CWnd)
	//{{AFX_MSG_MAP(CGuiMiniSplitter)
	ON_WM_SIZE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGuiMiniSplitter message handlers

BOOL CGuiMiniSplitter::Create(CWnd* pParentWnd)
{
	return CWnd::Create(0,0,
				 WS_CHILD|WS_VISIBLE,CRect(0,0,0,0), pParentWnd,0xffff);
}

void CGuiMiniSplitter::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	RecalLayout();
	// TODO: Add your message handler code here
	
}

void CGuiMiniSplitter::RecalLayout()
{
	CRect m_rectCli;
	CRect m_rctemp;
	if (m_ToolLeft== NULL || m_ToolRight==NULL) return ;
	GetClientRect(m_rectCli);
	if (m_rectCli.IsRectEmpty()) return;
	if (m_rcSplitter.IsRectEmpty())
	{
		m_rcSplitter=m_rectCli;
		m_rcSplitter.right=m_rectCli.Width()/2;
		m_rcSplitter.left=m_rcSplitter.right-3;	
	}
	
	m_rcSplitter.right=m_rcSplitter.left+3;
	m_rctemp=m_rectCli;
	m_rctemp.right=m_rcSplitter.left-1;
	m_ToolLeft->MoveWindow(m_rctemp);
	m_ToolLeft->UpdateWindow();
	m_rctemp=m_rectCli;
	m_rctemp.left=m_rcSplitter.right+1;
	m_ToolRight->MoveWindow(m_rctemp);
	m_ToolRight->UpdateWindow();
}
void CGuiMiniSplitter::OnSysColorChange() 
{
	CWnd::OnSysColorChange();
	m_clrface=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	m_clrborder=GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style);	
}

void CGuiMiniSplitter::OnPaint() 
{
	CPaintDC dc(this);
	CBrush cbr;
	CRect rcClient;
	GetClientRect(&rcClient);
	m_clrface=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	cbr.CreateSolidBrush(m_clrface);
	
	CDC			MemDC;
	CBitmap		m_BitmapMemDC;
	MemDC.CreateCompatibleDC(&dc);
	m_BitmapMemDC.CreateCompatibleBitmap(&dc,
				  rcClient.Width(),rcClient.Height());	

	CBitmap* m_bitmapOld=MemDC.SelectObject(&m_BitmapMemDC);
	MemDC.FillRect(&rcClient,&cbr);
	DrawSplitter(m_rcSplitter,&MemDC);
	
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&MemDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();
	cbr.DeleteObject();
}


void CGuiMiniSplitter::OnLButtonUp(UINT nFlags, CPoint point) 
{
		if (bIniciaArrastre==TRUE)
		{
			bIniciaArrastre=FALSE;
			RecalLayout();
			ReleaseCapture ();	
			Invalidate();
		}
		
	
		CWnd::OnLButtonUp(nFlags, point);

}



void CGuiMiniSplitter::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_rcSplitter.PtInRect(point) && !bIniciaArrastre)
		{
			bIniciaArrastre=TRUE;		
			SetCapture ();
			InvalidateRect(m_rcSplitter,TRUE);
		}
	else
		CWnd::OnLButtonDown(nFlags, point);
}

void CGuiMiniSplitter::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect m_rectCli;
	GetClientRect(m_rectCli);
    if (bIniciaArrastre==TRUE)
    {
		m_rcSplitterOld=m_rcSplitter;
		if (point.x < m_rectCli.left+50) 
			m_rcSplitter.left=50;
		else if (point.x >m_rectCli.right-50)
			m_rcSplitter.left=m_rectCli.right-55;
		else 
		{
			m_rcSplitter.left=	point.x;
			m_rcSplitter.right=point.x+3;
		}
		CClientDC dc(this);
		
		DrawSplitter(m_rcSplitter,&dc);
		InvalidateRect(m_rcSplitterOld);
		RecalLayout();

	}
	else
		CWnd::OnMouseMove(nFlags, point);
}

BOOL CGuiMiniSplitter::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptCurPos;
	GetCursorPos (&ptCurPos);
	ScreenToClient (&ptCurPos);

	if (m_rcSplitter.PtInRect (ptCurPos))
	{
		SetCursor (LoadCursor(NULL, IDC_SIZEWE));
		return TRUE;
	}
		
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CGuiMiniSplitter::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnTimer(nIDEvent);
}

BOOL CGuiMiniSplitter::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void  CGuiMiniSplitter::SetColor(COLORREF m_clrFace,COLORREF m_clrBorder)
{
	if (!GetSafeHwnd()) return;
	if (!HIWORD(m_ToolLeft) || !HIWORD(m_ToolRight))
		return;
	m_clrface=m_clrFace;
	m_clrborder=m_clrBorder;

	m_ToolLeft->SetColor(m_clrface);
	m_ToolRight->SetColor(m_clrface);
}


BOOL CGuiMiniSplitter::AddMiniToolLeft(CGuiMiniTool * m_Toolleft)
{
	if (!m_Toolleft->Create(_T(""),WS_VISIBLE | WS_CHILD |SS_OWNERDRAW, 
						CRect(0,0,0,0), this))
		return FALSE;
	m_ToolLeft= m_Toolleft;
	return TRUE;
}

BOOL CGuiMiniSplitter::AddMiniToolRight(CGuiMiniTool * m_Toolright)
{
	CRect m_rectCli;
	GetClientRect(m_rectCli);
	if (!m_Toolright->Create(_T(""),WS_VISIBLE | WS_CHILD |SS_OWNERDRAW, 
						CRect(0,0,0,0), this))
		return FALSE;
	m_ToolRight=m_Toolright;
	RecalLayout();
	return TRUE;
}


void  CGuiMiniSplitter::DrawSplitter(CRect rc,CDC* pDC)
{
	//CClientDC dc(this);
	rc.top+=1;
	rc.bottom-=1;
	pDC->Draw3dRect(rc,m_clrborder,m_clrborder);

}


