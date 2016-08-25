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
#include "GuiMiniFrameWnd.h"
#include "GuiDrawLayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiMiniFrameWnd

#define NORMAL 0 
#define OVER   1
#define PRESS  2


IMPLEMENT_DYNCREATE(CGuiMiniFrameWnd, CMiniFrameWnd)

CGuiMiniFrameWnd::CGuiMiniFrameWnd()
{
	pControl=NULL;
	m_stateBtn=NORMAL;
	bDestroy=FALSE;
	bClick=FALSE;
	nSizeLine=0;
}

CGuiMiniFrameWnd::~CGuiMiniFrameWnd()
{
	
}


BEGIN_MESSAGE_MAP(CGuiMiniFrameWnd, CMiniFrameWnd)
	//{{AFX_MSG_MAP(CGuiMiniFrameWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_NCLBUTTONDOWN()
//	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP

	ON_WM_CLOSE()
	ON_WM_NCPAINT()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_WM_CANCELMODE()
	ON_WM_NCACTIVATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SETFOCUS()
	ON_WM_NCCALCSIZE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_SETFOCUS()


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiMiniFrameWnd message handlers

void CGuiMiniFrameWnd::OnNcPaint()
{
	// TODO: Add your message handler code here
	CRect rcWindow;
	CRect rcClient;
	CWindowDC	dc(this);
	CDC			m_dc;		//contexto de dispositivo en memoria
	CBitmap		m_bitmap;
	//la idea es tomar el area de la ventana y area  cliente , luego debemos
	//igualar el area de coordenadas de ventana al cliente
	GetWindowRect(&rcWindow);
	GetClientRect(&rcClient);
	int nSize=rcClient.right;
	ScreenToClient(rcWindow);
    rcClient.OffsetRect(-rcWindow.TopLeft());
    rcWindow.OffsetRect(-rcWindow.TopLeft());
  	
	m_dc.CreateCompatibleDC(&dc);
	m_bitmap.CreateCompatibleBitmap(&dc,rcWindow.Width(),rcWindow.Height());
	CBitmap *m_OldBitmap=m_dc.SelectObject(&m_bitmap);
	//aqui debe utilizarse la brocha que define GuiDrawLayer, si no hacemos la siguiente
	//linea usted vera un horrible color negro, a cambio del dibujo.
	CBrush cb;
	cb.CreateSolidBrush(!bClick? GuiDrawLayer::GetRGBMenu(): GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	m_dc.FillRect(rcWindow, &cb);
	
	CRect rcCaption=rcClient;
	rcCaption.InflateRect(1,1);
	
	dc.Draw3dRect(rcCaption,GuiDrawLayer::GetRGBColorBTNHigh(),GuiDrawLayer::GetRGBColorBTNHigh());
	
	DrawGripper(&m_dc,&rcClient);
	dc.IntersectClipRect(rcWindow);
    dc.ExcludeClipRect(rcClient);//asi evitamos el parpadeo

	
	//rcWindow.InflateRect(1,1);
	dc.BitBlt(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),&m_dc,0,0,SRCCOPY);
	ReleaseDC(&dc);
	m_dc.SelectObject(m_OldBitmap);
	m_bitmap.DeleteObject();
	m_dc.DeleteDC();

	//CMiniFrameWnd::OnNcPaint();
}

