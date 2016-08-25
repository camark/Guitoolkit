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

#if !defined(AFX_GUIMINISPLITTER_H__F242B3CD_66D9_4046_912A_28A47FEE2D66__INCLUDED_)
#define AFX_GUIMINISPLITTER_H__F242B3CD_66D9_4046_912A_28A47FEE2D66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiMiniSplitter.h : header file
//

#include "GuiMiniTool.h"

class GUILIBDLLEXPORT CGuiMiniSplitter : public CWnd
{
// Construction
public:
	CGuiMiniSplitter();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiMiniSplitter)
	public:
	virtual BOOL Create(CWnd* pParentWnd);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGuiMiniSplitter();
	void    SetColor(COLORREF m_clrFace,COLORREF m_clrBorder);
	BOOL    AddMiniToolLeft(CGuiMiniTool * m_ToolLeft);
	BOOL    AddMiniToolRight(CGuiMiniTool * m_ToolRight);
	void	DrawSplitter(CRect rc,CDC* mdc);
	void	RecalLayout();
protected:
	int npos;	//splitter position
	CGuiMiniTool*	m_ToolLeft;
	CGuiMiniTool*	m_ToolRight;
	CRect m_rcSplitter;
	CRect m_rcSplitterOld;
	COLORREF m_clrface;	
	COLORREF m_clrborder;
	BOOL	 bIniciaArrastre;
	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiMiniSplitter)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysColorChange();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIMINISPLITTER_H__F242B3CD_66D9_4046_912A_28A47FEE2D66__INCLUDED_)
