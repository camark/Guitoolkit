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

// CGuiSplitterWnd

//*****************************************************************
class GUILIBDLLEXPORT CGuiSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CGuiSplitterWnd)

public:
	//********************************************
		CGuiSplitterWnd();
		virtual ~CGuiSplitterWnd();
	//********************************************
public:
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
	void SetBorderFlat(BOOL bBorder=TRUE);
		virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{	
		m_StyleDisplay=dwDsp;
		if (m_StyleDisplay==GUISTYLE_XP)
			m_bBorder=TRUE;
		else
			m_bBorder=FALSE;
		SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();
	}
	DWORD			m_StyleDisplay;
protected:
	BOOL m_bBorder;
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

};


