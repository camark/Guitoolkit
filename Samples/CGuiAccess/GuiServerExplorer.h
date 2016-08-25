#pragma once
#include "guicontrolbar.h"
#include "GuiContainer.h"
#include "guipanelAccess.h"
#include "GuiFolder.h"
#include "GuiSplitter.h"
#include "GuiToolButton.h"
class CGuiServerExplorer :	public CGuiControlBar
{
protected:
	
	CGuiPanelAccess	m_panelAccess;
	CGuiFolder			m_Folder;
	CGuiFolder			m_Folder1;
	CGuiSplitter		m_Splitter;
	CGuiSplitter		m_Splitter1;
	CGuiToolButton*     m_tb1;
	CGuiToolButton*     m_tb2;
	CTreeCtrl  m_TreeServerExplorer;
	CTreeCtrl  m_TreeServerExplorer1;
	CTreeCtrl  m_TreeServerExplorer2;
	CTreeCtrl  m_TreeServerExplorer3;
public:
	CGuiServerExplorer(void);
	virtual ~CGuiServerExplorer(void);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
