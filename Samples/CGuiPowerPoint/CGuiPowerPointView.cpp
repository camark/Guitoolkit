// CGuiPowerPointView.cpp : implementation of the CCGuiPowerPointView class
//

#include "stdafx.h"
#include "CGuiPowerPoint.h"

#include "CGuiPowerPointDoc.h"
#include "CGuiPowerPointView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointView

IMPLEMENT_DYNCREATE(CCGuiPowerPointView, CView)

BEGIN_MESSAGE_MAP(CCGuiPowerPointView, CView)
	//{{AFX_MSG_MAP(CCGuiPowerPointView)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointView construction/destruction

CCGuiPowerPointView::CCGuiPowerPointView()
{
	// TODO: add construction code here

}

CCGuiPowerPointView::~CCGuiPowerPointView()
{
}

BOOL CCGuiPowerPointView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointView drawing

void CCGuiPowerPointView::OnDraw(CDC* pDC)
{
	CCGuiPowerPointDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointView printing

BOOL CCGuiPowerPointView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGuiPowerPointView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGuiPowerPointView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointView diagnostics

#ifdef _DEBUG
void CCGuiPowerPointView::AssertValid() const
{
	CView::AssertValid();
}

void CCGuiPowerPointView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGuiPowerPointDoc* CCGuiPowerPointView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGuiPowerPointDoc)));
	return (CCGuiPowerPointDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointView message handlers

void CCGuiPowerPointView::OnFilePrintPreview() 
{
	// TODO: Add your command handler code here
	CView::OnFilePrintPreview();
}
