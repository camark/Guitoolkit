// SDIDemo.h : main header file for the SDIDEMO application
//

#if !defined(AFX_SDIDEMO_H__4C42A513_7EBD_4C1C_BB62_2222118AE284__INCLUDED_)
#define AFX_SDIDEMO_H__4C42A513_7EBD_4C1C_BB62_2222118AE284__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSDIDemoApp:
// See SDIDemo.cpp for the implementation of this class
//

class CSDIDemoApp : public CWinApp
{
public:
	CSDIDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSDIDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIDEMO_H__4C42A513_7EBD_4C1C_BB62_2222118AE284__INCLUDED_)
