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

#if !defined(AFX_GUIHEADERCTRL_H__E0AE9E10_F6F3_4C90_B19B_1DD8107B1C0D__INCLUDED_)
#define AFX_GUIHEADERCTRL_H__E0AE9E10_F6F3_4C90_B19B_1DD8107B1C0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiHeaderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiHeaderCtrl window

class GUILIBDLLEXPORT CGuiHeaderCtrl : public CHeaderCtrl
{
// Construction
public:
	//*******************************************************
	CGuiHeaderCtrl();
	virtual ~CGuiHeaderCtrl();
	//*******************************************************
protected:
	CWnd*		m_pParentWnd;
	COLORREF	m_clrFace;
	COLORREF	m_clrShadow;
	COLORREF	m_clrLight;
	CSize		m_sizeImag;
	CImageList  m_img;
	int			m_nNumbottomSelect;
	BOOL		m_bSentido;
public:
	//***********************************************************************
	void SetImageCol(int icol,int img);
	void ReDraw(); 
	void BiselaBoton(CRect rcWin,CDC* pDC);
	void SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask);
	void ClearImages();
	void DelImageCol(int icol,int img);
	void DrawTextExt(CString Cad,CDC* pDC,CRect* rc,UINT nFlags);
	void DrawArrow(CDC* pDC,CRect rc,BOOL bUp);
	void SetSortColumn(int nCol,BOOL sentido);
	int  GetSortColumn(BOOL* bSortCol );
	void CGuiHeaderCtrl::ResizeWindow();

	//***********************************************************************	
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiHeaderCtrl)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation

protected:
	//{{AFX_MSG(CGuiHeaderCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIHEADERCTRL_H__E0AE9E10_F6F3_4C90_B19B_1DD8107B1C0D__INCLUDED_)
