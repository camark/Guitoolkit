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
#include "GuiBaseTab.h"
#include "GuiWorkTab.h"
#include "GuiToolButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#define ID_WTABSPIN		501
#define ID_SCROLLWINDOW 0x9666

#define  SPACE_TAB		4
#define  DEFAULT_FLAT	18

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

#define MIN_SCROLL ::GetSystemMetrics(SM_CXHSCROLL)*2


#define SCROLLLEFT  0x889
#define SCROLLRIGHT 0x890



CGuiWorkTab::CGuiWorkTab()
{
	SetStyle(CGuiTabWnd::SHADOW);
	m_cfont.CreateFont(14, 0, 0, 0, 400, 0, 0, 0, 0, 1, 2, 1, 34, _T("Arial"));
	m_deplaza = 0;
	m_btndesplaza.SetRectEmpty();
	bIniciaArrastre = FALSE;
	m_EnableL = FALSE;
	m_EnableR = FALSE;
}

CGuiWorkTab::~CGuiWorkTab()
{
}


BEGIN_MESSAGE_MAP(CGuiWorkTab, CGuiTabWnd)
  ON_WM_HSCROLL()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEMOVE()
  ON_WM_SETCURSOR()
  ON_WM_SYSCOLORCHANGE()
  ON_COMMAND(SCROLLLEFT, OnSpiNiz)
  ON_COMMAND(SCROLLRIGHT, OnSpiNde)	
  	ON_WM_PAINT()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CGuiWorkTab::PintaSeparador(CDC* dc)
{
	CRect m_rClient = m_rectTab;
	// se pinta el boton de desplazamiento
	if (m_btndesplaza.IsRectNull())
	{
		m_rClient.left    = m_rClient.Width()/2;	
		m_rClient.top    -= 3;
		m_rClient.left   -= 5;
		m_rClient.right   = m_rClient.left + 5;	
		m_rClient.bottom -= 1;
		m_btndesplaza     = m_rClient;
		m_scroll.SetWindowPos(NULL, m_btndesplaza.right,
			m_rectTab.top, m_rectTab.right- (m_rClient.left + 5), m_rectTab.Height() - 1,
			SWP_NOACTIVATE | SWP_NOCOPYBITS);	        

		m_scroll.Invalidate();
		m_scroll.UpdateWindow();

		return;
	}
	else
	{
		CRect rcCli;
		GetClientRect(&rcCli);
		if (m_btndesplaza.left + 40 > rcCli.right)
		{
			m_btndesplaza.left=	rcCli.right - 40;
			m_btndesplaza.right = m_btndesplaza.left + 5;
		}
		m_btndesplaza.top = m_rectTab.top;
		m_btndesplaza.bottom = m_rectTab.bottom;
		m_rClient = m_btndesplaza;
	}
	if (!bIniciaArrastre)
	{
		dc->Draw3dRect(m_rClient, ::GetSysColor(BLACK_PEN),
			::GetSysColor(COLOR_BTNHIGHLIGHT));
		m_rClient.DeflateRect(1, 1);
		dc->Draw3dRect(m_rClient, ::GetSysColor(COLOR_BTNHIGHLIGHT),
			::GetSysColor(COLOR_BTNSHADOW));
	}
}

void CGuiWorkTab::OnSpiNiz()
{
	if (m_EnableL == TRUE)
	{
		m_PresLeft   = TRUE;
		m_PresRight  = FALSE;
		m_deplaza   += 10;
		CClientDC dc(this);
		Drawtabs(&dc);
	}
}
void CGuiWorkTab::OnSpiNde()
{
	if (m_EnableR == TRUE)
	{
		m_PresLeft = FALSE;
		m_PresRight = TRUE;
		m_deplaza -= 10; 	
		CClientDC dc(this);
		Drawtabs(&dc);	
	}
}


