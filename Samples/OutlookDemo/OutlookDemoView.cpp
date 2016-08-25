// OutlookDemoView.cpp : implementation of the COutlookDemoView class
//

#include "stdafx.h"
#include "OutlookDemo.h"

#include "OutlookDemoDoc.h"
#include "OutlookDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoView

IMPLEMENT_DYNCREATE(COutlookDemoView, CView)

BEGIN_MESSAGE_MAP(COutlookDemoView, CView)
	//{{AFX_MSG_MAP(COutlookDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoView construction/destruction

COutlookDemoView::COutlookDemoView()
{
	// TODO: add construction code here

}

COutlookDemoView::~COutlookDemoView()
{
}

BOOL COutlookDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style|=WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoView drawing

void COutlookDemoView::OnDraw(CDC* pDC)
{
	COutlookDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoView printing

BOOL COutlookDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COutlookDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COutlookDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoView diagnostics

#ifdef _DEBUG
void COutlookDemoView::AssertValid() const
{
	CView::AssertValid();
}

void COutlookDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COutlookDemoDoc* COutlookDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COutlookDemoDoc)));
	return (COutlookDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoView message handlers
