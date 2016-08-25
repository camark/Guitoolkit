#pragma once
#include "guicontrolbar.h"
#include "GuiTabWnd.h"
class CGuiHelp :	public CGuiControlBar
{
protected:
	CGuiTabWnd	m_TabSolExplorer;
	CTreeCtrl   m_TreeContents;
	CTreeCtrl   m_Treeindex;
	CTreeCtrl   m_TreeSearch;
public:
	CGuiHelp(void);
	virtual ~CGuiHelp(void);
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		m_TabSolExplorer.StyleDispl(dwDsp);
		CGuiControlBar::StyleDispl(dwDsp);
		
	}
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
