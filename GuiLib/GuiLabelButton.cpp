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
#include "guilabelbutton.h"
#include "GuiDrawLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CGuiLabelButton,CGuiToolButton)

CGuiLabelButton::CGuiLabelButton(void)
{
	m_cfont.CreateFont(14,0,0,0,FW_BOLD,0,0,0,0,1,2,1,34,_T("Arial"));
	m_bDrawLine=FALSE;
}

CGuiLabelButton::~CGuiLabelButton(void)
{
}

void CGuiLabelButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC*  pdc= CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc=lpDrawItemStruct->rcItem;
	UINT  uState=lpDrawItemStruct->itemState;
	CFont* m_OldFont;
	CBrush cb;
	int calculodify;

	cb.CreateSolidBrush(m_clColor); //deberia ser blanco
	m_OldFont=pdc->SelectObject(&m_cfont);
	pdc->FillRect(rc,&cb);
	
	
	calculodify=rc.Height()-(m_SizeImage.cy);
	calculodify/=2;
	CPoint m_point=CPoint(2,calculodify+1);
	if (m_SizeImage.cx > 2)
	{
		pdc->DrawState (m_point, m_SizeImage,m_Icon,
					(uState==ODS_DISABLED?DSS_DISABLED:DSS_NORMAL),(CBrush*)NULL);
	}
	if (m_SizeText.cx > 2)
	{
		int nMode = pdc->SetBkMode(TRANSPARENT);
		CRect rectletra=rc;
		rectletra.left+=m_SizeImage.cx > 0 ? m_SizeImage.cx+8: 0;
		CPoint pt=CSize(rectletra.top,rectletra.left);
		if (uState & ODS_DISABLED)
			pdc->DrawState(pt, m_SizeText, m_szText, DSS_DISABLED, TRUE, 0, (CBrush*)NULL);
		else
			pdc->DrawText(m_szText,rectletra,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
		pdc->SetBkMode(nMode);
	}
	pdc->SelectObject(m_OldFont);	
	if (m_bDrawLine)
	{
		CPen p(PS_SOLID,1,GuiDrawLayer::GetRGBColorShadow());
		CPen* pOldPen=pdc->SelectObject(&p);
		pdc->MoveTo(rc.left,rc.bottom-2);
		pdc->LineTo(rc.right,rc.bottom-2);
		pdc->SelectObject(pOldPen);
	}
	// TODO:  Add your code to draw the specified item
}
