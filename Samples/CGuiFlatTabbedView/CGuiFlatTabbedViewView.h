// CGuiFlatTabbedViewView.h : interface of the CCGuiFlatTabbedViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGUIFLATTABBEDVIEWVIEW_H__4FF0C93B_C41B_4CEA_9CC5_9492F44597F2__INCLUDED_)
#define AFX_CGUIFLATTABBEDVIEWVIEW_H__4FF0C93B_C41B_4CEA_9CC5_9492F44597F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiViewWorkTab.h"


class CListct:public CListCtrl
{
public:
	CListct();

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
	virtual ~CListct();

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputList)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


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


class CCGuiFlatTabbedViewView : public CGuiViewWorkTab
{
protected: // create from serialization only
	CCGuiFlatTabbedViewView();
	DECLARE_DYNCREATE(CCGuiFlatTabbedViewView)
protected:
	COutputList m_wndEdit;
	CListct	m_list;
	COutputList m_wndFind1;
	COutputList m_wndFind2;
	COutputList m_wndResult;
	COutputList m_wndSqlDebug;
// Attributes
public:
	CCGuiFlatTabbedViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiFlatTabbedViewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCGuiFlatTabbedViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGuiFlatTabbedViewView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};

#ifndef _DEBUG  // debug version in CGuiFlatTabbedViewView.cpp
inline CCGuiFlatTabbedViewDoc* CCGuiFlatTabbedViewView::GetDocument()
   { return (CCGuiFlatTabbedViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIFLATTABBEDVIEWVIEW_H__4FF0C93B_C41B_4CEA_9CC5_9492F44597F2__INCLUDED_)
