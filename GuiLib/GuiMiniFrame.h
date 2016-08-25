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



#pragma once

// CGuiMiniFrame frame
#include "GuiMiniFrame.h" 
#include "GuiDrawLayer.h" 

class GUILIBDLLEXPORT CGuiMiniFrame : public CMiniDockFrameWnd
{
	DECLARE_DYNCREATE(CGuiMiniFrame)

protected:
	BOOL IsGuiControlBar;
	CGuiControlBarButton m_btn;
	CRect m_rcCloseBtn;
	int	m_stateBtn;
	BOOL IsMenuBar;
	BOOL IsToolBar;
public:
// Construction
	CGuiMiniFrame();

// Operations
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual BOOL Create(CWnd* pParent, DWORD dwBarStyle);
	void DrawGripper(CDC* pDC,CRect* rc);
	void TypeBar();
	CWnd* GetChildWnd();

// Implementation
public:
	//{{AFX_MSG(CMiniFrameWnd)
	afx_msg void OnClose();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nHitTest, CPoint point);
	//}}AFX_MSG
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);

	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);

	DECLARE_MESSAGE_MAP()
};


