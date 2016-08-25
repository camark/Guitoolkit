/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 * (MFC extension)								*			 
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
 * Bug Fixes and improvements :(Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

#if !defined(AFX_CHECKBOX_H__38E72D24_A4C7_11D5_B914_000000000000__INCLUDED_)
#define AFX_CHECKBOX_H__38E72D24_A4C7_11D5_B914_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CGuiCheckBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiCheckBox window

#include "GuiDrawLayer.h"

class GUILIBDLLEXPORT CGuiCheckBox : public CButton
{
	// Construction
public:
	CGuiCheckBox();
	virtual ~CGuiCheckBox();
	
	
	// Attributes
public:
	void DrawCheck(CDC* pDC, CRect m_rcTemp);	
	void DrawOrange(CDC* pDC, CRect m_rcTemp);	
	
public:
	BOOL         m_bCheckBtn;
	BOOL         m_bPressBtn;
	BOOL         m_bOldTemp;
	COLORREF     m_clrHigh;
	COLORREF     m_clrCheck;
	GuiDrawLayer m_wd;
	BOOL         m_bSelected;
	
public:
	// Overrides
	//{{AFX_VIRTUAL(CGuiCheckBox)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CGuiCheckBox)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////
/////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKBOX_H__38E72D24_A4C7_11D5_B914_000000000000__INCLUDED_)
