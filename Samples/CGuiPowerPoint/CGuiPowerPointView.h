// CGuiPowerPointView.h : interface of the CCGuiPowerPointView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGUIPOWERPOINTVIEW_H__E3F452DC_D48B_4D26_9323_B5BED176564D__INCLUDED_)
#define AFX_CGUIPOWERPOINTVIEW_H__E3F452DC_D48B_4D26_9323_B5BED176564D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGuiPowerPointView : public CView
{
protected: // create from serialization only
	CCGuiPowerPointView();
	DECLARE_DYNCREATE(CCGuiPowerPointView)

// Attributes
public:
	CCGuiPowerPointDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiPowerPointView)
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
	virtual ~CCGuiPowerPointView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGuiPowerPointView)
	afx_msg void OnFilePrintPreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CGuiPowerPointView.cpp
inline CCGuiPowerPointDoc* CCGuiPowerPointView::GetDocument()
   { return (CCGuiPowerPointDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIPOWERPOINTVIEW_H__E3F452DC_D48B_4D26_9323_B5BED176564D__INCLUDED_)
