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


// CGuiSplitter
#include "GuiDrawlayer.h"

class GUILIBDLLEXPORT   CGuiSplitter : public CWnd
{
	DECLARE_DYNAMIC(CGuiSplitter)
public:
	enum TYPEALING {ALINGHORZ=0,ALINGVERT=1};
	enum STYLESEPARATOR{STYLE3D=0,STYLEFLAT=1};
	void SetColor(COLORREF m_clrface);
	void AddLeftCtrl(CWnd* pWnd,long MinSize);
	void AddRightCtrl(CWnd* pWnd,long MinSize);
	void SeTypeALing(TYPEALING typeAling);
	void SetPixelWidht(int nSizePix);
	void RecalLayout();
	virtual void DrawSplitter(CRect rcSeparator,CRect rcLeft,CRect rcRight,CDC* pDC);
	void SetStyleSeparator(STYLESEPARATOR StyleSeparator=STYLE3D,COLORREF clrLeftTop=GuiDrawLayer::GetRGBColorBTNHigh(),
							COLORREF clrBottomRight=GuiDrawLayer::GetRGBColorShadow());
	
public:
	CGuiSplitter();
	virtual ~CGuiSplitter();
protected:
	COLORREF	clrBg;
	CWnd*		pWndLeft;
	CWnd*		pWndRight;
	TYPEALING	TypeAling;
	CRect		m_rcSpplitter;
	int			m_nSizePix;
	CRect		m_rcSpplitterOld;
	BOOL		bIniciaArrastre;
	STYLESEPARATOR mStyleSeparator;
	COLORREF	mclrLeftTop;
	COLORREF	mclrBottomRight;
	CRect		m_rectLeft;
	CRect		m_rectRight;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(CWnd* pParentWnd);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


