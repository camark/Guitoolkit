// OutputWindow.cpp: implementation of the COutputWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Gui_DevStudio.h"
#include "OutputWindow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COutputWindow::COutputWindow()
{

}

COutputWindow::~COutputWindow()
{

}


BEGIN_MESSAGE_MAP(COutputWindow, CGuiControlBar)
	//{{AFX_MSG_MAP(CMyBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyBar message handlers

int COutputWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndWorkTab.Create(WS_CHILD|WS_VISIBLE,
					CRect(0,0,0,0), this, 124))
		return -1;
	

	
//	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);
	CFont m_Font;
	m_Font.CreateStockObject (DEFAULT_GUI_FONT);
	CRect rectClient (0, 0, lpCreateStruct->cx, lpCreateStruct->cy);

	
	const DWORD dwStyle =  LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	
	m_wndEdit.Create (dwStyle, rectClient, &m_wndWorkTab, 1);
	m_wndDebug.Create (dwStyle, rectClient, &m_wndWorkTab, 2);
	m_wndFind1.Create (dwStyle, rectClient, &m_wndWorkTab, 3);
	m_wndFind2.Create (dwStyle, rectClient, &m_wndWorkTab, 4);
	m_wndResult.Create (dwStyle, rectClient, &m_wndWorkTab, 5);
	m_wndSqlDebug.Create (dwStyle, rectClient, &m_wndWorkTab, 6);
	
	m_wndEdit.SetFont (&m_Font);
	m_wndDebug.SetFont (&m_Font);
	m_wndFind1.SetFont (&m_Font);
	m_wndFind2.SetFont (&m_Font);
	m_wndResult.SetFont (&m_Font);
	m_wndSqlDebug.SetFont (&m_Font);

	m_wndEdit.SetOwner (this);
	m_wndDebug.SetOwner (this);
	m_wndFind1.SetOwner (this);
	m_wndFind2.SetOwner (this);
	m_wndResult.SetOwner (this);
	m_wndSqlDebug.SetOwner (this);
	
	CString str;
	for (int i=0;i < 100;i++)
	{
	str.Format(_T("esta es una cadela laguiswwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiima item string %d"), i);
	m_wndEdit.AddString( str);
	}

	m_wndWorkTab.Addtab (&m_wndEdit, _T("Build"), -1);
	m_wndWorkTab.Addtab (&m_wndDebug, _T("Debug"), -1);
	m_wndWorkTab.Addtab (&m_wndFind1, _T("Find in Files 1"), -1);
	m_wndWorkTab.Addtab (&m_wndFind2, _T("Find in Files 2"), -1);
	m_wndWorkTab.Addtab (&m_wndResult, _T("Results"), -1);
	m_wndWorkTab.Addtab (&m_wndSqlDebug, _T("Sql Debugging"), -1);
	m_wndWorkTab.SetActualTitle(FALSE);
	SetIcon(IDB_BITMAPHELP,16,4,RGB(255,0,0),2);
	return 0;
}


void COutputWindow::OnSize(UINT nType, int cx, int cy) 
{
	CGuiControlBar::OnSize(nType, cx, cy);
	CClientDC dc (this);
	CString strItem;
	m_wndEdit.GetText (90, strItem);
	int cxExtentMax = 0;
	cxExtentMax = dc.GetTextExtent (strItem).cx;
	m_wndEdit.SetHorizontalExtent (cxExtentMax);
	
	// TODO: Add your message handler code here
	
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
	ShowScrollBar (SB_HORZ, FALSE);
	ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);
}

