// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"
#include "Gui_DevStudio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CGuiMDIFrame)

BEGIN_MESSAGE_MAP(CMainFrame, CGuiMDIFrame)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolbar)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_LOOK_2003, OnViewLook2003)
	ON_COMMAND(ID_VIEW_LOOK_XP, OnViewLookXp)
	ON_COMMAND(ID_NEW_ITEM, OnNewItem)
	ON_COMMAND(ID_UNDO, OnUndo)
	ON_COMMAND(ID_REDO, OnRedo)
	ON_COMMAND(ID_NAVIBACK, NaviBack)
	ON_COMMAND(ID_START, Start)
	ON_COMMAND(ID_FINDINFILES, FinFiles)
	ON_COMMAND(ID_SOLUTION, Solution)
	ON_COMMAND(ID_EXISTITEM,OnExistItem)
	ON_COMMAND(ID_ADDCLASS,OnAddClass)
	ON_COMMAND(ID_CLASSVIEW,OnClassView)
	ON_COMMAND(ID_SERVER,OnServer)
	ON_COMMAND(ID_HELP,OnHelp)
	ON_COMMAND(ID_OUTPUTNORMAL,OnOutputNormal)
	ON_COMMAND(ID_OUTPUT,OnOutput)
	ON_COMMAND(ID_WORKSPACE,OnWorkSpace)
	ON_WM_SPOOLERSTATUS()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static UINT Toolbars[] = {
	IDR_MAINFRAME,
	IDR_TOOLBARS,
	IDR_NEWITEM
	
};
static UINT ToolCombos[] = {
	ID_COMBO1,
	ID_COMBO2,
	ID_COMBO3
	
};
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
//toolbars
void CMainFrame::OnNewItem()
{

}

void CMainFrame::OnUndo()
{
}
void CMainFrame::OnExistItem(){}
void CMainFrame::OnAddClass(){}

