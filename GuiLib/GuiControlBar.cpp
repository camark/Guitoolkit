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

// GuiControlBar.cpp : implementation file

#include "stdafx.h"
#include "GuiControlBar.h"
#include "GuiDockContext.h"
#include "GuiDrawLayer.h"
#include "GuiToolBarWnd.h"
#include "menuBar.h"
#include "GuiMDIFrame.h"
#include "GuiFrameWnd.h"
#include "GuiMiniFrameWnd.h"


#define  GUI_SCROLLON   10
#define  GUI_SCROLLOFF  11
#define  GUI_NUMITER	5
#define  HTPIN			323
// CGuiControlBar
#pragma warning( disable : 4244 )

IMPLEMENT_DYNAMIC(CGuiControlBar, CControlBar)

CGuiControlBar::CGuiControlBar()
{
	nGapGripper=20;
	m_bActive=FALSE;
	m_bOldActive=FALSE;
	m_sizeMinFloating=m_sizeVert=m_sizeHorz=CSize(200,100);
	m_sizeMinFloating1=m_sizeMinFloating;
	m_sizeHorzt=CSize(200,100);
	m_sizeVertt=CSize(600,100);
	m_pos=0;
	m_Last=0;
	m_bTracking=FALSE;
	m_rcBorder=CRect(0,0,0,0);
	m_rcOldBorder=CRect(0,0,0,0);
	m_ptOld=CPoint(0,0);
	m_sizeMinV=CSize(28,28);
	m_sizeMinH=CSize(28,28);
	m_Initialize=FALSE;
	m_First=-1;
	m_bForcepaint=FALSE;
	m_stateBtn=NORMAL;
	m_stateAHBtn=NORMAL;
	m_bSupportMultiView=FALSE;
	m_MenuContext=NULL;
	m_StyleDisplay=GUISTYLE_XP;
	m_clrFondo=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	m_bAutoHide=FALSE;
	Porc=0.0;
	m_bComplete=TRUE;
	m_IsLoadDocking=TRUE;
	m_hIcon=NULL;


}

CGuiControlBar::~CGuiControlBar()
{

}


BEGIN_MESSAGE_MAP(CGuiControlBar, CControlBar)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCRBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCHITTEST()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_TIMER()
	ON_COMMAND(ID_GUI_SHOWTITLE, OnShowTitle)
	ON_WM_SYSCOLORCHANGE()

END_MESSAGE_MAP()



// CGuiControlBar message handlers

void CGuiControlBar::OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL /*bDisableIfNoHndler*/)
{

	CWnd* pFocus = GetFocus();
	m_bOldActive=(pFocus->GetSafeHwnd() && IsChild(pFocus));
	m_bForcepaint=TRUE;
	if (!m_bActive && m_bOldActive)
		OnActiveWindow();
	m_bForcepaint=FALSE;


}

void CGuiControlBar::OnSysColorChange( )
{
	m_clrFondo=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	CControlBar::OnSysColorChange( );

}

BOOL CGuiControlBar::Create(LPCTSTR lpszWindowName, DWORD dwStyle,CWnd* pParentWnd, UINT nID)
{
	// TODO: Add your specialized code here and/or call the base class
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
	m_dwStyle = (dwStyle & CBRS_ALL);//save the original style
	dwStyle &= ~CBRS_ALL;
	//en la siguiente instruccion el proposito que se busca es evitar el parpadeo
	//cuando se refresca la ventana.
	//WS_CLIPCHILDREN : recorta el area de las ventanas hijas cuando se dibuja sobre
	//				 la ventana que la contiene.
	//WS_CLIPSIBLING : cuando se recibe el mensaje paint se recorta el area de las otras ventanas
	//				   hijas superpuestas, que estan fuera de la region.
	dwStyle |= WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
	pMf=pParentWnd;
	//con el estilo CS_DBLCLKS, lo que se busca es que al recibir un doble clic
	//la ventana reaccione,ojo el problema es que esto lo hace solo con el area cliente.
	LPCTSTR lpszClassName=::AfxRegisterWndClass(CS_DBLCLKS,
												::LoadCursor(NULL,IDC_ARROW),
												::GetSysColorBrush(COLOR_BTNFACE),
												NULL);
	//poque no se llama a CControlBar::Create, bueno, da igual llamar a cualquiera, CWnd o CControlBar
	//esto debido a que CControlbar se deriva de CWnd y porque ademas CControlBar no sobrecarga el
	//metodo Create, nosotros si porque tenemos que particularizar, cosas.
	BOOL bResp= CWnd::Create(lpszClassName, lpszWindowName, dwStyle, CRect(0,0,0,0), pParentWnd, nID);
	if (!bResp) return FALSE;

	return TRUE;
}

int CGuiControlBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//aqui es cuando llamamos a nuestra clase CGuiDockContext, de esta manera
	//sobrecargamos el clase original que para nuestros propositos no nos sirve.
	//porque ?, bueno porque me interesa que no se pegen las toolbar en el interior
	//de las ventanas.
	if (m_pDockContext==NULL)
		m_pDockContext=new CGuiDockContext(this);
	ASSERT(m_pDockContext);
	m_CloseBtn.SetData(6,_T("Close"));
	m_CloseBtn.SetImageList(IDB_GUI_DOCKBAR,9,10,RGB(255,0,255));
	m_AutoHideBtn.SetData(12,_T("Auto Hide"));
	m_AutoHideBtn.SetImageList(IDB_GUI_DOCKBAR,9,15,RGB(255,0,255));
	return 0;
}


void CGuiControlBar::OnShowTitle()
{
	ActiveCaption();
	SendMessage(WM_NCPAINT);
}


CSize CGuiControlBar::CalcWinPos()
{
	
	POSITION pos = m_pDockSite->m_listControlBars.GetHeadPosition();
	DWORD dwDockStyle = m_dwDockStyle;
	dwDockStyle &= CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI;
	CRect rect;
	GetWindowRect(&rect);
	while (pos != NULL)
	{
		CDockBar* pDockBar = (CDockBar*)m_pDockSite->m_listControlBars.GetNext(pos);
		if (pDockBar->IsDockBar() && pDockBar->IsWindowVisible() &&
			(pDockBar->m_dwStyle & dwDockStyle & CBRS_ALIGN_ANY) &&
			(!pDockBar->m_bFloating ||
				(dwDockStyle & pDockBar->m_dwStyle & CBRS_FLOAT_MULTI)))
		{
			CRect rectBar;
			
			pDockBar->GetWindowRect(&rectBar);
			if (rectBar.Width() == 0)
				rectBar.right++;
			if (rectBar.Height() == 0)
				rectBar.bottom++;
			if (rectBar.IntersectRect(rectBar, rect))
			{

				int nSize=pDockBar->m_arrBars.GetSize();
				int iCont=0;
				UINT m_nDockBarID; 
				for (int i=0;i <nSize;  i++)
				{
					m_nDockBarID = pDockBar->GetDlgCtrlID();
					CControlBar* pBar;
					pBar = (CControlBar*) pDockBar->m_arrBars[i];
					if (HIWORD(pBar) == 0) continue; // placeholder
					if (!pBar->IsVisible()) continue;
					iCont++;
				}
				m_pDockSite->GetControlBar(m_nDockBarID)->GetWindowRect(rectBar);
				if((pDockBar->m_dwStyle & dwDockStyle) ==CBRS_ALIGN_LEFT)
				{
					if (iCont==0)
						return CSize(m_sizeMinFloating.cx,(rectBar.Height()-4));
					else if(iCont>0)
						return CSize(m_sizeMinFloating.cx,(rectBar.Height()/iCont));
				}
				else
				{
					if (iCont==0)
						return CSize((rectBar.Width()-4),m_sizeMinFloating.cy);
					else if(iCont>0)
						return CSize((rectBar.Width()/iCont),m_sizeMinFloating.cy);
				}
			}
		}
	}
	
/*	if (i==1)
		return CSize(m_sizeMinFloating.cx,(rcWin.Height()-4));
	else if(i>1)
		return CSize(m_sizeMinFloating.cx,(rcWin.Height()/i));
	else*/
	return m_sizeMinFloating;

}

//esta funcion calcula el tamaño horizontal de la ventana,no importa si esta
//docking a izquierda o derecha o arriba o abajo.Debemos disponer de un espacio equitativo entre todas
//ventanas que se encuentren docking ya sea en una fila o columna.
CSize CGuiControlBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	//la funcion original toma el ancho o alto dependiendo del sentido que nos
	//indica bHorz.
	ASSERT_VALID(this);
		
	//se modifica esta rutina para que se ajuste correctamente las ventanas docking
	if (IsFloating())
		return m_sizeMinFloating;//CalcWinPos();
	else
	{
		//si bStrerch es TRUE significa que esta ventana no se puede hacer
		//Docking

		if (bStretch)
		{
			if (bHorz)
				return CSize(32767, m_sizeHorz.cy);
			else
				return CSize(m_sizeVert.cx, 32767);
		}
	}



	int Len=GetHiWid();

	//call from GuiDockContext
	if (Len==0)
	{
		if (IsHorz())
			return 	m_sizeHorz;
		else
			return 	m_sizeVert;
	}


	int nWidth = GetWidthMax();
	int nMinSpace=0;//minimo espacio requerido con lo tamaños normales
	int nMinimo=0;  //minimo espacio de los tamaños minimos
	int nRealBars=0;
	int m_First=GetFirstPos();


	for (int nPos = m_First; nPos <= m_Last; nPos++)
	{
		CGuiControlBar* pBar = GetGuiControlBar(nPos,TRUE);
		if (pBar== NULL) continue;
		if (!pBar->IsVisible()) continue;
		if (!pBar->IsKindOf(RUNTIME_CLASS(CGuiControlBar)))
		{
			CPoint pt(GetMessagePos());

			CGuiFrameWnd* mFrame=(CGuiFrameWnd*)m_pDockSite;

				if (IsLeft())
					mFrame->DockControlBar(pBar,mFrame->m_dockLeft);
				if(IsTop())
					mFrame->DockControlBar(pBar,mFrame->m_dockTop);
				if(IsBottom())
					mFrame->DockControlBar(pBar,mFrame->m_dockBottom);
				if(IsRight())
					mFrame->DockControlBar(pBar,mFrame->m_dockRight);


			continue;
		}

		if (IsVert())
			 pBar->m_sizeVert.cx=nWidth;
		else
			pBar->m_sizeHorz.cy=nWidth; //todas se hacen con el mismo ancho
		nMinSpace+=IsVert() ? pBar->m_sizeVert.cy:pBar->m_sizeHorz.cx; //minimo espacio para alinear las barras
		nRealBars++; //cuantas barras realmente existen



	}

	//si el tamaño de las barras en la fila es mayor que
	//el espacio disponible, luego la solucion salomonica es
	//repartir el espacio entre todas.
	if (nRealBars == 1 )
	{
		if (bHorz)
			return m_sizeHorz= CSize(Len,m_sizeHorz.cy);
		else
			return m_sizeVert=CSize(m_sizeVert.cx,Len);

	}



	int niDif=(Len-nMinSpace);//sVert()?8:2);

	if (abs(niDif) !=0)
	{
		BOOL bGrow=FALSE;
		if (niDif > 0)
			bGrow=TRUE;
		niDif=abs(niDif);
		while(niDif > 0)
		{
			for (int nPos = m_First; nPos <= m_Last; nPos++)
			{
				CGuiControlBar* pBar = GetGuiControlBar(nPos);
				if (pBar== NULL) continue;
				if(IsVert())
				{
					if(bGrow)
						pBar->m_sizeVert.cy+=1;
					else
					{

						if (pBar->m_sizeVert.cy-1 < 26)
						{
							niDif--; //bug fixed
							continue;
						}
						pBar->m_sizeVert.cy-=1;

					}
				}
				else
				{
					if(bGrow)
						pBar->m_sizeHorz.cx+=1;
					else
					{

						if (pBar->m_sizeHorz.cx-1 < 26)
						{
							niDif--; //bug fixed
							continue;
						}
						pBar->m_sizeHorz.cx-=1;

					}

				}

				niDif--;
				if(niDif==0) break;
			}

		}

	}

   //--reubicar las ventanas, sin esta rutina nada funciona
  RecalWindowPos();

	if (IsHorz())
		return 	m_sizeHorz;
	else
		return 	m_sizeVert;
}


