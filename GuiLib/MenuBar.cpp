/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *							 (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software;so you are free to use it any of your		*
 * applications (Freeware, Shareware, Commercial),but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 *																			*
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 * -igor1960																*	
 ****************************************************************************/


//
// Class	:  CMenuBar
// 
// Version	: 1.0
// 
// Created	: Jan 14, 2001        
//
// Last Modified: Francisco Campos. 
//
// CMenuBar class version 2.12
//		simulates a Dev Studio style dockable menu bar.
//		based on PixieLib written by Paul DiLascia<www.dilascia.com>
//
// version history
//		2.12 : support OLE menu carelessly.
//		2.11 : WindowMenu fixed by VORGA.
//		2.10 : CMenuDockBar's problem fixed again and again.
//		2.08 : give up precise ComputeMenuTrackPoint
//		2.07 : Sychronizing with frame activation problem fixed
//		2.06 : CMenuItem::ComputeMenuTrackPoint fixed a little
//		2.05 : CMenuDockBar fixed
//			 : Inactive state problem fixed
//		2.04 : bug with ::TrackPopupEx carelessly fixed 
//           : synchronizing TrackPopup animation with win98 effect
//
//						written by MB <mb2@geocities.co.jp> 1999.11.27
//
//
//
// CMenuBar version 2.13

#include "stdafx.h"
#include "MenuBar.h"
#include "resource.h"
#include "GuiDockContext.h"
#include <afxole.h>
#include "Menubar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
	const BOOL bTraceOn = FALSE;
	#define LTRACE if (bTraceOn) TRACE
	const BOOL bTraceOn2 = TRUE;
	#define LTRACE2 if (bTraceOn2) TRACE
#else
	#define LTRACE
	#define LTRACE2
#endif

BOOL bActivSystemMenu;
//////////////////////////////////////////////////////////////////////
// I've found string resource of "More windows" in "user.exe".
// But I can't load it, so please replace a following with your language.
static const TCHAR _szMoreWindows[] = _T("&More windows...");

//////////////////////////////////////////////////////////////////////
// used for OLE menu (easy fix)
static BOOL _bWindowMenuSendCmd = FALSE;
static int _nPrevIndexForCmd = -1;

//////////////////////////////////////////////////////////////////////
// hook
static CMenuBar* g_pMenuBar = NULL;
static HHOOK	 g_hMsgHook = NULL;

// message
const UINT CMenuBar::WM_GETMENU = ::RegisterWindowMessage(_T("CMenuBar::WM_GETMENU"));
const UINT MB_SET_MENU_NULL = ::RegisterWindowMessage(_T("CMenuBar::MB_SET_MENU_NULL"));

const int cxBorder2 = ::GetSystemMetrics(SM_CXBORDER)*2;
const int cyBorder2 = ::GetSystemMetrics(SM_CYBORDER)*2;

// common resources
static CFont _fontHorzMenu, _fontVertMenu;
static int _cyHorzFont, _cyMenuOnBar, _cyTextMargin;
const int CXTEXTMARGIN = 5;

DWORD dSt;
COLORREF   m_clrFace;

int		gbintHorz;			//Horz=0, Vert=1
CRect	rcMenu;					//CRect of button
static BOOL _InitCommonResources(BOOL bForce = FALSE)
{
	if (bForce == FALSE && _fontHorzMenu.m_hObject != NULL)
		return TRUE;// no need to reinitialize

	// clean up
	_fontHorzMenu.DeleteObject();
	_fontVertMenu.DeleteObject();

	// create fonts
	NONCLIENTMETRICS info; info.cbSize = sizeof(info);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);
	if (!_fontHorzMenu.CreateFontIndirect(&info.lfMenuFont))
		return FALSE;

	// create vertical font
	info.lfMenuFont.lfEscapement = -900;
	info.lfMenuFont.lfOrientation = -900;
	strcpy(info.lfMenuFont.lfFaceName,"verdana");
	if (!_fontVertMenu.CreateFontIndirect(&info.lfMenuFont))
		return FALSE;

	// get font height
	_cyHorzFont = abs(info.lfMenuFont.lfHeight);

	// calc Y text margin
	_cyMenuOnBar = info.iMenuHeight;
	_cyMenuOnBar = max(_cyMenuOnBar, ::GetSystemMetrics(SM_CYSMICON));
	_cyTextMargin = (_cyMenuOnBar - _cyHorzFont) / 2;

	return TRUE;
}

// I wanted to control popup point, but I've fount we can never get popupmenu rect before popup.
// even if not owner draw menu...




static CPoint _ComputeMenuTrackPoint(const CRect& rcItem, DWORD dwStyle, UINT& fuFlags, TPMPARAMS& tpm)
{
	fuFlags = TPM_LEFTBUTTON | TPM_LEFTALIGN | TPM_HORIZONTAL;
	tpm.cbSize = sizeof(tpm);
	CPoint pt;
	CRect& rcExclude = (CRect&)tpm.rcExclude;
	CWnd::GetDesktopWindow()->GetWindowRect(&rcExclude);

	CRect rcFrame;
	AfxGetMainWnd()->GetWindowRect(&rcFrame);

	switch (dwStyle & CBRS_ALIGN_ANY) {
	case CBRS_ALIGN_RIGHT:
	case CBRS_ALIGN_LEFT:
		pt = CPoint(rcItem.right+1, rcItem.top-1);
		// to avoid strange menu flip, won't do : [rcExclude.right = rcItem.right+1;]
		// I want to use : fuFlags |= TPM_HORNEGANIMATION;
		break;

	default: //	case CBRS_ALIGN_TOP:
		// changed by Manfred Drasch - start
		CRect rcTmpItem;
		rcTmpItem = rcItem;
		if(rcTmpItem.left < 0)
		{
			rcTmpItem.right = rcTmpItem.Width();
			rcTmpItem.left = 0;
		}
		
		if(rcTmpItem.left > rcExclude.right)
		{
			rcTmpItem.right = rcExclude.right; 
			rcTmpItem.left = rcTmpItem.right-rcTmpItem.Width();
		}
		pt = CPoint(rcTmpItem.left-1, rcTmpItem.bottom);
		rcExclude.bottom = rcTmpItem.bottom+1;// <- insead of [fuFlags |= TPM_VERPOSANIMATION;]
		// changed by Manfred Drasch - end
		break;
	}
	return pt;
}


//******************************************************************
static int _CalcTextWidth(const CString& strText)
{
	CWindowDC dc(NULL);
	CRect rcText(0, 0, 0, 0);
	CFont* pOldFont = dc.SelectObject(&_fontHorzMenu);
	dc.DrawText(strText, &rcText, DT_SINGLELINE | DT_CALCRECT);
	dc.SelectObject(pOldFont);

	return rcText.Width();
}

//******************************************************************
// grippers pasted from MFC6
#define CX_GRIPPER  3
#define CY_GRIPPER  3
#define CX_BORDER_GRIPPER 2
#define CY_BORDER_GRIPPER 2
#define CX_GRIPPER_ALL CX_GRIPPER + CX_BORDER_GRIPPER*2
#define CY_GRIPPER_ALL CY_GRIPPER + CY_BORDER_GRIPPER*2

/////////////////////////////////////////////////////////////////////////////
// CMenuBar
BEGIN_MESSAGE_MAP(CMenuBar, CControlBar)
	//{{AFX_MSG_MAP(CMenuBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(MB_SET_MENU_NULL, OnSetMenuNull)
	ON_WM_PAINT()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CMenuBar, CControlBar)

/////////////////////////////////////////////////////////////////////////////
// CMenuBar Construction
CMenuBar::CMenuBar()
{
	m_nCurIndex  = -1;
	m_nTrackingState = none;
	m_bProcessRightArrow = m_bProcessLeftArrow = TRUE;
	m_bIgnoreAlt = FALSE;
	m_hMenu = NULL;
	m_nIDEvent = NULL;
	szNameHistory.Empty();
	bSaveHistory=FALSE;
	m_bChangeState=FALSE;
	m_bMDIMaximized = FALSE;
	m_hWndMDIClient = NULL;
	m_hWndActiveChild = NULL;

	m_pMenuIcon = NULL;
	m_pMenuControl = NULL;

	m_bDelayedButtonLayout = TRUE;
	m_dwExStyle = 0;

	m_bFrameActive = FALSE;
	m_bMDIApp = FALSE;
	m_bXP=FALSE;
	cmb=NULL;
	m_bCombo=FALSE;//combobox by default
	bIsTabbed=FALSE;
	m_MenuContext=NULL;
	m_StyleDisplay=GUISTYLE_XP;
}

//******************************************************************
BOOL CMenuBar::Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID)
{
	return CreateEx(pParentWnd, dwStyle,
		CRect(m_cxLeftBorder, m_cyTopBorder, m_cxRightBorder, m_cyBottomBorder), nID);
	
}

//******************************************************************
BOOL CMenuBar::CreateEx(CWnd* pParentWnd, DWORD dwStyle, CRect rcBorders, UINT nID)
{
	ASSERT_VALID(pParentWnd);// must have a parent
	ASSERT (!((dwStyle & CBRS_SIZE_FIXED) && (dwStyle & CBRS_SIZE_DYNAMIC)));

	SetBorders(rcBorders);

	// save the original style
	m_dwExStyle = dwStyle;

	// save the style
	m_dwStyle = (dwStyle & CBRS_ALL);// ******fixed by Mark Gentry, thanx!******
	
	dwStyle &= ~CBRS_ALL;
	dwStyle|=WS_CLIPCHILDREN | CCS_NOPARENTALIGN | CCS_NOMOVEY | CCS_NORESIZE;
	CString strClass = AfxRegisterWndClass(
		/*CS_HREDRAW | CS_VREDRAW |*/
		CS_DBLCLKS,// don't forget!
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		(HBRUSH)NULL);

	m_clrFace=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	return CWnd::Create(strClass, _T("MenuBar"), dwStyle, CRect(), pParentWnd, nID);
}
void CMenuBar::SetSaveHistory(CString sNameHistory,BOOL bsaveHistory)
{
	szNameHistory=sNameHistory;
	bSaveHistory=bsaveHistory;
}
//******************************************************************
int CMenuBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CWnd* pFrame = GetOwner();
	ASSERT_VALID(pFrame);

	// hook frame window to trap WM_MENUSELECT
	//m_hookFrame.Install(this, pFrame->GetSafeHwnd());

	// If this is an MDI app, hook client window to trap WM_MDISETMENU
	if (pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd))) {
		m_bMDIApp = TRUE;
		m_hWndMDIClient = ((CMDIFrameWnd*)pFrame)->m_hWndMDIClient;
		ASSERT(::IsWindow(m_hWndMDIClient));
		m_hookMDIClient.Install(this, m_hWndMDIClient);
	}

	if (m_pDockContext==NULL)
		m_pDockContext=new CGuiDockContext(this);
	ASSERT(m_pDockContext);

	if (!_InitCommonResources()) {
		TRACE(_T("Failed to create menubar resource\n"));
		return FALSE;
	}	

	return 0;
}


void CMenuBar::OnSysColorChange( )
{
	
	CClientDC dc(this);
	m_clrFace=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	for (int i = 0; i < m_arrItem.GetSize(); ++i)
		m_arrItem[i]->UpdateClr();
	CWnd::OnSysColorChange( );

	/*if(m_pMenuControl != NULL) 
		m_pMenuControl->SetColorButton(GuiDrawLayer::GetRGBColorFace());
	if(m_pMenuIcon != NULL) 
	{
		m_pMenuIcon->OnActivateChildWnd();
		m_pMenuIcon->Update(&dc);	
	}*/
	
}
//******************************************************************

BOOL CMenuBar::CreateCombo(CComboBox* pControl,UINT nID,int iSize,DWORD dwStyle)
{
	CFont m_Font;
	m_Font.CreateStockObject (DEFAULT_GUI_FONT);
	if(!pControl->Create(dwStyle, CRect(1,1,iSize,100), this, nID))
	{
		TRACE(_T("Failed to create combo-box\n"));
		m_bCombo=FALSE;
		return FALSE;
	}
	m_bCombo=TRUE;
	cmb=(CGuiComboBoxExt*)pControl;
	cmb->ActiveHistory(TRUE);
	cmb->LoadHistory(szNameHistory,bSaveHistory);	
	return TRUE;
}

//******************************************************************
void CMenuBar::OnSize(UINT nType, int cx, int cy) 
{
	RefreshBar();
	if (m_bCombo==TRUE)
		DrawCombo();
}


void CMenuBar::SetTabbed(BOOL bIstabed)
{
	bIsTabbed=bIstabed;
}

//******************************************************************
BOOL CMenuBar::InitItems()
{
	ASSERT(m_hMenu);

	// clean up all items
	DeleteItems();

	// buttons
	for (int i = 0; i < ::GetMenuItemCount(m_hMenu); ++i) {
		m_arrItem.Add(new CMenuButton(m_hMenu, i,this));
	}

	if (m_bMDIApp) {
		// icon
		CWnd* pFrame = GetTopLevelFrame();
		ASSERT_VALID(pFrame);
		CMDIFrameWnd* pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pFrame);
		HWND hWndMDIClient = pMDIFrame->m_hWndMDIClient;
		ASSERT(::IsWindow(hWndMDIClient));

		HWND hWndChild = (HWND)::SendMessage(hWndMDIClient,
			WM_MDIGETACTIVE, 0, 0);
		if ((!bIsTabbed) )
		{

			m_pMenuIcon = new CMenuIcon(this);
			m_arrItem.InsertAt(0, m_pMenuIcon);
			// frame control
			m_pMenuControl = new CMenuControl(this);
			m_arrItem.Add(m_pMenuControl);

			// reinitializing
			m_pMenuIcon->OnActivateChildWnd();
			m_pMenuControl->OnActivateChildWnd();
		}
	}
	
	return TRUE;
}


