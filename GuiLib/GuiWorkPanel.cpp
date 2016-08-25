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
#include "guiworkpanel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CGuiWorkPanel::CGuiWorkPanel(void)
{
	m_PressDown=FALSE;
	m_PressUp=FALSE;
	m_nDif=0;
}

CGuiWorkPanel::~CGuiWorkPanel(void)
{
}

void  CGuiWorkPanel::RecalLayout()
{
	if (!GetSafeHwnd()) return;
	CRect rcClient;
	CClientDC dc(this);
	GetClientRect(rcClient);
	rcClient.DeflateRect(1,1);
	CRect rctemp=rcClient;
	rctemp.top+=7;
	int nRealval=0;

	rctemp.top+=m_nDif;
		
	int nTipo=0;
	m_nResultTools=m_nDif;
	for (int i=0; i < m_nItems;i++)
	{
		
		CComponents* m_cwnd=(CComponents*) m_arrContainer[i];
		
		if(m_cwnd->bTypeSmall == TRUE)
			nTipo=18;
		m_nResultTools+=nTipo;
		rctemp.bottom=rctemp.top+nTipo;
		m_cwnd->m_cwnd->MoveWindow(rctemp);
		if((rctemp.top < rcClient.top+7) || (rctemp.top > rcClient.bottom-25))
			m_cwnd->m_cwnd->ShowWindow(SW_HIDE);
		else 
			m_cwnd->m_cwnd->ShowWindow(SW_SHOW);
		nRealval+=nTipo;

		rctemp.top+=nTipo;
		
	}
	
	m_ToolDown.ShowWindow(SW_HIDE);
	m_ToolUp.ShowWindow(SW_HIDE);
	m_PressDown=TRUE;
	m_PressUp=TRUE;

	if (rcClient.Height() > 1)
	{
		if(nRealval+8 > rcClient.Height())
		{
			if (m_nDif < 0)
			{
				m_ToolUp.ShowWindow(SW_SHOW);
				m_ToolUp.MoveWindow(0,0,rcClient.Width(),8);
			}
			if (m_nDif==0 || m_nResultTools > rcClient.bottom-25)
			{
				m_ToolDown.ShowWindow(SW_SHOW);
				m_ToolDown.MoveWindow(0,rcClient.bottom-8,rcClient.Width(),8);
			}
		}
		else
		{
			if (m_nDif < 0)
			{
				m_ToolUp.ShowWindow(SW_SHOW);
				m_ToolUp.MoveWindow(0,0,rcClient.Width(),8);
			}
		}
		
	}
	

	
}


void  CGuiWorkPanel::SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	CBitmap cbmp;
	BITMAP bmp;
	m_imgList.Create(nBitmapID,cx,nGrow,crMask);
	cbmp.LoadBitmap(nBitmapID);
	cbmp.GetBitmap(&bmp);
	m_imgList.Add(&cbmp,crMask);

}

void CGuiWorkPanel::Addlabel(UINT ID_BUTTON,CGuiLabelButton* m_btn)
{
	if (!m_btn->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0),this,ID_BUTTON))
	{
		m_btn=NULL;
		return;
    }
	AddComponen(m_btn);
	m_btn->DrawUnderLine();
	m_btn->SetColor(RGB(255,255,255));

}

void CGuiWorkPanel::AddImageLink(UINT ID_BUTTON,int nNumImage,CGuiImageLinkButton* m_Linkbtn)
{
	if (!m_Linkbtn->Create(_T(""),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0),this,ID_BUTTON))
	{
		m_Linkbtn=NULL;
		return;
	}
	AddComponen(m_Linkbtn);
	m_Linkbtn->SethIcon(m_imgList.ExtractIcon(nNumImage));
	m_Linkbtn->SetColor(RGB(255,255,255));
	
}

BOOL CGuiWorkPanel::OnCommand(WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = (HWND) lParam;	
	for (int i=0; i < m_nItems;i++)
	{
			if (((CComponents*) m_arrContainer[i])->m_cwnd->m_hWnd
				== hwnd)
			{
				int x=((CComponents*) m_arrContainer[i])->m_cwnd->GetDlgCtrlID();
				CWnd* pParent= GetParent();
				pParent->SendMessage (WM_COMMAND,x);
				AfxGetMainWnd()->SendMessage(WM_COMMAND,x);
				return TRUE;
			}
	
	}
	if (wParam == ID_GUI_TOOLUP)
		OnUp();
	
	if (wParam == ID_GUI_TOOLDOWN)
		OnDownd();
	
	return FALSE;

}


void  CGuiWorkPanel::OnDownd()
{
	m_nDif--;
	m_PressDown=TRUE;
	m_PressUp=FALSE;
	RecalLayout();
}
void  CGuiWorkPanel::OnUp()
{
	m_nDif++;
	m_PressDown=FALSE;
	m_PressUp=TRUE;
	RecalLayout();
}

BEGIN_MESSAGE_MAP(CGuiWorkPanel, CGuiContainer)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND(ID_GUI_TOOLUP,OnUp)
	ON_COMMAND(ID_GUI_TOOLDOWN,OnDownd)
	ON_WM_SYSCOLORCHANGE()
END_MESSAGE_MAP()

void CGuiWorkPanel::OnSysColorChange( )
{
	CGuiContainer::OnSysColorChange( );
	m_ToolUp.SetColor(GuiDrawLayer::GetRGBColorFace());
	m_ToolDown.SetColor(GuiDrawLayer::GetRGBColorFace());
	
	
}
int CGuiWorkPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiContainer::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CBitmap cbmp;
	BITMAP bmp;
	m_imgListLocal.Create(IDB_GUI_DOCKBAR,9,11,RGB(255,0,255));
	cbmp.LoadBitmap(IDB_GUI_DOCKBAR);
	cbmp.GetBitmap(&bmp);
	m_imgListLocal.Add(&cbmp,RGB(255,0,255));
	SetColor(RGB(255,255,255));
	m_ToolUp.Create(_T(""),WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,0,0),this,ID_GUI_TOOLUP);
	m_ToolUp.SethIcon(m_imgListLocal.ExtractIcon(8));
	m_ToolUp.SetScrollButton();
	m_ToolDown.Create(_T(""),WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,0,0),this,ID_GUI_TOOLDOWN);
	m_ToolDown.SethIcon(m_imgListLocal.ExtractIcon(0));
	m_ToolDown.SetScrollButton();
	m_ToolUp.ShowWindow(SW_HIDE);
	m_ToolDown.ShowWindow(SW_HIDE);
	SetDrawBorder();
	return 0;
}

void CGuiWorkPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CGuiContainer::OnPaint() for painting messages
	CRect rcClient;
	GetClientRect(rcClient);
	CBrush cb;
	cb.CreateSolidBrush(RGB(255,255,255));
	dc.FillRect(rcClient,&cb);
	

	if (m_ToolUp.IsWindowVisible())
		m_ToolUp.MoveWindow(0,0,rcClient.Width(),8);
	else
		m_ToolUp.MoveWindow(0,0,0,0);

	if (m_ToolDown.IsWindowVisible())
		m_ToolDown.MoveWindow(0,rcClient.bottom-8,rcClient.Width(),8);
	else
		m_ToolDown.MoveWindow(0,0,0,0);
	
}
