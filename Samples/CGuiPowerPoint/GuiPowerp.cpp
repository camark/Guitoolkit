// GuiPowerp.cpp : implementation file
//

#include "stdafx.h"
#include "CGuiPowerPoint.h"
#include "GuiPowerp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ID_CLOSE  WM_USER+1
/////////////////////////////////////////////////////////////////////////////
// CGuiPowerp
IMPLEMENT_DYNCREATE(CGuiPowerp, CGuiPowerPointView)
CGuiPowerp::CGuiPowerp()
{
}

CGuiPowerp::~CGuiPowerp()
{
}


BEGIN_MESSAGE_MAP(CGuiPowerp, CGuiPowerPointView)
	//{{AFX_MSG_MAP(CGuiPowerp)
	ON_WM_CREATE()
	ON_COMMAND(ID_CLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CGuiPowerp::OnClose()
{
	AfxMessageBox("What to do?");
}

/////////////////////////////////////////////////////////////////////////////
// CGuiPowerp message handlers

int CGuiPowerp::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CGuiPowerPointView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_tree1.Create(TVS_HASLINES |TVS_LINESATROOT | TVS_HASBUTTONS,CRect(0,0,0,0),&m_tbpp,0x3331 );
	m_tree2.Create(TVS_HASLINES |TVS_LINESATROOT | TVS_HASBUTTONS,CRect(0,0,0,0),&m_tbpp,0x3332 );
	m_tbpp.SetImageList(IDB_BITPP,16,3,RGB(255,0,0));
	m_tbpp.Addtab(&m_tree1,"  Esquemas  ",0);
	m_tbpp.Addtab(&m_tree2,"  Diapositivas  ",1);
	m_tbpp.SetIdButtonClose(ID_CLOSE);
	m_tbpp.ShowButtonClose(TRUE);
	return 0;
}
