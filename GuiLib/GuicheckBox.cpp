/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *                           (MFC extension)								*			 
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
#include "GuiCheckBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiCheckBox

CGuiCheckBox::CGuiCheckBox()
{
	m_bCheckBtn = FALSE;
	m_bPressBtn = FALSE;
	m_bOldTemp  = FALSE;
	m_clrHigh   = ::GetSysColor(COLOR_HIGHLIGHT);
	m_clrCheck  = RGB(0, 170, 170);
	m_bSelected = FALSE;
}

CGuiCheckBox::~CGuiCheckBox()
{
}

BEGIN_MESSAGE_MAP(CGuiCheckBox, CButton)
	//{{AFX_MSG_MAP(CGuiCheckBox)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiCheckBox message handlers

void CGuiCheckBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC         = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect m_rcClient(lpDrawItemStruct->rcItem);
	UINT m_State     = lpDrawItemStruct->itemState;
	CBrush cb;
	CRect m_rcTemp(m_rcClient);
	CPoint pt;
	CSize  m_Csize;
	CString m_szCaption;
	COLORREF m_Over = RGB(255, 193, 111);
	CPen cpOver(PS_SOLID, 1, RGB(255, 193, 111));
	int iMode      = pDC->SetBkMode(TRANSPARENT);
	int iExtile    = GetButtonStyle(); // obtenemos orientación del texto
	CRect m_rcText(m_rcClient);
	GetWindowText(m_szCaption);
	if (m_szCaption.GetLength() > 1)
		m_Csize= pDC->GetTextExtent(m_szCaption);

	// de acuerdo a la alineación del texto prepare la ubicación
	// del texto para Drawtex y DrawState
	
	if (m_rcClient.Height() > 13)
	{
		int Dif = m_rcClient.Height() - 13;
		Dif /= 2;
		m_rcTemp.top = Dif;
		m_rcTemp.bottom = m_rcTemp.top + 13;
	}
	if (iExtile & BS_LEFTTEXT)
	{
		m_rcTemp.left=	m_rcTemp.right - 13;
		pt = CPoint(m_rcTemp.left, m_rcTemp.top + 1);
	}
	else
	{
		m_rcTemp.right=	m_rcTemp.left + 13;
		pt = CPoint(m_rcTemp.right + 2, m_rcTemp.top + 1);
		m_rcText.left = m_rcTemp.right + 1;
	}
	
	// draw frame of checkbox
	pDC->Draw3dRect(m_rcTemp, m_clrHigh, m_clrHigh);
	m_rcTemp.DeflateRect(1, 1);
	DrawOrange(pDC, m_rcTemp);
	m_rcTemp.DeflateRect(1, 1);
	if (lpDrawItemStruct->itemState & ODS_DISABLED)
		pDC->DrawState(pt, m_Csize, m_szCaption, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
	else 
	{
		pDC->DrawText(m_szCaption, m_rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER);			   		
		if (lpDrawItemStruct->itemState & ODS_SELECTED)
		{
			if (m_bOldTemp == TRUE)
				DrawCheck(pDC, m_rcTemp);
		}
		else
		{
			if (m_bCheckBtn == TRUE && m_bPressBtn == FALSE)
				DrawCheck(pDC, m_rcTemp);
			else
			{
				if (m_bOldTemp == TRUE && m_bPressBtn == TRUE)
					DrawCheck(pDC, m_rcTemp);
			}
		}
	}
}

void CGuiCheckBox::DrawCheck(CDC* pDC, CRect m_rcTemp)
{
	int iMediaAltura = (m_rcTemp.Height()/2) - 2;
	int iMedioBox= m_rcTemp.Width()/2;
	CPen cp(PS_SOLID, 1, m_clrCheck);
	CPen *pOld = pDC->SelectObject(&cp);
	pDC->MoveTo(m_rcTemp.left + 1, m_rcTemp.top + iMediaAltura + 3);
	pDC->LineTo(m_rcTemp.left + 3, m_rcTemp.bottom - 2);
	pDC->MoveTo(m_rcTemp.left + 3, m_rcTemp.bottom - 2);
	pDC->LineTo(m_rcTemp.right - 1, m_rcTemp.top + 2);
				
	pDC->MoveTo(m_rcTemp.left + 1, m_rcTemp.top + iMediaAltura + 2);
	pDC->LineTo(m_rcTemp.left + 3, m_rcTemp.bottom - 3);
	pDC->MoveTo(m_rcTemp.left + 3, m_rcTemp.bottom - 3);
	pDC->LineTo(m_rcTemp.right - 1, m_rcTemp.top + 1);
	
	pDC->MoveTo(m_rcTemp.left + 1, m_rcTemp.top + iMediaAltura + 1);
	pDC->LineTo(m_rcTemp.left + 3, m_rcTemp.bottom - 4);
	pDC->MoveTo(m_rcTemp.left + 3, m_rcTemp.bottom - 4);
	pDC->LineTo(m_rcTemp.right - 1, m_rcTemp.top);
	pDC->SelectObject(pOld);
}

