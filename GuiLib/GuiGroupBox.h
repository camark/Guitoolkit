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



#if !defined(AFX_GUIGROUPBOX_H__C7AAD4CA_1B37_42E8_8F08_AEF18BA77DFD__INCLUDED_)
#define AFX_GUIGROUPBOX_H__C7AAD4CA_1B37_42E8_8F08_AEF18BA77DFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiGroupBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiGroupBox window

class GUILIBDLLEXPORT CGuiGroupBox : public CButton
{
// Construction
public:
	CGuiGroupBox();
	enum Aling{ALING_LEFT=0,ALING_RIGHT=1,ALING_DOWN=2, ALING_UP=3};
// Attributes
public:
   void SetStyle(Aling AlingStyle);
   void SetCaption(CString Caption);
   Aling m_style;
   COLORREF  m_clrface;
   COLORREF  m_clrShadow;
   CString   m_Caption;
// Operations
public:
	virtual void PreSubclassWindow();
public:
	virtual ~CGuiGroupBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiGroupBox)
	afx_msg void OnPaint();
	afx_msg void OnSysColorChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIGROUPBOX_H__C7AAD4CA_1B37_42E8_8F08_AEF18BA77DFD__INCLUDED_)
