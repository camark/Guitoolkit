#include "StdAfx.h"
#include "guisolexplorer.h"
#include "resource.h"

#define ID_PROPERTIES 0x332
//#define ID_CLASSVIEW  0x333
#define ID_NEWFOLDER  0x334

CGuiSolExplorer::CGuiSolExplorer(void)
{
}

CGuiSolExplorer::~CGuiSolExplorer(void)
{
}
BEGIN_MESSAGE_MAP(CGuiSolExplorer, CGuiControlBar)
	ON_WM_CREATE()
	ON_COMMAND(ID_PROPERTIES,  Onproperties)
	ON_COMMAND(ID_NEWFOLDER,  OnNewFolder)
END_MESSAGE_MAP()

int CGuiSolExplorer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	//creamos el tab 
	if (!m_TabSolExplorer.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,0x9999))
		return -1;

	const DWORD dwStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS ;
	
	

	if (!m_TreeResourceView.Create(dwStyle,	CRect(0,0,0,0), &m_TabSolExplorer, 2))
		return -1;
	
	m_imgList.Create (IDB_DBPROJECTS, 16, 20, RGB (255, 0, 0));
	CreatContExplorer();
	if (!m_TreeSolExplorer.Create(dwStyle,	CRect(0,0,0,0), &m_ctSolution, 2))
		return -1;
	CreatContClassView();
	
	if (!m_TreeClassView.Create(dwStyle,	CRect(0,0,0,0), &m_ctClassView, 2))
		return -1;
	
	m_TreeSolExplorer.SetImageList(&m_imgList,TVSIL_NORMAL);
	m_TreeClassView.SetImageList(&m_imgList,TVSIL_NORMAL);
	m_TabSolExplorer.SetImageList(IDB_DBPROJECTS, 16,21, RGB (255, 0, 0));
	m_TabSolExplorer.Addtab(&m_ctSolution,"Solution Explorer",0);
	m_TabSolExplorer.Addtab(&m_ctClassView,"Class View",1);
	m_TabSolExplorer.Addtab(&m_TreeResourceView,"Resource View",2);
	FillerSolExplorer();
	FillTreeClassView();
	m_ctSolution.AddComponen(&m_TreeSolExplorer);
	m_ctClassView.AddComponen(&m_TreeClassView);
	SetIcon(IDB_BITMAPHELP,16,4,RGB(255,0,0),1);
	return 0;
}

void CGuiSolExplorer::Onproperties()
{
	AfxMessageBox("Properties");
}
void CGuiSolExplorer::OnNewFolder()
{
	AfxMessageBox("New Folder");
}

int CGuiSolExplorer::CreatContClassView()
{
	if (!m_ctClassView.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),&m_TabSolExplorer,124))
		return -1;
	m_ctClassView.AddComponen(&m_miClassView);
	m_miClassView.AlingButtons(CGuiMiniTool::ALIGN_LEFT);
	m_miClassView.SetImageList(IDB_DBPROJECTS, 16,24, RGB (255, 0, 0));
	m_miClassView.AddButton(22,ID_CLASSVIEW,NULL,_T(""),"Class View Sort by Type");
	m_miClassView.AddButton(23,ID_NEWFOLDER,NULL,_T(""),"New Folder");
	m_miClassView.AutoSize(FALSE);
	//m_miClassView.SetColor(GuiDrawLayer::GetRGBColorXP());
	return 1;
}

int CGuiSolExplorer::CreatContExplorer()
{
	//CGuiContainer m_ctClassView;
	//CGuiMiniTool  m_miClassView;
	if (!m_ctSolution.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),&m_TabSolExplorer,124))
		return -1;
	m_ctSolution.AddComponen(&m_miSolution);
	m_miSolution.AlingButtons(CGuiMiniTool::ALIGN_LEFT);
	m_miSolution.SetImageList(IDB_DBPROJECTS, 16,22, RGB (255, 0, 0));
	m_miSolution.AddButton(21,ID_PROPERTIES,NULL,_T(""),"properties");
	m_miSolution.AutoSize(FALSE);
//	m_miSolution.SetColor(GuiDrawLayer::GetRGBColorXP());
	return 0;
}

