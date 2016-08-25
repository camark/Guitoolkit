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
#include "Guiofficebar.h"
#include "Guidrawlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define HORZF(dw) (dw & CBRS_ORIENT_HORZ)
#define VERTF(dw) (dw & CBRS_ORIENT_VERT)
#define CX_BORDER   1
#define CY_BORDER   1

enum btn
{
	HTBACK   = 520,
	HTFORWAR = 521,
	THMENU   = 522,
	HTCLOS   = 523
};

int ArrBtn[4]={HTBACK,HTFORWAR,THMENU,HTCLOS};

void  _AfxAdjustRectangle(CRect& rect, CPoint pt)
{
	int nXOffset = (pt.x < rect.left) ? (pt.x - rect.left) :
					(pt.x > rect.right) ? (pt.x - rect.right) : 0;
	int nYOffset = (pt.y < rect.top) ? (pt.y - rect.top) :
					(pt.y > rect.bottom) ? (pt.y - rect.bottom) : 0;
	rect.OffsetRect(nXOffset, nYOffset);
}

BEGIN_MESSAGE_MAP(CGuiOfficeBar,CGuiControlBar)
	ON_WM_CREATE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_TIMER()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCHITTEST()
	ON_COMMAND(HTBACK,OnBack)
	ON_COMMAND(HTFORWAR,OnForWard)
	ON_COMMAND(THMENU,OnMenu)
	ON_WM_NCCALCSIZE()

END_MESSAGE_MAP()

CGuiOfficeBar::CGuiOfficeBar(void)
{
	m_stateBtnBack=NORMAL;
	m_stateBtnClose=NORMAL;
	m_stateBtnFor=NORMAL;
	m_stateBtnMenu=NORMAL;
	m_StateBtn=NORMAL;
	m_nHits=-1;

}

CGuiOfficeBar::~CGuiOfficeBar(void)
{
	
}


void CGuiOfficeBar::OnBack()
{
}

void CGuiOfficeBar::OnForWard()
{
}

void CGuiOfficeBar::OnMenu()
{
}

int CGuiOfficeBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_ArrButtons[0].SetData(1,_T("Back"));
	m_ArrButtons[0].SetImageList(IDB_GUI_DOCKBAROFFICE,16,7,RGB(255,0,255));
	m_ArrButtons[1].SetData(2,_T("Forward"));
	m_ArrButtons[1].SetImageList(IDB_GUI_DOCKBAROFFICE,16,7,RGB(255,0,255));
	m_ArrButtons[2].SetData(0,_T("Menu"));
	m_ArrButtons[2].SetImageList(IDB_GUI_DOCKBAROFFICE,16,7,RGB(255,0,255));
	m_ArrButtons[3].SetData(6,_T("Close"));
	m_ArrButtons[3].SetImageList(IDB_GUI_DOCKBAROFFICE,16,7,RGB(255,0,255));
	m_ArrButtons[0].SetTypeButton(CGuiControlBarButton::GUITOOLBUTTON);
	m_ArrButtons[1].SetTypeButton(CGuiControlBarButton::GUITOOLBUTTON);
	m_ArrButtons[2].SetTypeButton(CGuiControlBarButton::GUITOOLBUTTON);
	m_ArrButtons[3].SetTypeButton(CGuiControlBarButton::GUITOOLBUTTON);
	SetColorFondo(RGB(255,255,255));
	
	return 0;
}


CSize CGuiOfficeBar::CalcDynamicLayout(int nLength, DWORD nMode)
{

	m_pDockSite->RecalcLayout();

	if (IsFloating())
	{
		// Enable diagonal arrow cursor for resizing
		//m_sizeVert=m_sizeHorz=CSize(200,200);
		GetParent()->GetParent()->ModifyStyle(MFS_4THICKFRAME|WS_CAPTION,0);
	} 
	if (nMode & (LM_HORZDOCK | LM_VERTDOCK)) 
	{
		m_pDockSite->DelayRecalcLayout();
		//obligar a reposicionar  la ventana, de lo contrario cuando vuelva de un doble click
		//desde la ventana CMiniFrameWnd queda sin area cliente
		SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER |
			SWP_NOACTIVATE | SWP_FRAMECHANGED|SWP_NOREDRAW);
	 	return CControlBar::CalcDynamicLayout(nLength, nMode);
	}
	if (nMode & LM_MRUWIDTH)
        return  m_sizeMinFloating;

    if (nMode & LM_COMMIT)
        return  m_sizeMinFloating ;
    
	if (IsFloating())
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

