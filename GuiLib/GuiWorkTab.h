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

#if !defined(AFX_GUIWORKTAB_H__A711D725_2268_4750_B58E_5218AD3BC0A5__INCLUDED_)
#define AFX_GUIWORKTAB_H__A711D725_2268_4750_B58E_5218AD3BC0A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiTabWnd.h"
#include "GuiDrawlayer.h"
#include "GuiMiniTool.h"
#include "GuiDrawLayer.h" 

//****************************************************************

class GUILIBDLLEXPORT  CGuiWorkTab : public CGuiTabWnd  
{
public:
	
	//***************************************
		CGuiWorkTab();
		virtual ~CGuiWorkTab();
	//***************************************

public:

	void  virtual Drawtabs(CDC* dc);
	void  OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
	void  PintaSeparador(CDC* dc);
	void  OnSpiNiz();
	void  OnSpiNde();	
	void  SizeScroll();
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{m_StyleDisplay=dwDsp;
	 SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();}
protected:
	

	CScrollBar		m_spin;
	GuiTabbedButton	m_toolBtn[2];
	CScrollBar		m_scroll;
	CFont			m_cfont;
	BOOL			m_PresRight;
	BOOL			m_PresLeft;
	int				m_deplaza;
	CRect			m_btndesplaza;
	BOOL			bIniciaArrastre;
	GuiDrawLayer	m_wd;
	BOOL			m_EnableL;
	BOOL			m_EnableR;
	CImageList		m_img;
protected:

	//{{AFX_MSG(CGuiWorkTab)
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
		afx_msg void OnSysColorChange(); 
		afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#endif // !defined(AFX_GUIWORKTAB_H__A711D725_2268_4750_B58E_5218AD3BC0A5__INCLUDED_)
