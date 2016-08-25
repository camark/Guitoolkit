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

#include "guitabwnd.h"
#include "GuiDrawLayer.h" 
#include "GuiComboBoxExt.h" 
class GUILIBDLLEXPORT CGuiTabbed :	public CGuiTabWnd
{
	enum ExtTab{NORMAL_TAB=0,COMBO_TAB=1};
	
protected:
	GuiTabbedButton m_toolBtn[2];
	CGuiToolButton m_toolBtnC;
	CGuiComboBoxExt  m_comboxBox;
	CImageList   m_img;
	CSize        m_sizeBtn;
	int			 m_nDif;
	ExtTab		 m_ExtTab;
public:
	CGuiTabbed(void);
	virtual ~CGuiTabbed(void);
public:

	void	virtual Drawtabs(CDC* dc);
	void	SetExtileExt(ExtTab= NORMAL_TAB);
	CSize   GetSizeButton();
	void  OnScrollLeft();
	void  OnScrollRight();
	void  virtual OnScrollClose();
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
	 m_StyleDisplay=dwDsp;
	  SendMessage(WM_NCPAINT);
	 Invalidate(); UpdateWindow();
	}
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual afx_msg void OnSysColorChange( );
	afx_msg void OnSelchangeCombo1();
};
