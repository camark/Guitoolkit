// SDIDemoView.cpp : implementation of the CSDIDemoView class
//

#include "stdafx.h"
#include "SDIDemo.h"

#include "SDIDemoDoc.h"
#include "SDIDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoView

IMPLEMENT_DYNCREATE(CSDIDemoView, CView)

BEGIN_MESSAGE_MAP(CSDIDemoView, CView)
	//{{AFX_MSG_MAP(CSDIDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoView construction/destruction

CSDIDemoView::CSDIDemoView()
{
	// TODO: add construction code here

}

CSDIDemoView::~CSDIDemoView()
{
}

BOOL CSDIDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoView drawing

void CSDIDemoView::OnDraw(CDC* pDC)
{
	CSDIDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoView printing

BOOL CSDIDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSDIDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSDIDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoView diagnostics

#ifdef _DEBUG
void CSDIDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIDemoDoc* CSDIDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIDemoDoc)));
	return (CSDIDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoView message handlers
