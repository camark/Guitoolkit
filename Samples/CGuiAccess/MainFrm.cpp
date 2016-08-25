#include "..\gui_devstudio\mainfrm.h"
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CGuiAccess.h"
#include "resource.h"
#include "MainFrm.h"
#include "DialSplitter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define CALLMESSAGE WM_USER+1
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CGuiFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CGuiFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SPLITTERS, OnSplitters)
	ON_COMMAND(ID_PRUEBA1, OnPrueba1)
	ON_COMMAND(ID_PRUEBA2, OnPrueba2)
	//}}AFX_MSG_MAP

	ON_WM_DESTROY()
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
	if (CGuiFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	InitMenu(IDR_MAINFRAME);
	InitToolBar(IDR_MAINFRAME);
	InitStatusBar(indicators,sizeof(indicators)/sizeof(UINT));
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	if (!m_Server.Create(_T("Splitter Demo"),WS_CHILD | WS_VISIBLE, this, 0x996))
    {
        TRACE0("Failed to create m_GuiSolEx\n");
        return -1;      
	}
	
	
	m_Server.SetBarStyle(m_Server.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_Server.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar,m_dockTop);
	DockControlBar(&m_wndToolBar,m_dockTop);
	DockControlBar(&m_Server, AFX_IDW_DOCKBAR_LEFT);
	m_wndStatusBar.SetStyle(CGuiStatusBar::OFFICE);

	GuiDrawLayer::m_Style=GUISTYLE_2003;
	StyleDispl(GUISTYLE_2003);
	m_Server.StyleDispl(GUISTYLE_2003);
	sProfile = _T("GuiDemoOffice");
	//LoadBars();
	menu.LoadMenu(IDR_MENU1);
	/*m_st.Create(this, CALLMESSAGE, "Click here", 
                          AfxGetApp()->LoadIcon(IDR_MAINFRAME), CALLMESSAGE);
	*/m_syst.Create(this,1020,CALLMESSAGE,AfxGetApp()->LoadIcon(IDR_MAINFRAME),_T("Hola"));
	m_syst.SetSysMenu(&menu);
	// TODO: Delete these three lines if you don't want the toolbar to
	
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CGuiFrameWnd::PreCreateWindow(cs) )
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
	CGuiFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CGuiFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
	// TODO: Add your command handler code here


void CMainFrame::OnSplitters() 
{
	// TODO: Add your command handler code here
	CDialSplitter dlg;
	dlg.DoModal();
}

void CMainFrame::OnPrueba1()
{
	AfxMessageBox("Hola");
}

void CMainFrame::OnPrueba2() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("Hola1");
}


