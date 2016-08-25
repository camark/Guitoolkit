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
 * -Francisco Campos
 * -Patrick (skydive241)				
 *																			*	
 ****************************************************************************/

#pragma once

#include "GuiDocbarExten.h"
#include "GuiDocbarExtenEx.h"
#include "GuiDocSpecial.h"
#include "GuiControlBar.h"
#include "GuiDockToolbar.h"
#include "MenuBar.h"
#include "CoolMenu.h"
#include "GuiStatusBar.h"
#include "GuiToolBarWnd.h"
#include "GuiDockToolBarEx.h"
#include "NewMenu.h"

class GUILIBDLLEXPORT  CGuiFrameWnd : public CFrameWnd
{
		DECLARE_DYNCREATE(CGuiFrameWnd)
protected:
	CString sProfile;
protected:
	CGuiDocBarExten m_dockbar;
	CGuiDockToolBar m_dockToolbarLeft;
	CGuiDockToolBar m_dockToolbarTop;
	CGuiDockToolBar m_dockToolbarBottom;
	CGuiDockToolBar m_dockToolbarRight;
public:
	CGuiDocBarExtenEx* m_dockTop;
	CGuiDocBarExtenEx* m_dockLeft;
	CGuiDocBarExtenEx* m_dockRight;
	CGuiDocBarExtenEx* m_dockBottom;
public:
	CGuiDockToolBarEx m_dockHideLeft;
	CGuiDockToolBarEx m_dockHideTop;
	CGuiDockToolBarEx m_dockHideBottom;
	CGuiDockToolBarEx m_dockHideRight;
protected:
	CMenuBar m_wndMenuBar;
	CNewMenu m_NewMenu;	
	CCoolMenuManager m_wndCool;	
public:
	CGuiStatusBar m_wndStatusBar;
	CGuiToolBarWnd    m_wndToolBar;
	BOOL			m_MdiTabbed;
public:
	void LoadBars();
	BOOL VerifyBarState(LPCTSTR lpszProfileName);
	void DockSpecialBars();
	int InitStatusBar(const UINT* lpIDArray,int nSize);
	int InitToolBar(UINT uIDMenu);
	int InitMenu(UINT uIDMenu);
	void ShowHideBar(CGuiControlBar* pBar);
	void ShowHideBar(CControlBar* pBar);
	void LoadPosBar(CString szBars);
	void SavePosBar(CString szBars);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void StyleDispl(DWORD dwDsp);
	DWORD m_StyleDisplay;
public:
	CGuiFrameWnd(void);
	virtual ~CGuiFrameWnd(void);
	virtual void EnableDocking(DWORD dwDockStyle);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs, UINT nIconID);
	virtual BOOL LoadFrame(UINT nIDResource, 
			DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW |FWS_ADDTOTITLE, 
			CWnd* pParentWnd = NULL,CCreateContext* pContext = NULL); 

	virtual BOOL DestroyWindow();
	
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange( );
};
