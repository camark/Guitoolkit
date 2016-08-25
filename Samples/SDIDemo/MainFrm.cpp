// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SDIDemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CGuiFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CGuiFrameWnd)
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
	if (CGuiFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	InitMenu(IDR_MAINFRAME);
	InitToolBar(IDR_MAINFRAME);
	InitStatusBar(indicators,sizeof(indicators)/sizeof(UINT));
	
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);	
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	if (!m_Server.Create(_T("Server Explorer"),WS_CHILD | WS_VISIBLE, this, 0x996))
    {
        TRACE0("Failed to create m_GuiSolEx\n");
        return -1;      
	}
	
	
	
	m_Server.SetBarStyle(m_Server.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_Server.EnableDocking(CBRS_ALIGN_ANY);	
	DockControlBar(&m_Server, AFX_IDW_DOCKBAR_LEFT);


	DockControlBar(&m_wndMenuBar,m_dockTop);
	DockControlBar(&m_wndToolBar,m_dockTop);
	GuiDrawLayer::m_Style=GUISTYLE_XP;
	StyleDispl(GUISTYLE_XP);
	m_Server.StyleDispl(GUISTYLE_XP);
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