//******************************************************************
BOOL CMenuBar::LoadMenuBar(UINT nIDResource)
{
	ASSERT(m_hMenu == NULL);

	ASSERT_VALID(m_pDockSite);
	if (m_pDockSite->GetMenu()) {
		PostMessage(MB_SET_MENU_NULL, (WPARAM)m_pDockSite->GetSafeHwnd());
	}
	
	m_hMenu = ::LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDResource));
	if (m_hMenu == NULL) {
		TRACE(_T("Failed to load menu\n"));
		return FALSE;
	}

	return InitItems();
}

//******************************************************************

HMENU CMenuBar::LoadMenu(HMENU hMenu, HMENU hWindowMenu)
{
	ASSERT(::IsMenu(hMenu));
	ASSERT_VALID(this);
	
	CFrameWnd* pFrame = GetParentFrame();
	if (::GetMenu(pFrame->GetSafeHwnd()) != NULL) {
		// not to make MFC ignore SetMenu(NULL), post it.
		PostMessage(MB_SET_MENU_NULL, (WPARAM)pFrame->GetSafeHwnd());
	}

	HMENU hOldMenu = m_hMenu;
	m_hMenu = hMenu;// menu is shared with MFC

	// initialize Items 
	VERIFY(InitItems());

	if (hMenu) {
		m_hWindowMenu = hWindowMenu;
		RefreshBar();// and menubar itself
	}

	return hOldMenu;
}

//******************************************************************

void CMenuBar::RefreshBar()
{
	InvalidateRect(NULL);

#if _MFC_VER >= 0x600
		if (GetParent()->IsKindOf(RUNTIME_CLASS(CReBar))) {
			m_bDelayedButtonLayout = TRUE;// to avoid ASSERTION
			Layout();
		}
#endif

	CFrameWnd* pFrame = (CFrameWnd*)GetTopLevelFrame();
	ASSERT_VALID(pFrame); ASSERT(pFrame->IsFrameWnd());

	pFrame->RecalcLayout();

	// floating frame
	CFrameWnd* pMiniFrame = GetParentFrame();
	if (pMiniFrame->IsKindOf(RUNTIME_CLASS(CMiniFrameWnd)))
		pMiniFrame->RecalcLayout();
}

/////////////////////////////////////////////////////////////////////////////
// CMenuBar clean up 
CMenuBar::~CMenuBar()
{
	
}

//******************************************************************
void CMenuBar::DeleteItems()
{
	for(int i = 0; i < m_arrItem.GetSize(); ++i) {
		CMenuItem* pItem = m_arrItem[i];
		delete pItem;
	}

	m_arrItem.RemoveAll();

	m_pMenuIcon = NULL;
	m_pMenuControl = NULL;
}

//******************************************************************
/////////////////////////////////////////////////////////////////////////////
// CMenuBar draw

//******************************************************************
void CMenuBar::UpdateBar(TrackingState nState, int nNewIndex)
{
	if (m_nTrackingState == buttonmouse)	
		m_bIgnoreAlt = FALSE;// if prev state is BUTTONMOUSE, always should be FALSE!

	m_nTrackingState = nState;


	// clean up
	if (IsValidIndex(m_nCurIndex)) {
		CMenuItem* pItem = m_arrItem[m_nCurIndex];
		CClientDC dc(this);
		pItem->ModifyState(MISTATE_HOT | MISTATE_PRESSED, 0);
		pItem->Update(&dc);

		// draw captions forcefully
		if (m_pMenuControl) {
			CRect rcCross = m_pMenuControl->GetRect() & m_arrItem[m_nCurIndex]->GetRect();
			if (!rcCross.IsRectEmpty()) {
				m_pMenuControl->DrawControl();
				if (m_bCombo==TRUE)
					DrawCombo();
			}
		}

		m_nCurIndex = -1;
	}

	if (nState != none) {
		ASSERT(IsValidIndex(nNewIndex));
		m_nCurIndex = nNewIndex;
		CMenuItem* pItem = m_arrItem[m_nCurIndex];
		CClientDC dc(this);

		if (nState == button || nState == buttonmouse) {
			pItem->ModifyState(MISTATE_PRESSED, MISTATE_HOT);
			pItem->Update(&dc);
		}
		else if (nState == popup) {
			pItem->ModifyState(MISTATE_HOT, MISTATE_PRESSED);
			pItem->Update(&dc);
		}

		// draw captions forcefully
		if (m_pMenuControl) {
			CRect rcCross = m_pMenuControl->GetRect() & m_arrItem[m_nCurIndex]->GetRect();
			if (!rcCross.IsRectEmpty()) {
				m_pMenuControl->DrawControl();
				if (m_bCombo==TRUE)
					DrawCombo();
			}
		}
	}
	else {
		// must be default parameter
		ASSERT(nNewIndex == -1);
	}

	m_bProcessRightArrow = m_bProcessLeftArrow = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMenuBar message handler
int CMenuBar::HitTestOnTrack(CPoint point)
{
	for (int i = 0; i < GetItemCount(); ++i) {
		CMenuItem* pItem = m_arrItem[i];
		CRect rcItem = pItem->GetRect();
				
		if ((pItem->GetStyle() & MISTYLE_TRACKABLE) &&
			rcItem.PtInRect(point))
			return i;
	}

	return -1;
}

//*******************************************************************
void CMenuBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
}

//******************************************************************
void CMenuBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCursor (LoadCursor(NULL, IDC_SIZEALL));
	//int nIndex = HitTestOnTrack(point);
	int nIndex=nFlags >= 100? nFlags-100: -1;
	if(m_bMDIApp && !bIsTabbed)
	{

		if (nFlags == 1000)
			nIndex=0;
		else if (nIndex == -1)
			nIndex=-2;
		else 
			nIndex++;
	}
	if (IsValidIndex(nIndex) &&	(m_arrItem[nIndex]->GetStyle() & MISTYLE_TRACKABLE)) {
		UpdateBar(button, nIndex);
		TrackPopup(nIndex);
		return;		// eat it!
	}

	CControlBar::OnLButtonDown(nFlags, point);
}

void CMenuBar::OnRButtonDown(UINT nFlags, CPoint point) 
{
	
	ClientToScreen (&point);
	CMenu m_menu;
	if (m_MenuContext!= NULL)
	{
		m_menu.LoadMenu(m_MenuContext);
		CMenu* m_SubMenu = m_menu.GetSubMenu(0);
		m_SubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,
				point.x, point.y-2, AfxGetMainWnd());
		Invalidate();
		UpdateWindow();
	}			
//	CMenuBar::OnRButtonDown(nFlags, point);
}


//******************************************************************
void CMenuBar::OnMouseMove(UINT nFlags, CPoint point)
{
	int nIndex = HitTestOnTrack(point);
	if (!IsTopParentActive() || !GetTopLevelParent()->IsWindowEnabled())
		return;
	if (IsValidIndex(nIndex)) {	
		if (m_nCurIndex == -1 || m_nCurIndex != nIndex) {// if other button
			UpdateBar(buttonmouse, nIndex);// button made hot with mouse

			if (!m_nIDEvent)
				m_nIDEvent = SetTimer(1, 100, NULL);
		}
	}
	else {
		UpdateBar();
	}

	CControlBar::OnMouseMove(nFlags, point);
}

//******************************************************************
LRESULT CMenuBar::OnSetMenuNull(WPARAM wParam, LPARAM)
{
	HWND hWnd = (HWND)wParam;
	ASSERT(::IsWindow(hWnd));
	::SetMenu(hWnd, NULL);
	
	return 0;
}

//******************************************************************
LRESULT CMenuBar::OnSettingChange(WPARAM wParam, LPARAM lParam)
{
	// reinitialize fonts etc
	if (!_InitCommonResources(TRUE)) {
		TRACE(_T("Failed to create bar resource\n"));
		return FALSE;
	}

	VERIFY(InitItems());

	CFrameWnd* pFrame = GetParentFrame();
	ASSERT_VALID(pFrame);
	pFrame->RecalcLayout();
	return 0;
}
//******************************************************************
void CMenuBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CControlBar::OnLButtonUp(nFlags, point);
}
//******************************************************************
void CMenuBar::CheckActiveChildWndMaximized()
{
	if(!m_pMenuControl) return;
	if (!bIsTabbed)
	{
		ASSERT(m_pMenuControl);
		ASSERT(m_pMenuIcon);
	}

	BOOL bMaximized = FALSE;
	GetActiveChildWnd(bMaximized);
	if (m_bMDIMaximized != bMaximized) {
		LTRACE(_T("CMenuBar::CheckActiveChildWndMaximized---state changed, refreshing\n"));
		m_bMDIMaximized = bMaximized;
		if (!bIsTabbed)
		{
		
			m_pMenuControl->OnActivateChildWnd();
			m_pMenuIcon->OnActivateChildWnd();
			if(!m_bMDIMaximized )
			{
				m_bChangeState=TRUE;
				m_pMenuControl->m_arrButton[0].ShowWindow(SW_HIDE);
				m_pMenuControl->m_arrButton[1].ShowWindow(SW_HIDE);
				m_pMenuControl->m_arrButton[2].ShowWindow(SW_HIDE);
			}
			else
			{
				m_bChangeState=TRUE;
				m_pMenuControl->m_arrButton[0].ShowWindow(SW_SHOW);
				m_pMenuControl->m_arrButton[1].ShowWindow(SW_SHOW);
				m_pMenuControl->m_arrButton[2].ShowWindow(SW_SHOW);
				
			}
		
		}
		
		if (m_bCombo==TRUE)
			DrawCombo();
				RefreshBar();	
	}


}
//******************************************************************
void CMenuBar::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	LTRACE(_T("CMenuBar::OnInitMenuPopup\n"));
	CMenu menu;
	menu.Attach((HMENU)m_hWindowMenu);

	// scan for first window command
	int n = menu.GetMenuItemCount();
	BOOL bAddSeperator = TRUE;
	for (int iPos=0; iPos<n; iPos++) {
		if (menu.GetMenuItemID(iPos) >= AFX_IDM_FIRST_MDICHILD) {
			bAddSeperator = FALSE;
			break;
		}
	}

	while (iPos < (int)menu.GetMenuItemCount())
		menu.RemoveMenu(iPos, MF_BYPOSITION);

	// get active window so I can check its menu item
	ASSERT(m_hWndMDIClient);
	HWND hwndActive = (HWND)::SendMessage(m_hWndMDIClient,
		WM_MDIGETACTIVE, 0, NULL);

	// append window names in the form "# title"
	// *****fixed by VORGA, thanks!*****
	int iWin;
	int nID = AFX_IDM_FIRST_MDICHILD;
	CString sWinName, sMenuItem;
	HWND hwnd;
	for (iWin = 1; iWin <= 10; iWin++, nID++)
	{
		hwnd = ::GetDlgItem(m_hWndMDIClient, nID);
		if (hwnd == NULL)
			break;

		if (bAddSeperator)
		{
			menu.InsertMenu(iPos++, MF_BYPOSITION | MF_SEPARATOR);
		bAddSeperator = FALSE;
		}

		if (iWin < 10)
		{
			CWnd::FromHandle(hwnd)->GetWindowText(sWinName);
			sMenuItem.Format(_T("&%d %s"), iWin, (LPCTSTR)sWinName);
			menu.InsertMenu(iPos, MF_BYPOSITION, nID, sMenuItem);
			if (hwnd == hwndActive)
				menu.CheckMenuItem(iPos, MF_BYPOSITION | MF_CHECKED);
		}
		else
		{
			menu.InsertMenu(iPos, MF_BYPOSITION, nID, _szMoreWindows);
		}
		iPos++;
	}

	menu.Detach();
}
//******************************************************************
void CMenuBar::OnSetMenu(HMENU hNewMenu, HMENU hWindowMenu)
{
	if (!bIsTabbed)
		ASSERT(m_pMenuIcon && m_pMenuControl);
	// We can get active MDI child window on this message!
	BOOL bMax = FALSE;
	HWND hWndChild = GetActiveChildWnd(bMax);

	if (!m_hWndActiveChild || m_hWndActiveChild != hWndChild) {// an active child window changed
		LTRACE(_T("CMenuBar::OnSetMenu---an active child window changed\n"));
		m_hWndActiveChild = hWndChild;
		// tell MenuIcon child window has been changed
		if (!bIsTabbed)
			m_pMenuIcon->OnActivateChildWnd();
	}

	if (!m_hMenu || m_hMenu != hNewMenu) {	// menu changed
		LTRACE(_T("CMenuBar::OnSetMenu---menu changed\n"));
		LoadMenu(hNewMenu, hWindowMenu);	// set menubar menu
		GetOwner()->SetMenu(NULL);			// clear frame menu
	}
}
//******************************************************************
BOOL CMenuBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{

	CPoint ptCurPos; 
	CRect rc;GetClientRect(rc);
	GetCursorPos (&ptCurPos);
	ScreenToClient (&ptCurPos);
	if (m_dwStyle & CBRS_ORIENT_HORZ)
	{
		rc.right=rc.left+2;
		if (ptCurPos.x< 0)
		{
			SetCursor (LoadCursor(NULL, IDC_SIZEALL));
			return TRUE;
		}
	}
	else
	{
		rc.bottom=rc.top+2;
		if (ptCurPos.y< 0)
		{
			SetCursor (LoadCursor(NULL, IDC_SIZEALL));
			return TRUE;
		}
	}
	return CControlBar::OnSetCursor(pWnd, nHitTest, message);

}

