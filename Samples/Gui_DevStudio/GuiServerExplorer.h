#pragma once
#include "guicontrolbar.h"
#include "GuiContainer.h"

class CGuiServerExplorer :	public CGuiControlBar
{
protected:
	
	CTreeCtrl   m_TreeServerExplorer;
	CGuiContainer m_ctServer;
	CGuiMiniTool  m_miServer;
public:
	void OnConnect();
	void OnServer();
	void OnExplorer();
	CGuiServerExplorer(void);
	virtual ~CGuiServerExplorer(void);
	int CreatServerExplorer();
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		m_miServer.StyleDispl(dwDsp);
		CGuiControlBar::StyleDispl(dwDsp);
		
	}
	
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
