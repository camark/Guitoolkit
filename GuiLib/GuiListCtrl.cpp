// GuiListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "GuiLib.h"
#include "GuiListCtrl.h"


// CGuiListCtrl

IMPLEMENT_DYNAMIC(CGuiListCtrl, CListCtrl)
CGuiListCtrl::CGuiListCtrl()
{
}

CGuiListCtrl::~CGuiListCtrl()
{
}


BEGIN_MESSAGE_MAP(CGuiListCtrl, CListCtrl)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// CGuiListCtrl message handlers


void CGuiListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	CListCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
