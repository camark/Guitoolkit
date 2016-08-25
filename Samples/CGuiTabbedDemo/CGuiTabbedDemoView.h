// CGuiTabbedDemoView.h : interface of the CCGuiTabbedDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGUITABBEDDEMOVIEW_H__83300727_68FC_4801_81F7_BB1C1B8716C5__INCLUDED_)
#define AFX_CGUITABBEDDEMOVIEW_H__83300727_68FC_4801_81F7_BB1C1B8716C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGuiTabbedDemoView : public CView
{
protected: // create from serialization only
	CCGuiTabbedDemoView();
	DECLARE_DYNCREATE(CCGuiTabbedDemoView)

// Attributes
public:
	CCGuiTabbedDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiTabbedDemoView)
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
	virtual ~CCGuiTabbedDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGuiTabbedDemoView)
	afx_msg void OnFilePrintPreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CGuiTabbedDemoView.cpp
inline CCGuiTabbedDemoDoc* CCGuiTabbedDemoView::GetDocument()
   { return (CCGuiTabbedDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUITABBEDDEMOVIEW_H__83300727_68FC_4801_81F7_BB1C1B8716C5__INCLUDED_)
