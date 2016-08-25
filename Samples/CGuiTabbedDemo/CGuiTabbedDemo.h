// CGuiTabbedDemo.h : main header file for the CGUITABBEDDEMO application
//

#if !defined(AFX_CGUITABBEDDEMO_H__FDB0FF81_AAEB_41EC_850D_A2839CEB60DF__INCLUDED_)
#define AFX_CGUITABBEDDEMO_H__FDB0FF81_AAEB_41EC_850D_A2839CEB60DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoApp:
// See CGuiTabbedDemo.cpp for the implementation of this class
//

class CCGuiTabbedDemoApp : public CWinApp
{
public:
	CCGuiTabbedDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiTabbedDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCGuiTabbedDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUITABBEDDEMO_H__FDB0FF81_AAEB_41EC_850D_A2839CEB60DF__INCLUDED_)
