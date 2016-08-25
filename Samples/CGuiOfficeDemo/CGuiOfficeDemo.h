// CGuiOfficeDemo.h : main header file for the CGUIOFFICEDEMO application
//

#if !defined(AFX_CGUIOFFICEDEMO_H__7B5616C1_A12B_4D34_8822_12CEC915F007__INCLUDED_)
#define AFX_CGUIOFFICEDEMO_H__7B5616C1_A12B_4D34_8822_12CEC915F007__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoApp:
// See CGuiOfficeDemo.cpp for the implementation of this class
//

class CCGuiOfficeDemoApp : public CWinApp
{
public:
	CCGuiOfficeDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiOfficeDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCGuiOfficeDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIOFFICEDEMO_H__7B5616C1_A12B_4D34_8822_12CEC915F007__INCLUDED_)
