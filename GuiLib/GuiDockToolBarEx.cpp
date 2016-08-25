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
#include "guidocktoolbarex.h"
#include "GuiDrawLayer.h"
#include "GuiMDIFrame.h"
#include "GuiFrameWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CDockButton

CDockButton::CDockButton()
{
	m_bMouseOver=FALSE;
	m_hIcon=NULL;
}

CDockButton::~CDockButton()
{
}


BEGIN_MESSAGE_MAP(CDockButton, CWnd)
	//{{AFX_MSG_MAP(CDockButton)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDockButton message handlers

BOOL CDockButton::Create(LPCTSTR lpszWindowName,DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,HWND hWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	m_Caption=lpszWindowName;
	m_nDockBarAling=nID;
	m_hWnd=hWnd;
	return CWnd::Create(NULL,lpszWindowName, dwStyle |WS_CLIPSIBLINGS|WS_CLIPCHILDREN, rect, pParentWnd, nID+(int)m_hWnd);

}

int CDockButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here

	return 0;
}

void CDockButton::SetIconBtn(HICON hIcon)
{
	m_hIcon=hIcon;
	m_szBtn=GuiDrawLayer::GetSizeIcon(m_hIcon);
}

void CDockButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bMouseOver) return;

	if (!IsTopParentActive() || !GetTopLevelParent()->IsWindowEnabled())
		return;
	CRect m_rect;
	GetClientRect(m_rect);
	if (m_rect.PtInRect(point))
	{

		CGuiControlBar* m_tb=GetBar(m_hWnd);
		if 	((m_tb->IsVisible() && m_tb->IsAutoHide()) )
		{
			
			m_tb->ScrollOff();
			GetParentFrame()->ShowControlBar(m_tb, FALSE, FALSE);
		}
		else
		{
			if 	(!m_tb->IsVisible())
			{
				CGuiControlBar* m_tb1=IsControlVisible(m_tb);
				if (m_tb1!= NULL)
				{
					if (m_tb1 != m_tb)
					{
						GetParentFrame()->ShowControlBar(m_tb1, FALSE, TRUE);
					}
				}
				m_tb->ScrollOn();
				m_bMouseOver=TRUE;  //numero de ventana a activar
				SetTimer(1,500,0);
			}
		}
	}


	CWnd::OnMouseMove(nFlags, point);
}


CGuiControlBar* CDockButton::IsControlVisible(CGuiControlBar* m_Bar)
{
	CGuiMDIFrame* pB;
	CGuiFrameWnd* pB1;
	CDockButton* pBtn;
	BOOL isMDI=FALSE;
			
	if (GetParentFrame()->IsKindOf(RUNTIME_CLASS(CGuiMDIFrame)))
		isMDI=TRUE;

	if (isMDI)
		 pB=(CGuiMDIFrame*)GetParentFrame();
	else 
		 pB1= (CGuiFrameWnd*)GetParentFrame();

	int nSize=isMDI==TRUE? pB->m_dockHideBottom.m_ArrayButton.GetSize() : pB1->m_dockHideBottom.m_ArrayButton.GetSize() ;
	for(int i=0; i < nSize; i++)
	{

		if (isMDI==TRUE)
			pBtn= (CDockButton*) pB->m_dockHideBottom.m_ArrayButton[i];
		else
			pBtn= (CDockButton*) pB1->m_dockHideBottom.m_ArrayButton[i];

		CGuiControlBar* pBar= GetBar(pBtn->m_hWnd);
		if(pBar == m_Bar) continue;
		if (pBar->IsWindowVisible())
			return pBar;
	}

	nSize=(isMDI==TRUE) ? pB->m_dockHideLeft.m_ArrayButton.GetSize(): pB1->m_dockHideLeft.m_ArrayButton.GetSize();
	for( i=0; i < nSize; i++)
	{
		if (isMDI==TRUE)
			pBtn= (CDockButton*) pB->m_dockHideLeft.m_ArrayButton[i];
		else
			pBtn= (CDockButton*) pB1->m_dockHideLeft.m_ArrayButton[i];

		CGuiControlBar* pBar= GetBar(pBtn->m_hWnd);
		if(pBar == m_Bar) continue;
		if(pBar->IsWindowVisible())
			return pBar;
	}

	nSize=(isMDI==TRUE) ? pB->m_dockHideRight.m_ArrayButton.GetSize() : pB1->m_dockHideRight.m_ArrayButton.GetSize();
	for( i=0; i < nSize; i++)
	{
		if (isMDI==TRUE)
			pBtn=(CDockButton*) pB->m_dockHideRight.m_ArrayButton[i] ;
		else
			pBtn=(CDockButton*) pB1->m_dockHideRight.m_ArrayButton[i];

		CGuiControlBar* pBar= GetBar(pBtn->m_hWnd);
		if(pBar == m_Bar) continue;
		if (pBar->IsWindowVisible())
			return pBar;
	}

	nSize=(isMDI==TRUE) ? pB->m_dockHideTop.m_ArrayButton.GetSize() : pB1->m_dockHideTop.m_ArrayButton.GetSize();
	for( i=0; i < nSize; i++)
	{
		if (isMDI==TRUE)
			pBtn= (CDockButton*) pB->m_dockHideTop.m_ArrayButton[i];
		else
			pBtn= (CDockButton*)pB1->m_dockHideTop.m_ArrayButton[i];

		CGuiControlBar* pBar= GetBar(pBtn->m_hWnd);
		if(pBar == m_Bar) continue;
		if (pBar->IsWindowVisible())
			return pBar;
	}

	return NULL;

}

