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

#if !defined(AFX_GUICOMBOBOXEXT_H__4E237771_A1F4_11D5_A8C4_0008C7B2934C__INCLUDED_)
#define AFX_GUICOMBOBOXEXT_H__4E237771_A1F4_11D5_A8C4_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CGuiComboBoxExt.h : header file
//

#include "GuiDrawLayer.h"

/////////////////////////////////////////////////////////////////////////////
// CGuiComboBoxExt window

class GUILIBDLLEXPORT CGuiComboBoxExt : public CComboBox
{
// Construction
public:
	CGuiComboBoxExt();
	virtual		~CGuiComboBoxExt();

// Attributes
public:
	
// Operations
public:
	enum enTypeShow{CM_NORMAL=0,CM_ONFOCUS,CM_SELECCIONADO};

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
	void		DrawCombo(enTypeShow enShow,CDC* pDC);
	void		DrawArrow(CDC* pDC,CRect m_rc);
	void		SetColor(COLORREF clrFace);
	void        AutoColor(BOOL bColor=TRUE);
	int			AddString(LPCTSTR lpszString);
	void        ActiveHistory(BOOL bHistory);
	void		LoadHistory(CString szHistory,BOOL bLoadCurrent);
	void		SaveHistory(CString szHistory,BOOL bSaveCurrent);
	void		DeleteHistory(CString szHistory);
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
		
	// Generated message map functions
protected:
	CImageList		m_imgArrow; //imagen arrow
	CPoint			mHeight;
	GuiDrawLayer	m_dw;
	BOOL			bColor;
protected:
	//{{AFX_MSG(CGuiComboBoxExt)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	//afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCbnKillfocus();//version 7.0
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSysColorChange( );
	afx_msg void OnCloseup();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnCbnEditupdate();
	afx_msg void OnCbnSelchange();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUICOMBOBOXEXT_H__4E237771_A1F4_11D5_A8C4_0008C7B2934C__INCLUDED_)
