#include "StdAfx.h"
#include "guioutput.h"
#include "resource.h"

CGuiOutPut::CGuiOutPut(void)
{
}

CGuiOutPut::~CGuiOutPut(void)
{
}
BEGIN_MESSAGE_MAP(CGuiOutPut, CGuiControlBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CGuiOutPut::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_TabSolExplorer.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,0x9999))
		return -1;

	const DWORD dwStyle =LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	
	if (!m_ListTask.Create(dwStyle,CRect(0,0,0,0), &m_TabSolExplorer, 1))
		return -1;

	if (!m_Search.Create(dwStyle,CRect(0,0,0,0), &m_TabSolExplorer, 2))
		return -1;

	if (!m_EditOutput.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0), &m_TabSolExplorer, 2))
		return -1;

	if (!m_EditFind.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0), &m_TabSolExplorer, 2))
		return -1;
	
	
	m_TabSolExplorer.SetImageList(IDB_DBPROJECTS, 16,8, RGB (255, 0, 0));
	m_TabSolExplorer.Addtab(&m_ListTask,"Task List",6);
	m_TabSolExplorer.Addtab(&m_EditOutput,"Output",7);
	m_TabSolExplorer.Addtab(&m_EditFind,"Find Results 1",8);
	m_TabSolExplorer.Addtab(&m_Search,"Search Results",5);
	SetIcon(IDB_BITMAPHELP,16,5,RGB(255,0,0),3);
	return 0;
}
