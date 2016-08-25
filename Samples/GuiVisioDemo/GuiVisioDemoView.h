// GuiVisioDemoView.h : interface of the CGuiVisioDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUIVISIODEMOVIEW_H__09AE1B8B_40AC_402D_8C67_AC83EC210A1F__INCLUDED_)
#define AFX_GUIVISIODEMOVIEW_H__09AE1B8B_40AC_402D_8C67_AC83EC210A1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGuiVisioDemoView : public CView
{
protected: // create from serialization only
	CGuiVisioDemoView();
	DECLARE_DYNCREATE(CGuiVisioDemoView)

// Attributes
public:
	CGuiVisioDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiVisioDemoView)
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
	virtual ~CGuiVisioDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGuiVisioDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GuiVisioDemoView.cpp
inline CGuiVisioDemoDoc* CGuiVisioDemoView::GetDocument()
   { return (CGuiVisioDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIVISIODEMOVIEW_H__09AE1B8B_40AC_402D_8C67_AC83EC210A1F__INCLUDED_)
