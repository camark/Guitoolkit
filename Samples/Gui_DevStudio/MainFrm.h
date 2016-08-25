// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__DABBB8B8_5430_48CA_BE83_D0748EE98197__INCLUDED_)
#define AFX_MAINFRM_H__DABBB8B8_5430_48CA_BE83_D0748EE98197__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiMDIFrame.h"
#include "GuiSolExplorer.h"
#include "GuiHelp.h"
#include "guioutput.h"
#include "GuiServerExplorer.h"
#include "OutputWindow.h"
#include "GuiComboBoxExt.h"
#include "GuiComboFont.h"
#include "Guiminiframe.h"
#include "DialUndo.h"
class CMainFrame : public CGuiMDIFrame
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
protected:
	CGuiSolExplorer  m_GuiSolEx;
	CGuiHelp		 m_GuiHelp;
	CGuiOutPut		 m_OutPut;	
	CGuiServerExplorer	 m_Server;
	COutputWindow    m_OutNormal;
	CGuiComboFont    m_comboDebug;
	CGuiComboBoxExt  m_comboFind;
	CGuiToolBarWnd   m_ToolCombos;
	CGuiComboBoxExt  m_combo1;
	CGuiComboBoxExt  m_combo2;
	CGuiComboBoxExt  m_combo3;
	CListBox m_tree;
	DialUndo	m_d;
// Operations
//toolbars
public:
	void OnNewItem();
	void OnUndo();
	void OnRedo();
	void NaviBack();
	void Start();
	void FinFiles();
	void Solution();
	void OnExistItem();
    void OnAddClass();
	void OnClassView();
	void OnServer();
void OnHelp();
void OnOutputNormal();
void OnOutput();
void OnWorkSpace();


public:
	void CreateCombos();
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

protected:  // control bar embedded members
	CMenu* cm;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewToolbar();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnViewLook2003();
	afx_msg void OnViewLookXp();
	afx_msg void OnSpoolerStatus(UINT nStatus, UINT nJobs);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWindowCascade();
	afx_msg void OnWindowTileHorz();
	afx_msg void OnDestroy();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__DABBB8B8_5430_48CA_BE83_D0748EE98197__INCLUDED_)
