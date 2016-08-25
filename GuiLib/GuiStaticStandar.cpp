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

#include "stdafx.h"
#include "GuiStaticStandar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiStaticStandar

CGuiStaticStandar::CGuiStaticStandar()
{
	m_pWnd=NULL;
}

CGuiStaticStandar::~CGuiStaticStandar()
{
}


BEGIN_MESSAGE_MAP(CGuiStaticStandar, CStatic)
	//{{AFX_MSG_MAP(CGuiStaticStandar)
	ON_WM_SIZE()
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiStaticStandar message handlers

void CGuiStaticStandar::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CStatic::PreSubclassWindow();
}

void CGuiStaticStandar::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	RecalLayout();
	// TODO: Add your message handler code here
	
}

void CGuiStaticStandar::AddChild(CWnd* pWnd)
{
	m_pWnd=pWnd;
	RecalLayout();
}

void CGuiStaticStandar::RecalLayout()
{
	if (m_pWnd== NULL) return;
	CRect rcClient;
	GetClientRect(rcClient);
	m_pWnd->MoveWindow(rcClient);
	
}

