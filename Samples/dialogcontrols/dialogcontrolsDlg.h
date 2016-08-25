// dialogcontrolsDlg.h : header file
//

#if !defined(AFX_DIALOGCONTROLSDLG_H__B07B822C_4CBF_4E25_A68D_635760C57139__INCLUDED_)
#define AFX_DIALOGCONTROLSDLG_H__B07B822C_4CBF_4E25_A68D_635760C57139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogcontrolsDlg dialog
#include "GuiFolder.h"
#include "GuiOutLook.h"
#include "GuiStaticStandar.h"
#include "GuiSplitter.h"
#include "GuiMiniTool.h"
#include "GuiMiniSplitter.h"
#include "GuiCapOutBar.h"
#include "GuiComboBoxExt.h"
class CDialogcontrolsDlg : public CDialog
{
// Construction
public:
	CDialogcontrolsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogcontrolsDlg)
	enum { IDD = IDD_DIALOGCONTROLS_DIALOG };
//	CStatic	m_outllok;
	CGuiStaticStandar	m_minitools;
	//}}AFX_DATA
	CGuiSplitter    m_Splitter;
	CGuiStaticStandar	m_outllok;
	CGuiFolder			cf;
	CTreeCtrl tc;
	CTreeCtrl tc1;
	CGuiOutLook out;
	//------------------------------------
	//caption bar
	CGuiMiniTool  m_guiMiniToolLeft;
	CGuiMiniTool  m_guiMiniToolRight;
	CGuiMiniSplitter m_MiniSplitter;
	GuiCapOutBar m_CapOutBar;
	CGuiComboBoxExt   m_cb;
	//------------------------------------
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogcontrolsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDialogcontrolsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGCONTROLSDLG_H__B07B822C_4CBF_4E25_A68D_635760C57139__INCLUDED_)
