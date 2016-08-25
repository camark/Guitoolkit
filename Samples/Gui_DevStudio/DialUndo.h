#if !defined(AFX_DIALUNDO_H__D3868C08_C359_4C55_B339_5F5122E22F24__INCLUDED_)
#define AFX_DIALUNDO_H__D3868C08_C359_4C55_B339_5F5122E22F24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialUndo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DialUndo dialog

class DialUndo : public CDialog
{
// Construction
public:
	DialUndo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DialUndo)
	enum { IDD = IDD_DIAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DialUndo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DialUndo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALUNDO_H__D3868C08_C359_4C55_B339_5F5122E22F24__INCLUDED_)
