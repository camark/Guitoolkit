// CGuiOfficeDemoView.cpp : implementation of the CCGuiOfficeDemoView class
//

#include "stdafx.h"
#include "CGuiOfficeDemo.h"

#include "CGuiOfficeDemoDoc.h"
#include "CGuiOfficeDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoView

IMPLEMENT_DYNCREATE(CCGuiOfficeDemoView, CView)

BEGIN_MESSAGE_MAP(CCGuiOfficeDemoView, CView)
	//{{AFX_MSG_MAP(CCGuiOfficeDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoView construction/destruction

CCGuiOfficeDemoView::CCGuiOfficeDemoView()
{
	// TODO: add construction code here

}

CCGuiOfficeDemoView::~CCGuiOfficeDemoView()
{
}

BOOL CCGuiOfficeDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoView drawing

void CCGuiOfficeDemoView::OnDraw(CDC* pDC)
{
	CCGuiOfficeDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoView printing

BOOL CCGuiOfficeDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGuiOfficeDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGuiOfficeDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoView diagnostics

#ifdef _DEBUG
void CCGuiOfficeDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CCGuiOfficeDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGuiOfficeDemoDoc* CCGuiOfficeDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGuiOfficeDemoDoc)));
	return (CCGuiOfficeDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoView message handlers
