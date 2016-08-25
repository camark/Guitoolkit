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


#if !defined(AFX_GUIMINIFRAMEWND_H__9C7DE978_51C1_485C_8F11_CFE5B97BFB6B__INCLUDED_)
#define AFX_GUIMINIFRAMEWND_H__9C7DE978_51C1_485C_8F11_CFE5B97BFB6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiMiniFrameWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiMiniFrameWnd frame

#include "GuiMiniFrame.h" 
#include "GuiDrawLayer.h" 

class GUILIBDLLEXPORT  CGuiMiniFrameWnd : public CMiniFrameWnd
{
	DECLARE_DYNCREATE(CGuiMiniFrameWnd)
public:
	CGuiMiniFrameWnd();           // protected constructor used by dynamic creation
	virtual ~CGuiMiniFrameWnd();
	void DrawGripper(CDC* pDC,CRect* rc);
// Attributes
public:
	CRect r;
	CWnd* pControl;
	BOOL bDestroy;
	CGuiControlBarButton m_btn;
	CRect m_rcCloseBtn;
	int		m_stateBtn;
	CWnd*	pParent;
	DWORD dwStyle;
	BOOL bClick;
	int  nSizeLine;
// Operations
public:

// Implementation
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CGuiMiniFrameWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	virtual BOOL Create(CWnd* pParentWnd,CWnd* pControl,const RECT& rect,LPCTSTR lpszWindowName,int nSize=0);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CWnd* GetChildWnd();
	void RecalLayout();
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnCancelMode();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIMINIFRAMEWND_H__9C7DE978_51C1_485C_8F11_CFE5B97BFB6B__INCLUDED_)
