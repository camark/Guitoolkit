// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CGuiPowerPoint.h"

#include "MainFrm.h"
#include "GuiPowerp.h"
#include "GuiView.h"
#include "GuiEdit.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_COMBOMENU 0x3655
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EMAIL, OnEmail)
	ON_COMMAND(ID_ORTOGRAFIA, OnOrtografia)
	ON_COMMAND(ID_PREVIEW, OnPreview)
	ON_COMMAND(ID_BUSCAR, OnBuscar)
	ON_COMMAND(ID_GRAFICO, OnGrafico)
	ON_COMMAND(ID_BACK, OnBack)
	ON_COMMAND(ID_FORWARD, OnForward)
	ON_COMMAND(ID_TABLA, OnTabla)
	ON_COMMAND(ID_GRISES, OnGrises)
	ON_COMMAND(ID_HELP, OnHelp)
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
	if(!m_OfficeBar.Create(_T("Office Panel"),WS_CHILD | WS_VISIBLE, this, 125))
    {
        TRACE0("Failed to create mybar\n");
        return -1;      // fail to create
	}
	if(!m_tb.Create(_T("Panel de Revisiones"),WS_CHILD | WS_VISIBLE, this, 125))
    {
        TRACE0("Failed to create mybar\n");
        return -1;      // fail to create
	}

	m_tb.SetBarStyle(m_tb.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_OfficeBar.SetBarStyle(m_OfficeBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	
	m_wndMenuBar.SetSaveHistory("MyHistory1",TRUE);
	m_wndMenuBar.CreateCombo(&m_combMenu,IDC_COMBOMENU,150);
	
	CFont m_Font;
	m_Font.CreateStockObject (DEFAULT_GUI_FONT);
	
	m_wndToolBar.CreateCombo(&m_comboZoom,ID_COMBOBOX,80);
	m_comboZoom.AddString("400%");
	m_comboZoom.AddString("300%");
	m_comboZoom.AddString("200%");
	m_comboZoom.AddString("150%");
	m_comboZoom.AddString("100%");
	m_comboZoom.AddString("85%");
	m_comboZoom.SetFont (&m_Font);
	

	m_tb.EnableDocking(CBRS_ALIGN_ANY);
	m_OfficeBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);	
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar,m_dockTop);
	DockControlBar(&m_wndToolBar,m_dockTop);
	DockControlBar(&m_tb,AFX_IDW_DOCKBAR_RIGHT);
	DockControlBar(&m_OfficeBar,AFX_IDW_DOCKBAR_RIGHT);
	sProfile = _T("DevStudio");
	LoadBars();
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



void CMainFrame::OnEmail() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnOrtografia() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnPreview() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnBuscar() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnGrafico() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnBack() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnForward() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnTabla() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnGrises() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnHelp() 
{
	// TODO: Add your command handler code here
	
}
