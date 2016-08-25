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

#include "guicontrolbar.h"
#include "GuiDockContext.h"

class  CGuiDockContextOffice :public CGuiDockContext
{
public:
	CGuiDockContextOffice(CControlBar* pBar) : CGuiDockContext(pBar) {}
	virtual ~CGuiDockContextOffice();
	virtual void StartDrag(CPoint pt);
protected:
	virtual void AdjustWindowForFloat(CRect& rect);

};


class GUILIBDLLEXPORT    CGuiOfficeBar :public CGuiControlBar
{
protected:
	CGuiControlBarButton  m_ArrButtons[4];
	int m_stateBtnBack;
	int m_stateBtnClose;
	int m_stateBtnFor;
	int m_stateBtnMenu;
	UINT m_nHits;
	int m_StateBtn;
	
public:
	CGuiOfficeBar(void);
	virtual ~CGuiOfficeBar(void);
	virtual void DrawGripper(CDC* pDC,CRect* rc);
	virtual void OnBack();
	virtual void OnForWard();
	virtual void OnMenu();
	void ShowTitle(CString m_Caption);
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
DECLARE_MESSAGE_MAP()
	afx_msg virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);

	
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcCalcSize(BOOL, NCCALCSIZE_PARAMS*);

};
