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


#if !defined(AFX_GUITOOLBARWND_H__EA24A3ED_2C8D_401D_AA89_0515F80714FA__INCLUDED_)
#define AFX_GUITOOLBARWND_H__EA24A3ED_2C8D_401D_AA89_0515F80714FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiDocbarExten.h"

class GUILIBDLLEXPORT CGuiToolBarWnd : public CToolBar  
{
	DECLARE_DYNAMIC(CGuiToolBarWnd)
public:
	
	enum StyleG
	{
		Office97   = 0,
		Office2000 = 1
	};	
	//*******************************************************	
				 CGuiToolBarWnd();
	virtual		~CGuiToolBarWnd();
	//*******************************************************

public:
	
	//***********************************************************************
	void	DrawGripper(CWindowDC* dc, CRect* rcWin);
	void	setStyleG(StyleG style) 
	{
		m_style = style;
		OnNcPaint();
	}

	//************************************************************************
	void	OnNcPaint();
	//************************************************************************
	BOOL	CreateCombo(CComboBox* pControl,UINT nID,int iSize,
				DWORD dwStyle=WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST | CBS_SORT | 
                    WS_VSCROLL | WS_TABSTOP);

	BOOL	CreateCombo(CComboBoxEx* pControl,UINT nID,
				int iSize,CImageList* m_imgList,
				DWORD dwStyle=WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST | CBS_SORT | 
                    WS_VSCROLL | WS_TABSTOP);
	
	//*************************************************************************
	void	AddRowComBoboxEx(CComboBoxEx* pControl,CString szMsg,int iItem,int iImage);
	void	SetButtonDropDown(UINT nID,int iImage,UINT nMENU);
	void	SetButtonDropDown(UINT nID,int iImage,CWnd* pWnd,LPCTSTR lpTitle=_T(""));
	BOOL	OnDropDown(NMHDR* pNMHDR, LRESULT* pRes);
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );	
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	void	DrawArrow(CDC* pDC,CRect m_rc);
	void	SetTextButton(int IdButton,CString sztexto);
	void	RestoreState();
	void	SetTextOptions();
	HMENU	LoadMenu(HMENU hmenu);
	void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{m_StyleDisplay=dwDsp;SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();}
	void SetRealSize();
	CSize CalcLayout(DWORD nMode, int nLength = -1);
	CSize CalcSize(TBBUTTON* pData, int nCount);
	int WrapToolBar(TBBUTTON* pData, int nCount, int nWidth);
	void SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert = FALSE);
	void _GetButton(int nIndex, TBBUTTON* pButton) const;
	void _SetButton(int nIndex, TBBUTTON* pButton);
	void SetMenuContext(UINT MnuContext) {MenuContext=MnuContext; };
	BOOL IsAutoHide(){return FALSE;}
	int GetLastPos();
	int GetFirstPos();
	CRect GetDockRect();
	int GetHiWid();
	BOOL IsLeft();
	BOOL IsRight();
	BOOL IsTop();
	BOOL IsBottom();
	BOOL IsVert();
	BOOL IsHorz();
	BOOL IsFloating();
//	void LockEspecial();
//	void UnLockEspecial();
protected:
	UINT			m_style;
	BOOL			m_pinta;
	int				m_iElements;
	BOOL			m_bIsXp;
	CPoint			mHeight;
	CPtrArray		m_pArray;	//submenus para botones dropdown
	CImageList		m_imgArrow; //imagen arrow
	CRect			m_rcBtnGlobal; //repaint button
	int				m_iWidthDrowDown;
	int				m_iSelected;
	CFont			m_cfont;
	BOOL			bVertDocked;
	BOOL			bOver;
	BOOL			bPressDown;
	UINT			nDockBarAling;
	UINT			MenuContext;
	UINT			m_idLock;
	CImageList		m_imgList;
	BOOL			bLoad;
	int				m_ActualBtn;
	CRect			m_rcSaveFloat;
	DWORD			m_StyleDisplay;
protected:

	//{{AFX_MSG(CGuiToolBar)
	afx_msg void OnPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point) ;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point) ;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point) ;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point) ;
	afx_msg void OnNcLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSysColorChange( );
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	//}}AFX_MSG(CGuiToolBar)

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_GUITOOLBARWND_H__EA24A3ED_2C8D_401D_AA89_0515F80714FA__INCLUDED_)
