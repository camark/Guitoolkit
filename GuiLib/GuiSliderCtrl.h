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

#if !defined(AFX_GUISLIDERCTRL_H__1DC8660F_0D35_408B_BD0D_95621F561841__INCLUDED_)
#define AFX_GUISLIDERCTRL_H__1DC8660F_0D35_408B_BD0D_95621F561841__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiSliderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiSliderCtrl window

#include "GuiDrawLayer.h"

class GUILIBDLLEXPORT CGuiSliderCtrl : public CSliderCtrl
{
// Construction
public:
	CGuiSliderCtrl();

// Attributes
public:
	
	void DrawHThumb(CDC* pDC, CRect rcClient);
	void DrawVThumb(CDC* pDC, CRect rcClient);
	void DrawSlider(CDC* pDC, CRect rcClient);
public:
	BOOL bSelected;
	COLORREF m_clrGreen;  //verder
	COLORREF m_clrOrange; //no tan naranja
	GuiDrawLayer m_dl;
	BOOL	m_Press;
public:
	virtual ~CGuiSliderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiSliderCtrl)
	afx_msg void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUISLIDERCTRL_H__1DC8660F_0D35_408B_BD0D_95621F561841__INCLUDED_)
