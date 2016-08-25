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

class GUILIBDLLEXPORT CGuiNormalButton :public CGuiToolButton
{
public:
	enum StyleBtn{STL_NORMAL=0,STL_FLAT=1,STL_SEMIFLAT=2,STL_XP=3};
public:
	CGuiNormalButton(void);
	virtual ~CGuiNormalButton(void);
	void SetStyleButton(StyleBtn StlButton);
private:
	StyleBtn m_stlbtn;
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};