//esta rutina dispone de la posición en el Dockbar de la pila de  ventanas
void CGuiControlBar::RecalWindowPos()
{
	int m_First=GetFirstPos();
	int m_Last=GetLastPos();
	int m_This=m_pDockBar->FindBar(this);

	AFX_SIZEPARENTPARAMS layout;
	layout.hDWP =::BeginDeferWindowPos( m_Last);

	CRect rcWin=GetDockRect();
	int m_VertPos=0;
	for(int i=m_First; i<= m_Last; i++)
	{
		CGuiControlBar* pBar = GetGuiControlBar(i);
		if (pBar == NULL) continue;
		CRect rcBar;
		pBar->GetWindowRect(rcBar);
		rcBar.OffsetRect(-rcWin.TopLeft());
		if (IsVert())
		{
	 	 if (i==m_First)
		 {
			rcBar.top=0;
		 }
		 else
		 	rcBar.top=m_VertPos;
		}
		else
		{
			if (i==m_First)
				rcBar.left=0;
			else
		 		rcBar.left=m_VertPos;
		}

		//AfxRepositionWindow(&layout,pBar->m_hWnd,&rcBar);
		if (IsVert())
			rcBar.bottom=m_VertPos+pBar->m_sizeVert.cy;
		else
			rcBar.right=m_VertPos+pBar->m_sizeHorz.cx;
		pBar->MoveWindow(rcBar,TRUE);

		if (IsVert())
			m_VertPos+=rcBar.Height();
		else
			m_VertPos+=rcBar.Width();

	}
	ASSERT( layout.hDWP != NULL );
	if( layout.hDWP != NULL )
	{
		VERIFY( ::EndDeferWindowPos(layout.hDWP) );
	}

	//m_pDockSite->DelayRecalcLayout();

}

CRect CGuiControlBar::GetDockRect()
{
	CRect rcWin;
	if(!m_bAutoHide)
	{
		if (IsVert())
			if (IsLeft())
			{
				m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT)->GetWindowRect(rcWin);
				CRect rc11;
				m_pDockSite->GetControlBar(CBRS_ALIGN_LEFT)->GetWindowRect(rc11);
			}
			else
				m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_RIGHT)->GetWindowRect(rcWin);
		else
			if(IsBottom())
				m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_BOTTOM)->GetWindowRect(rcWin);
			else
				m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rcWin);
	}
	else
	{
		if (IsHideVert())
			if (IsHideLeft())
			{
				m_pDockSite->GetControlBar(CBRS_ALIGN_LEFT)->GetWindowRect(rcWin);
				CRect rc11;
				m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT)->GetWindowRect(rc11);

			}
			else
				m_pDockSite->GetControlBar(CBRS_ALIGN_RIGHT)->GetWindowRect(rcWin);
		else
			if(IsHideBottom())
				m_pDockSite->GetControlBar(CBRS_ALIGN_BOTTOM)->GetWindowRect(rcWin);
			else
				m_pDockSite->GetControlBar(CBRS_ALIGN_TOP)->GetWindowRect(rcWin);

	}
	return rcWin;
}

CRect CGuiControlBar::GetDockRectBck()
{
	CRect rcWin=CRect(0,0,0,0);
	if (m_nLastAlingDockingBck==AFX_IDW_DOCKBAR_LEFT)
		m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT)->GetWindowRect(rcWin);
	else if(m_nLastAlingDockingBck==AFX_IDW_DOCKBAR_RIGHT)
		m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_RIGHT)->GetWindowRect(rcWin);
	else if(m_nLastAlingDockingBck==AFX_IDW_DOCKBAR_BOTTOM)
		m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_BOTTOM)->GetWindowRect(rcWin);
	else if(m_nLastAlingDockingBck==AFX_IDW_DOCKBAR_TOP)
			m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rcWin);
	return rcWin;
}



int CGuiControlBar::GetWidthMax()
{
	m_pos=m_pDockBar->FindBar(this);
	m_Last=GetLastPos();
	int nWidth=0;
	for (int nPos = GetFirstPos(); nPos <= m_Last; nPos++)
	{
		CGuiControlBar* pBar = GetGuiControlBar(nPos);
		if (pBar== NULL) continue;
		nWidth=max(nWidth,IsVert() ? pBar->m_sizeVert.cx:pBar->m_sizeHorz.cy);
	}
	return nWidth;
}



CGuiControlBar* CGuiControlBar::GetGuiControlBar(int nPos,BOOL bAll) const
{
	CGuiControlBar* pResult = (CGuiControlBar*)m_pDockBar->m_arrBars[nPos];
	if (bAll==FALSE)
	{
		if (HIWORD(pResult) == NULL) return NULL;
		else if (!pResult->IsVisible()) return NULL;
		else if (!pResult->IsKindOf(RUNTIME_CLASS(CGuiControlBar))) return NULL;
	}
	else
	{
		if (HIWORD(pResult) == NULL)
		return NULL;
	}
	return pResult;
}

//En esta función se calcula el tamaño de la ventana cuando esta flotando
//y gestionar cuando el mouse es presionado en las esquinas.
//#define HTTOPLEFT           13
//#define HTTOPRIGHT          14
//#define HTBOTTOMLEFT        16
//#define HTBOTTOMRIGHT       17


