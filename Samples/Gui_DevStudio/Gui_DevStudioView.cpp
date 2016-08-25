// Gui_DevStudioView.cpp : implementation of the CGui_DevStudioView class
//

#include "stdafx.h"
#include "Gui_DevStudio.h"

#include "Gui_DevStudioDoc.h"
#include "Gui_DevStudioView.h"
#include "NewMenu.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioView

IMPLEMENT_DYNCREATE(CGui_DevStudioView, CEditView)

BEGIN_MESSAGE_MAP(CGui_DevStudioView, CEditView)
	//{{AFX_MSG_MAP(CGui_DevStudioView)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioView construction/destruction

CGui_DevStudioView::CGui_DevStudioView()
{
	// TODO: add construction code here

}

CGui_DevStudioView::~CGui_DevStudioView()
{
}

BOOL CGui_DevStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioView drawing

void CGui_DevStudioView::OnDraw(CDC* pDC)
{
	CGui_DevStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioView printing

BOOL CGui_DevStudioView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CGui_DevStudioView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CGui_DevStudioView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioView diagnostics

#ifdef _DEBUG
/*void CGui_DevStudioView::AssertValid() const
{
	CEditView::AssertValid();
}

void CGui_DevStudioView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
*/
CGui_DevStudioDoc* CGui_DevStudioView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGui_DevStudioDoc)));
	return (CGui_DevStudioDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioView message handlers
static CString GetShort(UINT id)
{
	CString str;
	str.LoadString(id);
	int nIndex = str.ReverseFind(_T('\n'));
	if(nIndex!=-1)
	{
		str=str.Mid(nIndex+1);
	}
	return str;
}


void CGui_DevStudioView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	if(point.x==-1 && point.y==-1)
	{
		CRect rect;
		GetWindowRect(rect);

		point = rect.TopLeft()+CPoint(10,10);
	}
	SetFocus();

	CMenu menu;
	menu.CreatePopupMenu();
	menu.InsertMenu(0, MF_BYPOSITION , ID_EDIT_UNDO, GetShort(ID_EDIT_UNDO));
	menu.InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(2, MF_BYPOSITION , ID_EDIT_COPY, GetShort(ID_EDIT_COPY));
	menu.InsertMenu(2, MF_BYPOSITION , ID_EDIT_CUT, GetShort(ID_EDIT_CUT));
	menu.InsertMenu(4, MF_BYPOSITION , ID_EDIT_CLEAR, GetShort(ID_EDIT_CLEAR));
	menu.InsertMenu(5, MF_BYPOSITION , ID_EDIT_PASTE, GetShort(ID_EDIT_PASTE));
	menu.InsertMenu(6, MF_BYPOSITION|MF_SEPARATOR);

	menu.InsertMenu(7, MF_BYPOSITION , ID_EDIT_SELECT_ALL,GetShort(ID_EDIT_SELECT_ALL));

//	menu.SetMenuTitle(_T("Edit commands"),MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);
	//menu.Lo.LoadToolBar(IDR_MAINFRAME);

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
}