void CGuiOfficeBar::OnNcCalcSize(BOOL /*bCalcValidRects*/, NCCALCSIZE_PARAMS* lpncsp)
{
	// adjust non-client area for border space
	lpncsp->rgrc[0].left +=!IsFloating()?5:2;
	lpncsp->rgrc[0].top +=nGapGripper+3;
	lpncsp->rgrc[0].right -=!IsFloating()?IsVert()?7:4:2;
	lpncsp->rgrc[0].bottom -=!IsFloating()?3:2;
	
}

void CGuiOfficeBar::DrawGripper(CDC* pDC,CRect* rc)
{

	CRect gripper = rc;
	gripper.top =3;
	gripper.left+=4;
	gripper.right-=IsVert()?5:4;
	gripper.bottom =gripper.top +nGapGripper-3;
	//si la ventana esta activa pintamos el caption o el area del titulo de color azul 	
	
	CPen cp(PS_SOLID,1,::GetSysColor(COLOR_BTNHIGHLIGHT));
	CPen* cpold=pDC->SelectObject(&cp);
	//linea superior


	CBrush cb;
	cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));//GuiDrawLayer::GetRGBCaptionXP());
	pDC->FillRect(gripper,&cb);

	pDC->SelectObject(cpold);
	gripper.DeflateRect(1, 1);
	CString m_caption;
	GetWindowText(m_caption);
	CFont m_cfont;

	m_cfont.CreateFont(-11,0,0,0,FW_SEMIBOLD,0,0,0,0,1,2,1,34,_T("Microsoft Sans Serif"));
		
	CFont* m_fontOld=pDC->SelectObject(&m_cfont);
	int nMode = pDC->SetBkMode(TRANSPARENT);
	CSize SizeCad=pDC->GetTextExtent(m_caption);
	CRect rCText=gripper;
	rCText.top=6;
	rCText.bottom =rCText.top+14;
	rCText.left=34;
	
	int cont=SizeCad.cx;
	while(cont > 1 && gripper.Width()-60 > 0)
		{
			CSize coor=pDC->GetTextExtent(m_caption,m_caption.GetLength());
			if(coor.cx > gripper.Width()-60)
			{
				m_caption=m_caption.Left(m_caption.GetLength()-1);
			}
			else
				break;
			cont--;
				
		}

	//CRect gripper;
	//------------------------------------------------
	GetWindowRect( gripper );
	ScreenToClient( gripper );

	
	gripper.OffsetRect( -gripper.left, -gripper.top );
	//boton de Close
	m_ArrButtons[3].rcArea=gripper;
	m_ArrButtons[3].rcArea.left=m_ArrButtons[3].rcArea.right-20;
	m_ArrButtons[3].rcArea.right-=7;
	m_ArrButtons[3].rcArea.top+=4;
	m_ArrButtons[3].rcArea.bottom=m_ArrButtons[3].rcArea.top+13;

	
	//boton menu
	
	m_ArrButtons[2].rcArea=gripper;
	m_ArrButtons[2].rcArea.left=m_ArrButtons[3].rcArea.left-16;
	m_ArrButtons[2].rcArea.right=m_ArrButtons[2].rcArea.left+13;
	m_ArrButtons[2].rcArea.top+=4;
	m_ArrButtons[2].rcArea.bottom=m_ArrButtons[2].rcArea.top+13;
	//boton back
	
	m_ArrButtons[0].rcArea=gripper;
	m_ArrButtons[0].rcArea.left+=4;
	m_ArrButtons[0].rcArea.right=m_ArrButtons[0].rcArea.left+13;
	m_ArrButtons[0].rcArea.top+=4;
	m_ArrButtons[0].rcArea.bottom=m_ArrButtons[0].rcArea.top+13;
	//boton forward


	m_ArrButtons[1].rcArea=gripper;
	m_ArrButtons[1].rcArea.left+=m_ArrButtons[0].rcArea.right+2;
	m_ArrButtons[1].rcArea.right=m_ArrButtons[1].rcArea.left+13;
	m_ArrButtons[1].rcArea.top+=4;
	m_ArrButtons[1].rcArea.bottom=m_ArrButtons[1].rcArea.top+13;

	//m_rcCloseBtn.left-=4;
	//ClientToScreen(m_rcCloseBtn);
	
	 m_ArrButtons[0].Paint(pDC,m_stateBtnBack,m_ArrButtons[0].rcArea,GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	 m_ArrButtons[1].Paint(pDC,m_stateBtnFor,m_ArrButtons[1].rcArea,GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	 m_ArrButtons[2].Paint(pDC,m_stateBtnMenu,m_ArrButtons[2].rcArea,GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	 m_ArrButtons[3].Paint(pDC,m_stateBtnClose,m_ArrButtons[3].rcArea,GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	//------------------------------------------------

	
	if (gripper.Width() > 0	)
	pDC->TextOut(rCText.left+3,rCText.top,m_caption);
	//CRect gripper;
	//------------------------------------------------
	pDC->SetBkMode(nMode);
	pDC->SelectObject(m_fontOld);
	
}

void CGuiOfficeBar::ShowTitle(CString m_Caption)
{
	SetWindowText(m_Caption);
	SendMessage(WM_COMMAND, ID_GUI_SHOWTITLE);
}

void CGuiOfficeBar::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	if( m_nHits == HTCLOS || m_nHits == HTBACK || m_nHits == HTFORWAR|| m_nHits == THMENU)											
	{
		if (m_nHits == HTCLOS)
			m_stateBtnClose=PRESS;
		else if (m_nHits == HTBACK)
			m_stateBtnBack=PRESS;
		else if(m_nHits == HTFORWAR)
			m_stateBtnFor=PRESS;
		else if(m_nHits == THMENU)
			m_stateBtnMenu=PRESS;
		m_StateBtn=PRESS;
		SendMessage(WM_NCPAINT);
		SetTimer(1,100,0);
		return;
	} 
	if (nHitTest == HTCAPTION)
		SetCursor(::LoadCursor(NULL,IDC_SIZEALL));
	CGuiControlBar::OnNcLButtonDown(nHitTest, point);
}

void CGuiOfficeBar::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rcT;
	point.y+=23;
	point.x+=5;
	if (m_stateBtnBack!=NORMAL)
		rcT=m_ArrButtons[0].rcArea;
	else if(m_stateBtnFor!=NORMAL)
		rcT=m_ArrButtons[1].rcArea;
	else if(m_stateBtnMenu!=NORMAL)
		rcT=m_ArrButtons[2].rcArea;
	else if(m_stateBtnClose!=NORMAL)
		rcT=m_ArrButtons[3].rcArea;
	
	ClientToScreen(rcT);
	if (rcT.PtInRect(point))
	{
		
		if (m_StateBtn ==PRESS)
		{
			
			if(m_stateBtnClose!=NORMAL)
				 GetDockingFrame()->ShowControlBar(this, FALSE, FALSE);
			else
			{
				SendMessage (WM_COMMAND,m_nHits);
				AfxGetMainWnd()->SendMessage(WM_COMMAND,m_nHits);
			}
			m_StateBtn=NORMAL;
			m_stateBtnBack=NORMAL;
			m_stateBtnClose=NORMAL;
			m_stateBtnFor=NORMAL;
			m_stateBtnMenu=NORMAL;
			m_nHits=-1;
			KillTimer(1);
			
		}
		//SendMessage(WM_NCPAINT);
		return;
			
	}
	CGuiControlBar::OnNcLButtonUp(nHitTest, point);
}

void CGuiOfficeBar::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (m_StateBtn==NORMAL) return;
	CRect rc;
	CPoint pt(GetMessagePos());
	CRect rcT=CRect(0,0,0,0);
	if (m_stateBtnBack!=NORMAL)
		rcT=m_ArrButtons[0].rcArea;
	else if(m_stateBtnFor!=NORMAL)
		rcT=m_ArrButtons[1].rcArea;
	else if(m_stateBtnMenu!=NORMAL)
		rcT=m_ArrButtons[2].rcArea;
	else if(m_stateBtnClose!=NORMAL)
		rcT=m_ArrButtons[3].rcArea;
	
	ClientToScreen(rcT);
	pt.y+=23;
	pt.x+=5;
	if (!rcT.PtInRect(pt))
	{
		m_StateBtn=NORMAL;
		m_stateBtnBack=NORMAL;
		m_stateBtnClose=NORMAL;
		m_stateBtnFor=NORMAL;
		m_stateBtnMenu=NORMAL;
		m_nHits=-1;
		KillTimer(1);
		SendMessage(WM_NCPAINT); 		
	}
	CGuiControlBar::OnTimer(nIDEvent);
}

