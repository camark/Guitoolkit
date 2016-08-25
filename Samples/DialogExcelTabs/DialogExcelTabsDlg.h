// DialogExcelTabsDlg.h : header file
//

#if !defined(AFX_DIALOGEXCELTABSDLG_H__878C0B20_AA0D_4355_9E4F_68B2F511777E__INCLUDED_)
#define AFX_DIALOGEXCELTABSDLG_H__878C0B20_AA0D_4355_9E4F_68B2F511777E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogExcelTabsDlg dialog

class COutputList : public CListBox
{
// Construction
public:
	COutputList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputList();

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputList)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#include "GuiStaticStandar.h"
#include "GuiWorkTab.h"

class CDialogExcelTabsDlg : public CDialog
{
// Construction
public:
	CDialogExcelTabsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogExcelTabsDlg)
	enum { IDD = IDD_DIALOGEXCELTABS_DIALOG };
	CGuiStaticStandar	m_excel;
	CGuiWorkTab	m_wndWorkTab;
	COutputList m_wndEdit;
	COutputList m_wndDebug;
	COutputList m_wndFind1;
	COutputList m_wndFind2;
	COutputList m_wndResult;
	COutputList m_wndSqlDebug;

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogExcelTabsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDialogExcelTabsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGEXCELTABSDLG_H__878C0B20_AA0D_4355_9E4F_68B2F511777E__INCLUDED_)
