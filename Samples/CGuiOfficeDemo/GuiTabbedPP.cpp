#include "stdafx.h"
#include "guitabbedpp.h"
#include "resource.h"
CGuiTabbedPP::CGuiTabbedPP(void)
{
}

CGuiTabbedPP::~CGuiTabbedPP(void)
{
}
BEGIN_MESSAGE_MAP(CGuiTabbedPP, CGuiOfficeBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CGuiTabbedPP::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiOfficeBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_tbpp.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,0x3333))
		return -1;
	m_ArrButtons[0].SetEnabled(FALSE);
	m_ArrButtons[1].SetEnabled(FALSE);
	m_tree1.Create(TVS_HASLINES |TVS_LINESATROOT | TVS_HASBUTTONS,CRect(0,0,0,0),&m_tbpp,0x3331 );
	m_tree2.Create(TVS_HASLINES |TVS_LINESATROOT | TVS_HASBUTTONS,CRect(0,0,0,0),&m_tbpp,0x3331 );
	m_tree3.Create(TVS_HASLINES |TVS_LINESATROOT | TVS_HASBUTTONS,CRect(0,0,0,0),&m_tbpp,0x3331 );
	m_tbpp.SetImageList(IDB_BITPP,16,3,RGB(255,0,0));
	m_tbpp.Addtab(&m_tree1,"  Galeria  ",0);
	m_tbpp.Addtab(&m_tree2,"  Lista  ",1);
	//m_tbpp.Addtab(&m_tree3,"  Lista  ",-1);
	m_tbpp.SetColorTabs(GuiDrawLayer::GetRGBColorFace());
	m_tbpp.SetAutoAjust(TRUE);
	m_tbpp.ShowButtonClose(TRUE);
	// TODO:  Add your specialized creation code here

	return 0;
}
