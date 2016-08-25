// OutBar.cpp: implementation of the COutBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OutlookDemo.h"
#include "OutBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(COutBar, GuiToolLook)
	//{{AFX_MSG_MAP(COutBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

COutBar::COutBar()
{

}

COutBar::~COutBar()
{

}

COutBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (GuiToolLook::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	
	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

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
	if (!tc.Create(WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS,
		CRect(0,0,0,0), &cf, 2))
		return -1;
	HTREEITEM hRoot = tc.InsertItem (_T("Opcion uno"), 0, 0);
	tc.SetItemState (hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hClass = tc.InsertItem (_T("Opcion dos"), 1, 1, hRoot);
	tc.InsertItem (_T("SubOpcion dos"), 3, 3, hClass);
	tc.InsertItem (_T("SubOpcion tres"), 4, 4, hClass);

	tc.Expand (hRoot, TVE_EXPAND);

	out.SetXp(TRUE);
	cf.AddFolder(&out,"Folder Uno");
	cf.AddFolder(&tc,"Folder Dos");
	return 0;
}





