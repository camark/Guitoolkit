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
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 * -Serge Koroleuve															*
 * -Patrick (skydive241)													*	
 * -Stanimir Jordanov (Demosten)											*	
 ****************************************************************************/



#include "stdafx.h"
#include "guiframewnd.h"
#include "GuiMiniFrame.h"

IMPLEMENT_DYNCREATE(CGuiFrameWnd, CFrameWnd)
CGuiFrameWnd::CGuiFrameWnd(void)
{
	m_MdiTabbed=FALSE;
	sProfile = AfxGetAppName();
	sProfile.Replace(_T(' '), _T('_'));
	m_StyleDisplay=GUISTYLE_XP;
}

CGuiFrameWnd::~CGuiFrameWnd(void)
{
}

void CGuiFrameWnd::OnSysColorChange( )
{
	CFrameWnd::OnSysColorChange( );
	GuiDrawLayer::IsThemeXP();
}


BOOL CGuiFrameWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	// Restore main window position
	CWinApp* pApp = AfxGetApp();
	TCHAR szSection[256];
 	wsprintf(szSection, "%s-Main", sProfile);

	// Restore main window position
    CWinApp* app = AfxGetApp();
    int s, t, b, r, l;

	l = pApp->GetProfileInt(szSection, "left",10);
	t = pApp->GetProfileInt(szSection, "top",10);
	b = pApp->GetProfileInt(szSection, "bottom",400);
	r = pApp->GetProfileInt(szSection, "right",600);
	s = pApp->GetProfileInt(szSection, "status", SW_NORMAL);
	GuiDrawLayer::m_Style=(int)pApp->WriteProfileInt(szSection, _T("Style"),GUISTYLE_XP);
	GuiDrawLayer::m_Theme=(int)pApp->WriteProfileInt(szSection, _T("Theme"),0);

	// only restore if there is a previously saved position
	// restore the window's status
	app->m_nCmdShow = s;
                             
	// restore the window's width and height
	cs.cx = r - l;
	cs.cy = b - t;
                             
	// the following correction is needed when the taskbar is
    // at the left or top and it is not "auto-hidden"
	RECT workArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
	l += workArea.left;
	t += workArea.top;
                             
	// make sure the window is not completely out of sight
	int max_x = GetSystemMetrics(SM_CXSCREEN) - GetSystemMetrics(SM_CXICON);
	int max_y = GetSystemMetrics(SM_CYSCREEN) - GetSystemMetrics(SM_CYICON);
	cs.x = min(l, max_x);
	cs.y = min(t, max_y);

	return CFrameWnd::PreCreateWindow(cs);
}

BOOL CGuiFrameWnd::PreTranslateMessage(MSG* pMsg) 
{
	if (m_wndMenuBar.TranslateFrameMessage(pMsg))
		return TRUE;
	
	return CFrameWnd::PreTranslateMessage(pMsg);
}

//*************************************************************************
BOOL CGuiFrameWnd::PreCreateWindow(CREATESTRUCT& cs, UINT nIconID)
{
	cs.lpszClass = AfxRegisterWndClass( 0, NULL, NULL,
		AfxGetApp()->LoadIcon(nIconID));
	ASSERT(cs.lpszClass);

	return CFrameWnd::PreCreateWindow(cs);
}

void CGuiFrameWnd::StyleDispl(DWORD dwDsp)
{
	m_StyleDisplay=dwDsp;
	GuiDrawLayer::m_Style=m_StyleDisplay;
	GuiDrawLayer::IsThemeXP();
	m_wndCool.StyleDispl(m_StyleDisplay);
	m_wndStatusBar.StyleDispl(m_StyleDisplay);
	m_wndMenuBar.StyleDispl(m_StyleDisplay);
	m_wndToolBar.StyleDispl(m_StyleDisplay);
	m_dockTop->StyleDispl(m_StyleDisplay);
	m_dockLeft->StyleDispl(m_StyleDisplay);
	m_dockRight->StyleDispl(m_StyleDisplay);
	m_dockBottom->StyleDispl(m_StyleDisplay);
	m_NewMenu.StyleDispl(m_StyleDisplay);
	SendMessage(WM_NCPAINT);
	Invalidate(); 
	UpdateWindow();
}

