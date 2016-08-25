#pragma once
#include "guiofficebar.h"
#include "GuiWorkPanel.h"
#include "GuiLabelButton.h"
#include "GuiImageLinkButton.h"
#include "GuiContainer.h"

class CGuiBarOffice :	public CGuiControlBar
{
public:
	CGuiBarOffice(void);
	virtual ~CGuiBarOffice(void);
	CGuiWorkPanel m_wndPanel;
	CGuiContainer m_ctClassView;
	CGuiLabelButton m_ArrLabels[10];
	CGuiImageLinkButton m_ArrLinks[10];
	CTreeCtrl*	m_TreeGaleria;
	void OnNuevoDoc();
	void OnNuevoWeb();
	void OnOpenDoc();
	virtual void OnBack();
	virtual void OnForWard();
	virtual void OnMenu();
	void UpdateChilds();
protected:
	//{{AFX_MSG(CMyBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
};
