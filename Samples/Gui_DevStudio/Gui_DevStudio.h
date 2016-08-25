// Gui_DevStudio.h : main header file for the GUI_DEVSTUDIO application
//

#if !defined(AFX_GUI_DEVSTUDIO_H__22A0E37F_B958_4599_B0FC_5A4CB8EDD131__INCLUDED_)
#define AFX_GUI_DEVSTUDIO_H__22A0E37F_B958_4599_B0FC_5A4CB8EDD131__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioApp:
// See Gui_DevStudio.cpp for the implementation of this class
//

class CGui_DevStudioApp : public CWinApp
{

protected:

	BOOL bFirstStart;
public:
	CGui_DevStudioApp();
	CMultiDocTemplate* m_pDocTemplateSplash;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGui_DevStudioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGui_DevStudioApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_DEVSTUDIO_H__22A0E37F_B958_4599_B0FC_5A4CB8EDD131__INCLUDED_)
