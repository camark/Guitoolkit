// ToolBarsDemo.h : main header file for the TOOLBARSDEMO application
//

#if !defined(AFX_TOOLBARSDEMO_H__DFACA6B0_5E62_453A_AF88_2DAC4BDEB54A__INCLUDED_)
#define AFX_TOOLBARSDEMO_H__DFACA6B0_5E62_453A_AF88_2DAC4BDEB54A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoApp:
// See ToolBarsDemo.cpp for the implementation of this class
//

class CToolBarsDemoApp : public CWinApp
{
public:
	CToolBarsDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarsDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CToolBarsDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARSDEMO_H__DFACA6B0_5E62_453A_AF88_2DAC4BDEB54A__INCLUDED_)
