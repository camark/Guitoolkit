// GuiPanelAccessDemoDlg.h : header file
//

#if !defined(AFX_GUIPANELACCESSDEMODLG_H__8039F59E_CAA5_4C14_9716_7D0193089547__INCLUDED_)
#define AFX_GUIPANELACCESSDEMODLG_H__8039F59E_CAA5_4C14_9716_7D0193089547__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiStaticStandar.h"
#include "GuiSplitter.h"
#include "GuiPanelAccess.h"
#include "GuiFolderFlat.h"
#include "GuiMiniTool.h"
/////////////////////////////////////////////////////////////////////////////
// CGuiPanelAccessDemoDlg dialog

class CGuiPanelAccessDemoDlg : public CDialog
{
// Construction
public:
	CGuiPanelAccessDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGuiPanelAccessDemoDlg)
	enum { IDD = IDD_GUIPANELACCESSDEMO_DIALOG };
	CGuiMiniTool	m_minitool;
	CGuiStaticStandar	m_Frame;
	CGuiSplitter    m_Splitter;
	CGuiPanelAccess m_panAcc;
	CGuiPanelAccess m_panAcc1;
	CGuiFolderFlat		cf;
		
	CGuiToolButton  m_btn1;
	CGuiToolButton  m_btn2;
	CGuiToolButton  m_btn3;
	CGuiToolButton  m_btn4;
	CGuiToolButton  m_btn5;
	CGuiToolButton  m_btn6;
	CGuiToolButton  m_btn7;
	CGuiToolButton  m_btn8;
	CGuiToolButton  m_btn9;
	CGuiToolButton  m_btn10;
	CGuiToolButton  m_btn11;
	CGuiToolButton  m_btn12;
	CGuiToolButton  m_btn13;
	CGuiToolButton  m_btn14;
	CGuiToolButton  m_btn15;
	CGuiToolButton  m_btn16;
	CGuiToolButton  m_btn17;
	CListCtrl m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiPanelAccessDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	void OnTest();
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGuiPanelAccessDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIPANELACCESSDEMODLG_H__8039F59E_CAA5_4C14_9716_7D0193089547__INCLUDED_)
