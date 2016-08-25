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
#include "resource.h"
#include "guitabbed.h"
#include "GuiBaseTab.h"
#include "Guitabbed.h"

#define SCROLLCLOSE 0x886
#define SCROLLLEFT  0x887
#define SCROLLRIGHT 0x888
#define IDD_COMBOBOX 0x889


CGuiTabbed::CGuiTabbed(void)
{
	m_nDif=0;
	GuiDrawLayer::m_Style=GUISTYLE_XP;
}

CGuiTabbed::~CGuiTabbed(void)
{
}

void CGuiTabbed::SetExtileExt(ExtTab m_ext)
{
	m_ExtTab=m_ext;
	if (m_ExtTab == COMBO_TAB)
	{
		m_comboxBox.ShowWindow(SW_SHOW);	
		m_toolBtn[0].ShowWindow(SW_HIDE);
		m_toolBtn[1].ShowWindow(SW_HIDE);
		m_toolBtnC.ShowWindow(SW_HIDE);
		m_comboxBox.ResetContent();
		for (int iCont=0; iCont< m_Numtabs;iCont++)
		{
			CGuiTab* ct=(CGuiTab*) m_pArray[iCont];
			CRect m_Arect;
			m_comboxBox.AddString(ct->lpMsg);
		}		
		m_comboxBox.SetCurSel(0);
	}
	else
	{
		m_comboxBox.ShowWindow(SW_HIDE);			
		m_toolBtn[0].ShowWindow(SW_SHOW);
		m_toolBtn[1].ShowWindow(SW_SHOW);
		m_toolBtnC.ShowWindow(SW_SHOW);
	}
	
}