//******************************************************************
void CMenuBar::OnNcPaint() 
{
	EraseNonClientEx();
}
//******************************************************************
UINT CMenuBar::OnNcHitTest(CPoint point) 
{
	// make nonclient area clickable
	return HTCLIENT;
}
//******************************************************************
void CMenuBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// calculate border space (will add to top/bottom, subtract from right/bottom)
	CRect rect; rect.SetRectEmpty();
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	_CalcInsideRect(rect, bHorz);

	if (!(m_dwStyle & CBRS_FLOATING))
	{
		// adjust non-client area for border space
		lpncsp->rgrc[0].left += bHorz?rect.left+4:rect.left+1;
		lpncsp->rgrc[0].top += bHorz?rect.top+4:rect.top+2;
	}
	else
	{
		lpncsp->rgrc[0].left += rect.left;
		lpncsp->rgrc[0].top += rect.top+4;
	}
	lpncsp->rgrc[0].right += rect.right;
	lpncsp->rgrc[0].bottom += rect.bottom;

}
//******************************************************************
void CMenuBar::OnDestroy() 
{
	if(m_bCombo==TRUE)
		cmb->SaveHistory(szNameHistory,bSaveHistory);
	CControlBar::OnDestroy();
	
	// TODO: 
	DeleteItems();
	
	if (m_nIDEvent)
		KillTimer(m_nIDEvent);

		// for SDI application
	if (m_bMDIApp == FALSE && m_hMenu != NULL)
		::FreeResource(m_hMenu);
}
//******************************************************************
void CMenuBar::OnTimer(UINT nIDEvent) 
{
	if (m_nTrackingState == buttonmouse) {
		CPoint pt; ::GetCursorPos(&pt);
		CRect rect;
		GetWindowRect(&rect);

		if (!rect.PtInRect(pt)) {
			UpdateBar();

			if (m_nIDEvent) {
				KillTimer(m_nIDEvent);
				m_nIDEvent = NULL;
			}
		}
	}	

	CControlBar::OnTimer(nIDEvent);
}
//******************************************************************
HWND CMenuBar::GetActiveChildWnd(BOOL& bMaximized)
{
	if (!m_hWndMDIClient)
		return NULL;

	BOOL bMax = FALSE;
	HWND hWnd = (HWND)::SendMessage(m_hWndMDIClient,
		WM_MDIGETACTIVE, 0, (LPARAM)&bMax);
	bMaximized = bMax;

	return hWnd;
}
//******************************************************************
/////////////////////////////////////////////////////////////////////////////
// CMenuBar system hook
void CMenuBar::OnMenuSelect(HMENU hMenu, UINT nIndex)
{
//	LTRACE(_T("CMenuBar::OnMenuSelect\n"));
	if (m_nTrackingState == popup) {
		m_bProcessRightArrow = (::GetSubMenu(hMenu, nIndex) == NULL);
		HMENU hSubMenu = ::GetSubMenu(hMenu, m_nCurIndex);
		if (hSubMenu == NULL)
			return;
		m_bProcessLeftArrow = (hMenu == hSubMenu);
	}
}
//******************************************************************
void CMenuBar::OnFrameNcActivate(BOOL bActive) 
{
	CFrameWnd* pFrame = GetTopLevelFrame();
	ASSERT_VALID(pFrame);

	if (pFrame->m_nFlags & WF_STAYACTIVE)
		bActive = TRUE;
	if (!pFrame->IsWindowEnabled())
		bActive = FALSE;
	if (bActive == m_bFrameActive)
		return;

	if (!bActive) {
		for (int i = 0; i < GetItemCount(); ++i) {
			m_arrItem[i]->ModifyState(0, MISTATE_INACTIVE);
		}
	}
	else {
		for (int i = 0; i < GetItemCount(); ++i) {
			m_arrItem[i]->ModifyState(MISTATE_INACTIVE, 0);
		}
	}

	m_bFrameActive = bActive;

	// InvalidateRect(NULL); is better, but too late
	// while clicking the application title bar (like IE5)
	// so we have to redraw now!

}
//******************************************************************
LRESULT CALLBACK CMenuBar::MenuInputFilter(int code, WPARAM wParam, LPARAM lParam)
{
	return (
		code == MSGF_MENU &&
		g_pMenuBar &&
		g_pMenuBar->OnMenuInput( *((MSG*)lParam) )
		) ? TRUE : CallNextHookEx(g_hMsgHook, code, wParam, lParam);
}
//******************************************************************
void CMenuBar::TrackPopup(int nIndex)
{
	ASSERT_VALID(this);

	m_nCurIndex = nIndex;
	m_bLoop = TRUE;
	while (m_bLoop == TRUE) {
		UpdateWindow();	// force to repaint when button hidden by other window
		UpdateBar(popup, m_nCurIndex);
	
		// install hook
		ASSERT(g_pMenuBar == NULL);
		g_pMenuBar = this;
		ASSERT(g_hMsgHook == NULL);

		m_bLoop = FALSE;
		g_hMsgHook = ::SetWindowsHookEx(WH_MSGFILTER,
			MenuInputFilter, NULL, AfxGetApp()->m_nThreadID);// m_bLoop may become TRUE

		// popup!!
		m_nTrackingState = popup;
		_nPrevIndexForCmd = m_nCurIndex;
		m_arrItem[m_nCurIndex]->TrackPopup(this, GetTopLevelParent());

		// uninstall hook
		::UnhookWindowsHookEx(g_hMsgHook);
		g_hMsgHook = NULL;
		g_pMenuBar = NULL;
	}

	UpdateBar();
}

//******************************************************************
BOOL CMenuBar::OnMenuInput(MSG& m)
{
	ASSERT_VALID(this);
	int nMsg = m.message;
	CPoint pt = m.lParam;
	ScreenToClient(&pt);

	switch (nMsg) {
	case WM_MOUSEMOVE:
		if (pt != m_ptMouse) {
			int nIndex = HitTestOnTrack(pt);
			if ((IsValidIndex(nIndex) && nIndex != m_nCurIndex ) ) {
				// defferent button clicked
			//	Invalidate();
				if (!bActivSystemMenu)
					AfxGetMainWnd()->PostMessage(WM_CANCELMODE); // destroy popupped menu
				if (bActivSystemMenu)
					PostMessage(WM_CANCELMODE);
				UpdateBar(button, nIndex);
				UpdateBar();	
				bActivSystemMenu=FALSE;
				m_nCurIndex = nIndex;
				m_bLoop = TRUE;							// continue loop
			}
			m_ptMouse = pt;
		}
		break;

	case WM_LBUTTONDOWN:
		if ((HitTestOnTrack(pt) != -1 && HitTestOnTrack(pt) == m_nCurIndex)) {
			// same button clicked
			AfxGetMainWnd()->PostMessage(WM_CANCELMODE); // destroy popupped menu
			//PostMessage(WM_CANCELMODE);
			UpdateBar(button, m_nCurIndex);
			m_bLoop = FALSE;						// out of loop
			return TRUE;							// eat it!
		}
		break;
	
	
	case WM_KEYDOWN:	{
		TCHAR vKey = m.wParam;
		if (m_dwStyle & CBRS_ORIENT_VERT) {	// if vertical
			break; // do nothing
		}

		if ((vKey == VK_LEFT  && m_bProcessLeftArrow) ||
			(vKey == VK_RIGHT && m_bProcessRightArrow)) {
			// no submenu
			int nNewIndex = GetNextOrPrevButton(m_nCurIndex, vKey==VK_LEFT);
			AfxGetMainWnd()->PostMessage(WM_CANCELMODE); // destroy popupped menu
			UpdateBar();
			m_nCurIndex = nNewIndex;
			m_bLoop = TRUE;							// continue loop			
			return TRUE;							// eat it!
		}
						}
		break;

	case WM_SYSKEYDOWN:
//		LTRACE(_T("    m_bIgnore = TRUE\n"));
		m_bIgnoreAlt = TRUE;					// next SysKeyUp will be ignored
		break;
	}

	return FALSE;	// pass along...
}

//******************************************************************
BOOL CMenuBar::TranslateFrameMessage(MSG* pMsg)
{
	ASSERT_VALID(this);
	ASSERT(pMsg);

	UINT nMsg = pMsg->message;
	if (WM_LBUTTONDOWN <= nMsg && nMsg <= WM_MOUSELAST) {
		if (pMsg->hwnd != m_hWnd && m_nTrackingState > 0) {
			// clicked outside
			UpdateBar();
		}
	}
	else if (nMsg == WM_SYSKEYDOWN || nMsg == WM_SYSKEYUP || nMsg == WM_KEYDOWN) {
		BOOL bAlt = HIWORD(pMsg->lParam) & KF_ALTDOWN;	// Alt key presed?
		TCHAR vkey = pMsg->wParam;						// + X key
		if (vkey == VK_MENU ||
			(vkey == VK_F10 && !((GetKeyState(VK_SHIFT) & 0x80000000) ||
			                   (GetKeyState(VK_CONTROL) & 0x80000000) || bAlt))) {
			// only alt key pressed
			if (nMsg == WM_SYSKEYUP) {
				switch (m_nTrackingState) {
				case none:
					if (m_bIgnoreAlt == TRUE) {
//						LTRACE(_T("    ignore ALT key up\n"));
						m_bIgnoreAlt = FALSE;
						break;
					}
				
					if (m_bMDIApp) {
						UpdateBar(button, GetNextOrPrevButton(0, FALSE));
					}
					else {
						UpdateBar(button, 0);
					}
					break;
				case button:
					UpdateBar();
					break;
				case buttonmouse:
					break;	// do nothing
				}
			}
			return TRUE;
		}
		else if ((nMsg == WM_SYSKEYDOWN || nMsg == WM_KEYDOWN)) {
			if (m_nTrackingState == button) {
				if (m_dwStyle & CBRS_ORIENT_HORZ) {	// if horizontal
					switch (vkey) {
					case VK_LEFT:
					case VK_RIGHT: {
						int nNewIndex  = GetNextOrPrevButton(m_nCurIndex, vkey == VK_LEFT);
						UpdateBar(button, nNewIndex);
						return TRUE;
								   }
					case VK_SPACE:
					case VK_UP:
					case VK_DOWN:
						TrackPopup(m_nCurIndex);
						return TRUE;

					case VK_ESCAPE:
						UpdateBar();
						return TRUE;
					}
				}
				else {								// if vertical
					switch (vkey) {
					case VK_UP:
					case VK_DOWN:{
						int nNewIndex = GetNextOrPrevButton(m_nCurIndex, vkey == VK_UP);
						UpdateBar(button, nNewIndex);
						return TRUE;
								   }
					case VK_SPACE:
					case VK_RIGHT:
					case VK_LEFT:
						TrackPopup(m_nCurIndex);
						return TRUE;

					case VK_ESCAPE:
						UpdateBar();
						return TRUE;
					}
				}
			}

			// Alt + X pressed
			if ((bAlt || m_nTrackingState == button) && _istalnum(vkey)) {
				int nIndex;
				if (MapAccessKey(vkey, nIndex) == TRUE) {
					UpdateBar(button, nIndex);
					UpdateBar();
					TrackPopup(nIndex);
					return TRUE;		// eat it!
				}
				else if (m_nTrackingState==button && !bAlt) {
//					MessageBeep(0);		// if you want
					return TRUE;
				}
			}

			if (m_nTrackingState > 0) {	// unknown key
				if (m_nTrackingState != buttonmouse) {	// if tracked with mouse, don't update bar
					UpdateBar();
				}
			}
		}
	}
	return FALSE;	// pass along...
}

