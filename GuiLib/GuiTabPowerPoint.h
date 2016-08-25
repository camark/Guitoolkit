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

#include "guitabwnd.h"
#include "guitoolbutton.h"

class GUILIBDLLEXPORT CGuiTabPowerPoint :public CGuiTabWnd
{
protected:
	
	CImageList m_img;
	BOOL bAutoAjust;
	COLORREF m_clrTabs;
	CGuiToolButton  m_ToolButton;
	BOOL m_bShowButton;
public:
	CGuiTabPowerPoint(void);
	virtual ~CGuiTabPowerPoint(void);
	virtual void AjustTabs();
	void SetAutoAjust(BOOL bAjust=TRUE);
	void SetColorTabs(COLORREF clrTabs);
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{m_StyleDisplay=dwDsp;SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();}
	DWORD			m_StyleDisplay;
	
public:
	void	virtual Drawtabs(CDC* dc);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void    ShowButtonClose(BOOL bShowButton=TRUE);	
	void	SetIdButtonClose(UINT uClose);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
