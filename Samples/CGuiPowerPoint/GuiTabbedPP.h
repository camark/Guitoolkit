#pragma once
#include "guiofficebar.h"
#include "GuiTabPowerPoint.h"
class CGuiTabbedPP :public CGuiOfficeBar
{
protected:
	CGuiTabPowerPoint m_tbpp;
	CTreeCtrl m_tree1;
	CTreeCtrl m_tree2;
	CTreeCtrl m_tree3;
public:
	CGuiTabbedPP(void);
	virtual ~CGuiTabbedPP(void);


	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