void CGuiWorkTab::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CBrush cbr;
	CRect m_rectDraw;
	cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorXP());
	
	GetClientRect(m_rectCliente);
	m_rectTab = m_rectCliente;
	m_rectDraw = m_rectCliente;
	
	if (m_alnTab == ALN_BOTTOM)
		m_rectDraw.bottom = m_rectCliente.bottom- (m_sizeImag.cy + SPACE_TAB + 2);	
	
	CRect rc = m_rectDraw;
	rc.top += 1;
	rc.bottom = rc.top + 1;
	dc.Draw3dRect(rc, GuiDrawLayer::GetRGBColorFace(m_StyleDisplay), GuiDrawLayer::GetRGBColorFace(m_StyleDisplay));
	
	if (m_alnTab == ALN_BOTTOM)
	{
		m_rectCliente.bottom = m_rectCliente.bottom- (DEFAULT_FLAT);
		m_rectTab.top = m_rectCliente.bottom + 2;
	}
	cbr.DeleteObject();
	Drawtabs(&dc);
}

void CGuiWorkTab::Drawtabs(CDC* dc)
{
	int m_StrPos      = 0;
	BOOL m_ViewAlltab = TRUE;
	CRect m_rClient;
	CBrush cbr;
	CPen cp(PS_SOLID, 1,::GetSysColor(COLOR_BTNSHADOW));
	int m_ianchoScroll=::GetSystemMetrics(SM_CXHSCROLL) * 2;
	m_EnableR = TRUE;
	m_EnableL = TRUE;
	cbr.CreateSolidBrush(m_wd.GetRGBColorXP());
	GetClientRect(m_rClient);
	CRect rectT = m_rectTab;
	rectT.right = m_btndesplaza.left;
	rectT.right += 4;
	
	if (!::IsWindow(m_toolBtn[0].GetSafeHwnd()))
	{
		CRect r = m_rectTab;
		r.right = r.left + 35;
		r.top += 1;
		// r.bottom-=1;
		if (!m_img.Create(IDB_GUI_DOCKBAR, 9, 11, RGB(255, 0, 255)))
		{
			TRACE0("error imagelist");
		}
		
		m_toolBtn[0].Create(_T(""), 
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
			CRect(0, 0, 0, 0), this, SCROLLLEFT);
		m_toolBtn[0].SetToolTip(_T("Scroll Left"));
		m_toolBtn[0].SethIcon(m_img.ExtractIcon(4));
		m_toolBtn[0].ShowDark(FALSE);
		m_toolBtn[0].SetWait(1000);
		m_toolBtn[1].Create(_T(""), 
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
			CRect(0, 0, 0, 0), this, SCROLLRIGHT);
		m_toolBtn[1].SetToolTip(_T("Scroll Right"));
		m_toolBtn[1].SethIcon(m_img.ExtractIcon(2));
		m_toolBtn[1].ShowDark(FALSE);
		m_toolBtn[1].SetWait(1000);
	}
	

	if(m_StyleDisplay== GUISTYLE_2003)
	{
		CGradient M(CSize(rectT.Width(),rectT.Height()+1));	
		M.PrepareReverseVertTab(dc,m_StyleDisplay);
		M.Draw(dc,0,rectT.bottom-rectT.Height(),0,0,rectT.Width(),rectT.Height(),SRCCOPY);	
		dc->LineTo(rectT.left, rectT.bottom+3);
		dc->MoveTo(rectT.right, rectT.bottom+3);
		m_toolBtn[0].StyleDispl(m_StyleDisplay,FALSE);
		m_toolBtn[1].StyleDispl(m_StyleDisplay,FALSE);
	}	
	else
	{
		dc->FillRect(rectT, &cbr);
		m_toolBtn[0].SetColor(GuiDrawLayer::GetRGBColorTabs());
		m_toolBtn[1].SetColor(GuiDrawLayer::GetRGBColorTabs());

	}
	CPen* pOldPenGlobal = dc->SelectObject(&cp);
	dc->MoveTo(m_rectTab.left, m_rectTab.top);
	dc->LineTo(m_btndesplaza.right + 1, m_rectTab.top);
	dc->Draw3dRect(m_rClient, ::GetSysColor(COLOR_BTNSHADOW),
		::GetSysColor(COLOR_BTNHIGHLIGHT));
	
	if (!::IsWindow(m_scroll.GetSafeHwnd()))
	{
		m_scroll.Create(WS_CHILD | WS_VISIBLE | SBS_HORZ, m_rectTab, this, (UINT) -1/*ID_SCROLLWINDOW*/);
	}
	
	CSize szBtn_1 = m_toolBtn[0].GetSizeButton();
	CSize szBtn_2 = m_toolBtn[0].GetSizeButton();
	
	CRect rcSpin = CRect(0, 0, szBtn_1.cx + szBtn_2.cx + 2, szBtn_1.cy + szBtn_2.cy);
	m_StrPos = rcSpin.Width();
	if ((m_btndesplaza.left < rcSpin.right) && ! m_btndesplaza.IsRectEmpty())
	{
		m_btndesplaza.left = rcSpin.right + 5;
		m_btndesplaza.right = m_btndesplaza.left + 5;
	}

	PintaSeparador(dc);
	
	int m_Space = 8;
	int m_Pos   = 10;
	int m_right = m_StrPos;
	if (m_iMinValRec - 26 > m_btndesplaza.left) // No existe suficioente espacio para los tabs
	{
		m_ViewAlltab = FALSE;
		// m_spin.EnableScrollBar();
		if (m_PresLeft == TRUE)
			m_right += m_deplaza;
		if (m_PresRight == TRUE)
			m_right += m_deplaza;
		if (m_deplaza == 0)
		{
			m_EnableL = FALSE;
			m_EnableR = TRUE;
			//m_spin.EnableScrollBar(ESB_DISABLE_LTUP);
		}
		if ((m_iMinValRec + m_deplaza) - 26 <= m_btndesplaza.left)
		{
			//m_spin.EnableScrollBar(ESB_DISABLE_RTDN);
			m_EnableR = FALSE;
			m_EnableL = TRUE;
		}
	}
	else
	{
		m_EnableL = FALSE;
		m_EnableR = FALSE;
		// m_spin.EnableScrollBar(ESB_DISABLE_BOTH);
		m_ViewAlltab = TRUE;
		m_deplaza = 0;
	}
	CRect rectScroll; 
	CRgn reg;	
	CRect rectRecorte;
	rectRecorte.left = m_rectTab.left + m_ianchoScroll;
	rectRecorte.top = m_rectTab.top;
	rectRecorte.bottom = m_rectTab.bottom;
	rectRecorte.right = m_btndesplaza.left;
	reg.CreateRectRgnIndirect(rectRecorte);
	dc->SelectClipRgn(&reg);
	for (int iCont = 0; iCont < m_Numtabs; iCont++)
	{	
		//;
		CGuiTab* ctb = (CGuiTab*)m_pArray[iCont];
		CRect mrt = ctb->rect;		
		int ancho = mrt.Width();
		mrt.left = m_right;
		mrt.right = mrt.left + ancho;
		CPoint Coor[4];
		// dibujar la hoja seleccionada
		if (iCont == 0)
		{
			dc->MoveTo(mrt.left, mrt.top);
			dc->LineTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
			dc->MoveTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
			dc->LineTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
			dc->MoveTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
			if (m_iSelectTab ==iCont)
				dc->LineTo(mrt.right - 2, mrt.top + 2);
			else
				dc->LineTo((mrt.right) - 3, mrt.top+ (m_rectTab.Height()/2));
			
			m_right = mrt.right;
		}
		else
		{
			// Se dibuja la hoja siguiente a la seleccionada
			// no se dibuja toda la diagonal y no es la ultima hoja
			
			if (iCont - 1 == m_iSelectTab) 
			{	
				dc->MoveTo(mrt.left+ (m_rectTab.Height()/4) + 1, mrt.top + m_rectTab.Height()/2);
				dc->LineTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
				dc->MoveTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
				dc->LineTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
				dc->MoveTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
				if (iCont == m_Numtabs - 1)
					dc->LineTo((mrt.right - 2), mrt.top + 2);
				else
					dc->LineTo((mrt.right) - 3, mrt.top+ (m_rectTab.Height()/2));
			}
			else
			{
				dc->MoveTo(mrt.left, mrt.top);
				dc->LineTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
				dc->MoveTo((mrt.left) + m_rectTab.Height()/2, mrt.bottom - 1);
				dc->LineTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
				dc->MoveTo((mrt.right) - m_rectTab.Height()/2, mrt.bottom - 1);
				if (iCont == m_iSelectTab || iCont == m_Numtabs - 1)
					dc->LineTo((mrt.right - 2), mrt.top + 2);
				else
					dc->LineTo((mrt.right) - 3, mrt.top + 3+ (m_rectTab.Height()/2));
			}
			m_right = mrt.right;
		}
		if (iCont == m_iSelectTab)
		{
			Coor[0].x = mrt.left;
			Coor[0].y = mrt.top;
			Coor[1].x = (mrt.left) + m_rectTab.Height()/2;
			Coor[1].y = mrt.bottom - 1;
			Coor[2].x = (mrt.right) - m_rectTab.Height()/2; 
			Coor[2].y = mrt.bottom - 1;
			Coor[3].x = (mrt.right - 1);
			Coor[3].y = mrt.top + 3;
			dc->Polygon(Coor, 4);	
			dc->SelectStockObject(WHITE_PEN);
			dc->SelectObject(&cp);
		}
		
		CFont* m_fontOld = dc->SelectObject(&m_cfont);
		dc->SetBkMode(TRANSPARENT);
		CRect mrtt = mrt;
		mrtt.top += 2;
		dc->DrawText(ctb->lpMsg, mrtt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ctb->rect = mrt;
		m_right -= (m_rectTab.Height()/2);	
		if (!bIniciaArrastre)
		{
			CRect m_rectCli;
			GetClientRect(m_rectCli);
			if (m_btndesplaza.left <m_rectCli.left + rcSpin.left + 1)
			{
				m_btndesplaza.left = m_rectCli.left + rcSpin.left + 5;
				m_btndesplaza.right = m_btndesplaza.left + 5;
				PintaSeparador(dc);
			}
			m_scroll.SetWindowPos(NULL, 
				m_btndesplaza.right, m_rectTab.top, m_rectCli.right - (m_btndesplaza.left + 5), 
				m_rectTab.Height() - 1, SWP_NOACTIVATE | SWP_NOCOPYBITS);	        
			m_scroll.Invalidate();
			m_scroll.UpdateWindow();
			CSize szBtn = m_toolBtn[0].GetSizeButton();
			m_toolBtn[0].MoveWindow(m_rectTab.left + 1, 
				m_rectTab.top + 1, szBtn.cx, m_rectTab.Height() - 2);
			CSize szBtn1 = m_toolBtn[1].GetSizeButton();
			m_toolBtn[1].MoveWindow(m_rectTab.left + szBtn.cx + 1, m_rectTab.top + 1, 
				szBtn1.cx, m_rectTab.Height() - 2);
		}

		dc->SelectObject(m_fontOld);
	}

	dc->SelectObject(pOldPenGlobal);
	cbr.DeleteObject();
	dc->SelectClipRgn(NULL);
	m_toolBtn[0].Invalidate();
    m_toolBtn[0].UpdateWindow();	
	m_toolBtn[1].Invalidate();
    m_toolBtn[1].UpdateWindow();	
}


void CGuiWorkTab::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
	
	if (pScrollBar->GetSafeHwnd() == m_scroll.GetSafeHwnd())
	{
		CGuiTab* ct = (CGuiTab*) m_pArray[m_iSelectTab];
		CWnd* ViewAc = ct->pParent;
		ViewAc->SendMessage(WM_HSCROLL, MAKEWPARAM(nSBCode, nPos));  
		SizeScroll();
		
		return;
	}

    CClientDC dc(this);
	Drawtabs(&dc);
}