void CGuiTabbed::Drawtabs(CDC* dc)
{
	
	if (m_ExtTab == COMBO_TAB)
	{
		m_comboxBox.MoveWindow(m_rectTab);
		return;
	}
	
	
	
	int m_StrPos=0;
	BOOL m_ViewAlltab=TRUE;
	CRect m_rClient;
	CBrush cbr;
	CPen light(PS_SOLID,1,GetSysColor(COLOR_BTNHIGHLIGHT));
	CPen Dark(PS_SOLID,1,GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	CPen Black(PS_SOLID,1,GetSysColor(BLACK_PEN));	
	CPen pPress(PS_SOLID,1,::GetSysColor(COLOR_HIGHLIGHT));	
	CRect rectText;
	CFont* m_fontOld=dc->SelectObject(&m_cfontBold);
	CRect m_rcTabMain;	
	CSize mszBtn=GetSizeButton();
	int m_iSizeButton=mszBtn.cx;
	if(GuiDrawLayer::m_Style== GUISTYLE_2003)
	{
		CGradient M(CSize(m_rectTab.Width(),m_rectTab.Height()+1));	
		M.PrepareReverseVertTab(dc,GUISTYLE_2003);
		M.Draw(dc,0,0,0,0,m_rectTab.Width(),m_rectTab.Height(),SRCCOPY);	
		m_toolBtn[0].StyleDispl(GuiDrawLayer::m_Style,FALSE);
		m_toolBtn[1].StyleDispl(GuiDrawLayer::m_Style,FALSE);
		m_toolBtnC.StyleDispl(GuiDrawLayer::m_Style,FALSE);
	
	}	
	m_rectTab.DeflateRect(1,1);
	m_rectTab.bottom+=1;
	
	if(GuiDrawLayer::m_Style== GUISTYLE_XP)
	{
		m_toolBtn[0].SetColor(GuiDrawLayer::GetRGBColorTabs());
		m_toolBtn[1].SetColor(GuiDrawLayer::GetRGBColorTabs());
		m_toolBtnC.SetColor(GuiDrawLayer::GetRGBColorTabs());
		cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorTabs());
		dc->FillRect(m_rectTab,&cbr);
		m_toolBtn[0].StyleDispl(GuiDrawLayer::m_Style);
		m_toolBtn[1].StyleDispl(GuiDrawLayer::m_Style);
		m_toolBtnC.StyleDispl(GuiDrawLayer::m_Style);

	}



	m_rectTab.InflateRect(1,1);

	CRect rectT=m_rectTab;
	rectT.right-=m_iSizeButton+2;
	int mSizeTotal=m_iMinValRec;
	m_toolBtn[0].EnableWindow(FALSE);
	m_toolBtn[1].EnableWindow(FALSE);
	if (mSizeTotal > m_rectTab.Width())
	{
		
		m_toolBtn[1].EnableWindow(TRUE);
		if (m_nDif < 0) 
			m_toolBtn[0].EnableWindow(TRUE);
		if((mSizeTotal-(abs(m_nDif)-20)) < m_rectTab.Width())
			m_toolBtn[1].EnableWindow(FALSE);
	}
	else
		m_nDif=0;
	
	CRect rectScroll; 
	CRgn reg;	
	CRect rectRecorte;
	rectRecorte=rectT;
	reg.CreateRectRgnIndirect(rectRecorte);
	dc->SelectClipRgn(&reg);
	int m_right=m_nDif;
	for ( int iCont=0; iCont< m_Numtabs;iCont++)
	{	

		CGuiTab* ctb=(CGuiTab*)m_pArray[iCont];
		CRect mrt=ctb->rect;		
		int ancho=mrt.Width();
		mrt.left=m_right;
		mrt.right=mrt.left+ancho;
		CPoint Coor[6];
		//si es la carpeta seleccionada, se debe 
		//eliminar las lineas oscuras de encima
		if (iCont ==m_iSelectTab)
		{
			
			if(GuiDrawLayer::m_Style== GUISTYLE_XP)
			{
				CBrush cbr;
				CRect  m_rectTabAux=mrt;
				cbr.CreateSysColorBrush(COLOR_BTNFACE);
				m_rectTabAux.top+=3;
				m_rectTabAux.bottom+=2;
				dc->FillRect(m_rectTabAux,&cbr);
				CPen* pOldPen=dc->SelectObject(&light);
				dc->MoveTo(m_rectTabAux.left,m_rectTabAux.top);
				dc->LineTo(m_rectTabAux.left,m_rectTabAux.bottom);
				//linea de arriba
				dc->MoveTo(m_rectTabAux.left,m_rectTabAux.top);
				dc->LineTo(m_rectTabAux.right,m_rectTabAux.top);
				//linea derecha observe que se pinta dos veces para
				//dar el efecto de redondeada en la puntas
				dc->SelectObject(pOldPen);
				pOldPen=dc->SelectObject(&Black);
				dc->MoveTo(m_rectTabAux.right-1,m_rectTabAux.top+1);
				dc->LineTo(m_rectTabAux.right-1,m_rectTabAux.bottom);
				dc->SelectObject(pOldPen);
			}

			if(GuiDrawLayer::m_Style== GUISTYLE_2003)
			{

					CRect  m_rectTabAux=mrt;
					m_rcTabMain=m_rectTabAux;
					CGradient M(CSize(m_rectTabAux.Width(),m_rectTabAux.Height()));	
					M.PrepareTabs(dc,ctb->m_clrLTab,ctb->m_clrHtab);
					M.Draw(dc,m_rectTabAux.left-14,m_rectTabAux.bottom+2,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-13,m_rectTabAux.bottom+1,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-12,m_rectTabAux.bottom,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-11,m_rectTabAux.bottom-1,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-10,m_rectTabAux.bottom-2,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-9,m_rectTabAux.bottom-3,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-8,m_rectTabAux.bottom-4,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-7,m_rectTabAux.bottom-5,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-6,m_rectTabAux.bottom-6,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-5,m_rectTabAux.bottom-7,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-4,m_rectTabAux.bottom-8,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-3,m_rectTabAux.bottom-9,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left-2,m_rectTabAux.bottom-10,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left+1,m_rectTabAux.top+6,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left+2,m_rectTabAux.top+5,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left+3,m_rectTabAux.top+4,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					M.Draw(dc,m_rectTabAux.left+4,m_rectTabAux.top+3,0,0,m_rectTabAux.Width(),m_rectTabAux.Height(),SRCCOPY);
					CPen* pOldPen=dc->SelectObject(&Dark);
					if ( iCont== 0)
						dc->MoveTo(m_rectTabAux.left+1, m_rectTabAux.bottom+3);
					else
					{
						dc->MoveTo(m_rectTabAux.left-15, m_rectTabAux.bottom+1);
						dc->LineTo(m_rectTabAux.left-13, m_rectTabAux.bottom+1);
						dc->MoveTo(m_rectTabAux.left-16, m_rectTabAux.bottom+2);
						dc->LineTo(m_rectTab.left, m_rectTabAux.bottom+2);
						dc->MoveTo(m_rectTabAux.left-13, m_rectTabAux.bottom+1);
					}
					dc->LineTo(m_rectTabAux.left+1, m_rectTabAux.top+6);
					dc->MoveTo(m_rectTabAux.left+1, m_rectTabAux.top+6);
					dc->LineTo(m_rectTabAux.left+6, m_rectTabAux.top+2);
					

					dc->MoveTo(m_rectTabAux.left+6, m_rectTabAux.top+2);
					dc->LineTo(m_rectTabAux.right+1, m_rectTabAux.top+2);
					dc->MoveTo(m_rectTabAux.right+1, m_rectTabAux.top+2);
					dc->LineTo(m_rectTabAux.right+4, m_rectTabAux.top+5);

					dc->MoveTo(m_rectTabAux.right+4, m_rectTabAux.top+5);
					dc->LineTo(m_rectTabAux.right+4, m_rectTabAux.bottom+3);

					//linea desde el punto inferior derecho del tab hasta el final del area de tabs
					dc->MoveTo(m_rectTabAux.right+4, m_rectTabAux.bottom+2);
					dc->LineTo(m_rectTab.right, m_rectTabAux.bottom+2);
					
					dc->SelectObject(pOldPen);

			}
			//pDC->TextOut(rCText.left+3,rCText.top,m_caption);

		}
		else
		{
			if(GuiDrawLayer::m_Style== GUISTYLE_XP)
			{
				if ((iCont+1) != m_iSelectTab)
				{
					CPen* pOldPen=dc->SelectObject(&Dark);
					dc->MoveTo(mrt.right-1,mrt.top+3);
					dc->LineTo(mrt.right-1,mrt.bottom+1);
					dc->SelectObject(pOldPen);
				}
			}
			
			if(GuiDrawLayer::m_Style== GUISTYLE_2003)
				{
					CRect  m_rectTabAux=mrt;
					CGradient M(CSize(m_rectTabAux.Width(),m_rectTabAux.Height()));	
					M.PrepareTabs(dc,ctb->m_clrLTab,ctb->m_clrHtab);
					if (iCont == 0)
					{
						M.Draw(dc,m_rectTabAux.left+1,m_rectTabAux.top+6,0,0,m_rectTabAux.Width(),m_rectTabAux.Height()-4,SRCCOPY);
						M.Draw(dc,m_rectTabAux.left+2,m_rectTabAux.top+5,0,0,m_rectTabAux.Width(),m_rectTabAux.Height()-4,SRCCOPY);
						M.Draw(dc,m_rectTabAux.left+3,m_rectTabAux.top+4,0,0,m_rectTabAux.Width(),m_rectTabAux.Height()-2,SRCCOPY);
						M.Draw(dc,m_rectTabAux.left+4,m_rectTabAux.top+3,0,0,m_rectTabAux.Width(),m_rectTabAux.Height()-1,SRCCOPY);
					}
					else
					{
						M.Draw(dc,m_rectTabAux.left+6,m_rectTabAux.top+6,0,0,m_rectTabAux.Width(),m_rectTabAux.Height()-4,SRCCOPY);
						M.Draw(dc,m_rectTabAux.left+6,m_rectTabAux.top+5,0,0,m_rectTabAux.Width(),m_rectTabAux.Height()-4,SRCCOPY);
						M.Draw(dc,m_rectTabAux.left+6,m_rectTabAux.top+4,0,0,m_rectTabAux.Width(),m_rectTabAux.Height()-4,SRCCOPY);
						M.Draw(dc,m_rectTabAux.left+6,m_rectTabAux.top+3,0,0,m_rectTabAux.Width(),m_rectTabAux.Height()-4,SRCCOPY);
					}

					CPen* pOldPen=dc->SelectObject(&Dark);
					if (iCont == 0)
					{
						dc->MoveTo(m_rectTabAux.left+1, m_rectTabAux.bottom+3);
						dc->LineTo(m_rectTabAux.left+1, m_rectTabAux.top+6);
						dc->MoveTo(m_rectTabAux.left+1, m_rectTabAux.top+6);
						dc->LineTo(m_rectTabAux.left+6, m_rectTabAux.top+2);
					}
					else
					{
						dc->MoveTo(m_rectTabAux.left+3, m_rectTabAux.top+4);
						dc->LineTo(m_rectTabAux.left+6, m_rectTabAux.top+2);
					}
					

					dc->MoveTo(m_rectTabAux.left+6, m_rectTabAux.top+2);
					dc->LineTo(m_rectTabAux.right+1, m_rectTabAux.top+2);
					dc->MoveTo(m_rectTabAux.right+1, m_rectTabAux.top+2);
					dc->LineTo(m_rectTabAux.right+4, m_rectTabAux.top+5);

					dc->MoveTo(m_rectTabAux.right+4, m_rectTabAux.top+5);
					dc->LineTo(m_rectTabAux.right+4, m_rectTabAux.bottom+3);
					dc->SelectObject(pOldPen);

					
				}
							
			
		}
		
		
		
		CRect m_rectTabAux= mrt;
		m_rectTabAux.top+=4;
		m_rectTabAux.left+=4;
		int OldMode=dc->SetBkMode(TRANSPARENT);

		COLORREF clrtext;
		
		if (iCont !=m_iSelectTab)
		{
			clrtext=dc->SetTextColor(RGB(0,0,0));
			dc->SelectObject(&m_cfont);
		}
		dc->DrawText(ctb->lpMsg,m_rectTabAux,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		
		if (iCont !=m_iSelectTab)
		{
			dc->SetTextColor(clrtext);
			dc->SelectObject(&m_cfontBold);
		}	
		m_right=mrt.right;
		ctb->rect=mrt;
		dc->SetBkMode(OldMode);
	}


	dc->SelectClipRgn(NULL);

	CPen* pOldPen=dc->SelectObject(&pPress);
	dc->MoveTo(m_rectTab.right-(m_iSizeButton+2), m_rcTabMain.bottom+2);
	dc->LineTo(m_rectTab.right, m_rcTabMain.bottom+2);
	dc->SelectObject(pOldPen);

	CRect rcCli;
	GetClientRect(rcCli);
    rcCli.top=m_rectTab.top;
	rcCli.bottom=m_rectTab.bottom;
	rcCli.left=rcCli.right-(m_iSizeButton);
	int nacum=0;
	for (int i=0; i<3;i++)
	{
		CSize szBtn=m_toolBtn[i].GetSizeButton();
		m_toolBtn[i].MoveWindow(rcCli.left+nacum-1,rcCli.top+4,szBtn.cx,rcCli.Height()-6);
		nacum+=szBtn.cx;
	}
	GetClientRect(rcCli);
	dc->Draw3dRect(rcCli,GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());
	m_toolBtnC.EnableWindow(TRUE);
	cbr.DeleteObject();
	dc->SelectObject(m_fontOld);
	m_toolBtnC.Invalidate();
    m_toolBtnC.UpdateWindow();
	m_toolBtn[0].Invalidate();
    m_toolBtn[0].UpdateWindow();
	m_toolBtn[1].Invalidate();
    m_toolBtn[1].UpdateWindow();
}


BEGIN_MESSAGE_MAP(CGuiTabbed, CGuiTabWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_COMMAND(SCROLLLEFT,OnScrollLeft)
	ON_COMMAND(SCROLLRIGHT,OnScrollRight)
	ON_COMMAND(SCROLLCLOSE,OnScrollClose)
	ON_CBN_SELCHANGE(IDD_COMBOBOX, OnSelchangeCombo1)
END_MESSAGE_MAP()

void CGuiTabbed::OnSelchangeCombo1()
{
	SetCurtab(m_comboxBox.GetCurSel());
	SendMessage(WM_LBUTTONDOWN);
}


void  CGuiTabbed::OnScrollLeft()
{
	m_nDif+=10;
	CClientDC dc(this);
	Drawtabs(&dc);	
	//RecalLayout();
	
}

void  CGuiTabbed::OnScrollRight()
{
	m_nDif-=10;
	CClientDC dc(this);
	Drawtabs(&dc);	
	//RecalLayout();
}

void  CGuiTabbed::OnScrollClose()
{
	//no es nuestro problema lo debe manejar la clase derivada
}


int CGuiTabbed::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGuiTabWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_img.Create(IDB_GUI_DOCKBAR,9,11,RGB(255,0,255)))
	{
		TRACE0("error imagelist");
	}

	if (!m_comboxBox.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWN | 
                    WS_VSCROLL | WS_TABSTOP| CBS_AUTOHSCROLL,CRect(1,1,100,100),this,IDD_COMBOBOX))
	m_ExtTab=NORMAL_TAB;
	m_comboxBox.ShowWindow(SW_HIDE);	
	m_toolBtn[0].Create(_T(""),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0),this,SCROLLLEFT);