void CGuiMiniFrameWnd::DrawGripper(CDC* pDC,CRect* rc)
{

	
	CRect gripper = rc;
	gripper.top =3;
	gripper.left-=1;
	gripper.right+=2;
	gripper.bottom +=2;
	if (gripper.right < 0) return;
	int nCaption=::GetSystemMetrics(SM_CYSMCAPTION);
	//si la ventana esta activa pintamos el caption o el area del titulo de color azul 	
	CBrush cb;
	cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorShadow());//GuiDrawLayer::GetRGBCaptionXP());
	pDC->Draw3dRect(gripper,GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style),GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
	if (!bClick)
	{
		
		CRect rcLineLeft=gripper;
		CBrush cb1;
		cb1.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));//GuiDrawLayer::GetRGBCaptionXP());
		rcLineLeft.top=-1;
		rcLineLeft.right=rcLineLeft.left+nSizeLine;
		rcLineLeft.bottom=1;
		pDC->Draw3dRect(rcLineLeft,GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style),GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));	
		gripper.top-=2;
		pDC->FillRect(gripper,&cb1);
		rcLineLeft=gripper;
		rcLineLeft.top+=1;
		rcLineLeft.left+=2;
		rcLineLeft.right-=1;
		rcLineLeft.bottom-=1;
		pDC->Draw3dRect(rcLineLeft,GuiDrawLayer::GetRGBColorBTNHigh(),GuiDrawLayer::GetRGBColorBTNHigh());	
		//------------- draw minigripper ------------------
		   int ncalc=gripper.Width()/2;
		   ncalc-=5;
		   CRect rcgri=gripper;
		   rcgri.top+=5;
		   rcgri.left=ncalc;
		   rcgri.right=rcgri.left+20;
		   rcgri.bottom=rcgri.top+1;
		   pDC->Draw3dRect(rcgri,GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());	
		   rcgri.top+=2;
		   rcgri.bottom=rcgri.top+1;
		   pDC->Draw3dRect(rcgri,GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());		
		//-------------------------------------------------
		return;
	}
	CRect rcLineLeft=gripper;
	rcLineLeft.top+=nCaption+2;
	rcLineLeft.left+=2;
	rcLineLeft.right-=1;
	rcLineLeft.bottom-=1;
	pDC->Draw3dRect(rcLineLeft,GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style),GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));	

	gripper.DeflateRect(1, 1);
	CString m_caption;
	GetWindowText(m_caption);
	CFont m_cfont;

	m_cfont.CreateFont(-11,0,0,0,FW_BOLD,0,0,0,0,1,2,1,34,_T("Verdana"));
		
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
	{
		pDC->SetTextColor(GuiDrawLayer::GetRGBTitleMenu());
		pDC->TextOut(rCText.left+3,rCText.top,m_caption);
	}
	//CRect gripper;
	//------------------------------------------------
	GetWindowRect( gripper );
	ScreenToClient( gripper );
	gripper.OffsetRect( -gripper.left, -gripper.top );
	gripper.left=gripper.right-20;
	gripper.right-=4;
	gripper.top+=4;
	gripper.bottom=gripper.top+nCaption;
	m_rcCloseBtn=gripper;
	if (m_stateBtn==NORMAL)
		m_btn.Paint(pDC,m_stateBtn,gripper,GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	else if (m_stateBtn==OVER)
		m_btn.Paint(pDC,m_stateBtn,gripper,GuiDrawLayer::GetRGBFondoXP());
	else
		m_btn.Paint(pDC,m_stateBtn,gripper,GuiDrawLayer::GetRGBPressBXP());
	
	pDC->SetBkMode(nMode);
	pDC->SelectObject(m_fontOld);

	
}

void CGuiMiniFrameWnd::OnClose()
{
	OnCancelMode();
}


BOOL CGuiMiniFrameWnd::Create(CWnd* pParentWnd,CWnd* pControl1,const RECT& rc,LPCTSTR lpszWindowName,int nSize)
{
	// TODO: Add your specialized code here and/or call the base class
	pControl=pControl1;
	pParent=pParentWnd;
	nSizeLine=nSize;
	if (pControl->IsWindowVisible()) 
	{
		delete this;
		return false;
	}
	
	LPCTSTR lpszClassName=::AfxRegisterWndClass(CS_DBLCLKS,
												::LoadCursor(NULL,IDC_ARROW),
												::GetSysColorBrush(COLOR_BTNFACE),
												NULL);
	

	dwStyle = WS_POPUP|MFS_SYNCACTIVE|MFS_MOVEFRAME|MFS_4THICKFRAME;
	m_btn.SetData(6,_T("Close"));
	m_btn.SetImageList(IDB_GUI_DOCKBAR,9,10,RGB(255,0,255));
	m_btn.SetTypeButton(CGuiControlBarButton::GUITOOLBUTTON);
	CPoint pt (rc.left, rc.bottom);
	CRect rcCtrl;
	pControl->GetWindowRect(rcCtrl);
	BOOL bResp= CMiniFrameWnd::Create(NULL, lpszWindowName,dwStyle, CRect (pt.x, pt.y-2, rc.left+rcCtrl.Width(), rc.top+rcCtrl.Height()), pControl1->GetParentFrame(), 0);
	pControl->SetWindowPos (NULL, 0, 0, 0, 0, SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW);
	pControl->SetParent (this);
	pControl->ShowWindow(SW_SHOW);
	ShowWindow (SW_SHOW);
	SetTimer(1010,100,NULL);
	SendMessage(WM_SIZE);
	if (!bResp) return FALSE;
	return TRUE;
	
}

BOOL CGuiMiniFrameWnd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (!bClick) 
	switch ( pMsg->message )
    {
        case WM_KEYDOWN:
            // Default action for <Escape> key
            if ( pMsg->wParam == VK_ESCAPE )
            {
				bClick=TRUE;
				pParent->UnlockWindowUpdate();
				pParent->Invalidate();
				pParent->UpdateWindow();
	            OnCancelMode();
				pParent->SetFocus();
				PostMessage (WM_DESTROY);
				DestroyWindow();
				bDestroy=TRUE;
				return TRUE;
                
            }
            break;

        case WM_LBUTTONUP:
			bClick=TRUE;
			pParent->UnlockWindowUpdate();
			pParent->Invalidate();
			pParent->UpdateWindow();
			CWnd* pBar = GetWindow( GW_CHILD );
			if( pBar == NULL ) return FALSE;
			long rt=pBar->SendMessage(pMsg->wParam,pMsg->lParam);
			OnCancelMode();
			DestroyWindow();
			//KillTimer(8889);
			return FALSE;
			break;

	 }
	
	return CMiniFrameWnd::PreTranslateMessage(pMsg);
}

