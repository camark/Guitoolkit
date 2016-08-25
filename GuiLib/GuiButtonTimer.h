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

#if !defined(AFX_GUIBUTTONTIMER_H__2F022AE8_E4A9_444C_8827_AA1D82AC5BE0__INCLUDED_)
#define AFX_GUIBUTTONTIMER_H__2F022AE8_E4A9_444C_8827_AA1D82AC5BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiToolButton.h" 

class GUILIBDLLEXPORT CGuiButtonTimer : public CGuiToolButton  
{
public:
	CGuiButtonTimer();
	virtual ~CGuiButtonTimer();
	void SetWaitClick(int nInterval = 50){m_nInterval = nInterval;}

protected:
	BOOL	bPress;
	int		m_nInterval;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_GUIBUTTONTIMER_H__2F022AE8_E4A9_444C_8827_AA1D82AC5BE0__INCLUDED_)
