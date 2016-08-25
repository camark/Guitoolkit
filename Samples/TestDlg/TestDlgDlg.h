// TestDlgDlg.h : header file
//

#if !defined(AFX_TESTDLGDLG_H__2BFE986B_A526_11D5_B915_000000000000__INCLUDED_)
#define AFX_TESTDLGDLG_H__2BFE986B_A526_11D5_B915_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiCheckBox.h"
#include "GuiComboBoxExt.h"
#include "GuiLinkButton.h"
#include "GuiButton.h"
#include "GuiSliderCtrl.h"
#include "GuiMiniTool.h"
#include "GuiEdit.h"
#include "GuiGroupBox.h"
#include "GuiRadioButton.h"
#include "GuiComboFont.h"
/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg dialog

class CTestDlgDlg : public CDialog
{
// Construction
public:
	CTestDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlgDlg)
	enum { IDD = IDD_TESTDLG_DIALOG };
	CGuiLinkButton	m_Link;
	CGuiGroupBox	m_gbox;
	CGuiMiniTool	m_mini;
	CGuiSliderCtrl	m_shor;
	CGuiSliderCtrl	m_sli;
	CGuiButton	m_cancel;
	CGuiButton	m_Okbtn;
	CGuiButton	m_btnArrow;
	CGuiLinkButton	m_email;
	CGuiComboBoxExt	m_Combobox;
	CGuiCheckBox	m_btnCheck2;
	CGuiCheckBox	m_btnCheck1;
	CGuiEdit		m_guiedit;
	CImageList		m_imag;
	CGuiRadioButton m_rd1;
	CGuiRadioButton m_rd2;
	CMenu menu;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheck1();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnOption1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLGDLG_H__2BFE986B_A526_11D5_B915_000000000000__INCLUDED_)
