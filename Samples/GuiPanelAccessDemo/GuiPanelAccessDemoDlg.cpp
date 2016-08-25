// GuiPanelAccessDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GuiPanelAccessDemo.h"
#include "GuiPanelAccessDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
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
#define BTN_TEST11  511
#define BTN_TEST12  512
#define BTN_TEST13  513
#define BTN_TEST14  514
#define BTN_TEST15  515
#define BTN_TEST16  516


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiPanelAccessDemoDlg dialog

CGuiPanelAccessDemoDlg::CGuiPanelAccessDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGuiPanelAccessDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGuiPanelAccessDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGuiPanelAccessDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGuiPanelAccessDemoDlg)
	DDX_Control(pDX, IDC_MINITOOL, m_minitool);
	DDX_Control(pDX, IDC_FRAME, m_Frame);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGuiPanelAccessDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGuiPanelAccessDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
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
	ON_COMMAND(BTN_TEST11,  OnTest)
	ON_COMMAND(BTN_TEST12,  OnTest)
	ON_COMMAND(BTN_TEST13,  OnTest)
	ON_COMMAND(BTN_TEST14,  OnTest)
	ON_COMMAND(BTN_TEST15,  OnTest)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiPanelAccessDemoDlg message handlers

void CGuiPanelAccessDemoDlg::OnTest()
{
	AfxMessageBox("Test");
}

BOOL CGuiPanelAccessDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	if (!m_Splitter.Create(&m_Frame))
		return -1;
	if (!cf.Create(WS_VISIBLE|WS_CHILD,
			CRect(0,0,0,0), &m_Splitter, 0))
		return -1;
	
	m_Splitter.AddLeftCtrl(&cf,50);
	if (!m_panAcc.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),&cf,1000))
		return -1;
	if (!m_panAcc1.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),&cf,1001))
		return -1;
	m_panAcc1.SetColor(GuiDrawLayer::GetRGBFondoXP());

	m_panAcc.SetColor(GuiDrawLayer::GetRGBFondoXP());
	m_Splitter.AddLeftCtrl(&cf,50);
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
	m_panAcc.AddButton(BTN_TEST10,5,&m_btn11,"Option 11");
	m_panAcc.AddButton(BTN_TEST11,6,&m_btn12,"Option 12");
	m_panAcc.AddButton(BTN_TEST12,7,&m_btn13,"Option 13");
	m_panAcc.AddButton(BTN_TEST13,0,&m_btn14,"Option 14");
	m_panAcc.AddButton(BTN_TEST14,7,&m_btn15,"Option 15");
	m_panAcc.AddButton(BTN_TEST15,0,&m_btn16,"Option 16");
	m_list.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),&m_Splitter,509);
	m_Splitter.AddRightCtrl(&m_list,50);
	m_Splitter.SetStyleSeparator(CGuiSplitter::STYLE3D,GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());
	cf.AddFolder(&m_panAcc,"Access panel");
	m_Frame.AddChild(&m_Splitter);
	m_minitool.SetImageList(IDB_BITMAP1,16,11,RGB (255, 0, 0));
	m_minitool.AddButton(0,500);
	m_minitool.AddButton(1,501);
	m_minitool.AddButton(2,502);
	m_minitool.SetBorder(CGuiMiniTool::STYLE3D);
	
	m_panAcc1.SetImageList(IDB_BITMAP1,16,11,RGB (255, 0, 0));
	m_panAcc1.AddButton(BTN_TEST8,15,&m_btn17,"Option 1");
	cf.AddFolder(&m_panAcc1,"Grupos");
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGuiPanelAccessDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGuiPanelAccessDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGuiPanelAccessDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