//******************************************************************
BOOL CMenuBar::MapAccessKey(TCHAR cAccessKey, int& nIndex)
{
	for (int i = 0; i < GetItemCount(); ++i) {
		// fixing point
		TCHAR cKey = m_arrItem[i]->GetAccessKey();
		if (toupper(cKey)/*_totupper(cKey)*/ == cAccessKey) {// *****fixed by andi, thanx!*****
			nIndex = i;
			return TRUE;
		}
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CMenuBar layout
int CMenuBar::GetClipBoxLength(BOOL bHorz)
{
	CFrameWnd* pFrame = GetTopLevelFrame(); ASSERT_VALID(pFrame);
	CRect rcFrame; pFrame->GetWindowRect(rcFrame);

	CWnd* pParent = GetParent(); ASSERT_VALID(pParent);
	CRect rcParent; pParent->GetWindowRect(rcParent);

	const int cxFrameBorder = ::GetSystemMetrics(SM_CXFRAME);
	int cxNonClient = cxFrameBorder*2 + m_cxLeftBorder + m_cxRightBorder;
	if (m_dwExStyle & CBRS_GRIPPER)
		cxNonClient += CX_GRIPPER_ALL;

	if (m_dwStyle & CBRS_SIZE_DYNAMIC) {
		if (bHorz) {
			return rcFrame.Width() - cxNonClient;
		}
		else {
			int nResult = rcParent.Height();
			// I don't know the reason of the following code...
			nResult -= m_cxRightBorder + m_cxLeftBorder + cyBorder2*2;	
			if (m_dwExStyle & CBRS_GRIPPER)
				nResult -= CY_GRIPPER_ALL;

			return nResult;
		}
	}
	else {
		CRect rect; GetClientRect(rect);
		if (bHorz) {
			return rect.Width();
		}
		else {
			return rect.Height();
		}
	}
}

//******************************************************************
CSize CMenuBar::CalcLayout(DWORD dwMode, int nLength)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));
	if (dwMode & LM_HORZDOCK)
		ASSERT(dwMode & LM_HORZ);

	// make SC_CLOSE button disable
	if (m_dwStyle & CBRS_FLOATING) {
		CFrameWnd* pMiniFrame = GetParentFrame(); ASSERT_KINDOF(CMiniFrameWnd, pMiniFrame);
//		Don't do this, cause right click menu turns unavairable
//		pMiniFrame->ModifyStyle(WS_SYSMENU, 0);
		CMenu* pSysMenu = pMiniFrame->GetSystemMenu(FALSE);	ASSERT_VALID(pSysMenu);
		pSysMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
	}

	int nCount = GetItemCount();
	CSize sizeResult(0, 0);

	if (nCount > 0)
	{
		if (!(m_dwStyle & CBRS_SIZE_FIXED))
		{
			BOOL bDynamic = m_dwStyle & CBRS_SIZE_DYNAMIC;

			if (bDynamic && (dwMode & LM_MRUWIDTH))
			{
				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---LM_MRUWIDTH\n"));
				SizeMenuBar(m_nMRUWidth);
				CalcItemLayout(nCount);// added

				sizeResult = CalcSize(nCount);
			}
			else if (bDynamic && (dwMode & LM_HORZDOCK))
			{
				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---LM_HORZDOCK\n"));
				if (IsFloating() || (m_dwStyle & CBRS_ORIENT_VERT)) {
					// I can't synchronize horz size on dragging with size on dock bar
					// as VC++ developer can't.
					SizeMenuBar(32767);
				}
				else {
					// Menu Button wrapped by frame width
					SizeMenuBar(GetClipBoxLength(TRUE));
				}

				CalcItemLayout(nCount);// added
				
				sizeResult = CalcSize(nCount);
				if (!IsFloating() && !(m_dwStyle & CBRS_ORIENT_VERT)) {
					if (m_pDockContext->m_pDC) {// while dragging (m_pDockContext->m_bDragging is helpless)
						sizeResult.cx = GetClipBoxLength(TRUE);
					}
				}
			}
			else if (bDynamic && (dwMode & LM_VERTDOCK))
			{
				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---LM_VERTDOCK\n"));
				//SizeMenuBar(0);
				CalcItemLayout(nCount, TRUE);// added

				sizeResult = CalcVertDockSize(nCount);
				if (!IsFloating() && !(m_dwStyle & CBRS_ORIENT_HORZ)) {
					if (m_pDockContext->m_pDC) {// while dragging
						sizeResult.cy = GetClipBoxLength(FALSE);//GetrcParent.Height() - m_cxRightBorder - m_cxLeftBorder;
					}
				}
			}
			else if (bDynamic && (nLength != -1))
			{
				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---nLength != -1\n"));
				CRect rect; rect.SetRectEmpty();
				_CalcInsideRect(rect, (dwMode & LM_HORZ));
				BOOL bVert = (dwMode & LM_LENGTHY);
				int nLen = nLength + (bVert ? rect.Height() : rect.Width());

				SizeMenuBar(nLen, bVert);
				CalcItemLayout(nCount, bVert);// added

				sizeResult = CalcSize(nCount);
			}
			else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
			{
				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---CBRS_FLOATING\n"));
				SizeMenuBar(m_nMRUWidth);
				CalcItemLayout(nCount);// added

				sizeResult = CalcSize(nCount);
			}
			else
			{
				if (!bDynamic) {
					InvalidateRect(NULL);
					goto Junk;
				}

				LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_DYNAMIC)---other\n"));
				BOOL bVert = !(dwMode & LM_HORZ);
				SizeMenuBar(GetClipBoxLength(TRUE));
				CalcItemLayout(nCount, bVert);// added

				if (bVert) {
					InvalidateRect(NULL);// draw forcefully for captions
					sizeResult = CalcVertDockSize(nCount);
					// DockBar not replaced yet, so I can't get precise size
					sizeResult.cy = 10000;
				}
				else {
					sizeResult = CalcSize(nCount);
					sizeResult.cx = GetClipBoxLength(TRUE);
				}
			}
		}
		else {// CBRS_SIZE_FIXED
			LTRACE(_T("CMenuBar::CalcLayout(CBRS_SIZE_FIXED)\n"));
Junk:
			BOOL bVert = !(dwMode & LM_HORZ);
			SizeMenuBar(32767);
			CalcItemLayout(nCount, bVert);// added

			if (bVert) {
				sizeResult = CalcVertDockSize(nCount);
			}
			else {
				sizeResult = CalcSize(nCount);
			}
		}

		if (dwMode & LM_COMMIT)
		{
			LTRACE(_T("CMenuBar::CalcLayout---LM_COMMIT\n"));
			int nControlCount = 0;
			BOOL bIsDelayed = m_bDelayedButtonLayout;
			m_bDelayedButtonLayout = FALSE;

			if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
				m_nMRUWidth = sizeResult.cx;

			CalcItemLayout(nCount, dwMode);

			m_bDelayedButtonLayout = bIsDelayed;
		}
	}

	//BLOCK: Adjust Margins
	{
		CRect rect; rect.SetRectEmpty();
		_CalcInsideRect(rect, (dwMode & LM_HORZ));
		sizeResult.cy -= rect.Height();
		sizeResult.cx -= rect.Width();
		CSize size = CControlBar::CalcFixedLayout((dwMode & LM_STRETCH), (dwMode & LM_HORZ));
		sizeResult.cx = max(sizeResult.cx, size.cx);
		sizeResult.cy = max(sizeResult.cy, size.cy);
	}
	
	if (dwMode & LM_HORZ)

		sizeResult.cy+=5;
	else
		sizeResult.cx+=3;

	return sizeResult;
}

//******************************************************************
CSize CMenuBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	LTRACE(_T("CMenuBar::CalcFixedLayout\n"));
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));

	DWORD dwMode = bStretch ? LM_STRETCH : 0;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout(dwMode);
}
//******************************************************************

CSize CMenuBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	LTRACE(_T("CMenuBar::CalcDynamicLayout\n"));
	if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
		((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
	{
		LTRACE(_T("    FixedLayout\n"));
		return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
	}
	return CalcLayout(dwMode, nLength);
}

// set m_bWrapped by nWidth
int CMenuBar::WrapMenuBar(int nCount, int nWidth)
{
//	LTRACE(_T("CMenuBar::WrapMenuBar\n"));
	int nResult = 0;
	int x = 0;

	for (int i = 0; i < nCount; ++i) {
		CMenuItem* pItem = m_arrItem[i];
		if (i+1 == nCount)
			return ++nResult;
		
		if (x + pItem->GetHorizontalSize().cx> nWidth) {// itself is over
			if (pItem->GetStyle() & MISTYLE_WRAPPABLE) {
				pItem->ModifyState(0, MISTATE_WRAP);
				++nResult;
				x = 0;
			}
		}
		else if (x + pItem->GetHorizontalSize().cx + 
				 m_arrItem[i+1]->GetHorizontalSize().cx> nWidth) {
			if (pItem->GetStyle() & MISTYLE_WRAPPABLE) {
				pItem->ModifyState(0, MISTATE_WRAP);
				++nResult;
				x = 0;
			}
		}
		else {
			pItem->ModifyState(MISTATE_WRAP, 0);
			x += pItem->GetHorizontalSize().cx;
		}
	}

	return nResult + 1;
}
//******************************************************************
// calc only size, by using m_bWrapped
CSize CMenuBar::CalcSize(int nCount)
{
	ASSERT(nCount > 0);
	CPoint cur(0,0);
	CSize sizeResult(0,0);
	int nWrap = 0;
	for (int i = 0; i < nCount; ++i) {
		CMenuItem* pItem = m_arrItem[i];
		sizeResult.cx = max(cur.x + pItem->GetHorizontalSize().cx, sizeResult.cx);
		sizeResult.cy = max(cur.y + pItem->GetHorizontalSize().cy, sizeResult.cy);

		cur.x += pItem->GetHorizontalSize().cx;
		
		if (pItem->GetState() & MISTATE_WRAP) {
			//LTRACE(_T("    nIndex:%d is wrapped\n"), i);
			cur.x = 0;// reset x pos
			cur.y += pItem->GetHorizontalSize().cy;
			++nWrap;
		}
	}

	return sizeResult;
}
//******************************************************************
void CMenuBar::Layout()
{
	ASSERT(m_bDelayedButtonLayout);

	m_bDelayedButtonLayout = FALSE;

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
		((CMenuBar*)this)->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH | LM_COMMIT);
	else if (bHorz)
		((CMenuBar*)this)->CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK | LM_COMMIT);
	else
		((CMenuBar*)this)->CalcDynamicLayout(0, LM_VERTDOCK | LM_COMMIT);
}
//******************************************************************
void CMenuBar::SizeMenuBar(int nLength, BOOL bVert)
{
	//LTRACE("CMenuBar::SizeMenuBar\n");
	int nCount = GetItemCount(); ASSERT(nCount > 0);

	if (!bVert) {				// nLength is horizontal length

		if (IsFloating()) {		// half size wrapping

			CSize sizeMax, sizeMin, sizeMid;

			// Wrap MenuBar vertically
			WrapMenuBar(nCount, 0);
			sizeMin = CalcSize(nCount);

			// Wrap MenuBar horizontally
			WrapMenuBar(nCount, 32767);
			sizeMax = CalcSize(nCount);

			// we can never understand this algorithm :), see CToolBar implementation
			while (sizeMin.cx < sizeMax.cx) {
//				LTRACE("looping sizeMin.cx:%d < sizeMax.cx:%d\n", sizeMin.cx, sizeMax.cx);
				sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;
				WrapMenuBar(nCount, sizeMid.cx);
				sizeMid = CalcSize(nCount);
				if (sizeMid.cx == sizeMax.cx) {	// if you forget, it loops forever!
					return;
				}
//				LTRACE("    sizeMid : %d %d\n", sizeMid.cx, sizeMid.cy);

				if (nLength >= sizeMax.cx) {
//					LTRACE("    nLength:%d >= sizeMax.cx:%d\n", nLength, sizeMax.cx);
					if (sizeMin == sizeMid) {
						WrapMenuBar(nCount, sizeMax.cx);
//						LTRACE("out SizeMenuBar\n");
						return;
					}
					sizeMin = sizeMid;
				}
				else if (nLength < sizeMax.cx) {
//					LTRACE("    nLength:%d < sizeMax.cx:%d\n", nLength, sizeMax.cx);
					sizeMax = sizeMid;
				}
				else {
//					LTRACE("out SizeMenuBar\n");
					return;
				}
			}
		}
		else {								// each one wrapping
			//LTRACE("    just each one wrapping\n");
			WrapMenuBar(nCount, nLength);
		}
	}
	else {						// nLength is vertical length
		CSize sizeMax, sizeMin, sizeMid;

		// Wrap MenuBar vertically
		WrapMenuBar(nCount, 0);
		sizeMin = CalcSize(nCount);

		// Wrap MenuBar horizontally
		WrapMenuBar(nCount, 32767);
		sizeMax = CalcSize(nCount);

		while (sizeMin.cx < sizeMax.cx) {
			sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;
			WrapMenuBar(nCount, sizeMid.cx);
			sizeMid = CalcSize(nCount);
			if (sizeMid.cx == sizeMax.cx) {
				return;
			}
			if (nLength < sizeMid.cy) {
				if (sizeMin == sizeMid) {
					WrapMenuBar(nCount, sizeMax.cx);
					//LTRACE("out SizeMenuBar\n");
					return;
				}
				sizeMin = sizeMid;
			}
			else if (nLength > sizeMid.cy)
				sizeMax = sizeMid;
			else {
				//LTRACE("out SizeMenuBar\n");
				return;
			}
		}
	}

	//LTRACE("out SizeMenuBar\n");
}
//***********************************************************************************
void CMenuBar::DrawCombo()
{
	CRect rect;
	GetClientRect(rect);
	CalcSizeItem();
	CWnd* pFrame = GetTopLevelFrame();
	BOOL bMaximized = FALSE;	
	//la idea es verificar que la ventana es MDI
	if (pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)))
	{
		ASSERT_VALID(pFrame);
		CMDIFrameWnd* pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pFrame);
		HWND hWndMDIClient = pMDIFrame->m_hWndMDIClient;
		ASSERT(::IsWindow(hWndMDIClient));
		HWND hWndChild = (HWND)::SendMessage(hWndMDIClient,
			WM_MDIGETACTIVE, 0, (LPARAM)&bMaximized);
	}
	if ((m_dwStyle & CBRS_ORIENT_HORZ) && m_bCombo==TRUE && !(m_dwStyle & CBRS_FLOATING))
	{
		CRect reccombo;
		cmb->GetClientRect (&reccombo);
		if (rect.Width() > m_sizex+(bMaximized?30:0)+reccombo.Width() )
		{
			cmb->ShowWindow(SW_SHOW);				
			CRect rctemp=rect;
			rctemp.top=-1;
			rctemp.bottom-=2;
			int nDif;
			if (!bIsTabbed)
			   nDif=bMaximized?60:0;
			else
			   nDif=0;	
			rctemp.left=rctemp.right-reccombo.Width()-  nDif;
			rctemp.right=rctemp.left+reccombo.Width();
			cmb->MoveWindow(rctemp);	
		}
		else
		{
			cmb->ShowWindow(SW_HIDE);
		}
	}	

}

//******************************************************************
void CMenuBar::CalcSizeItem()
{
	m_sizex=0;
	for(int i = 0; i < m_arrItem.GetSize(); ++i) {
		CMenuItem* pItem = m_arrItem[i];
		m_sizex+=pItem->GetRect().Width();
	}

}

//******************************************************************
CSize CMenuBar::CalcVertDockSize(int nCount)
{
	ASSERT(nCount > 0);
	CSize sizeResult(0, 0);
	
	for (int i = 0; i < nCount; ++i) {
		CMenuItem* pItem = m_arrItem[i];
		sizeResult.cy += pItem->GetRect().Height();
	}

	sizeResult.cx = _cyMenuOnBar;
	return sizeResult;
}

//******************************************************************
void CMenuBar::CalcItemLayout(int nCount, BOOL bVert)
{
	ASSERT(nCount > 0);
	int x = 0; int y = 0;

	if (!bVert) {
		for (int i = 0; i < nCount; ++i) {
			CMenuItem* pItem = m_arrItem[i];
			CPoint ptItem(x, y);
			pItem->Layout(ptItem, TRUE);// layout by itself!
			if (pItem->GetState() & MISTATE_WRAP) {
				x = 0;// reset x to 0
				y += pItem->GetRect().Height();
			}
			else
				x += pItem->GetRect().Width();
		}		
	}
	else {
		for (int i = 0; i < nCount; ++i) {
			CMenuItem* pItem = m_arrItem[i];
			CPoint	ptItem(0, y);
			pItem->Layout(ptItem, FALSE);	// layout by itself
			y += pItem->GetRect().Height();
		}
	}
}
//******************************************************************
//////////////////////////////////////////////////////////////////////
// Added by Koay Kah Hoe. Thanx!
void CMenuBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	if (m_bMDIApp)
		CheckActiveChildWndMaximized();
}
//******************************************************************
//////////////////////////////////////////////////////////////////////
// CMenuBar decoration

