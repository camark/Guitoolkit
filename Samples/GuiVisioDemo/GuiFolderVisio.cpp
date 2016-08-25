// GuiFolderVisio.cpp: implementation of the CGuiFolderVisio class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GuiVisioDemo.h"
#include "GuiFolderVisio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuiFolderVisio::CGuiFolderVisio()
{

}

CGuiFolderVisio::~CGuiFolderVisio()
{

}
BEGIN_MESSAGE_MAP(CGuiFolderVisio, CGuiControlBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CGuiFolderVisio::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_ctServer.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,124))
		return -1;
	// TODO:  Add your specialized creation code here
	 if (!m_fv.Create(WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), &m_ctServer, 125))
		 	return -1;
		 
	m_ctServer.AddComponen(&m_fv); 
	m_fv.SetImageList(IDB_BITMAP1,16,3,RGB(255,0,0));
	m_tree.Create(WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS,CRect(0,0,0,0),&m_fv,126);
	m_fv.AddFolder(&m_tree,"ToolBox1",0);
	return 0;
}
