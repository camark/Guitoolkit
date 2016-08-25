// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F45FF51D_1F5D_4B88_8C75_DF81C6313D12__INCLUDED_)
#define AFX_MAINFRM_H__F45FF51D_1F5D_4B88_8C75_DF81C6313D12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiMDIFrame.h"
#include "GuiBarOffice.h"
#include "guitabbedpp.h"
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
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void OnComboMenu();

protected:  // control bar embedded members
CGuiBarOffice m_OfficeBar;
CGuiComboBoxExt m_combMenu;
CGuiTabbedPP	m_tb;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewOfficebar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnOfficebar();
	afx_msg void OnViewToolbar();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F45FF51D_1F5D_4B88_8C75_DF81C6313D12__INCLUDED_)