CSize CGuiControlBar::CalcDynamicLayout(int nLength, DWORD nMode)
{

	//	m_pDockSite->DelayRecalcLayout();

	if (IsFloating() && !m_bAutoHide)
	{
			// Enable diagonal arrow cursor for resizing
			//m_sizeVert=m_sizeHorz=CSize(200,200);
			GetParent()->GetParent()->ModifyStyle(MFS_4THICKFRAME/*|WS_CAPTION*/,0);
	}
	
	if (nMode & (LM_HORZDOCK | LM_VERTDOCK) )
	{
		m_pDockSite->DelayRecalcLayout();
		//obligar a reposicionar  la ventana, de lo contrario cuando vuelva de un doble click
		//desde la ventana CMiniFrameWnd queda sin area cliente
		if (!m_bAutoHide)
		{
			SetWindowPos(NULL, 0, 0, 0, 0,
				SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER |
				SWP_NOACTIVATE | SWP_FRAMECHANGED|SWP_NOREDRAW);
		}
	 	return CControlBar::CalcDynamicLayout(nLength, nMode);
	}
	if (nMode & LM_MRUWIDTH && !m_bAutoHide)
		return  m_sizeMinFloating;



	if (nMode & LM_COMMIT && !m_bAutoHide)
		return  m_sizeMinFloating ;


	if (m_bAutoHide)
	{
		CRect rcW;
		CRect rcC;
		CRect rcFrameClient;
		GetClientRect(rcC);
		if (m_nLastAlingDocking ==CBRS_ALIGN_LEFT)
		{
			
			m_pDockSite->GetControlBar(CBRS_ALIGN_LEFT)->GetWindowRect(rcW);
			m_sizeMinFloating.cy=rcW.Height();
		}

		if (m_nLastAlingDocking == CBRS_ALIGN_RIGHT)
		{
			m_pDockSite->GetControlBar(CBRS_ALIGN_RIGHT)->GetWindowRect(rcW);
			m_sizeMinFloating.cy=rcW.Height();
		}
		
		if (m_nLastAlingDocking == CBRS_ALIGN_TOP)
		{
			m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rcW);
			m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rcFrameClient);
			m_sizeMinFloating.cx=rcFrameClient.Width();
		}
		if (m_nLastAlingDocking == CBRS_ALIGN_BOTTOM)
		{
			m_pDockSite->GetControlBar(CBRS_ALIGN_BOTTOM)->GetWindowRect(rcW);
			m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_BOTTOM)->GetWindowRect(rcFrameClient);
			m_sizeMinFloating.cx=rcFrameClient.Width();
		}	

		
		return m_sizeMinFloating;
		
	}
	if (IsFloating() && !m_bAutoHide)
	{

		CRect	rcWin;
		POINT	cpt;
		GetCursorPos(&cpt);
		GetParent()->GetParent()->GetWindowRect(&rcWin);
		int nXOffset=0;int nYOffset=0;
		switch (m_pDockContext->m_nHitTest)
		{

			//------------------------------------------------------------------
			case HTLEFT:
				m_pDockContext->m_rectFrameDragHorz= rcWin;
				m_pDockContext->m_rectFrameDragHorz.left = cpt.x;
				m_sizeMinFloating.cx = max(rcWin.right - cpt.x,32)-4 ;
				m_sizeMinFloating.cy = max((rcWin.bottom -rcWin.top)-nGapGripper-5,32)+2 ;
				return m_sizeMinFloating;
			break;
			case HTTOP:
				m_pDockContext->m_rectFrameDragHorz=rcWin;
				m_pDockContext->m_rectFrameDragHorz.top = cpt.y;
				m_sizeMinFloating.cx = max(rcWin.right-rcWin.left-2,32)-4 ;
				m_sizeMinFloating.cy = max((rcWin.bottom -nGapGripper-cpt.y-3),32) ;
				return m_sizeMinFloating;
			break;
			case HTRIGHT:
				m_pDockContext->m_rectFrameDragHorz=rcWin;
				m_pDockContext->m_rectFrameDragHorz.right = cpt.x;
				m_sizeMinFloating.cy = max(rcWin.bottom -rcWin.top-nGapGripper-3,32) ;
				m_sizeMinFloating.cx = max(cpt.x-rcWin.left-4,32);
				return m_sizeMinFloating;
			break;
			case HTBOTTOM:
				m_pDockContext->m_rectFrameDragHorz=rcWin;
				m_sizeMinFloating.cy = max(cpt.y-rcWin.top -nGapGripper-3,32) ;
				m_sizeMinFloating.cx = max(rcWin.right-rcWin.left-2,32)-4 ;
				m_pDockContext->m_rectFrameDragHorz.bottom = cpt.y-4;
				return m_sizeMinFloating;
				break;
			case HTTOPLEFT:
				//---------------------------------------------------------
			//En este caso crece la ventana a izquierda y hacia arriba
			//izquierda incrementa cx y top incrementa cy
				m_sizeMinFloating.cx = max(rcWin.right - cpt.x,32)-3 ;
				m_sizeMinFloating.cy = max(rcWin.bottom -nGapGripper-cpt.y,32)-2 ;
				m_pDockContext->m_rectFrameDragHorz.top = cpt.y-1;
				m_pDockContext->m_rectFrameDragHorz.left = cpt.x-2;

				return m_sizeMinFloating;
				break;
			case HTTOPRIGHT:
				m_sizeMinFloating.cx = max(cpt.x-rcWin.left,32)-4 ;
				m_sizeMinFloating.cy = max(rcWin.bottom -nGapGripper-cpt.y,32)-2 ;
				m_pDockContext->m_rectFrameDragHorz.top = cpt.y-1;
				m_pDockContext->m_rectFrameDragHorz.right = cpt.x-2;
				return m_sizeMinFloating;
				break;
			case HTBOTTOMLEFT:
				m_sizeMinFloating.cx = max(rcWin.right - cpt.x,32)-4;
				m_sizeMinFloating.cy = max(cpt.y-rcWin.top -nGapGripper,32)-2 ;
				m_pDockContext->m_rectFrameDragHorz.top = rcWin.top;
				m_pDockContext->m_rectFrameDragHorz.bottom = cpt.y-1;
				m_pDockContext->m_rectFrameDragHorz.left = cpt.x-2;
				return m_sizeMinFloating;
				break;
			case HTBOTTOMRIGHT:
				m_sizeMinFloating.cx = max(cpt.x-rcWin.left,32);
				m_sizeMinFloating.cy = max(cpt.y-rcWin.top -nGapGripper,32) ;
				m_pDockContext->m_rectFrameDragHorz.top = rcWin.top;
				m_pDockContext->m_rectFrameDragHorz.bottom = cpt.y+1;
				m_pDockContext->m_rectFrameDragHorz.right = cpt.x+2;
				return m_sizeMinFloating;
				break;



		}

	}

	if(nMode & LM_LENGTHY)
		 m_sizeMinFloating.cy = max(nLength,32);
	else
	     m_sizeMinFloating.cx = max(nLength,32);
	return m_sizeMinFloating;
}

void CGuiControlBar::ScrollOff()
{
	
	ScrollOnEfect(FALSE);
	GetDockingFrame()->ShowControlBar(this, FALSE, FALSE);
	
	

}

void CGuiControlBar::ScrollOn()
{
	m_sizeMinFloating1=m_sizeMinFloating;
	GetDockingFrame()->ShowControlBar(this, TRUE, TRUE);
	if (m_nLastAlingDocking ==CBRS_ALIGN_LEFT || m_nLastAlingDocking == CBRS_ALIGN_RIGHT)
	{
		m_nSizeMed= m_sizeMinFloating.cx/GUI_NUMITER;
		m_sizeMinFloating.cx=0;
	}
	else
	{
		m_nSizeMed= m_sizeMinFloating.cy/GUI_NUMITER;
		m_sizeMinFloating.cy=0;
	}
	ScrollOnEfect(TRUE);
	
	
}

void CGuiControlBar::ScrollOnEfect(BOOL on)
{
	
	CRect rcW;
	CRect rcC;
	CRect rcFrameClient;
	CRect rcWinScroll;
	GetClientRect(rcC);
	GetWindowRect(rcWinScroll);
	CDockBar* pDockBar = m_pDockBar;
	CMiniDockFrameWnd* pDockFrame =	(CMiniDockFrameWnd*)pDockBar->GetParent();
	CFrameWnd*		pFrame = reinterpret_cast<CFrameWnd*>(AfxGetMainWnd());

	CRect rc1;
	m_bComplete=FALSE;	
		
		
	

	long iWidth80;
	long iWidth20;

	long iGUI_NUMITER=GUI_NUMITER;
	

	if (IsHideVert())
	{
		iWidth80=m_sizeMinFloating1.cx/iGUI_NUMITER;
		iWidth20=m_sizeMinFloating1.cx/iGUI_NUMITER;
	}
	else
	{
		iWidth80=m_sizeMinFloating1.cy/iGUI_NUMITER;
		iWidth20=m_sizeMinFloating1.cy/iGUI_NUMITER;
	}
	
		
	for(int i=0; i< iGUI_NUMITER; i++)
	{
	
		if (IsHideVert())
		{
			if (IsHideLeft())
				m_pDockSite->GetControlBar(CBRS_ALIGN_LEFT)->GetWindowRect(rcW);
			else
				m_pDockSite->GetControlBar(CBRS_ALIGN_RIGHT)->GetWindowRect(rcW);	
		}
		else
		{
			if(IsHideBottom())
			{
				m_pDockSite->GetControlBar(CBRS_ALIGN_BOTTOM)->GetWindowRect(rcW);
				m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_BOTTOM)->GetWindowRect(rcFrameClient);
				m_sizeMinFloating.cx=rcFrameClient.Width();
				}
			else
			{
				
				m_pDockSite->GetControlBar(CBRS_ALIGN_TOP)->GetWindowRect(rcW);
				m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rcFrameClient);
				m_sizeMinFloating.cx=rcFrameClient.Width();
			}

		}
		
		if (on)
		{
			if (IsHideVert())
				m_sizeMinFloating.cx+=(long)iWidth80;
			else
				m_sizeMinFloating.cy+=(long)iWidth80;
		}
		else
		{
			if (IsHideVert())
				m_sizeMinFloating.cx-=(long)iWidth80;
			else
				m_sizeMinFloating.cy-=(long)iWidth80;	

		}

		if (IsHideVert())
			m_sizeMinFloating.cy=rcW.Height()-(rcW.Height()+m_pDockSite->GetControlBar(CBRS_ALIGN_TOP)->IsVisible()?24:0);
		
		
		
		if (IsHideVert())
		{
			if (IsHideLeft())
				rc1.left=rcW.right+24;
			else
				rc1.left=rcW.left-(m_sizeMinFloating.cx+26);
			rc1.top=rcW.top;
			rc1.right=rc1.left+m_sizeMinFloating.cx;
			rc1.bottom=rc1.top+m_sizeMinFloating.cy;
		
		}			
		else
		{
			if (IsHideBottom())
				rc1.top=rcW.top-(m_sizeMinFloating.cy+26);
			else
				rc1.top=rcW.bottom+26;
			rc1.left=rcFrameClient.left;
			rc1.right=rc1.left+m_sizeMinFloating.cx;
			rc1.bottom=rc1.top+m_sizeMinFloating.cy;
		
		}
		
		pDockFrame->SetWindowPos(reinterpret_cast<CWnd*>(HWND_TOP),rc1.left,rc1.top, rc1.Width(),rc1.Height(),SWP_HIDEWINDOW);
		
		CRect rcInvalidateClient(rc1);
		MapWindowPoints(NULL,&rcInvalidateClient);
		
		pDockFrame->RecalcLayout(TRUE);
		
		pDockFrame->UpdateWindow();	
		pDockFrame->SetWindowPos(reinterpret_cast<CWnd*>(HWND_TOP), rc1.left,rc1.top, rc1.Width(),rc1.Height(),
		SWP_SHOWWINDOW|SWP_NOACTIVATE);

		RedrawWindow(&rcInvalidateClient,NULL, RDW_UPDATENOW);
		if(!on)
		{
			pFrame->RecalcLayout(TRUE);
			pFrame->UpdateWindow();
			pFrame->RedrawWindow(&rcInvalidateClient,NULL,RDW_UPDATENOW);
		}
			
		
		//Sleep(10);
		
	}
	m_bComplete=TRUE;
	m_sizeMinFloating=m_sizeMinFloating1;
	if (!on)
	{
		pDockFrame->SetWindowPos(reinterpret_cast<CWnd*>(HWND_TOP),rc1.left,rc1.top, rc1.Width(),rc1.Height(),SWP_HIDEWINDOW);
	}
	else
	{
		pDockFrame->RecalcLayout(TRUE);
		pDockFrame->UpdateWindow();	
	}




}


void CGuiControlBar::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	

	if (nIDEvent == 1)
	{
		if (m_stateBtn==NORMAL) return;
		CRect rc;
		CPoint pt(GetMessagePos());

		CRect rcT=m_rcCloseBtn;
		ClientToScreen(rcT);
		pt.y+=23;
		pt.x+=5;
		if (!rcT.PtInRect(pt))
		{
			m_stateBtn=NORMAL;
			KillTimer(1);
			SendMessage(WM_NCPAINT);
		}
	}

	if (nIDEvent == 2)
	{
		if (m_stateAHBtn==NORMAL) return;
		CRect rc;
		CPoint pt(GetMessagePos());

		CRect rcT=m_rcAutoHideBtn;
		ClientToScreen(rcT);
		pt.y+=23;
		pt.x+=5;
		if (!rcT.PtInRect(pt))
		{
			m_stateAHBtn=NORMAL;
			KillTimer(2);
			SendMessage(WM_NCPAINT);
		}
	}

	
	CControlBar::OnTimer(nIDEvent);
}

