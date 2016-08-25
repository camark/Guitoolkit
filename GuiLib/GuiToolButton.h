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


// CGuiToolButton

class GUILIBDLLEXPORT   CGuiToolButton : public CButton
{
	DECLARE_DYNAMIC(CGuiToolButton)

public:
	CGuiToolButton();
	virtual ~CGuiToolButton();
public:
	void SetToolTip(LPCTSTR szToolTip);
	void SetCaption(CString szCaption);
	void SethIcon(HICON hIcon);
	void SetColor(COLORREF clColor);
	void RecalSize();
	void ShowDark(BOOL bShow);
	CSize GetSizeButton();
    void ShowMenu();
	void SetScrollButton(BOOL bScroll=TRUE);
	void SetSimpleButton(BOOL bSimple=TRUE){m_bSimple=bSimple;};
	void SetFontColor(COLORREF clrFont);
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP,BOOL bTransParent=TRUE)
	{m_StyleDisplay=dwDsp;
	m_Transparent=bTransParent;
	SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();}
	DWORD			m_StyleDisplay;
	BOOL			m_Transparent;
protected:
	CToolTipCtrl m_toolTip;
	HICON		 m_Icon;
	CSize		 m_SizeImage;
	CSize		 m_SizeText;
	CString		 m_szText;
	COLORREF	 m_clColor;
	BOOL		 m_bMouserOver;
	BOOL		 m_ReposWindow;
	CSize		 m_szButton;
	BOOL		 m_bShowDark;
	BOOL		 m_ScrollButton;	
	COLORREF	 m_clrFont;
	BOOL		 m_bSimple;

public:
	HMENU		 m_hMenu;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
	afx_msg void OnSysColorChange( );
};


