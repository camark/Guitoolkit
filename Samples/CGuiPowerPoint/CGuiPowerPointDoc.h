// CGuiPowerPointDoc.h : interface of the CCGuiPowerPointDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGUIPOWERPOINTDOC_H__CEA6D5F5_4D04_4D28_8DC3_EA851FBAB48E__INCLUDED_)
#define AFX_CGUIPOWERPOINTDOC_H__CEA6D5F5_4D04_4D28_8DC3_EA851FBAB48E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGuiPowerPointDoc : public CDocument
{
protected: // create from serialization only
	CCGuiPowerPointDoc();
	DECLARE_DYNCREATE(CCGuiPowerPointDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiPowerPointDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCGuiPowerPointDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGuiPowerPointDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIPOWERPOINTDOC_H__CEA6D5F5_4D04_4D28_8DC3_EA851FBAB48E__INCLUDED_)
