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

#if !defined(AFX_GUICAPOUTBAR_H__367A6805_A544_11D5_B916_000000000000__INCLUDED_)
#define AFX_GUICAPOUTBAR_H__367A6805_A544_11D5_B916_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiMiniSplitter.h" 
#include "GuiMiniTool.h" 

class GUILIBDLLEXPORT GuiCapOutBar : public CControlBar  
{
public:
	GuiCapOutBar();
	virtual ~GuiCapOutBar();
	
public:
	BOOL	Create(DWORD dwStyle, CWnd* pParentWnd, UINT uID, int iMaxi = 32);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	void	SetStyleFlag(BOOL m_bFlag);
	BOOL	SetSplitter(CGuiMiniSplitter* m_sppliter);
	BOOL	SetMiniTool(CGuiMiniTool* m_sppliter);
	void	RecalLayout();
	
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();
	}

	DWORD	m_StyleDisplay;
	
protected:
	int			        m_iBorder;
	BOOL		        m_bIsFlag;
	int			        m_iHigh;
	UINT		        m_uID;
	CGuiMiniSplitter*	m_miniSplitter;
	CGuiMiniTool*		m_MiniTool;
	
protected:
	
	//{{AFX_MSG(GuiCapOutBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysColorChange();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	//}}AFX_MSG	
	
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GUICAPOUTBAR_H__367A6805_A544_11D5_B916_000000000000__INCLUDED_)
