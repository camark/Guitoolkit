// DialogExcelTabs.h : main header file for the DIALOGEXCELTABS application
//

#if !defined(AFX_DIALOGEXCELTABS_H__B5000D2B_F475_41BB_B960_478C07FB408E__INCLUDED_)
#define AFX_DIALOGEXCELTABS_H__B5000D2B_F475_41BB_B960_478C07FB408E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDialogExcelTabsApp:
// See DialogExcelTabs.cpp for the implementation of this class
//

class CDialogExcelTabsApp : public CWinApp
{
public:
	CDialogExcelTabsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogExcelTabsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDialogExcelTabsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGEXCELTABS_H__B5000D2B_F475_41BB_B960_478C07FB408E__INCLUDED_)
