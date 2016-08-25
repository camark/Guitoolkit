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
 * -Ernesto Garcia															*	
 ****************************************************************************/

#include "stdafx.h"
#include "GuiLib.h"
#include "guisystray.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CGuiSysTray

IMPLEMENT_DYNAMIC(CGuiSysTray, CWnd)

CGuiSysTray::CGuiSysTray()
{
	memset(&tnid,sizeof(NOTIFYICONDATA),0x00);
	tnid.cbSize=sizeof(NOTIFYICONDATA);
	m_bStartAnimation=FALSE;
	m_ActualImage=0;
	m_pMenu=NULL;
}

CGuiSysTray::~CGuiSysTray()
{
    Del();
}


BEGIN_MESSAGE_MAP(CGuiSysTray, CWnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CGuiSysTray message handlers

void CGuiSysTray::StartAnimation(int nMilliseconds,int nPosInit, int nPosEnd)
{
	if(m_bStartAnimation)
		return;
	m_bStartAnimation=TRUE;
	m_ActualImage=nPosInit;
	m_Init=nPosInit;
	m_End=nPosEnd;
	SetTimer(156,100,0);
}

void CGuiSysTray::StopAnimation()
{
	KillTimer(156);
	m_ActualImage=m_End=m_Init=0;
}

BOOL CGuiSysTray::Add(UINT uID,UINT uCallBackMessage, HICON hIcon, LPCTSTR lpszTip)
{
  tnid.uID = uID;
  tnid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
  tnid.uCallbackMessage = uCallBackMessage;
  tnid.hIcon = hIcon;
  _tcsncpy(tnid.szTip,lpszTip,sizeof(tnid.szTip)-1);
  return (Shell_NotifyIcon(NIM_ADD, &tnid));
}

BOOL CGuiSysTray::Update(UINT uID, HICON hIcon, LPCTSTR lpszTip)
{
  tnid.hIcon = hIcon;
  _tcsncpy(tnid.szTip,lpszTip,sizeof(tnid.szTip)-1);
  return (Shell_NotifyIcon(NIM_MODIFY, &tnid));
}

BOOL CGuiSysTray::Del()
{
  return(Shell_NotifyIcon(NIM_DELETE, &tnid));
}

BOOL CGuiSysTray::SetIcon(HICON hIcon)
{
  tnid.hIcon = hIcon;
  tnid.uFlags |= NIF_ICON;
  return (Shell_NotifyIcon(NIM_MODIFY, &tnid));
}

BOOL CGuiSysTray::SetIcon(LPCTSTR lpszIcon)
{
	return SetIcon(AfxGetApp()->LoadIcon(lpszIcon));
}

BOOL CGuiSysTray::SetTips(LPCTSTR lpszTip)
{
  tnid.uFlags |= NIF_TIP;	
  _tcsncpy(tnid.szTip,lpszTip,sizeof(tnid.szTip)-1);
  return (Shell_NotifyIcon(NIM_MODIFY, &tnid));
}

void CGuiSysTray::SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	CBitmap cbmp;
	BITMAP bmp;
	m_ImgList.Create(nBitmapID,cx,nGrow,crMask);
	cbmp.LoadBitmap(nBitmapID);
	cbmp.GetBitmap(&bmp);
	m_ImgList.Add(&cbmp,crMask);

}

BOOL CGuiSysTray::Create(CWnd* pParentWnd, UINT nID,UINT uCallBackMessage, HICON hIcon, LPCTSTR lpszTip)
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT(pParentWnd->GetSafeHwnd());
	CWnd::CreateEx(0, AfxRegisterWndClass(0),_T(""), WS_POPUP, CRect(0,0,1,1), pParentWnd, 0);
	tnid.hWnd = GetSafeHwnd();
	if(Add(nID,uCallBackMessage,hIcon,lpszTip))
		return TRUE;
	else
	return TRUE;
}

void CGuiSysTray::SetSysMenu(CMenu* pMenu)
{
	ASSERT(pMenu->GetSafeHmenu());
	m_pMenu=pMenu;
}

LRESULT CGuiSysTray::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message== tnid.uCallbackMessage)
    { 
        if (LOWORD(lParam) == WM_RBUTTONUP)
       {
            if(m_pMenu == NULL) return FALSE;
           CPoint pt;
          GetCursorPos(&pt);
           m_pMenu->GetSubMenu(0)->TrackPopupMenu(0, pt.x, pt.y, GetParent(), NULL);
        }
        //ERNESTO -> This portion of code was outside the if (message== tnid.uCallbackMessage), so it was never reached and double-click was never sent.
        else if (LOWORD(lParam) == WM_LBUTTONDBLCLK) 
            GetParent()->SendMessage(WM_LBUTTONDBLCLK,0, 0);
    }
    else
        return CWnd::WindowProc(message, wParam, lParam);
    return TRUE;
}


void CGuiSysTray::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 156)
	{
		if (m_ActualImage > m_End)
			m_ActualImage=m_Init;
		SetIcon(m_ImgList.ExtractIcon(m_ActualImage));
		m_ActualImage++;
	}
	CWnd::OnTimer(nIDEvent);
}

