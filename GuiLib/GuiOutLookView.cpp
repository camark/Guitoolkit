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
#include "GuiOutLookView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CGuiOutLookView,CView)

CGuiOutLookView::CGuiOutLookView()
{

}

CGuiOutLookView::~CGuiOutLookView()
{

}


BEGIN_MESSAGE_MAP(CGuiOutLookView, CView)
	//{{AFX_MSG_MAP(COutlookBarView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookBarView drawing

void CGuiOutLookView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// COutlookBarView diagnostics

#ifdef _DEBUG
void CGuiOutLookView::AssertValid() const
{
	CView::AssertValid();
}

void CGuiOutLookView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// COutlookBarView message handlers

void CGuiOutLookView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
}

void CGuiOutLookView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	cf.MoveWindow(0,0,cx,cy);

}

int CGuiOutLookView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!cf.Create(WS_VISIBLE|WS_CHILD,
			CRect(0,0,0,0), this, 0))
		return -1;
	return 0;
}


