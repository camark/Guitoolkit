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
#include "GuiToolButton.h"
#include "GuiDrawLayer.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// CGuiToolButton

#define UPDATEWIN  Invalidate();\
				   UpdateWindow();  

IMPLEMENT_DYNAMIC(CGuiToolButton, CButton)
CGuiToolButton::CGuiToolButton()
{
	m_bMouserOver=FALSE;
	m_SizeImage=CSize(0,0);
	m_SizeText=CSize(0,0);
	m_clColor=GuiDrawLayer::GetRGBColorXP();
	m_bShowDark=TRUE;
	m_ScrollButton=FALSE;
	m_clrFont=RGB(0,0,0);
	m_bSimple=FALSE;
	m_Icon=NULL;
	m_StyleDisplay=GUISTYLE_XP;
	m_Transparent=TRUE;
	
}

CGuiToolButton::~CGuiToolButton()
{
	//if (m_Icon!=NULL) DestroyIcon(m_Icon);
}


BEGIN_MESSAGE_MAP(CGuiToolButton, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CGuiToolButton message handlers

void CGuiToolButton::SetFontColor(COLORREF clrFont)
{
	m_clrFont=clrFont;
}


void CGuiToolButton::ShowDark(BOOL bShow)
{
	m_bShowDark=bShow;
}

void CGuiToolButton::OnSysColorChange( )
{
	m_clColor=GuiDrawLayer::GetRGBColorXP();
	CButton::OnSysColorChange( );
	
}

void CGuiToolButton::PreSubclassWindow() 
{
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

void CGuiToolButton::SetScrollButton(BOOL bScroll)
{
	m_ScrollButton=bScroll;
}

void CGuiToolButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC*  pdc= CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc=lpDrawItemStruct->rcItem;
	UINT  uState=lpDrawItemStruct->itemState;
	CBrush cb;
	
	if( uState & ODS_SELECTED) //the button is pressed
	{
		if(m_StyleDisplay==GUISTYLE_2003 || m_StyleDisplay == GUISTYLE_2003MENUBTN)
				cb.CreateSolidBrush(GuiDrawLayer::m_Theme? RGB(249,200,102):GuiDrawLayer::GetRGBPressBXP());
			else
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBPressBXP());

	}	
	else
		if (m_bMouserOver)
		{
			if(m_StyleDisplay==GUISTYLE_2003 || m_StyleDisplay== GUISTYLE_2003MENUBTN)
				cb.CreateSolidBrush(GuiDrawLayer::m_Theme? RGB(252,230,186):GuiDrawLayer::GetRGBFondoXP());
			else
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBFondoXP());

		}
		else
		{
		
			if(m_StyleDisplay==GUISTYLE_2003)
			{
				if (m_Transparent && m_StyleDisplay )
					cb.CreateStockObject(NULL_BRUSH);
				else
				{
					CGradient M(CSize(rc.Width(),rc.Height()+1));	
					M.PrepareReverseVertTab(pdc,m_StyleDisplay);
					M.Draw(pdc,rc.left,rc.top,0,0,rc.Width(),rc.Height(),SRCCOPY);	
				}
			}
			else
				if (m_StyleDisplay== GUISTYLE_2003MENUBTN)
					cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(m_StyleDisplay));
				else
					cb.CreateSolidBrush(m_clColor);
			
		}
	
	if (( uState & ODS_SELECTED) || m_bMouserOver )
	{
		pdc->Draw3dRect(rc,GuiDrawLayer::GetRGBCaptionXP(),GuiDrawLayer::GetRGBCaptionXP());
		rc.DeflateRect(1,1);
		
	}
	else if(m_ScrollButton || m_bSimple)
	{
		pdc->Draw3dRect(rc,GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());
		rc.DeflateRect(1,1);
	}

	if (m_Transparent )
		pdc->FillRect(rc,&cb);


	int calculodify;
	calculodify=rc.Height()-(m_SizeImage.cy);
	calculodify/=2;
	int nHeigh=calculodify+(m_bShowDark?1:0);
	int nWidth=m_ScrollButton?rc.Width()/2 :2;
	CPoint m_point=CPoint(nWidth,nHeigh);
	
	if (m_SizeImage.cx > 2)
	{
		if(m_bMouserOver == 1 && !(uState & ODS_DISABLED) && !(uState & ODS_SELECTED) && m_bShowDark)
		{
			CPoint p(m_point.x+1,m_point.y+1);
			pdc->DrawState(p,m_SizeImage,m_Icon,DSS_MONO,CBrush (GuiDrawLayer::GetRGBColorShadow()));
			m_point.x-=1; m_point.y-=1;
		}
		pdc->DrawState (m_point, m_SizeImage,m_Icon,
					(uState==ODS_DISABLED?DSS_DISABLED:DSS_NORMAL),(CBrush*)NULL);
	}
	if (m_SizeText.cx > 2)
	{
		int nMode = pdc->SetBkMode(TRANSPARENT);
		CRect rectletra=rc;
		int nt=m_ScrollButton?0:8;
		rectletra.left+=m_SizeImage.cx+nt;
		CPoint pt=CSize(rectletra.top,rectletra.left);
		if (uState & ODS_DISABLED)
			pdc->DrawState(pt, m_SizeText, m_szText, DSS_DISABLED, TRUE, 0, (CBrush*)NULL);
		else
		{
			if(m_bMouserOver != 1) 
				pdc->SetTextColor(m_clrFont);
			pdc->DrawText(m_szText,rectletra,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
		}
		pdc->SetBkMode(nMode);
	}
	
	// TODO:  Add your code to draw the specified item
}

