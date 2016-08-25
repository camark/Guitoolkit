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
#include "GuiDockToolBar.h"
#include "GuiDrawlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiDockToolBar

CGuiDockToolBar::CGuiDockToolBar()
{
	m_clrface=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	m_Size=3;
}

CGuiDockToolBar::~CGuiDockToolBar()
{

}


BEGIN_MESSAGE_MAP(CGuiDockToolBar, CControlBar)
	//{{AFX_MSG_MAP(CGuiDockToolBar)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGuiDockToolBar message handlers

BOOL CGuiDockToolBar::Create(CWnd* pParentWnd,DWORD dwAling) 
{
	// TODO: Add your specialized code here and/or call the base class
/*		ASSERT (  (dwAling & CBRS_ALIGN_TOP) &&
				  (dwAling & CBRS_ALIGN_RIGHT) &&
				  (dwAling & CBRS_ALIGN_BOTTOM) &&
				  (dwAling & CBRS_ALIGN_LEFT) );
*/	ASSERT ( dwAling & CBRS_ALIGN_ANY);
	SetBarStyle (dwAling);
	DWORD dwStyle = CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;
	if (pParentWnd->GetStyle() & WS_THICKFRAME)
		dwStyle |= SBARS_SIZEGRIP;
	dwStyle |= WS_CHILD|WS_VISIBLE;
	return CControlBar::Create(0,0,dwStyle,
						CRect(0,0,0,0),pParentWnd,0x9999);
}

int CGuiDockToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

BOOL CGuiDockToolBar::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	CBrush cbr;
	cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	CRect m_rect;
	GetClientRect(m_rect);
	pDC->FillRect(m_rect,&cbr);
	return TRUE;

}


void CGuiDockToolBar::OnSysColorChange()
{
	m_clrface=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	CControlBar::OnSysColorChange();
}

void CGuiDockToolBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect m_rect;
	GetClientRect(m_rect);
	CBrush cbr;
	m_clrface=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	cbr.CreateSolidBrush(m_clrface);
	dc.FillRect(m_rect,&cbr);

	// TODO: Add your message handler code here
	
	// Do not call CControlBar::OnPaint() for painting messages
}


void CGuiDockToolBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// TODO: Add your message handler code here and/or call default
	CControlBar::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CGuiDockToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
}

CSize CGuiDockToolBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	if (bHorz)
		return CSize(32767,m_Size);
	else
		return CSize(m_Size,32767);
}


