// OutputWindow.h: interface for the COutputWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTWINDOW_H__35C1CE94_D79B_11D4_B90C_000000000000__INCLUDED_)
#define AFX_OUTPUTWINDOW_H__35C1CE94_D79B_11D4_B90C_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiControlBar.h"
#include "GuiWorktab.h"

class COutputList : public CListBox
{
// Construction
public:
	COutputList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputList();

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputList)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class COutputWindow : public CGuiControlBar  
{
public:
	COutputWindow();
	virtual ~COutputWindow();
	CGuiWorkTab	m_wndWorkTab;
		COutputList m_wndEdit;
	COutputList m_wndDebug;
	COutputList m_wndFind1;
	COutputList m_wndFind2;
	COutputList m_wndResult;
	COutputList m_wndSqlDebug;
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		m_wndWorkTab.StyleDispl(dwDsp);
		CGuiControlBar::StyleDispl(dwDsp);
	}
protected:
	//{{AFX_MSG(CMyBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_OUTPUTWINDOW_H__35C1CE94_D79B_11D4_B90C_000000000000__INCLUDED_)