void CGuiFrameWnd::EnableDocking(DWORD dwDockStyle)
{
	ASSERT((dwDockStyle & ~ (CBRS_ALIGN_ANY | CBRS_FLOAT_MULTI)) == 0);


	m_pFloatingFrameClass = RUNTIME_CLASS(CMiniDockFrameWnd);
	CGuiDocBarExten* pDock;
	DWORD dwStyle = WS_CHILD| WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	DWORD dwstyle;
	DockSpecialBars();

	pDock = new CGuiDocBarExten();
	pDock->Create(this,dwStyle|CBRS_TOP, AFX_IDW_DOCKBAR_TOP);
	dwstyle = pDock->GetBarStyle();
	dwstyle &= ~CBRS_BORDER_ANY;
	pDock->SetBarStyle(dwstyle);
	
	pDock = new CGuiDocBarExten();
	pDock->Create(this, dwStyle|CBRS_BOTTOM, AFX_IDW_DOCKBAR_BOTTOM);
	dwstyle = pDock->GetBarStyle();
	dwstyle &= ~CBRS_BORDER_ANY;
	pDock->SetBarStyle(dwstyle);

	pDock = new CGuiDocBarExten();
	pDock->Create(this,dwStyle|CBRS_LEFT, AFX_IDW_DOCKBAR_LEFT);
	dwstyle = pDock->GetBarStyle();
	dwstyle &= ~CBRS_BORDER_ANY;
	pDock->SetBarStyle(dwstyle);

	pDock = new CGuiDocBarExten();
	pDock->Create(this,dwStyle|CBRS_RIGHT, AFX_IDW_DOCKBAR_RIGHT);
	dwstyle = pDock->GetBarStyle();
	dwstyle &= ~CBRS_BORDER_ANY;
	pDock->SetBarStyle(dwstyle);
	m_pFloatingFrameClass = RUNTIME_CLASS(CGuiMiniFrame);


}

void CGuiFrameWnd::ShowHideBar(CGuiControlBar* pBar)
{
	if (pBar->IsWindowVisible())
		ShowControlBar(pBar, FALSE, FALSE);
	else
		ShowControlBar(pBar, TRUE, FALSE);
}

void CGuiFrameWnd::ShowHideBar(CControlBar* pBar)
{
	if (pBar->IsWindowVisible())
		ShowControlBar(pBar, FALSE, FALSE);
	else
		ShowControlBar(pBar, TRUE, FALSE);
}

void CGuiFrameWnd::SavePosBar(CString szBars)
{
	POSITION pos = m_listControlBars.GetHeadPosition();
    while (pos != NULL)
    {
        CGuiControlBar* pBar = (CGuiControlBar*) m_listControlBars.GetNext(pos);
        ASSERT(pBar != NULL);
        if (pBar->IsKindOf(RUNTIME_CLASS(CGuiControlBar)))
            pBar->SaveBar(szBars);
    }
}

void CGuiFrameWnd::LoadPosBar(CString szBars)
{
	POSITION pos = m_listControlBars.GetHeadPosition();
    while (pos != NULL)
    {
        CGuiControlBar* pBar = (CGuiControlBar*) m_listControlBars.GetNext(pos);
        ASSERT(pBar != NULL);
        if (pBar->IsKindOf(RUNTIME_CLASS(CGuiControlBar)))
            pBar->LoadStateBar(szBars);
    }
}

void CGuiFrameWnd::DockSpecialBars()
{
	
	DWORD dwStyle = WS_CHILD| WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	m_dockTop=new CGuiDocBarExtenEx();
	m_dockTop->Create(this,dwStyle|CBRS_TOP,CBRS_ALIGN_TOP);
	DWORD dwstyle;
	dwstyle = m_dockTop->GetBarStyle();
	dwstyle &= ~CBRS_BORDER_ANY;
	m_dockTop->SetBarStyle(dwstyle);
	
	m_dockBottom=new CGuiDocBarExtenEx();
	m_dockBottom->Create(this,dwStyle|CBRS_BOTTOM,CBRS_ALIGN_BOTTOM);
	dwstyle = m_dockBottom->GetBarStyle();
	dwstyle &= ~CBRS_BORDER_ANY;
	m_dockBottom->SetBarStyle(dwstyle);

	m_dockLeft=new CGuiDocBarExtenEx();
	m_dockLeft->Create(this,dwStyle|CBRS_LEFT,CBRS_ALIGN_LEFT);
	dwstyle = m_dockLeft->GetBarStyle();
	dwstyle &= ~CBRS_BORDER_ANY;
	m_dockLeft->SetBarStyle(dwstyle);
	
	m_dockRight=new CGuiDocBarExtenEx();
	m_dockRight->Create(this,dwStyle|CBRS_RIGHT,CBRS_ALIGN_RIGHT);
	dwstyle = m_dockRight->GetBarStyle();
	dwstyle &= ~CBRS_BORDER_ANY;
	m_dockRight->SetBarStyle(dwstyle);
	

	m_dockHideTop.Create(this,CBRS_ALIGN_TOP);

	m_dockHideBottom.Create(this,CBRS_ALIGN_BOTTOM);
	
	m_dockHideLeft.Create(this,CBRS_ALIGN_LEFT);
	
	m_dockHideRight.Create(this,CBRS_ALIGN_RIGHT);
	



	m_dockToolbarTop.Create(this,CBRS_ALIGN_TOP);
	m_dockToolbarBottom.Create(this,CBRS_ALIGN_BOTTOM);
	m_dockToolbarLeft.Create(this,CBRS_ALIGN_LEFT);
	m_dockToolbarRight.Create(this,CBRS_ALIGN_RIGHT);

}
/////////////////////////////////////////////////////////////////////////////
// CGuiMDIFrame message handlers
//***********************************************************************
BOOL CGuiFrameWnd::DestroyWindow()
{
	CWinApp* pApp = AfxGetApp();
	TCHAR szSection[256];
	wsprintf(szSection, "%s-Main", sProfile);

	WINDOWPLACEMENT wp;
    GetWindowPlacement(&wp);
	
	pApp->WriteProfileString(szSection, NULL, NULL);
	pApp->WriteProfileInt(szSection, "left", wp.rcNormalPosition.left);
	pApp->WriteProfileInt(szSection, "right", wp.rcNormalPosition.right);
	pApp->WriteProfileInt(szSection, "bottom", wp.rcNormalPosition.bottom);
	pApp->WriteProfileInt(szSection, "top", wp.rcNormalPosition.top);
	pApp->WriteProfileInt(szSection, "status", wp.showCmd);
	pApp->WriteProfileInt(szSection, _T("Style"),(int) GuiDrawLayer::m_Style);
	pApp->WriteProfileInt(szSection, _T("Theme"),(int) GuiDrawLayer::m_Theme);

	SaveBarState(sProfile);
	SavePosBar(sProfile);
	return CFrameWnd::DestroyWindow();
}

