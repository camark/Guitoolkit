// GuiHeaderControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GuiHeaderControl.h"
#include "GuiHeaderControlDlg.h"

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
// CGuiHeaderControlDlg dialog

CGuiHeaderControlDlg::CGuiHeaderControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGuiHeaderControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGuiHeaderControlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGuiHeaderControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGuiHeaderControlDlg)
		//{{AFX_DATA_MAP(test)
	DDX_Control(pDX, IDC_LIST1, m_list);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGuiHeaderControlDlg, CDialog)
	//{{AFX_MSG_MAP(CGuiHeaderControlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiHeaderControlDlg message handlers

BOOL CGuiHeaderControlDlg::OnInitDialog()
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
	
	//--------------------------------------------------------------
	CRect rect;
	m_list.GetClientRect(&rect);
	int nInterval = rect.Width()/5;
	m_list.InsertColumn(0, _T("Option"), LVCFMT_LEFT, nInterval*2);
	m_list.InsertColumn(1, _T("Value"), LVCFMT_LEFT, nInterval);

	m_list.InsertColumn(2, _T("String"), LVCFMT_LEFT, nInterval*3); 

	// Create the columns
	// Put 10 items in the list
	LV_ITEM lvi;
	TCHAR szItem[256];
	lvi.mask = LVIF_TEXT;
	for (int i=0; i  < 4; i++)
	{
		lvi.iItem = i;
		lvi.iSubItem = 0;
		_stprintf(szItem, _T("Option %d"), i);
		lvi.pszText = szItem;
		m_list.InsertItem(&lvi);

		lvi.iSubItem = 1;
		_stprintf(szItem, _T("%d"), i*3);
		lvi.pszText = szItem;
		m_list.SetItem(&lvi);

		lvi.iSubItem = 2;
		strcpy(szItem,"My List");
		m_list.SetItem(&lvi);

	}
	
	HWND hWndHeader = m_list.GetDlgItem(0)->GetSafeHwnd();
//	m_h.SetImageList(IDB_BITMAP1, 16, 4, RGB (255, 0, 0));
	m_h.SubclassWindow (hWndHeader);
//	m_h.SetImageCol(0,0);
//	m_h.SetImageCol(1,1);
	ListView_SetExtendedListViewStyleEx(m_list.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//--------------------------------------------------------------
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGuiHeaderControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGuiHeaderControlDlg::OnPaint() 
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
HCURSOR CGuiHeaderControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGuiHeaderControlDlg::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	BOOL bSortAscending;
	if(pNMListView->iSubItem == m_h.GetSortColumn(&bSortAscending))
		bSortAscending = !bSortAscending;
	else
        bSortAscending = TRUE;

	m_h.SetSortColumn(pNMListView->iSubItem, bSortAscending);

	*pResult = 0;
}
