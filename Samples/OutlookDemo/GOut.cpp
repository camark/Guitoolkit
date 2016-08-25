// GOut.cpp: implementation of the CGOut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OutlookDemo.h"
#include "GOut.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define IDO_OUTODAY	   5600
#define IDO_CALENDARIO 5601
#define IDO_CONTACTO   5602

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CGOut,CGuiOutLookView)

CGOut::CGOut()
{

}

CGOut::~CGOut()
{

}

BEGIN_MESSAGE_MAP(CGOut, CGuiOutLookView)
	//{{AFX_MSG_MAP(CGuiOutLookView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




int CGOut::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CGuiOutLookView::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!out.Create(WS_VISIBLE,
		CRect(0,0,0,0), &cf, 1))
		return -1;

#define IDO_OUTODAY	   5600
#define IDO_CALENDARIO 5601
#define IDO_CONTACTO   5602
#define IDO_TAREAS     5603
#define IDO_NOTAS	   5604	
#define IDO_ELIMINAR   5605

	out.SetImageList(IDB_BITMAP1, 32, 0, RGB(255,0,0));
	out.AddItem(IDO_OUTODAY,"OutLook para hoy",7);
	out.AddItem(IDO_CALENDARIO,"Calendario",1);
	out.AddItem(IDO_CONTACTO,"Contactos",2);
	out.AddItem(IDO_TAREAS,"tareas",3);
	out.AddItem(IDO_NOTAS,"Notas",5);
	out.AddItem(IDO_ELIMINAR,"Elementos Eliminados",6);
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
	out.StyleDispl(GUISTYLE_2003);
//	out.SetXp(TRUE);
	cf.AddFolder(&out,"General");
	cf.AddFolder(&tc,"Folders");

	return 0;
}


