// CGuiFlatTabbedViewDoc.h : interface of the CCGuiFlatTabbedViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGUIFLATTABBEDVIEWDOC_H__9866DEE6_2598_48EB_94B1_EB228077D678__INCLUDED_)
#define AFX_CGUIFLATTABBEDVIEWDOC_H__9866DEE6_2598_48EB_94B1_EB228077D678__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGuiFlatTabbedViewDoc : public CDocument
{
protected: // create from serialization only
	CCGuiFlatTabbedViewDoc();
	DECLARE_DYNCREATE(CCGuiFlatTabbedViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiFlatTabbedViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCGuiFlatTabbedViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGuiFlatTabbedViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIFLATTABBEDVIEWDOC_H__9866DEE6_2598_48EB_94B1_EB228077D678__INCLUDED_)
