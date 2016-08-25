// CGuiPowerPoint.h : main header file for the CGUIPOWERPOINT application
//

#if !defined(AFX_CGUIPOWERPOINT_H__BD387FC3_E857_40DE_A613_0B18F2A8716E__INCLUDED_)
#define AFX_CGUIPOWERPOINT_H__BD387FC3_E857_40DE_A613_0B18F2A8716E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointApp:
// See CGuiPowerPoint.cpp for the implementation of this class
//

class CCGuiPowerPointApp : public CWinApp
{
public:
	CCGuiPowerPointApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiPowerPointApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCGuiPowerPointApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIPOWERPOINT_H__BD387FC3_E857_40DE_A613_0B18F2A8716E__INCLUDED_)
