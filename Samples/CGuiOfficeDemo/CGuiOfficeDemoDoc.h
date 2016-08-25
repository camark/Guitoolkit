// CGuiOfficeDemoDoc.h : interface of the CCGuiOfficeDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGUIOFFICEDEMODOC_H__3ADC6CCC_CFA5_40C2_BDDF_A5183B498069__INCLUDED_)
#define AFX_CGUIOFFICEDEMODOC_H__3ADC6CCC_CFA5_40C2_BDDF_A5183B498069__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGuiOfficeDemoDoc : public CDocument
{
protected: // create from serialization only
	CCGuiOfficeDemoDoc();
	DECLARE_DYNCREATE(CCGuiOfficeDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGuiOfficeDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCGuiOfficeDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGuiOfficeDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGUIOFFICEDEMODOC_H__3ADC6CCC_CFA5_40C2_BDDF_A5183B498069__INCLUDED_)
