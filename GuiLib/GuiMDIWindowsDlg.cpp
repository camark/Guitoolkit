// GuiMDIWindowsDlg.cpp: implementation of the CGuiMDIWindowsDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GuiMDIWindowsDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiMDIWindowsDlg dialog

CGuiMDIWindowsDlg::CGuiMDIWindowsDlg(CMDIFrameWnd * pMDIFrame)
	: CDialog(CGuiMDIWindowsDlg::IDD, pMDIFrame)
{
	m_pMDIFrame = pMDIFrame;
	//{{AFX_DATA_INIT(CGuiMDIWindowsDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CGuiMDIWindowsDlg::CGuiMDIWindowsDlg(CMDIFrameWnd* pMDIFrame, CWnd* pParentWnd)
	: CDialog(CGuiMDIWindowsDlg::IDD, pParentWnd)
{
	m_pMDIFrame = pMDIFrame;
	//{{AFX_DATA_INIT(CGuiMDIWindowsDlg)
	//}}AFX_DATA_INIT
}

void CGuiMDIWindowsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGuiMDIWindowsDlg)
	DDX_Control(pDX, IDC_GUI_WINDOWLIST_LIST, m_wndList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGuiMDIWindowsDlg, CDialog)
	//{{AFX_MSG_MAP(CGuiMDIWindowsDlg)
	ON_BN_CLICKED(IDC_GUI_WINDOWLIST_CLOSE, OnClose)
	ON_LBN_SELCHANGE(IDC_GUI_WINDOWLIST_LIST, OnSelChange)
	ON_BN_CLICKED(IDC_GUI_WINDOWLIST_SAVE, OnSave)
	ON_BN_CLICKED(IDC_GUI_WINDOWLIST_ACTIVATE, OnActivate)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_GUI_WINDOWLIST_TILEHORZ, OnTileHorz)
	ON_BN_CLICKED(IDC_GUI_WINDOWLIST_MINIMIZE, OnMinimize)
	ON_BN_CLICKED(IDC_GUI_WINDOWLIST_TILEVERT, OnTileVert)
	ON_BN_CLICKED(IDC_GUI_WINDOWLIST_CASCADE, OnCascade)
	ON_LBN_DBLCLK(IDC_GUI_WINDOWLIST_LIST, OnActivate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiMDIWindowsDlg message handlers
				 
BOOL CGuiMDIWindowsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FillWindowList(); 	
	SelActive();
	UpdateButtons();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CGuiMDIWindowsDlg::OnClose() 
{
	int	nItems = m_wndList.GetCount();
	if (nItems != LB_ERR && nItems > 0)
	{
		HWND hMDIClient = m_pMDIFrame->m_hWndMDIClient;
		
		m_wndList.SetRedraw(FALSE);
		
		for (int i = nItems - 1; i >= 0; i--)
		{
			if (m_wndList.GetSel(i) > 0)
			{					   
				HWND hWnd = reinterpret_cast<HWND>(m_wndList.GetItemData(i));
				::SendMessage(hWnd, WM_CLOSE, static_cast<WPARAM>(0), 
					static_cast <LPARAM>(0));
				if (::GetParent(hWnd) == hMDIClient) 
					break;
			}				  
		}
		m_wndList.SetRedraw(TRUE);
	}
	FillWindowList();
	SelActive();
	UpdateButtons();
}

void CGuiMDIWindowsDlg::OnSelChange() 
{
	UpdateButtons();
}
// Enables/Disables states of buttons
void CGuiMDIWindowsDlg::UpdateButtons()
{						   
	int	nSel = m_wndList.GetSelCount();
	
	GetDlgItem(IDC_GUI_WINDOWLIST_CLOSE)->EnableWindow(nSel > 0);	
	GetDlgItem(IDC_GUI_WINDOWLIST_SAVE)->EnableWindow(nSel > 0);
	GetDlgItem(IDC_GUI_WINDOWLIST_TILEHORZ)->EnableWindow(nSel >= 2);
	GetDlgItem(IDC_GUI_WINDOWLIST_TILEVERT)->EnableWindow(nSel >= 2);
	GetDlgItem(IDC_GUI_WINDOWLIST_CASCADE)->EnableWindow(nSel >= 2);
	GetDlgItem(IDC_GUI_WINDOWLIST_MINIMIZE)->EnableWindow(nSel > 0);
	
	GetDlgItem(IDC_GUI_WINDOWLIST_ACTIVATE)->EnableWindow(nSel == 1);
}

// Selects currently active window in listbox
void CGuiMDIWindowsDlg::SelActive()
{
	int	nItems = m_wndList.GetCount();
	if (nItems != LB_ERR && nItems > 0)
	{
		m_wndList.SetRedraw(FALSE);
		m_wndList.SelItemRange(FALSE, 0, nItems - 1);
		
		HWND hwndActive = reinterpret_cast<HWND>(::SendMessage(m_pMDIFrame->m_hWndMDIClient,
			WM_MDIGETACTIVE, 0, 0));
		
		for (int i = 0; i < nItems; i++) 
		{
			if ((HWND) m_wndList.GetItemData(i) == hwndActive)  
			{
				m_wndList.SetSel(i);
				break;
			}
		}
		m_wndList.SetRedraw(TRUE);
	}
}

// Saves selected documents
void CGuiMDIWindowsDlg::OnSave() 
{
	int	nItems = m_wndList.GetCount();
	if (nItems != LB_ERR && nItems > 0)
	{
		for (int i = 0; i < nItems; i++)
		{
			if (m_wndList.GetSel(i) > 0)
			{
				HWND	   hWnd   = reinterpret_cast<HWND>(m_wndList.GetItemData(i));
				CWnd*	   pWnd   = CWnd::FromHandle(hWnd);
				CFrameWnd* pFrame = DYNAMIC_DOWNCAST(CFrameWnd, pWnd);
				if (pFrame != NULL)
				{
					CDocument* pDoc = pFrame->GetActiveDocument();
					if (pDoc != NULL) 
						pDoc->SaveModified();
				}
			}
		}
	}
	
	FillWindowList();
	SelActive();
	UpdateButtons();
}

void CGuiMDIWindowsDlg::OnActivate() 
{
	if (m_wndList.GetSelCount() == 1)
	{
		int	index;	
		if (m_wndList.GetSelItems(1, &index) == 1)
		{						 
			DWORD dw = m_wndList.GetItemData(index);
			if (dw != LB_ERR)
			{
				WINDOWPLACEMENT	wndpl;
				wndpl.length = sizeof(WINDOWPLACEMENT);
				::GetWindowPlacement(reinterpret_cast<HWND>(dw), &wndpl);
				if (wndpl.showCmd == SW_SHOWMINIMIZED) 
					::ShowWindow(reinterpret_cast<HWND>(dw), SW_RESTORE);
				::SendMessage(m_pMDIFrame->m_hWndMDIClient, WM_MDIACTIVATE, 
					static_cast<WPARAM>(dw), 0);
				EndDialog(IDOK);
			}
		}
	}
}

// Refresh windows list
void CGuiMDIWindowsDlg::FillWindowList(void)
{
	m_wndList.SetRedraw(FALSE);
	m_wndList.ResetContent();
	HWND hwndT;
	hwndT = ::GetWindow(m_pMDIFrame->m_hWndMDIClient, GW_CHILD);
	while (hwndT != NULL)
	{
		TCHAR szWndTitle[_MAX_PATH];
		::GetWindowText(hwndT, szWndTitle, sizeof(szWndTitle)/sizeof(szWndTitle[0]));
		
		int index = m_wndList.AddString(szWndTitle);
		m_wndList.SetItemData(index, reinterpret_cast<DWORD>(hwndT));
		hwndT = ::GetWindow(hwndT, GW_HWNDNEXT);
	}
	m_wndList.SetRedraw(TRUE);
}

// Draws listbox item
void CGuiMDIWindowsDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS) 
{
	if (nIDCtl == IDC_GUI_WINDOWLIST_LIST)
	{
		if (lpDIS->itemID == LB_ERR) 
			return; 
		
		HBRUSH	brBackground;
		RECT	rcTemp = lpDIS->rcItem; 
		HDC		hDC    = lpDIS->hDC;
		
		COLORREF	clText; 
		
		if (lpDIS->itemState & ODS_SELECTED)  
		{ 
			brBackground = GetSysColorBrush(COLOR_HIGHLIGHT); 
			clText       = GetSysColor(COLOR_HIGHLIGHTTEXT); 
		} 
		else 
		{ 
			brBackground = GetSysColorBrush(COLOR_WINDOW); 
			clText       = GetSysColor(COLOR_WINDOWTEXT); 
		} 
		
		if (lpDIS->itemAction &(ODA_DRAWENTIRE | ODA_SELECT)) 	
			FillRect(hDC, &rcTemp, brBackground); 
		
		int		 OldBkMode = ::SetBkMode(hDC, TRANSPARENT); 
		COLORREF clOldText = ::SetTextColor(hDC, clText); 
		
		TCHAR szBuf[1024];
		::SendMessage(lpDIS->hwndItem, LB_GETTEXT, static_cast<WPARAM>(lpDIS->itemID), 
			reinterpret_cast<LPARAM>(szBuf));		
		
		int h = rcTemp.bottom - rcTemp.top;
		rcTemp.left += h + 4;
		DrawText(hDC, szBuf, -1, &rcTemp, DT_LEFT | DT_VCENTER |	
			DT_NOPREFIX | DT_SINGLELINE);
		
		HICON hIcon = reinterpret_cast<HICON>
			(::GetClassLong(reinterpret_cast<HWND>(lpDIS->itemData), GCL_HICONSM));
		/*AfxGetApp()->LoadStandardIcon(IDI_HAND); */
		//(HICON) ::SendMessage((HWND) lpDIS->itemData,WM_GETICON,(WPARAM)ICON_BIG,(LPARAM) 0);
		rcTemp.left = lpDIS->rcItem.left;
		::DrawIconEx(hDC, rcTemp.left + 2, rcTemp.top, hIcon, h, h, 0, 0, DI_NORMAL);		
		
		::SetTextColor(hDC, clOldText);
		::SetBkMode(hDC, OldBkMode);
		
		if (lpDIS->itemAction & ODA_FOCUS)   
			DrawFocusRect(hDC, &lpDIS->rcItem); 
		return;		
	}
	CDialog::OnDrawItem(nIDCtl, lpDIS);
}

