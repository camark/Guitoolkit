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
#include "guiviewworktab.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// CGuiViewWorkTab

IMPLEMENT_DYNCREATE(CGuiViewWorkTab, CView)

CGuiViewWorkTab::CGuiViewWorkTab()
{
}

CGuiViewWorkTab::~CGuiViewWorkTab()
{
}

BEGIN_MESSAGE_MAP(CGuiViewWorkTab, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGuiViewWorkTab drawing

void CGuiViewWorkTab::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CGuiViewWorkTab diagnostics
/*
#ifdef _DEBUG
void CGuiViewWorkTab::AssertValid() const
{
	CView::AssertValid();
}

void CGuiViewWorkTab::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG
*/

// CGuiViewWorkTab message handlers

int CGuiViewWorkTab::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_guiWorktab.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,0x9999))
		return -1;
	// TODO:  Add your specialized creation code here

	return 0;
}

void CGuiViewWorkTab::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	m_guiWorktab.MoveWindow(0,0,cx,cy);

}