void CMenuBar::_DrawGripper(CWindowDC* dc,CRect* rcWin)
{


	if (m_dwStyle & CBRS_FLOATING) return ;
	if(m_StyleDisplay == GUISTYLE_2003) //no es XP
	{
		if (m_dwStyle & CBRS_ORIENT_HORZ)
		{
			rcWin->top+=(rcWin->Height()/2)-4;
			rcWin->left+=7;
			rcWin->right=rcWin->left+2;
			rcWin->bottom-=8;
			CRect rcBlack;
	
			for (int i=0; i < rcWin->Height(); i+=4)
			{
				CRect rcWindow;
				CBrush cb;
				cb.CreateSolidBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
				rcWindow=rcWin;
				rcWindow.top=rcWin->top+i;
				rcWindow.bottom=rcWindow.top+2;
				dc->FillRect(rcWindow,&cb);
				rcBlack=rcWindow;
				rcBlack.left-=1;
				rcBlack.top=(rcWin->top+i)-1;
				rcBlack.bottom=rcBlack.top+2;
				rcBlack.right=rcBlack.left+2;
				cb.DeleteObject();
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorShadow(m_StyleDisplay));
				dc->FillRect(rcBlack,&cb);
		
			}
			
			
		}
		else
		{

			rcWin->top+=3;
			rcWin->left+=4;
			rcWin->right-=2;
			rcWin->bottom=rcWin->top+2;
			CRect rcBlack;
			for (int i=0; i < rcWin->Width(); i+=4)
			{
				CRect rcWindow;
				CBrush cb;
				cb.CreateSolidBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
				rcWindow=rcWin;
				rcWindow.left=rcWindow.left+i;
				rcWindow.right=rcWindow.left+2;
				dc->FillRect(rcWindow,&cb);
				rcBlack=rcWindow;
				rcBlack.top-=1;
				rcBlack.left-=1;
				rcBlack.bottom=rcBlack.top+2;
				rcBlack.right=rcBlack.left+2;
				cb.DeleteObject();
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorShadow(m_StyleDisplay));
				dc->FillRect(rcBlack,&cb);
		
			}
		}
	}
	else
	{
		if (m_dwStyle & CBRS_ORIENT_HORZ)
			{
				
				rcWin->top+=(rcWin->Height()/2)-4;
				rcWin->left+=7;
				rcWin->right=rcWin->left+3;
				rcWin->bottom-=6;

				for (int i=0; i < rcWin->Height(); i+=2)
				{
					CRect rcWindow;
					CBrush cb;
					cb.CreateSolidBrush(::GetSysColor(COLOR_BTNSHADOW));
					rcWindow=rcWin;
					rcWindow.top=rcWin->top+i;
					rcWindow.bottom=rcWindow.top+1;
					dc->FillRect(rcWindow,&cb);
			
				}
				
			}
			else
			{
				rcWin->top+=2;
				rcWin->left+=2;
				rcWin->right-=2;
				rcWin->bottom=rcWin->top+3;
				for (int i=0; i < rcWin->Width(); i+=2)
				{
					CRect rcWindow;
					CBrush cb;
					cb.CreateSolidBrush(::GetSysColor(COLOR_BTNSHADOW));
					rcWindow=rcWin;
					rcWindow.left=rcWindow.left+i;
					rcWindow.right=rcWindow.left+1;
					dc->FillRect(rcWindow,&cb);
			
				}

			}
	}

}

//******************************************************************
void CMenuBar::EraseNonClientEx()
{
	// get window DC that is clipped to the non-client area
	
	CRect rcWindow;
	CRect rcClient;
	CWindowDC	dc(this);
	GetWindowRect(&rcWindow);
	GetClientRect(&rcClient);
	CBrush cbr;
	cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	rcClient.OffsetRect(-rcWindow.TopLeft());
    rcWindow.OffsetRect(-rcWindow.TopLeft());
    ScreenToClient(rcWindow);
	rcClient.OffsetRect(-rcWindow.left, - rcWindow.top);
	dc.ExcludeClipRect(rcClient);   
	rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);
	int ibotton = rcWindow.bottom;
	rcWindow.top = rcWindow.bottom - 1;
	dc.FillRect(rcWindow, &cbr); 
	rcWindow.top = 0;
	rcWindow.bottom += 3;
	dc.FillRect(rcWindow, &cbr); 
	dc.FillSolidRect(0, rcWindow.top + 1, rcWindow.right + 1, 1, 
		GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style)); 
	cbr.DeleteObject();


	// draw gripper in non-client area
	_DrawGripper(&dc, &rcWindow);
}

#define CX_BORDER   1
#define CY_BORDER   1
//******************************************************************
void CMenuBar::DrawRaisedBorders(CDC* pDC, CRect& rect)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	DWORD dwStyle = m_dwStyle;
	if (!(dwStyle & CBRS_BORDER_ANY))
		return;

	// prepare for dark lines
	ASSERT(rect.top == 0 && rect.left == 0);
	CRect rect1, rect2;
	rect1 = rect;
	rect2 = rect;
	COLORREF clrBtnShadow = GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style);//afxData.bWin4 ? afxData.clrBtnShadow : afxData.clrWindowFrame;
	COLORREF clrBtnFace = GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	COLORREF clrBtnHilight = ::GetSysColor(COLOR_BTNHILIGHT);

	// draw dark line one pixel back/up
	if (dwStyle & CBRS_BORDER_3D)
	{
		rect1.right -= CX_BORDER;
		rect1.bottom -= CY_BORDER;
	}
	if (dwStyle & CBRS_BORDER_TOP)
		rect2.top += cyBorder2;
	if (dwStyle & CBRS_BORDER_BOTTOM)
		rect2.bottom -= cyBorder2;

	// draw left and top
	if (dwStyle & CBRS_BORDER_LEFT)
		pDC->FillSolidRect(0, rect2.top, CX_BORDER, rect2.Height(), clrBtnFace);
	if (dwStyle & CBRS_BORDER_TOP)
		pDC->FillSolidRect(0, 0, rect.right, CY_BORDER, clrBtnFace);

	// draw right and bottom
	if (dwStyle & CBRS_BORDER_RIGHT)
		pDC->FillSolidRect(rect1.right, rect2.top, -CX_BORDER, rect2.Height(), clrBtnShadow);
	if (dwStyle & CBRS_BORDER_BOTTOM)
		pDC->FillSolidRect(0, rect1.bottom, rect.right, -CY_BORDER, clrBtnShadow);

	if (dwStyle & CBRS_BORDER_3D)
	{
		// draw left and top
		if (dwStyle & CBRS_BORDER_LEFT)
			pDC->FillSolidRect(1, rect2.top, CX_BORDER, rect2.Height(), clrBtnHilight);
		if (dwStyle & CBRS_BORDER_TOP)
			pDC->FillSolidRect(0, 1, rect.right, CY_BORDER, clrBtnHilight);

		// draw right and bottom
		if (dwStyle & CBRS_BORDER_RIGHT)
			pDC->FillSolidRect(rect.right, rect2.top, -CX_BORDER, rect2.Height(), clrBtnFace);
		if (dwStyle & CBRS_BORDER_BOTTOM)
			pDC->FillSolidRect(0, rect.bottom, rect.right, -CY_BORDER, clrBtnFace);
	}

	if (dwStyle & CBRS_BORDER_LEFT)
		rect.left += cxBorder2;
	if (dwStyle & CBRS_BORDER_TOP)
		rect.top += cyBorder2;
	if (dwStyle & CBRS_BORDER_RIGHT)
		rect.right -= cxBorder2;
	if (dwStyle & CBRS_BORDER_BOTTOM)
		rect.bottom -= cyBorder2;		
}

//******************************************************************
int CMenuBar::GetNextOrPrevButton(int nIndex, BOOL bPrev)
{
	int nCount = GetItemCount();
	if (bPrev) {				// <-
		--nIndex;
		if (nIndex < 0)
			nIndex = nCount - 1;
	}
	else {						// ->
		++nIndex;
		if (nIndex >= nCount)
			nIndex = 0;
	}

	if (!(m_arrItem[nIndex]->GetStyle() & MISTYLE_TRACKABLE) ||
		(m_arrItem[nIndex]->GetState() & MISTATE_HIDDEN)) {
		return GetNextOrPrevButton(nIndex, bPrev);
	}

	return nIndex;
}

//******************************************************************
/////////////////////////////////////////////////////////////////////////////
// CMenuBar OLE menu support
//		MFC does'nt do command routing for other process server.
//		::TrackPopupMenuEx won't accept HWND of other process and
//		we have to determine a message target(ole server window or not)
//		as ::OleCreateMenuDescriptor do.
//		This is a hard coding. 
//		First menu(ordinarily File menu) and WindowMenu regarded as container's own menu.
//		Some components can't update toolbar button and statusbar pane.
HWND CMenuBar::OleMenuDescriptor(BOOL& bSend, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CWnd* pOleWnd = GetCmdSentOleWnd();
	if (pOleWnd == NULL)
		return NULL;
	HWND hWndSentCmd = NULL;

	HMENU hMenu = NULL;
	if (nMsg == WM_INITMENUPOPUP || nMsg == WM_INITMENU)
		hMenu = (HMENU)wParam;
	else if (nMsg == WM_MENUSELECT)
		hMenu = (HMENU)lParam;

	switch (nMsg) {
	case WM_INITMENUPOPUP:
	case WM_INITMENU:
	case WM_MENUSELECT:
		bSend = TRUE;
		if (m_nTrackingState == popup) {
			LTRACE2(_T("    now popup\n"));
			if (m_bMDIApp) {
				LTRACE2(_T("    this is MDI\n"));
				if (m_nCurIndex == 0 || m_nCurIndex == 1 || hMenu == m_hWindowMenu) {
					LTRACE2(_T("    it's container menu, send to frame\n"));
					return NULL;
				}
			}
			else {
				LTRACE2(_T("    it's container menu, send to frame\n"));
				if (m_nCurIndex == 0) {
					return NULL;
				}
			}
			LTRACE2(_T("    it's server menu, send to server\n"));
			return pOleWnd->GetSafeHwnd();
		}
		break;

	case WM_COMMAND:
		bSend = FALSE;
		if (m_bMDIApp) {
			LTRACE2(_T("    this is MDI\n"));
			if (_nPrevIndexForCmd == 0 || _nPrevIndexForCmd == 1 || _bWindowMenuSendCmd) {
				LTRACE2(_T("    it's container menu, send to frame\n"));
				return NULL;
			}
		}
		else {
			if (_nPrevIndexForCmd == 0) {
				LTRACE2(_T("    it's container menu, send to frame\n"));
				return NULL;
			}
		}
		LTRACE2(_T("    it's server menu, send to server\n"));
		return pOleWnd->GetSafeHwnd();
	}

	return NULL;// send to frame
}
//******************************************************************
CWnd* CMenuBar::GetCmdSentOleWnd()
{
	// *****fixed by VORGA, thanks!*****
	CWnd* pWnd = AfxGetMainWnd();
	if (pWnd == NULL || !pWnd->IsFrameWnd())
		return NULL;
	
	CFrameWnd* pFrame = NULL;
	if (m_bMDIApp) {
		CMDIFrameWnd *pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pWnd);
		if (pMDIFrame == NULL)
			return NULL;
		pFrame = pMDIFrame->GetActiveFrame();
	}
	else {
		pFrame = STATIC_DOWNCAST(CFrameWnd, pWnd);
	}

	if (pFrame == NULL)
		return NULL;

	CDocument* pDoc = pFrame->GetActiveDocument();
	if (pDoc != NULL && pDoc->IsKindOf(RUNTIME_CLASS(COleDocument))) {
		COleDocument* pOleDoc = STATIC_DOWNCAST(COleDocument, pDoc);
		ASSERT_VALID(pOleDoc);
		COleClientItem* pClientItem = pOleDoc->GetInPlaceActiveItem(pFrame);
		CWnd* pWnd = (pClientItem == NULL) ? NULL : pClientItem->GetInPlaceWindow();
		if (pWnd != NULL) {
			return pWnd;
		}
	}

	return NULL;
}
//******************************************************************
/////////////////////////////////////////////////////////////////////////////
// CMDIClientHook 
CMDIClientHook::CMDIClientHook()
{
	m_pMenuBar = NULL;
}
//******************************************************************
BOOL CMDIClientHook::Install(CMenuBar* pMenuBar, HWND hWndToHook)
{
	ASSERT_VALID(pMenuBar);
	ASSERT(m_pMenuBar == NULL);
	m_pMenuBar = pMenuBar;
	return HookWindow(hWndToHook);
}
//******************************************************************
CMDIClientHook::~CMDIClientHook()
{
		HookWindow((HWND)NULL);
}
//******************************************************************
LRESULT CMDIClientHook::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT_VALID(m_pMenuBar);

	switch (nMsg) {
	case WM_MDISETMENU:			// only sent to MDI client window
		// Setting new frame/window menu: bypass MDI. wParam is new menu.
		if (wParam) {
			//LTRACE(_T("CMenuBar::WM_MDISETMENU 0x%04x\n"), wParam);
			m_pMenuBar->OnSetMenu((HMENU)wParam, (HMENU)lParam);
		}
		return 0;

	case WM_MDIREFRESHMENU:		// only sent to MDI client window
		// Normally, would call DrawMenuBar, but I have the menu, so eat it.
		//LTRACE(_T("CMenuBar::WM_MDIREFRESHMENU\n"));
		return 0;

	}

	return CSubclassWnd::WindowProc(nMsg, wParam, lParam);
}
//******************************************************************
/////////////////////////////////////////////////////////////////////////////
// CMainFrameHook 
CMainFrameHook::CMainFrameHook()
{
	m_pMenuBar = NULL;
}

//******************************************************************
BOOL CMainFrameHook::Install(CMenuBar* pMenuBar, HWND hWndToHook)
{
	ASSERT_VALID(pMenuBar);
	ASSERT(m_pMenuBar == NULL);
	m_pMenuBar = pMenuBar;
	return HookWindow(hWndToHook);
}

//******************************************************************
CMainFrameHook::~CMainFrameHook()
{
}

