// EditListBox.h : main header file for the EDITLISTBOX application
//

#if !defined(AFX_EDITLISTBOX_H__8739157F_DEBE_4751_A425_EE09D0BC9CB6__INCLUDED_)
#define AFX_EDITLISTBOX_H__8739157F_DEBE_4751_A425_EE09D0BC9CB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEditListBoxApp:
// See EditListBox.cpp for the implementation of this class
//

class CEditListBoxApp : public CWinApp
{
public:
	CEditListBoxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditListBoxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEditListBoxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLISTBOX_H__8739157F_DEBE_4751_A425_EE09D0BC9CB6__INCLUDED_)
