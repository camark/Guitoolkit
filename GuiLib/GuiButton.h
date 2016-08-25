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

#if !defined(AFX_SBUTTON_H__94947860_0E28_43E3_9F81_E966EF769ABE__INCLUDED_)
#define AFX_SBUTTON_H__94947860_0E28_43E3_9F81_E966EF769ABE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSButton window


//*****************************************************************

class GUILIBDLLEXPORT  CGuiButton : public CButton
{
	// Construction
public:
	
	//*************************************************
	CGuiButton();
	virtual ~CGuiButton();
	//*************************************************
	
	enum Style // Disposicìón del estilo
	{	
		STYLE_3D       = 0,
		STYLE_SEMIFLAT = 1,
		STYLE_FLAT     = 2,
		STYLEXP        = 3
	};

	enum AlingMsg  // alineacion del Mensaje
	{
		ALING_LEFT = 0, 
		ALING_RIGTH = 1
	};
	
	enum TypeButton
	{ 
		TYPE_NORMAL = 0, // Un boton normal
		TYPE_ARROW  = 1, // un Boton con flecha por lo general para menus
		TYPE_LINK   = 2  // Un boton con links
	};
	
	enum StyleArrow
	{
		ARROW_RIGHT = 0, // el flecha va a la derecha
		ARROW_DOWN  = 1  // el flecha va  hacia abajo
	};
	
public:	
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();

public:
	//*********************************************************
	void	SetToolTip(LPCTSTR lpMsg); // pone tooltip al boton
	void	SetCaption(LPCTSTR lpMsg);	// pone un mensaje en el boton
	void	SetStyleBorder(Style m_Style = STYLE_3D);  // el boton es 3d semiflat estilo xp, etc
	void	SetTypeButton(TypeButton m_TypeButton = TYPE_NORMAL); 
	void	SetAlingArrow(StyleArrow m_AlingArron = ARROW_RIGHT);
	void	DrawBottonXP(CDC* pDC, CRect rc, BOOL bPress);
	BOOL	SetImage(UINT uBitmapNormal, UINT uBitmapFoco = (UINT) - 1,
		UINT uBitmapPush = (UINT) - 1);
	void	SetImage(HICON hIcon);
	void	SetAlingMsg(AlingMsg m_AlingMsg = ALING_LEFT);
	void	ShowImage(BOOL m_viewimage = TRUE);
	void	ShowText(BOOL m_viewText = TRUE);
	void	ShowMenu();
	void	CalLayout();
	void    SetColor(COLORREF m_clrFace);
	CSize	GetSizeButton();
	void    SetDarkButton(BOOL bDark)
	{
		m_bIsDark = bDark;
	};
	void    AutoSizeButton(BOOL m_bAutoAjust = TRUE);
	void    SetPopupMenu(CMenu* pMenu);
	//********************************************************
	
protected:
	CMenu* m_pMenu;
	//********************************************************
	CToolTipCtrl	m_ToolTipCtrl;
	int				m_iAling;	// message aling
	int				m_iStyle;   // Border Style
	int				m_iTypeButton; // Style bottom (Arrow,Normal,Link)
	int				m_iSelected;
	int				m_iStyleArrow;
	HICON			m_hicon[3];	
	LPCTSTR			m_lpMsg;
	BOOL			m_viewImage;
	BOOL			m_ViewText;
	int				m_iResMenu;
	BOOL			m_iMenuActivo;
	COLORREF		m_clrface;
	CSize			m_szButton;
	BOOL			m_ReposWindow;
	BOOL			m_bIsDark;
	// *******************************************************
public:
	HMENU			m_hMenu;
protected:
	
	//{{AFX_MSG(CSButton)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SBUTTON_H__94947860_0E28_43E3_9F81_E966EF769ABE__INCLUDED_)
