// ToolBarsDemoDoc.h : interface of the CToolBarsDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBARSDEMODOC_H__70C21DCC_DFEC_40FF_8BEF_AE8E3E3EE6D7__INCLUDED_)
#define AFX_TOOLBARSDEMODOC_H__70C21DCC_DFEC_40FF_8BEF_AE8E3E3EE6D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CToolBarsDemoDoc : public CDocument
{
protected: // create from serialization only
	CToolBarsDemoDoc();
	DECLARE_DYNCREATE(CToolBarsDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarsDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolBarsDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarsDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARSDEMODOC_H__70C21DCC_DFEC_40FF_8BEF_AE8E3E3EE6D7__INCLUDED_)
