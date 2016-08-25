// GuiVisioDemoDoc.h : interface of the CGuiVisioDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUIVISIODEMODOC_H__E2383086_C2A3_4CA4_ACE4_44C37E821D47__INCLUDED_)
#define AFX_GUIVISIODEMODOC_H__E2383086_C2A3_4CA4_ACE4_44C37E821D47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGuiVisioDemoDoc : public CDocument
{
protected: // create from serialization only
	CGuiVisioDemoDoc();
	DECLARE_DYNCREATE(CGuiVisioDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiVisioDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGuiVisioDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGuiVisioDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIVISIODEMODOC_H__E2383086_C2A3_4CA4_ACE4_44C37E821D47__INCLUDED_)
