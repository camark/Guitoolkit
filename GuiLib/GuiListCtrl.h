#pragma once


// CGuiListCtrl

class CGuiListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CGuiListCtrl)

public:
	CGuiListCtrl();
	virtual ~CGuiListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};