void CGuiControlBar::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_pDockBar != NULL)
	{
		ActiveCaption();
	//	m_pDockContext->ToggleDocking();
	}
	else
			CWnd::OnLButtonDblClk(nFlags, point);
}
void CGuiControlBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (m_pDockBar != NULL)
    {
        // start the drag
        ClientToScreen(&point);
       // m_pDockContext->StartDrag(point);
    }
    else
		CControlBar::OnLButtonDown(nFlags, point);
}

void CGuiControlBar::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (m_pDockBar != NULL)
    {
        // start the drag
        ReleaseCapture();
        m_pDockSite->UnlockWindowUpdate();

    }
    else
		CControlBar::OnLButtonDown(nFlags, point);



}

void CGuiControlBar::OnMouseMove( UINT nHitTest, CPoint point)
{

	if(m_bTracking)
	{
		if (GetCapture() != this)
		{
			//StopTracking(FALSE);
			m_bTracking=FALSE;
		}

		OnInvertTracker(m_rcBorder);
		//nuevos tamaños de la ventana
		if (IsVert() || IsHideVert())
		{
			if (m_SideMove==HTLEFT || m_SideMove==HTRIGHT)
			{
				m_rcBorder.left=point.x;
				m_rcBorder.right=m_rcBorder.left+4;

			}
			else
			{
				m_rcBorder.top=point.y+26;
				m_rcBorder.bottom=m_rcBorder.top+4;

			}
		}
		else
		{
			if (m_SideMove==HTBOTTOM || m_SideMove==HTTOP)
			{
				m_rcBorder.top=point.y+26;
				m_rcBorder.bottom=m_rcBorder.top+4;

			}
			else
			{
				m_rcBorder.left=point.x;
				m_rcBorder.right=m_rcBorder.left+4;

			}
		}

		//--------------------------------------------------
		//se hacen iguales todos los tamaños
		//if(!m_bAutoHide)
		{
			ClientToScreen(&point);
			m_pDockSite->ScreenToClient(&point);
		}
		m_ptActualPos=point;

		OnInvertTracker(m_rcBorder);
		//SetEqualWidth();
		//-----------------------------------------------



	}

}


//depende de la posicion se hace igual el tamanio del ancho o alto
void CGuiControlBar::SetEqualWidth()
{

	int nFirstPos=GetFirstPos();
	for (int nPos = nFirstPos; nPos <= m_Last; nPos++)
	{
		CGuiControlBar* pBar = GetGuiControlBar(nPos);
		if (pBar== NULL) continue;
		if (IsHorz())
			pBar->m_sizeHorz.cy=m_sizeHorz.cy;//rcDockBar.Height();
		else
			pBar->m_sizeVert.cx=m_sizeVert.cx;
	}
}

int CGuiControlBar::GetHiWid()
{
	CRect rcWin;
	CMenuDockBar* pDock=(CMenuDockBar*)m_pDockBar;
	rcWin=pDock->m_rectLayout; //the real size
	if(IsVert())
		return rcWin.Height();
	else
		return rcWin.Width();

}


//espero que funcione el truco
//la idea es trabajar con coordenadas screen las dimensiones de los bordes del
//dockBar, mas no con los movimientos internos.
void CGuiControlBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CPoint ptTemp=point;
	ClientToScreen(&ptTemp);
	CRect rcFrame;
	CDockBar* pDockBar = m_pDockBar;
	BOOL isMDI=FALSE;		
	if (GetParentFrame()->IsKindOf(RUNTIME_CLASS(CGuiMDIFrame)))
		isMDI=TRUE;
    
	if (m_bAutoHide)
	{
		if (isMDI)
		 ((CGuiMDIFrame*)GetParentFrame())->GetParent()->GetClientRect(rcFrame);
		else 
		 ((CGuiFrameWnd*)GetParentFrame())->GetParent()->GetClientRect(rcFrame);
	}
	else
	{
		if (isMDI)
		 ((CGuiMDIFrame*)GetParentFrame())->GetClientRect(rcFrame);
		else 
		 ((CGuiFrameWnd*)GetParentFrame())->GetClientRect(rcFrame);
	}

	
	if (m_bTracking)
	{
		ReleaseCapture();
		m_bTracking=FALSE;
		OnInvertTracker(m_rcBorder);
		m_pDockSite->UnlockWindowUpdate();

		if (ptTemp ==m_ptStartPos) return;
		
		if (IsVert())
		{
			if (m_SideMove==HTLEFT)
				m_sizeVert.cx-=point.x;
			else if(m_SideMove==HTRIGHT)
				m_sizeVert.cx=point.x;
			else if(m_SideMove==HTTOP)
				AjustReDinSize(point);
		}
		else if (IsHorz())
		{
		   if (m_SideMove==HTBOTTOM)
			   {
				if (point.y < 0)
					m_sizeHorz.cy+=abs(point.y);
				else
					m_sizeHorz.cy=point.y;
			}

		   else if (m_SideMove==HTTOP)
		   {
			  if (point.y < 0)
				  m_sizeHorz.cy+=abs(point.y)-12;
			  else
				  m_sizeHorz.cy-=abs(point.y)+12;
		   }
			else if (m_SideMove==HTRIGHT)
		   	   AjustReDinSize(point);

		}

		if (IsHideVert()== TRUE)
		{

			
			if (IsHideRight())
			{
				
				if(point.x<0)
				   m_sizeMinFloating.cx+=abs(point.x);
				else
				   m_sizeMinFloating.cx-=point.x;

				if (m_sizeMinFloating.cx < (rcFrame.Width()-50) && m_sizeMinFloating.cx > 20)
					m_sizeMinFloating1=m_sizeMinFloating;
				else
				{
					m_sizeMinFloating=m_sizeMinFloating1;
					return;
				}
				CRect rc1;
				CMiniDockFrameWnd* pDockFrame =	(CMiniDockFrameWnd*)pDockBar->GetParent();
				pDockFrame->GetWindowRect(rc1);
			
				if(point.x<0)
					rc1.right+=point.x;
				else
					rc1.right-=point.x;
				ClientToScreen(&point);
				pDockFrame->SetWindowPos(reinterpret_cast<CWnd*>(HWND_TOP),point.x-5,rc1.top, rc1.Width(),rc1.Height(),NULL);
			}
			else
			{
				m_sizeMinFloating.cx=point.x+8;
				if (m_sizeMinFloating.cx < (rcFrame.Width()-50) && m_sizeMinFloating.cx > 20)
					m_sizeMinFloating1=m_sizeMinFloating;
				else
					m_sizeMinFloating=m_sizeMinFloating1;
				m_sizeMinFloating1=m_sizeMinFloating;
				GetParentFrame()->RecalcLayout(TRUE);
			}
			return ;
		}
		if (IsHideTop() ||	IsHideBottom())
		{
			if(IsHideTop())
			{
				m_sizeMinFloating.cy=point.y+25;
				if (m_sizeMinFloating.cy < (rcFrame.Height()-100) && m_sizeMinFloating.cy > 20)
					m_sizeMinFloating1=m_sizeMinFloating;
				else
				{
					m_sizeMinFloating=m_sizeMinFloating1;
					return;
				}
				
				m_pDockSite->RecalcLayout();
				GetParentFrame()->RecalcLayout(TRUE);
			}
			else
			{
				if(point.y<0)
				   m_sizeMinFloating.cy+=abs(point.y);
				else
				   m_sizeMinFloating.cy-=point.y;
				if (m_sizeMinFloating.cy < (rcFrame.Height()-100) && m_sizeMinFloating.cy > 20)
					m_sizeMinFloating1=m_sizeMinFloating;
				else
				{
					m_sizeMinFloating=m_sizeMinFloating1;
					return ;
				}
				CRect rc1;
				CDockBar* pDockBar = m_pDockBar;
				CMiniDockFrameWnd* pDockFrame =	(CMiniDockFrameWnd*)pDockBar->GetParent();
				pDockFrame->GetWindowRect(rc1);
			
				if(point.y<0)
					rc1.top+=abs(point.y);
				else
					rc1.top-=point.y;
				ClientToScreen(&point);
					//m_sizeMinFloating.cx=rc1.Width();
					//GetDockingFrame()->FloatControlBar(this,rc1.TopLeft());
				pDockFrame->SetWindowPos(reinterpret_cast<CWnd*>(HWND_TOP),rc1.left,point.y, rc1.Width(),rc1.Height(),NULL);

			}
			
			return;

		}
		

		if (!m_bAutoHide)
		SetEqualWidth();


	}
		
		if(!m_bAutoHide)
			m_pDockSite->RecalcLayout();


}

//ajusta las ventanas a redimencionarlas verticalmente
//se decrementa las anteriores ventanas a la actual y se
//incrementan las posteriores.
void CGuiControlBar::AjustReDinSize(CPoint point)
{

	int nFirstPos=GetFirstPos();
	int nLastPos=GetLastPos();
	int m_ThisPos=m_pDockBar->FindBar(this);


	ClientToScreen(&point);

	//si la diferencia es negativa esta barra crece la anterior a esta disminuye
	int nDif=0;
	BOOL bGrow=FALSE;

	if (IsVert())
	{
		 nDif=m_ptStartPos.y- point.y;
		 if (nDif > 0)
			bGrow=TRUE;

		 if (bGrow)
                m_sizeVert.cy+=abs(nDif)+4;
		 else
				m_sizeVert.cy-=abs(nDif);

	 	 if (nFirstPos == m_ThisPos)
			return;

	}
	else
	{
		 nDif=m_ptStartPos.x- point.x;
		 if (nDif < 0)
			bGrow=TRUE;

		 if (bGrow)
				m_sizeHorz.cx+=abs(nDif);
			else
				m_sizeHorz.cx-=abs(nDif);

         if (nLastPos == m_ThisPos)
			return;
	}


	if (IsVert())
		AjustVert(bGrow,nDif);
	else
		AjustHorz(bGrow,nDif);

	RecalWindowPos();



}


