// CGuiAccessView.cpp : implementation of the CCGuiAccessView class
//

#include "stdafx.h"
#include "CGuiAccess.h"

#include "CGuiAccessDoc.h"
#include "CGuiAccessView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessView

IMPLEMENT_DYNCREATE(CCGuiAccessView, CView)

BEGIN_MESSAGE_MAP(CCGuiAccessView, CView)
	//{{AFX_MSG_MAP(CCGuiAccessView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessView construction/destruction

CCGuiAccessView::CCGuiAccessView()
{
	// TODO: add construction code here

}

CCGuiAccessView::~CCGuiAccessView()
{
}

BOOL CCGuiAccessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessView drawing

void CCGuiAccessView::OnDraw(CDC* pDC)
{
	CCGuiAccessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessView printing

BOOL CCGuiAccessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGuiAccessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGuiAccessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessView diagnostics

#ifdef _DEBUG
void CCGuiAccessView::AssertValid() const
{
	CView::AssertValid();
}

void CCGuiAccessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGuiAccessDoc* CCGuiAccessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGuiAccessDoc)));
	return (CCGuiAccessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessView message handlers
