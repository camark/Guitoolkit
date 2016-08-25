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

// CGuiListEdit
#include "GuiContainer.h"
#include "GuiMiniTool.h"
#include "GuiNormalButton.h"

class GUILIBDLLEXPORT CGuiListEdit : public CStatic
{
	DECLARE_DYNAMIC(CGuiListEdit)
public:
	enum Border{STYLE3D=0,STYLEPRESS=1,STYLEFRAME=2};
private:
	CGuiContainer	m_Conta;
	CGuiMiniTool	m_MiniTool;
	CListCtrl*		m_list;
	COLORREF		m_clrface;
	Border			m_border;
	BOOL			m_bChange;
public:
	void Delete();
	void Insert();
	void Up();
	void Down();
	void SetStyle(Border border);
	CString GetText(int nItem);
	void AddItem(CString m_szCad);
	int GetNumItem();
	CGuiNormalButton m_toolBtn;
	CListCtrl* GetListCtrl();
public:
	CGuiListEdit();
	virtual ~CGuiListEdit();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditList(NMHDR *pNMHDR, LRESULT *pResult);
};


