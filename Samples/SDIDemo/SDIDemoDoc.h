// SDIDemoDoc.h : interface of the CSDIDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIDEMODOC_H__2FEAD84F_3618_4CB6_9EDC_EBF6C8F261E8__INCLUDED_)
#define AFX_SDIDEMODOC_H__2FEAD84F_3618_4CB6_9EDC_EBF6C8F261E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSDIDemoDoc : public CDocument
{
protected: // create from serialization only
	CSDIDemoDoc();
	DECLARE_DYNCREATE(CSDIDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSDIDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSDIDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIDEMODOC_H__2FEAD84F_3618_4CB6_9EDC_EBF6C8F261E8__INCLUDED_)
