// TestDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "TestDlgDlg.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CTestDlgDlg dialog

CTestDlgDlg::CTestDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlgDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlgDlg)
	DDX_Control(pDX, IDC_LINKBUTTON, m_Link);
	DDX_Control(pDX, IDC_GROUPBOX, m_gbox);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDOK, m_Okbtn);
	DDX_Control(pDX, IDC_BTNARROW , m_btnArrow);
	DDX_Control(pDX, IDC_COMBO1, m_Combobox);
	DDX_Control(pDX, IDC_CHECK2, m_btnCheck2);
	DDX_Control(pDX, IDC_CHECK1, m_btnCheck1);
	DDX_Control(pDX, IDC_EDITFLAT, m_guiedit);
	DDX_Control(pDX, IDC_RADIO1, m_rd1);
	DDX_Control(pDX, IDC_RADIO2, m_rd2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlgDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)

	//}}AFX_MSG_MAP

//ON_COMMAND(ID_OPTION2, OnOption2)
ON_COMMAND(ID_OPTION1, OnOption1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg message handlers

BOOL CTestDlgDlg::OnInitDialog()
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

	//*****************************************************************
	
	m_Link.SetLink("www.beyondata.com");
	m_Link.SetToolTip("Goto GuiLib Site");
	menu.LoadMenu(IDR_MENU1);
	m_Okbtn.SetCaption("&Ok");
	m_Okbtn.SetStyleBorder(CGuiButton::STYLEXP);
//	m_Okbtn.AutoSizeButton();
//	m_Okbtn.SetImage(IDI_ICON1);
//	m_Okbtn.ShowImage();
	m_cancel.ShowText();
	m_cancel.SetToolTip("Cancelar");

	m_cancel.SetImage(IDI_ICON1,-1,-1);
	m_cancel.ShowImage();
//	m_cancel.AutoSizeButton();
	m_gbox.SetWindowText("Algunos controles");
	m_gbox.SetStyle(CGuiGroupBox::ALING_LEFT);
	//*****************************************************************
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	//********************************************************************	
	m_guiedit.SetToolTip("test de tooltip");
	m_guiedit.SetMask("ID:##.###.### Ciudad:(aaaAAAa)","ID:__.___.___ Ciudad:(_______)",CGuiEdit::MASK_HOUR12);
//	m_guiedit.AddButton(m_imag.ExtractIcon(0),333,NULL,"Press Here");
	m_btnArrow.SetTypeButton(CGuiButton::TYPE_ARROW);
	m_btnArrow.SetAlingArrow(CGuiButton::ARROW_RIGHT);
	m_btnArrow.SetPopupMenu(&menu);
//	m_btnArrow.AutoSizeButton();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDlgDlg::OnPaint() 
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
HCURSOR CTestDlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlgDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	
}




void CTestDlgDlg::OnOption1()
{
	// TODO: Add your command handler code here
	AfxMessageBox("Hola");
}
