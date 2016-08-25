#if !defined(AFX_GUIPOWERP_H__FC88E72E_50BB_4CF7_B6DE_193D29719BD8__INCLUDED_)
#define AFX_GUIPOWERP_H__FC88E72E_50BB_4CF7_B6DE_193D29719BD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiPowerp.h : header file
//
#include "GuiPowerPointView.h"
/////////////////////////////////////////////////////////////////////////////
// CGuiPowerp window

class CGuiPowerp : public CGuiPowerPointView
{
// Construction
public:
	CGuiPowerp();
	DECLARE_DYNCREATE(CGuiPowerp)
// Attributes
public:
	CTreeCtrl	m_tree1;
	CTreeCtrl	m_tree2;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiPowerp)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGuiPowerp();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiPowerp)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIPOWERP_H__FC88E72E_50BB_4CF7_B6DE_193D29719BD8__INCLUDED_)
