// SDIDemoView.h : interface of the CSDIDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIDEMOVIEW_H__1C550997_967C_400E_9F56_E913B37C9539__INCLUDED_)
#define AFX_SDIDEMOVIEW_H__1C550997_967C_400E_9F56_E913B37C9539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSDIDemoView : public CView
{
protected: // create from serialization only
	CSDIDemoView();
	DECLARE_DYNCREATE(CSDIDemoView)

// Attributes
public:
	CSDIDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIDemoView)
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
	virtual ~CSDIDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSDIDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SDIDemoView.cpp
inline CSDIDemoDoc* CSDIDemoView::GetDocument()
   { return (CSDIDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIDEMOVIEW_H__1C550997_967C_400E_9F56_E913B37C9539__INCLUDED_)
