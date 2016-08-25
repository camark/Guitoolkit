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

#if !defined(AFX_GUIRADIOBUTTON_H__B0A3DCE3_0F46_43C1_B4EB_7EFCEA8F57E7__INCLUDED_)
#define AFX_GUIRADIOBUTTON_H__B0A3DCE3_0F46_43C1_B4EB_7EFCEA8F57E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiRadioButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiRadioButton window

class GUILIBDLLEXPORT CGuiRadioButton : public CButton
{
	DECLARE_DYNAMIC(CGuiRadioButton);
// Construction
public:
	CGuiRadioButton();

// Attributes
public:
	BOOL m_SelectBtn;
	BOOL m_bOldCheck;
	BOOL m_bPressBtn;
	CRect m_rc;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiRadioButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGuiRadioButton();
	void UnCheckRadio();
	void CheckRadio(CDC* pDC,CRect m_rcTemp); 
	void DrawEllipse(CDC* pDC,CRect m_rc);
	void SetCheck(int nCheck);
	void DrawOrange(CDC* pDC,CRect m_rc);
	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiRadioButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIRADIOBUTTON_H__B0A3DCE3_0F46_43C1_B4EB_7EFCEA8F57E7__INCLUDED_)
