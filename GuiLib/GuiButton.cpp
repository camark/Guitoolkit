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
#include "GuiButton.h"
#include "GuiDrawLayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define   OVER     0
#define   FOCUS    1
#define   NORMAL   2
#define   DISABLED 3

/////////////////////////////////////////////////////////////////////////////
// CGuiButton

CGuiButton::CGuiButton()
{
	m_iAling       = ALING_LEFT; 
	m_iStyle       = STYLE_SEMIFLAT;
	m_lpMsg        = _T("");
	m_iSelected    = 0;
	m_viewImage    = FALSE;
	m_ViewText     = FALSE;
	m_iTypeButton  = TYPE_NORMAL;	// Normal by default
	m_iMenuActivo  = FALSE;
	m_clrface      = GuiDrawLayer::GetRGBColorFace();
	m_ReposWindow  = FALSE;
	m_bIsDark      = FALSE;
}

CGuiButton::~CGuiButton()
{
	for (int i = 0; i < 3; i++)
	{
		if (m_hicon[i] != NULL)
			DestroyIcon(m_hicon[i]);
	}
}

BEGIN_MESSAGE_MAP(CGuiButton, CButton)
	//{{AFX_MSG_MAP(CGuiButton)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiButton message handlers


//*****************************************************************************
void CGuiButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	ICONINFO bm;
	CSize sizeImag;
	CBrush cb;
	CSize SizeCad(0, 0);
	CSize pt;
	CPoint m_point;
	int m_Index = 0;
	ZeroMemory(&bm, sizeof(ICONINFO));
	CDC* pDC= CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect m_rect = &lpDrawItemStruct->rcItem;
	UINT m_State = lpDrawItemStruct->itemState;
	
	//---------------------------------------------------------------------
	// Se obtiene la cadena del boton si tiene
	//---------------------------------------------------------------------
	CString m_caption;
	GetWindowText(m_caption);
	//---------------------------------------------------------------------
	// Se dibuja el fondo segun sea el estilo
	// si es TooBarXP
	// si no si es un boton Normal
	//---------------------------------------------------------------------
	if (m_State & ODS_SELECTED) // el boton esta presionado
	{
		if (STYLEXP == m_iStyle) 
			cb.CreateSolidBrush(m_clrface);	
	}
	else if (m_iSelected == 1) // el mouse esta sobre el boton
	{
		if (STYLEXP == m_iStyle) 
			cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorBTNHigh());	
	}
	else // el boton esta normal
	{
		if (STYLEXP == m_iStyle) 
			cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorBTNHigh());	
	}
	if (STYLEXP == m_iStyle) 
	{
		CRect rcTemp = m_rect;
		rcTemp.DeflateRect(2, 2);
		rcTemp.right -= 2;
		pDC->FillRect(&rcTemp, &cb);	
	}
	else
	{
		cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace());
		pDC->FillRect(&m_rect, &cb);	
	}
	//********************************************************************
	int nMode = pDC->SetBkMode(TRANSPARENT);
	if (m_caption.GetLength() > 0)
		SizeCad = pDC->GetTextExtent(m_caption);
	
	//-------------------------------------------------------------------
	// si el boton esta seleccionado, se mueve el rectangulo para dar la 
	// impresion de presion
	//-------------------------------------------------------------------
	if (m_State & ODS_SELECTED)
		m_rect.bottom += 2;
	
	//-------------------------------------------------------------------
	// El boton tiene una imagen
	//-------------------------------------------------------------------
	if (m_viewImage == TRUE)
	{
		if (m_State & ODS_SELECTED)
			m_Index = 2;
		else if (m_iSelected== 1)
			m_Index = 1;
		else
			m_Index = 0;
		
		if (m_hicon[m_Index]!= NULL) 
		{
			::GetIconInfo(m_hicon[m_Index], &bm);
			sizeImag = CSize((BYTE)(bm.xHotspot * 2), (BYTE)(bm.yHotspot * 2));
			::DeleteObject(bm.hbmMask);
			::DeleteObject(bm.hbmColor);
		}
		else 
		{
			m_Index = -1;
		}
	}
	
	//---------------------------------------------------------------------
	// el boton tiene una imagen pero no texto
	//---------------------------------------------------------------------
	if (m_viewImage == TRUE && m_ViewText== FALSE)
	{
		if (m_Index != -1)
		{
			int calculodify;
			m_rect.right = m_rect.left + sizeImag.cx + 5;
			calculodify = m_rect.Height()- (sizeImag.cy);
			calculodify /= 2;
			m_point = CPoint(2, calculodify);
			if (m_bIsDark && m_iSelected == 1 && !(m_State & ODS_DISABLED))
			{
				CPoint p(m_point.x + 1, m_point.y + 1);
				pDC->DrawState(p, sizeImag, m_hicon[m_Index], DSS_MONO, CBrush(GuiDrawLayer::GetRGBColorShadow()));
				m_point.x -= 1;
				m_point.y -= 1;
			}
			
			pDC->DrawState(m_point, sizeImag, m_hicon[m_Index], (m_State == ODS_DISABLED ? DSS_DISABLED:DSS_NORMAL), CBrush(GuiDrawLayer::GetRGBColorFace()));
		}
	}
	//-----------------------------------------------------------------------
	// El boton tiene una imagen y ademas texto
	//-----------------------------------------------------------------------
	else if (m_viewImage == TRUE && m_ViewText == TRUE)
	{
		int calculodifx = 0;
		int calculodify = 0;
		if (m_Index != -1)
		{
			CRect rectletra;
			calculodifx = m_rect.Width()- (sizeImag.cx);
			calculodifx /= 2;
			calculodify = m_rect.Height()- (sizeImag.cy);
			calculodify /= 2;
			if (m_iAling ==ALING_RIGTH)
			{
				m_point = CPoint(4, calculodify);
				if (m_bIsDark && m_iSelected == 1 && !(m_State & ODS_DISABLED))
				{
					CPoint p(m_point.x + 1, m_point.y + 1);
					pDC->DrawState(p, sizeImag, m_hicon[m_Index], DSS_MONO, CBrush(GuiDrawLayer::GetRGBColorShadow()));
					m_point.x -= 1;
					m_point.y -= 1;
				}
				pDC->DrawState(m_point, sizeImag, m_hicon[m_Index],
					(m_State == ODS_DISABLED ? DSS_DISABLED:DSS_NORMAL), (CBrush*)NULL);
				rectletra = m_rect;
				rectletra.left += sizeImag.cx + 8;
				pt = CSize(rectletra.top, rectletra.left);
				if (m_State & ODS_DISABLED)
					pDC->DrawState(pt, SizeCad, m_caption, DSS_DISABLED, TRUE, 0, (CBrush*)NULL);
				else
					pDC->DrawText(m_caption, rectletra, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
			}
			else
			{
				rectletra = m_rect;
				rectletra.left += 4;
				if (m_bIsDark && m_iSelected == 1 && !(m_State & ODS_DISABLED))
				{	
					CPoint p = CPoint(m_point.x + 1, m_point.y + 1);
					pDC->DrawState(p, sizeImag, m_hicon[m_Index], DSS_MONO, CBrush(GuiDrawLayer::GetRGBColorShadow()));
					m_point.x -= 1;
					m_point.y -= 1;
				}
				
				pt = CSize(rectletra.top, rectletra.left);

				if (m_State & ODS_DISABLED)
					pDC->DrawState(pt, SizeCad, m_caption, DSS_DISABLED, TRUE, 0, (CBrush*)NULL);
				else
					pDC->DrawText(m_caption, rectletra, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				m_point = CPoint((rectletra.right - sizeImag.cx) - 4, calculodify);
				pDC->DrawState(m_point, sizeImag, m_hicon[m_Index], (m_State == ODS_DISABLED ? DSS_DISABLED:DSS_NORMAL), (CBrush*)NULL);
			}
		}
	}
	//-----------------------------------------------------------------------
	// Si el texto es visible
	//-----------------------------------------------------------------------
	else if (m_ViewText == TRUE)
	{
		CSize sz = pDC->GetTextExtent(m_caption);
		int ntempcx = m_rect.Width() - sz.cx;
		int ntempcy = m_rect.Height() - sz.cy;
		pt = CSize(m_rect.left+ (ntempcx/2), m_rect.top+ (ntempcy/2));
		if (m_State & ODS_DISABLED)
			pDC->DrawState(pt, SizeCad, m_caption, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		else
			pDC->DrawText(m_caption, m_rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	m_rect = &lpDrawItemStruct->rcItem;
	
	//-----------------------------------------------------------------
	// se inicia el dibujo de bordes 
	// 1) si es semiflat
	// 2) si es Flat
	// 3) si es estilo ToolBarXp  
	// 4) si es estilo 3d
	//-----------------------------------------------------------------
	if (m_State & ODS_SELECTED)
	{
		if (STYLE_SEMIFLAT== m_iStyle)
			pDC->Draw3dRect(m_rect, GuiDrawLayer::GetRGBColorShadow(), GuiDrawLayer::GetRGBColorBTNHigh());
		else if (STYLE_FLAT == m_iStyle)
			pDC->Draw3dRect(m_rect, GuiDrawLayer::GetRGBColorShadow(), GuiDrawLayer::GetRGBColorBTNHigh());
		else if (STYLEXP == m_iStyle)
			DrawBottonXP(pDC, m_rect, NORMAL);
		else	// si es 3d
		{
			pDC->Draw3dRect(m_rect, GuiDrawLayer::GetRGBColorShadow(), GuiDrawLayer::GetRGBColorBTNHigh());
			CPen cp(PS_SOLID, 1, GuiDrawLayer::GetRGBColorShadow());
			CPen* cpa = pDC->SelectObject(&cp);
			pDC->MoveTo(m_rect.left + 1, m_rect.top + 1);
			pDC->LineTo(m_rect.right - 1, m_rect.top + 1);
			pDC->SelectObject(cpa);
		}
	}	
	//-----------------------------------------------------------------------
	// el boton esta presionado
	//-----------------------------------------------------------------------
	else if (m_iSelected == 1)  // el mouse esta sobre el boton
	{
		if (STYLE_SEMIFLAT== m_iStyle)
			pDC->Draw3dRect(m_rect, GuiDrawLayer::GetRGBColorBTNHigh(), GuiDrawLayer::GetRGBColorShadow());
		else if (STYLE_FLAT == m_iStyle)
			pDC->Draw3dRect(m_rect, GuiDrawLayer::GetRGBColorBTNHigh(), GuiDrawLayer::GetRGBColorShadow());
		else if (STYLEXP == m_iStyle)
			DrawBottonXP(pDC, m_rect, OVER);
		else	// si es 3d
		{
			pDC->Draw3dRect(m_rect, GuiDrawLayer::GetRGBColorBTNHigh(), GuiDrawLayer::GetRGBColorShadow());
			CPen cp(PS_SOLID, 1, GuiDrawLayer::GetRGBColorShadow());
			CPen* cpa = pDC->SelectObject(&cp);
			pDC->MoveTo(m_rect.left + 1, m_rect.bottom - 2);
			pDC->LineTo(m_rect.right - 2, m_rect.bottom - 2);
			pDC->MoveTo(m_rect.right - 2, m_rect.top + 1);
			pDC->LineTo(m_rect.right - 2, m_rect.bottom - 2);
			pDC->SelectObject(cpa);
		}
	}
	else
	{
		//-----------------------------------------------------------------
		// el boton esta en estado normal, es decir el mouse ni lo presiona
		// ni esta sobre el.
		//-----------------------------------------------------------------
		if (STYLE_3D == m_iStyle)
		{
			pDC->Draw3dRect(m_rect, GuiDrawLayer::GetRGBColorBTNHigh(), GuiDrawLayer::GetRGBColorShadow());
			CPen cp(PS_SOLID, 1, GuiDrawLayer::GetRGBColorShadow());
			CPen* cpa = pDC->SelectObject(&cp);
			pDC->MoveTo(m_rect.left + 1, m_rect.bottom - 2);
			pDC->LineTo(m_rect.right - 2, m_rect.bottom - 2);
			pDC->MoveTo(m_rect.right - 2, m_rect.top + 1);
			pDC->LineTo(m_rect.right - 2, m_rect.bottom - 2);
			pDC->SelectObject(cpa);
		}
		else if (STYLEXP == m_iStyle)
		{
			if (m_State & ODS_DISABLED)
			{
				DrawBottonXP(pDC, m_rect, DISABLED);
			}
			else
			{
				if (m_State & ODS_FOCUS)
					DrawBottonXP(pDC, m_rect, FOCUS);
				else	
					DrawBottonXP(pDC, m_rect, NORMAL);
			}
		}
		else
		{
			pDC->Draw3dRect(m_rect, m_clrface, m_clrface);
		}
	}
	
	if ((m_State & ODS_FOCUS) && (STYLEXP != m_iStyle))
	{
		m_rect.DeflateRect(2, 2);
		pDC->DrawFocusRect(m_rect);
	}
	pDC->SetBkMode(nMode);
}


void CGuiButton::AutoSizeButton(BOOL m_bAutoAjust)
{
	m_ReposWindow = m_bAutoAjust;
	Invalidate();
	UpdateWindow();
}

void CGuiButton::OnSysColorChange()
{
	CButton::OnSysColorChange();
	m_clrface = GuiDrawLayer::GetRGBColorXP();
}

//*************************************************************************
void CGuiButton::DrawBottonXP(CDC* pDC, CRect rc, int Estado)
{
	COLORREF clrPress  = ::GetSysColor(COLOR_HIGHLIGHT);
	COLORREF clrShadow = ::GetSysColor(COLOR_BTNSHADOW);
	//*****************************************************
	// dibujamos los bordes del boton
	
	CPen cp(PS_SOLID,       1, clrPress);
	CPen cpface(PS_SOLID,   1, m_clrface);
	CPen cpsxp(PS_SOLID,    1, GuiDrawLayer::GetRGBColorXP());
	CPen cpOver(PS_SOLID,   1, RGB(255, 193, 111));
	CPen cpShadow(PS_SOLID, 1, clrShadow); 
	CPen* pOld = NULL;
	if (Estado != DISABLED)
		pOld = pDC->SelectObject(&cp);
	else
		pOld = pDC->SelectObject(&cpShadow);
	rc.right  -= 4;
	rc.bottom -= 2;
	// la linea superior
	pDC->MoveTo(rc.left + 2, rc.top);
	pDC->LineTo(rc.right - 1, rc.top);
	// linea izquierda
	pDC->MoveTo(rc.left, rc.top + 2);
	pDC->LineTo(rc.left, rc.bottom - 1);
	// linea derecha
	pDC->MoveTo(rc.right, rc.top + 2);
	pDC->LineTo(rc.right, rc.bottom - 1);
	// linea inferior
	pDC->MoveTo(rc.left + 2, rc.bottom);
	pDC->LineTo(rc.right - 1, rc.bottom);
	
	if (Estado != DISABLED)
	{	
		// se dibuja algunas lineas para dar forma 3d
		// linea inferior
		pDC->SelectObject(&cpface);
		pDC->MoveTo(rc.left + 2, rc.bottom - 1);
		pDC->LineTo(rc.right - 1, rc.bottom - 1);
		pDC->MoveTo(rc.right - 1, rc.top + 2);
		pDC->LineTo(rc.right - 1, rc.bottom - 1);
		pDC->SelectObject(&cpsxp);
		pDC->MoveTo(rc.left + 2, rc.bottom - 2);
		pDC->LineTo(rc.right - 1, rc.bottom - 2);
		pDC->MoveTo(rc.right - 2, rc.top + 2);
		pDC->LineTo(rc.right - 2, rc.bottom - 1);
		
		// fin bordes del boton
		//***************************************************************
		CRect rcBordes = rc;
		rcBordes.left += 1;
		rcBordes.top += 1;
		switch (Estado)
		{
			case OVER:
				pDC->Draw3dRect(rcBordes, RGB(255, 202, 130), RGB(255, 193, 111));
				rcBordes.DeflateRect(1, 1);
				pDC->Draw3dRect(rcBordes, RGB(255, 202, 130), RGB(255, 193, 111));
				break;
			case FOCUS:
				pDC->Draw3dRect(rcBordes, GuiDrawLayer::GetRGBFondoXP(), GuiDrawLayer::GetRGBFondoXP());
				rcBordes.DeflateRect(1, 1);
				pDC->Draw3dRect(rcBordes, GuiDrawLayer::GetRGBFondoXP(), GuiDrawLayer::GetRGBFondoXP());
				break;
		}
		//****************************************************************
		// pintar los vertices
		// left,top
		pDC->SetPixel(rc.left + 1, rc.top, Estado != DISABLED ? GuiDrawLayer::GetRGBFondoXP():clrShadow);
		pDC->SetPixel(rc.left, rc.top + 1, Estado != DISABLED ? GuiDrawLayer::GetRGBFondoXP():clrShadow);
		pDC->SetPixel(rc.left + 1, rc.top + 1, Estado != DISABLED ? clrPress:clrShadow);	
		// pintar los vertices
		// left,bottom
		pDC->SetPixel(rc.left + 1, rc.bottom, Estado != DISABLED ? GuiDrawLayer::GetRGBFondoXP():clrShadow);
		pDC->SetPixel(rc.left, rc.bottom - 1, Estado != DISABLED ? GuiDrawLayer::GetRGBFondoXP():clrShadow);
		pDC->SetPixel(rc.left + 1, rc.bottom - 1, Estado != DISABLED ? clrPress:clrShadow);	
		// right,top
		pDC->SetPixel(rc.right - 1, rc.top, Estado != DISABLED ? GuiDrawLayer::GetRGBFondoXP():clrShadow);
		pDC->SetPixel(rc.right, rc.top + 1, Estado != DISABLED ? GuiDrawLayer::GetRGBFondoXP():clrShadow);
		pDC->SetPixel(rc.right - 1, rc.top + 1, Estado != DISABLED ? clrPress:clrShadow);	
		// right,bottom
		pDC->SetPixel(rc.right - 1, rc.bottom, Estado != DISABLED ? GuiDrawLayer::GetRGBFondoXP():clrShadow);
		pDC->SetPixel(rc.right, rc.bottom - 1, Estado != DISABLED ? GuiDrawLayer::GetRGBFondoXP():clrShadow);
		pDC->SetPixel(rc.right - 1, rc.bottom - 1, Estado != DISABLED ? clrPress:clrShadow);	
	}	
	pDC->SelectObject(pOld);
}

//*****************************************************************************
void CGuiButton::SetColor(COLORREF m_clrFaces)
{
	m_clrface = m_clrFaces;
}

//*****************************************************************************
void CGuiButton::ShowImage(BOOL m_viewimage)
{
	m_viewImage = m_viewimage;	
	CalLayout();
}

//*****************************************************************************
void CGuiButton::ShowText(BOOL m_viewText)
{
	m_ViewText = m_viewText;	
	CalLayout();
}

//*****************************************************************************
void CGuiButton::CalLayout()
{
	CString m_str;
	CRect m_rect;
	CSize sizeImag = CSize(0, 0);
	int m_High = 0;
	if (GetSafeHwnd() == NULL)
		return;
	GetWindowText(m_str);
	CClientDC dc(this);
	ICONINFO bm;
	ZeroMemory(&bm, sizeof(ICONINFO));
	GetClientRect(&m_rect);
	CSize SizeCad = CSize(0, 0);
	if (m_viewImage == TRUE)
	{
		if (m_hicon[0]!= NULL)
		{
			::GetIconInfo(m_hicon[0], &bm);
			sizeImag = CSize((BYTE)(bm.xHotspot * 2), (BYTE)(bm.yHotspot * 2));
			::DeleteObject(bm.hbmMask);
			::DeleteObject(bm.hbmColor);
		}
	}

	if (m_ViewText == TRUE)
	{
		if (m_str.GetLength() > 0)
		{
			SizeCad = dc.GetTextExtent(m_str);
			SizeCad.cx -= 7;
		}
	}

	m_High = max(sizeImag.cy, SizeCad.cy);
	m_High = max(m_High, m_rect.Height());
	m_szButton= CSize(SizeCad.cx + sizeImag.cx + 7, m_High);
	
	if (m_ReposWindow == TRUE)
	{
		SetWindowPos(NULL, 0, 0, SizeCad.cx + sizeImag.cx + 10, m_High,
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}
}


//*****************************************************************************
CSize CGuiButton::GetSizeButton()
{
	m_ReposWindow = FALSE;
	CalLayout();
	m_ReposWindow = TRUE;
	return m_szButton;
}

//*****************************************************************************


void CGuiButton::SetImage(HICON hIcon)
{
	m_hicon[0] = hIcon;
	m_hicon[1] = hIcon;
	m_hicon[2] = hIcon;
	ShowImage(TRUE);
}

BOOL CGuiButton::SetImage(UINT uBitmapNormal, UINT uBitmapFocus, UINT uBitmapPush)
{
	BOOL result = FALSE;
	
	HINSTANCE hirc = AfxFindResourceHandle(MAKEINTRESOURCE(uBitmapNormal), RT_BITMAP);
	
	if (uBitmapNormal != -1) 
	{
		m_hicon[0] = (HICON)::LoadImage(hirc, MAKEINTRESOURCE(uBitmapNormal), 
			IMAGE_ICON, 16, 16, LR_LOADMAP3DCOLORS);
		result = TRUE;
	}
	else
	{
		result = FALSE;
	}
	if (uBitmapFocus != -1)
	{
		m_hicon[1] = (HICON)::LoadImage(hirc, MAKEINTRESOURCE(uBitmapFocus), 
			IMAGE_ICON, 16, 16, LR_LOADMAP3DCOLORS);
		if (m_hicon[1] == NULL && m_hicon[0] != NULL)
			m_hicon[1] = (HICON)::LoadImage(hirc, MAKEINTRESOURCE(uBitmapNormal), 
			IMAGE_ICON, 16, 16, LR_LOADMAP3DCOLORS);
	}
	else
	{
		if (m_hicon[0] != NULL)
			m_hicon[1] = (HICON)::LoadImage(hirc, MAKEINTRESOURCE(uBitmapNormal), 
			IMAGE_ICON, 16, 16, LR_LOADMAP3DCOLORS);
	}
	if (uBitmapPush != -1)
	{
		m_hicon[2] = (HICON)::LoadImage(hirc, MAKEINTRESOURCE(uBitmapFocus), 
			IMAGE_ICON, 16, 16, LR_LOADMAP3DCOLORS);
		if (m_hicon[2] == NULL && m_hicon[0]!= NULL)
			m_hicon[2] = (HICON)::LoadImage(hirc, MAKEINTRESOURCE(uBitmapNormal), 
			IMAGE_ICON, 16, 16, LR_LOADMAP3DCOLORS);
	}
	else
	{
		if (m_hicon[0] != NULL)
			m_hicon[2] = (HICON)::LoadImage(hirc, MAKEINTRESOURCE(uBitmapNormal), 
			IMAGE_ICON, 16, 16, LR_LOADMAP3DCOLORS | LR_LOADTRANSPARENT);
	}
	
	CalLayout();
	return result;
}

//*****************************************************************************
void CGuiButton::SetToolTip(LPCTSTR lpMsg)
{
	CRect rc;
	m_lpMsg = lpMsg;
	if (GetSafeHwnd()== NULL)
		return;
	if (m_lpMsg != NULL)
	{
		if (m_ToolTipCtrl.GetSafeHwnd() == NULL) 
		{
			m_ToolTipCtrl.Create(this, TTS_ALWAYSTIP);
			m_ToolTipCtrl.Activate(TRUE);
			m_ToolTipCtrl.AddTool(this, lpMsg);
		}
		else
		{
			m_ToolTipCtrl.UpdateTipText(lpMsg, this);	
		}
	}
	else
	{
		if (m_ToolTipCtrl.GetSafeHwnd() == NULL) 
		{
			m_ToolTipCtrl.Create(this, TTS_ALWAYSTIP);
			m_ToolTipCtrl.AddTool(this, lpMsg);
		}
		else
		{
			m_ToolTipCtrl.UpdateTipText(lpMsg, this);
		}
		
		m_ToolTipCtrl.Activate(FALSE);
	}
}

//*****************************************************************************
void CGuiButton::SetCaption(LPCTSTR lpMsg)
{
	SetWindowText(lpMsg);
	m_ViewText = TRUE;
	CalLayout();
	Invalidate();
}

//*****************************************************************************
void CGuiButton::SetTypeButton(TypeButton m_TypeButton)
{
	m_iTypeButton = m_TypeButton;
	if (m_iTypeButton == TYPE_ARROW)
	{
		m_iStyleArrow = ARROW_RIGHT;
		m_iAling      = ALING_LEFT;
		m_iTypeButton = TYPE_ARROW;
		m_iStyle      = STYLE_3D;
		m_lpMsg       = _T("");
		m_iSelected   = 0;
		m_viewImage   = TRUE;
		m_ViewText    = TRUE;
		SetAlingArrow(ARROW_RIGHT);
	}
}

//*****************************************************************************

void CGuiButton::SetAlingArrow(StyleArrow m_AlingArron)
{
	if (m_iTypeButton == TYPE_ARROW)
	{
		m_iStyleArrow = m_AlingArron;
		
		if (m_iStyleArrow == ARROW_RIGHT)
		{
			if (m_hicon[0]== NULL)
			{
				m_hicon[0] = GuiDrawLayer::LoadIconLib(IDI_GUI_ARROWRIGHT);
			}
			else
			{
				m_hicon[0] = GuiDrawLayer::LoadIconLib(IDI_GUI_ARROWRIGHT);
				m_hicon[1] = GuiDrawLayer::LoadIconLib(IDI_GUI_ARROWRIGHT);
				m_hicon[2] = NULL;
			}
		}
		else
		{
			if (m_hicon[0] == NULL)
			{
				m_hicon[0] = GuiDrawLayer::LoadIconLib(IDI_GUI_ARROWDOWN);		
			}
			else
			{
				m_hicon[0] = GuiDrawLayer::LoadIconLib(IDI_GUI_ARROWDOWN);		
				m_hicon[1] = GuiDrawLayer::LoadIconLib(IDI_GUI_ARROWDOWN);
				m_hicon[2] = NULL;
			}
		}
	}
}

//*****************************************************************************
void CGuiButton::SetStyleBorder(Style m_Style)
{
	m_iStyle = m_Style;
}

//*****************************************************************************
void CGuiButton::SetAlingMsg(AlingMsg m_AlingMsg)
{
	if (m_iTypeButton == TYPE_NORMAL)
		m_iAling = m_AlingMsg;
}

//*****************************************************************************
int CGuiButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

//*****************************************************************************
BOOL CGuiButton::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

//*****************************************************************************
void CGuiButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect m_rect;
	GetClientRect(&m_rect);
	if (m_rect.PtInRect(point))
	{
		if (m_iSelected == 1)
			return;
		m_iSelected =1;
		Invalidate();
		UpdateWindow();
		
		SetTimer(1, 10, NULL);
	}
	
	CButton::OnMouseMove(nFlags, point);
}

//*****************************************************************************
void CGuiButton::PreSubclassWindow() 
{
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}


//*****************************************************************************
void CGuiButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CButton::OnLButtonUp(nFlags, point);
	if (m_iSelected == 1)
		m_iSelected = 0;

	Invalidate();
	UpdateWindow();
}

//*****************************************************************************
void CGuiButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CButton::OnLButtonDown(nFlags, point);
	Invalidate();
	UpdateWindow();
	if (m_iTypeButton == TYPE_ARROW)
	{
		SetFocus();
		ShowMenu();
	}
}

void CGuiButton::SetPopupMenu(CMenu* pMenu)
{
	m_pMenu = pMenu;
}

//*****************************************************************************
void CGuiButton::ShowMenu()
{
	CRect rcW;
	int x, y;
	GetWindowRect(&rcW);
	if (m_iStyleArrow == ARROW_RIGHT)
	{
		x = rcW.right + 1;
		y = rcW.top;
	}
	else
	{
		x = rcW.left;
		y = rcW.bottom;
	}
	
	if (m_pMenu->GetSafeHmenu() != NULL && m_iMenuActivo == FALSE)
	{
		m_iMenuActivo  = TRUE;	
		int m_iResMenu = m_pMenu->GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, 
												x, y,  GetParent(), NULL);
		if (m_iResMenu != 0)
		{
			CWnd* pParent= GetParent();
			pParent->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM) m_hWnd);
		}
		m_iMenuActivo = FALSE;
	}
	else
	{
		return;
	}
	ReleaseCapture();
}

//*****************************************************************************
BOOL CGuiButton::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (m_ToolTipCtrl.GetSafeHwnd())
			m_ToolTipCtrl.RelayEvent(pMsg);
	}
	return CButton::PreTranslateMessage(pMsg);
}

//*****************************************************************************
void CGuiButton::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		CRect m_rect;
		CPoint pt(GetMessagePos());
		ScreenToClient(&pt);
		GetClientRect(m_rect);
		
		if (!m_rect.PtInRect(pt))
		{
			m_iSelected = 0;
			Invalidate();
			UpdateWindow();
			KillTimer(1);
		}
	}
	CButton::OnTimer(nIDEvent);
}