//******************************************************************
LRESULT CMainFrameHook::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT_VALID(m_pMenuBar);
	// be care for other windows(MainFrame) hooking
	// possible called when already this wnd destroyed (WM_NCACTIVATE is)
	if (!::IsWindow(m_pMenuBar->m_hWnd)) {
		return CSubclassWnd::WindowProc(nMsg, wParam, lParam);
	}

	BOOL bSend = FALSE;
	if (HWND hWndServer = m_pMenuBar->OleMenuDescriptor(bSend, nMsg, wParam, lParam)) {
		// OLE wnd will handle message
		if (bSend)
			return ::SendMessage(hWndServer, nMsg, wParam, lParam);
		else
			return ::PostMessage(hWndServer, nMsg, wParam, lParam);
	}

	switch (nMsg) {
	case WM_MENUSELECT:
		m_pMenuBar->OnMenuSelect((HMENU)lParam, (UINT)LOWORD(wParam));
		break;

	case WM_INITMENUPOPUP:
		if (!HIWORD(lParam) && (HMENU)wParam == m_pMenuBar->m_hWindowMenu)
			m_pMenuBar->OnInitMenuPopup(CMenu::FromHandle((HMENU)wParam),
				LOWORD(lParam), (BOOL)HIWORD(lParam));
		break;

	case WM_NCACTIVATE:
		m_pMenuBar->OnFrameNcActivate((BOOL)wParam);
		break;
	
	case WM_SYSCOLORCHANGE:
	case WM_SETTINGCHANGE:
		LTRACE(_T("CMenuBar::WM_SETTINGCHANGE\n"));
		// It's enough to reinitialize common resources once.
		m_pMenuBar->OnSettingChange(wParam, lParam);
		break;
	}

	if (nMsg == CMenuBar::WM_GETMENU)
		return (LRESULT)m_pMenuBar->m_hMenu;

	return CSubclassWnd::WindowProc(nMsg, wParam, lParam);
}





//******************************************************************
//////////////////////////////////////////////////////////////////////
// CMenuItem interface
CMenuItem::CMenuItem()
{
	m_fsStyle = 0;
	m_fsState = 0;
	m_rcItem.SetRectEmpty();
	m_sizeHorz = CSize(0, 0);
	m_cAccessKey = 0;
}
//******************************************************************
void CMenuItem::ModifyState(BYTE fsRemove, BYTE fsAdd)
{
	m_fsState = (m_fsState & ~fsRemove) | fsAdd;
}

//******************************************************************
CSize CMenuItem::GetHorizontalSize() const
{
	if (m_fsState & MISTATE_HIDDEN)
		return CSize(0, 0);
	else
		return m_sizeHorz;
}


//-----------------------------------------------------------------
CGuiMenuButton::CGuiMenuButton()
{
	m_bHorz=TRUE;
}

CGuiMenuButton::~CGuiMenuButton()
{
}


void CGuiMenuButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC*  pdc= CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc=lpDrawItemStruct->rcItem;
	UINT  uState=lpDrawItemStruct->itemState;
	CBrush cb;
	
	if( uState & ODS_SELECTED) //the button is pressed
		cb.CreateSolidBrush(GuiDrawLayer::GetRGBPressBXP());
	else
		if (m_bMouserOver)
		{
			if(m_StyleDisplay==GUISTYLE_2003)
			{
				if (GuiDrawLayer::m_Theme)
				{
					CGradient M(CSize(rc.Width(),rc.Height()));	
					M.PrepareCaption(pdc,m_StyleDisplay);
					M.Draw(pdc,rc.left,rc.top,0,0,rc.Width(),rc.Height(),SRCCOPY);	
					cb.CreateStockObject(NULL_BRUSH);
				}
				else
					cb.CreateSolidBrush(GuiDrawLayer::GetRGBFondoXP());
			}
			else
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBFondoXP());
		}
		else
		{
			if(m_StyleDisplay==GUISTYLE_2003)
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(m_StyleDisplay));
			else
				cb.CreateSolidBrush(m_clColor);
		}
			
	
	
	if (( uState == ODS_SELECTED) || m_bMouserOver )
	{
		pdc->Draw3dRect(rc,GuiDrawLayer::GetRGBCaptionXP(),GuiDrawLayer::GetRGBCaptionXP());
		rc.DeflateRect(1,1);
		
	}

	
	pdc->FillRect(rc,&cb);
	if (m_SizeText.cx > 2)
	{

		
		int nMode = pdc->SetBkMode(TRANSPARENT);
	
		if (m_bHorz)
		{
			CRect rectletra=rc;
			CPoint pt=CSize(rectletra.top+1,rectletra.left);
			if (uState & ODS_DISABLED)
				pdc->DrawState(pt, m_SizeText, m_szText, DSS_DISABLED, TRUE, 0, (CBrush*)NULL);
			else
			{
				if(m_bMouserOver != 1) 
					pdc->SetTextColor(m_clrFont);
				pdc->DrawText(m_szText,rectletra,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			}
		}
		else
		{
			if (( uState == ODS_SELECTED) || m_bMouserOver )
				rc.InflateRect(1,1);
			
			COLORREF clr = ::GetSysColor(COLOR_MENUTEXT);
			pdc->SetTextColor(clr);
			CPoint ptOffset=CPoint(1,1);
			CRect rcBtn = rc;
			int nLength = m_szText.GetLength();
			int nIndex = m_szText.Find('&');
			CString strBtn = m_szText.Left(nIndex) + m_szText.Right(nLength - (nIndex+1));
			
			// fixed for WinNT. *****fixed by Simon, thanks!*****
			int iGraphicsMode = ::GetGraphicsMode(pdc->m_hDC);
			::SetGraphicsMode(pdc->m_hDC, GM_ADVANCED);
			pdc->SetBkMode(TRANSPARENT);
			CFont* pOldFont = pdc->SelectObject(&_fontVertMenu);
			// I know precise text size
			//m_sizeHorz=((CMenuBar*)GetParent())->m_sizeHors;
			CSize m_sizeHorz;
			m_sizeHorz.cx = (_CalcTextWidth(m_szText) + CXTEXTMARGIN*2)+8;
			m_sizeHorz.cy = (_cyHorzFont + _cyTextMargin*2)+1;
			CRect rcString = CRect(
				CPoint(rcBtn.right - _cyTextMargin, rcBtn.top + CXTEXTMARGIN), m_sizeHorz);
			pdc->DrawText(strBtn, rcString + ptOffset,
				DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX);// don't forget DT_NOCLIP
			gbintHorz=-1;
			rcMenu=rcBtn;
			rcMenu.bottom-=3;
			pdc->SelectObject(pOldFont);
			
			// CDC::DrawText is poor, so we have to draw vertical line by ourselves
			CPen pen(PS_SOLID, 0, clr);
			CPen* pOldPen = pdc->SelectObject(&pen);
			
			CPoint m_ptLineFrom;
			CPoint m_ptLineTo;
			if (nIndex == 0) {
				m_ptLineFrom = CPoint(_cyTextMargin-1, CXTEXTMARGIN+1);
				m_ptLineTo	 = CPoint(_cyTextMargin-1, CXTEXTMARGIN + _CalcTextWidth(strBtn.Left(nIndex+1)));
			}
			else {
				m_ptLineFrom = CPoint(_cyTextMargin-1, CXTEXTMARGIN + _CalcTextWidth(strBtn.Left(nIndex+1)));
				m_ptLineTo = CPoint(_cyTextMargin-1, CXTEXTMARGIN + _CalcTextWidth(strBtn.Left(nIndex+1)));
			}

			pdc->MoveTo(rcBtn.TopLeft() + m_ptLineFrom);
			pdc->LineTo(rcBtn.TopLeft() + m_ptLineTo );

			pdc->SelectObject(pOldPen);
			::SetGraphicsMode( pdc->m_hDC, iGraphicsMode );
		}
	}
	
}

BEGIN_MESSAGE_MAP(CGuiMenuButton,CGuiToolButton)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CGuiMenuButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	ShowWindow(SW_HIDE);
	ClientToScreen(&point);
	GetParent()->SendMessage(WM_LBUTTONDOWN,100+GetDlgCtrlID(),MAKEWPARAM(point.x,point.y));
}


CGuiIconButton::CGuiIconButton()
{
}

CGuiIconButton::~CGuiIconButton()
{
	::FreeResource(m_Icon);
}

void CGuiIconButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC*  pdc= CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc=lpDrawItemStruct->rcItem;
	UINT  uState=lpDrawItemStruct->itemState;
	CBrush cb;
	
	cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	pdc->FillRect(rc,&cb);

	CPoint m_point=CPoint(1,1);
	if (m_SizeImage.cx > 2)
	{
		
		pdc->DrawState (m_point, m_SizeImage,m_Icon,
					(uState==ODS_DISABLED?DSS_DISABLED:DSS_NORMAL),(CBrush*)NULL);
	}
}

BEGIN_MESSAGE_MAP(CGuiIconButton,CGuiToolButton)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CGuiIconButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	GetParent()->SendMessage(WM_LBUTTONDOWN,1000,MAKEWPARAM(point.x,point.y));
}

//-----------------------------------------------------------------


//******************************************************************
//////////////////////////////////////////////////////////////////////
// CMenuButton class	
CMenuButton::CMenuButton(HMENU hMenu, int nIndex,CWnd* pWnd)
{
	ASSERT(::IsMenu(hMenu));
	ASSERT(nIndex >= 0);
	pParent=pWnd;
	m_cfont.CreateFont(-11,0,0,0,400,0,0,0,0,1,2,1,34,"MS Sans Serif");
	m_fsStyle |= (MISTYLE_TRACKABLE | MISTYLE_WRAPPABLE);
	m_bt.Create(_T(""), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
		CRect(0,0,0,0), pWnd, nIndex);
	
	m_bt.SetFont(&_fontHorzMenu);
	m_bt.StyleDispl(GuiDrawLayer::m_Style);
	m_bt.SetColor(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	InitButtonStringAndSubMenuHandle(hMenu, nIndex);
	InitHorizontalButtonSize();
	InitAccessKeyAndVerticalLinePoint();
}


//******************************************************************
// ERNESTO
void	CMenuButton::SetText(TCHAR *szText)
{
		m_strBtn  = szText;
		InitHorizontalButtonSize();
		InitAccessKeyAndVerticalLinePoint();

}

//******************************************************************
void CMenuButton::InitButtonStringAndSubMenuHandle(HMENU hMenu, int nIndex)
{
	// get menu button Text
	TCHAR szText[256];
	MENUITEMINFO info; ::memset(&info, 0, sizeof(MENUITEMINFO));
	info.cbSize		= sizeof(MENUITEMINFO);
	info.fMask		= MIIM_ID | MIIM_TYPE;
	info.dwTypeData = szText;
	info.cch		= sizeof(szText);
	::GetMenuItemInfo(hMenu, nIndex, TRUE, &info);
	m_strBtn = CString(szText);
	
	m_bt.SetCaption(m_strBtn);
	m_hSubMenu = ::GetSubMenu(hMenu, nIndex);
	if (!m_hSubMenu) {
		m_nID = ::GetMenuItemID(hMenu, nIndex);
		ASSERT(m_nID != -1);
	}
	else {
		m_nID = -1;
	}
}

//******************************************************************
void CMenuButton::InitHorizontalButtonSize()
{
	// get menu button Text size
	ASSERT(m_strBtn.IsEmpty() == FALSE);
	m_sizeHorz.cx = (_CalcTextWidth(m_strBtn) + CXTEXTMARGIN*2)+8;
	m_sizeHorz.cy = (_cyHorzFont + _cyTextMargin*2)+1;
}

//******************************************************************
void CMenuButton::InitAccessKeyAndVerticalLinePoint()
{
	int nIndex = m_strBtn.Find('&');
	if (nIndex + 1 == m_strBtn.GetLength()) {
		TRACE(_T("warning : & is bad position, access key is invalid.\n"));
		m_cAccessKey = 0;
		m_ptLineFrom = m_ptLineTo = CPoint(0, 0);
		return;
	}
	
	m_cAccessKey = m_strBtn[nIndex + 1];// -1 + 1 = 0; it's ok

	if (nIndex == -1) {
		m_ptLineFrom = m_ptLineTo = CPoint(0, 0);
	}
	else if (nIndex == 0) {
		m_ptLineFrom = CPoint(_cyTextMargin, CXTEXTMARGIN);
		m_ptLineTo	 = CPoint(_cyTextMargin, CXTEXTMARGIN + _CalcTextWidth(m_strBtn.Left(nIndex+2)));
	}
	else {
		m_ptLineFrom = CPoint(_cyTextMargin, CXTEXTMARGIN + _CalcTextWidth(m_strBtn.Left(nIndex)));
		m_ptLineTo = CPoint(_cyTextMargin, CXTEXTMARGIN + _CalcTextWidth(m_strBtn.Left(nIndex+2)));
	}
}

//******************************************************************
void CMenuButton::Layout(CPoint point, BOOL bHorz)
{
	if (bHorz)
		m_fsState |= MISTATE_HORZ;
	else
		m_fsState &= ~MISTATE_HORZ;

	if (m_fsState & MISTATE_HIDDEN) {
		m_rcItem.SetRectEmpty();
		return;
	}
	
	if (bHorz) {
		m_rcItem = CRect(point, m_sizeHorz);
	}
	else {
		m_rcItem = CRect(point, CSize(m_sizeHorz.cy, m_sizeHorz.cx));
	}
}

//******************************************************************
void CMenuButton::Update(CDC* pDC)
{
	if (m_fsState & MISTATE_HIDDEN)
		return;
	
	// clean background
	COLORREF clr = GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style );
	pDC->FillSolidRect(m_rcItem, clr);

	if (m_fsState & MISTATE_HOT){
			if (m_bt.IsWindowVisible()) m_bt.ShowWindow(SW_HIDE);
		DrawHot(pDC);
	}
	else if (m_fsState & MISTATE_PRESSED){
			if (m_bt.IsWindowVisible()) m_bt.ShowWindow(SW_HIDE);
		DrawPressed(pDC);
	}
	else {
		DrawNone(pDC);
	}
}

