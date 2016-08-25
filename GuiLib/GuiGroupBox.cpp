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
#include "GuiGroupBox.h"
#include "GuiDrawLayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiGroupBox

CGuiGroupBox::CGuiGroupBox()
{
	m_clrface=GuiDrawLayer::GetRGBColorFace();
	m_clrShadow=GuiDrawLayer::GetRGBColorShadow();
	m_style=ALING_LEFT;
	m_Caption=_T("");
}

CGuiGroupBox::~CGuiGroupBox()
{
}


BEGIN_MESSAGE_MAP(CGuiGroupBox, CButton)
	//{{AFX_MSG_MAP(CGuiGroupBox)
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiGroupBox message handlers

void CGuiGroupBox::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
	GetWindowText(m_Caption);
	SetWindowText(_T(""));
}

void CGuiGroupBox::SetCaption(CString Caption)
{
	m_Caption=Caption;
	SetWindowText(_T(""));
}

void CGuiGroupBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(rc);
	CBrush cb;
	CFont m_cfont;
	CString m_caption;
	CPen cpshadow(PS_SOLID,1,GuiDrawLayer::GetRGBColorShadow());
	cb.CreateSolidBrush(m_clrface);
	
	if ((m_style == ALING_LEFT) || (m_style == ALING_RIGHT))
		m_cfont.CreateFont( -11,0,0,0,400,0,0,0,0,1,2,1,34,_T("Verdana"));
	else
		m_cfont.CreateFont(-11,0,900,900,400,0,0,0,0,1,2,1,34,_T("Verdana"));	
	
	//********************************************************
	CFont* m_fontOld=dc.SelectObject(&m_cfont);
	CSize SizeCad=dc.GetTextExtent(m_Caption);
	SizeCad.cx+=2;
	CRect rCText=rc;
	rc.DeflateRect(1,1);
	rc.top+=6;
	
	//orientar la cadena*************************************

		
	if (m_style == ALING_LEFT)
	{
		rCText.left+=6;
		rCText.bottom=rCText.top+SizeCad.cy+1;
		rCText.right=rCText.left+SizeCad.cx+1;
	}
	else if (m_style == ALING_RIGHT)
	{
		rCText.right-=6;
		rCText.left=rCText.right-SizeCad.cx+1;
		rCText.bottom=rCText.top+SizeCad.cy+1;
	}
	else if (m_style == ALING_DOWN)
	{
		rCText.bottom-=6;
		rCText.left=-7;
		rCText.top=rCText.bottom-SizeCad.cx;
		rCText.right=rCText.left+SizeCad.cy+1;
	}
	else if (m_style == ALING_UP)
	{
		rCText.top+=10;
		rCText.left=-7;
		rCText.right=rCText.left+SizeCad.cy+1;
		rCText.bottom=rCText.top+SizeCad.cx+7;
		
	}
	//********************************************************
	CPen* pOld=dc.SelectObject(&cpshadow);
	//linea superior
	dc.MoveTo(rc.left+2,rc.top);
	dc.LineTo(rc.right-2,rc.top);
	//linea vertical izquierda
	dc.MoveTo(rc.left,rc.top+2);
	dc.LineTo(rc.left,rc.bottom-2);
	//linea vertical derecha
	dc.MoveTo(rc.right,rc.top+2);
	dc.LineTo(rc.right,rc.bottom-2);
	//linea horizontal inferior
	dc.MoveTo(rc.left+2,rc.bottom);
	dc.LineTo(rc.right-2,rc.bottom);

	//ahora se dibujan los vertices

	//l,t
	dc.MoveTo(rc.left+2,rc.top);
	dc.LineTo(rc.left,rc.top+2);
	//r,t
	dc.MoveTo(rc.right-2,rc.top);
	dc.LineTo(rc.right,rc.top+2);
	//l,b
	dc.MoveTo(rc.left,rc.bottom-2);
	dc.LineTo(rc.left+2,rc.bottom);
	//r,b
	dc.MoveTo(rc.right-2,rc.bottom);
	dc.LineTo(rc.right,rc.bottom-2);
	
	//sentido del mensaje
	
	int nMode = dc.SetBkMode(TRANSPARENT);
	dc.FillRect(rCText,&cb);
	dc.SetTextColor(GuiDrawLayer::GetRGBCaptionXP());
	int cont=SizeCad.cx;
	if (m_style == ALING_DOWN || m_style == ALING_UP)
		dc.TextOut(rCText.left,rCText.bottom-2,m_Caption);
	else
		dc.TextOut(rCText.left,rCText.top,m_Caption);
 	dc.SetBkMode(nMode);
	dc.SelectObject(&m_fontOld);
}

void CGuiGroupBox::SetStyle(Aling style)
{
	m_style=style;
}

void CGuiGroupBox::OnSysColorChange() 
{
	m_clrface=GuiDrawLayer::GetRGBColorFace();
	m_clrShadow=GuiDrawLayer::GetRGBColorShadow();

	CButton::OnSysColorChange();

}