BOOL CGuiWorkTab::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CPoint ptCurPos;
	GetCursorPos(&ptCurPos);
	ScreenToClient(&ptCurPos);
	
	if (m_btndesplaza.PtInRect(ptCurPos))
	{
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		return TRUE;
	}
	
	return CGuiTabWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CGuiWorkTab::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_btndesplaza.PtInRect(point) && !bIniciaArrastre)
	{
		bIniciaArrastre = TRUE;		
		SetCapture();
		InvalidateRect(m_btndesplaza, TRUE);
	}
	else
	{
		CGuiTabWnd::OnLButtonDown(nFlags, point);
		CGuiTab* ct = (CGuiTab*) m_pArray[m_iSelectTab];
		CWnd* ViewAc = ct->pParent;
		int rangmin, rangMax;
		ViewAc->GetScrollRange(SB_HORZ, &rangmin, &rangMax);
		m_scroll.SetScrollRange(rangmin, rangMax);
		m_scroll.SetScrollPos(ViewAc->GetScrollPos(SB_HORZ));
	}
}

void CGuiWorkTab::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (bIniciaArrastre == TRUE)
	{
		bIniciaArrastre = FALSE;
		int iDiferencia = m_rectTab.right - 31;
		if (point.x < m_rectTab.left + 31)
			point.x = m_rectTab.left + 31;
		if (point.x > iDiferencia)
			point.x= iDiferencia;
		m_btndesplaza.left = point.x;
		m_btndesplaza.right = m_btndesplaza.left + 5;
		ReleaseCapture();	
		Invalidate();
		UpdateWindow();
	}
	
	CGuiTabWnd::OnLButtonUp(nFlags, point);
}

