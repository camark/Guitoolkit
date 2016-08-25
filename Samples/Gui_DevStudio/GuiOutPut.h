#pragma once
#include "guicontrolbar.h"
#include "GuiTabWnd.h"
class CGuiOutPut :	public CGuiControlBar
{
protected:
	CGuiTabWnd	m_TabSolExplorer;
	CListCtrl   m_ListTask;
	CEdit		m_EditOutput;
	CEdit		m_EditFind;
	CListCtrl   m_Search;
public:
	CGuiOutPut(void);
	virtual ~CGuiOutPut(void);
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		m_TabSolExplorer.StyleDispl(dwDsp);
		CGuiControlBar::StyleDispl(dwDsp);
		
	}
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
