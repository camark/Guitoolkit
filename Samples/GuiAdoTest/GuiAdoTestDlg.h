// GuiAdoTestDlg.h : header file
//

#if !defined(AFX_GUIADOTESTDLG_H__16675909_D29A_4FAA_B803_976E0ABCE914__INCLUDED_)
#define AFX_GUIADOTESTDLG_H__16675909_D29A_4FAA_B803_976E0ABCE914__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGuiAdoTestDlg dialog

class CGuiAdoTestDlg : public CDialog
{
// Construction
public:
	CGuiAdoTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGuiAdoTestDlg)
	enum { IDD = IDD_GUIADOTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiAdoTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGuiAdoTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIADOTESTDLG_H__16675909_D29A_4FAA_B803_976E0ABCE914__INCLUDED_)
