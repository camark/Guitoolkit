/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *                           (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software; so you are free to use it any of your		*
 * applications(Freeware, Shareware, Commercial), but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements :(Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

#include "stdafx.h"
#include "GuiCapOutBar.h"
#include "GuiDrawLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(GuiCapOutBar, CControlBar)
	//{{AFX_MSG_MAP(GuiCapOutBar)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

GuiCapOutBar::GuiCapOutBar()
{
	m_iBorder      = 2;
	m_MiniTool     = NULL;
	m_miniSplitter = NULL;	
	m_StyleDisplay=GUISTYLE_XP;
}

GuiCapOutBar::~GuiCapOutBar()
{
}

BOOL GuiCapOutBar::Create(DWORD dwStyle, CWnd* pParentWnd, UINT uID, int iMaxi)
{
	SetBarStyle(CBRS_ALIGN_TOP);
	m_uID   = uID;
	m_iHigh = iMaxi;

	return CControlBar::Create(0, 0, dwStyle|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, CRect(0, 0, 0, 0), pParentWnd, uID);
}

void GuiCapOutBar::SetStyleFlag(BOOL m_bFlag)
{
	m_bIsFlag = m_bFlag;  // si quiere que se comporte como un boton
}

void GuiCapOutBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
}

CSize GuiCapOutBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	return CSize(32767, m_iHigh);
}

int GuiCapOutBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CControlBar::OnCreate(lpCreateStruct)==-1)
		return -1;

	return 0;
}

void GuiCapOutBar::OnPaint()
{
	CPaintDC dc(this);
	CRect rcClient;
	GetClientRect(&rcClient);
	CBrush cb;
	cb.CreateSysColorBrush(GuiDrawLayer::GetRGBColorFace(m_StyleDisplay));
	dc.FillRect(rcClient, &cb);
		
}

void GuiCapOutBar::RecalLayout()
{
	if (!GetSafeHwnd())
		return;
	CRect m_rc;
	GetClientRect(m_rc);
	if (m_MiniTool != NULL  && m_miniSplitter != NULL) 
	{
		CRect m_rctemp = m_rc;
		m_rctemp.right = m_rc.Width()/2;
		m_MiniTool->MoveWindow(m_rctemp);
		m_rctemp = m_rc;
		m_rctemp.left = (m_rc.Width()/2) + 1;
		m_miniSplitter->MoveWindow(m_rctemp);
	}
	else if (m_MiniTool != NULL)
	{
		m_MiniTool->MoveWindow(m_rc);
	}
	else if (m_miniSplitter != NULL)
	{
		m_miniSplitter->MoveWindow(m_rc);
	}
}

BOOL  GuiCapOutBar::SetSplitter(CGuiMiniSplitter* m_sppliter)
{
	if (!m_sppliter->Create(this))
		return FALSE;
	m_miniSplitter = m_sppliter;
	RecalLayout();

	return TRUE;
}

BOOL GuiCapOutBar::SetMiniTool(CGuiMiniTool* m_sppliter)
{
	if (!m_sppliter->Create(_T(""), WS_VISIBLE | WS_CHILD |SS_OWNERDRAW, 
		CRect(0, 0, 0, 0), this))
		return FALSE;
	m_MiniTool = m_sppliter;
	RecalLayout();

	return TRUE;
}


BOOL GuiCapOutBar::OnEraseBkgnd(CDC* pDC)
{
	CBrush cbr;
	cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(m_StyleDisplay));
	CRect m_rect;
	GetClientRect(m_rect);
	pDC->FillRect(m_rect, &cbr);
	cbr.DeleteObject();

	return TRUE;
}

void GuiCapOutBar::OnSize(UINT nType, int cx, int cy)
{
	CControlBar::OnSize(nType, cx, cy);
	RecalLayout();
}


void GuiCapOutBar::OnSysColorChange()
{
	CControlBar::OnSysColorChange();
}

void GuiCapOutBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	lpncsp->rgrc[0].bottom -= m_iBorder;
	lpncsp->rgrc[0].top    += m_iBorder + 3;
	lpncsp->rgrc[0].left   += m_iBorder;
	lpncsp->rgrc[0].right  -= m_iBorder;
}

void GuiCapOutBar::OnNcPaint()
{
	CRect rcWindow;
	CRect rcClient;
	CWindowDC	dc(this);
	GetWindowRect(&rcWindow);
	GetClientRect(&rcClient);
	CBrush cbr;
	cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(m_StyleDisplay));
	rcClient.OffsetRect(-rcWindow.TopLeft());
    rcWindow.OffsetRect(-rcWindow.TopLeft());
    ScreenToClient(rcWindow);
	rcClient.OffsetRect(-rcWindow.left, - rcWindow.top);
	dc.ExcludeClipRect(rcClient);   
	rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);
	int ibotton = rcWindow.bottom;
	rcWindow.top = rcWindow.bottom - m_iBorder;
	dc.FillRect(rcWindow, &cbr); 
	rcWindow.top = 0;
	rcWindow.bottom += 3;
	dc.FillRect(rcWindow, &cbr); 
	dc.FillSolidRect(0, rcWindow.top + 1, rcWindow.right + 1, 1, 
		GuiDrawLayer::GetRGBColorBTNHigh()); 
	cbr.DeleteObject();
}
