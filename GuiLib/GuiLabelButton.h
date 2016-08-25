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

class GUILIBDLLEXPORT CGuiLabelButton : public CGuiToolButton
		
{
		DECLARE_DYNAMIC(CGuiLabelButton)
public:
	CGuiLabelButton(void);
	virtual ~CGuiLabelButton(void);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void DrawUnderLine(BOOL bDraw=TRUE){m_bDrawLine=bDraw; Invalidate(); UpdateData();};
protected:
	CFont	m_cfont;
	BOOL	m_bDrawLine;
};
