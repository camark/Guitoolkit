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

#include "guicontainer.h"
#include "guiToolButton.h"
#include "GuiButton.h" 
#include "GuiButtonTimer.h"

class GUILIBDLLEXPORT CGuiPanelAccess :
	public CGuiContainer
{
public:
	CGuiPanelAccess(void);
	virtual ~CGuiPanelAccess(void);
	virtual void	RecalLayout();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void  SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void AddButton(UINT ID_BUTTON,int nNumImage,CGuiToolButton* m_pBtn,CString m_sztext);
protected:
	CGuiButtonTimer m_ToolUp;
	CGuiButtonTimer m_ToolDown;
	CImageList	m_imgList;
	CImageList  m_imgListLocal;
	BOOL		m_PressDown;
	BOOL		m_PressUp;
	int			m_nDif;
	CFont		m_cfont;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	void OnDownd();
	void OnUp();
};