void CGuiMDIWindowsDlg::MDIMessage(UINT uMsg, WPARAM flag)
{
	int	nItems = m_wndList.GetCount();
	if (nItems != LB_ERR && nItems > 0)
	{
		HWND hMDIClient = m_pMDIFrame->m_hWndMDIClient;
		::LockWindowUpdate(hMDIClient);
		for (int i = nItems - 1; i >= 0; i--)
		{
			HWND hWnd = reinterpret_cast<HWND>(m_wndList.GetItemData(i));
			if (m_wndList.GetSel(i) > 0)	
				::ShowWindow(hWnd, SW_RESTORE);
			else						
				::ShowWindow(hWnd, SW_MINIMIZE);
		}
		::SendMessage(hMDIClient, uMsg, flag, 0);	
		::LockWindowUpdate(NULL);
	}
}

void CGuiMDIWindowsDlg::OnTileHorz() 
{
	MDIMessage(WM_MDITILE, MDITILE_HORIZONTAL);	
}

void CGuiMDIWindowsDlg::OnTileVert() 
{
	MDIMessage(WM_MDITILE, MDITILE_VERTICAL);	
}

void CGuiMDIWindowsDlg::OnMinimize() 
{
	int	nItems = m_wndList.GetCount();
	if (nItems != LB_ERR && nItems > 0)
	{
		m_wndList.SetRedraw(FALSE);
		
		for (int i = nItems - 1; i >= 0; i--)
		{
			if (m_wndList.GetSel(i) > 0)
			{
				HWND hWnd = reinterpret_cast < HWND>(m_wndList.GetItemData(i));
				::ShowWindow(hWnd, SW_MINIMIZE);
			}
		}
		m_wndList.SetRedraw(TRUE);
	}
	
	FillWindowList();
	SelActive();
	UpdateButtons();
}

void CGuiMDIWindowsDlg::OnCascade() 
{
	MDIMessage(WM_MDICASCADE, 0);
}

