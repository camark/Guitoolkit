// dialogcontrolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dialogcontrols.h"
#include "dialogcontrolsDlg.h"
#include "GuiDrawLayer.h"
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
// CDialogcontrolsDlg dialog

CDialogcontrolsDlg::CDialogcontrolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogcontrolsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogcontrolsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialogcontrolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogcontrolsDlg)
	DDX_Control(pDX, IDC_STATICOUTLOOK, m_outllok);
	DDX_Control(pDX, IDC_STATICMINITOOLS, m_minitools);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialogcontrolsDlg, CDialog)
	//{{AFX_MSG_MAP(CDialogcontrolsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogcontrolsDlg message handlers

BOOL CDialogcontrolsDlg::OnInitDialog()
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
	
	if (!m_Splitter.Create(&m_outllok))
		return -1;
	if (!cf.Create(WS_VISIBLE|WS_CHILD,
			CRect(0,0,0,0), &m_Splitter, 0))
		return -1;
	
	m_Splitter.AddLeftCtrl(&cf,50);

	if (!out.Create(WS_VISIBLE,	CRect(0,0,0,0), &cf, 1))
		return -1;

	#define IDO_OUTODAY	   5600
	#define IDO_CALENDARIO 5601
	#define IDO_CONTACTO   5602
	#define IDO_TAREAS     5603
	#define IDO_NOTAS	   5604	
	#define IDO_ELIMINAR   5605

	out.SetImageList(IDB_BITMAP1, 32, 0, RGB(255,0,0));
	out.AddItem(IDO_OUTODAY,"OutLook para hoy",7);
	out.AddItem(IDO_CALENDARIO,"Calendario",1);
	out.AddItem(IDO_CONTACTO,"Contactos",2);
	out.AddItem(IDO_TAREAS,"tareas",3);
	out.AddItem(IDO_NOTAS,"Notas",5);
	out.AddItem(IDO_ELIMINAR,"Elementos Eliminados",6);
	//------------------------------------------------------------------
	if (!tc.Create(WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS,
		CRect(0,0,0,0), &cf, 2))
		return -1;
	HTREEITEM hRoot = tc.InsertItem (_T("Opcion uno"), 0, 0);
	tc.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hClass = tc.InsertItem (_T("Opcion dos"), 1, 1, hRoot);
	tc.InsertItem (_T("SubOpcion dos"), 3, 3, hClass);
	tc.InsertItem (_T("SubOpcion tres"), 4, 4, hClass);

	tc.Expand (hRoot, TVE_EXPAND);

	//--------------------------------------------------------------------
	if (!tc1.Create(WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS,
		CRect(0,0,0,0), &m_Splitter, 2))
		return -1;
	hRoot = tc1.InsertItem (_T("Opcion uno"), 0, 0);
	tc1.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);

	hClass = tc1.InsertItem (_T("Opcion dos"), 1, 1, hRoot);
	tc1.InsertItem (_T("SubOpcion dos"), 3, 3, hClass);
	tc1.InsertItem (_T("SubOpcion tres"), 4, 4, hClass);

	tc1.Expand (hRoot, TVE_EXPAND);
	//-------------------------------------------------------------------

//	out.SetXp(TRUE);
	cf.AddFolder(&out,"Accesos directos de OutLook");
	cf.AddFolder(&tc,"Mis Accesos directos");
	m_Splitter.AddRightCtrl(&tc1,50);
	m_outllok.AddChild(&m_Splitter);
	m_Splitter.SetStyleSeparator(CGuiSplitter::STYLE3D,GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());
	// TODO: Add extra initialization here
	

	//-------------------------------------------------------------------------
	//caption Bar Outlook Style

#define ID_VIEWCAPTION WM_USER+1
#define IDT_BACK	   ID_VIEWCAPTION+1
#define IDT_FORW	   IDT_BACK+1		
#define	IDT_STANDAR    IDT_FORW+1
#define	IDT_GO		    IDT_STANDAR+1
#define	IDT_UNDO		IDT_GO+1

	if (!m_CapOutBar.Create (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 
			&m_minitools,ID_VIEWCAPTION))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;
	}

	if (!m_CapOutBar.SetSplitter(&m_MiniSplitter))
		return FALSE;

	m_MiniSplitter.AddMiniToolLeft(&m_guiMiniToolLeft);
	m_MiniSplitter.AddMiniToolRight(&m_guiMiniToolRight);
	m_guiMiniToolLeft.SetImageList(IDB_BITMAP2,16,11,RGB (255, 0, 0));
	m_guiMiniToolRight.SetImageList(IDB_BITMAP2,16,11,RGB (255, 0, 0));
	
	//Left MiniTool 
	m_guiMiniToolLeft.AddButton(11,IDT_BACK,NULL,"Back ","Back");
	m_guiMiniToolLeft.AddButton(12,IDT_FORW,NULL,"Forward","Forward");
	m_guiMiniToolLeft.AddButton(0,IDT_STANDAR,NULL,"OutLook Today","OutLook Today");
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetFontColor(RGB(255,255,255));

	//Right MiniTool
	m_guiMiniToolRight.CreateCombo(&m_cb,333,100);
	m_guiMiniToolRight.AddButton(13,IDT_GO,NULL,"Go  ","Go  ");
	m_guiMiniToolRight.AddButton(15,IDT_UNDO,NULL,"Undo  ","Undo  ");
	m_MiniSplitter.SetColor(GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorBTNHigh());
	m_guiMiniToolRight.SetCaption("&Direccion:",CGuiMiniTool::ALIGN_LEFT);
	m_guiMiniToolRight.SetColorCaption(GuiDrawLayer::GetRGBColorBTNHigh());
	m_guiMiniToolRight.AutoSize(TRUE);
	
	m_cb.AddString("outlook:Tareas");
	m_cb.AddString("outlook:Notas");
	m_cb.AddString("Toolbar Combobox item four");
	m_cb.AddString("Toolbar Combobox item five");
	m_cb.AddString("Toolbar Combobox item six");
	m_cb.SetColor(GuiDrawLayer::GetRGBColorShadow());
	m_minitools.AddChild(&m_CapOutBar);
	//--------------------------------------------------------------------------
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDialogcontrolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDialogcontrolsDlg::OnPaint() 
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
HCURSOR CDialogcontrolsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
