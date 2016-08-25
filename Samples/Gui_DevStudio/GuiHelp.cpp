#include "StdAfx.h"
#include "guihelp.h"
#include "resource.h"

CGuiHelp::CGuiHelp(void)
{
}

CGuiHelp::~CGuiHelp(void)
{
}
BEGIN_MESSAGE_MAP(CGuiHelp, CGuiControlBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CGuiHelp::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_TabSolExplorer.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,0x9999))
		return -1;

	const DWORD dwStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS ;
	
	if (!m_TreeContents.Create(dwStyle,CRect(0,0,0,0), &m_TabSolExplorer, 1))
		return -1;

	if (!m_Treeindex.Create(dwStyle,	CRect(0,0,0,0), &m_TabSolExplorer, 2))
		return -1;

	if (!m_TreeSearch.Create(dwStyle,	CRect(0,0,0,0), &m_TabSolExplorer, 2))
		return -1;
	
	
	m_TabSolExplorer.SetImageList(IDB_DBPROJECTS, 16,5, RGB (255, 0, 0));
	m_TabSolExplorer.Addtab(&m_TreeContents,"Contents",3);
	m_TabSolExplorer.Addtab(&m_Treeindex,"Index",4);
	m_TabSolExplorer.Addtab(&m_TreeSearch,"Search",5);
	SetIcon(IDB_BITMAPHELP,16,1,RGB(255,0,0));
	// TODO:  Add your specialized creation code here

	return 0;
}
