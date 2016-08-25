// CGuiOfficeDemoView.h : interface of the CCGuiOfficeDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGUIOFFICEDEMOVIEW_H__F79FC18F_56FC_4DF3_988D_9D1C5F79F5C0__INCLUDED_)
#define AFX_CGUIOFFICEDEMOVIEW_H__F79FC18F_56FC_4DF3_988D_9D1C5F79F5C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGuiOfficeDemoView : public CView
{
protected: // create from serialization only
	CCGuiOfficeDemoView();
	DECLARE_DYNCREATE(CCGuiOfficeDemoView)

// Attributes
public:
	CCGuiOfficeDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiOfficeDemoView)
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
	virtual ~CCGuiOfficeDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGuiOfficeDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CGuiOfficeDemoView.cpp
inline CCGuiOfficeDemoDoc* CCGuiOfficeDemoView::GetDocument()
   { return (CCGuiOfficeDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIOFFICEDEMOVIEW_H__F79FC18F_56FC_4DF3_988D_9D1C5F79F5C0__INCLUDED_)
