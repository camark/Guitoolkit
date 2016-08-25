#include "..\gui_devstudio\mainfrm.h"
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CGuiOfficeDemo.h"
#include "resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_COMBOMENU 5338
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CGuiMDIFrame)

BEGIN_MESSAGE_MAP(CMainFrame, CGuiMDIFrame)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_OFFICEBAR, OnViewOfficebar)
	ON_COMMAND(IDC_COMBOMENU, OnComboMenu)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_OFFICEBAR, OnOfficebar)
	ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolbar)
	
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

void CMainFrame::OnComboMenu()
{
	AfxMessageBox("Enter menu");
}

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiMDIFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitMenu(IDR_MAINFRAME);
	InitToolBar(IDR_MAINFRAME);
	InitStatusBar(indicators,sizeof(indicators)/sizeof(UINT));
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	if(!m_OfficeBar.Create(_T("Office Panel"),WS_CHILD | WS_VISIBLE, this, 125))
    {
        TRACE0("Failed to create mybar\n");
        return -1;      // fail to create
	}

	
	m_OfficeBar.SetBarStyle(m_OfficeBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.SetSaveHistory("MyHistory1",TRUE);
	m_wndMenuBar.CreateCombo(&m_combMenu,IDC_COMBOMENU,150);
	m_OfficeBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar,m_dockTop);
	DockControlBar(&m_wndToolBar,m_dockTop);
	DockControlBar(&m_OfficeBar,AFX_IDW_DOCKBAR_LEFT);
	DockControlBar(&m_wndToolBar);
	sProfile = _T("GuiDemoOffice");

	LoadBars();


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CGuiMDIFrame::PreCreateWindow(cs) )
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
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnOfficebar()
{
	
}

void CMainFrame::OnViewToolbar()
{
	ShowHideBar(&m_wndToolBar);
}

void CMainFrame::OnViewOfficebar() 
{
	ShowHideBar(&m_OfficeBar);
	
}


