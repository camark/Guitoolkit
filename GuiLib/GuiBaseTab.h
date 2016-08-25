/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *                           (MFC extension)								*			 
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

// CTab.h : implementation file
#if !defined(AFX_CBASETAB_INCLUDED_)
#define AFX_CBASETAB_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGuiTab 
{
public:
	CGuiTab(CWnd* mpParent, CString mlpMsg, UINT muIcon = -1)
	{
		pParent	= mpParent;
		lpMsg	= mlpMsg;
		uIcon	= muIcon;
		nMenu   = 0;
		rect.SetRectEmpty();
	}
	
	void AddMenu(UINT nMENU)
	{
		nMenu = nMENU;
	}
	
public:
	UINT    nMenu;
	CWnd*	pParent;
	CString	lpMsg;
	UINT	uIcon;
	CRect	rect;
	COLORREF 	m_clrLTab; //new field for theme 2003
	COLORREF	m_clrHtab;
};



#endif