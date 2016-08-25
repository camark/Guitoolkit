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

#if !defined(AFX_GUITABWND_H__4C966B28_CE7A_407D_9A7A_9BE7A80B395D__INCLUDED_)
#define AFX_GUITABWND_H__4C966B28_CE7A_407D_9A7A_9BE7A80B395D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabWnd window

#include "GuiDrawlayer.h"

//*********************************************************
class GUILIBDLLEXPORT  CGuiTabWnd : public CWnd
{
// Construction

public:

	//************************************************
	CGuiTabWnd();
	virtual ~CGuiTabWnd();
	//************************************************

	enum Style{S3D=0,FLAT=1,SHADOW=2};
	enum AlingTab{ALN_TOP=0,ALN_BOTTOM=1};
	enum TypeTab{TYPE_NORMAL=0,TYPE_MDI=1};

public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

public:
	//***********************************************************************	
	void	SetStyle(Style estyle);
	void    SetTypeTab(TypeTab Type=TYPE_NORMAL);
	void	virtual Drawtabs(CDC* dc);
	void	Addtab(CWnd* pParent,CString lpMsg,UINT uIcon);
	void	SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void	RecalLayout();
	virtual void AjustTabs();
	void    SetCurtab(int m_numtab);
	int     GetCurtab();
	void    DeleteTab(int m_numTab);
	void	ShowTitle(CString m_Caption);
	CWnd*   GetActiveWnd () const;
	CWnd*   GetNumWnd(int m_numtab)  const;
	int     GetCount(){return m_Numtabs;}
	void	SetActualTitle(BOOL bActual);
	void    SetALingTabs(AlingTab alnTab);
	BOOL	FindItem(HWND hWnd);
	void    UpdateCaption(CWnd* pWnd,CString m_Title);
	void    SetTabsTitle(int iTabNr, CString sNewTitle);
	void    SetTabMenu(UINT nMENU,int nNumTab=0);
	
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{m_StyleDisplay=dwDsp;SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();}
	DWORD			m_StyleDisplay;
	//***********************************************************************
	
	
protected:
	TypeTab			m_TypeTab;
	BOOL			m_ActualTitle;
	CPtrArray		m_pArray;
	CSize			m_sizeImag;
	int				m_Numtabs;
	int				m_iMinValRec;
	int				m_ActualVar;
	int				m_iSelectTab;
	CRect			m_rectCliente;
	CRect			m_rectTab;
	CToolTipCtrl	CToolTip;
	CImageList		Image;
	CFont			m_cfont;
	CFont			m_cfontBold;
	BOOL			m_style;
	GuiDrawLayer	m_wd;
	CWnd*			pParent;
	AlingTab		m_alnTab;
	BOOL			m_InTab;

protected:

	//{{AFX_MSG(CGuiTabWnd)
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnPaint();
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnSysColorChange( );
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
	afx_msg void OnDestroy();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUITABWND_H__4C966B28_CE7A_407D_9A7A_9BE7A80B395D__INCLUDED_)