void CGuiControlBar::AjustVert(BOOL bGrow,int nDif)
{
	int nFirstPos=GetFirstPos();
	int nLastPos=GetLastPos();
	int m_ThisPos=m_pDockBar->FindBar(this);

	if(m_SideMove==HTTOP)
	{

		//Esta ventana crece las anteriores reducen su tamaño

		if (bGrow)
			{
				for (int i=m_ThisPos-1; i > 0; i--)
				{
					CGuiControlBar* pBar = GetGuiControlBar(i);
					if (pBar== NULL) return;
					if(IsVert())
					{
						if (pBar->m_sizeVert.cy-abs(nDif) < pBar->m_sizeMinV.cy)
						{
							pBar->m_sizeVert.cy=pBar->m_sizeMinV.cy;
							continue;
						}
						else
						{
							pBar->m_sizeVert.cy-=abs(nDif);
							break;
						}
					}
				}//for

			}//bGrow
			else	//este disminuye la anterior crece
			{
				if (m_ThisPos-1 > 0)
				{
					CGuiControlBar* pBar = GetGuiControlBar(m_ThisPos-1);
					if (pBar== NULL) return;
					pBar->m_sizeVert.cy+=abs(nDif);
					if(m_sizeVert.cy > m_sizeMinV.cy)
						return;
					else
					  pBar->m_sizeVert.cy-=m_sizeMinV.cy;
				}
				for (int i=m_ThisPos+1; i >= m_Last; i++)
				{
					CGuiControlBar* pBar = GetGuiControlBar(i);
					if (pBar== NULL) return;
					if(IsVert())
					{
						if (pBar->m_sizeVert.cy-abs(nDif) < pBar->m_sizeMinV.cy)
							continue;
						else
						{
							pBar->m_sizeVert.cy-=abs(nDif);
							return;
						}
					}
				}//for
			}
	}
}


void CGuiControlBar::AjustHorz(BOOL bGrow,int nDif)
{
	int nFirstPos=GetFirstPos();
	int nLastPos=GetLastPos();
	int m_ThisPos=m_pDockBar->FindBar(this);

	if(m_SideMove==HTRIGHT)
	{

		//Esta ventana crece las anteriores reducen su tamaño

		if (bGrow)
			{
				for (int i=m_ThisPos+1; i <= nLastPos; i++)
				{
					CGuiControlBar* pBar = GetGuiControlBar(i);
					if (pBar== NULL) return;
					if(IsHorz())
					{
						if (pBar->m_sizeHorz.cx-abs(nDif) < pBar->m_sizeMinH.cx)
						{
							pBar->m_sizeHorz.cx=pBar->m_sizeMinH.cx;
							continue;
						}
						else
						{
							pBar->m_sizeHorz.cx-=abs(nDif);
							break;
						}
					}
				}//for

			}//bGrow
			else	//este disminuye la anterior crece
			{
			   if (m_ThisPos+1 <= m_Last)
				{
					CGuiControlBar* pBar = GetGuiControlBar(m_ThisPos+1);
					if (pBar== NULL) return;
					pBar->m_sizeHorz.cx+=abs(nDif);
					if(m_sizeHorz.cx > m_sizeMinH.cx)
						return;
					else
					  pBar->m_sizeHorz.cx+=abs(nDif);
				}


				for (int i=m_ThisPos-1; i >0; i--)
				{
					CGuiControlBar* pBar = GetGuiControlBar(i);
					if (pBar== NULL) return;
					if(IsHorz())
					{
						if (pBar->m_sizeHorz.cx-abs(nDif) < pBar->m_sizeMinH.cx)
							continue;
						else
						{
							pBar->m_sizeHorz.cx-=abs(nDif);
							return;
						}
					}
				}//for
			}
	}


}


//----------------------------------------------------
//OnActiveWindow retira o asigna el foco a la ventana

void CGuiControlBar::OnActiveWindow()
{
	POSITION pos = m_pDockSite->m_listControlBars.GetHeadPosition();
	while (pos != NULL)
	{
		CDockBar* pDockBar = (CDockBar*)m_pDockSite->m_listControlBars.GetNext(pos);
		if (pDockBar->IsDockBar() && pDockBar->IsWindowVisible() &&
			(!pDockBar->m_bFloating || m_bAutoHide))
			{
				int nNumBars=(int)pDockBar->m_arrBars.GetSize();
				for(int i=0; i< nNumBars;i++)
				{
					CGuiControlBar* pBar = (CGuiControlBar*) pDockBar->m_arrBars[i];
					if (HIWORD(pBar) == NULL) continue;
					if (!pBar->IsVisible()) continue;
					if (!pBar->IsKindOf(RUNTIME_CLASS(CGuiControlBar))) continue;
					if (pBar != this)
					{
						pBar->m_bOldActive=FALSE;
						pBar->m_bActive=FALSE;
						pBar->m_bForcepaint=TRUE;
						pBar->SendMessage(WM_NCPAINT);
						pBar->m_bForcepaint=FALSE;
					}
					else
					{
						m_bOldActive=m_bActive;
						m_bActive=TRUE;
						m_bForcepaint=TRUE;
						SendMessage(WM_NCPAINT);
						m_bForcepaint=FALSE;


					}
				}
			}
	}
}


void CGuiControlBar::ActiveCaption()
{
	CWnd* pFocus=SetFocus();
	if(pFocus->GetSafeHwnd())
		IsChild(pFocus);
	m_bForcepaint=TRUE;
	OnActiveWindow();
	m_bForcepaint=FALSE;


}


void CGuiControlBar::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bTracking /*|| IsFloating()*/)
        return;
//	ScreenToScreen (&point);
	CMenu m_menu;
	if (m_MenuContext!=NULL)
	{
		m_menu.LoadMenu(m_MenuContext);
		CMenu* m_SubMenu = m_menu.GetSubMenu(0);
		m_SubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,
				point.x, point.y-2, AfxGetMainWnd());
		Invalidate();
		UpdateWindow();
	}

	CWnd::OnNcLButtonDown(nHitTest, point);
}

void CGuiControlBar::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bTracking /*|| IsFloating()*/)
        return;



	m_ptStartPos=point;
	if( nHitTest == HTCAPTION || nHitTest == HTCLOSE || nHitTest == HTPIN)
		ActiveCaption();
	//---------para el boton----
	if( nHitTest == HTCLOSE)
	{
		m_stateBtn=PRESS;
		SendMessage(WM_NCPAINT);
		/*SetTimer(1,100,0);
		CRect rc;

		CGuiMiniFrameWnd* p = new CGuiMiniFrameWnd;
		if (!p->Create(this,this,CRect(100,100,300,400),
			_T("Title"),300))
		{

		}*/
		return;
	}
	if( nHitTest == HTPIN)
	{
		m_stateAHBtn=PRESS;
		SendMessage(WM_NCPAINT);
		/*SetTimer(1,100,0);
		CRect rc;

		CGuiMiniFrameWnd* p = new CGuiMiniFrameWnd;
		if (!p->Create(this,this,CRect(100,100,300,400),
			_T("Title"),300))
		{

		}*/
		return;
	}
	//--------------------------

	if (m_pDockBar != NULL )
	{

		if (HTCAPTION == nHitTest && !m_bAutoHide)
		{
			m_pDockContext->StartDrag(point);
			m_sizeHorzt=m_sizeHorz;
			m_sizeVertt=m_sizeVert;
		}
		if(!m_bTracking)
		{
			if(m_rcBorder.PtInRect(point))
			{

				m_pDockSite->LockWindowUpdate();
				OnInvertTracker(m_rcBorder);

				m_ptStartPos=point;
				SetCapture();
				SetFocus();

				m_bTracking=TRUE;
				m_sizeHorzt=m_sizeHorz;
				m_sizeVertt=m_sizeVert;

			}
		}
	}
	//other bug fixed
//	CWnd::OnNcLButtonDown(nHitTest, point);

}

void CGuiControlBar::InitAutoHide()
{

	if (m_bAutoHide==TRUE)
	{
		m_stateBtn=NORMAL;
		m_sizeMinFloatingBck=m_sizeMinFloating;	
		Porc=0.0;
		KillTimer(1);
		CGuiMDIFrame* pB=(CGuiMDIFrame*)pMf;
		pB->FloatControlBar(this,CPoint(400,400));
		if(IsHideRight())
		{
			m_nLastAlingDocking=CBRS_ALIGN_RIGHT;
 			pB->m_dockHideRight.AddToolBars(this);
			
		}
		if(IsHideLeft())
		{
			m_nLastAlingDocking=CBRS_ALIGN_LEFT;
			pB->m_dockHideLeft.AddToolBars(this);
			
		}
		if(IsHideTop())
		{
			m_nLastAlingDocking=CBRS_ALIGN_TOP;
			pB->m_dockHideTop.AddToolBars(this);
			
		}
		if(IsHideBottom())
		{
			m_nLastAlingDocking=CBRS_ALIGN_BOTTOM;
			pB->m_dockHideBottom.AddToolBars(this);

		}


		GetDockingFrame()->ShowControlBar(this, FALSE, FALSE);
		GetDockingFrame()->FloatControlBar(this,CPoint(400,400));
		GetParent()->GetParent()->ModifyStyle(WS_CAPTION,0);
	}
	else
		m_IsLoadDocking=FALSE;
}

