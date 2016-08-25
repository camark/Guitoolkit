#if !defined(AFX_DIALSPLITTER_H__E8378C75_2698_45E6_A845_9E4DAE27D321__INCLUDED_)
#define AFX_DIALSPLITTER_H__E8378C75_2698_45E6_A845_9E4DAE27D321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialSplitter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialSplitter dialog
#include "GuiSplitter.h"
class CDialSplitter : public CDialog
{
// Construction
public:
	CDialSplitter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialSplitter)
	enum { IDD = IDD_SPLITTERS };
	CGuiSplitter	m_Splitter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialSplitter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
		CTreeCtrl  m_TreeServerExplorer;
	CTreeCtrl  m_TreeServerExplorer1;
	// Generated message map functions
	//{{AFX_MSG(CDialSplitter)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALSPLITTER_H__E8378C75_2698_45E6_A845_9E4DAE27D321__INCLUDED_)
