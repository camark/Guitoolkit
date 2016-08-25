// CGuiFlatTabbedViewView.cpp : implementation of the CCGuiFlatTabbedViewView class
//

#include "stdafx.h"
#include "CGuiFlatTabbedView.h"

#include "CGuiFlatTabbedViewDoc.h"
#include "CGuiFlatTabbedViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGuiFlatTabbedViewView

IMPLEMENT_DYNCREATE(CCGuiFlatTabbedViewView, CGuiViewWorkTab)

BEGIN_MESSAGE_MAP(CCGuiFlatTabbedViewView, CGuiViewWorkTab)
	//{{AFX_MSG_MAP(CCGuiFlatTabbedViewView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CGuiViewWorkTab::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CGuiViewWorkTab::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGuiViewWorkTab::OnFilePrintPreview)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGuiFlatTabbedViewView construction/destruction

CCGuiFlatTabbedViewView::CCGuiFlatTabbedViewView()
{
	// TODO: add construction code here

}

CCGuiFlatTabbedViewView::~CCGuiFlatTabbedViewView()
{
}

BOOL CCGuiFlatTabbedViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CGuiViewWorkTab::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiFlatTabbedViewView drawing

void CCGuiFlatTabbedViewView::OnDraw(CDC* pDC)
{
	CCGuiFlatTabbedViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiFlatTabbedViewView printing

BOOL CCGuiFlatTabbedViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGuiFlatTabbedViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGuiFlatTabbedViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCGuiFlatTabbedViewView diagnostics

#ifdef _DEBUG
void CCGuiFlatTabbedViewView::AssertValid() const
{
	CGuiViewWorkTab::AssertValid();
}

void CCGuiFlatTabbedViewView::Dump(CDumpContext& dc) const
{
	CGuiViewWorkTab::Dump(dc);
}

CCGuiFlatTabbedViewDoc* CCGuiFlatTabbedViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGuiFlatTabbedViewDoc)));
	return (CCGuiFlatTabbedViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGuiFlatTabbedViewView message handlers



CListct::CListct()
{
}

CListct::~CListct()
{
}


BEGIN_MESSAGE_MAP(CListct, CListCtrl)
	//{{AFX_MSG_MAP(COutputList)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputList message handlers

void CListct::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	CListCtrl::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:

	ShowScrollBar (SB_HORZ, FALSE);
	ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);
	
}


COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}


BEGIN_MESSAGE_MAP(COutputList, CListBox)
	//{{AFX_MSG_MAP(COutputList)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputList message handlers

void COutputList::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	CListBox::OnWindowPosChanging(lpwndpos);

	// Hide horizontal scrollbar:

//	ShowScrollBar (SB_HORZ, FALSE);
//	ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);
	
}


int CCGuiFlatTabbedViewView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CGuiViewWorkTab::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	CFont m_Font;
	m_Font.CreateStockObject (DEFAULT_GUI_FONT);
	CRect rectClient (0, 0, lpCreateStruct->cx, lpCreateStruct->cy);
	
	const DWORD dwStyle =  LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	
	m_list.Create(
   WS_CHILD|WS_VISIBLE|LVS_REPORT,
   CRect(0,0,0,0), &m_guiWorktab, 2);
	m_wndEdit.Create (dwStyle, rectClient, &m_guiWorktab, 1);
	
	m_wndFind1.Create (dwStyle, rectClient, &m_guiWorktab, 3);
	m_wndFind2.Create (dwStyle, rectClient, &m_guiWorktab, 4);
	m_wndResult.Create (dwStyle, rectClient, &m_guiWorktab, 5);
	m_wndSqlDebug.Create (dwStyle, rectClient, &m_guiWorktab, 6);
	
	m_wndEdit.SetFont (&m_Font);
	m_wndFind1.SetFont (&m_Font);
	m_wndFind2.SetFont (&m_Font);
	m_wndResult.SetFont (&m_Font);
	m_wndSqlDebug.SetFont (&m_Font);

/*	m_wndEdit.SetOwner (this);
	m_wndFind1.SetOwner (this);
	m_wndFind2.SetOwner (this);
	m_wndResult.SetOwner (this);
	m_wndSqlDebug.SetOwner (this);
*/	//----------------------------------------------
	
	CString str;
	for (int i=0;i < 100;i++)
	{
	str.Format(_T("Item No:%d this is a laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaarge streamcccccc"), i);
	m_wndEdit.AddString( str);
	}
	//-----------------------------------------------
	
	CRect rect;
	m_list.GetClientRect(&rect);
	int nInterval = rect.Width()/5;
	
	// Create the columns
	// Put 10 items in the list
	LV_ITEM lvi;
	TCHAR szItem[256];
	TCHAR szCol[256];
	lvi.mask = LVIF_TEXT;
	for ( i=0; i  < 20; i++)
	{

		_stprintf(szCol, _T("Column %d"), i);
		m_list.InsertColumn(0, szCol, LVCFMT_LEFT,80);
		lvi.iItem = 0;
		lvi.iSubItem = 0;
		_stprintf(szItem, _T("Option %d"), i);
		lvi.pszText = szItem;
		m_list.InsertItem(&lvi);
		for (int j=1; j  < 20; j++)
		{
			
			lvi.iSubItem = j;
			strcpy(szItem,"My List");
			m_list.SetItem(&lvi);
		}
	}
	
	ListView_SetExtendedListViewStyleEx(m_list.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);



	//------------------------------------------------
		
	m_guiWorktab.Addtab (&m_wndEdit, _T("Build"), -1);
	m_guiWorktab.Addtab (&m_list, _T("CLisCtrl"), -1);
	m_guiWorktab.Addtab (&m_wndFind1, _T("Find in Files 1"), -1);
	m_guiWorktab.Addtab (&m_wndFind2, _T("Find in Files 2"), -1);
	m_guiWorktab.Addtab (&m_wndResult, _T("Results"), -1);
	m_guiWorktab.Addtab (&m_wndSqlDebug, _T("Sql Debugging"), -1);
	m_guiWorktab.SetActualTitle(FALSE);

	// TODO: Add your specialized creation code here
	
	return 0;
}

void CCGuiFlatTabbedViewView::OnSize(UINT nType, int cx, int cy) 
{
	CGuiViewWorkTab::OnSize(nType, cx, cy);
	CClientDC dc (this);
	CString strItem;
	m_wndEdit.GetText (90, strItem);
	int cxExtentMax = 0;
	cxExtentMax = dc.GetTextExtent (strItem).cx;
	m_wndEdit.SetHorizontalExtent (cxExtentMax);
	
	// TODO: Add your message handler code here
	
}

void CCGuiFlatTabbedViewView::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CGuiViewWorkTab::OnWindowPosChanging(lpwndpos);
	
//	m_wndEdit.ShowScrollBar (SB_HORZ, FALSE);
//	m_wndEdit.ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);
	m_list.ShowScrollBar (SB_HORZ, FALSE);
	m_list.ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);
	m_wndFind1.ShowScrollBar (SB_HORZ, FALSE);
	m_wndFind1.ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);

	m_wndFind2.ShowScrollBar (SB_HORZ, FALSE);
	m_wndFind2.ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);

	m_wndResult.ShowScrollBar (SB_HORZ, FALSE);
	m_wndResult.ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);

	m_wndSqlDebug.ShowScrollBar (SB_HORZ, FALSE);
	m_wndSqlDebug.ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);
	// TODO: Add your message handler code here
}
