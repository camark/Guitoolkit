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

#pragma once

// CGuiDropDownEdit
#include "GuiEdit.h"
#include "GuiNormalButton.h"

class GUILIBDLLEXPORT CGuiDropDownEdit : public CStatic
{
	DECLARE_DYNAMIC(CGuiDropDownEdit)
public:
	enum Border{STYLE3D = 0, STYLEPRESS = 1, STYLEFRAME = 2};
	
protected:
	CGuiEdit m_Edit;
	CGuiNormalButton m_toolBtn;
	BOOL bShowButton;
	Border m_border;
	CFont m_cfont;
	
public:
	CGuiDropDownEdit();
	virtual ~CGuiDropDownEdit();
	void ShowButton(BOOL bShow = TRUE);
	void SetImageButton(HICON hIcon);
	void SetStyle(Border border);
	void SetToolTipEdit(CString szToolTop);
	void SetToolTipBtn(CString szToolTop);
	void SetMask(CString mszMask, CString mszShowMask, CGuiEdit::Mask enTypeMask);
	CString GetText();
	void SetText(CString szCaption);
	void OnDropButton();
	void SetLimitText(int numText);
	
protected:
	DECLARE_MESSAGE_MAP()
		virtual void PreSubclassWindow();
	void CreateControls();
	
public:
	afx_msg void OnNcPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
