// CGuiTabbedDemoDoc.h : interface of the CCGuiTabbedDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGUITABBEDDEMODOC_H__FE7BA1F4_B5A2_4F1F_86C0_B4272806B70F__INCLUDED_)
#define AFX_CGUITABBEDDEMODOC_H__FE7BA1F4_B5A2_4F1F_86C0_B4272806B70F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGuiTabbedDemoDoc : public CDocument
{
protected: // create from serialization only
	CCGuiTabbedDemoDoc();
	DECLARE_DYNCREATE(CCGuiTabbedDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiTabbedDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCGuiTabbedDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGuiTabbedDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUITABBEDDEMODOC_H__FE7BA1F4_B5A2_4F1F_86C0_B4272806B70F__INCLUDED_)
