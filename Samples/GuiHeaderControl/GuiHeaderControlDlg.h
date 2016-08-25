// GuiHeaderControlDlg.h : header file
//

#if !defined(AFX_GUIHEADERCONTROLDLG_H__97BC9F7A_16EA_44AD_B505_4B92D7F731C6__INCLUDED_)
#define AFX_GUIHEADERCONTROLDLG_H__97BC9F7A_16EA_44AD_B505_4B92D7F731C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGuiHeaderControlDlg dialog
#include "GuiHeaderCtrl.h"
class CGuiHeaderControlDlg : public CDialog
{
// Construction
public:
	CGuiHeaderControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGuiHeaderControlDlg)
	enum { IDD = IDD_GUIHEADERCONTROL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiHeaderControlDlg)
	protected:
	CGuiHeaderCtrl m_h;
	CImageList m_cImageList;
	CListCtrl	m_list;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGuiHeaderControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIHEADERCONTROLDLG_H__97BC9F7A_16EA_44AD_B505_4B92D7F731C6__INCLUDED_)