void CGuiOfficeBar::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_StateBtn != NORMAL) return;
	if (m_nHits == HTCLOS)
	{
		m_StateBtn=OVER;
		m_stateBtnClose=OVER;
		m_stateBtnBack=NORMAL;
		m_stateBtnFor=NORMAL;
		m_stateBtnMenu=NORMAL;
		SendMessage(WM_NCPAINT);
		SetTimer(1,100,0);
		return;
	}
	
	if (m_nHits == HTBACK)
	{
		m_stateBtnBack=OVER;
		m_stateBtnClose=NORMAL;
		m_stateBtnFor=NORMAL;
		m_stateBtnMenu=NORMAL;
		m_StateBtn=OVER;
		SendMessage(WM_NCPAINT);
		SetTimer(1,100,0);
		return;
	}
	if (m_nHits == HTFORWAR)
	{
		m_stateBtnBack=NORMAL;
		m_stateBtnClose=NORMAL;
		m_stateBtnFor=OVER;
		m_stateBtnMenu=NORMAL;
		m_StateBtn=OVER;
		SendMessage(WM_NCPAINT);
		SetTimer(1,100,0);
		return;
	}
	if (m_nHits == THMENU)
	{
		m_stateBtnBack=NORMAL;
		m_stateBtnClose=NORMAL;
		m_stateBtnFor=NORMAL;
		m_stateBtnMenu=OVER;
		m_StateBtn=OVER;
		SendMessage(WM_NCPAINT);
		SetTimer(1,100,0);
		return;
	}
	
	CGuiControlBar::OnNcMouseMove(nHitTest, point);
}

