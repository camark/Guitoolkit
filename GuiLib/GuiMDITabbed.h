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

#include "guitabbed.h"

class GUILIBDLLEXPORT CGuiMDITabbed :public CGuiTabbed
{
public:
	CGuiMDITabbed(void);
	virtual ~CGuiMDITabbed(void);
protected:
	CWnd* pParentWindow;
	CGuiTabbed m_GuiTabbed;
	DECLARE_MESSAGE_MAP();
	void  virtual OnScrollClose();
	BOOL bFirst;
	UINT hMenu;
public:
	void UpdateWindows();
	void SetTabsMenu(UINT uMenu){hMenu=uMenu;};
	afx_msg LRESULT OnSizeParent(WPARAM, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);

};