//	m_toolBtn[0].SetStyleButton(CGuiNormalButton::STL_FLAT);
	m_toolBtn[0].SetToolTip("Scroll Left");
	m_toolBtn[0].SethIcon(m_img.ExtractIcon(4));
	m_toolBtn[0].SetColor(GuiDrawLayer::GetRGBColorTabs());
	m_toolBtn[0].ShowDark(FALSE);
	m_toolBtn[1].Create(_T(""),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0),this,SCROLLRIGHT);
//	m_toolBtn[1].SetStyleButton(CGuiNormalButton::STL_FLAT);
	m_toolBtn[1].SetToolTip("Scroll Right");
	m_toolBtn[1].SethIcon(m_img.ExtractIcon(2));
	m_toolBtn[1].SetColor(GuiDrawLayer::GetRGBColorTabs());
	m_toolBtn[1].ShowDark(FALSE);
	m_toolBtnC.Create(_T(""),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0),this,SCROLLCLOSE);
//	m_toolBtnC.SetStyleButton(CGuiNormalButton::STL_FLAT);
	m_toolBtnC.SetToolTip("Close");
	m_toolBtnC.SethIcon(m_img.ExtractIcon(10));
//	m_toolBtnC.SetColor(GuiDrawLayer::GetRGBColorTabs());
	m_toolBtnC.ShowDark(FALSE);
	m_toolBtn[0].EnableWindow(FALSE);
	m_toolBtn[1].EnableWindow(FALSE);
	SetALingTabs(CGuiTabWnd::ALN_TOP); //los tabs arriba
	SetStyle(CGuiTabWnd::SHADOW);	   //no debe acondicionar el tamaño de los tabs		return 0;
	SetTypeTab(CGuiTabWnd::TYPE_MDI);
	SetActualTitle(FALSE);
	return 0;
}

