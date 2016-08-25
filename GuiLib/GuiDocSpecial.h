/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 * (MFC extension)								*			 
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

#if !defined(AFX_GUIDOCSPECIAL_H__18F3DFEE_82D2_4F88_AB42_7BD36F100842__INCLUDED_)
#define AFX_GUIDOCSPECIAL_H__18F3DFEE_82D2_4F88_AB42_7BD36F100842__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiTabWnd.h"

class GUILIBDLLEXPORT CGuiDocSpecial : public CDockBar  
{
public:
	CGuiDocSpecial();
	virtual ~CGuiDocSpecial();

public:
	void RecalTabs();
	CSize CalcDynamicLayout(int nLength, DWORD nMode);

protected:
	CGuiTabWnd  m_tabwnd;
	
protected:
	
	//{{AFX_VIRTUAL(CGuiDocSpecial)
	afx_msg void OnSize(UINT  nType, int cx, int cy);	
	afx_msg void OnNcPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_VIRTUAL
	
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GUIDOCSPECIAL_H__18F3DFEE_82D2_4F88_AB42_7BD36F100842__INCLUDED_)
