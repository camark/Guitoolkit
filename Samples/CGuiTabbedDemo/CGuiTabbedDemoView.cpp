// CGuiTabbedDemoView.cpp : implementation of the CCGuiTabbedDemoView class
//

#include "stdafx.h"
#include "CGuiTabbedDemo.h"

#include "CGuiTabbedDemoDoc.h"
#include "CGuiTabbedDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoView

IMPLEMENT_DYNCREATE(CCGuiTabbedDemoView, CView)

BEGIN_MESSAGE_MAP(CCGuiTabbedDemoView, CView)
	//{{AFX_MSG_MAP(CCGuiTabbedDemoView)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoView construction/destruction

CCGuiTabbedDemoView::CCGuiTabbedDemoView()
{
	// TODO: add construction code here

}

CCGuiTabbedDemoView::~CCGuiTabbedDemoView()
{
}

BOOL CCGuiTabbedDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoView drawing

void CCGuiTabbedDemoView::OnDraw(CDC* pDC)
{
	CCGuiTabbedDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoView printing

BOOL CCGuiTabbedDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGuiTabbedDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGuiTabbedDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoView diagnostics

#ifdef _DEBUG
void CCGuiTabbedDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CCGuiTabbedDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGuiTabbedDemoDoc* CCGuiTabbedDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGuiTabbedDemoDoc)));
	return (CCGuiTabbedDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoView message handlers

void CCGuiTabbedDemoView::OnFilePrintPreview() 
{
	// TODO: Add your command handler code here
	CMDIFrameWnd* pParent = STATIC_DOWNCAST(CMDIFrameWnd, AfxGetMainWnd());
	ASSERT_VALID(pParent);
	
	pParent->SendMessage(ID_FILE_PRINT_PREVIEW);
	CView::OnFilePrintPreview();
}
