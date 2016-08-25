#if !defined(AFX_CAJON_H__38FBEF50_E3B4_4A1E_854B_F0FB1C04959B__INCLUDED_)
#define AFX_CAJON_H__38FBEF50_E3B4_4A1E_854B_F0FB1C04959B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Cajon.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCajon view
#include <afxcview.h>
class CCajon : public CListView
{
protected:
	CCajon();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCajon)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCajon)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCajon();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCajon)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAJON_H__38FBEF50_E3B4_4A1E_854B_F0FB1C04959B__INCLUDED_)