void CGuiToolButton::SetColor(COLORREF clColor)
{
	m_clColor=clColor;

}

BOOL CGuiToolButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CGuiToolButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rcCli;
	GetClientRect(rcCli);
	ClientToScreen(rcCli);
	GetParent()->ScreenToClient(rcCli);
	GetParent()->InvalidateRect(rcCli);
	GetParent()->UpdateWindow();
	UPDATEWIN 		
	CButton::OnLButtonUp(nFlags, point);
		
}

void CGuiToolButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CButton::OnLButtonDown(nFlags, point);
}

void CGuiToolButton::OnMouseMove(UINT nFlags, CPoint 
								 point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bMouserOver) return;
	if (!IsTopParentActive() || !GetTopLevelParent()->IsWindowEnabled())
		return;
	CRect rc;
	GetClientRect(rc);
	if (rc.PtInRect(point))
	{
		m_bMouserOver=TRUE;
		SetTimer(1,50,0);
		UPDATEWIN 		
	}
	
	CButton::OnMouseMove(nFlags, point);
}

void CGuiToolButton::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bMouserOver) return;
	CRect rc;
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	GetClientRect(rc);

	if (!rc.PtInRect(pt))
	{
		m_bMouserOver=FALSE;
		KillTimer(1);
		ClientToScreen(rc);
		GetParent()->ScreenToClient(rc);
		GetParent()->InvalidateRect(rc);
		GetParent()->UpdateWindow();
		UPDATEWIN 		
	}
	CButton::OnTimer(nIDEvent);
}

BOOL CGuiToolButton::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_MOUSEMOVE)
		if (m_toolTip.GetSafeHwnd())
			m_toolTip.RelayEvent(pMsg);

	return CButton::PreTranslateMessage(pMsg);
}

void CGuiToolButton::SetToolTip(LPCTSTR lpMsg)
{
	if (GetSafeHwnd ()== NULL) return;
	if (lpMsg != NULL)
	{
		if (m_toolTip.GetSafeHwnd () == NULL) 
		{
			m_toolTip.Create(this,TTS_ALWAYSTIP);
			m_toolTip.Activate(TRUE);
			m_toolTip.AddTool(this,lpMsg);
		}
		else
		{
			m_toolTip.UpdateTipText(lpMsg,this);	
		}
	}
	else
	{
		if (m_toolTip.GetSafeHwnd () == NULL) 
		{
			m_toolTip.Create(this,TTS_ALWAYSTIP);
			m_toolTip.AddTool(this,lpMsg);
		}
		else
			m_toolTip.UpdateTipText(lpMsg,this);	
		m_toolTip.Activate(FALSE);
	}
		
}

CSize CGuiToolButton::GetSizeButton()
{
	m_ReposWindow=FALSE;
	RecalSize();
	m_ReposWindow=TRUE;
	return m_szButton;
}

void CGuiToolButton::RecalSize()
{
	CRect m_rect;
	int m_High=0;
	if (GetSafeHwnd() == NULL) return;
	CClientDC dc(this);
	GetClientRect(&m_rect);
	CSize SizeCad=CSize(0,0);
	m_High=max(m_SizeImage.cy,m_SizeText.cy);
	m_High=max(m_High,m_rect.Height());
	m_szButton= CSize(m_SizeText.cx+m_SizeImage.cx+7,m_High);
	if (m_ReposWindow==TRUE)
		SetWindowPos (NULL, -1,-1, m_szButton.cx, m_High,
			SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CGuiToolButton::SetCaption(CString szCaption)
{
	m_szText=szCaption;
	CClientDC dc(this);
	m_SizeText= dc.GetTextExtent(m_szText,m_szText.GetLength());
	m_SizeText.cx-=7;
}


void CGuiToolButton::SethIcon(HICON hIcon)
{
	m_Icon=hIcon;
	ICONINFO bm;
	ZeroMemory(&bm, sizeof(ICONINFO));
	::GetIconInfo(m_Icon,&bm);
	m_SizeImage =CSize((BYTE)(bm.xHotspot*2),(BYTE)(bm.yHotspot*2));
	::DeleteObject(bm.hbmMask);
	::DeleteObject(bm.hbmColor);

}

void CGuiToolButton::ShowMenu()
{
	CRect rcW;
	int x,y;
	GetWindowRect(&rcW);
	
	x=rcW.left;
	y=rcW.bottom;
	
	if (m_hMenu != NULL )
	{
	   UINT m_iResMenu= ::TrackPopupMenu (m_hMenu,TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, 
		x, y, 0, GetSafeHwnd (), NULL);
		if (m_iResMenu!=0)
		{
			CWnd* pParent= GetParent();
			pParent->SendMessage (	WM_COMMAND,
									MAKEWPARAM (GetDlgCtrlID (), BN_CLICKED),
									(LPARAM) m_hWnd);
		}
		
	}
	else
		return;
	Invalidate ();
	UpdateWindow ();
	ReleaseCapture();
	
}
