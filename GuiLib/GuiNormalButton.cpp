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
#include "guinormalbutton.h"
#include "GuiDrawLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CGuiNormalButton::CGuiNormalButton(void)
{
	m_stlbtn=STL_NORMAL;
	m_clColor=GuiDrawLayer::GetRGBColorFace();
}

CGuiNormalButton::~CGuiNormalButton(void)
{
}

void CGuiNormalButton::SetStyleButton(StyleBtn StlButton)
{
	m_stlbtn=StlButton;
}
//STL_NORMAL=0,STL_FLAT=1,STL_SEMIFLAT=2,STL_XP=3
void CGuiNormalButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC*  pdc= CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc=lpDrawItemStruct->rcItem;
	UINT  uState=lpDrawItemStruct->itemState;
	CBrush cb;
	cb.CreateSolidBrush(m_clColor);
	COLORREF clrTL =GuiDrawLayer::GetRGBColorBTNHigh();
	COLORREF clrBR =GuiDrawLayer::GetRGBColorShadow();
	pdc->FillRect(rc,&cb);
	

	if( uState & ODS_SELECTED) //the button is pressed
	{
		switch(m_stlbtn)
		{
		case STL_FLAT:	
		case STL_NORMAL:
		case STL_SEMIFLAT:
			pdc->Draw3dRect(rc,clrBR,clrTL);
			rc.DeflateRect(1,1);
			break;

		}
		
	}

	else if(m_bMouserOver)
	{
		switch(m_stlbtn)
		{
		case STL_FLAT:	
		case STL_NORMAL:
		case STL_SEMIFLAT:
			pdc->Draw3dRect(rc,clrTL,clrBR);
			rc.DeflateRect(1,1);
			break;

		}
	}else
	{
		switch(m_stlbtn)
		{
		case STL_NORMAL:
			pdc->Draw3dRect(rc,clrTL,clrBR);
			rc.DeflateRect(1,1);
			break;
		case STL_SEMIFLAT:
			pdc->Draw3dRect(rc,clrTL,clrBR);
			rc.DeflateRect(1,1);
			break;
		case STL_FLAT:
			break;
		}	
	}
	

	
	int calculodify;
	calculodify=rc.Height()-(m_SizeImage.cy);
	calculodify/=2;
	int nHeigh=calculodify+(m_bShowDark?1:0);
	int nWidth=rc.Width()/2 ;
	CPoint m_point=CPoint(nWidth,nHeigh);
	
	if (m_SizeImage.cx > 2)
	{
		if(m_bMouserOver == 1 && !(uState & ODS_DISABLED) && !(uState & ODS_SELECTED) && m_bShowDark)
		{
			CPoint p(m_point.x+1,m_point.y+1);
			pdc->DrawState(p,m_SizeImage,m_Icon,DSS_MONO,CBrush (GuiDrawLayer::GetRGBColorShadow()));
			m_point.x-=1; m_point.y-=1;
		}
		pdc->DrawState (m_point, m_SizeImage,m_Icon,
					(uState==ODS_DISABLED?DSS_DISABLED:DSS_NORMAL),(CBrush*)NULL);
	}
	if (m_SizeText.cx > 2)
	{
		int nMode = pdc->SetBkMode(TRANSPARENT);
		CRect rectletra=rc;
		rectletra.left+=m_SizeImage.cx;
		CPoint pt=CSize(rectletra.top,rectletra.left);
		if (uState & ODS_DISABLED)
			pdc->DrawState(pt, m_SizeText, m_szText, DSS_DISABLED, TRUE, 0, (CBrush*)NULL);
		else
			pdc->DrawText(m_szText,rectletra,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
		pdc->SetBkMode(nMode);
	}
}

