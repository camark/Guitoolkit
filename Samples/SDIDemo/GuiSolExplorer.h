#pragma once
#include "guicontrolbar.h"
#include "GuiTabWnd.h"
#include "GuiContainer.h"
#include "GuiMiniTool.h"

class CGuiSolExplorer :	public CGuiControlBar
{
protected:
	CGuiTabWnd	m_TabSolExplorer;
	CTreeCtrl   m_TreeSolExplorer;
	CTreeCtrl   m_TreeClassView;
	CTreeCtrl   m_TreeResourceView;
	CImageList	m_imgList;
	CGuiContainer m_ctSolution;
	CGuiMiniTool  m_miSolution;

	CGuiContainer m_ctClassView;
	CGuiMiniTool  m_miClassView;

public:
	void Onproperties();
	void OnNewFolder();
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		m_miSolution.StyleDispl(dwDsp);
		m_miClassView.StyleDispl(dwDsp);
		m_TabSolExplorer.StyleDispl(dwDsp);
		CGuiControlBar::StyleDispl(dwDsp);
	}
public:
	CGuiSolExplorer(void);
	virtual ~CGuiSolExplorer(void);
	void FillerSolExplorer();
	void FillTreeClassView();
	int  CreatContExplorer();
	int CreatContClassView();
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
};
