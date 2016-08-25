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
#include "GuiStatusBar.h"
#include "GuiDrawLayer.h"

// CGuiStatusBar

IMPLEMENT_DYNAMIC(CGuiStatusBar, CStatusBar)
CGuiStatusBar::CGuiStatusBar()
{
	m_Style=DEVSTUDIO;
	m_cfont.CreateFont(14,0,0,0,400,0,0,0,0,1,2,1,34,"Arial");
	m_StyleDisplay=GUISTYLE_XP;
}

CGuiStatusBar::~CGuiStatusBar()
{
}


BEGIN_MESSAGE_MAP(CGuiStatusBar, CStatusBar)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CGuiStatusBar message handlers

void CGuiStatusBar::SetStyle(Style nStyle)
{
	m_Style=nStyle;
}
void CGuiStatusBar::PreSubclassWindow() 
{
	ModifyStyle(0,BS_OWNERDRAW);
	CStatusBar::PreSubclassWindow();
}

void CGuiStatusBar::OnPaint()
{
	CRect rcClient,rcTemp;
	CBrush cb;
	CPaintDC dc(this); 
	GetClientRect(&rcClient);
	cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace(m_StyleDisplay));
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)dc.m_hDC, 0 );
	rcTemp=rcClient;
	rcClient.bottom=rcClient.top+2;
	rcClient.right+=50;
//	dc.FillRect(rcClient,&cb);
	Drawpanels(&dc);
	cb.DeleteObject();
}

void  CGuiStatusBar::Drawpanels(CDC *pDC)
{
	int iCont=GetCount();
	CRect rcCli,rcCliente;
	CString m_cad;
	int OldMode=pDC->SetBkMode(TRANSPARENT);
	for (int i=0; i < iCont; i++)
	{
		GetItemRect(i,&rcCli);
		GetPaneText(i, m_cad);
		if (i == iCont-1)
		{
			CSize m_sChar=pDC->GetTextExtent(m_cad,m_cad.GetLength());
			if (rcCli.Width() < m_sChar.cx)
			{
				int dif=m_sChar.cx-rcCli.Width();
				rcCli.right=rcCli.left+m_sChar.cx-dif;
			}
			
		}
		
		/*if(m_StyleDisplay=GUISTYLE_2003)
		{
			CFont m_fontMenu;
			NONCLIENTMETRICS info;
			info.cbSize = sizeof(info);
			SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);
			VERIFY(m_fontMenu.CreateFontIndirect(&info.lfMenuFont));
			CFont* oldfont=(CFont*)pDC->SelectObject(&m_fontMenu);
			CGradient M(CSize(rcCli.Width(),rcCli.Height()));	
			M.PrepareReverseVert(pDC,m_StyleDisplay);
			M.Draw(pDC,rcCli.left,rcCli.top,0,0,rcCli.Width(),rcCli.Height(),SRCCOPY);
			rcCli.top+=2;
			rcCli.left+=3;
			pDC->DrawText(m_cad,rcCli,DT_LEFT   );
			pDC->SelectObject(oldfont);

		}
		else
		{*/
			if (m_Style == DEVSTUDIO)
				pDC->Draw3dRect(rcCli,GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style),GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
			else
				pDC->Draw3dRect(rcCli,GuiDrawLayer::GetRGBColorTabs(),GuiDrawLayer::GetRGBColorTabs());
		//}
		if (i == iCont-1)
		{
			rcCli.left=rcCli.right;
			rcCli.right=rcCli.left+2;
			pDC->Draw3dRect(rcCli,GuiDrawLayer::GetRGBColorFace(),GuiDrawLayer::GetRGBColorFace());
			rcCli.right+=1;
			pDC->Draw3dRect(rcCli,GuiDrawLayer::GetRGBColorFace(),GuiDrawLayer::GetRGBColorFace());
			rcCli.right+=1;
			pDC->Draw3dRect(rcCli,GuiDrawLayer::GetRGBColorFace(),GuiDrawLayer::GetRGBColorFace());

		}
		
		
	
	}

	pDC->SetBkMode(OldMode);
	GetClientRect(&rcCliente);
	if ((rcCliente.right - rcCli.right) != 0)
	{
		CBrush cb;
		cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace());
		rcCliente.left = rcCli.right;
		rcCliente.bottom= rcCliente.top+6;
		pDC->FillRect(rcCliente,&cb);
		//DrawLB(&rcCliente,pDC);
	}

	CRect rc;
	GetClientRect(&rc);
	rc.left=rc.right-15;
	rc.top=rc.bottom-15;
	CPen pWhite;
	CPen pDark;
	pWhite.CreatePen(PS_SOLID,1,RGB(255,255,255));
	pDark.CreatePen(PS_SOLID,1,GuiDrawLayer::m_Style==GUISTYLE_2003?GuiDrawLayer::GetRGBColorShadow():GuiDrawLayer::GetRGBPressBXP());
	CPen* pPt= pDC->SelectObject(&pWhite);
	pDC->MoveTo(rc.left,rc.bottom);
	pDC->LineTo(rc.right,rc.top);
	pDC->SelectObject(&pDark);
	pDC->MoveTo(rc.left+1,rc.bottom);
	pDC->LineTo(rc.right,rc.top+1);
	pDC->MoveTo(rc.left+2,rc.bottom);
	pDC->LineTo(rc.right,rc.top+2);
	pDC->SelectObject(&pWhite);
	pDC->MoveTo(rc.left+4,rc.bottom);
	pDC->LineTo(rc.right,rc.top+4);
	pDC->SelectObject(&pDark);
	pDC->MoveTo(rc.left+5,rc.bottom);
	pDC->LineTo(rc.right,rc.top+5);
	pDC->MoveTo(rc.left+6,rc.bottom);
	pDC->LineTo(rc.right,rc.top+6);
	pDC->SelectObject(&pWhite);
	pDC->MoveTo(rc.left+8,rc.bottom);
	pDC->LineTo(rc.right,rc.top+8);
	pDC->SelectObject(&pDark);
	pDC->MoveTo(rc.left+9,rc.bottom);
	pDC->LineTo(rc.right,rc.top+9);
	pDC->MoveTo(rc.left+10,rc.bottom);
	pDC->LineTo(rc.right,rc.top+10);

	pDC->SelectObject(&pWhite);
	pDC->MoveTo(rc.left+12,rc.bottom);
	pDC->LineTo(rc.right,rc.top+12);
	pDC->SelectObject(&pDark);
	pDC->MoveTo(rc.left+13,rc.bottom);
	pDC->LineTo(rc.right,rc.top+13);
	pDC->SelectObject(pPt);

}