void CGuiControlBar::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	//------------------ para el boton
	CRect rcT=m_rcCloseBtn;
	ClientToScreen(rcT);
	point.y+=23;
	point.x+=5;
	if (rcT.PtInRect(point))
	{

		if (m_stateBtn ==PRESS)
		{
			m_stateBtn=NORMAL;
			KillTimer(1);
			if (m_bAutoHide)
			{
				m_bAutoHide=FALSE;
				GetParent()->GetParent()->ModifyStyle(WS_CAPTION,1);
				CGuiMDIFrame* pB;
				CGuiFrameWnd* pB1;
				BOOL isMDI=FALSE;
			
				if (pMf->IsKindOf(RUNTIME_CLASS(CGuiMDIFrame)))
					isMDI=TRUE;

				if (isMDI)
					 pB=(CGuiMDIFrame*)pMf;
				else 
					 pB1= (CGuiFrameWnd*)pMf;


				
				if(m_nLastAlingDocking==CBRS_ALIGN_RIGHT)
				{
					if (isMDI)
					{
						pB->m_dockHideRight.DeleteToolBars(this);
						pB->DockControlBar(this, AFX_IDW_DOCKBAR_RIGHT);
					}
					else
					{
						pB1->m_dockHideRight.DeleteToolBars(this);
						pB1->DockControlBar(this, AFX_IDW_DOCKBAR_RIGHT);
					}
					
				}
				if(m_nLastAlingDocking==CBRS_ALIGN_LEFT)
				{
					if (isMDI)
					{
						pB->m_dockHideLeft.DeleteToolBars(this);
						pB->DockControlBar(this, AFX_IDW_DOCKBAR_LEFT);
					}
					else
					{
						pB1->m_dockHideLeft.DeleteToolBars(this);
						pB1->DockControlBar(this, AFX_IDW_DOCKBAR_LEFT);
					}
					
				}
				if(m_nLastAlingDocking==CBRS_ALIGN_TOP)
				{
					if (isMDI)
					{
						pB->m_dockHideTop.DeleteToolBars(this);
						pB->DockControlBar(this, AFX_IDW_DOCKBAR_TOP);
					}
					else
					{
						pB1->m_dockHideTop.DeleteToolBars(this);
						pB1->DockControlBar(this, AFX_IDW_DOCKBAR_TOP);
					}
					
				}
				if(m_nLastAlingDocking==CBRS_ALIGN_BOTTOM)
				{
					if (isMDI)
					{
						pB->m_dockHideBottom.DeleteToolBars(this);
						pB->DockControlBar(this, AFX_IDW_DOCKBAR_BOTTOM);
					}
					else
					{
						pB1->m_dockHideBottom.DeleteToolBars(this);
						pB1->DockControlBar(this, AFX_IDW_DOCKBAR_BOTTOM);
					}

				}
				m_nLastAlingDocking=0;
			//	SendMessage(WM_NCLBUTTONDBLCLK);

			}
			//--------------------------------------------------------------
			GetDockingFrame()->ShowControlBar(this, FALSE, FALSE);
		}
		SendMessage(WM_NCPAINT);
		m_pDockSite->RecalcLayout();

		return;

	}

	//ojo guardar el aling de la ventana

	rcT=m_rcAutoHideBtn;
	ClientToScreen(rcT);
	if (rcT.PtInRect(point))
	{

		if (m_stateAHBtn ==PRESS)
		{

			if (m_bAutoHide)
			{
				CGuiMDIFrame* pB;
				CGuiFrameWnd* pB1;
				
				BOOL isMDI=FALSE;

				m_bAutoHide=FALSE;
				m_sizeMinFloating=m_sizeMinFloatingBck;
				GetParent()->GetParent()->ModifyStyle(WS_CAPTION,1);
				
				pB=(CGuiMDIFrame*)pMf;
				
				if (pMf->IsKindOf(RUNTIME_CLASS(CGuiMDIFrame)))
					isMDI=TRUE;

				if (isMDI)
					 pB=(CGuiMDIFrame*)pMf;
				else 
					 pB1= (CGuiFrameWnd*)pMf;

				if(m_nLastAlingDocking==CBRS_ALIGN_RIGHT)
				{
					if (isMDI)
					{
						pB->m_dockHideRight.DeleteToolBars(this);
						pB->DockControlBar(this, AFX_IDW_DOCKBAR_RIGHT);
					}
					else
					{
						pB1->m_dockHideRight.DeleteToolBars(this);
						pB1->DockControlBar(this, AFX_IDW_DOCKBAR_RIGHT);
					}
					
				}
				if(m_nLastAlingDocking==CBRS_ALIGN_LEFT)
				{
					if (isMDI)
					{
						pB->m_dockHideLeft.DeleteToolBars(this);
						pB->DockControlBar(this, AFX_IDW_DOCKBAR_LEFT);
					}
					else
					{
						pB1->m_dockHideLeft.DeleteToolBars(this);
						pB1->DockControlBar(this, AFX_IDW_DOCKBAR_LEFT);
					}
					
				}
				if(m_nLastAlingDocking==CBRS_ALIGN_TOP)
				{
					if (isMDI)
					{
						pB->m_dockHideTop.DeleteToolBars(this);
						pB->DockControlBar(this, AFX_IDW_DOCKBAR_TOP);
					}
					else
					{
						pB1->m_dockHideTop.DeleteToolBars(this);
						pB1->DockControlBar(this, AFX_IDW_DOCKBAR_TOP);
					}
					
				}
				if(m_nLastAlingDocking==CBRS_ALIGN_BOTTOM)
				{
					if (isMDI)
					{
						pB->m_dockHideBottom.DeleteToolBars(this);
						pB->DockControlBar(this, AFX_IDW_DOCKBAR_BOTTOM);
					}
					else
					{
						pB1->m_dockHideBottom.DeleteToolBars(this);
						pB1->DockControlBar(this, AFX_IDW_DOCKBAR_BOTTOM);
						
					}

				}
				
				GetDockingFrame()->ShowControlBar(this, TRUE, TRUE);
				m_nLastAlingDocking=0;
			//	SendMessage(WM_NCLBUTTONDBLCLK);

			}
			else
			{
				m_sizeMinFloatingBck=m_sizeMinFloating;
				m_stateBtn=NORMAL;
				m_bAutoHide=TRUE;
				Porc=0.0;
				KillTimer(1);
				CGuiMDIFrame* pB;
				CGuiFrameWnd* pB1;
				pMf=GetParentFrame();
				BOOL isMDI=FALSE;
				
				if (pMf->IsKindOf(RUNTIME_CLASS(CGuiMDIFrame)))
					isMDI=TRUE;

				if (isMDI)
					 pB=(CGuiMDIFrame*)pMf;
				else 
					 pB1= (CGuiFrameWnd*)pMf;

				if(IsRight())
				{
					m_nLastAlingDocking=CBRS_ALIGN_RIGHT;
					if (isMDI)
						pB->m_dockHideRight.AddToolBars(this);
					else
						pB1->m_dockHideRight.AddToolBars(this);
				}
				if(IsLeft())
				{
					m_nLastAlingDocking=CBRS_ALIGN_LEFT;
					if (isMDI)
						pB->m_dockHideLeft.AddToolBars(this);
					else
						pB1->m_dockHideLeft.AddToolBars(this);
					
				}
				if(IsTop())
				{
					m_nLastAlingDocking=CBRS_ALIGN_TOP;
					if (isMDI)
						pB->m_dockHideTop.AddToolBars(this);
					else
						pB1->m_dockHideTop.AddToolBars(this);
					
				}
				if(IsBottom())
				{
					m_nLastAlingDocking=CBRS_ALIGN_BOTTOM;
					if (isMDI)
						pB->m_dockHideBottom.AddToolBars(this);
					else
						pB1->m_dockHideBottom.AddToolBars(this);

				}

			//	if (isMDI)
				{
					GetDockingFrame()->ShowControlBar(this, FALSE, FALSE);
					GetDockingFrame()->FloatControlBar(this,CPoint(400,400));
				}
			/*	else
				{
					pB1->ShowControlBar(this, FALSE, FALSE);
					pB1->FloatControlBar(this,CPoint(400,400));
				}*/
				
				GetParent()->GetParent()->ModifyStyle(WS_CAPTION,0);
				
			}


		}
		SendMessage(WM_NCPAINT);
		m_pDockSite->RecalcLayout();

		return;

	}

	//-------------------para el boton
	m_pDockSite->RecalcLayout();

}

void CGuiControlBar::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CControlBar::OnNcPaint() for painting messages
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
	cb.CreateSolidBrush(m_clrFondo);
	m_dc.FillRect(rcWindow, &cb);

	DrawGripper(&m_dc,&rcWindow);
	dc.IntersectClipRect(rcWindow);
    dc.ExcludeClipRect(rcClient);//asi evitamos el parpadeo
	dc.BitBlt(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),&m_dc,0,0,SRCCOPY);
	//ReleaseDC(&dc);  //TODO--PAUL
	//::ReleaseDC(m_hWnd, dc.Detach());
	m_dc.SelectObject(m_OldBitmap);
	m_bitmap.DeleteObject();
	m_dc.DeleteDC();
}

void CGuiControlBar::DrawGripper(CDC* pDC,CRect* rc)
{

	CRect gripper = rc;
	gripper.top =3;
	gripper.left+=4;
	if (IsVert())
		gripper.right-=!IsFloating()?!IsRight()?6:3:2;
	else
		gripper.right-=3;
	if(m_StyleDisplay == GUISTYLE_XP)
		gripper.bottom =gripper.top +nGapGripper-3;
	if(m_StyleDisplay == GUISTYLE_2003)
		gripper.bottom =gripper.top +nGapGripper+1;
	//si la ventana esta activa pintamos el caption o el area del titulo de color azul
	if (m_bAutoHide)
		m_bActive=FALSE;
	else if (IsFloating() )
		m_bActive=TRUE;
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
			cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorShadow(m_StyleDisplay));
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
	CString m_cadBreak=m_caption;
	CSize SizeCad=pDC->GetTextExtent(m_cadBreak,m_cadBreak.GetLength());
	CRect rCText=gripper;
	rCText.top=6;
	rCText.bottom =rCText.top+14;

	int cont=m_cadBreak.GetLength();
	if (SizeCad.cx > (gripper.Width()-30))
	{
		while(cont > 1 )
			{
				CString m_scadtemp=m_cadBreak+"...";
				CSize coor=pDC->GetTextExtent(m_scadtemp,m_scadtemp.GetLength());
				if(coor.cx > (gripper.Width()-30))
				{
					m_cadBreak=m_cadBreak.Left(m_cadBreak.GetLength()-1);
				}
				else
					break;
				cont--;

			}
		m_cadBreak+=_T("...");
		
	}

	if (gripper.Width() > 0	)
	if (!m_bActive)
		pDC->TextOut(rCText.left+8,rCText.top,m_cadBreak);
	else
	{
		if (GuiDrawLayer::m_Style == GUISTYLE_XP)
			pDC->SetTextColor(RGB(255,255,255));
		pDC->TextOut(rCText.left+8,rCText.top,m_cadBreak);
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
	m_rcAutoHideBtn=gripper;
	m_rcAutoHideBtn.right-=14;
	m_rcAutoHideBtn.left-=14;
	m_rcCloseBtn=gripper;
	//m_rcCloseBtn.left-=4;
	//ClientToScreen(m_rcCloseBtn);
	if(!m_bAutoHide)
		m_AutoHideBtn.SetData(12,_T("Auto Hide"));
	else
		m_AutoHideBtn.SetData(14,_T("Auto Hide"));
	m_CloseBtn.Paint(pDC,m_stateBtn,gripper,NULL_BRUSH,m_bActive && GuiDrawLayer::m_Style != GUISTYLE_2003);
	m_AutoHideBtn.Paint(pDC,m_stateAHBtn,m_rcAutoHideBtn,NULL_BRUSH,m_bActive && GuiDrawLayer::m_Style != GUISTYLE_2003);

	//------------------------------------------------
 	pDC->SetBkMode(nMode);
	pDC->SelectObject(m_fontOld);

}

