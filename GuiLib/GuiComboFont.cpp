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
#include "GuiComboFont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CGuiComboFont

IMPLEMENT_DYNAMIC(CGuiComboFont, CComboBox)

CGuiComboFont::CGuiComboFont()
{
	m_clrBtnFace     = GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	m_clrBtnLight    = ::GetSysColor(COLOR_3DHILIGHT);
	m_clrBtnDark     = ::GetSysColor(COLOR_3DSHADOW);
	m_iWidthDrowDown = GetSystemMetrics(SM_CXHTHUMB);
	m_bOverCombo     = FALSE;
	m_Font.CreateStockObject(DEFAULT_GUI_FONT);
	m_bPress         = FALSE;

	m_imgArrow.Create(IDB_GUI_DOCKBAR, 9, 11, RGB(255, 0, 255));
	CBitmap cbmp;
	BITMAP bmp;
	cbmp.LoadBitmap(IDB_GUI_DOCKBAR);
	cbmp.GetBitmap(&bmp);
	mHeight          = CPoint(bmp.bmWidth, bmp.bmHeight);	
	m_bFondoXp       = FALSE;
	m_IsCallMiniTool = FALSE;
	bColor           = TRUE;
	bhistory         = FALSE;
}

CGuiComboFont::~CGuiComboFont()
{
}


void CGuiComboFont::FillerCombo()
{
	CClientDC dc(this);
	ResetContent();
	::EnumFonts(
		dc,                  // handle to device context
		NULL,       // pointer to font typeface name string
		(FONTENUMPROC) EnumFontsProc,  // pointer to callback function
		(LPARAM) this);             // pointer to application-supplied data
		
	SetCurSel(0);
}

void CGuiComboFont::OnSysColorChange()
{
	CComboBox::OnSysColorChange();
	m_clrBtnLight    = ::GetSysColor(COLOR_3DHILIGHT);
	m_clrBtnDark     = ::GetSysColor(COLOR_3DSHADOW);
	if (bColor)
		m_clrBtnFace = GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
}

void CGuiComboFont::AutoColor(BOOL bAColor)
{
	bColor = bAColor;
}

BEGIN_MESSAGE_MAP(CGuiComboFont, CComboBox)
	//{{AFX_MSG_MAP(CGuiComboFont)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnCbnKillfocus)
    // ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillFocus)
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	//}}AFX_MSG_MAP
		ON_CONTROL_REFLECT(CBN_EDITUPDATE, OnCbnEditupdate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiComboFont message handlers

void CGuiComboFont::PreSubclassWindow() 
{
	CComboBox::PreSubclassWindow();
	// FillerCombo();
}

void CGuiComboFont::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_bOverCombo = TRUE;
	m_bPress = TRUE;
	CClientDC dc(this);
	DrawCombo(CM_SELECCIONADO, &dc);			
	CComboBox::OnLButtonDown(nFlags, point);
}

void CGuiComboFont::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_IsCallMiniTool == TRUE)
		m_bPress = FALSE;
	CComboBox::OnLButtonUp(nFlags, point);
}

void CGuiComboFont::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
   /*
    * Se hace un llamamdo a la función definida por defecto
    * para el procesamiento de mensajes que la aplicación definitivamente
    * no esta interesado en manejar
	**/ 
	m_clrBtnFace=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	CComboBox::DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
	if (m_bPress != TRUE)
		DrawCombo(CM_NORMAL, &dc);
	else
		DrawCombo(CM_SELECCIONADO, &dc);
	// Do not call CComboBox::OnPaint() for painting messages
}

void CGuiComboFont::OnSetFocus(CWnd* pOldWnd) 
{
	CComboBox::OnSetFocus(pOldWnd);
	CClientDC dc(this);
	DrawCombo(CM_SELECCIONADO, &dc);			
}

BOOL CGuiComboFont::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptCurPos;
	CRect m_rcCli;
	GetCursorPos(&ptCurPos);
	ScreenToClient(&ptCurPos);
	GetClientRect(&m_rcCli);
	if (m_rcCli.PtInRect(ptCurPos) && m_bOverCombo == FALSE && m_bPress == FALSE)
	{
		m_bOverCombo = TRUE;
		CClientDC dc(this);
		DrawCombo(CM_ONFOCUS, &dc);			
		SetTimer(1, 10, NULL);
		OnTimer(1);
		return TRUE;
	}
	
	return CComboBox::OnSetCursor(pWnd, nHitTest, message);
}

