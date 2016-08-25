// TestClass.h: interface for the TestClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCLASS_H__3CAEF7F6_A781_11D5_A8C7_0008C7B2934C__INCLUDED_)
#define AFX_TESTCLASS_H__3CAEF7F6_A781_11D5_A8C7_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiToolBar.h"
#include "GuiFolder.h"
#include "GuiOutLook.h"
class TestClass : public GuiToolBar  
{
public:
	TestClass();
	virtual ~TestClass();
public:
	CGuiFolder cf;
	CGuiOutLook out;

protected:
	//{{AFX_MSG(CMyBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_TESTCLASS_H__3CAEF7F6_A781_11D5_A8C7_0008C7B2934C__INCLUDED_)