void CGuiWorkTab::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect m_rectCli;
	GetClientRect(m_rectCli);
    if (bIniciaArrastre == TRUE)
    {
		int iDiferencia = m_rectCli.right - 31;
		if (point.x < m_rectTab.left + 31)
			point.x = m_rectTab.left + 31;
		if (point.x > iDiferencia)
			point.x= iDiferencia;
		m_scroll.SetWindowPos(NULL, point.x, 
			m_rectTab.top, m_rectCli.right - point.x, m_rectTab.Height() - 1,
			SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOCOPYBITS);	        
		m_scroll.Invalidate();
		m_scroll.UpdateWindow();
		m_btndesplaza.left = point.x;
		m_rectCli = m_btndesplaza;
		m_rectCli.left -= 5;
		InvalidateRect(m_btndesplaza, TRUE);
		UpdateWindow();
	}
	else
	{
		CGuiTabWnd::OnMouseMove(nFlags, point);
	}
}

void CGuiWorkTab::OnSysColorChange() 
{
	CGuiTabWnd::OnSysColorChange();
	
	//m_toolBtn[0].StyleDispl(GuiDrawLayer::m_Style);
	//m_toolBtn[1].StyleDispl(GuiDrawLayer::m_Style);
	
	m_toolBtn[0].SetColor(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));	
	m_toolBtn[1].SetColor(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));	
	/*m_toolBtn[0].Invalidate();
    m_toolBtn[0].UpdateWindow();	
	m_toolBtn[1].Invalidate();
    m_toolBtn[1].UpdateWindow();
*/
	Invalidate();
	UpdateWindow();
}

