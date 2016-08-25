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

// CGuiSysTray

class GUILIBDLLEXPORT  CGuiSysTray : public CWnd
{
	DECLARE_DYNAMIC(CGuiSysTray)

public:
	CGuiSysTray();
	virtual ~CGuiSysTray();
	BOOL Add(UINT uID, UINT uCallBackMessage, HICON hIcon, LPCTSTR lpszTip);
	BOOL Del();
	BOOL Update(UINT uID, HICON hIcon, LPCTSTR lpszTip);
	BOOL SetIcon(HICON hIcon);
	BOOL SetIcon(LPCTSTR lpszIcon);
	BOOL SetTips(LPCTSTR lpszTip);
	void SetSysMenu(CMenu* pMenu);
	void SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void StartAnimation(int nMilliseconds,int nPosInit, int nPosEnd);
	void StopAnimation();
protected:
	NOTIFYICONDATA tnid;
	CMenu* m_pMenu;
	CImageList	m_ImgList;
	BOOL	m_bStartAnimation;
	int		m_ActualImage;
	int		m_Init;
	int     m_End;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(CWnd* pParentWnd, UINT nID,UINT uCallBackMessage, HICON hIcon, LPCTSTR lpszTip);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT nIDEvent);
};


