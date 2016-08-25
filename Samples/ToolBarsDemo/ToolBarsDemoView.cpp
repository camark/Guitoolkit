// ToolBarsDemoView.cpp : implementation of the CToolBarsDemoView class
//

#include "stdafx.h"
#include "ToolBarsDemo.h"

#include "ToolBarsDemoDoc.h"
#include "ToolBarsDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoView

IMPLEMENT_DYNCREATE(CToolBarsDemoView, CEditView)

BEGIN_MESSAGE_MAP(CToolBarsDemoView, CEditView)
	//{{AFX_MSG_MAP(CToolBarsDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoView construction/destruction

CToolBarsDemoView::CToolBarsDemoView()
{
	// TODO: add construction code here

}

CToolBarsDemoView::~CToolBarsDemoView()
{
}

BOOL CToolBarsDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
	
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoView drawing

void CToolBarsDemoView::OnDraw(CDC* pDC)
{
	CToolBarsDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CToolBarsDemoView::Message()
{
	AfxMessageBox("dfdfd");
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoView printing

BOOL CToolBarsDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CToolBarsDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CToolBarsDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoView diagnostics

#ifdef _DEBUG
void CToolBarsDemoView::AssertValid() const
{
	CEditView::AssertValid();
}

void CToolBarsDemoView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CToolBarsDemoDoc* CToolBarsDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolBarsDemoDoc)));
	return (CToolBarsDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoView message handlers
