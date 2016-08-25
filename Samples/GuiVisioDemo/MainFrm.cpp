// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GuiVisioDemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_COMBOMENU 5006
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	InitMenu(IDR_MAINFRAME);
	InitToolBar(IDR_MAINFRAME);
	InitStatusBar(indicators,sizeof(indicators)/sizeof(UINT));

	if (!m_OutNormal.Create(_T("ToolBar Visio"),WS_CHILD | WS_VISIBLE, this, 0x995))
    {
        TRACE0("Failed to create m_OutNormal\n");
        return -1;      
	}

	m_OutNormal.SetBarStyle(m_OutNormal.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.SetSaveHistory("HistoryVisio",TRUE);
	m_wndMenuBar.CreateCombo(&m_combMenu,IDC_COMBOMENU,150);
	DockControlBar(&m_wndMenuBar,m_dockTop);
	DockControlBar(&m_wndToolBar,m_dockTop);
	m_OutNormal.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_OutNormal, AFX_IDW_DOCKBAR_LEFT);
	sProfile = _T("GuiVisioDemo");
//	LoadBars();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