//*********************************************************
void CMenuButton::TrackPopup(CWnd* pBar, CWnd* pWndSentCmd)
{
	LTRACE(_T("CMenuButton::TrackPopup\n"));
	ASSERT_VALID(pBar);
	ASSERT(!(m_fsState & MISTATE_HIDDEN));
	pMenuBar = STATIC_DOWNCAST(CMenuBar, pBar);
	ASSERT_VALID(pMenuBar);

	// "! menu" (no sub menu)
	if (!m_hSubMenu) {
		ASSERT(m_nID != -1);
		pWndSentCmd->SendMessage(WM_COMMAND, (WPARAM)m_nID, (LPARAM)pBar->GetSafeHwnd());		
		return;
	}

	CRect rcItem(m_rcItem);	pMenuBar->ClientToScreen(rcItem);
	UINT fuFlags; TPMPARAMS tpm;
	CPoint pt = _ComputeMenuTrackPoint(rcItem, pMenuBar->GetBarStyle(), fuFlags, tpm);
	
	if (m_hSubMenu == pMenuBar->m_hWindowMenu)
		_bWindowMenuSendCmd = TRUE;
	else
		_bWindowMenuSendCmd = FALSE;
		
	if (pMenuBar->GetBarStyle() & CBRS_ORIENT_HORZ)
	{
		pt.x+=1; pt.y-=2;
	}
	else
	{
		pt.x-=2; pt.y+=2;
	}
	::TrackPopupMenuEx(m_hSubMenu, fuFlags,
		pt.x, pt.y, pWndSentCmd->GetSafeHwnd(), &tpm);
	gbintHorz=-1;
	rcMenu.SetRectEmpty();

}

//****************************************************************
void CMenuButton::DrawHorzText(CDC* pDC, CPoint ptOffset)
{
	COLORREF clr = (m_fsState & MISTATE_INACTIVE) ? 
		::GetSysColor(COLOR_GRAYTEXT) : ::GetSysColor(COLOR_MENUTEXT);
	pDC->SetTextColor(clr);
	
	CRect rcBtn = m_rcItem;
	rcBtn.right-=1;
	pDC->SetBkMode(TRANSPARENT);
	CFont* pOldFont = pDC->SelectObject(&_fontHorzMenu);
	// I know precise text size, but better to leave this job to Windows
	// *****fixed by andi, thanks!*****
	ptOffset.y-=1;
	ptOffset.x+=2;
	pDC->DrawText(m_strBtn, rcBtn + ptOffset,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->SelectObject(pOldFont);
	gbintHorz=0;
	rcMenu=rcBtn;
	rcMenu.right-=4;
	
}

//******************************************************************
void CMenuButton::DrawVertText(CDC* pDC, CPoint ptOffset)
{
	COLORREF clr = (m_fsState & MISTATE_INACTIVE) ? 
		::GetSysColor(COLOR_GRAYTEXT) : ::GetSysColor(COLOR_MENUTEXT);
	pDC->SetTextColor(clr);

	CRect rcBtn = m_rcItem;
	int nLength = m_strBtn.GetLength();
	int nIndex = m_strBtn.Find('&');
	CString strBtn = m_strBtn.Left(nIndex) + m_strBtn.Right(nLength - (nIndex+1));
	
	// fixed for WinNT. *****fixed by Simon, thanks!*****
	int iGraphicsMode = ::GetGraphicsMode(pDC->m_hDC);
	::SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->SetBkMode(TRANSPARENT);
	CFont* pOldFont = pDC->SelectObject(&_fontVertMenu);
	// I know precise text size
	CRect rcString = CRect(
		CPoint(rcBtn.right - _cyTextMargin, rcBtn.top + CXTEXTMARGIN), m_sizeHorz);
	pDC->DrawText(strBtn, rcString + ptOffset,
		DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX);// don't forget DT_NOCLIP
	gbintHorz=1;
	rcMenu=rcBtn;
	rcMenu.bottom-=3;
	pDC->SelectObject(pOldFont);
	
	// CDC::DrawText is poor, so we have to draw vertical line by ourselves
	CPen pen(PS_SOLID, 0, clr);
	CPen* pOldPen = pDC->SelectObject(&pen);
	rcBtn.left-=2;
	pDC->MoveTo(rcBtn.TopLeft() + m_ptLineFrom + ptOffset);
	pDC->LineTo(rcBtn.TopLeft() + m_ptLineTo + ptOffset);

	pDC->SelectObject(pOldPen);
	::SetGraphicsMode( pDC->m_hDC, iGraphicsMode );
}

//******************************************************************
void CMenuButton::DrawButton(CDC* pDC,WORD wState)
{

	CBrush cblu;
	CRect rcBtn =m_rcItem;
	if (dSt & CBRS_ORIENT_HORZ )
		rcBtn.right-=4;
	else
		rcBtn.bottom-=2;

	if (wState & BDR_RAISEDINNER)
		pDC->Draw3dRect(rcBtn,m_dw.GetRGBCaptionXP(),m_dw.GetRGBCaptionXP());
	else
	{
		if (dSt & CBRS_ORIENT_HORZ )
			rcBtn.bottom+=1;
		else
			rcBtn.bottom-=1;
		COLORREF ColBorder;
		if (GuiDrawLayer::m_Style==GUISTYLE_XP)
			ColBorder = GuiDrawLayer::GetRGBMenu();
		else
			ColBorder=GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style);

		pDC->Draw3dRect(rcBtn,ColBorder,ColBorder);
		
		if (dSt & CBRS_ORIENT_HORZ )
			rcBtn.bottom-=1;
		else
			rcBtn.bottom+=1;
		if (GuiDrawLayer::m_Style == GUISTYLE_2003)
		{
			CRect rcb=rcBtn;
			
			if (dSt & CBRS_ORIENT_HORZ)
			{
					
					CGradient M(CSize(rcb.Width(),rcb.Height()));	
					M.PrepareVertical(pDC,GuiDrawLayer::m_Style);
					M.Draw(pDC,rcb.left+1,rcb.top+1,0,0,rcb.Width()-2,rcb.Height(),SRCCOPY);	
				
			}
			else
			{
				CGradient M(CSize(rcb.Width(),rcb.Height()));	
				M.PrepareHorizontal(pDC,GuiDrawLayer::m_Style);
				M.Draw(pDC,rcb.left+1,rcb.top+1,0,0,rcb.Width(),rcb.Height()-3,SRCCOPY);	
			}

		}
		COLORREF ColB = GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
		CPen pen(PS_SOLID, 0, ColB);
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->MoveTo(rcBtn.left, rcBtn.bottom);
		pDC->LineTo(rcBtn.right, rcBtn.bottom);
		COLORREF ColA = GetSysColor(COLOR_WINDOW);
		
		CRect rect = rcBtn;
		int X,Y;
		X=Y=0;
		int winH = rect.Height(); 
		int winW = rect.Width();	
		if (dSt & CBRS_ORIENT_HORZ )
		{ 
			
			rect.right+=4;
			// Simulate a shadow on right edge... 
			for (X=1; X<=4 ;X++)
			{ 
			  for (Y=0; Y<4 ;Y++)
				pDC->SetPixel(rect.right-X,Y+rect.top, ColB );
			  for (Y=4; Y<8 ;Y++)
				  pDC->SetPixel(rect.right-X,Y+rect.top,GuiDrawLayer::DarkenColor(3 * X * (Y - 3), ColB)) ;
			  for (Y=8; Y<=(winH-1) ;Y++)
					pDC->SetPixel(rect.right - X, Y+rect.top, GuiDrawLayer::DarkenColor(15 * X, ColB) );
			}
		}
		else
		{
		  rect.bottom+=2;
		  for(Y=1; Y<=3 ;Y++)
		  {
			for(X=0; X<=3 ;X++)
			{
			  pDC->SetPixel(X,rect.bottom-Y,pDC->GetPixel(rect.left+X,rect.bottom-Y)) ;
			}
			for(X=4; X<=7 ;X++)
			{
			  COLORREF c = pDC->GetPixel(rect.left + X, rect.bottom - Y) ;
			  pDC->SetPixel(X, rect.bottom - Y, GuiDrawLayer::DarkenColor(3 * (X - 3) * Y, c)) ;
			}
			for(X=8; X<=(winW-2) ;X++)
			{
			  COLORREF  c = pDC->GetPixel(rect.left + X, rect.bottom - Y); 
			  pDC->SetPixel(X, rect.bottom- Y, GuiDrawLayer::DarkenColor(15 * Y, c)) ;
			}
		  }   
  

		}
		pDC->SelectObject(pOldPen);

	}
	rcBtn.DeflateRect(1,1);
	if (wState & BDR_RAISEDINNER)
	{
		
		cblu.CreateSolidBrush(m_dw.GetRGBFondoXP());
		pDC->FillRect(rcBtn,&cblu);					
	}

}
//******************************************************************
void CMenuButton::DrawHot(CDC* pDC)
{
	if (m_fsState & MISTATE_HORZ) {

		// draw pressed button
		dSt=CBRS_ORIENT_HORZ;
		DrawButton(pDC,BDR_RAISEDINNER);
		//pDC->DrawEdge(m_rcItem, BDR_RAISEDINNER, BF_RECT);
		DrawHorzText(pDC,CPoint(-1, 1));
	}
	else {
		dSt=CBRS_ORIENT_VERT;
		DrawButton(pDC,BDR_RAISEDINNER);
		//pDC->DrawEdge(m_rcItem, BDR_RAISEDINNER, BF_RECT);
		DrawVertText(pDC);
	}
}

//******************************************************************
void CMenuButton::DrawPressed(CDC* pDC)
{
	if (m_fsState & MISTATE_HORZ) {
		DrawButton(pDC,BDR_SUNKENOUTER);
		//pDC->DrawEdge(m_rcItem, BDR_SUNKENOUTER, BF_RECT);// draw pressed button
		DrawHorzText(pDC, CPoint(-1, 1));
	}
	else {
		DrawButton(pDC,BDR_SUNKENOUTER);
		//pDC->DrawEdge(m_rcItem, BDR_SUNKENOUTER, BF_RECT);
		DrawVertText(pDC, CPoint(1, 1));
	}

}
//--------------------------------

//--------------------------------
//******************************************************************
void CMenuButton::DrawNone(CDC* pDC)
{
	CRect rcBtn = m_rcItem;
	if (!m_bt.IsWindowVisible())
		m_bt.ShowWindow(SW_SHOW);
	m_bt.MoveWindow(rcBtn);

	if (m_fsState & MISTATE_HORZ) {
		m_bt.SetHorzVert();
	}
	else {
		CRect rcBtn = m_rcItem;
		m_bt.SetHorzVert(FALSE);
	}
	

}


void CMenuButton::UpdateButtons()
{
	if (m_bt.IsWindowVisible())
	{
		CRect rcBtn = m_rcItem;
		m_bt.ShowWindow(SW_SHOW);
		m_bt.MoveWindow(rcBtn);
		m_bt.Invalidate();
		m_bt.UpdateWindow();
	}
}
//******************************************************************
//////////////////////////////////////////////////////////////////////
// CMenuIcon class
CMenuIcon::CMenuIcon(CWnd* pMenuBar)
{
	ASSERT_VALID(pMenuBar);
	m_pMenuBar = pMenuBar;
	m_hIconWinLogo = AfxGetApp()->LoadStandardIcon(IDI_WINLOGO);
	ASSERT(m_hIconWinLogo);
	m_btnIcon.Create(_T(""), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
		CRect(0,0,0,0), pMenuBar, 0x999);
	m_btnIcon.ShowWindow(SW_HIDE);
	m_btnIcon.SetScrollButton();
	m_fsStyle |= MISTYLE_TRACKABLE;
	m_fsState |= MISTATE_HIDDEN;
	m_sizeHorz = CSize(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
}
//******************************************************************
CMenuIcon::~CMenuIcon()
{
	if (m_hIconWinLogo != NULL) 
		::FreeResource(m_hIconWinLogo);
	
}
//******************************************************************
void CMenuIcon::OnActivateChildWnd()
{
	//LTRACE(_T("CMenuIcon::OnActivateChildWnd\n"));

	ASSERT_VALID(m_pMenuBar);
			
	CWnd* pFrame = m_pMenuBar->GetTopLevelFrame();
	ASSERT_VALID(pFrame);
	CMDIFrameWnd* pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pFrame);
	HWND hWndMDIClient = pMDIFrame->m_hWndMDIClient;
	ASSERT(::IsWindow(hWndMDIClient));

	BOOL bMaximized = FALSE;
	HWND hWndChild = (HWND)::SendMessage(hWndMDIClient,
		WM_MDIGETACTIVE, 0, (LPARAM)&bMaximized);

	if (bMaximized == FALSE) {
		//LTRACE(_T("    not maximized\n"));
		m_fsState |= MISTATE_HIDDEN;
		m_btnIcon.ShowWindow(SW_HIDE);
	}
	else {
		//LTRACE(_T("    maximized\n"));
		m_fsState &= ~MISTATE_HIDDEN;
		m_btnIcon.SethIcon(m_hDocIcon);
		m_btnIcon.ShowWindow(SW_SHOW);
	}

	m_hDocIcon = (HICON)::GetClassLong(hWndChild, GCL_HICONSM);

	if (m_hDocIcon == NULL) // if hWndChild doesn't have own icon
		m_hDocIcon = m_hIconWinLogo;
}

//******************************************************************
void CMenuIcon::Update(CDC* pDC)
{
	if (m_fsState & MISTATE_HIDDEN)
		return;

	ASSERT(m_hDocIcon);
	ASSERT(m_rcItem.IsRectEmpty() == FALSE);
	m_btnIcon.MoveWindow(m_rcItem);
	::DrawIconEx(pDC->m_hDC, m_rcItem.left, m_rcItem.top, m_hDocIcon,
		m_rcItem.Width(), m_rcItem.Height(), 0, NULL, DI_NORMAL);
}


