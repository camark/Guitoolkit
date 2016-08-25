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
#include "guifolderflat.h"
#include "GuiDrawLayer.h"
#include "Guifolderflat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CGuiFolderFlat::CGuiFolderFlat(void)
{
}

CGuiFolderFlat::~CGuiFolderFlat(void)
{
}


void CGuiFolderFlat::DrawFolder(CFolderBar* cfb,Style m_Style)
{
	CRect rc=cfb->m_rect;
	CBrush cb;
	CClientDC pDC(this);
	cb.CreateSysColorBrush(COLOR_BTNFACE);
	rc.top+=1;
	//rc.right-=1;
	rc.right+=1;
	pDC.FillRect(&rc,&cb);

	pDC.Draw3dRect(rc, GuiDrawLayer::GetRGBColorBTNHigh(),GuiDrawLayer::GetRGBColorShadow());
	
	int OldMode=pDC.SetBkMode(TRANSPARENT);
	cfont = pDC.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	CString m_cadBreak=cfb->m_lpMsg;
	int cont=m_cadBreak.GetLength();
	CSize coor=pDC.GetTextExtent(m_cadBreak,m_cadBreak.GetLength());
	if ( coor.cx > rc.Width())
	{
		rc.left+=1;
		while(cont > 1 )
		{
			CString m_scadtemp=m_cadBreak+"...";
			CSize coor=pDC.GetTextExtent(m_scadtemp,m_scadtemp.GetLength());
			if(coor.cx > rc.Width())
				m_cadBreak=m_cadBreak.Left(m_cadBreak.GetLength()-1);
			else
				break;
			cont--;
		}
		m_cadBreak+=_T("...");
		rc.right+=3;
		
			pDC.DrawText(m_cadBreak,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	}
	else
	{
	  if (m_typel!=mOutlook)
			pDC.DrawText(cfb->m_lpMsg,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	  else	
			pDC.DrawText(cfb->m_lpMsg,rc,DT_WORDBREAK|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	}

   	pDC.SetBkColor(OldMode);


}
BEGIN_MESSAGE_MAP(CGuiFolderFlat, CGuiFolder)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CGuiFolderFlat::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(::LoadCursor(NULL,IDC_SIZEALL));
	CGuiFolder::OnLButtonDown(nFlags, point);
}
