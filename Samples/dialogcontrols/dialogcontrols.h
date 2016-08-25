// dialogcontrols.h : main header file for the DIALOGCONTROLS application
//

#if !defined(AFX_DIALOGCONTROLS_H__774DF946_DD1A_4A4F_811D_21045B66254E__INCLUDED_)
#define AFX_DIALOGCONTROLS_H__774DF946_DD1A_4A4F_811D_21045B66254E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDialogcontrolsApp:
// See dialogcontrols.cpp for the implementation of this class
//

class CDialogcontrolsApp : public CWinApp
{
public:
	CDialogcontrolsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogcontrolsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDialogcontrolsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGCONTROLS_H__774DF946_DD1A_4A4F_811D_21045B66254E__INCLUDED_)
