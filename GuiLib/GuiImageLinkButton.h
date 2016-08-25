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

#include "guitoolbutton.h"

class GUILIBDLLEXPORT CGuiImageLinkButton : public CGuiToolButton
{
	DECLARE_DYNAMIC(CGuiImageLinkButton)
public:
	CGuiImageLinkButton(void);
	virtual ~CGuiImageLinkButton(void);
	//esta funcion identa la cadenade caracteres a la derecha en el caso
	//que no exista imagen
	void AjustRightText(int nIdent){m_iDent=nIdent;}
protected:
	CFont	m_cfontSelect;
	CFont	m_cfontNormal;
	CRect	rectletra;
	int     m_iDent;
protected:
	DECLARE_MESSAGE_MAP()
	
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

class GUILIBDLLEXPORT    CGuiScrollButton :
	public CGuiToolButton
{
public:
	CGuiScrollButton(void);
	virtual ~CGuiScrollButton(void);

protected:
	DECLARE_MESSAGE_MAP()
	BOOL m_bMouserOvernew;
public:
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
};
