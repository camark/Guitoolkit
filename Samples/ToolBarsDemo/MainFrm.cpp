// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ToolBarsDemo.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

#define BTN_TEST  500
#define BTN_TEST1  501
#define BTN_TEST2  502
#define BTN_TEST3  503
#define BTN_TEST4  504
#define BTN_TEST5  505
#define BTN_TEST6  506
#define BTN_TEST7  507
#define BTN_TEST8  508
#define BTN_TEST9  509
#define BTN_TEST10  510

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_DROP, OnDrop)
	ON_COMMAND(ID_PANELS, OnPanels)
	ON_COMMAND(BTN_TEST,  OnTest)
	ON_COMMAND(BTN_TEST1,  OnTest)
	ON_COMMAND(BTN_TEST2,  OnTest)
	ON_COMMAND(BTN_TEST3,  OnTest)
	ON_COMMAND(BTN_TEST4,  OnTest)
	ON_COMMAND(BTN_TEST5,  OnTest)
	ON_COMMAND(BTN_TEST6,  OnTest)
	ON_COMMAND(BTN_TEST7,  OnTest)
	ON_COMMAND(BTN_TEST8,  OnTest)
	ON_COMMAND(BTN_TEST9,  OnTest)
	ON_COMMAND(BTN_TEST10,  OnTest)
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

void CMainFrame::OnTest()
{
	CString sText;
	static val=0;
	CEditView* pView = (CEditView*)((CMDIFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	sText.Format ("Number= %d\r\n",val );
	pView->GetEditCtrl().ReplaceSel (sText);
	val++;
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
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.SetSaveHistory("MyHistory1",TRUE);
	DockControlBar(&m_wndMenuBar,m_dockTop);
	DockControlBar(&m_wndToolBar,m_dockTop);
	m_wndStatusBar.SetStyle(CGuiStatusBar::OFFICE);
	DockControlBar(&m_wndToolBar);
	sProfile = _T("GuiFlatDemo");
	
	if (!m_ctSolution.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),this,124))
		return -1;

	
	const DWORD dwStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS|WS_HSCROLL|WS_HSCROLL ;
	if (!m_tree.Create(dwStyle,	CRect(0,0,100,100),&m_ctSolution, 2))
		return -1;
	m_ctSolution.AddComponen(&m_tree);
	HTREEITEM hRoot =m_tree.InsertItem (_T("Gui_DevStudio"), 0, 0);
	HTREEITEM hGlobal = m_tree.InsertItem (_T("Global Functions and Variables"), 16, 16, hRoot);
	m_tree.InsertItem (_T("indicators"), 18, 18, hGlobal);
	m_tree.InsertItem (_T("theApp"), 18, 18, hGlobal);
	m_tree.InsertItem (_T("THIS_FILE"), 18, 18, hGlobal);
	m_tree.InsertItem (_T("theApp"), 18, 18, hGlobal);
	m_tree.InsertItem (_T("THIS_FILE"), 18, 18, hGlobal);
	m_tree.InsertItem (_T("theApp"), 18, 18, hGlobal);
	m_tree.InsertItem (_T("THIS_FILE"), 18, 18, hGlobal);
	m_wndToolBar.SetButtonDropDown(ID_DROP,8,&m_ctSolution,_T("Prueba"));


	if (!m_panAcc.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,100,100),this,1000))
		return -1;
	
	m_panAcc.SetColor(GuiDrawLayer::GetRGBFondoXP());
	m_panAcc.SetImageList(IDB_BITMAP1,16,11,RGB (255, 0, 0));
	m_panAcc.AddButton(BTN_TEST,0,&m_btn1,"Option 1");
	m_panAcc.AddButton(BTN_TEST1,1,&m_btn2,"Option 2");
	m_panAcc.AddButton(BTN_TEST2,2,&m_btn3,"Option 3");
	m_panAcc.AddButton(BTN_TEST3,3,&m_btn4,"Option 4");
	m_panAcc.AddButton(BTN_TEST4,4,&m_btn5,"Option 5");
	m_panAcc.AddButton(BTN_TEST5,5,&m_btn6,"Option 6");
	m_panAcc.AddButton(BTN_TEST6,6,&m_btn7,"Option 7");
	m_panAcc.AddButton(BTN_TEST7,7,&m_btn8,"Option 8");
	m_panAcc.AddButton(BTN_TEST8,0,&m_btn9,"Option 9");
	m_panAcc.AddButton(BTN_TEST9,4,&m_btn10,"Option 10");
	m_wndToolBar.SetButtonDropDown(ID_PANELS,6,&m_panAcc,_T("Prueba"));


//	LoadBars();

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


void CMainFrame::OnDrop() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnPanels() 
{
	// TODO: Add your command handler code here
	
}
