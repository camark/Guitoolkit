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
#include "guitabpowerpoint.h"
#include "GuiDrawLayer.h"
#include "GuiBaseTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CGuiTabPowerPoint::CGuiTabPowerPoint(void)
{
	bAutoAjust=TRUE;
	m_clrTabs=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Theme);
	m_bShowButton=TRUE;
	
}

CGuiTabPowerPoint::~CGuiTabPowerPoint(void)
{
}
BEGIN_MESSAGE_MAP(CGuiTabPowerPoint, CGuiTabWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()



BOOL CGuiTabPowerPoint::OnCommand(WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = (HWND) lParam;	
	if (m_ToolButton.GetSafeHwnd() == hwnd)
	{
		UINT x=m_ToolButton.GetDlgCtrlID();
		CWnd* pParent= GetParent();
		pParent->SendMessage (WM_COMMAND,x);
	//	AfxGetMainWnd()->SendMessage(WM_COMMAND,x);
	}
	return TRUE;

}


void CGuiTabPowerPoint::AjustTabs()
{
	
	int m_iSizeAct=0;
	m_iMinValRec=4;
	CClientDC dc(this);
	GetClientRect(m_rectCliente);
	m_rectCliente.bottom=m_rectCliente.top+(m_sizeImag.cy+4+1);

	CFont* m_fontOld=dc.SelectObject(&m_cfont);
	for (int iCont=0; iCont< m_Numtabs;iCont++)
	{
		CGuiTab* ct=(CGuiTab*) m_pArray[iCont];
		CRect m_Arect;
		CSize m_sChar=dc.GetTextExtent(ct->lpMsg);
		m_Arect.left=m_iMinValRec+1;
		m_iMinValRec+=m_alnTab!=ALN_TOP?m_sizeImag.cx+2+m_sChar.cx+14:m_sChar.cx+14;
		if(m_alnTab==ALN_BOTTOM)
		{
			m_Arect.top=m_rectCliente.bottom;
			m_Arect.right=m_iMinValRec;
			m_Arect.bottom=m_rectCliente.bottom+4+m_sizeImag.cy;
		}
		else
		{
			m_Arect.top=m_rectCliente.top;
			m_Arect.right=m_iMinValRec;
			m_Arect.bottom=m_rectCliente.top+4+m_sizeImag.cy;
		}
		ct->rect= m_Arect;
		
	}		
	dc.SelectObject(m_fontOld);
	
	if (bAutoAjust)
	{
		int m_NewResize=4;
		if (m_iMinValRec > m_rectCliente.Width()-4)
		{
			m_iSizeAct=(m_rectCliente.Width()-12)/m_Numtabs;
			for (int iCont=0; iCont< m_Numtabs;iCont++)
			{

				CGuiTab* ct=(CGuiTab*) m_pArray[iCont];
				if (ct->uIcon != -1)
				{
					if (m_sizeImag.cx+22 > m_NewResize+m_iSizeAct)
						continue;
				}
				CRect m_Arect;
				m_Arect.left=m_NewResize;
				m_Arect.right=m_NewResize+m_iSizeAct;
				m_Arect.top=m_alnTab==ALN_TOP? m_rectCliente.top:m_rectCliente.bottom;
				m_Arect.bottom=m_alnTab==ALN_TOP? m_rectCliente.top+4+m_sizeImag.cy:m_rectCliente.bottom+4+m_sizeImag.cy;
				m_NewResize+=m_iSizeAct+1;
				ct->rect= m_Arect;
			}	
		}
	}


}




void CGuiTabPowerPoint::Drawtabs(CDC* dc)
{
	CBrush cb;
	CRect rectText;
	CRect rc;
	int nHeight=0;
	CBrush cbr;
	CPen cp(PS_SOLID,1,::GetSysColor(COLOR_BTNSHADOW));
	CPen cpw(PS_SOLID,1,GuiDrawLayer::GetRGBColorWhite());
	
	cbr.CreateSolidBrush(m_clrTabs);
	dc->FillRect(m_rectTab,&cbr);
	CFont* m_fontOld=dc->SelectObject(&m_cfont);
	CPen penShadow(PS_SOLID, 1, GuiDrawLayer::GetRGBColorShadow());
	CPen* pOldPen;
	dc->MoveTo(m_rectTab.left,m_rectTab.bottom-1);
	dc->LineTo(m_rectTab.right,m_rectTab.bottom-1);
	int nMode = dc->SetBkMode(TRANSPARENT);
	int m_right=0;

	pOldPen=dc->SelectObject(&penShadow);
	for ( int iCont=0; iCont< m_Numtabs;iCont++)
	{	

		
		CGuiTab* ctb=(CGuiTab*)m_pArray[iCont];
		CRect mrt=ctb->rect;		
		int ancho=mrt.Width();
		mrt.left=m_right;
		mrt.right=mrt.left+ancho;
		CPoint Coor[4];
		CPoint CoorFive[6];
				
				if (iCont-1 == m_iSelectTab ) 
				{	
					CBrush brushRed(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Theme));
					CBrush* pOldBrush = dc->SelectObject(&brushRed);
					CoorFive[0].x=mrt.left+(m_rectTab.Height()/4)+1;			
					CoorFive[0].y=(mrt.bottom-m_rectTab.Height()/2)+1;
					CoorFive[1].x=(mrt.left)+m_rectTab.Height()/2;			
					CoorFive[1].y=mrt.top+1;
					CoorFive[2].x=(mrt.right)-m_rectTab.Height()/2;			
					CoorFive[2].y=mrt.top+1;
					
					if (iCont == m_Numtabs-1)
					{
						CoorFive[3].x=mrt.right-2;			
						CoorFive[3].y=mrt.bottom+1;
					}
					else
					{
						CoorFive[3].x=(mrt.right)-5;			
						CoorFive[3].y=(mrt.bottom-(m_rectTab.Height()/2))+1;
					}

					CoorFive[4].x=(mrt.right)-8;			
					CoorFive[4].y=mrt.bottom+1;

					CoorFive[5].x=(mrt.left)+9;			
					CoorFive[5].y=mrt.bottom+1;

					
					dc->Polygon(CoorFive,6);	
					dc->SelectObject(pOldBrush);
				}
				else
				{
					CBrush brushRed(GuiDrawLayer::GetRGBColorXP());
					CBrush* pOldBrush = dc->SelectObject(&brushRed);

					CoorFive[0].x=mrt.left;			
					CoorFive[0].y=mrt.bottom+1;
					CoorFive[1].x=(mrt.left)+m_rectTab.Height()/2;			
					CoorFive[1].y=mrt.top+1;
					CoorFive[2].x=(mrt.right)-m_rectTab.Height()/2;			
					CoorFive[2].y=mrt.top+1;
					
					if (iCont == m_iSelectTab || iCont == m_Numtabs-1 )
					{
						CoorFive[3].x=mrt.right-2;			
						CoorFive[3].y=mrt.bottom+1;
					}
					else
					{
						CoorFive[3].x=(mrt.right)-5;			
						CoorFive[3].y=(mrt.bottom-(m_rectTab.Height()/2))+1;
					}
					
					CoorFive[4].x=(mrt.right)-8;			
					CoorFive[4].y=mrt.bottom+1;

					CoorFive[5].x=(mrt.left)+9;			
					CoorFive[5].y=mrt.bottom+1;
					
					
					dc->Polygon(CoorFive,6);	
					dc->SelectObject(pOldBrush);
					
				}
				m_right=mrt.right;
			if (iCont == m_iSelectTab )
			{
				CBrush brushRed(GuiDrawLayer::GetRGBColorWhite());
				CBrush* pOldBrush = dc->SelectObject(&brushRed);
				Coor[0].x=mrt.left;
				Coor[0].y=mrt.bottom;
				Coor[1].x=(mrt.left)+m_rectTab.Height()/2;
				Coor[1].y=mrt.top+1;
				Coor[2].x=(mrt.right)-m_rectTab.Height()/2; 
				Coor[2].y=mrt.top+1;
				Coor[3].x=(mrt.right-1);
				Coor[3].y=mrt.bottom;
				dc->Polygon(Coor,4);	
				dc->SelectObject(pOldBrush);
				CPen* pOldPen=dc->SelectObject(&cpw);
				dc->MoveTo(mrt.left+1,mrt.bottom);
				dc->LineTo(mrt.right-1,mrt.bottom);
				dc->MoveTo(mrt.left+1,mrt.bottom+1);
				dc->LineTo(mrt.right-1,mrt.bottom+1);
				dc->SelectObject(pOldPen);
				
				
			}

			m_fontOld=dc->SelectObject(&m_cfont);
			dc->SetBkMode(TRANSPARENT);
			CRect mrtt=mrt; mrtt.top+=2;
			CSize m_sChar=dc->GetTextExtent(ctb->lpMsg,lstrlen(ctb->lpMsg));
			ctb->rect=mrt;
			m_right-=(m_rectTab.Height()/2);	
			if (m_sChar.cx < ctb->rect.Width()-8)  
				{
					rectText=ctb->rect;
					dc->DrawText(ctb->lpMsg,mrtt,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
				}
				else
				{
					int nDif= ctb->rect.Width()-m_sizeImag.cx;
					nDif/=2;
					if(ctb->uIcon == -1) continue;
					Image.Draw(dc,ctb->uIcon,CPoint(ctb->rect.left+nDif,ctb->rect.top+2),ILD_TRANSPARENT);
					CToolTip.SetToolRect(this,iCont+1,CRect(0,0,0,0));
				}
				
			
		}





	GetClientRect(rc);
	if (m_ToolButton.GetSafeHwnd())
	{
		CSize m_SizeBtn=m_ToolButton.GetSizeButton();
		if (m_bShowButton==TRUE)
		{
			if (m_right+m_SizeBtn.cx > rc.Width())
				m_ToolButton.ShowWindow(SW_HIDE);
			else
			{
				rc.left=rc.right-(m_SizeBtn.cx+2);
				rc.bottom=m_rectTab.Height()-2;
				m_ToolButton.MoveWindow(rc.left,rc.top+1,m_SizeBtn.cx,rc.bottom-1);
				m_ToolButton.ShowWindow(SW_SHOW);
			}
		}
	}
	cbr.DeleteObject();
	dc->SetBkMode(nMode);
	dc->SelectObject(m_fontOld);
	dc->SelectObject(pOldPen);
}

void CGuiTabPowerPoint::ShowButtonClose(BOOL bShowButton)
{
	m_bShowButton=bShowButton;

};	
void CGuiTabPowerPoint::SetAutoAjust(BOOL bAjust)
{
	bAutoAjust=bAjust;
	if (m_ToolButton.GetSafeHwnd())
		m_ToolButton.ShowWindow(bAutoAjust==FALSE?SW_HIDE:SW_SHOW);
}

void CGuiTabPowerPoint::SetColorTabs(COLORREF clrTabs)
{
	m_clrTabs=clrTabs;
}

int CGuiTabPowerPoint::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiTabWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_img.Create(IDB_GUI_MDIICONS,9,3,RGB(255,0,255)))
	{
		TRACE0("error imagelist");
	}
	SetActualTitle(FALSE);
	SetALingTabs(CGuiTabWnd::ALN_TOP); //los tabs arriba
	SetStyle(CGuiTabWnd::FLAT);
	
	
	// TODO:  Add your specialized creation code here

	return 0;
}

void CGuiTabPowerPoint::SetIdButtonClose(UINT uClose)
{
	m_ToolButton.ShowDark(FALSE);
	
	m_ToolButton.Create(_T(""),WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,CRect(0,0,0,0),this,uClose);
	m_ToolButton.SetToolTip(_T("Close"));
	m_ToolButton.SethIcon(m_img.ExtractIcon(2));
	m_ToolButton.SetColor(GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Theme));
	m_bShowButton=TRUE;
	Invalidate();
	UpdateWindow();
	
}


