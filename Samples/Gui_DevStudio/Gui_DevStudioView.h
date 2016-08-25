// Gui_DevStudioView.h : interface of the CGui_DevStudioView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUI_DEVSTUDIOVIEW_H__551AA264_1A61_43F4_994C_7E3395AD3AB5__INCLUDED_)
#define AFX_GUI_DEVSTUDIOVIEW_H__551AA264_1A61_43F4_994C_7E3395AD3AB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGui_DevStudioView : public CEditView
{
protected: // create from serialization only
	CGui_DevStudioView();
	DECLARE_DYNCREATE(CGui_DevStudioView)

// Attributes
public:
	CGui_DevStudioDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGui_DevStudioView)
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
	virtual ~CGui_DevStudioView();
/*#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
*/
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGui_DevStudioView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Gui_DevStudioView.cpp
inline CGui_DevStudioDoc* CGui_DevStudioView::GetDocument()
   { return (CGui_DevStudioDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_DEVSTUDIOVIEW_H__551AA264_1A61_43F4_994C_7E3395AD3AB5__INCLUDED_)