UINT CGuiOfficeBar::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rcWindow;
	//no se convierte las coordenadas de pantalla porque el punto
	//entregado por esta función esta dado en el mismo sentido.
	GetWindowRect(rcWindow);
	
		
	CPoint pt=point;
	pt.y+=23;
	pt.x+=5;
	for(int i=0; i < 4; i++)
	{
		CRect rcT=m_ArrButtons[i].rcArea;
		ClientToScreen(rcT);
		if (rcT.PtInRect(pt))
			return m_nHits=ArrBtn[i];

	}
	m_nHits=-1;
	
	return CGuiControlBar::OnNcHitTest(point);
}



CGuiDockContextOffice::~CGuiDockContextOffice()
{

}

void CGuiDockContextOffice::StartDrag(CPoint pt)
{
	ASSERT_VALID(m_pBar);
	m_bDragging = TRUE;

	InitLoop();

	// GetWindowRect returns screen coordinates(not mirrored),
	// so if the desktop is mirrored then turn off mirroring
	// for the desktop dc so that we get correct focus rect drawn.
	// This layout change should be remembered, just in case ...

//	if (m_pDC->GetLayout() & LAYOUT_RTL)
//		m_pDC->SetLayout(LAYOUT_LTR);

	if (m_pBar->m_dwStyle & CBRS_SIZE_DYNAMIC)
	{
		// get true bar size (including borders)
		CRect rect;
		m_pBar->GetWindowRect(rect);
		m_ptLast = pt;
		AdjustWindowForFloat(rect);
		CSize sizeHorz = m_pBar->CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK);
		CSize sizeVert = m_pBar->CalcDynamicLayout(0, LM_VERTDOCK);
		CSize sizeFloat = m_pBar->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH);

		m_rectDragHorz = CRect(rect.TopLeft(), sizeHorz);
		m_rectDragVert = CRect(rect.TopLeft(), sizeVert);

		// calculate frame dragging rectangle
		m_rectFrameDragHorz = CRect(rect.TopLeft(), sizeFloat);
		m_rectFrameDragVert = CRect(rect.TopLeft(), sizeFloat);

		CMiniFrameWnd::CalcBorders(&m_rectFrameDragHorz);
		CMiniFrameWnd::CalcBorders(&m_rectFrameDragVert);

