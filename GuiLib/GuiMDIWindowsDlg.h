// GuiMDIWindowsDlg.h: interface for the CGuiMDIWindowsDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GUIMDIWINDOWSDLG_H__)
#define _GUIMDIWINDOWSDLG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGuiMDIWindowsDlg dialog

class CGuiMDIWindowsDlg : public CDialog
{
	// Construction
public:
	CGuiMDIWindowsDlg(CMDIFrameWnd* pMDIFrame, CWnd* pParentWnd);
	CGuiMDIWindowsDlg(CMDIFrameWnd* pMDIFrame);   
	
	// Dialog Data
	//{{AFX_DATA(CGuiMDIWindowsDlg)
	enum { IDD = IDD_GUI_WINDOW_MANAGE };
	CListBox	m_wndList;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiMDIWindowsDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	void  MDIMessage(UINT uMsg, WPARAM flag);
	void  FillWindowList(void);
	void  SelActive(void);
	void  UpdateButtons(void);
	
	CMDIFrameWnd* m_pMDIFrame;
	
	// Generated message map functions
	//{{AFX_MSG(CGuiMDIWindowsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSelChange();
	afx_msg void OnSave();
	afx_msg void OnActivate();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnUpdateUI(CCmdUI * pCmdUI);
	afx_msg void OnTileHorz();
	afx_msg void OnMinimize();
	afx_msg void OnTileVert();
	afx_msg void OnCascade();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(_GUIMDIWINDOWSDLG_H__)
