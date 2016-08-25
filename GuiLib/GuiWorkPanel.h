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
#include "GuiImageLinkButton.h"

class GUILIBDLLEXPORT CGuiWorkPanel : public CGuiContainer
{
public:
	CGuiWorkPanel(void);
	virtual ~CGuiWorkPanel(void);
	virtual void	RecalLayout();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void  SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void Addlabel(UINT ID_BUTTON,CGuiLabelButton* m_btn);
	void AddImageLink(UINT ID_BUTTON,int nNumImage,CGuiImageLinkButton* m_Linkbtn);
protected:
	CGuiScrollButton m_ToolUp;
	CGuiScrollButton m_ToolDown;
	CImageList	m_imgList;
	CImageList  m_imgListLocal;
	BOOL		m_PressDown;
	BOOL		m_PressUp;
	int			m_nDif;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSysColorChange( );
	void OnDownd();
	void OnUp();
};
