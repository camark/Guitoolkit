#pragma once

#include "GuiControlBar.h"

static CFont m_fontHorzMenu, m_fontVertMenu;
static int _cyHorzFont, _cyMenuOnBar, _cyTextMargin;
const int CXTEXTMARGIN = 5;

static BOOL InitGlobalFont()
{

	if (m_fontHorzMenu.GetSafeHandle() != NULL &&  m_fontVertMenu.GetSafeHandle() != NULL)
		return TRUE;
	m_fontHorzMenu.DeleteObject();
	m_fontVertMenu.DeleteObject();

	// create fonts
	NONCLIENTMETRICS info; info.cbSize = sizeof(info);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);
	if(!m_fontHorzMenu.CreateFontIndirect(&info.lfMenuFont))
		return FALSE;

	// create vertical font
	info.lfMenuFont.lfEscapement = -900;
	info.lfMenuFont.lfOrientation = -900;
	strcpy(info.lfMenuFont.lfFaceName,"verdana");
	if(!m_fontVertMenu.CreateFontIndirect(&info.lfMenuFont))
		return FALSE;

	_cyHorzFont = abs(info.lfMenuFont.lfHeight);

	// calc Y text margin
	_cyMenuOnBar = info.iMenuHeight;
	_cyMenuOnBar = max(_cyMenuOnBar, ::GetSystemMetrics(SM_CYSMICON));
	_cyTextMargin = (_cyMenuOnBar - _cyHorzFont) / 2;

	return TRUE;
}

class CDockButton : public CWnd
{
// Construction
public:
	CDockButton();

protected:
	CRect   rect;
	CString m_Caption;
	UINT	m_nDockBarAling;
	HWND	m_hWnd;
	BOOL	m_bMouseOver;
	HICON	m_hIcon;
	CSize   m_szBtn;
// Attributes

public:
	
	void SetRect(CRect rc=CRect(0,0,0,0))
	{
		rect=rc;
	}

	HWND  GethWnd() {return m_hWnd; }
	CGuiControlBar* GetBar(HWND hWnd);
	CGuiControlBar* IsControlVisible(CGuiControlBar*);
	void DrawTextHorz(CDC* pDC, CRect m_rect);
	void DrawTextVert(CDC* pDC, CRect m_rect);
	CString GetString(){ return m_Caption;}
	UINT GetAling() {return m_nDockBarAling;}

	void SetIconBtn(HICON hIcon); 
	CSize GetSizeIconBtn()
	{
		if(m_hIcon != NULL)
			return m_szBtn;
		return CSize(0,0);
	} 
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockButton)
	public:
	virtual BOOL Create(LPCTSTR lpszWindowName,DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, HWND m_hWnd);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDockButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDockButton)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};






class GUILIBDLLEXPORT CGuiDockToolBarEx : public CControlBar
{
	// Construction
public:
	CGuiDockToolBarEx();

	// Attributes
public:

	// Operations
public:
	int n_numBars;
	CPtrArray	m_ArrayButton;
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiDockToolBar)
public:
	virtual BOOL Create(CWnd* pParentWnd, DWORD dwAling);
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual ~CGuiDockToolBarEx();
	void AddToolBars(CGuiControlBar* m_ctrlBars);
	void DeleteToolBars(CGuiControlBar* m_ctrlBars);
	void UpdateBars();
	void CalcButton();
	virtual int GetCount(){return n_numBars;}
	CGuiControlBar* GetBar(int );
	
	// Generated message map functions
protected:
	int      m_Size;
	COLORREF m_clrface;

protected:
	//{{AFX_MSG(CGuiDockToolBarEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnSysColorChange();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
