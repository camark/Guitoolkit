/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 * (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software; so you are free to use it any of your		*
 * applications(Freeware, Shareware, Commercial), but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements :(Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

#if !defined(AFX_GUIDOCBAREXTENEX_H__2B746533_9AEB_11D5_A8C3_0008C7B2934C__INCLUDED_)
#define AFX_GUIDOCBAREXTENEX_H__2B746533_9AEB_11D5_A8C3_0008C7B2934C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GUILIBDLLEXPORT CGuiDocBarExtenEx : public CDockBar  
{
	DECLARE_DYNCREATE(CGuiDocBarExtenEx)

public:
	CGuiDocBarExtenEx();
	~CGuiDocBarExtenEx();
	
public:
	void	BarsDocking(CFrameWnd* pFrame, DWORD dwDockStyle);
	virtual void DoPaint(CDC* pDC);
	BOOL _IsMenuBar(int nPos, CPtrArray& arrBars);
	virtual void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		SendMessage(WM_NCPAINT);
		Invalidate(); 
		UpdateWindow();
	}

	DWORD	m_StyleDisplay;
public:
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockBarEx)
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	//}}AFX_VIRTUAL
	
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GUIDOCBAREXTEN_H__2B746533_9AEB_11D5_A8C3_0008C7B2934C__INCLUDED_)
