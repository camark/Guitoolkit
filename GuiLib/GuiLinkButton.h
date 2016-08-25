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

#if !defined(AFX_GUILINKBUTTON_H__DAEC7876_F23A_11D4_9617_0008C7B2934C__INCLUDED_)
#define AFX_GUILINKBUTTON_H__DAEC7876_F23A_11D4_9617_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGuiLinkButton window

//***********************************************************
class GUILIBDLLEXPORT CGuiLinkButton : public CButton
{
// Construction
public:
	//*****************************************
	CGuiLinkButton();
	virtual ~CGuiLinkButton();
	//*****************************************

public:

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();

public:

	void SetLink(LPCTSTR lpMsg);
	void SetToolTip(LPCTSTR lpToolTip);
	void SetColorNormal(COLORREF m_clnor);
	void SetColorSelect(COLORREF m_clselec);

protected:

	COLORREF	 m_clNormal;
	COLORREF	 m_clover;
	CString		 m_Link;
	CToolTipCtrl m_ToolTipCtrl;
	CFont		 m_cfont;
	int			 m_iSelected;
	CRect		 m_rectMsg;
	BOOL		 m_bFirstPas;
	HCURSOR		 m_hCursor;
	// Generated message map functions
protected:

	//{{AFX_MSG(CGuiLinkButton)
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnTimer(UINT nIDEvent);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUILINKBUTTON_H__DAEC7876_F23A_11D4_9617_0008C7B2934C__INCLUDED_)
