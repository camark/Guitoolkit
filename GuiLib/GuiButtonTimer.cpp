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

#include "stdafx.h"
#include "GuiButtonTimer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuiButtonTimer::CGuiButtonTimer()
{
	bPress      = FALSE;
	m_nInterval = 50;
}

CGuiButtonTimer::~CGuiButtonTimer()
{
}

BEGIN_MESSAGE_MAP(CGuiButtonTimer, CGuiToolButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CGuiButtonTimer::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!bPress)
		return;
	bPress = FALSE;
	KillTimer(1);
	// CGuiNormalButton::OnLButtonUp(nFlags, point);
}
void CGuiButtonTimer::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (bPress) 
		return;
	bPress = TRUE;
	SetTimer(1, m_nInterval, NULL);
	// CGuiNormalButton::OnLButtonDown(nFlags, point);
}

void CGuiButtonTimer::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (bPress == FALSE) 
		return;
	CRect rc;
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	GetClientRect(rc);
	if (rc.PtInRect(pt))
	{
		CWnd* pParent = GetParent();
		if (IsWindowEnabled())
			pParent->SendMessage(WM_COMMAND, GetDlgCtrlID());
		// bPress=FALSE;
		// KillTimer(1);
	}
	else
	{
		bPress = FALSE;
		KillTimer(1);
		// CGuiNormalButton::OnTimer(nIDEvent);
	}
}
