#if !defined(AFX_GUIBUTTONDOC_H__4125FFBD_B199_405D_A917_E40634763AB7__INCLUDED_)
#define AFX_GUIBUTTONDOC_H__4125FFBD_B199_405D_A917_E40634763AB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuiButtonDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGuiButtonDoc window

class CGuiButtonDoc : public CWnd
{
// Construction
public:
	CGuiButtonDoc();

// Attributes
public:
	enum ALING_BTN{LEFT=0,RIGHT,TOP,BOTTOM};
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiButtonDoc)
	public:
	virtual BOOL Create(DWORD dwStyle, CWnd* pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGuiButtonDoc();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGuiButtonDoc)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIBUTTONDOC_H__4125FFBD_B199_405D_A917_E40634763AB7__INCLUDED_)
