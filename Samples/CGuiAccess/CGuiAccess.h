// CGuiAccess.h : main header file for the CGUIACCESS application
//

#if !defined(AFX_CGUIACCESS_H__AD89D800_0724_4F94_96B7_C13C6F83919E__INCLUDED_)
#define AFX_CGUIACCESS_H__AD89D800_0724_4F94_96B7_C13C6F83919E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessApp:
// See CGuiAccess.cpp for the implementation of this class
//

class CCGuiAccessApp : public CWinApp
{
public:
	CCGuiAccessApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiAccessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCGuiAccessApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIACCESS_H__AD89D800_0724_4F94_96B7_C13C6F83919E__INCLUDED_)