void CGuiComboFont::SetColor(COLORREF clrFace)
{
	m_clrBtnFace = clrFace;
	Invalidate();
	UpdateWindow();
}

void CGuiComboFont::DrawCombo(enTypeShow enShow, CDC* pDC)
{
    CRect m_rcClient;
	CRect m_rcDropDown;
	GetClientRect(&m_rcClient);
	m_rcClient.bottom -= 1;
	// primero eliminamos los bordes 3D del combobox
	
	pDC->Draw3dRect(&m_rcClient, m_clrBtnFace, m_clrBtnFace);
	m_rcClient.DeflateRect(1, 1);
	if (IsWindowEnabled())
	{
		if (enShow == CM_NORMAL)
			pDC->Draw3dRect(&m_rcClient, 
			GuiDrawLayer::GetRGBPressBXP(), GuiDrawLayer::GetRGBPressBXP());
	}
    else
	{
		pDC->Draw3dRect(&m_rcClient, m_clrBtnLight, m_clrBtnLight);	
	}
	if (enShow == CM_NORMAL)
	{
		m_rcClient.bottom -= 1;
		pDC->Draw3dRect(&m_rcClient, m_clrBtnFace, m_clrBtnFace);
		m_rcClient.bottom += 1;
	}
	else // && !XP
	{
		m_rcClient.bottom -= 1;
		pDC->Draw3dRect(&m_rcClient, 
			GuiDrawLayer::GetRGBCaptionXP(), GuiDrawLayer::GetRGBCaptionXP());
		m_rcClient.bottom += 1;	
	}
	// debemos pintar el borde del boton drawDwon
	CRect m_rc = m_rcClient;
	m_rcClient.DeflateRect(1, 1);
	m_rcClient.left = m_rcClient.right - m_iWidthDrowDown;
	pDC->Draw3dRect(&m_rcClient, m_clrBtnFace, m_clrBtnFace);
	m_rcClient.DeflateRect(1, 1);
	m_rcClient.InflateRect(0, 1);
	if (enShow == CM_NORMAL)
	{
		// el boton no esta seleccionado
		m_rc.DeflateRect(1, 1);
		CBrush cblu;
		m_rcClient.bottom += 1;
		cblu.CreateSolidBrush(m_clrBtnFace);
		pDC->FillRect(&m_rcClient, &cblu);
		m_rcClient.right += 1;
		m_rcClient.left -= 1;
		m_rcClient.bottom -= 1;
		pDC->Draw3dRect(&m_rcClient, 
			GuiDrawLayer::GetRGBColorBTNHigh(), GuiDrawLayer::GetRGBColorBTNHigh());
		pDC->Draw3dRect(&m_rc, 
			GuiDrawLayer::GetRGBColorBTNHigh(), GuiDrawLayer::GetRGBColorBTNHigh());
		m_rcClient.right += 1;
		m_rcClient.left += 1;
		m_rcClient.bottom += 1;
		DrawArrow(pDC, m_rcClient);
		cblu.DeleteObject();
	}
	else
	{
		m_rcClient.InflateRect(1, 1);
		CBrush cblu;
		cblu.CreateSolidBrush(enShow == CM_ONFOCUS? GuiDrawLayer::GetRGBFondoXP():GuiDrawLayer::GetRGBPressBXP());
		pDC->FillRect(&m_rcClient, &cblu);
		m_rcClient.right += 1;
		m_rcClient.bottom -= 1;
		pDC->Draw3dRect(&m_rcClient, GuiDrawLayer::GetRGBCaptionXP(), GuiDrawLayer::GetRGBCaptionXP());
		DrawArrow(pDC, m_rcClient);
		cblu.DeleteObject();
	}
}

