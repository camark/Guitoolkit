// HeaderControlDlg.h : header file
//

#if !defined(AFX_HEADERCONTROLDLG_H__E5A5B9D0_6597_43E1_A16D_D8391D71CE25__INCLUDED_)
#define AFX_HEADERCONTROLDLG_H__E5A5B9D0_6597_43E1_A16D_D8391D71CE25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHeaderControlDlg dialog

class CHeaderControlDlg : public CDialog
{
// Construction
public:
	CHeaderControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHeaderControlDlg)
	enum { IDD = IDD_HEADERCONTROL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHeaderControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADERCONTROLDLG_H__E5A5B9D0_6597_43E1_A16D_D8391D71CE25__INCLUDED_)
