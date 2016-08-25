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
#include "GuiSliderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiSliderCtrl

CGuiSliderCtrl::CGuiSliderCtrl()
{
	bSelected=FALSE;
	m_clrGreen=RGB(0,198,0);  //verder
	m_clrOrange=RGB(255,193,111); //no tan naranja
	m_Press=FALSE;
}

CGuiSliderCtrl::~CGuiSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CGuiSliderCtrl, CSliderCtrl)
	//{{AFX_MSG_MAP(CGuiSliderCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)

	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiSliderCtrl message handlers

void CGuiSliderCtrl::OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	LPNMCUSTOMDRAW lpcd = (LPNMCUSTOMDRAW)pNMHDR;
	CDC*	pDC=CDC::FromHandle(lpcd->hdc);
	CRect	rcClient=lpcd->rc;
	UINT	dwItemSpec=lpcd->dwItemSpec;
	DWORD	dwDrawStage=lpcd->dwDrawStage;
	UINT    uItemState=lpcd->uItemState;
	//bSelected= uItemState & CDIS_FOCUS ? TRUE:FALSE;
	//------------------------------------------------
	//aun no se puede pintar el control
	//------------------------------------------------
	if (dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;         
		return;
	}
	//-----------------------------------------------
	//intentelo ahora
	//-----------------------------------------------
	if (dwDrawStage == CDDS_ITEMPREPAINT)
	{	
		if (dwItemSpec == TBCD_TICS)
		{
			*pResult = CDRF_DODEFAULT;
			return;
		}	
		else if (dwItemSpec ==  TBCD_THUMB)
		{
			*pResult = CDRF_SKIPDEFAULT;

			if (rcClient.Height() > rcClient.Width())
					DrawVThumb(pDC, rcClient);
			else
					DrawHThumb(pDC, rcClient);
			return;
		}
		else if (dwItemSpec == TBCD_CHANNEL)
		{
			*pResult = CDRF_SKIPDEFAULT;
			pDC->Draw3dRect(&rcClient,m_dl.GetRGBPressBXP(),::GetSysColor(COLOR_BTNHIGHLIGHT));
			return;
		}
	}
	
}

