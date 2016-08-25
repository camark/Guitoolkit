#if !defined(AFX_GUIDOCKBAR_H__7B496F64_7230_419E_9A90_4D1BAC105E95__INCLUDED_)
#define AFX_GUIDOCKBAR_H__7B496F64_7230_419E_9A90_4D1BAC105E95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiDockBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiDockBar window

class CGuiDockBar : public CDockBar
{
	// Construction
public:
	CGuiDockBar();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiDockBar)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CGuiDockBar();
	virtual CSize ReCalLayout(CGuiControlBar* pWnd);
	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiDockBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIDOCKBAR_H__7B496F64_7230_419E_9A90_4D1BAC105E95__INCLUDED_)
