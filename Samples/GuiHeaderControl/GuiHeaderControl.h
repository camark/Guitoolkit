// GuiHeaderControl.h : main header file for the GUIHEADERCONTROL application
//

#if !defined(AFX_GUIHEADERCONTROL_H__CF16383E_BBE7_45C6_AE66_E6E282FCF162__INCLUDED_)
#define AFX_GUIHEADERCONTROL_H__CF16383E_BBE7_45C6_AE66_E6E282FCF162__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGuiHeaderControlApp:
// See GuiHeaderControl.cpp for the implementation of this class
//

class CGuiHeaderControlApp : public CWinApp
{
public:
	CGuiHeaderControlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiHeaderControlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGuiHeaderControlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIHEADERCONTROL_H__CF16383E_BBE7_45C6_AE66_E6E282FCF162__INCLUDED_)
