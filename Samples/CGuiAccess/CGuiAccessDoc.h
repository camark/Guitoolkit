// CGuiAccessDoc.h : interface of the CCGuiAccessDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGUIACCESSDOC_H__5CC4B231_3729_40BA_8B5C_86E69BC311F2__INCLUDED_)
#define AFX_CGUIACCESSDOC_H__5CC4B231_3729_40BA_8B5C_86E69BC311F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGuiAccessDoc : public CDocument
{
protected: // create from serialization only
	CCGuiAccessDoc();
	DECLARE_DYNCREATE(CCGuiAccessDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiAccessDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCGuiAccessDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGuiAccessDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIACCESSDOC_H__5CC4B231_3729_40BA_8B5C_86E69BC311F2__INCLUDED_)