CSize CGuiTabbed::GetSizeButton()
{
	CSize szresult=CSize(0,0);
	for (int i=0; i < 3; i++)
	{
		CSize sztemp=m_toolBtn[i].GetSizeButton();
		szresult.cx+=sztemp.cx;
		szresult.cy+=sztemp.cy;
	}
	return szresult;
}

void CGuiTabbed::OnSysColorChange() 
{
	CGuiTabWnd::OnSysColorChange();
/*	m_toolBtn[0].SetColor(GuiDrawLayer::GetRGBColorTabs());	
	m_toolBtn[1].SetColor(GuiDrawLayer::GetRGBColorTabs());
	m_toolBtn[2].SetColor(GuiDrawLayer::GetRGBColorTabs());	
*/	m_toolBtn[0].Invalidate();
    m_toolBtn[0].UpdateWindow();	
	m_toolBtn[1].Invalidate();
    m_toolBtn[1].UpdateWindow();
	m_toolBtn[2].Invalidate();
    m_toolBtn[2].UpdateWindow();
	Invalidate ();
	UpdateWindow ();
}

/*BOOL CGuiTabbed::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd* pParent= GetParent();
	
	if (pParent->GetSafeHwnd())
		pParent->SendMessage(WM_NOTIFY, wParam, lParam);
	
	return TRUE;
}*/