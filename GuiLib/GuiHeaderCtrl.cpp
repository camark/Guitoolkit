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
#include "GuiHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiHeaderCtrl

CGuiHeaderCtrl::CGuiHeaderCtrl()
{
	m_clrFace= ::GetSysColor(COLOR_3DFACE);
	m_clrShadow= ::GetSysColor(COLOR_BTNSHADOW);
	m_clrLight= ::GetSysColor(COLOR_BTNHIGHLIGHT);
	m_nNumbottomSelect=-1;
	m_bSentido=TRUE;
}

CGuiHeaderCtrl::~CGuiHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CGuiHeaderCtrl, CHeaderCtrl)
	//{{AFX_MSG_MAP(CGuiHeaderCtrl)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiHeaderCtrl message handlers

//***************************************************************************
void CGuiHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC		*pDC	=	CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect	rcitem	=	lpDrawItemStruct->rcItem;
	UINT	uState	=	lpDrawItemStruct->itemState;
	int     nItemID =   lpDrawItemStruct->itemID;
	CBrush	m_brush;
	CString m_caption;
	CSize	siImg=CSize(0,0);
	TCHAR caption[256];
	IMAGEINFO pImageInfo;
	int OldMode=pDC->SetBkMode(TRANSPARENT);
	m_brush.CreateSysColorBrush(COLOR_3DFACE);
	pDC->FillRect(rcitem,&m_brush);
	HDITEM hdi;
	hdi.mask = HDI_TEXT | HDI_FORMAT|HDI_IMAGE| HDI_ORDER;
	hdi.pszText = caption;
	hdi.cchTextMax = 255;
	GetItem( nItemID, &hdi );
	//---------------------------------------------------------
	//se mueve la imagen para dar la sensacion
	//de seleccion del item
	//---------------------------------------------------------
	if (uState == ODS_SELECTED) 
	{
		rcitem.left+=1;
		rcitem.top+=1;
	}

	if (m_nNumbottomSelect==nItemID)
	{
		DrawArrow(pDC,rcitem,m_bSentido);
		rcitem.right-=12;
	}
	
	if (hdi.iImage > -1)
	{
		m_img.GetImageInfo(hdi.iImage,&pImageInfo);
		CRect rcima =pImageInfo.rcImage;
		siImg=CSize(rcima.Width(),rcima.Height());
		CPoint pti(rcitem.left+2,rcitem.top+1);
		m_img.Draw(pDC, hdi.iImage, pti, ILD_TRANSPARENT);
	}
	if (lstrlen(caption) > 0)
		{
			CRect m_rctext=rcitem;
			m_rctext.left+=siImg.cx+4;
			m_rctext.bottom-=2;
			DrawTextExt(caption,pDC,&m_rctext,DT_SINGLELINE|DT_BOTTOM);
			
		}
	pDC->SetBkMode(OldMode);

	
}

//**********************************************************************************
void CGuiHeaderCtrl::DrawTextExt(CString Cad,CDC* pDC,CRect* rc,UINT nFlags)
{
	CString m_cadBreak=Cad;
	int c=0;
	int cont=m_cadBreak.GetLength();
	CSize coor=pDC->GetTextExtent(m_cadBreak,m_cadBreak.GetLength());
	if (coor.cx > rc->Width()-1)
	{
		while(cont > 1 )
		{
			CString m_scadtemp=m_cadBreak+"...";
			coor=pDC->GetTextExtent(m_scadtemp,m_scadtemp.GetLength());
			if(coor.cx > rc->Width())
				m_cadBreak=m_cadBreak.Left(m_cadBreak.GetLength()-1);
			else
				break;
			cont--;
		}
		m_cadBreak+=_T("...");
		rc->right+=3;
	}
	pDC->DrawText(m_cadBreak,rc,nFlags);

}

