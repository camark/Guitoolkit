// GuiPanelWnd.cpp : implementation file
//

#include "stdafx.h"
#include "guilib.h"
#include "GuiPanelWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiPanelWnd

CGuiPanelWnd::CGuiPanelWnd()
{
	m_pWin=NULL;		 
	bHide=TRUE;      
	m_bActive=FALSE;  
	m_StyleDisplay=GUISTYLE_XP;
	nGapGripper=20;
	m_stateBtn=NORMAL;
}

CGuiPanelWnd::~CGuiPanelWnd()
{
}


BEGIN_MESSAGE_MAP(CGuiPanelWnd, CWnd)
	//{{AFX_MSG_MAP(CGuiPanelWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CGuiPanelWnd::DrawGripper(CDC* pDC, CRect* rc)
{
	CRect gripper = rc;
	gripper.top =3;
	gripper.left+=4;
	gripper.right-=3;	
	if(m_StyleDisplay == GUISTYLE_XP)
		gripper.bottom =gripper.top +nGapGripper-3;
	if(m_StyleDisplay == GUISTYLE_2003)
		gripper.bottom =gripper.top +nGapGripper+1;
	//si la ventana esta activa pintamos el caption o el area del titulo de color azul 	
	if(!m_bActive)
	{
		if (m_StyleDisplay == GUISTYLE_2003)
		{
			CGradient M(CSize(gripper.Width(),gripper.Height()));	
			M.PrepareVertical(pDC,m_StyleDisplay);
			M.Draw(pDC,4,0,0,0,gripper.Width(),gripper.Height(),SRCCOPY);	
		}
		
		if (m_StyleDisplay == GUISTYLE_XP)
		{
			CPen cp(PS_SOLID,1,::GetSysColor(COLOR_BTNSHADOW));
			CPen* cpold=pDC->SelectObject(&cp);
			//linea superior
			pDC->MoveTo(gripper.left+1,gripper.top);
			pDC->LineTo(gripper.right,gripper.top);
			//linea izquierda
			pDC->MoveTo(gripper.left,gripper.top+1);
			pDC->LineTo(gripper.left,gripper.bottom);
			//linea inferior
			pDC->MoveTo(gripper.left+1,gripper.bottom);
			pDC->LineTo(gripper.right,gripper.bottom);
			//linea derecha
			pDC->MoveTo(gripper.right,gripper.top+1);
			pDC->LineTo(gripper.right,gripper.bottom);
			pDC->SelectObject(cpold);
		}
	}
	else
	{
		if (m_StyleDisplay == GUISTYLE_XP)
		{
			CBrush cb;
			cb.CreateSolidBrush(::GetSysColor(COLOR_ACTIVECAPTION));//GuiDrawLayer::GetRGBCaptionXP());
			pDC->FillRect(gripper,&cb);
			cb.DeleteObject();
		}
		
		if (m_StyleDisplay == GUISTYLE_2003)
		{
			CGradient M(CSize(gripper.Width(),gripper.Height()));	
			M.PrepareCaption(pDC,m_StyleDisplay);
			M.Draw(pDC,4,0,0,0,gripper.Width(),gripper.Height(),SRCCOPY);	
		}
	}

	if(m_StyleDisplay == GUISTYLE_2003) //no es XP
	{
		
		CRect rcWin=gripper;
		//rcWin.left= gripper.left;
		rcWin.top+=5;
		rcWin.left+=5;
		rcWin.right=rcWin.left+2;
		rcWin.bottom-=4;
		CRect rcBlack;

		for (int i=0; i < rcWin.Height(); i+=4)
		{
			CRect rcWindow;
			CBrush cb;
			cb.CreateSolidBrush(::GetSysColor(COLOR_BTNHIGHLIGHT));
			rcWindow=rcWin;
			rcWindow.top=rcWin.top+i;
			rcWindow.bottom=rcWindow.top+2;
			pDC->FillRect(rcWindow,&cb);
			rcBlack=rcWindow;
			rcBlack.left-=1;
			rcBlack.top=(rcWin.top+i)-1;
			rcBlack.bottom=rcBlack.top+2;
			rcBlack.right=rcBlack.left+2;
			cb.DeleteObject();
			cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Theme));
			pDC->FillRect(rcBlack,&cb);
	
		}
		
			
		
	}


	gripper.DeflateRect(1, 1);
	CString m_caption;
	GetWindowText(m_caption);
	CFont m_cfont;

	m_cfont.CreateFont(-11,0,0,0,400,0,0,0,0,1,2,1,34,_T("Verdana"));
		
	CFont* m_fontOld=pDC->SelectObject(&m_cfont);
	int nMode = pDC->SetBkMode(TRANSPARENT);
	CSize SizeCad=pDC->GetTextExtent(m_caption);
	CRect rCText=gripper;
	rCText.top=6;
	rCText.bottom =rCText.top+14;
	
	int cont=SizeCad.cx;
	while(cont > 1 && gripper.Width() > 0)
		{
			CSize coor=pDC->GetTextExtent(m_caption,m_caption.GetLength());
			if(coor.cx > gripper.Width()-10)
			{
				m_caption=m_caption.Left(m_caption.GetLength()-1);
			}
			else
				break;
			cont--;
				
		}
	if (gripper.Width() > 0	)
	if (!m_bActive)
		pDC->TextOut(rCText.left+8,rCText.top,m_caption);
	else
	{
		if (!GuiDrawLayer::m_Theme)
		pDC->SetTextColor(RGB(255,255,255));
		pDC->TextOut(rCText.left+8,rCText.top,m_caption);
	}
	//CRect gripper;
	//------------------------------------------------
	GetWindowRect( gripper );
	ScreenToClient( gripper );
	gripper.OffsetRect( -gripper.left, -gripper.top );
	gripper.left=gripper.right-20;
	gripper.right-=7;
	gripper.top+=6;
	gripper.bottom=gripper.top+13;
	m_rcCloseBtn=gripper;
	//m_rcCloseBtn.left-=4;
	//ClientToScreen(m_rcCloseBtn);
		
	m_CloseBtn.Paint(pDC,m_stateBtn,gripper,NULL_BRUSH);
		
	
	//------------------------------------------------
 	pDC->SetBkMode(nMode);
	pDC->SelectObject(m_fontOld);
	
}

