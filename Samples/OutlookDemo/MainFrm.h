// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__98E93E6D_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
#define AFX_MAINFRM_H__98E93E6D_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiCapOutBar.h"
#include "GuiToolBarWnd.h"
#include "GuiDocbarExten.h"
#include "TestClass.h"
#include "MenuBar.h"
#include "CoolMenu.h"
#include "GuiSplitterWnd.h"
#include "GuiStatusBar.h"
#include "GuiMiniSplitter.h"
#include "GuiMiniTool.h"
#include "GuiFrameWnd.h"
#include "GuiComboBoxExt.h"
class CMainFrame : public CGuiFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CGuiMiniTool  m_guiMiniToolLeft;
	CGuiMiniTool  m_guiMiniToolRight;
	CGuiMiniSplitter m_MiniSplitter;
	GuiCapOutBar m_CapOutBar;
	CGuiDocBarExten m_dockbar;
	TestClass	m_outbar1;
	CGuiComboBoxExt   m_cb;
	//CSplitterWnd m_wndSplitter;
	CGuiSplitterWnd m_wndSplitter;
	CFont m_cfont;
	void OnBack();
	void OnToday();
	void OnCalendario();
	void OnContacto();
	void OnTareas();
	void OnNotas();
	void OnEliminar();

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCut();
	afx_msg void On2003();
	afx_msg void OnXP();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__98E93E6D_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