//********************************************************************************
void CGuiHeaderCtrl::DrawArrow(CDC* pDC,CRect rc,BOOL bUp)
{
	CPen cp(PS_SOLID,1, m_clrFace);
	CPen cps(PS_SOLID,1, m_clrShadow);
	CPen cpw(PS_SOLID,1, m_clrLight);
	CPen *pOld;
	
	rc.left=rc.right-12;
	rc.right=rc.left+8;
	rc.bottom=rc.top+12;
	rc.top+=2;	
	int m_mitad=rc.left+4;
	
	if (bUp == TRUE)
	{
			//linea izquierda
			pOld=pDC->SelectObject(&cps);
			pDC->MoveTo(rc.left,rc.bottom);
			pDC->LineTo(m_mitad,rc.top);
			//linea derecha
			pDC->SelectObject(&cpw);
			pDC->MoveTo(rc.right,rc.bottom);
			pDC->LineTo(m_mitad,rc.top);
			//linea de abajo
			pDC->MoveTo(rc.left,rc.bottom);
			pDC->LineTo(rc.right,rc.bottom);
	}
	else
	{
			rc.bottom=rc.top+12;
			rc.top+=4;	
			//linea izquierda
			pOld=pDC->SelectObject(&cps);
			pDC->MoveTo(rc.left,rc.top);
			pDC->LineTo(m_mitad,rc.bottom);
			//linea superior
			pDC->MoveTo(rc.left,rc.top);
			pDC->LineTo(rc.right,rc.top);
			//linea derecha
				pDC->SelectObject(&cpw);
			pDC->MoveTo(rc.right,rc.top);
			pDC->LineTo(m_mitad,rc.bottom);

	}

	pDC->SelectObject(pOld);
}

//*******************************************************************

void CGuiHeaderCtrl::DelImageCol(int icol,int img)
{
	HDITEM hdi;
	GetItem(icol,&hdi);
	hdi.iImage=-1;
	hdi.fmt |=  HDF_IMAGE;
	hdi.mask |= HDI_IMAGE | HDI_FORMAT;
	SetItem(icol,&hdi);
}

//*********************************************************************
void CGuiHeaderCtrl::SetImageCol(int icol,int img)
{
	HDITEM hdi;
	GetItem(icol,&hdi);
	hdi.iImage=img;
	hdi.fmt |=  HDF_IMAGE;
	hdi.mask |= HDI_IMAGE | HDI_FORMAT;
	SetItem(icol,&hdi);
}

//********************************************************************
int CGuiHeaderCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CHeaderCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_pParentWnd = CWnd::FromHandle(lpCreateStruct->hwndParent);
	ASSERT(m_pParentWnd);

	return 0;
}

//********************************************************************
void CGuiHeaderCtrl::PreSubclassWindow() 
{
	m_pParentWnd = GetParent();
	ASSERT(m_pParentWnd);
	CHeaderCtrl::PreSubclassWindow();
	ClearImages();
	ReDraw(); 
}

//********************************************************************
void CGuiHeaderCtrl::ReDraw() 
{
	int iNumItems=GetItemCount();
	HDITEM m_hditems;
	m_hditems.fmt  |= HDF_OWNERDRAW;
	for (int i =0; i < iNumItems; i++)
		SetItem(i,&m_hditems);

}

//*********************************************************************
void CGuiHeaderCtrl::ClearImages()
{
	HDITEM m_hditems;
	m_hditems.mask |=HDI_FORMAT|HDI_IMAGE;
	int iNumItems=GetItemCount();
	for (int i =0; i < iNumItems; i++)
	{
		m_hditems.iImage=-1;
		SetItem(i,&m_hditems);
	}

}