CGuiControlBar* CDockButton::GetBar(HWND hWnd)
{
	POSITION pos = GetParentFrame()->m_listControlBars.GetHeadPosition();
	while (pos)
	{
		CControlBar* pBar =
			(CControlBar*)GetParentFrame()->m_listControlBars.GetNext(pos);
		ASSERT_VALID(pBar);
		if (pBar->m_hWnd == hWnd)
		   return (CGuiControlBar *)pBar;
	}
	return NULL;
}

void CDockButton::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBrush cb;
	COLORREF m_clrBorder=GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style);
	COLORREF m_clrFace=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	CPen cp(PS_SOLID,1,m_clrFace);
	CPen* cpold=dc.SelectObject(&cp);
	CRect m_rect;
	GetClientRect(m_rect);
	cb.CreateSolidBrush(m_clrFace);
	if (GuiDrawLayer::m_Style== GUISTYLE_XP)
		dc.FillRect(m_rect,&cb);
	else
	{
		CGradient M(CSize(m_rect.Width(),m_rect.Height()));
		if (m_nDockBarAling ==AFX_IDW_DOCKBAR_LEFT || m_nDockBarAling ==AFX_IDW_DOCKBAR_RIGHT)
			M.PrepareCaptionVert(&dc,GuiDrawLayer::m_Style);
		else
			M.PrepareCaption(&dc,GuiDrawLayer::m_Style);
		M.Draw(&dc,m_rect.left,m_rect.top,0,0,m_rect.Width(),m_rect.Height(),SRCCOPY);
	}

	dc.Draw3dRect(m_rect,m_clrBorder,m_clrBorder);
	GuiDrawLayer::DrawIcon(&dc,CPoint(m_rect.left+2,m_rect.top+2),m_szBtn,m_hIcon);

	switch(m_nDockBarAling)
	{


		case AFX_IDW_DOCKBAR_TOP:
			dc.MoveTo(m_rect.left,m_rect.top);
			dc.LineTo(m_rect.right,m_rect.top);
			if(m_hIcon != NULL)
				m_rect.left+=m_szBtn.cx+4;
			DrawTextHorz(&dc,m_rect);
			break;
		case AFX_IDW_DOCKBAR_LEFT:
			dc.MoveTo(m_rect.left,m_rect.top);
			dc.LineTo(m_rect.left,m_rect.bottom);
			if(m_hIcon != NULL)
				m_rect.top+=m_szBtn.cy+4;
			DrawTextVert(&dc,m_rect);
			break;
		case AFX_IDW_DOCKBAR_RIGHT:
			dc.MoveTo(m_rect.right-1,m_rect.top);
			dc.LineTo(m_rect.right-1,m_rect.bottom);
			if(m_hIcon != NULL)
				m_rect.top+=m_szBtn.cy+4;
			DrawTextVert(&dc,m_rect);
			break;
		case AFX_IDW_DOCKBAR_BOTTOM:
			dc.MoveTo(m_rect.left,m_rect.bottom-1);
			dc.LineTo(m_rect.right,m_rect.bottom-1);
			if(m_hIcon != NULL)
				m_rect.left+=m_szBtn.cx+4;
			DrawTextHorz(&dc,m_rect);
			break;
	}
	dc.SelectObject(cpold);

}

