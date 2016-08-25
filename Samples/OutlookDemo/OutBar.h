// OutBar.h: interface for the COutBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTBAR_H__98E93E79_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
#define AFX_OUTBAR_H__98E93E79_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "GuiToolLook.h"
#include "GuiFolder.h"
#include "GuiOutLook.h"
class COutBar : public GuiToolLook    
{
public:
	COutBar();
	virtual ~COutBar();
public:
	CGuiFolder cf;
	CGuiOutLook out;
	CTreeCtrl tc;
protected:
	//{{AFX_MSG(CMyBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_OUTBAR_H__98E93E79_A5FA_11D5_A8C6_0008C7B2934C__INCLUDED_)
