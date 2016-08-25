// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CGuiTabbedDemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define IDC_COMBOMENU WM_USER+1

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_WM_TIMER()
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
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitMenu(IDR_MAINFRAME);
	InitToolBar(IDR_MAINFRAME);
	InitStatusBar(indicators,sizeof(indicators)/sizeof(UINT));
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.SetSaveHistory("MyHistory1",TRUE);
	m_wndMenuBar.CreateCombo(&m_combMenu,IDC_COMBOMENU,150);
	
	DockControlBar(&m_wndMenuBar,m_dockTop);
	DockControlBar(&m_wndToolBar,m_dockTop);
	m_wndStatusBar.SetStyle(CGuiStatusBar::OFFICE);
	
	DockControlBar(&m_wndToolBar);
	sProfile = _T("GuiTabbedDemo");
	LoadBars();
	InitMDITabbed();
	m_MdiTabbed.SetTabsMenu(IDR_MENUTABS);
	SetTimer(1,150,0);	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
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


void CMainFrame::OnFilePrintPreview() 
{
	// TODO: Add your command handler code here
	
	AfxMessageBox("hola");
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	StyleDispl(GUISTYLE_2003);
	KillTimer(nIDEvent);
	CMDIFrameWnd::OnTimer(nIDEvent);
}
