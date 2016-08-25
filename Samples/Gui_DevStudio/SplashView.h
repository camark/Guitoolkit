#if !defined(AFX_SPLASHVIEW_H__15D3A2E9_99F6_4319_9A28_18D6D5654B62__INCLUDED_)
#define AFX_SPLASHVIEW_H__15D3A2E9_99F6_4319_9A28_18D6D5654B62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SplashView view

class SplashView : public CView
{
protected:
	SplashView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(SplashView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SplashView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~SplashView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(SplashView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHVIEW_H__15D3A2E9_99F6_4319_9A28_18D6D5654B62__INCLUDED_)
