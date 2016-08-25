// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F51D87F2_7144_425D_9E7E_71E084FE67EB__INCLUDED_)
#define AFX_MAINFRM_H__F51D87F2_7144_425D_9E7E_71E084FE67EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiMDIFrame.h"
#include "GuiContainer.h"
#include "GuiPanelAccess.h"
class CMainFrame : public CGuiMDIFrame
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CGuiContainer m_ctSolution;
	CTreeCtrl	  m_tree;
	CGuiPanelAccess m_panAcc;
	CGuiToolButton  m_btn1;
	CGuiToolButton  m_btn2;
	CGuiToolButton  m_btn3;
	CGuiToolButton  m_btn4;
	CGuiToolButton  m_btn5;
	CGuiToolButton  m_btn6;
	CGuiToolButton  m_btn7;
	CGuiToolButton  m_btn8;
	CGuiToolButton  m_btn9;
	CGuiToolButton  m_btn10;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrop();
	afx_msg void OnPanels();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnTest();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F51D87F2_7144_425D_9E7E_71E084FE67EB__INCLUDED_)
