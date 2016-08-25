// HeaderControl.h : main header file for the HEADERCONTROL application
//

#if !defined(AFX_HEADERCONTROL_H__026C91C3_B4B2_4B12_BBD9_94CAF8F1611D__INCLUDED_)
#define AFX_HEADERCONTROL_H__026C91C3_B4B2_4B12_BBD9_94CAF8F1611D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHeaderControlApp:
// See HeaderControl.cpp for the implementation of this class
//

class CHeaderControlApp : public CWinApp
{
public:
	CHeaderControlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderControlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHeaderControlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADERCONTROL_H__026C91C3_B4B2_4B12_BBD9_94CAF8F1611D__INCLUDED_)