void CGuiSliderCtrl::DrawHThumb(CDC* pDC,CRect rcClient)
{
	//------------------------------------------
	//prefiero todo a pulso
	//------------------------------------------
	CPen cpGreen(PS_SOLID,1,m_clrGreen);
	CPen cpOrange(PS_SOLID,1,m_clrOrange);
	CPen cp(PS_SOLID,1,m_dl.GetRGBPressBXP());
	CPen cpFondo(PS_SOLID,1,m_dl.GetRGBFondoXP());
	CPen cpSombra(PS_SOLID,1,RGB(225,225,225));
	CPen cpSombraDark(PS_SOLID,1,RGB(200,200,200));
	CPen* pOld;
	CBrush cb;
	
	//se pinta arriba y luego por la derecha
	//vertice left,top
	pOld=pDC->SelectObject(&cp);
	int nMedio=rcClient.Width()-7;
	//------------------------------------------
	//pintar el fondo estilo  xp
	//------------------------------------------
	rcClient.bottom--;
	CRect m_rectTemp=rcClient;
	m_rectTemp.right-=5;
	cb.CreateSolidBrush(m_dl.GetRGBColorXP());
	pDC->FillRect(&m_rectTemp,&cb);
	//*************************************************
	// -
	pDC->MoveTo(rcClient.left+1,rcClient.top);
	pDC->LineTo(rcClient.left+nMedio,rcClient.top);
	// |
	pDC->MoveTo(rcClient.left,rcClient.top+1);
	pDC->LineTo(rcClient.left,rcClient.bottom);

	// -
	pDC->MoveTo(rcClient.left+1,rcClient.bottom);
	pDC->LineTo(rcClient.left+nMedio,rcClient.bottom);
	//Algo de sombra
	pDC->SelectObject(&cpSombraDark);
	pDC->MoveTo(rcClient.left+1,rcClient.top+1);
	pDC->LineTo(rcClient.left+nMedio,rcClient.top+1);

	pDC->SelectObject(&cpSombra);
	pDC->MoveTo(rcClient.left+1,rcClient.top+2);
	pDC->LineTo(rcClient.left+nMedio,rcClient.top+2);
	pDC->MoveTo(rcClient.left+1,rcClient.bottom-1);
	pDC->LineTo(rcClient.left+nMedio,rcClient.bottom-1);

	//-----------------------------------------------------------
	//se pinta los colores de acuerdo al la seleccion del boton
	//naranja si se selecciona y verde normal, en la parte superior
	//-----------------------------------------------------------
	rcClient.DeflateRect(1,1);
	pDC->SelectObject(bSelected!=TRUE?&cpGreen:&cpOrange);
	for (int i=0; i<3;i++)
	{
		pDC->MoveTo(rcClient.left+i,rcClient.top);
		pDC->LineTo(rcClient.left+i,rcClient.bottom+1);
			
	}
	rcClient.InflateRect(1,1);
	pDC->SelectObject(&cp);
	//-------------------------------------------------------------
	//se pinta la punta
	//-------------------------------------------------------------
	for (int y =0; y<5;y++)
	{
		pDC->SetPixel(rcClient.left+nMedio+y,rcClient.top+y,m_dl.GetRGBPressBXP());
		pDC->SetPixel(rcClient.left+nMedio+y,rcClient.bottom-y,m_dl.GetRGBPressBXP());
	}
	pDC->SetPixel(rcClient.left+nMedio+y,rcClient.bottom-y,m_dl.GetRGBPressBXP());
	
	//pDC->SetPixel(rcClient.right-y,rcClient.top+nMedio+y,m_dl.GetRGBPressBXP());

	//********************************************************
	
	//-----------------------------------------------------------
	//se pinta los colores de acuerdo al la seleccion del boton
	//naranja si se selecciona y verde normal
	//-----------------------------------------------------------
	pDC->SelectObject(bSelected!=TRUE?&cpGreen:&cpOrange);
	
	for (y =0; y<5;y++)
	{
		pDC->SetPixel(rcClient.left+nMedio+y,(rcClient.top+y)+1,
			bSelected!=TRUE?m_clrGreen:m_clrOrange);
		pDC->SetPixel((rcClient.left+nMedio+y),(rcClient.bottom-y)-1,
			bSelected!=TRUE?m_clrGreen:m_clrOrange);
	}

	//-----------------------------------------------------------
	//se pinta sombra a la punta para dar un aspecto mas grueso 
	//al boton
	//-----------------------------------------------------------
	pDC->SelectObject(bSelected!=TRUE?&cpGreen:&cpOrange);
	
	for (y =0; y<4;y++)
	{
		pDC->SetPixel(rcClient.left+nMedio+y,(rcClient.top+y)+2,
			RGB(225,225,225));
		pDC->SetPixel(rcClient.left+nMedio+y,(rcClient.bottom-y)-2,
			RGB(200,200,200));
	}

	pDC->SelectObject(pOld);
		
}




