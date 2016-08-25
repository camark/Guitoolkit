// TestClass.cpp: implementation of the TestClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OutlookDemo.h"
#include "TestClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestClass::TestClass()
{

}

TestClass::~TestClass()
{

}


BEGIN_MESSAGE_MAP(TestClass, GuiToolBar)
	//{{AFX_MSG_MAP(TestClass)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



TestClass::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (GuiToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	
	//SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	if (!cf.Create(WS_VISIBLE|WS_CHILD,
			CRect(0,0,0,0), this, 6))
		return -1;
	if (!out.Create(WS_VISIBLE,
		CRect(0,0,0,0), &cf, 1))
		return -1;
	out.SetImageList(IDB_BITMAP1, 32, 0, RGB(128,128,128));
	out.AddItem(1,"Primero",0);
	out.AddItem(2,"Segundo",1);
	out.AddItem(3,"Tercero",2);
	out.AddItem(4,"Cuarto",3);
	out.AddItem(5,"Cinco",4);
	out.AddItem(6,"Seis",5);
	out.StyleDispl(GUISTYLE_2003);
	cf.AddFolder(&out,"Folder Uno");
	return 0;
}