BOOL CGuiCheckBox::PreTranslateMessage(MSG* pMsg)
{
	return CButton::PreTranslateMessage(pMsg);
}

void CGuiCheckBox::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}
	
BOOL CGuiCheckBox::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
}

int CGuiCheckBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CGuiCheckBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CButton::OnLButtonDown(nFlags, point);
	m_bPressBtn = TRUE;
	m_bOldTemp = m_bCheckBtn;
	Invalidate();
	UpdateWindow();
	KillTimer(1);
	SetTimer(1, 10, NULL);
}

void CGuiCheckBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CButton::OnLButtonUp(nFlags, point);
	CRect m_rect;
	GetClientRect(&m_rect);
	if (m_rect.PtInRect(point))
	{
		if (m_bCheckBtn == TRUE)
			m_bCheckBtn = FALSE;
		else 
			m_bCheckBtn = TRUE;
		m_bOldTemp = m_bCheckBtn;
		m_bPressBtn = FALSE;
		m_bSelected =FALSE;	
		KillTimer(1);
		SetTimer(1, 100, NULL);
		
		Invalidate();
		UpdateWindow();
	}
}


void CGuiCheckBox::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRect m_rect;
	GetClientRect(&m_rect);
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	if (!m_rect.PtInRect(pt))
	{
		m_bPressBtn = TRUE;
		m_bSelected = FALSE;

		Invalidate();
		UpdateWindow();
		KillTimer(1);
	}	
	CButton::OnTimer(nIDEvent);
}

void CGuiCheckBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect m_rect;
	GetClientRect(&m_rect);
	if (m_bSelected == TRUE)
		return;
	if (m_rect.PtInRect(point))
	{
		m_bSelected =TRUE;
		Invalidate();
		UpdateWindow();
		SetTimer(1, 100, NULL);
	}
	CButton::OnMouseMove(nFlags, point);
}


void CGuiCheckBox::DrawOrange(CDC* pDC, CRect m_rcTemp)
{
	if (m_bSelected== TRUE)
	{
		for (int i = 0; i < 2; i++)
		{
			COLORREF m_Over = RGB(255, 193+ (i + 10), 111+ (i + 10));
			pDC->Draw3dRect(m_rcTemp, m_Over, m_Over);
			m_rcTemp.DeflateRect(1, 1);
		}
		m_rcTemp.InflateRect(2, 2);
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 2,::GetSysColor(COLOR_3DHIGHLIGHT));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 3, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 4, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 5, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 6, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 2, m_rcTemp.top, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 3, m_rcTemp.top, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 4, m_rcTemp.top, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left + 5, m_rcTemp.top, RGB(255, 220, 185));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top, RGB(254, 225, 158));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 1, RGB(255, 255, 255));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 2, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 3, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 4, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 5, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 6, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 7, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 8, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 9, RGB(255, 243, 217));
		
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top, RGB(254, 255, 255));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 2, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 3, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 4, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 5, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 6, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left + 7, m_rcTemp.top, RGB(255, 243, 217));
		pDC->SetPixel(m_rcTemp.left, m_rcTemp.top + 1, RGB(254, 255, 255));
		pDC->SetPixel(m_rcTemp.left + 1, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 2, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 3, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 4, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 5, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 6, m_rcTemp.top + 1, RGB(254, 220, 139));
		pDC->SetPixel(m_rcTemp.left + 7, m_rcTemp.top + 1, RGB(254, 220, 139));
	}
	else
	{ 
		CBrush cbSelec;
		cbSelec.CreateSysColorBrush(COLOR_3DHILIGHT);
		pDC->FillRect(m_rcTemp, &cbSelec);
	}
}