//en esta función se calcula el area cliente que podra ser utilizado
//por ventanas que deriven esta clase.
void CGuiControlBar::OnNcCalcSize(BOOL /*bCalcValidRects*/, NCCALCSIZE_PARAMS* lpncsp)
{
	// adjust non-client area for border space
	
	lpncsp->rgrc[0].left +=!IsFloating() || m_bAutoHide ?5:2;
	lpncsp->rgrc[0].top +=!IsFloating() || m_bAutoHide ?nGapGripper+3:3;
	if (IsVert())
		lpncsp->rgrc[0].right -=!IsFloating() || m_bAutoHide?!IsRight()?5:2:2;
	else
		lpncsp->rgrc[0].right -=3;
	lpncsp->rgrc[0].bottom -=!IsFloating()||m_bAutoHide?3:2;

}


//Aqui la idea es verificar que si se da clic sobre otra ventana de este tipo
//automaticamente emita un mensaje eliminando el caption que la identifica como
//ventana default.

void CGuiControlBar::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{

	CRect rc;
	GetClientRect(rc);
	
	nDockBarAling = GetParent()->GetDlgCtrlID();
	if(!IsFloating())
		m_nLastAlingDockingBck=nDockBarAling;
	
	
	//envie un recalculo del area cliente solo si el tamaño ha sido
	//cambiado, de lo contrario permanezca igual
	lpwndpos->flags |= SWP_FRAMECHANGED;
	CControlBar::OnWindowPosChanged(lpwndpos);

	CWnd* pWnd = GetWindow(GW_CHILD);
	if (!m_bSupportMultiView)
	{
        if (pWnd != NULL)
        {
            pWnd->MoveWindow(rc);
			ASSERT(pWnd->GetWindow(GW_HWNDNEXT) == NULL);
		}
	}
	else
	{
		while (pWnd != NULL)
        {
            if (pWnd->IsWindowVisible())
			{
				pWnd->MoveWindow(rc);
				break;
			}
            pWnd=pWnd->GetWindow(GW_HWNDNEXT);
		}

	}


}


//este conjunto de clases nos indican el estado de la ventana
//en un momento determinado

BOOL CGuiControlBar::IsHideVert()
{
	if (m_nLastAlingDocking ==CBRS_ALIGN_LEFT || m_nLastAlingDocking == CBRS_ALIGN_RIGHT)
		return TRUE;
	return FALSE;
}

BOOL CGuiControlBar::IsHideLeft()
{
	if (m_nLastAlingDocking ==CBRS_ALIGN_LEFT)	return TRUE;
	return FALSE;
}

BOOL CGuiControlBar::IsHideRight()
{
	if (m_nLastAlingDocking == CBRS_ALIGN_RIGHT)	return TRUE;
	return FALSE;
}

BOOL CGuiControlBar::IsHideTop()
{
	if (m_nLastAlingDocking == CBRS_ALIGN_TOP) return TRUE;
	return FALSE;
}

BOOL CGuiControlBar::IsHideBottom()
{
	if (m_nLastAlingDocking == CBRS_ALIGN_BOTTOM) return TRUE;
	return FALSE;
}



BOOL CGuiControlBar::IsLeft()
{
	if (nDockBarAling == AFX_IDW_DOCKBAR_LEFT)	return TRUE;
	return FALSE;
}

BOOL CGuiControlBar::IsRight()
{
	if (nDockBarAling == AFX_IDW_DOCKBAR_RIGHT)	return TRUE;
	return FALSE;
}

BOOL CGuiControlBar::IsTop()
{
	if (nDockBarAling == AFX_IDW_DOCKBAR_TOP) return TRUE;
	return FALSE;
}

BOOL CGuiControlBar::IsBottom()
{
	if (nDockBarAling == AFX_IDW_DOCKBAR_BOTTOM) return TRUE;
	return FALSE;
}

BOOL CGuiControlBar::IsVert()
{
	if (IsLeft() || IsRight())	return TRUE;
	return FALSE;
}

BOOL CGuiControlBar::IsHorz()
{
	if (IsTop() || IsBottom())	return TRUE;
	return FALSE;
}

BOOL CGuiControlBar::IsFloating()
{
	if (nDockBarAling == AFX_IDW_DOCKBAR_FLOAT)	return TRUE;
	return FALSE;

}
void CGuiControlBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	m_pDockSite->RecalcLayout();//si quita esto se tiene problemas

	// TODO: Add your message handler code here
	// Do not call CControlBar::OnPaint() for painting messages
}


UINT CGuiControlBar::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rcWindow;
	//no se convierte las coordenadas de pantalla porque el punto
	//entregado por esta función esta dado en el mismo sentido.
	GetWindowRect(rcWindow);
	int it=0;
//	if (IsFloating())
//        return CControlBar::OnNcHitTest(point);
	CRect rcT=m_rcCloseBtn;
	ClientToScreen(rcT);
	CPoint pt=point;
	pt.y+=23;
	pt.x+=5;
	//pt.Offset(-rcT.left,-rcT.top);
	if (rcT.PtInRect(pt))
		return HTCLOSE;
	rcT=m_rcAutoHideBtn;
	ClientToScreen(rcT);
	pt=point;
	pt.y+=23;
	pt.x+=5;
	if (rcT.PtInRect(pt))
		return HTPIN;
	
	CRect rcTemp;
	for (int i=0; i< 4; i++)
	{
		rcTemp=rcWindow;
		if (i== 0)		//left
		{
			it=	rcTemp.left;
			it+=4;
			rcTemp.right=it;
			m_rcBorder=rcTemp;
			if (rcTemp.PtInRect(point))
				if(IsLegal(HTLEFT)) return m_SideMove=HTLEFT;
		}
		if (i==1)  //top
		{
			it=	rcTemp.top;
			it+=4;
			rcTemp.bottom=it;
			m_rcBorder=rcTemp;
			if (rcTemp.PtInRect(point))
				 if(IsLegal(HTTOP)) return m_SideMove=HTTOP ;
		}
		if (i==2)  //right
		{
			it=	rcTemp.right;
			it-=4;
			rcTemp.left=it;
			m_rcBorder=rcTemp;
			if (rcTemp.PtInRect(point))
				if (IsLegal(HTRIGHT)) return m_SideMove=HTRIGHT;
		}
		if (i==3)  //bottom
		{
			it=	rcTemp.bottom;
			it-=4;
			rcTemp.top=it;
			m_rcBorder=rcTemp;
			if (rcTemp.PtInRect(point))
				if (IsLegal(HTBOTTOM))return m_SideMove=HTBOTTOM;
		}

	}
	it=0;
	rcTemp=rcWindow;
	it=	rcTemp.top+nGapGripper;
	rcTemp.bottom=it;
	if (rcTemp.PtInRect(point))
	{
			SetCursor(::LoadCursor(NULL,IDC_ARROW));
		return m_SideMove=HTCAPTION;
	}
	return CControlBar::OnNcHitTest(point);
}

//-----------------------------------------------------------
//aqui se verifica que las coordenadas de cambio de tamaño
//sean las correctas

BOOL CGuiControlBar::IsLegal(UINT uAlin)
{
	m_First=GetFirstPos();
//	if (IsFloating()) return FALSE;
	switch(uAlin)
	{
		case HTLEFT:
			if(!m_bAutoHide)
			{
				if (IsHorz() && m_pos >0 && (m_pos != m_Last && m_pos != m_First)) return TRUE;
				if (IsVert() && m_pos <= m_Last && IsRight() ) return TRUE;
			}
			else
			{
				if (!IsHideVert() && m_pos >0 && (m_pos != m_Last && m_pos != m_First)) return TRUE;
				if (IsHideVert() && m_pos <= m_Last && IsHideRight() ) return TRUE;
			}
			return FALSE;
			break;
		case HTTOP:
			if(!m_bAutoHide)
			{
				if (m_pos != m_First && IsVert()) return TRUE;
				if (IsHorz() && m_pos <= m_Last && IsBottom() ) return TRUE;
			}
			else
			{
				if (m_pos != m_First && IsHideVert()) return TRUE;
				if (!IsHideVert() && m_pos <= m_Last && IsHideBottom() ) return TRUE;
			}
			return FALSE;
			break;
		case HTRIGHT:
			if(!m_bAutoHide)
			{
				if (m_pos <= m_Last && IsVert() && IsLeft() ) return TRUE;
				if (IsHorz() && m_pos >0 &&  m_pos != m_Last) return TRUE;
			}
			else
			{
				if (m_pos <= m_Last && IsHideVert() && IsHideLeft() ) return TRUE;
				if (!IsHideVert() && m_pos >0 &&  m_pos != m_Last) return TRUE;
			}

			return FALSE;
		case HTBOTTOM:
			if(!m_bAutoHide)
			{
				if ((m_pos != m_Last && m_pos != m_First) && IsHorz() && IsBottom()) return TRUE;
				if (m_pos <= m_Last && IsHorz() && IsTop()) return TRUE;
			}
			else
			{
				if ((m_pos != m_Last && m_pos != m_First) && !IsHideVert() && IsHideBottom()) return TRUE;
				if (m_pos <= m_Last && !IsHideVert() && IsHideTop()) return TRUE;
			}
			//if (IsVert() && m_pos >0 ) return TRUE;
			return FALSE;
			break;
	}
	return FALSE;
}



//----------------------------------------------
//debemos obtener cuantas barras existen en esta columnas
//porque si intentamos obtener el conteo con la funciones de dockbar
//siempre obtendremos nuestra actual barra mas otra de otra fila, por lo que
//el conteo es incorrecto, luego despues de nuestra barra la siguiente nula
//es el final de esta fila.

int CGuiControlBar::GetLastPos()
{

	int nNumBars=(int)m_pDockBar->m_arrBars.GetSize();
	int m_pos=m_pDockBar->FindBar(this);
	for(int i=m_pos+1; i< nNumBars;i++)
	{
		if (m_pDockBar->m_arrBars[i]== NULL)
		    return i-1;
	}
	return -1;
}

