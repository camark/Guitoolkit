/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *							 (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software;so you are free to use it any of your		*
 * applications (Freeware, Shareware, Commercial),but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

#pragma once 

// CGuiStatusBar

//****************************************************************

class GUILIBDLLEXPORT  CGuiStatusBar : public CStatusBar
{
	DECLARE_DYNAMIC(CGuiStatusBar)

public:
	enum Style{
		   DEVSTUDIO=0,
           OFFICE=1
	};
	//**************************************
	CGuiStatusBar();
	virtual ~CGuiStatusBar();
	//**************************************
public:
	BOOL SetIndicators (const UINT* lpIDArray, int nIDCount);

	void		 Drawpanels(CDC *pDC);
	virtual void PreSubclassWindow();
	void		 DrawLB(CRect *rcLb,CDC* pDC);
	void		 ClearRect(CDC* pDC,CRect rc);
	void		 SetStyle(Style nStyle=CGuiStatusBar::DEVSTUDIO);
	void		 SetPanelText(CString szText,UINT uPanel);
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();
	}

	DWORD			m_StyleDisplay;
protected:
	Style m_Style;
	DECLARE_MESSAGE_MAP()
	CFont m_cfont;
public:
	afx_msg void OnPaint();
};




