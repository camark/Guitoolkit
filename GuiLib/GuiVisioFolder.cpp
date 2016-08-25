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
#include "guivisiofolder.h"
#include "guiDrawLayer.h"
#include "Guivisiofolder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CGuiVisioFolder, CGuiFolder)

void  CGuiVisioFolder::SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	CBitmap cbmp;
	BITMAP bmp;
	m_Img.Create(nBitmapID,cx,nGrow,crMask);
	cbmp.LoadBitmap(nBitmapID);
	cbmp.GetBitmap(&bmp);
	m_Img.Add(&cbmp,crMask);

}



void CGuiVisioFolder::DrawFolder(CFolderBar* cfb,Style m_Style)
{
	CRect rc=cfb->m_rect;
	CRect rcWin=cfb->m_rect;
	int nNuImage=cfb->m_img;
	CString szStringPoints=_T("...");
	CBrush cb;
	CClientDC pDC(this);
	cb.CreateSysColorBrush(COLOR_BTNFACE);
	rc.top+=1;
	pDC.FillRect(&rc,&cb);
	
	//se pintan  bordes que simulen un boton

	if (m_Style == mNormal)  //el folder no tiene el mouse 
	{
				
		pDC.Draw3dRect(rc, GuiDrawLayer::GetRGBColorBTNHigh(),GuiDrawLayer::GetRGBColorShadow());
		rc.DeflateRect(1,1);
		pDC.Draw3dRect(rc, GuiDrawLayer::GetRGBColorFace(),GuiDrawLayer::GetRGBColorShadow());
	}
	else if (m_Style == mFlat) //el mouse esta sobre el folder pero no presiona
		pDC.Draw3dRect(rc, GuiDrawLayer::GetRGBColorBTNHigh(),GuiDrawLayer::GetRGBColorShadow());
	else if (m_Style == mPush) //el mouse esta sobre el folder y presiona
		pDC.Draw3dRect(rc, GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorBTNHigh());
	int OldMode=pDC.SetBkMode(TRANSPARENT);
	cfont = pDC.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	CString m_cadBreak=cfb->m_lpMsg;
	int cont=m_cadBreak.GetLength();
	CSize coor=pDC.GetTextExtent(m_cadBreak,m_cadBreak.GetLength());
	CSize szImage=CSize(0,0);

	//se dibuja la imagen
	if(nNuImage != -1) 
	{
		IMAGEINFO pImageInfo;
		m_Img.GetImageInfo(nNuImage,&pImageInfo);
		CRect rcima =pImageInfo.rcImage;
		szImage=CSize(rcima.Width(),rcima.Height());
		CPoint pti=CPoint(rc.left+2,rc.top+3);
		m_Img.Draw(&pDC, nNuImage, pti, ILD_TRANSPARENT);
	}
	
	//guardar espacio para la imagen
	rc.left+=szImage.cx+4;
	rc.right-=8;
	if ( coor.cx > rc.Width())
	{
		rc.left+=1;
		while(cont > 1 )
		{
			CString m_scadtemp=m_cadBreak+szStringPoints;
			CSize coor=pDC.GetTextExtent(m_scadtemp,m_scadtemp.GetLength());
			if(coor.cx > rc.Width())
				m_cadBreak=m_cadBreak.Left(m_cadBreak.GetLength()-1);
			else
				break;
			cont--;
		}
		m_cadBreak+=szStringPoints;
		rc.right+=3;
		
			pDC.DrawText(m_cadBreak,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	}
	else
		pDC.DrawText(cfb->m_lpMsg,rc,DT_WORDBREAK|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	//----se dibuja el gripper----------

	rcWin.top+=5;
	rcWin.right-=4;
	rcWin.left=rcWin.right-3;
	rcWin.bottom-=4;

	for (int i=0; i < rcWin.Height(); i+=2)
	{
		CRect rcWindow;
		CBrush cb;
		cb.CreateSolidBrush(::GetSysColor(COLOR_BTNSHADOW));
		rcWindow=rcWin;
		rcWindow.top=rcWin.top+i;
		rcWindow.bottom=rcWindow.top+1;
		pDC.FillRect(rcWindow,&cb);
		cb.DeleteObject();			
	}
	//-------------------------
	cb.DeleteObject();
   	pDC.SetBkColor(OldMode);
	
}

CGuiVisioFolder::CGuiVisioFolder(void)
{
	
}

CGuiVisioFolder::~CGuiVisioFolder(void)
{
}

BEGIN_MESSAGE_MAP(CGuiVisioFolder, CGuiFolder)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	
END_MESSAGE_MAP()

void CGuiVisioFolder::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CGuiFolder::OnMouseMove(nFlags, point);
	::SetCursor(::LoadCursor(NULL,MAKEINTRESOURCE(32649)));//IDC_HAND));
	
}

void CGuiVisioFolder::OnLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	::SetCursor(::LoadCursor(NULL,MAKEINTRESOURCE(32649)));
	CGuiFolder::OnLButtonDown(nHitTest, point);
}