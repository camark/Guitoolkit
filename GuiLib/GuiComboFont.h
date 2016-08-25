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
 * Bug Fixes and improvements :(Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

#pragma once

#include "GuiDrawLayer.h"

/////////////////////////////////////////////////////////////////////////////
// CGuiComboFont window

class GUILIBDLLEXPORT CGuiComboFont : public CComboBox
{
	// Construction
public:
	DECLARE_DYNAMIC(CGuiComboFont)
		CGuiComboFont();
	virtual		~CGuiComboFont();
	
	// Attributes
public:
	
	// Operations
public:
	enum enTypeShow{CM_NORMAL = 0, CM_ONFOCUS, CM_SELECCIONADO};
	
public:
	BOOL		m_bOverCombo;
	int			m_iWidthDrowDown;
	COLORREF	m_clrBtnFace;
	COLORREF	m_clrBtnLight;
	COLORREF	m_clrBtnDark;
	CFont		m_Font;
	BOOL		m_bPress;
	BOOL        m_bFondoXp;
	BOOL		m_IsCallMiniTool;
	BOOL		bhistory;
	
public:
	//******************************************************
	void		DrawCombo(enTypeShow enShow, CDC* pDC);
	void		DrawArrow(CDC* pDC, CRect m_rc);
	void		SetColor(COLORREF clrFace);
	void        AutoColor(BOOL bColor = TRUE);
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	static BOOL CALLBACK EnumFontsProc(LPLOGFONT lplf, LPTEXTMETRIC lptm, 
		DWORD dwFontType, LPARAM lpData);
	void FillerCombo();

protected:
	CImageList		m_imgArrow; // imagen arrow
	CPoint			mHeight;
	GuiDrawLayer	m_dw;
	BOOL			bColor;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiComboFont)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	// afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCbnKillfocus();// version 7.0
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSysColorChange();
	afx_msg void OnCloseup();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	
	afx_msg void OnCbnEditupdate();
	DECLARE_MESSAGE_MAP()
};