void CGuiSliderCtrl::DrawVThumb(CDC* pDC,CRect rcClient)
{
	//------------------------------------------
	//prefiero todo a pulso
	//------------------------------------------
	CPen cpGreen(PS_SOLID,1,m_clrGreen);
	CPen cpOrange(PS_SOLID,1,m_clrOrange);
	CPen cp(PS_SOLID,1,m_dl.GetRGBPressBXP());
	CPen cpFondo(PS_SOLID,1,m_dl.GetRGBFondoXP());
	CPen cpSombra(PS_SOLID,1,RGB(225,225,225));
	CPen cpSombraDark(PS_SOLID,1,RGB(200,200,200));
	CPen* pOld;
	CBrush cb;
	
	//se pinta arriba y luego por la derecha
	//vertice left,top
	pOld=pDC->SelectObject(&cp);
	int nMedio=rcClient.Height()-7;
	//------------------------------------------
	//pintar el fondo estilo  xp
	//------------------------------------------
	rcClient.right-=1;
	rcClient.bottom++;
	CRect m_rectTemp=rcClient;
	m_rectTemp.bottom-=5;
	m_rectTemp.DeflateRect(1,1);
	cb.CreateSolidBrush(m_dl.GetRGBColorXP());
	pDC->FillRect(&m_rectTemp,&cb);
	//*************************************************
	// -
	pDC->MoveTo(rcClient.left+1,rcClient.top);
	pDC->LineTo(rcClient.right,rcClient.top);
	// |
	pDC->MoveTo(rcClient.left,rcClient.top+1);
	pDC->LineTo(rcClient.left,rcClient.top+nMedio);

	// |
	pDC->MoveTo(rcClient.right,rcClient.top+1);
	pDC->LineTo(rcClient.right,rcClient.top+nMedio);
	//Algo de sombra
	pDC->SelectObject(&cpSombraDark);
	pDC->MoveTo(rcClient.right-1,rcClient.top+1);
	pDC->LineTo(rcClient.right-1,rcClient.top+nMedio+2);

	pDC->SelectObject(&cpSombra);
	pDC->MoveTo(rcClient.right-2,rcClient.top+1);
	pDC->LineTo(rcClient.right-2,rcClient.top+nMedio+2);
	pDC->MoveTo(rcClient.left+1,rcClient.top+1);
	pDC->LineTo(rcClient.left+1,rcClient.top+nMedio);

	//-----------------------------------------------------------
	//se pinta los colores de acuerdo al la seleccion del boton
	//naranja si se selecciona y verde normal, en la parte superior
	//-----------------------------------------------------------
	rcClient.DeflateRect(1,1);
	pDC->SelectObject(bSelected!=TRUE?&cpGreen:&cpOrange);
	for (int i=0; i<3;i++)
	{
		pDC->MoveTo(rcClient.left,rcClient.top+i);
		pDC->LineTo(rcClient.right+1,rcClient.top+i);
			
	}
	rcClient.InflateRect(1,1);
	pDC->SelectObject(&cp);
	//-------------------------------------------------------------
	//se pinta la punta
	//-------------------------------------------------------------
	for (int y =0; y<5;y++)
	{
		pDC->SetPixel(rcClient.left+y,rcClient.top+nMedio+y,m_dl.GetRGBPressBXP());
		pDC->SetPixel(rcClient.right-y,rcClient.top+nMedio+y,m_dl.GetRGBPressBXP());
	}
	pDC->SetPixel(rcClient.right-y,rcClient.top+nMedio+y,m_dl.GetRGBPressBXP());
	//********************************************************
	
	//-----------------------------------------------------------
	//se pinta los colores de acuerdo al la seleccion del boton
	//naranja si se selecciona y verde normal
	//-----------------------------------------------------------
	pDC->SelectObject(bSelected!=TRUE?&cpGreen:&cpOrange);
	
	for (y =0; y<5;y++)
	{
		pDC->SetPixel((rcClient.left+y)+1,rcClient.top+nMedio+y,
			bSelected!=TRUE?m_clrGreen:m_clrOrange);
		pDC->SetPixel((rcClient.right-y)-1,(rcClient.top+nMedio+y),
			bSelected!=TRUE?m_clrGreen:m_clrOrange);
	}

	//-----------------------------------------------------------
	//se pinta sombra a la punta para dar un aspecto mas grueso 
	//al boton
	//-----------------------------------------------------------
	pDC->SelectObject(bSelected!=TRUE?&cpGreen:&cpOrange);
	
	for (y =0; y<4;y++)
	{
		pDC->SetPixel((rcClient.left+y)+2,rcClient.top+nMedio+y,
			RGB(225,225,225));
		pDC->SetPixel((rcClient.right-y)-2,rcClient.top+nMedio+y,
			RGB(200,200,200));
	}

	pDC->SelectObject(pOld);

	//uff!!!, que rutina tan aburridora de hacer!!!! 
}


void CGuiSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (bSelected==TRUE)
		return;
	CRect rc;
	GetClientRect(&rc);
	if (rc.PtInRect(point))
	{
		bSelected=TRUE;
		Invalidate();
		UpdateWindow();
		SetTimer(1,100,NULL);
	}
	CSliderCtrl::OnMouseMove(nFlags, point);
}


void CGuiSliderCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRect m_rect;
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	GetClientRect(m_rect);
	if (!m_rect.PtInRect(pt))
	{
		bSelected=FALSE;
		Invalidate();
		UpdateWindow();
		KillTimer(1);
	}
	CSliderCtrl::OnTimer(nIDEvent);
}

void CGuiSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (bSelected==FALSE)
	{
		bSelected=TRUE;
		Invalidate();
		UpdateWindow();
	}
	CSliderCtrl::OnLButtonDown(nFlags, point);
}

void CGuiSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	bSelected=FALSE;
	Invalidate();
	UpdateWindow();
	KillTimer(1);
	CSliderCtrl::OnLButtonUp(nFlags, point);
}
