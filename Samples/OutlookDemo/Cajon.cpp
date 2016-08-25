// Cajon.cpp : implementation file
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "Cajon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCajon

IMPLEMENT_DYNCREATE(CCajon, CListView)

CCajon::CCajon()
{
}

CCajon::~CCajon()
{
}


BEGIN_MESSAGE_MAP(CCajon, CListView)
	//{{AFX_MSG_MAP(CCajon)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCajon drawing

void CCajon::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CCajon diagnostics

#ifdef _DEBUG
void CCajon::AssertValid() const
{
	CListView::AssertValid();
}

void CCajon::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCajon message handlers
