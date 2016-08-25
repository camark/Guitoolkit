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

#if !defined(AFX_GUIMINITOOL_H__D4A0E123_2E03_4BF4_B22F_8E89EC901EFD__INCLUDED_)
#define AFX_GUIMINITOOL_H__D4A0E123_2E03_4BF4_B22F_8E89EC901EFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiMiniTool.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiMiniTool window

#include "GuiToolButton.h"
#include "GuiComboBoxExt.h"

//esta clase da la flexibilidad de adicionar componentes
//diferentes a botones.
class CGuiMiniTool;

class CArrButton
{
public:
	CArrButton(CGuiMiniTool* pParent,HICON m_hIcon,UINT Cmd,CFont* m_cfont,CString m_szCaption,CMenu* pMenu=NULL,CString m_ToolTip=_T(""));
	CArrButton(CGuiComboBoxExt* m_pComponent);
public:
	CGuiToolButton		   m_bt;
	CGuiComboBoxExt*      m_pwnd;
	int				   m_btipo;  //es un boton o un derivado de Cwnd

};


class GUILIBDLLEXPORT CGuiMiniTool : public CStatic
{
// Construction
public:
	CGuiMiniTool();
public:
	enum Borders{STYLEFLAT=0,STYLE3D=1,STYLEPRESS=2,STYLEFRAME=3};
	enum Aling{	ALIGN_LEFT=0,ALIGN_RIGHT=1};
// Attributes
public:
	//*********************************************************************
	void  AddButton(int nIndex,UINT Cmd,CMenu* pMenu=NULL,CString m_szCaption=_T(""),CString m_ToolTip=_T(""));
	BOOL  CreateCombo(CGuiComboBoxExt* pControl,UINT nID,int iSize,
				DWORD dwStyle=WS_CHILD|WS_VISIBLE|CBS_AUTOHSCROLL|
				CBS_DROPDOWNLIST|CBS_HASSTRINGS);
	void  SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void  DelButton(int nIndex);
	int   GetCountButton();
	void  RecalLayout();
	void  SetCaption(CString mSzCaption,Aling AlinText);
	//*********************************************************************
	void  SetBorder(Borders Style);
	void  SetColor(COLORREF m_clrface);
	void  AlingButtons(Aling Alingsb);
	void  AutoSize(BOOL mbAutosize);
	void  CalcAutoSize(CRect m_rc);
	void  SetColorCaption(COLORREF	clrCaption);
	void  Drawtext();
	HICON GetImagIcon(int nNum);
	CGuiToolButton* GetButton(UINT uID_Object);//,CGuiToolButton* m_btn);
	
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		for (int i=0; i < nNumItems;i++)
    		if (((CArrButton*) m_arrButtons [i])->m_btipo ==TRUE)
			{
				((CArrButton*) m_arrButtons [i])->m_bt.StyleDispl(dwDsp);
				((CArrButton*) m_arrButtons [i])->m_bt.SetColor(m_clrface);
			}
			SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();
	}

	DWORD			m_StyleDisplay;
// Operations
protected:
   CPtrArray	m_arrButtons;
   CImageList	m_imgList;
   COLORREF		m_clrface;
   int			nNumItems;
   Borders		m_border;
   Aling		m_AlingButton;		
   BOOL			m_bAutoSize;
   int			m_nResultCombo;
   int			m_nResultButtons; 
   BOOL			m_bExisteCombo;
   CFont		m_cfont;	   
   CString		m_Caption;		
   COLORREF		m_clrCaption;
   CSize		msz;
   Aling		m_AlinTexto;
   CRect	    m_rcDrawTexto;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiMiniTool)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGuiMiniTool();
	virtual void PreSubclassWindow();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiMiniTool)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint(); 
	afx_msg void OnSysColorChange( );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnDestroy();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIMINITOOL_H__D4A0E123_2E03_4BF4_B22F_8E89EC901EFD__INCLUDED_)
