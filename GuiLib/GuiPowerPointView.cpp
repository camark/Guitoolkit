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
#include "GuiLib.h"
#include "GuiPowerPointView.h"
#include "GuiDrawLayer.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CGuiPowerPointView

IMPLEMENT_DYNCREATE(CGuiPowerPointView, CView)

CGuiPowerPointView::CGuiPowerPointView()
{
}

CGuiPowerPointView::~CGuiPowerPointView()
{
}

BEGIN_MESSAGE_MAP(CGuiPowerPointView, CView)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


void CGuiPowerPointView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	m_tbpp.MoveWindow(0,0,cx,cy);

}

int CGuiPowerPointView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_tbpp.Create(WS_VISIBLE|WS_CHILD,
			CRect(0,0,0,0), this, 0))
		return -1;
	m_tbpp.SetColorTabs(GuiDrawLayer::GetRGBColorFace());
	m_tbpp.SetAutoAjust(TRUE);
	m_tbpp.ShowButtonClose(TRUE);
	return 0;
}

// CGuiPowerPointView drawing

void CGuiPowerPointView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CGuiPowerPointView diagnostics

#ifdef _DEBUG
void CGuiPowerPointView::AssertValid() const
{
	CView::AssertValid();
}

void CGuiPowerPointView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CGuiPowerPointView message handlers
