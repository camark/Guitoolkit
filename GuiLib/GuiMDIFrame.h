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
 *																			*	
 ****************************************************************************/

#if !defined(AFX_GUIFRAMEWND_H__B5DCA3BF_291F_4175_98E9_99A1D6E91C44__INCLUDED_)
#define AFX_GUIFRAMEWND_H__B5DCA3BF_291F_4175_98E9_99A1D6E91C44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CGuiMDIFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiFrameWnd frame
#include "GuiDocbarExten.h"
#include "GuiDocbarExtenEx.h"
#include "GuiDocSpecial.h"
#include "GuiControlBar.h"
#include "GuiDockToolbar.h"
#include "GuiMDITabbed.h"
#include "MenuBar.h"
#include "CoolMenu.h"
#include "GuiStatusBar.h"
#include "GuiToolBarWnd.h" 
#include "NewMenu.h"
#include "GuiDockToolBarEx.h"

class GUILIBDLLEXPORT CGuiMDIFrame : public CMDIFrameWnd
{
	DECLARE_DYNCREATE(CGuiMDIFrame)
protected:
	CGuiMDIFrame();           // protected constructor used by dynamic creation
	CString sProfile;
	CGuiMDITabbed m_MdiTabbed;
	CMenuBar m_wndMenuBar;
	CCoolMenuManager m_wndCool;	
public:
	CGuiStatusBar m_wndStatusBar;
	CGuiToolBarWnd    m_wndToolBar;
	CNewMenu m_NewMenu;	
	CSize m_size; 
	BOOL  m_InitClass;
// Attributes
public:
	void LoadBars();
	BOOL VerifyBarState(LPCTSTR lpszProfileName);
// Operations
public:

	virtual void EnableDocking(DWORD dwDockStyle);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs, UINT nIconID);
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DWORD CanDock(CRect rect, DWORD dwDockStyle,
		CDockBar** ppDockBar = NULL); // called by CDockContext
	BOOL InitMDITabbed();
	int InitStatusBar(UINT* indicators,int nSize);
	int InitToolBar(UINT uIDMenu);
	int InitMenu(UINT uIDMenu);
	void DockSpecialBars();
	void ShowHideBar(CGuiControlBar* pBar);
	void ShowHideBar(CControlBar* pBar);
	void LoadPosBar(CString szBars);
	void SavePosBar(CString szBars);
	void OnFilePrintPreview() ;
	CMenuBar* GetMenuBar(){return &m_wndMenuBar;}
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP);
	DWORD m_StyleDisplay;
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
	virtual ~CGuiMDIFrame();

	// Generated message map functions
	//{{AFX_MSG(CGuiMDIFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	afx_msg void OnSysColorChange( );
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIFRAMEWND_H__B5DCA3BF_291F_4175_98E9_99A1D6E91C44__INCLUDED_)
