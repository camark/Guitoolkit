// GuiToolBar.h: interface for the GuiToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUITOOLBAR_H__38CE47D6_A6A2_11D5_A8C6_0008C7B2934C__INCLUDED_)
#define AFX_GUITOOLBAR_H__38CE47D6_A6A2_11D5_A8C6_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GuiToolBar : public CControlBar  
{
public:
	GuiToolBar();
	virtual ~GuiToolBar();
public:
	BOOL Create (CWnd* pParentWnd, CString m_szTitle,UINT uID,DWORD dwStyle=WS_CHILD| WS_VISIBLE| CBRS_LEFT);
	// Overridables
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
protected:
	int m_iBorder;
	CBrush cb;
	CRect mrcBorder;
protected:
	//{{AFX_MSG(GuiToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnNcPaint();
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg UINT OnNcHitTest(CPoint point);
   // afx_msg void OnCaptureChanged(CWnd *pWnd);
 //   afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  //  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    //afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
    //afx_msg void OnPaint();
  
    //}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GUITOOLBAR_H__38CE47D6_A6A2_11D5_A8C6_0008C7B2934C__INCLUDED_)
