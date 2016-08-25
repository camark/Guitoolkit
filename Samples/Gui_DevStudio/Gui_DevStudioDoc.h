// Gui_DevStudioDoc.h : interface of the CGui_DevStudioDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUI_DEVSTUDIODOC_H__DC784789_830D_4B08_AF11_831AB9A57B70__INCLUDED_)
#define AFX_GUI_DEVSTUDIODOC_H__DC784789_830D_4B08_AF11_831AB9A57B70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGui_DevStudioDoc : public CDocument
{
protected: // create from serialization only
	CGui_DevStudioDoc();
	DECLARE_DYNCREATE(CGui_DevStudioDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGui_DevStudioDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGui_DevStudioDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGui_DevStudioDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_DEVSTUDIODOC_H__DC784789_830D_4B08_AF11_831AB9A57B70__INCLUDED_)