//********************************************************************
void CGuiHeaderCtrl::OnPaint() 
{
	
	
	CPaintDC	dc(this); // device context for painting
	CDC			MemDC;
	CBitmap		m_BitmapMemDC;
	CRect		rcClient;
	CRect		rcWin;
	CBrush		m_brush;
	//******************************************
	GetWindowRect( &rcWin);
	GetClientRect( &rcClient );
	MemDC.CreateCompatibleDC(&dc);
	m_BitmapMemDC.CreateCompatibleBitmap(&dc,
				  rcClient.Width(),rcClient.Height());	

	CBitmap* m_bitmapOld=MemDC.SelectObject(&m_BitmapMemDC);
	m_brush.CreateSysColorBrush(COLOR_3DFACE);
	MemDC.FillRect(rcClient,&m_brush); //evita el horrible color negro
	//*****************************************************
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)MemDC.m_hDC, 0 );	
	//*****************************************************
	ScreenToClient(rcWin);
	BiselaBoton(rcWin,&MemDC);
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&MemDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();

}

//************************************************************************
void CGuiHeaderCtrl::BiselaBoton(CRect rcWin,CDC* pDC)
{
	CPen cp(PS_SOLID,1, m_clrFace);
	CPen cps(PS_SOLID,1, m_clrShadow);
	CPen cpw(PS_SOLID,1, m_clrLight);

	//***************************************************
	pDC->Draw3dRect(rcWin,m_clrLight,m_clrShadow);
	rcWin.DeflateRect(1,1);
	pDC->Draw3dRect(rcWin,m_clrFace,m_clrFace);
	//***************************************************

	CPen* cpold=pDC->SelectObject(&cp);	
	int iNumItems=GetItemCount();
	int iContx=0;
	HDITEM m_hditems;
	
	for (int i =0; i < iNumItems; i++)
	{
		CRect recItem;
		GetItem(i,&m_hditems);
		GetItemRect(i, recItem);
		iContx+=recItem.Width();
		//quitamos todas las lineas
		recItem.DeflateRect(1,1);
		pDC->SelectObject(&cp);
		pDC->MoveTo(iContx-2,rcWin.top+1);
		pDC->LineTo(iContx-2,rcWin.bottom-1);
		pDC->MoveTo(iContx-1,rcWin.top+1);
		pDC->LineTo(iContx-1,rcWin.bottom-1);
		pDC->MoveTo(iContx,rcWin.top+1);
		pDC->LineTo(iContx,rcWin.bottom-1);
		pDC->MoveTo(iContx+1,rcWin.top+1);
		pDC->LineTo(iContx+1,rcWin.bottom-1);
		//ponemos dos para dar el efecto
		pDC->SelectObject(&cps);
		pDC->MoveTo(iContx-1,rcWin.top+2);
		pDC->LineTo(iContx-1,rcWin.bottom-2);
		pDC->SelectObject(&cpw);
		pDC->MoveTo(iContx,rcWin.top+2);
		pDC->LineTo(iContx,rcWin.bottom-2);
	
	}
	pDC->SelectObject(cpold);

}

//*********************************************************************
void CGuiHeaderCtrl::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CHeaderCtrl::OnWindowPosChanged(lpwndpos);
	Invalidate();
	UpdateWindow();
	ReDraw();

}

//*********************************************************************************
BOOL CGuiHeaderCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

//*********************************************************************************
void CGuiHeaderCtrl::SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	CBitmap cbmp;
	BITMAP bmp;
	m_img.Create(nBitmapID,cx,nGrow,crMask);
	cbmp.LoadBitmap(nBitmapID);
	cbmp.GetBitmap(&bmp);
	m_img.Add(&cbmp,crMask);
	m_sizeImag=CSize(cx,bmp.bmHeight);	
	
}

int CGuiHeaderCtrl::GetSortColumn(BOOL* bSortCol )
{
	*bSortCol =m_bSentido;
	return m_nNumbottomSelect;

}

void CGuiHeaderCtrl::SetSortColumn(int nCol,BOOL sentido)
{
	m_nNumbottomSelect	=nCol;
	m_bSentido=sentido;
	Invalidate();
	UpdateWindow();
}