void CGuiComboFont::DrawArrow(CDC* pDC, CRect m_rc)
{
	int difh =m_rc.Height() - mHeight.y;
	difh /= 2;
	
	m_rc.left = m_rc.right - m_iWidthDrowDown;
	m_imgArrow.Draw(pDC, 0, CPoint(m_rc.left + 2, m_rc.top + difh), ILD_TRANSPARENT);		
}

void CGuiComboFont::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent== 1)
	{
		CPoint pt(GetMessagePos());
		CRect m_rc;
		ScreenToClient(&pt);
		GetClientRect(m_rc);
		if (!m_rc.PtInRect(pt) && m_bPress != TRUE)
		{
			KillTimer(1);
			m_bOverCombo = FALSE;
			CClientDC dc(this);
			if (m_bPress == FALSE)
				DrawCombo(CM_NORMAL, &dc);			
			else
				DrawCombo(CM_ONFOCUS, &dc);	
			m_bPress = FALSE;
		}		
	}
	
	CComboBox::OnTimer(nIDEvent);
}

void  CGuiComboFont::OnCloseup() 
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);
	m_bPress = FALSE;
	OnTimer(1);
}

// void CGuiComboFont::OnKillFocus(CWnd* pNewWnd) //version 6
void CGuiComboFont::OnCbnKillfocus() // version 7.0
{
    CClientDC dc(this);
	DrawCombo(CM_NORMAL, &dc);
	
	if (!(GetStyle() & CBS_DROPDOWNLIST))
	{
		CString sCad;
		GetWindowText(sCad);
		AddString(sCad);
	}
	
	m_bPress = FALSE;
	m_bOverCombo = FALSE;
}

int CGuiComboFont::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetFont(&m_Font);
	FillerCombo();
	return 0;
}


BOOL CALLBACK CGuiComboFont::EnumFontsProc(LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwFontType, LPARAM lpData)	
{	
	CGuiComboFont *pThis = (CGuiComboFont*)(lpData);		
	int index = pThis->AddString(lplf->lfFaceName);
	ASSERT(index != -1);
	int ret = pThis->SetItemData(index, dwFontType); 
	ASSERT(ret != -1);

	return TRUE;
}

void CGuiComboFont::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc = lpDrawItemStruct->rcItem;
	int nNumItem = lpDrawItemStruct->itemID;
	CBrush bf;	
	if (nNumItem == -1)
		return;
	rc.bottom -= 2;
	CString szFontName;
	GetLBText(nNumItem, szFontName);
	DWORD dwData = GetItemData(nNumItem);
	
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		bf.CreateSolidBrush(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
		bf.CreateSolidBrush(pDC->GetBkColor());
	}
	
	pDC->SetBkMode(TRANSPARENT);
	pDC->FillRect(&rc, &bf);
	
	CFont font;
	if (!font.CreateFont(
		16,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		szFontName))			   // lpszFacename		                 
		return;		
	
	CSize sz;
	HFONT hFont = NULL;
	hFont = (HFONT)pDC->SelectObject(font);
	sz    = pDC->GetTextExtent(szFontName);
	
	if (GetItemData(lpDrawItemStruct->itemID) & TRUETYPE_FONTTYPE)
	{
		m_imgArrow.Draw(pDC, 11, CPoint(rc.left + 2, rc.top + 1), ILD_TRANSPARENT);
	}

	pDC->TextOut(rc.left + 13, rc.top, szFontName);
	pDC->SelectObject(hFont);
}

void CGuiComboFont::OnCbnEditupdate()
{
	CString m_szCad;
	GetWindowText(m_szCad);
	
	DWORD m_dwCurRange = GetEditSel();
	DWORD m_dwStart    = LOWORD(m_dwCurRange);
	DWORD m_dwEnd      = HIWORD(m_dwCurRange);
	// se busca la cadena aprox, si no existe se debe insertar
	
	if (SelectString(-1, m_szCad) == CB_ERR)
	{
		SetCurSel(0);
	}
	else
	{
		if (m_dwCurRange != CB_ERR)
		{
			if (m_dwEnd <(DWORD) m_szCad.GetLength())
				SetEditSel(m_dwStart, m_dwEnd);
			else
				SetEditSel(m_szCad.GetLength(), - 1);
		}
	}
}

void CGuiComboFont::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
}

