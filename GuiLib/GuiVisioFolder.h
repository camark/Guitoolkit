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
#include "guifolder.h"

class GUILIBDLLEXPORT CGuiVisioFolder :	public CGuiFolder
{
	DECLARE_DYNAMIC(CGuiVisioFolder)
protected:
	CImageList	m_Img;
	
public:
	void  SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	virtual void DrawFolder(CFolderBar* cfb,Style m_Style);
public:
	CGuiVisioFolder(void);
	virtual ~CGuiVisioFolder(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nHitTest, CPoint point);
	
};