//		m_rectFrameDragHorz.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
//		m_rectFrameDragVert.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
	}
	else if (m_pBar->m_dwStyle & CBRS_SIZE_FIXED)
	{
		// get true bar size (including borders)
		CRect rect;
		m_pBar->GetWindowRect(rect);
		AdjustWindowForFloat(rect);
		m_ptLast = pt;
		CSize sizeHorz = m_pBar->CalcDynamicLayout(-1, LM_HORZ | LM_HORZDOCK);
		CSize sizeVert = m_pBar->CalcDynamicLayout(-1, LM_VERTDOCK);

		// calculate frame dragging rectangle
		m_rectFrameDragHorz = m_rectDragHorz = CRect(rect.TopLeft(), sizeHorz);
		m_rectFrameDragVert = m_rectDragVert = CRect(rect.TopLeft(), sizeVert);

		CMiniFrameWnd::CalcBorders(&m_rectFrameDragHorz);
		CMiniFrameWnd::CalcBorders(&m_rectFrameDragVert);
//		m_rectFrameDragHorz.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
//		m_rectFrameDragVert.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
	}
	else
	{
		// get true bar size (including borders)
		CRect rect;
		m_pBar->GetWindowRect(rect);
		AdjustWindowForFloat(rect);
		m_ptLast = pt;
		BOOL bHorz = HORZF(m_dwStyle);
		DWORD dwMode = !bHorz ? (LM_HORZ | LM_HORZDOCK) : LM_VERTDOCK;
		CSize size = m_pBar->CalcDynamicLayout(-1, dwMode);

		// calculate inverted dragging rect
		if (bHorz)
		{
			m_rectDragHorz = rect;
			m_rectDragVert = CRect(CPoint(pt.x - rect.Height()/2, rect.top), size);
		}
		else // vertical orientation
		{
			m_rectDragVert = rect;
			m_rectDragHorz = CRect(CPoint(rect.left, pt.y - rect.Width()/2), size);
		}

		// calculate frame dragging rectangle
		m_rectFrameDragHorz = m_rectDragHorz;
		m_rectFrameDragVert = m_rectDragVert;

		CMiniFrameWnd::CalcBorders(&m_rectFrameDragHorz);
		CMiniFrameWnd::CalcBorders(&m_rectFrameDragVert);
//		m_rectFrameDragHorz.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
//		m_rectFrameDragVert.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);
	}

	// adjust rectangles so that point is inside
	_AfxAdjustRectangle(m_rectDragHorz, pt);
	_AfxAdjustRectangle(m_rectDragVert, pt);
	_AfxAdjustRectangle(m_rectFrameDragHorz, pt);
	_AfxAdjustRectangle(m_rectFrameDragVert, pt);

	// initialize tracking state and enter tracking loop
	m_dwOverDockStyle = CanDock();
	Move(pt);   // call it here to handle special keys
	Track();
}

void CGuiDockContextOffice::AdjustWindowForFloat(CRect& rect)
{
	if( m_pBar->IsFloating())
		rect.top+=(GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME));
}
