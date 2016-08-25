// ToolBarsDemoView.h : interface of the CToolBarsDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBARSDEMOVIEW_H__DF4248BD_863B_4841_A462_91AC2921CE8F__INCLUDED_)
#define AFX_TOOLBARSDEMOVIEW_H__DF4248BD_863B_4841_A462_91AC2921CE8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CToolBarsDemoView : public CEditView
{
protected: // create from serialization only
	CToolBarsDemoView();
	DECLARE_DYNCREATE(CToolBarsDemoView)

// Attributes
public:
	CToolBarsDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarsDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	
public:
	void Message();
	virtual ~CToolBarsDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarsDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ToolBarsDemoView.cpp
inline CToolBarsDemoDoc* CToolBarsDemoView::GetDocument()
   { return (CToolBarsDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARSDEMOVIEW_H__DF4248BD_863B_4841_A462_91AC2921CE8F__INCLUDED_)
