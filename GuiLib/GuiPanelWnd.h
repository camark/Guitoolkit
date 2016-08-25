/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *                           (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software; so you are free to use it any of your		*
 * applications(Freeware, Shareware, Commercial), but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 *																			*	
 ****************************************************************************/


#if !defined(AFX_GUIPANELWND_H__7800D92C_C2CC_43C6_B272_A0D43D898DDA__INCLUDED_)
#define AFX_GUIPANELWND_H__7800D92C_C2CC_43C6_B272_A0D43D898DDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiPanelWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiPanelWnd window
#define NORMAL 0
#define OVER   1
#define PRESS  2

#include "GuiDrawLayer.h"

class GUILIBDLLEXPORT CGuiPanelWnd : public CWnd
{
// Construction
public:
	CGuiPanelWnd();

// Attributes
public:
	void DrawGripper(CDC* pDC, CRect* rc);
	void AddWindow(CWnd* pWin);
	void DeletedWindow();

	BOOL IsLeft()
	{
		if(m_nLastAlingDocking==CBRS_ALIGN_LEFT)
			return TRUE;
		return FALSE;
	}

	BOOL IsRight()
	{
		if(m_nLastAlingDocking==CBRS_ALIGN_RIGHT)
			return TRUE;
		return FALSE;
	}

	BOOL IsTop()
	{
		if(m_nLastAlingDocking==CBRS_ALIGN_TOP)
			return TRUE;
		return FALSE;

	}
	
	BOOL IsBottom()
	{
		if(m_nLastAlingDocking==CBRS_ALIGN_BOTTOM)
			return TRUE;		
		return FALSE;
	}

	BOOL IsVert()
	{
		return (IsLeft() && IsRight());

	}

	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{m_StyleDisplay=dwDsp;SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();}
	DWORD			m_StyleDisplay;
	
// Operations
protected:
	CWnd* m_pWin;		  //the Child	
	BOOL  bHide;      //is the windows hide
	BOOL  m_bActive;   //is selected 	
	CGuiControlBarButton m_CloseBtn;
	int	  nGapGripper;
	CRect m_rcCloseBtn;
	int	  m_stateBtn;
	UINT  m_nLastAlingDocking;
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiPanelWnd)
	public:
	virtual BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,UINT nAling);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGuiPanelWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiPanelWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcCalcSize(BOOL, NCCALCSIZE_PARAMS*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIPANELWND_H__7800D92C_C2CC_43C6_B272_A0D43D898DDA__INCLUDED_)