void CDockButton::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bMouseOver) return;
	CRect m_rc;
	CPoint pt(GetMessagePos());
	CRect m_rect;
	GetClientRect(m_rect);
	CPoint ptB=pt;
	ScreenToClient(&pt);
	CGuiControlBar* m_tb=GetBar(m_hWnd);
	m_tb->GetWindowRect(&m_rc);
	if (m_rc.PtInRect(ptB)) return;
	if (m_rect.PtInRect(pt)) return;
	if (m_tb->IsTracking()) return;
	if (!m_rect.PtInRect(pt))
	{
		m_bMouseOver=0;
		KillTimer(1);
		CGuiControlBar* m_tb1=IsControlVisible(m_tb);
		if (!m_tb1)
			m_tb->ScrollOff();
		//aqui se debe ocultar la ventana auto hide
	}

	CWnd::OnTimer(nIDEvent);
}

void CDockButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}

void CDockButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
}

void CDockButton::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here

}


void CDockButton::DrawTextHorz(CDC* pDC, CRect m_rect)
{
	pDC->SetBkMode(TRANSPARENT);
	CFont* pOldFont = pDC->SelectObject(&m_fontHorzMenu);
	pDC->DrawText(m_Caption, m_rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->SelectObject(pOldFont);
}


void CDockButton::DrawTextVert(CDC* pDC, CRect m_rect)
{
	COLORREF clr = ::GetSysColor(COLOR_MENUTEXT);
	pDC->SetTextColor(clr);

	// fixed for WinNT. *****fixed by Simon, thanks!*****
	int iGraphicsMode = ::GetGraphicsMode(pDC->m_hDC);
	::SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	pDC->SetBkMode(TRANSPARENT);
	CFont* pOldFont = pDC->SelectObject(&m_fontVertMenu);
	// I know precise text size
	CSize m_sizeHorz;
	CSize m_sizeCad=pDC->GetTextExtent(m_Caption);
	m_sizeHorz.cx = ( m_sizeCad.cx + CXTEXTMARGIN*2)+8;
	m_sizeHorz.cy = (_cyHorzFont + _cyTextMargin*2)+1;
	CRect rcString = CRect(
	CPoint(m_rect.right - _cyTextMargin, m_rect.top + CXTEXTMARGIN), m_sizeHorz);

	pDC->DrawText(m_Caption, rcString,
		DT_SINGLELINE | DT_NOCLIP | DT_NOPREFIX);// don't forget DT_NOCLIP
	pDC->SelectObject(pOldFont);

	// CDC::DrawText is poor, so we have to draw vertical line by ourselves
	::SetGraphicsMode( pDC->m_hDC, iGraphicsMode );
}

/////////////////////////////////////////////////////////////////////////////
// CGuiDockToolBarEx


CGuiDockToolBarEx::CGuiDockToolBarEx()
{
	m_clrface=GuiDrawLayer::GetRGBColorTabs();
	m_Size=24;
	n_numBars=0;
	m_ArrayButton.RemoveAll();

}

CGuiDockToolBarEx::~CGuiDockToolBarEx()
{
	m_ArrayButton.RemoveAll();
}

void CGuiDockToolBarEx::OnDestroy()
{
	// Libera la memoria
    for( int i=0; i<n_numBars; i++ )
    {
    CDockButton *pBtn = (CDockButton*)m_ArrayButton.GetAt(i);
    if( pBtn )
        delete pBtn;
    }
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
}



BEGIN_MESSAGE_MAP(CGuiDockToolBarEx, CControlBar)
	//{{AFX_MSG_MAP(CGuiDockToolBarEx)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGuiDockToolBarEx message handlers

BOOL CGuiDockToolBarEx::Create(CWnd* pParentWnd,DWORD dwAling)
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT ( dwAling & CBRS_ALIGN_ANY);
	SetBarStyle (dwAling);
	DWORD dwStyle = CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;
	if (pParentWnd->GetStyle() & WS_THICKFRAME)
		dwStyle |= SBARS_SIZEGRIP;
	dwStyle |= WS_CHILD;
	return CControlBar::Create(0,0,dwStyle,	CRect(0,0,0,0),pParentWnd,0x9999);
}

int CGuiDockToolBarEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	if (!InitGlobalFont())
	   return -1;
	return 0;
}

BOOL CGuiDockToolBarEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CBrush cbr;
	cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	CRect m_rect;
	GetClientRect(m_rect);
	pDC->FillRect(m_rect,&cbr);
	return TRUE;

}




