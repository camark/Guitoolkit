/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *							 (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software;so you are free to use it any of your		*
 * applications (Freeware, Shareware, Commercial),but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/



#if !defined(AFX_GUISTATICSTANDAR_H__E577069E_DA47_4E1D_9271_B7EA22634BCE__INCLUDED_)
#define AFX_GUISTATICSTANDAR_H__E577069E_DA47_4E1D_9271_B7EA22634BCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiStaticStandar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiStaticStandar window

class GUILIBDLLEXPORT CGuiStaticStandar : public CStatic
{
// Construction
public:
	CGuiStaticStandar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiStaticStandar)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGuiStaticStandar();
	void AddChild(CWnd* pWnd);
	void RecalLayout();
	// Generated message map functions
protected:
	CWnd* m_pWnd;
	//{{AFX_MSG(CGuiStaticStandar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUISTATICSTANDAR_H__E577069E_DA47_4E1D_9271_B7EA22634BCE__INCLUDED_)
