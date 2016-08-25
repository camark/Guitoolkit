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
#include "Guimditabbed.h"
#include "GuiMDIFrame.h"
#include "MenuBar.h"

BEGIN_MESSAGE_MAP(CGuiMDITabbed, CGuiTabbed)
	  ON_MESSAGE(WM_SIZEPARENT, OnSizeParent)
	  ON_WM_TIMER()
END_MESSAGE_MAP()






LRESULT CGuiMDITabbed::OnSizeParent(WPARAM, LPARAM lParam)
{
	AFX_SIZEPARENTPARAMS* pParams = (AFX_SIZEPARENTPARAMS*)lParam;
    CRect rc=pParams->rect;
	CFrameWnd* pParent=(CFrameWnd*)AfxGetMainWnd();
	if (pParent->IsKindOf(RUNTIME_CLASS(CFrameWnd)) == NULL) return 0;

	CGuiMDIFrame* p= (CGuiMDIFrame*)pParent;
	ASSERT_VALID(p);
	
	CMenuBar *m=p->GetMenuBar();
	if (!m->GetSafeHwnd()) 
	{
		KillTimer(1);
		return 0;
	}

	if (rc.top ==0 ) 
	{
		SetTimer(1,100,NULL);
		
	}
	if (GetCount() > 0 && m->IsWindowVisible())
	{
		pParams->rect.top += 24;	
		pParams->rect.left+=2;
		pParams->rect.right-=1;	
		pParams->rect.bottom-=1;		
		ShowWindow(SW_SHOW);
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
   MoveWindow(rc.left, rc.top , rc.Width(), rc.Height(), true);
   CClientDC dc(this);
   GetClientRect(rc);
   dc.Draw3dRect(rc,GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style),GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
   
   return 0;
}

void CGuiMDITabbed::OnTimer(UINT nIDEvent) 
{

	UpdateWindows();
	CFrameWnd* pParent = STATIC_DOWNCAST(CFrameWnd, AfxGetMainWnd());
	CGuiMDIFrame* p= (CGuiMDIFrame*)pParent;
	ASSERT_VALID(p);
	KillTimer(1);

	CMenuBar *m=p->GetMenuBar();
	if (GetCount() > 0 && m->IsWindowVisible())
	{
		if(IsWindowVisible()==FALSE)
			pParent->SendMessage(WM_SIZE);
	}
	
	if (!m->GetSafeHwnd()) 
	{
		KillTimer(1);
		return;
	}
	if (!m->IsWindowVisible())
	{
		CRect rc;
		ShowWindow(SW_HIDE);
		p->RecalcLayout();
	}
	if(m->IsFloating())
		p->RecalcLayout();

	
	
}

CGuiMDITabbed::CGuiMDITabbed(void)
{
	pParentWindow = NULL;
	hMenu=0;
}

CGuiMDITabbed::~CGuiMDITabbed(void)
{
}


void CGuiMDITabbed::OnScrollClose()
{
	CWnd* pWnd=GetNumWnd(GetCurtab());
	if (pWnd==NULL)
	{
		
		return;
	}
	pWnd->SendMessage(WM_CLOSE);
	UpdateWindows();
	if (GetCurtab()== 0)
		GetParentFrame()->RecalcLayout();
}

void CGuiMDITabbed::UpdateWindows()
{
	
CFrameWnd* pParent = STATIC_DOWNCAST(CFrameWnd, AfxGetMainWnd());

	SetTimer(1,200,NULL);
	CWnd* pWnd=CWnd::FromHandle(::GetTopWindow(GetParentFrame()->GetSafeHwnd()));	
	char ClassName[32];
	
	while (pWnd != NULL)
	{
		::GetClassName(pWnd->GetSafeHwnd(),ClassName,32);
		CString szClassName=ClassName;
		if(szClassName=="MDIClient")
			break;
		pWnd=pWnd->GetNextWindow();
	}
	ASSERT(::IsWindow(pWnd->GetSafeHwnd()));
	//primero adicionar los nuevos
	
	
	
	CWnd* pChild= CWnd::FromHandle(::GetTopWindow(pWnd->GetSafeHwnd()));	

		
	while(pChild != NULL)
	{
		CString m_Caption;
		pChild->GetWindowText(m_Caption);
		if (!m_Caption.IsEmpty()) 
		{
			
			if (!FindItem(pChild->GetSafeHwnd()))
			{

				Addtab(pChild,m_Caption,-1);
				SetTabMenu(hMenu);
			}
			else
				UpdateCaption(pChild,m_Caption);
			
		}
		
		pChild= CWnd::FromHandle(::GetNextWindow(pChild->GetSafeHwnd(), GW_HWNDNEXT));
		
	}

	//---eliminar las ventanas borradas
	int nNumtabs=GetCount();
	for (int i=0; i< nNumtabs; i++)
	{
			CWnd* pWnd=GetNumWnd(i);
			if (!::IsWindow(HWND(pWnd->GetSafeHwnd())))
			{
				DeleteTab(i);
				UpdateWindow();
				break;
			}
	}
	SetTimer(1,100,NULL);
	
}