void CGuiSolExplorer::FillerSolExplorer()
{
	HTREEITEM hRoot = m_TreeSolExplorer.InsertItem (_T("Solution \'GuiLib\'(2 projects)"), 0, 0);
	HTREEITEM hProject = m_TreeSolExplorer.InsertItem (_T("Gui_DevStudio"), 10, 10, hRoot);
	m_TreeSolExplorer.SetItemState (hProject, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hSrc = m_TreeSolExplorer.InsertItem (_T("Source Files"), 11, 12, hProject);

	m_TreeSolExplorer.InsertItem (_T("ChildFrm.cpp"), 13, 13, hSrc);
	m_TreeSolExplorer.InsertItem (_T("Gui_DevStudio.cpp"), 13, 13, hSrc);
	m_TreeSolExplorer.InsertItem (_T("Gui_DevStudio.rc"), 13, 13, hSrc);
	m_TreeSolExplorer.InsertItem (_T("Gui_DevStudioDoc.cpp"), 13, 13, hSrc);
	m_TreeSolExplorer.InsertItem (_T("Gui_DevStudioView.cpp"), 13, 13, hSrc);
	m_TreeSolExplorer.InsertItem (_T("GuiHelp.cpp"), 13, 13, hSrc);
	m_TreeSolExplorer.InsertItem (_T("MainFrm.cpp"), 13, 13, hSrc);
	m_TreeSolExplorer.InsertItem (_T("StdAfx.cpp"), 13, 13, hSrc);

	HTREEITEM hInc = m_TreeSolExplorer.InsertItem (_T("Header Files"), 11, 12, hProject);

	m_TreeSolExplorer.InsertItem (_T("ChildFrm.h"), 14, 14, hInc);
	m_TreeSolExplorer.InsertItem (_T("Gui_DevStudio.h"), 14, 14, hInc);
	m_TreeSolExplorer.InsertItem (_T("Gui_DevStudioDoc.h"), 14, 14, hInc);
	m_TreeSolExplorer.InsertItem (_T("Gui_DevStudioView.h"), 14, 14, hInc);
	m_TreeSolExplorer.InsertItem (_T("GuiHelp.h"), 14, 14, hInc);
	m_TreeSolExplorer.InsertItem (_T("MainFrm.h"), 14, 14, hInc);
	m_TreeSolExplorer.InsertItem (_T("StdAfx.h"), 14, 14, hInc);

	HTREEITEM hRes = m_TreeSolExplorer.InsertItem (_T("Resource Files"), 11, 12, hProject);

	m_TreeSolExplorer.InsertItem (_T("dbproject.bmp"), 14, 14, hRes);
	m_TreeSolExplorer.InsertItem (_T("Gui_DevStudio.ico"), 14, 14, hRes);
	m_TreeSolExplorer.InsertItem (_T("Gui_DevStudio.rc2"), 14, 14, hRes);
	m_TreeSolExplorer.InsertItem (_T("Toolbar.bmp"), 2, 2, hRes);

	m_TreeSolExplorer.Expand (hProject, TVE_EXPAND);
	m_TreeSolExplorer.Expand (hRoot, TVE_EXPAND);
	m_TreeSolExplorer.Expand (hSrc, TVE_EXPAND);
	m_TreeSolExplorer.Expand (hInc, TVE_EXPAND);
	m_TreeSolExplorer.Expand (hRes, TVE_EXPAND);
}

void CGuiSolExplorer::FillTreeClassView()
{
	HTREEITEM hRoot =m_TreeClassView.InsertItem (_T("Gui_DevStudio"), 0, 0);
	HTREEITEM hGlobal = m_TreeClassView.InsertItem (_T("Global Functions and Variables"), 16, 16, hRoot);
	m_TreeClassView.InsertItem (_T("indicators"), 18, 18, hGlobal);
	m_TreeClassView.InsertItem (_T("theApp"), 18, 18, hGlobal);
	m_TreeClassView.InsertItem (_T("THIS_FILE"), 18, 18, hGlobal);
	m_TreeClassView.InsertItem (_T("THIS_FILE"), 18, 18, hGlobal);
	m_TreeClassView.InsertItem (_T("THIS_FILE"), 18, 18, hGlobal);
	m_TreeClassView.InsertItem (_T("THIS_FILE"), 18, 18, hGlobal);
	m_TreeClassView.InsertItem (_T("THIS_FILE"), 18, 18, hGlobal);

	HTREEITEM hMacros = m_TreeClassView.InsertItem (_T("Macros and Constants"), 20, 20, hRoot);
	m_TreeClassView.InsertItem (_T("AFX_CHILDFRM_H_AF42DC2C"), 20, 20, hMacros);
	m_TreeClassView.InsertItem (_T("AFX_GUI_DEVSTUDIO_H"), 20, 20, hMacros);
	m_TreeClassView.InsertItem (_T("AFX_GUI_DECSTUDIOVIEW_H"), 20, 20, hMacros);
	m_TreeClassView.InsertItem (_T("AFX_MAINFRM_H"), 20, 20, hMacros);
	m_TreeClassView.InsertItem (_T("_APS_3D_CONTROLS"), 20, 20, hMacros);
	m_TreeClassView.InsertItem (_T("_APS_NEXT_COMMAND_VALUE"), 20, 20, hMacros);
	m_TreeClassView.InsertItem (_T("IDB_DBPROJECTS"), 20, 20, hMacros);
	m_TreeClassView.InsertItem (_T("IDR_MAINFRAME"), 20, 20, hMacros);
	m_TreeClassView.InsertItem (_T("new"), 20, 20, hMacros);

	HTREEITEM hDlg = m_TreeClassView.InsertItem (_T("CAboutDlg"), 15, 15, hRoot);

	m_TreeClassView.InsertItem (_T("Bases and Interfaces"), 15, 15,hDlg);
	m_TreeClassView.InsertItem (_T("Maps"), 15, 15, hDlg);
	m_TreeClassView.InsertItem (_T("_unnamed_d4099230_1"), 15, 15, hDlg);
	m_TreeClassView.InsertItem (_T("CAboutDlg(void)"), 15, 15, hDlg);

	HTREEITEM hChild = m_TreeClassView.InsertItem (_T("CChilFrame"), 15, 15, hRoot);
	HTREEITEM hChild1 = m_TreeClassView.InsertItem (_T("CGui_DevStudioApp"), 15, 15, hRoot);
	HTREEITEM hChild2 = m_TreeClassView.InsertItem (_T("CGui_DevStudioView"), 15, 15, hRoot);
	
	
	m_TreeClassView.Expand (hRoot, TVE_EXPAND);
	m_TreeClassView.Expand (hGlobal, TVE_EXPAND);
	m_TreeClassView.Expand (hMacros, TVE_EXPAND);
	m_TreeClassView.Expand (hDlg, TVE_EXPAND);
}