//--------------------------------------------
//esta rutina funciona algo parecido a la anterior
//con la diferencia que ahora se parte desde la posicion
//que indetifica m_pos hacia atraz hasta encontrar el nulo
int CGuiControlBar::GetFirstPos()
{
	int m_pos=m_pDockBar->FindBar(this);
	for(int i=m_pos; i>=0;i--)
	{
		if (m_pDockBar->m_arrBars[i]== NULL)
		    return i+1;
	}
	return -1;

}



//------------------------------------------------------------------------

BOOL CGuiControlBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	if (IsFloating() && !m_bAutoHide) return 0;
	CPoint ptCursor;
	::GetCursorPos (&ptCursor);
	if(nHitTest == HTLEFT ||nHitTest == HTRIGHT)
		SetCursor(AfxGetApp ()->LoadCursor (AFX_IDC_HSPLITBAR));
	else if(nHitTest == HTTOP ||nHitTest == HTBOTTOM)
		SetCursor(AfxGetApp ()->LoadCursor (AFX_IDC_VSPLITBAR));
	else
		return CControlBar::OnSetCursor(pWnd, nHitTest, message);
	return 1;
}



void CGuiControlBar::OnInvertTracker(const CRect& rect)
{
	ASSERT_VALID(this);
	ASSERT(!rect.IsRectEmpty());

	CRect rcWin=GetDockRect();
	
	CDC *pDC = m_pDockSite->GetDCEx(NULL,
        DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
	CRect rcBar;
	GetWindowRect(rcBar);
	if (m_bAutoHide)
		rcWin=rcBar;
	if (IsVert()|| IsHideVert())  //el sentido de las barras es vertical
	{



		if (m_SideMove==HTLEFT || m_SideMove==HTRIGHT) //el mouse esta en el borde izquierdo o derecho
		{
			
			rcWin.OffsetRect(-rect.left,-rect.top);
			rcWin.top+=10;
			rcWin.left=rect.left+2;
			rcWin.right=rect.right+2;
		}
		else  //el mouse esta el borde de arriba pero de una barra vertical
		{
			rcBar.OffsetRect(-rect.TopLeft());
			rcBar.OffsetRect(CPoint(0,9));
			rcWin=rcBar;
			if (IsLeft() || IsRight())   //a la izquierda
			{

				rcWin.top=rect.top;
				rcWin.bottom=rect.bottom;
			}
			//

		}
	}
	else  //el sentido de las barras es horizontal
	{

		if (m_SideMove==HTTOP || m_SideMove==HTBOTTOM) //el mouse esta en el borde de arriba o abajo
		{
			rcWin.OffsetRect(-rect.left,-rect.top);
			rcWin.top=rect.top-2;
			rcWin.bottom=rect.bottom;
		}
		else		//el mouse esta en el borde derecho
		{
			rcBar.OffsetRect(-rect.TopLeft());
			rcBar.OffsetRect(CPoint(0,8));
			rcWin=rcBar;
			if ((IsBottom()|| IsHideBottom()) || (IsTop()|| IsHideTop()))	//abajo
			{
				rcWin.left=rect.left+2;
				rcWin.right=rect.right+2;
			}
		}
	}
	ClientToScreen(&rcWin);
	m_pDockSite->ScreenToClient(&rcWin);
	
	// invert the brush pattern (looks just like frame window sizing)
	CBrush* pBrush = CDC::GetHalftoneBrush();
	HBRUSH hOldBrush = NULL;
	if (pBrush != NULL)
		hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, pBrush->m_hObject);
	pDC->PatBlt(rcWin.left, rcWin.top, rcWin.Width(), rcWin.Height(), PATINVERT);
	if (hOldBrush != NULL)
		SelectObject(pDC->m_hDC, hOldBrush);
	m_pDockSite->ReleaseDC(pDC);
}

/*void CGuiControlBar::OnInvertTracker(const CRect& rect)
{
	ASSERT_VALID(this);
	ASSERT(!rect.IsRectEmpty());

	CRect rcWin=GetDockRect();
	
	CDC *pDC = m_pDockSite->GetDCEx(NULL,
        DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
	CRect rcBar;
	GetParent()->GetWindowRect(rcBar);
	if (m_bAutoHide)
		rcWin=rcBar;
	if (IsVert()|| IsHideVert())  //el sentido de las barras es vertical
	{



		if (m_SideMove==HTLEFT || m_SideMove==HTRIGHT) //el mouse esta en el borde izquierdo o derecho
		{
			
			rcWin.OffsetRect(-rect.left,-rect.top);
			rcWin.top+=10;
			rcWin.left=rect.left+2;
			rcWin.right=rect.right+2;
		}
		else  //el mouse esta el borde de arriba pero de una barra vertical
		{
			rcBar.OffsetRect(-rect.TopLeft());
			rcBar.OffsetRect(CPoint(0,9));
			rcWin=rcBar;
			if (IsLeft() || IsRight())   //a la izquierda
			{

				rcWin.top=rect.top;
				rcWin.bottom=rect.bottom;
			}
			//

		}
	}
	else  //el sentido de las barras es horizontal
	{

		if (m_SideMove==HTTOP || m_SideMove==HTBOTTOM) //el mouse esta en el borde de arriba o abajo
		{
			rcWin.OffsetRect(-rect.left,-rect.top);
			rcWin.top=rect.top-2;
			rcWin.bottom=rect.bottom-2;
		}
		else		//el mouse esta en el borde derecho
		{
			rcBar.OffsetRect(-rect.TopLeft());
			rcBar.OffsetRect(CPoint(0,8));
			rcWin=rcBar;
			if ((IsBottom()|| IsHideBottom()) || (IsTop()|| IsHideTop()))	//abajo
			{
				rcWin.left=rect.left+2;
				rcWin.right=rect.right+2;
			}
		}
	}
	ClientToScreen(&rcWin);
	GetParentFrame()->ScreenToClient(&rcWin);
	
	// invert the brush pattern (looks just like frame window sizing)
	CBrush* pBrush = CDC::GetHalftoneBrush();
	HBRUSH hOldBrush = NULL;
	if (pBrush != NULL)
		hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, pBrush->m_hObject);
	pDC->PatBlt(rcWin.left, rcWin.top, rcWin.Width(), rcWin.Height(), PATINVERT);
	if (hOldBrush != NULL)
		SelectObject(pDC->m_hDC, hOldBrush);
	m_pDockSite->ReleaseDC(pDC);
}

*/

void CGuiControlBar::OnSize(UINT nType, int cx, int cy)
{
//	CControlBar::OnSize(nType, cx, cy);
	
	CWnd* pWnd = GetWindow(GW_CHILD);
	if (!m_bSupportMultiView)
	{
        if (pWnd != NULL)
        {
            pWnd->MoveWindow(0, 0, cx, cy);
            ASSERT(pWnd->GetWindow(GW_HWNDNEXT) == NULL);
		}
	}
	else
	{
		while (pWnd != NULL)
        {
            if (pWnd->IsWindowVisible())
			{
				pWnd->MoveWindow(0, 0, cx, cy);
				break;
			}
            pWnd=pWnd->GetWindow(GW_HWNDNEXT);
		}
	}

	// TODO: Add your message handler code here
}
void CGuiControlBar::SetColorFondo(COLORREF clrFondo)
{
	m_clrFondo=clrFondo;

}

//enum State{NORMAL=0,OVER=1,PRESS=2};



void CGuiControlBar::LoadStateBar(CString sProfile)
{
	CWinApp* pApp = AfxGetApp();
	TCHAR szSection[256] = {0};
	wsprintf(szSection, _T("%s-Bar%d"),sProfile,GetDlgCtrlID());
	m_sizeHorz.cx=pApp->GetProfileInt(szSection, _T("sizeHorz.cx"),200 );
	m_sizeHorz.cy=pApp->GetProfileInt(szSection, _T("sizeHorz.cy"),100 );
	m_sizeVert.cx=pApp->GetProfileInt(szSection, _T("sizeVert.cx"),200 );
	m_sizeVert.cy=pApp->GetProfileInt(szSection, _T("sizeVert.cy"),100 );
	m_bAutoHide=pApp->GetProfileInt(szSection, _T("AutoHide"),0 );
	m_nLastAlingDocking=pApp->GetProfileInt(szSection, _T("Aling"),0 );
	if (m_bAutoHide)
		InitAutoHide();
	else
		m_nLastAlingDocking=0;

	
}

void CGuiControlBar::SaveBar(CString sProfile)
{
	CWinApp* pApp = AfxGetApp();
	TCHAR szSection[256] = {0};
	wsprintf(szSection, _T("%s-Bar%d"), sProfile,GetDlgCtrlID());
	pApp->WriteProfileString(szSection, NULL, NULL);
	pApp->WriteProfileInt(szSection, _T("sizeHorz.cx"), m_sizeHorz.cx);
	pApp->WriteProfileInt(szSection, _T("sizeHorz.cy"), m_sizeHorz.cy);
	pApp->WriteProfileInt(szSection, _T("sizeVert.cx"), m_sizeVert.cx);
	pApp->WriteProfileInt(szSection, _T("sizeVert.cy"), m_sizeVert.cy);
	pApp->WriteProfileInt(szSection, _T("AutoHide"), m_bAutoHide);
	pApp->WriteProfileInt(szSection, _T("Aling"), m_nLastAlingDocking);
}
void CGuiControlBar::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nHitTest == HTCLOSE)
		if (m_stateBtn != NORMAL) return;

	if (nHitTest == HTPIN)
		if (m_stateAHBtn != NORMAL) return;

	if (nHitTest == HTCLOSE)
	{
		m_stateBtn=OVER;
		SetTimer(1,100,0);
	}

	if (nHitTest == HTPIN)
	{
		m_stateAHBtn=OVER;
		SetTimer(2,100,0);
	}

	SendMessage(WM_NCPAINT);
	CControlBar::OnNcMouseMove(nHitTest, point);
}






void CGuiControlBar::OnNcLButtonDblClk(UINT nFlags, CPoint point)
{
	if(m_pDockBar != NULL && !m_bAutoHide)
	{

		m_pDockContext->ToggleDocking();
		m_rcOldBorder=CRect(0,0,0,0);

	}
}



