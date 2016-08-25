// OutlookDemoDoc.h : interface of the COutlookDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTLOOKDEMODOC_H__98E93E6F_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
#define AFX_OUTLOOKDEMODOC_H__98E93E6F_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COutlookDemoDoc : public CDocument
{
protected: // create from serialization only
	COutlookDemoDoc();
	DECLARE_DYNCREATE(COutlookDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutlookDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutlookDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKDEMODOC_H__98E93E6F_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
