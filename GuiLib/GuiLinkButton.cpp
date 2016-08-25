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
#include "GuiLinkButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiLinkButton

CGuiLinkButton::CGuiLinkButton()
{
	m_clNormal=RGB(0,0,200);
	m_clover=RGB(0,0,255);
	m_Link="";
	m_cfont.CreateFont(14,0,0,0,400,0,1,0,0,1,2,1,34,_T("Arial"));
	m_iSelected=0;
	m_rectMsg.SetRectEmpty( );
	m_bFirstPas=TRUE;
}

CGuiLinkButton::~CGuiLinkButton()
{
}


BEGIN_MESSAGE_MAP(CGuiLinkButton, CButton)
	//{{AFX_MSG_MAP(CGuiLinkButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiLinkButton message handlers

void CGuiLinkButton::SetColorNormal(COLORREF m_clnor)
{
	m_clNormal=m_clnor;
}
void CGuiLinkButton::SetColorSelect(COLORREF m_clselec)
{
	m_clover=m_clselec;
}
void CGuiLinkButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect m_rect=lpDrawItemStruct->rcItem;
	CSize SizeCad=CSize(0,0);
	int m_iStatus=lpDrawItemStruct->itemState;
	int m_iMode;
	int m_iposx;
	int m_iposy;
	CBrush cb;
	cb.CreateSysColorBrush(COLOR_BTNFACE); 
	static CPoint pt=CPoint(2,1);
	CString m_sCaption;
	GetWindowText(m_sCaption);
	
	//se calcula la posición exacta del texto para que solo se 
	//seleccione cuando se encuentre el puntero en el rectangulo
	SizeCad=pDC->GetTextExtent(m_sCaption);
	if (m_bFirstPas==TRUE)
	{
	if (SizeCad.cx < m_rect.Width())
	{
		pDC->FillRect(m_rect,&cb);
		m_iposx=m_rect.Width()-(SizeCad.cx+10);
		m_iposy=m_rect.Height()-SizeCad.cy;
		m_rectMsg=m_rect;
		m_rectMsg.bottom=m_rect.bottom-(m_iposy-2);
		m_rectMsg.right=m_rect.right-(m_iposx);
		
		SetWindowPos (NULL, m_rectMsg.left, m_rectMsg.top,m_rectMsg.right, m_rectMsg.bottom,
			SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
		m_bFirstPas=FALSE;
		
	}
	}
	m_iMode=pDC->SetBkMode(TRANSPARENT);
	CFont* m_OldFont=pDC->SelectObject(&m_cfont);
	if (m_iSelected==1)
		pDC->SetTextColor(m_clover);
	else
		pDC->SetTextColor(m_clNormal);
	pDC->DrawState(pt, SizeCad, m_sCaption, (m_iStatus==ODS_DISABLED)?DSS_DISABLED:DSS_NORMAL, TRUE, 0, (CBrush*)NULL);
	pDC->SelectObject(m_OldFont);
	pDC->SetBkMode(m_iMode);
}

void CGuiLinkButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

BOOL CGuiLinkButton::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (GetSafeHwnd() == NULL) return FALSE;
	if (pMsg->message== WM_MOUSEMOVE)
		if (m_ToolTipCtrl.GetSafeHwnd())
			m_ToolTipCtrl.RelayEvent(pMsg);
	return CButton::PreTranslateMessage(pMsg);
}

BOOL CGuiLinkButton::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}

void CGuiLinkButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	::SetCursor(::LoadCursor(NULL,MAKEINTRESOURCE(32649)));//IDC_HAND));
 	
	CRect m_rect;
	GetClientRect(&m_rect);
	if (m_iSelected == 1) return;
	if (m_rect.PtInRect(point))
	{
		m_iSelected =1;
		Invalidate();
		UpdateWindow();
		SetTimer(1,100,NULL);
		}
	
	CButton::OnMouseMove(nFlags, point);
}

void CGuiLinkButton::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(nIDEvent== 1)
	{
		CPoint pt=GetMessagePos();
		ScreenToClient(&pt);
		if (!m_rectMsg.PtInRect(pt))
		{
			m_iSelected=0;
			Invalidate();
			UpdateWindow();
			KillTimer(1);
		}
	}
	CButton::OnTimer(nIDEvent);
}

void CGuiLinkButton::SetToolTip(LPCTSTR m_lpMsg)
{
	if (GetSafeHwnd()== NULL) return;
	if (m_lpMsg != NULL)
	{
		if (m_ToolTipCtrl.GetSafeHwnd () == NULL) 
		{
			m_ToolTipCtrl.Create(this,TTS_ALWAYSTIP);
			m_ToolTipCtrl.Activate(TRUE);
			m_ToolTipCtrl.AddTool(this,m_lpMsg);
		}
		else
		{
			m_ToolTipCtrl.UpdateTipText(m_lpMsg,this);	
		}
	}
	else
	{
		if (m_ToolTipCtrl.GetSafeHwnd () == NULL) 
		{
			m_ToolTipCtrl.Create(this,TTS_ALWAYSTIP);
			m_ToolTipCtrl.AddTool(this,m_lpMsg);
		}
		else
			m_ToolTipCtrl.UpdateTipText(m_lpMsg,this);	
		m_ToolTipCtrl.Activate(FALSE);
	}
}

void CGuiLinkButton::SetLink(LPCTSTR lpMsg)
{
	m_Link=lpMsg;
}
void CGuiLinkButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ShellExecute (NULL, _T("open"),m_Link, NULL, NULL, 0) ;
	CButton::OnLButtonDown(nFlags, point);
}

int CGuiLinkButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	// TODO: Add your specialized creation code here
	
	return 0;
}


BOOL CGuiLinkButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
		
		SetCursor(::LoadCursor(NULL,MAKEINTRESOURCE(32649)));	
		return CButton::OnSetCursor(pWnd, nHitTest, message);
		

}
