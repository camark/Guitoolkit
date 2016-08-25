// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__5E3ABF70_6851_4024_B3CD_377C21C50496__INCLUDED_)
#define AFX_MAINFRM_H__5E3ABF70_6851_4024_B3CD_377C21C50496__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiFrameWnd.h"
#include "GuiSplitterWnd.h"
#include "GuiBarOffice.h"
#include "guitabbedpp.h"
#include "GuiComboBoxExt.h"
class CMainFrame : public CGuiFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
protected:
	CGuiSplitterWnd	m_wndSplitter;
	CGuiBarOffice m_OfficeBar;
	CGuiTabbedPP	m_tb;
	CSplitterWnd	m_wndSplitter1;
	CGuiComboBoxExt	 m_combMenu;
	CGuiComboBoxExt  m_comboZoom;
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEmail();
	afx_msg void OnOrtografia();
	afx_msg void OnPreview();
	afx_msg void OnBuscar();
	afx_msg void OnGrafico();
	afx_msg void OnBack();
	afx_msg void OnForward();
	afx_msg void OnTabla();
	afx_msg void OnGrises();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__5E3ABF70_6851_4024_B3CD_377C21C50496__INCLUDED_)
