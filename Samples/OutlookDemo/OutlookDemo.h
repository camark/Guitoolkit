// OutlookDemo.h : main header file for the OUTLOOKDEMO application
//

#if !defined(AFX_OUTLOOKDEMO_H__98E93E69_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
#define AFX_OUTLOOKDEMO_H__98E93E69_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COutlookDemoApp:
// See OutlookDemo.cpp for the implementation of this class
//

class COutlookDemoApp : public CWinApp
{
public:
	COutlookDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COutlookDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKDEMO_H__98E93E69_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