void CGuiMiniFrameWnd::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	 bDestroy=TRUE;
	 delete this;
}

void CGuiMiniFrameWnd::RecalLayout()
{
	CRect rc;
	CWnd* pBar = GetWindow( GW_CHILD );
    if( pBar == NULL ) return ;
	pBar->GetWindowRect(&rc);
	CRect rcWin;
	GetWindowRect(&rcWin);
	rc.left=rcWin.left;
	rc.top=rcWin.top;
	rc.right+=3;
	rc.bottom+=3;
	MoveWindow(rc);	
}
void CGuiMiniFrameWnd::OnSize(UINT nType, int cx, int cy)
{
	CMiniFrameWnd::OnSize(nType, cx, cy);
	RecalLayout();
	// TODO: Add your message handler code here
}

void CGuiMiniFrameWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CMiniFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	if ( nState == WA_INACTIVE && !bClick)
    {
		bClick=TRUE;
		pParent->UnlockWindowUpdate();
		pParent->Invalidate();
		pParent->UpdateWindow();
		OnCancelMode();
		PostMessage (WM_DESTROY);
		DestroyWindow();
		return ;
    }
	else
		RecalLayout();
	
	// TODO: Add your message handler code here
}

void CGuiMiniFrameWnd::OnCancelMode()
{
	pControl->ShowWindow(SW_HIDE);
	pControl->SetParent (pParent);

	// TODO: Add your message handler code here
}

BOOL CGuiMiniFrameWnd::OnNcActivate(BOOL bActive)
{
	// TODO: Add your message handler code here and/or call default
	BOOL bNc=CMiniFrameWnd::OnNcActivate(bActive);
	RecalLayout();
	SendMessage( WM_NCPAINT );
	return bNc;

}

void CGuiMiniFrameWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	SendMessage( WM_NCPAINT );
	// TODO: Add your message handler code here
	// Do not call CMiniFrameWnd::OnPaint() for painting messages
}

void CGuiMiniFrameWnd::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent==8889)
	{
		OnCancelMode();
		pParent->SetFocus();
		PostMessage (WM_DESTROY);
		DestroyWindow();
		bDestroy=TRUE;
		return;
	}
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
		KillTimer(1010);
		SendMessage(WM_NCPAINT); 		
	}
	
	
	CMiniFrameWnd::OnTimer(nIDEvent);
}



void CGuiMiniFrameWnd::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: Add your message handler code here and/or call default
	
	if (bClick==TRUE)
	{
		lpncsp->rgrc[0].top +=19;
		lpncsp->rgrc[0].right-=1;
		lpncsp->rgrc[0].bottom-=1;
	}
	else
	{
		lpncsp->rgrc[0].top +=9;
		lpncsp->rgrc[0].left-=1;
	}
	CMiniFrameWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
	
	
}

void CGuiMiniFrameWnd::OnSetFocus(CWnd* pOldWnd)
{
	SendMessage(WM_NCACTIVATE);
	CMiniFrameWnd::OnSetFocus(pOldWnd);
	// TODO: Add your message handler code here
}


UINT CGuiMiniFrameWnd::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rcWindow;
	//no se convierte las coordenadas de pantalla porque el punto
	//entregado por esta función esta dado en el mismo sentido.
	GetWindowRect(rcWindow);
	int it=0;
	CRect rcT=m_rcCloseBtn;
	ClientToScreen(rcT);
	CPoint pt=point;
	pt.y+=23;
	pt.x+=5;
	if (rcT.PtInRect(pt))
		return HTCLOSE;
	else
		return HTCAPTION;
	return CMiniFrameWnd::OnNcHitTest(point);
}

void CGuiMiniFrameWnd::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
        
	if (m_stateBtn != NORMAL) return;
	if (nHitTest == HTCLOSE)
	{
		m_stateBtn=OVER;
		SetTimer(1,100,0);
		SendMessage(WM_NCPAINT);
	}
	else if (nHitTest == HTCAPTION && !bClick)
	{
		SetCursor (LoadCursor(NULL, IDC_SIZEALL));
	}
	
	CMiniFrameWnd::OnNcMouseMove(nHitTest, point);
}

void CGuiMiniFrameWnd::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (bClick==FALSE)
	{
		pParent->UnlockWindowUpdate();
		pParent->Invalidate();
				pParent->UpdateWindow();

		bClick=TRUE;
		dwStyle|=MFS_MOVEFRAME|MFS_4THICKFRAME;
		CRect rc;
		GetWindowRect(rc);
		rc.DeflateRect(1,1);
		MoveWindow(rc);		

	}
	if (nHitTest == HTCLOSE)
	{
		m_stateBtn=PRESSBTN;
		OnCancelMode();
		DestroyWindow();
		return;
		
	}
	SetCursor (LoadCursor(NULL, IDC_SIZEALL));
	SendMessage(WM_NCPAINT);
	CMiniFrameWnd::OnNcLButtonDown(nHitTest, point);
}



