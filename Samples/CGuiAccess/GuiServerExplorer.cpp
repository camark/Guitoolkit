#include "StdAfx.h"
#include "guiserverexplorer.h"
#include "resource.h"

#define ID_REFRESH 0x355
#define ID_CONNECT 0x356
#define ID_CONSERVER 0x367

CGuiServerExplorer::CGuiServerExplorer(void)
{
}

CGuiServerExplorer::~CGuiServerExplorer(void)
{
}
BEGIN_MESSAGE_MAP(CGuiServerExplorer, CGuiControlBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CGuiServerExplorer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	const DWORD dwStyle =WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS ;
	
	if (!m_Splitter.Create(this))
		return -1;

	if (!m_Splitter1.Create(&m_Splitter))
		return -1;

	if (!m_Folder.Create(WS_VISIBLE|WS_CHILD,
			CRect(0,0,0,0),&m_Splitter, 0xfff))
		return -1;

	if (!m_Folder1.Create(WS_VISIBLE|WS_CHILD,
			CRect(0,0,0,0),&m_Splitter1, 0xfff1))
		return -1;
		/*if (!m_panelAccess.Create(WS_VISIBLE,
		CRect(0,0,0,0), &m_Folder, 1))
		return -1;

*/
	m_Splitter.SeTypeALing(CGuiSplitter::ALINGVERT);//ALINGHORZ
	m_Splitter.SetPixelWidht(2);
	m_Splitter.AddLeftCtrl(&m_Splitter1,3);
	m_Splitter.AddRightCtrl(&m_Folder,4);
	m_Splitter.SetStyleSeparator(CGuiSplitter::STYLE3D,
		GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());

	m_Splitter1.SeTypeALing(CGuiSplitter::ALINGHORZ);//ALINGHORZ
	m_Splitter1.SetPixelWidht(2);
	m_Splitter1.AddLeftCtrl(&m_Splitter1,3);
	m_Splitter1.AddRightCtrl(&m_Folder,4);
	m_Splitter1.SetStyleSeparator(CGuiSplitter::STYLE3D,
		GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());
	
	if(!m_TreeServerExplorer.Create(dwStyle,CRect(0,0,0,0),&m_Folder,3 ))
		return -1;
	if(!m_TreeServerExplorer1.Create(dwStyle,CRect(0,0,0,0),&m_Folder1,4 ))
		return -1;
	
	if(!m_TreeServerExplorer2.Create(dwStyle,CRect(0,0,0,0),&m_Splitter1,3 ))
		return -1;
	
	m_Splitter1.AddLeftCtrl(&m_Folder1,3);
	m_Splitter1.AddRightCtrl(&m_TreeServerExplorer2,4);
	
	
	m_Folder.AddFolder(&m_TreeServerExplorer,"Objetos");
	m_Folder1.AddFolder(&m_TreeServerExplorer1,"Objetos1");

/*	m_panelAccess.SetImageList(IDB_BITMAP1, 16, 3, RGB(255,0,0));
	m_tb1=m_panelAccess.AddButton(890,0);
	m_tb2=m_panelAccess.AddButton(891,1);
	
	*/
	
	// TODO:  Add your specialized creation code here

	return 0;
}