void CMenuIcon::UpdateButtons()
{
	
}
//******************************************************************
void CMenuIcon::TrackPopup(CWnd* pBar, CWnd* pWndSentCmd)
{
	ASSERT(!(m_fsState & MISTATE_HIDDEN));
	ASSERT_VALID(m_pMenuBar);
	
	CWnd* pFrame = m_pMenuBar->GetTopLevelFrame();
	ASSERT_VALID(pFrame);
	CMDIFrameWnd* pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pFrame);
	HWND hWndMDIClient = pMDIFrame->m_hWndMDIClient;
	ASSERT(::IsWindow(hWndMDIClient));

	BOOL bMaximized = FALSE;
	HWND hWndChild = (HWND)::SendMessage(hWndMDIClient,
		WM_MDIGETACTIVE, 0, (LPARAM)&bMaximized);
	ASSERT(bMaximized);
	HMENU hSysMenu = ::GetSystemMenu(hWndChild, FALSE);
	ASSERT(::IsMenu(hSysMenu));	
	CControlBar* pControlBar = STATIC_DOWNCAST(CControlBar, m_pMenuBar);
	ASSERT_VALID(pControlBar);
	CRect rcItem(m_rcItem);	m_pMenuBar->ClientToScreen(rcItem);

	UINT fuFlags; TPMPARAMS tpm;
	bActivSystemMenu=TRUE;
	CPoint pt = _ComputeMenuTrackPoint(rcItem, pControlBar->GetBarStyle(), fuFlags, tpm);
	gbintHorz=-1;
	CRect rcBtn=CRect(0,0,0,0);
	CRect rcMenu=rcBtn;
	
	::TrackPopupMenuEx(hSysMenu, fuFlags, pt.x, pt.y,m_pMenuBar->GetSafeHwnd(), &tpm);
	
	bActivSystemMenu=FALSE;
}

//******************************************************************
void CMenuIcon::Layout(CPoint point, BOOL bHorz)
{
	if (bHorz)
		m_fsState |= MISTATE_HORZ;
	else
		m_fsState &= ~MISTATE_HORZ;

	if (m_fsState & MISTATE_HIDDEN) {
		m_rcItem.SetRectEmpty();
		return;
	}
	
	m_rcItem = CRect(point, CSize(::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON)));
}

//******************************************************************
//////////////////////////////////////////////////////////////////////
// CMenuControl class
#define CX_GAP_CAPTION 2


CMenuControl::CMenuControl(CWnd* pMenuBar)
{
	ASSERT_VALID(pMenuBar);
	m_pMenuBar = pMenuBar;
	m_bDown = FALSE;
	m_nTracking = -1;

	m_fsState |= MISTATE_HIDDEN;
	
	if (!m_img.Create(IDB_GUI_MDIICONS,9,3,RGB(255,0,255)))
	{
		TRACE0("error");
	}
	m_arrButton[2].Create(_T(""), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
		CRect(0,0,0,0),m_pMenuBar, SC_CLOSE);
	m_arrButton[2].SethIcon(m_img.ExtractIcon(2));
	m_arrButton[2].SetToolTip("Close");
	m_arrButton[2].SetColor(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	m_arrButton[2].ShowDark(FALSE);
	m_arrButton[1].Create(_T(""), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
		CRect(0,0,0,0),m_pMenuBar, SC_RESTORE);
	m_arrButton[1].SethIcon(m_img.ExtractIcon(1));
	m_arrButton[1].SetToolTip("Restore");
	m_arrButton[1].SetColor(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	m_arrButton[1].ShowDark(FALSE);
	m_arrButton[0].Create(_T(""), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
		CRect(0,0,0,0),m_pMenuBar,SC_MINIMIZE);
	m_arrButton[0].SethIcon(m_img.ExtractIcon(0));
	m_arrButton[0].SetToolTip("Minimize");
	m_arrButton[0].SetColor(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	m_arrButton[0].ShowDark(FALSE);
	CSize sizeCaption = GetCaptionSize();
	m_sizeHorz = CSize(sizeCaption.cx*3 + CX_GAP_CAPTION + 1, sizeCaption.cy + 2);
	
}

void CMenuControl::SetColorButton(COLORREF clrBtn)
{
	m_arrButton[2].SetColor(clrBtn);
	m_arrButton[1].SetColor(clrBtn);
	m_arrButton[0].SetColor(clrBtn);
}

//******************************************************************
void CMenuControl::Update(CDC* pDC)
{
	// do nothing
	
}


void CMenuControl::UpdateButtons()
{

}
//******************************************************************
void CMenuControl::Layout(CPoint point, BOOL bHorz)
{
	//LTRACE(_T("CMenuControl::Layout bHorz:%d\n"), bHorz);

	if (bHorz)
		m_fsState |= MISTATE_HORZ;
	else
		m_fsState &= ~MISTATE_HORZ;

	if (m_fsState & MISTATE_HIDDEN) {
		m_rcItem.SetRectEmpty();
		return;
	}

	// just layout easily
	if (bHorz) {
		m_rcItem = CRect(point, m_sizeHorz);
	}
	else {
		m_rcItem = CRect(point, CSize(m_sizeHorz.cy, m_sizeHorz.cx));
	}
}

//******************************************************************
void CMenuControl::DelayLayoutAndDraw(CDC* pDC, CSize sizeBar,BOOL bFlota)
{
	CSize sizeCaption = GetCaptionSize();
	int cxCaption = sizeCaption.cx;
	int cyCaption = sizeCaption.cy;

	if (m_fsState & MISTATE_HORZ) {
		CRect rcCaption;
		rcCaption.right = !bFlota?sizeBar.cx-5:sizeBar.cx;
		rcCaption.bottom = sizeBar.cy-3;
		rcCaption.left = rcCaption.right - cxCaption;
		rcCaption.top = (rcCaption.bottom - cyCaption);

		m_arrCaption[0] = rcCaption;

		rcCaption -= CPoint(cxCaption+CX_GAP_CAPTION, 0);
		m_arrCaption[1] = rcCaption;

		rcCaption -= CPoint(cxCaption, 0);
		m_arrCaption[2] = rcCaption;

		m_rcItem = CRect(m_arrCaption[2].left, m_arrCaption[2].top,
			m_arrCaption[0].right, m_arrCaption[0].bottom);
	}
	else {
		CRect rcCaption;
		rcCaption.left = 0;
		rcCaption.bottom = sizeBar.cy-5;
		rcCaption.right = rcCaption.left + cxCaption;
		rcCaption.top = rcCaption.bottom - cyCaption;
		
		m_arrCaption[0] = rcCaption;	

		rcCaption -= CPoint(0, cyCaption+CX_GAP_CAPTION);
		m_arrCaption[1] = rcCaption;

		rcCaption -= CPoint(0, cyCaption);
		m_arrCaption[2] = rcCaption;

		m_rcItem = CRect(m_arrCaption[2].left, m_arrCaption[2].top,
			m_arrCaption[0].right, m_arrCaption[0].bottom);
	}

	if (m_fsState & MISTATE_HIDDEN) {
		//LTRACE(_T("    hidden\n"));
		return;
	}

	
	// draw frame controls
	DrawControl();
		
}

//******************************************************************


//******************************************************************
void CMenuControl::DrawControl()
{
	CWnd* pFrame = m_pMenuBar->GetTopLevelFrame();
	ASSERT_VALID(pFrame);
	CMDIFrameWnd* pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pFrame);
	HWND hWndMDIClient = pMDIFrame->m_hWndMDIClient;
	ASSERT(::IsWindow(hWndMDIClient));
	BOOL bMaximized = FALSE;
	HWND hWndChild = (HWND)::SendMessage(hWndMDIClient,
		WM_MDIGETACTIVE, 0, (LPARAM)&bMaximized);

	if (bMaximized == TRUE) {
		m_arrButton[2].MoveWindow(m_arrCaption[0]);
		if (!(m_fsState & MISTATE_HORZ)) m_arrButton[0].SetSimpleButton();
		else m_arrButton[2].SetSimpleButton(FALSE);
		m_arrButton[1].MoveWindow(m_arrCaption[1]);
		if (!(m_fsState & MISTATE_HORZ)) m_arrButton[1].SetSimpleButton();
		else m_arrButton[1].SetSimpleButton(FALSE);
		m_arrButton[0].MoveWindow(m_arrCaption[2]);
		if (!(m_fsState & MISTATE_HORZ)) m_arrButton[2].SetSimpleButton();
		else m_arrButton[0].SetSimpleButton(FALSE);

	}
/*	m_arrButton[2].SetColor(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	m_arrButton[1].SetColor(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	m_arrButton[0].SetColor(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
*/
	m_arrButton[2].Invalidate();
	m_arrButton[1].Invalidate();
	m_arrButton[0].Invalidate();
	m_arrButton[2].UpdateWindow();
	m_arrButton[1].UpdateWindow();
	m_arrButton[0].UpdateWindow();
}

//******************************************************************


//******************************************************************
void CMenuControl::OnActivateChildWnd()
{
	//LTRACE(_T("CMenuControl::OnActivateChildWnd\n"));
	ASSERT_VALID(m_pMenuBar);
	
	CWnd* pFrame = m_pMenuBar->GetTopLevelFrame();
	ASSERT_VALID(pFrame);
	CMDIFrameWnd* pMDIFrame = STATIC_DOWNCAST(CMDIFrameWnd, pFrame);
	HWND hWndMDIClient = pMDIFrame->m_hWndMDIClient;
	ASSERT(::IsWindow(hWndMDIClient));

	BOOL bMaximized = FALSE;
	HWND hWndChild = (HWND)::SendMessage(hWndMDIClient,
		WM_MDIGETACTIVE, 0, (LPARAM)&bMaximized);

	if (bMaximized == FALSE) {
		m_fsState |= MISTATE_HIDDEN;
	}
	else {
		m_fsState &= ~MISTATE_HIDDEN;
	}
}



//******************************************************************
CSize CMenuControl::GetCaptionSize()
{
	NONCLIENTMETRICS info; info.cbSize = sizeof(info);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);

	// due to my own feeling
	return CSize(info.iMenuHeight - info.iBorderWidth*2, info.iMenuHeight - info.iBorderWidth*4);
}

//******************************************************************
#if _MFC_VER < 0x0600
void CMenuBar::SetBorders(int cxLeft, int cyTop, int cxRight, int cyBottom)
{
	ASSERT(cxLeft >= 0);
	ASSERT(cyTop >= 0);
	ASSERT(cxRight >= 0);
	ASSERT(cyBottom >= 0);

	m_cxLeftBorder = cxLeft;
	m_cyTopBorder = cyTop;
	m_cxRightBorder = cxRight;
	m_cyBottomBorder = cyBottom;
}
#endif
//******************************************************************
// input CRect should be client rectangle size
void CMenuBar::_CalcInsideRect(CRect& rect, BOOL bHorz) const
{
	LTRACE(_T("CMenuBar::_CalcInsideRect\n"));
	ASSERT_VALID(this);
	DWORD dwStyle = m_dwStyle;

	if (dwStyle & CBRS_BORDER_LEFT)
		rect.left += cxBorder2;
	if (dwStyle & CBRS_BORDER_TOP)
		rect.top += cyBorder2;
	if (dwStyle & CBRS_BORDER_RIGHT) 
		rect.right -= cxBorder2;
	if (dwStyle & CBRS_BORDER_BOTTOM)
		rect.bottom -= cyBorder2;

	BOOL bDrawGripper = !(m_dwStyle & CBRS_FLOATING) && (m_dwExStyle & CBRS_GRIPPER);

	// inset the top and bottom.
	if (bHorz)
	{
		rect.left += m_cxLeftBorder;
		rect.top += m_cyTopBorder;
		rect.right -= m_cxRightBorder;
		rect.bottom -= m_cyBottomBorder;
		if (bDrawGripper)
			rect.left += CX_GRIPPER_ALL;
	}
	else
	{
		rect.left += m_cyTopBorder;
		rect.top += m_cxLeftBorder;
		rect.right -= m_cyBottomBorder;
		rect.bottom -= m_cxRightBorder;
		if (bDrawGripper)
			rect.top += CY_GRIPPER_ALL;
	}
}

//******************************************************************
/////////////////////////////////////////////////////////////////////////////
// CMenuDockBar implementation
// a little changed from CDockBar implementation

static BOOL _IsMenuBar(int nPos, CPtrArray& arrBars)
{
	if (nPos < arrBars.GetSize()) {
		CControlBar* pBar = (CControlBar*)arrBars[nPos];
		if (pBar && pBar->GetDlgCtrlID() == AFX_IDW_MENUBAR)
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}


//******************************************************************
// ERNESTO
BOOL	CMenuBar::SetSubMenuText( int id, TCHAR *szText)
{
	BOOL ret= FALSE;
	if( id >= m_arrItem.GetSize() )
		return FALSE;
	CMenuButton *pMenu = (CMenuButton*)m_arrItem.GetAt(id);
	if( pMenu)
	{
		pMenu->SetText(szText);		
		ret = TRUE;
	}
	else 
		ret = FALSE;
	return ret;
}
//******************************************************************


void CMenuBar::OnPaint()
{
	CPaintDC pDC(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CControlBar::OnPaint() for painting messages
	CRect rect;	GetClientRect(rect);
	BOOL bFlota=m_dwStyle & CBRS_FLOATING;
	// draw items
	m_sizex=0;
	CRect m_rect;
	GetClientRect(m_rect);
	CBrush cbr;
	cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	pDC.FillRect(m_rect,&cbr);
	
	for (int i = 0; i < m_arrItem.GetSize(); ++i) {
			m_arrItem[i]->Update(&pDC);
			if (m_bChangeState)
				m_arrItem[i]->UpdateButtons();
		}
	if (m_bChangeState)
		m_bChangeState=FALSE;
	
	// delay draw captions 
	if (m_pMenuControl) {
		if (IsFloating()) {
			m_pMenuControl->DelayLayoutAndDraw(&pDC, rect.Size(),bFlota);
			

		}
		else {
			if (m_dwStyle & CBRS_ORIENT_HORZ)
				m_pMenuControl->DelayLayoutAndDraw(&pDC, CSize(GetClipBoxLength(TRUE), rect.Height()),bFlota);
			else
				m_pMenuControl->DelayLayoutAndDraw(&pDC, CSize(rect.Width(), GetClipBoxLength(FALSE)),bFlota);
		}
	}

}