void CGuiPanelWnd::AddWindow(CWnd* pWin)
{
//	m_pParent= (CGuiControlBar*)pWin->GetParent();
	m_pWin=pWin;
	m_pWin->SetOwner(this);
}

void CGuiPanelWnd::DeletedWindow()
{
	m_pWin->SetOwner(GetParent());
}



/////////////////////////////////////////////////////////////////////////////
// CGuiPanelWnd message handlers

int CGuiPanelWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CGuiPanelWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(rect);
	CBrush cbr;
	cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	dc.FillRect(rect,&cbr);

}
void CGuiPanelWnd::OnNcPaint() 
{
	// TODO: Add your message handler code here
	// Tomo la misma rutina que se desarrolla para la clase 
	// CGuiToolBarWnd.
	CRect rcWindow;
	CRect rcClient;
	CWindowDC	dc(this);
	CDC			m_dc;		//contexto de dispositivo en memoria
	CBitmap		m_bitmap;
	//la idea es tomar el area de la ventana y area  cliente , luego debemos
	//igualar el area de coordenadas de ventana al cliente
	GetWindowRect(&rcWindow);
	GetClientRect(&rcClient);
	ScreenToClient(rcWindow);
    rcClient.OffsetRect(-rcWindow.TopLeft());
    rcWindow.OffsetRect(-rcWindow.TopLeft());
  	
	m_dc.CreateCompatibleDC(&dc);
	m_bitmap.CreateCompatibleBitmap(&dc,rcWindow.Width(),rcWindow.Height());
	CBitmap *m_OldBitmap=m_dc.SelectObject(&m_bitmap);
	//aqui debe utilizarse la brocha que define GuiDrawLayer, si no hacemos la siguiente
	//linea usted vera un horrible color negro, a cambio del dibujo.
	CBrush cb;
	cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	m_dc.FillRect(rcWindow, &cb);

	DrawGripper(&m_dc,&rcWindow);
	dc.IntersectClipRect(rcWindow);
    dc.ExcludeClipRect(rcClient);//asi evitamos el parpadeo
	dc.BitBlt(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),&m_dc,0,0,SRCCOPY);
	m_dc.SelectObject(m_OldBitmap);
	m_bitmap.DeleteObject();
	m_dc.DeleteDC();
}

void CGuiPanelWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnMouseMove(nFlags, point);
}

void CGuiPanelWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CGuiPanelWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CGuiPanelWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CWnd::OnEraseBkgnd(pDC);
}

//en esta función se calcula el area cliente que podra ser utilizado
//por ventanas que deriven esta clase.
void CGuiPanelWnd::OnNcCalcSize(BOOL /*bCalcValidRects*/, NCCALCSIZE_PARAMS* lpncsp)
{
	// adjust non-client area for border space
	lpncsp->rgrc[0].left +=5;
	lpncsp->rgrc[0].top +=nGapGripper+3;
	if (IsVert())
		lpncsp->rgrc[0].right -=5;
	else
		lpncsp->rgrc[0].right -=3;
	lpncsp->rgrc[0].bottom -=3;

}

void CGuiPanelWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	CRect rc;
	GetClientRect(rc);
	m_pWin->MoveWindow(rc,TRUE);	
	// TODO: Add your message handler code here
	
}

BOOL CGuiPanelWnd::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, UINT nAling) 
{
	//gran parte del codigo se tomo como guia de clases MFC
	ASSERT_VALID(pParentWnd);   // must have a parent
	//en esta linea se verifica que la ventana debe disponer de un estilo fijo o dinamico
	//pero no los dos.el estilo Dynamic permite cambiar el tamaño dela ventana mientras flota
	//pero no cuando esta docking, el estilo fijo determina las columnas en que se disponen los
	//componentes y permance asi.
	ASSERT(!((dwStyle & CBRS_SIZE_FIXED) && (dwStyle & CBRS_SIZE_DYNAMIC)));
	// save the style
	//en dwStyle debe asignarse un tipo de alineación por ejemplo CBRS_TOP,etc de lo contrario
	//se generase un ASSERT al acambiar el Style
	dwStyle|=CBRS_TOP;
	DWORD m_dwStyle = (dwStyle & CBRS_ALL);//save the original style
	dwStyle &= ~CBRS_ALL;
	m_nLastAlingDocking=nAling;
	//en la siguiente instruccion el proposito que se busca es evitar el parpadeo 
	//cuando se refresca la ventana.
	//WS_CLIPCHILDREN : recorta el area de las ventanas hijas cuando se dibuja sobre 
	//				 la ventana que la contiene.
	//WS_CLIPSIBLING : cuando se recibe el mensaje paint se recorta el area de las otras ventanas
	//				   hijas superpuestas, que estan fuera de la region.	
	dwStyle |= WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
	//con el estilo CS_DBLCLKS, lo que se busca es que al recibir un doble clic
	//la ventana reaccione,ojo el problema es que esto lo hace solo con el area cliente. 
	LPCTSTR lpszClassName=::AfxRegisterWndClass(CS_DBLCLKS,
												::LoadCursor(NULL,IDC_ARROW),
												::GetSysColorBrush(COLOR_BTNFACE),
												NULL);
	BOOL bResp= CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID,NULL);
	if (!bResp) return FALSE;
	
	return TRUE;
	
}