void CGuiWorkTab::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CGuiTabWnd::OnWindowPosChanging(lpwndpos);
	CGuiTab* ct  = (CGuiTab*) m_pArray[m_iSelectTab];
	CWnd* ViewAc = ct->pParent;
}

void CGuiWorkTab::OnSize(UINT nType, int cx, int cy)
{
	CGuiTabWnd::OnSize(nType, cx, cy);
	SizeScroll();
}


void CGuiWorkTab::SizeScroll()
{
	SCROLLINFO sCrollInfo;
	ASSERT_VALID(this);	
	
	if (!m_pArray.GetSize()) 
		return;
	
	CGuiTab* ct  = (CGuiTab*) m_pArray[m_iSelectTab];
	CWnd* ViewAc = ct->pParent;
	
	memset(&sCrollInfo, 0, sizeof(SCROLLINFO));
	sCrollInfo.cbSize = sizeof(SCROLLINFO);
	sCrollInfo.fMask  = SIF_ALL;
	
	ViewAc->GetScrollInfo(SB_HORZ, &sCrollInfo);
	if (::IsWindow(m_scroll.GetSafeHwnd()))
		m_scroll.SetScrollInfo(&sCrollInfo);
	
	ViewAc->ShowScrollBar(SB_HORZ, FALSE);
	ViewAc->ModifyStyle(WS_HSCROLL, 0, SWP_DRAWFRAME);	
}
