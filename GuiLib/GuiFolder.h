/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *                            (MFC extension)								*			 
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

#if !defined(AFX_GUIFOLDER_H__44CCC3EF_FC44_4877_94C7_61A7ACB0E216__INCLUDED_)
#define AFX_GUIFOLDER_H__44CCC3EF_FC44_4877_94C7_61A7ACB0E216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGuiFolder window

class CFolderBar
{
public:
	CFolderBar(CWnd* m_wnd, LPCSTR lp_msg, UINT uImg = (UINT) - 1);
public:
	CWnd*	m_Cwnd;
	LPCSTR	m_lpMsg;
	UINT	m_img;
	CRect	m_rect;
	BOOL	m_posUp;
};

class GUILIBDLLEXPORT CGuiFolder : public CWnd
{
	DECLARE_DYNAMIC(CGuiFolder)

	// Construction
public:
	CGuiFolder();
	virtual ~CGuiFolder();

public:
	enum Style
	{
		mNormal	= 0,
		mPush	= 1,
		mFlat	= 2
	};

	enum TypeFolder
	{
		mOutlook = 0,
		mToolBox = 1
	};
	
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow(); 

public:
	void			AddFolder(CWnd* pParent, LPCSTR lpMsg, UINT uIMg = (UINT) - 1);
	void			DeleteFolder(int m_iNumFolder, BOOL bUpdate = TRUE);
	void			RecalLayout();
	virtual void	DrawFolder(CFolderBar* cfb, Style m_Style);
	int				PointInFolder(CPoint pt);
	void			EfectoScroll();
	void			RemoveAllFolder();
	void			TypeLook(TypeFolder tol);
	void			SelectFolder(int m_iNumFolder);
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();
	}

	DWORD	m_StyleDisplay;

protected:
	CPtrArray		m_ArrayFolder;
	CToolTipCtrl	m_ToolTip;
	int				m_NumFolders;   // total de folders
	int				m_numFolderDown;
	int				m_numFolderUp;   // numero de folders arriba
	CFont*			cfont;
	int				m_iSelected;
	int				m_ultimoFolderResal;
	int				m_iPosDown; // a partir de donde se ubica el anterior folder
	int			    m_iposUp;   // a partir de donde se ubica el siguiente folder
	int				m_itemp;
	int				m_AntFolder; // folder anterior
	TypeFolder		m_typel;	// tipo de look
	int				m_iWhatFolderIsDrawNow; // que folder estoy pintando

protected:
	//{{AFX_MSG(CFolder)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIFOLDER_H__44CCC3EF_FC44_4877_94C7_61A7ACB0E216__INCLUDED_)