void CGuiDockToolBarEx::CalcButton()
{
	int nPos=20;
	CRect rcCli;
	GetClientRect(rcCli);
	CClientDC dc(this);
	CRect m_Arect;
	for (int iCont=0; iCont< n_numBars;iCont++)
	{
		CDockButton* ct=(CDockButton*) m_ArrayButton[iCont];
		CSize m_sChar=dc.GetTextExtent(ct->GetString());
		m_Arect.SetRectEmpty();
		CSize szBtn=ct->GetSizeIconBtn();

		if (ct->GetAling() == AFX_IDW_DOCKBAR_TOP ||
			ct->GetAling() == AFX_IDW_DOCKBAR_BOTTOM)
		{
			m_Arect.left=nPos+4;
			m_Arect.right+= nPos+m_sChar.cx+4;
			m_Arect.right+= szBtn.cy+6;
			m_Arect.top=AFX_IDW_DOCKBAR_TOP?rcCli.top:rcCli.top+4;
			m_Arect.bottom=AFX_IDW_DOCKBAR_TOP? rcCli.bottom-2:rcCli.Width()+4;
			nPos+=m_Arect.Width();
			nPos+=2;
		}
		else
		{

			m_Arect.top=nPos+4;
			m_Arect.bottom+= nPos+m_sChar.cx+4;
			m_Arect.bottom+= szBtn.cx+6;
			m_Arect.right+=AFX_IDW_DOCKBAR_LEFT?rcCli.left+22: rcCli.left+22;
			m_Arect.left+=AFX_IDW_DOCKBAR_LEFT?0:m_Arect.right;
			nPos+=m_Arect.Height();
			nPos+=8;


		}
		ct->SetRect(m_Arect);
		ct->MoveWindow(m_Arect,TRUE);
		//ct->UpdateWindow();
	}

}

void CGuiDockToolBarEx::AddToolBars(CGuiControlBar* m_ctrlBars)
{
	CString m_string;
	m_ctrlBars->GetWindowText(m_string);
	m_ArrayButton.SetAtGrow(n_numBars,
		new CDockButton());
	if (!((CDockButton *)m_ArrayButton[n_numBars])->Create(m_string,WS_VISIBLE,CRect(0,0,0,0),this,m_ctrlBars->GetDlgID(),m_ctrlBars->m_hWnd))
		return ;
	((CDockButton *)m_ArrayButton[n_numBars])->SetIconBtn(m_ctrlBars->GetIcon());
	n_numBars++;
	CalcButton();
	UpdateBars();
	Invalidate();
	UpdateWindow();
}

void CGuiDockToolBarEx::DeleteToolBars(CGuiControlBar* m_ctrlBars)
{
	for (int i=0; i < n_numBars; i++)
	{

		CGuiControlBar *m_tb=(CGuiControlBar *) ((CDockButton *)m_ArrayButton[i])->GetBar(((CDockButton *)m_ArrayButton[i])->GethWnd());
		if (m_tb == m_ctrlBars)
			break;
	}

	CDockButton *pBtn = (CDockButton*)m_ArrayButton.GetAt(i);
    if( pBtn )
        delete pBtn;
	m_ArrayButton.RemoveAt(i);
	n_numBars--;
	UpdateBars();
	CalcButton();
	Invalidate();
	UpdateWindow();
}

void CGuiDockToolBarEx::UpdateBars()
{
	DWORD dwstyle = GetBarStyle();
	if (m_ArrayButton.GetSize() > 0)
		ShowWindow(SW_SHOW);
	else
		ShowWindow(SW_HIDE);


}

void CGuiDockToolBarEx::OnSysColorChange()
{
	m_clrface=GuiDrawLayer::m_Style!= GUISTYLE_XP?GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style): GuiDrawLayer::GetRGBColorTabs();
	CControlBar::OnSysColorChange();
}

void CGuiDockToolBarEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect m_rect;
	GetClientRect(m_rect);
	CBrush cbr;
	m_clrface=GuiDrawLayer::m_Style!= GUISTYLE_XP?GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style): GuiDrawLayer::GetRGBColorTabs();
	cbr.CreateSolidBrush(m_clrface);
	dc.FillRect(m_rect,&cbr);
	CalcButton();
	UpdateBars();
	// TODO: Add your message handler code here

	// Do not call CControlBar::OnPaint() for painting messages
}


void CGuiDockToolBarEx::OnMouseMove(UINT nFlags, CPoint point)
{

	CControlBar::OnMouseMove(nFlags, point);
}

void CGuiDockToolBarEx::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CControlBar::OnTimer(nIDEvent);
}




void CGuiDockToolBarEx::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	// TODO: Add your message handler code here and/or call default
	UpdateBars();
	CControlBar::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CGuiDockToolBarEx::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
}

CSize CGuiDockToolBarEx::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	if (bHorz)
		return CSize(32767,m_Size);
	else
		return CSize(m_Size,32767);
}


