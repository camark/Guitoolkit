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
 * Created by: Ernesto Garcia.												*
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

#include "stdafx.h"
#include "GuiView.h"
#include "newmenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiView

IMPLEMENT_DYNCREATE(CGuiView, CView)

CGuiView::CGuiView()
{
}

CGuiView::~CGuiView()
{
}


BEGIN_MESSAGE_MAP(CGuiView, CView)
	//{{AFX_MSG_MAP(CGuiView)
	ON_WM_INITMENUPOPUP()
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiView drawing

void CGuiView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CGuiView diagnostics

#ifdef _DEBUG
void CGuiView::AssertValid() const
{
	CView::AssertValid();
}

void CGuiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGuiView message handlers

void CGuiView::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
    CView::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
    CNewMenu::OnInitMenuPopup(m_hWnd,pPopupMenu, nIndex, bSysMenu);
}

void CGuiView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
    if(!CNewMenu::OnMeasureItem(GetCurrentMessage()))
    {
      CView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
    }
}


LRESULT CGuiView::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
    LRESULT lresult;
    if( DYNAMIC_DOWNCAST(CNewMenu,pMenu) )
      lresult=CNewMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
    else
      lresult=CView::OnMenuChar(nChar, nFlags, pMenu);
    return lresult;
}