void CMainFrame::OnRedo(){}
void CMainFrame::NaviBack(){}
void CMainFrame::Start(){}
void CMainFrame::FinFiles(){}
void CMainFrame::Solution(){}
void CMainFrame::OnClassView()
{

}
void CMainFrame::OnServer()
{
	ShowHideBar(&m_Server);
}
void CMainFrame::OnHelp()
{
	ShowHideBar(&m_GuiHelp);
}
void CMainFrame::OnOutputNormal()
{
	ShowHideBar(&m_OutNormal);
}
void CMainFrame::OnOutput()
{
	ShowHideBar(&m_OutPut);
}
void CMainFrame::OnWorkSpace()
{
	ShowHideBar(&m_GuiSolEx);
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
	m_wndToolBar.SetWindowText("ToolBar");
	
	if (!m_ToolCombos.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_TOOLCOMBOS) ||
		!m_ToolCombos.LoadToolBar(IDR_TOOLCOMBOS))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_GuiSolEx.Create(_T("Workspace"),WS_CHILD | WS_VISIBLE, this, 0x999))
    {
        TRACE0("Failed to create m_GuiSolEx\n");
        return -1;      
	}

	if (!m_GuiHelp.Create(_T("Help"),WS_CHILD | WS_VISIBLE, this, 0x998))
    {
        TRACE0("Failed to create m_GuiSolEx\n");
        return -1;     
	}

	if (!m_OutPut.Create(_T("OutPut"),WS_CHILD | WS_VISIBLE, this, 0x997))
    {
        TRACE0("Failed to create m_GuiSolEx\n");
        return -1;      
	}

	if (!m_Server.Create(_T("Server Explorer"),WS_CHILD | WS_VISIBLE, this, 0x996))
    {
        TRACE0("Failed to create m_GuiSolEx\n");
        return -1;      
	}
	
	if (!m_OutNormal.Create(_T("Output Normal"),WS_CHILD | WS_VISIBLE, this, 0x995))
    {
        TRACE0("Failed to create m_GuiSolEx\n");
        return -1;      
	}

	m_GuiSolEx.SetBarStyle(m_GuiSolEx.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_GuiHelp.SetBarStyle(m_GuiHelp.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_OutPut.SetBarStyle(m_OutPut.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
	m_Server.SetBarStyle(m_Server.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_OutNormal.SetBarStyle(m_OutNormal.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	
	const DWORD dwStyle =  LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL ;
	
	m_tree.Create (dwStyle, CRect(0,0,100,100), this, 1);


	
	m_tree.ShowWindow(SW_HIDE);
	CString str;
	for (int i=0;i < 100;i++)
	{
	str.Format(_T("esta es una cadena larga %d"), i);
	m_tree.AddString( str);
	}




	m_wndToolBar.SetButtonDropDown(ID_FILE_NEW,0,IDR_MENUNEW);
	m_wndToolBar.SetButtonDropDown(ID_NEW_ITEM,1,IDR_MENUNEWITEM);
	m_wndToolBar.SetButtonDropDown(ID_UNDO,8,&m_tree,_T("Prueba"));
	m_wndToolBar.SetButtonDropDown(ID_REDO,9,IDR_MENUNEW);
	m_wndToolBar.SetButtonDropDown(ID_CLASSVIEW,14,IDR_MENUTOOLBARS);
	m_wndToolBar.SetMenuContext(IDR_MENUTOOLBARS);
//	CreateCombos();
	m_ToolCombos.CreateCombo(&m_comboDebug,ID_COMBO1,150,WS_CHILD|WS_VISIBLE|CBS_DROPDOWN  | 
							WS_VSCROLL | CBS_HASSTRINGS |CBS_OWNERDRAWVARIABLE);
	m_ToolCombos.CreateCombo(&m_combo2,ID_COMBO2,150);
	CFont m_Font;
	m_Font.CreateStockObject (DEFAULT_GUI_FONT);
	m_comboDebug.SetFont (&m_Font);	
	m_combo2.AddString("m_TreeClassView.");
	m_combo2.AddString("m_TreeSolExplorer.");
	m_combo2.AddString("m_FileView->");
	m_combo2.SetFont (&m_Font);
	EnableDocking(CBRS_ALIGN_ANY);
	
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_ToolCombos.EnableDocking(CBRS_ALIGN_ANY);
	m_GuiSolEx.EnableDocking(CBRS_ALIGN_ANY);
	m_GuiHelp.EnableDocking(CBRS_ALIGN_ANY);
	m_OutPut.EnableDocking(CBRS_ALIGN_ANY);
	m_Server.EnableDocking(CBRS_ALIGN_ANY);
	m_OutNormal.EnableDocking(CBRS_ALIGN_ANY);

	m_GuiSolEx.SetMenuContext(IDR_MENUTOOLBARS);
	m_Server.SetMenuContext(IDR_MENUTOOLBARS);
	m_GuiHelp.SetMenuContext(IDR_MENUTOOLBARS);
	m_OutPut.SetMenuContext(IDR_MENUTOOLBARS);
	m_wndMenuBar.SetMenuContext(IDR_MENUTOOLBARS);

	DockControlBar(&m_wndMenuBar,m_dockTop);
	DockControlBar(&m_wndToolBar,m_dockLeft);
	DockControlBar(&m_ToolCombos,m_dockTop);
	DockControlBar(&m_GuiSolEx, AFX_IDW_DOCKBAR_RIGHT);
	DockControlBar(&m_GuiHelp, AFX_IDW_DOCKBAR_LEFT);
	DockControlBar(&m_OutPut, AFX_IDW_DOCKBAR_BOTTOM);
	DockControlBar(&m_Server, AFX_IDW_DOCKBAR_LEFT);
	DockControlBar(&m_OutNormal, AFX_IDW_DOCKBAR_BOTTOM);
	
	sProfile = _T("Gui_DevStudio");
	LoadBars();
	InitMDITabbed();
	m_MdiTabbed.SetTabsMenu(IDR_MENUTABS);
	
	#define _countof(array) (sizeof(array)/sizeof(array[0]))
	m_wndCool.LoadToolbars(Toolbars, _countof(Toolbars));
	
	RecalcLayout();
	m_MdiTabbed.SetTabMenu(0,0);
	if(m_StyleDisplay== GUISTYLE_2003)
		OnViewLook2003();
	else
		OnViewLookXp();
	return 0;
}



void CMainFrame::CreateCombos()
{

	CFont m_Font;
	m_Font.CreateStockObject (DEFAULT_GUI_FONT);
	
	m_wndToolBar.CreateCombo(&m_comboDebug,ID_COMBODEBUG,150,WS_CHILD|WS_VISIBLE|CBS_DROPDOWN  | 
                    WS_VSCROLL | WS_TABSTOP | CBS_HASSTRINGS |CBS_OWNERDRAWFIXED );
	/*m_comboDebug.AddString("Debug");
	m_comboDebug.AddString("Release");
	m_comboDebug.AddString("Configuration Manager...");
	m_comboDebug.SetFont (&m_Font);*/
	//m_comboDebug.EnableWindow(FALSE);     
	m_wndToolBar.CreateCombo(&m_comboFind,ID_COMBOFIND,200);
	m_comboFind.AddString("m_TreeClassView.");
	m_comboFind.AddString("m_TreeSolExplorer.");
	m_comboFind.AddString("m_FileView->");
	m_comboFind.SetFont (&m_Font);
//	m_comboFind.EnableWindow(FALSE);

	
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
	CGuiMDIFrame::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CGuiMDIFrame::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CGuiMDIFrame::OnSize(nType, cx, cy);
//	m_MdiTabbed::OnSize((nType, cx, cy);
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnViewToolbar() 
{
	// TODO: Add your command handler code here
	ShowHideBar(&m_wndToolBar);
}

void CMainFrame::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck();
	
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CGuiMDIFrame::OnClose();
}

void CMainFrame::OnWindowCascade()
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnViewLook2003() 
{
	// TODO: Add your command handler code here


	GuiDrawLayer::m_Style=GUISTYLE_2003;
	StyleDispl(GUISTYLE_2003);
	m_GuiSolEx.StyleDispl(GUISTYLE_2003);
	m_GuiHelp.StyleDispl(GUISTYLE_2003);
	m_OutPut.StyleDispl(GUISTYLE_2003);	
	m_Server.StyleDispl(GUISTYLE_2003);
	m_OutNormal.StyleDispl(GUISTYLE_2003);
	m_ToolCombos.StyleDispl(GUISTYLE_2003);
	m_OutPut.StyleDispl(GUISTYLE_2003);
	

	
}

void CMainFrame::OnViewLookXp() 
{
	// TODO: Add your command handler code here
	GuiDrawLayer::m_Style=GUISTYLE_XP;
	GuiDrawLayer::m_Theme=0;
	m_GuiSolEx.StyleDispl();
	m_GuiHelp.StyleDispl();
	m_OutPut.StyleDispl();	
	m_Server.StyleDispl();
	m_OutNormal.StyleDispl();
	m_ToolCombos.StyleDispl();
	StyleDispl();
	RecalcLayout();
	Invalidate();
	UpdateWindow();
}

void CMainFrame::OnSpoolerStatus(UINT nStatus, UINT nJobs) 
{
	CGuiMDIFrame::OnSpoolerStatus(nStatus, nJobs);
	
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnSysColorChange() 
{
	CGuiMDIFrame::OnSysColorChange();
	GuiDrawLayer::IsThemeXP();
	// TODO: Add your message handler code here
	
}
