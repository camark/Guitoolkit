// OutlookDemoView.h : interface of the COutlookDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTLOOKDEMOVIEW_H__98E93E71_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
#define AFX_OUTLOOKDEMOVIEW_H__98E93E71_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COutlookDemoView : public CView
{
protected: // create from serialization only
	COutlookDemoView();
	DECLARE_DYNCREATE(COutlookDemoView)

// Attributes
public:
	COutlookDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookDemoView)
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
	virtual ~COutlookDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutlookDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OutlookDemoView.cpp
inline COutlookDemoDoc* COutlookDemoView::GetDocument()
   { return (COutlookDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKDEMOVIEW_H__98E93E71_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