//***********************************************************************
BOOL CGuiFrameWnd::VerifyBarState(LPCTSTR lpszProfileName)
{
    CDockState state;
    state.LoadState(lpszProfileName);

    for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++)
    {
        CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
        ASSERT(pInfo != NULL);
        int nDockedCount = pInfo->m_arrBarID.GetSize();
        if (nDockedCount > 0)
        {
            // dockbar
            for (int j = 0; j < nDockedCount; j++)
            {
                UINT nID = (UINT) pInfo->m_arrBarID[j];
                if (nID == 0) continue; // row separator
                if (nID > 0xFFFF)
                    nID &= 0xFFFF; // placeholder - get the ID
                if (GetControlBar(nID) == NULL)
                    return FALSE;
            }
        }

        if (!pInfo->m_bFloating) // floating dockbars can be created later
            if (GetControlBar(pInfo->m_nBarID) == NULL)
                return FALSE; // invalid bar ID
    }

    return TRUE;
}


void CGuiFrameWnd::LoadBars()
{
	if (VerifyBarState(sProfile))
	{
		LoadBarState(sProfile);
		LoadPosBar(sProfile);
	}
}

BEGIN_MESSAGE_MAP(CGuiFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
END_MESSAGE_MAP()

int CGuiFrameWnd::InitMenu(UINT uIDMenu)
{
	if (!m_wndMenuBar.CreateEx(this, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_SIZE_DYNAMIC ) ||
		!m_wndMenuBar.LoadMenuBar(uIDMenu))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}	
	m_NewMenu.LoadMenu(uIDMenu);
	m_wndCool.Install(this);
	m_wndCool.LoadToolbar(uIDMenu);
	
	return 0;
}

int CGuiFrameWnd::InitStatusBar(const UINT* lpIDArray,int nSize)
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(lpIDArray,
		  nSize))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	return 0;
}

int CGuiFrameWnd::InitToolBar(UINT uIDMenu)
{

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),uIDMenu) ||
		!m_wndToolBar.LoadToolBar(uIDMenu))
		{
		TRACE0("Failed to create toolbar\n");
		return -1; // fail to create
	}
// new code:  Serge Koroleuve

	IMAGEINFO ii;
	m_wndToolBar.GetToolBarCtrl().GetImageList()->GetImageInfo(0, &ii);
	int cx = ii.rcImage.right - ii.rcImage.left;
	int cy = ii.rcImage.bottom - ii.rcImage.top;
	int nCount = m_wndToolBar.GetToolBarCtrl().GetImageList()->GetImageCount();

	CImageList imageList;
	CBitmap bitmap;

	bitmap.LoadBitmap(uIDMenu);
	imageList.Create(cx, cy, ILC_COLORDDB|ILC_MASK, nCount, 0);
	imageList.Add(&bitmap, RGB(192,192,192));
	m_wndToolBar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)imageList.m_hImageList);
	imageList.Detach();
	bitmap.Detach();
// end of new code
return 0;
}


int CGuiFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style|=WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  Add your specialized creation code here

	return 0;
}

BOOL CGuiFrameWnd::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// only do this once
	ASSERT_VALID_IDR(nIDResource);
	ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

	m_nIDHelp = nIDResource; // ID for help context (+HID_BASE_RESOURCE)

	CString strFullString;
	if (strFullString.LoadString(nIDResource))
		AfxExtractSubString(m_strTitle, strFullString, 0); // first sub-string

	VERIFY(AfxDeferRegisterClass(AFX_WNDFRAMEORVIEW_REG));

	// attempt to create the window
	LPCTSTR lpszClass = GetIconWndClass(dwDefaultStyle, nIDResource);
	LPCTSTR lpszTitle = m_strTitle;
	if (!Create(lpszClass, lpszTitle, dwDefaultStyle, rectDefault,pParentWnd, NULL, 0L, pContext))
	{
		return FALSE; // will self destruct on failure normally
	}

	// save the default menu handle
	ASSERT(m_hWnd != NULL);
	m_hMenuDefault = ::GetMenu(m_hWnd);

	// load accelerator resource
	LoadAccelTable(MAKEINTRESOURCE(nIDResource));

	if (pContext == NULL) // send initial update
		SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);

	return TRUE;
}