void CGuiStatusBar::ClearRect(CDC* pDC,CRect rc)
{
	CRect rcCli=rc;
	rcCli.left+=1;
	rcCli.top+=1;
	for (int i=0; i < 3; i++)
	{
		rcCli.right-=1;
		rcCli.bottom-=1;
        pDC->Draw3dRect(rcCli,GuiDrawLayer::GetRGBColorFace(),GuiDrawLayer::GetRGBColorFace());
	}
}
void CGuiStatusBar::DrawLB(CRect* rcLb,CDC* pDC)
{
	pDC->SelectStockObject(COLOR_3DSHADOW);
	int gap=10;
	for (int i=0; i< 3; i++)
	{
		pDC->MoveTo(rcLb->left+gap,rcLb->bottom);
		pDC->LineTo(rcLb->right,rcLb->top+gap+1);
		gap+=2;
	}
}

void CGuiStatusBar::SetPanelText(CString szText,UINT uPanel)
{
	int nIndex=CommandToIndex(uPanel);
	SetPaneText(nIndex,szText);
	CWindowDC dc(this);
	CSize sizeText=dc.GetTextExtent(szText);
	SetPaneInfo(nIndex,uPanel,SBPS_NORMAL,sizeText.cx);

}


BOOL CGuiStatusBar::SetIndicators (const UINT* lpIDArray, int nIDCount)
{
    if ( !CStatusBar::SetIndicators (lpIDArray, nIDCount) )
    {
        return false;
    }
    //SendMessage (SB_SETMINHEIGHT, 20);

    for ( int nIndex = 0; nIndex < nIDCount; nIndex++ )
    {
        UINT nID;
		UINT nStyle;
        int cxWidth;
        GetPaneInfo (nIndex, nID, nStyle, cxWidth);
        SetPaneInfo (nIndex, nID, nStyle|SBPS_NOBORDERS, cxWidth);
    }
    return true;
}