// EditListBoxDlg.h : header file
//

#if !defined(AFX_EDITLISTBOXDLG_H__1EB69633_FBE8_4F27_9839_4055DA656FF2__INCLUDED_)
#define AFX_EDITLISTBOXDLG_H__1EB69633_FBE8_4F27_9839_4055DA656FF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiListEdit.h"
#include "GuiDropDownEdit.h"
	
/////////////////////////////////////////////////////////////////////////////
// CEditListBoxDlg dialog

class CEditListBoxDlg : public CDialog
{
// Construction
public:
	CEditListBoxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEditListBoxDlg)
	enum { IDD = IDD_EDITLISTBOX_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditListBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	CGuiListEdit ListBox;
	CGuiDropDownEdit m_edit;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEditListBoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLISTBOXDLG_H__1EB69633_FBE8_4F27_9839_4055DA656FF2__INCLUDED_)
