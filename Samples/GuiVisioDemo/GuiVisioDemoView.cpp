// GuiVisioDemoView.cpp : implementation of the CGuiVisioDemoView class
//

#include "stdafx.h"
#include "GuiVisioDemo.h"

#include "GuiVisioDemoDoc.h"
#include "GuiVisioDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiVisioDemoView

IMPLEMENT_DYNCREATE(CGuiVisioDemoView, CView)

BEGIN_MESSAGE_MAP(CGuiVisioDemoView, CView)
	//{{AFX_MSG_MAP(CGuiVisioDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiVisioDemoView construction/destruction

CGuiVisioDemoView::CGuiVisioDemoView()
{
	// TODO: add construction code here

}

CGuiVisioDemoView::~CGuiVisioDemoView()
{
}

BOOL CGuiVisioDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGuiVisioDemoView drawing

void CGuiVisioDemoView::OnDraw(CDC* pDC)
{
	CGuiVisioDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGuiVisioDemoView printing

BOOL CGuiVisioDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGuiVisioDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGuiVisioDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGuiVisioDemoView diagnostics

#ifdef _DEBUG
void CGuiVisioDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CGuiVisioDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGuiVisioDemoDoc* CGuiVisioDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGuiVisioDemoDoc)));
	return (CGuiVisioDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGuiVisioDemoView message handlers
