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
#include "GuiRadioButton.h"
#include "GuiDrawLayer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiRadioButton

IMPLEMENT_DYNAMIC(CGuiRadioButton,CButton);
CGuiRadioButton::CGuiRadioButton()
{
	m_SelectBtn=FALSE;
	m_bOldCheck=FALSE;
	m_bPressBtn=FALSE;
	m_rc=CRect(0,0,0,0);
}

CGuiRadioButton::~CGuiRadioButton()
{
}


BEGIN_MESSAGE_MAP(CGuiRadioButton, CButton)
	//{{AFX_MSG_MAP(CGuiRadioButton)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	//ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	//ON_WM_KILLFOCUS()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiRadioButton message handlers



void CGuiRadioButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect m_rcClient=lpDrawItemStruct->rcItem;
	UINT m_State=lpDrawItemStruct->itemState;
	CBrush cb;
	CRect m_rcTemp=m_rcClient;
	CPoint pt;
	CSize  m_Csize;
	CString m_szCaption;
	COLORREF m_clrCheck=RGB(0,170,170);
	COLORREF m_Over=RGB(255,193,111);
	CPen cpOver(PS_SOLID,1,RGB(255,193,111));
	cb.CreateSolidBrush(GuiDrawLayer::GetRGBColorXP());
	pDC->FillRect(m_rcTemp,&cb);
	int iMode=pDC->SetBkMode(TRANSPARENT);
	int iExtile=GetButtonStyle(); //obtenemos orientación del texto
	CRect m_rcText=m_rcClient;
	GetWindowText(m_szCaption);
	
	
	//-------------------------------------------------------
	//Ajust text
	//-------------------------------------------------------
	if(m_szCaption.GetLength() > 1)
		m_Csize= pDC->GetTextExtent(m_szCaption);
	
	if (m_rcClient.Height() > 13)
	{
		int Dif=m_rcClient.Height()-13;
		Dif/=2;
		m_rcTemp.top=Dif;
		m_rcTemp.bottom=m_rcTemp.top+13;
	}
	if (iExtile & BS_LEFTTEXT)
	{
		m_rcTemp.left=	m_rcTemp.right-13;
		pt=CPoint(m_rcTemp.left,m_rcTemp.top+1);
	}
	else
	{
		m_rcTemp.right=	m_rcTemp.left+13;
		pt=CPoint(m_rcTemp.right+2,m_rcTemp.top+1);
		m_rcText.left=m_rcTemp.right+1;
	}
	
	m_rc=m_rcTemp;
	//-------------------------------------------------------------------
	//Draw Ellipse
	//-------------------------------------------------------------------
	DrawEllipse(pDC,m_rcTemp);

	int x=lpDrawItemStruct->itemState;
	if (lpDrawItemStruct->itemState & ODS_DISABLED)
	   pDC->DrawState(pt, m_Csize, m_szCaption, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
	else 
		pDC->DrawText(m_szCaption,m_rcText,DT_SINGLELINE|DT_LEFT|DT_VCENTER);			   		
	
	if (m_bPressBtn && !m_SelectBtn)
	{
		CheckRadio(pDC,m_rc) ;
	}
	else if(m_SelectBtn && !m_bPressBtn)
	{
		DrawOrange(pDC,m_rc);
	}
	else if(m_SelectBtn && m_bPressBtn)
	{
		DrawOrange(pDC,m_rc);
		CheckRadio(pDC,m_rc) ;
	}
	
}

void CGuiRadioButton::SetCheck(int nCheck)
{
	m_bPressBtn=nCheck;
}


void CGuiRadioButton::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRect m_rect;
	GetClientRect(&m_rect);
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	if (!m_rect.PtInRect(pt))
	{
		m_SelectBtn=FALSE;
		Invalidate();
		KillTimer(1);
	}	
		
	CButton::OnTimer(nIDEvent);
}

void CGuiRadioButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_SelectBtn==TRUE) return;
	CRect m_rect;
	GetClientRect(&m_rect);
	if (m_rect.PtInRect(point))
	{
		m_SelectBtn =TRUE;
		Invalidate();
		UpdateWindow();
		SetTimer(1,100,NULL);
	}
	CButton::OnMouseMove(nFlags, point);
}

void CGuiRadioButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_SelectBtn=TRUE;
	SetTimer(1,100,NULL);
	Invalidate();
	UpdateWindow();
	CButton::OnLButtonDown(nFlags, point);
	
}

void CGuiRadioButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CButton::OnLButtonUp(nFlags, point);
	CRect m_rect;
	GetClientRect(&m_rect);
	if (m_rect.PtInRect(point))
	{
		m_bPressBtn=TRUE;
		m_SelectBtn=FALSE;
		UnCheckRadio();
		Invalidate();
		KillTimer(1);
	}	
}

//*******************************************************************

int CGuiRadioButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

//*******************************************************************
void CGuiRadioButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	
}

//*******************************************************************
void CGuiRadioButton::DrawEllipse(CDC* pDC,CRect m_rc)
{
	//***************************************
	//pDC->SetPixel(CPoint(3,0),RGB(222,228,229));
	pDC->SetPixel(CPoint(4,0),RGB(164,184,198));
	pDC->SetPixel(CPoint(5,0),RGB(90,128,160));
	pDC->SetPixel(CPoint(6,0),RGB(133,158,175));
	pDC->SetPixel(CPoint(7,0),RGB(90,128,160));
	pDC->SetPixel(CPoint(8,0),RGB(164,184,198));
	//pDC->SetPixel(CPoint(9,0),RGB(223,228,229));


	pDC->SetPixel(CPoint(2,1),RGB(180,196,207));
	pDC->SetPixel(CPoint(3,1),RGB(133,158,175));
	pDC->SetPixel(CPoint(4,1),RGB(102,135,163));
	pDC->SetPixel(CPoint(5,1),RGB(171,186,197));
	pDC->SetPixel(CPoint(7,1),RGB(171,186,197));
	pDC->SetPixel(CPoint(8,1),RGB(102,135,163));
	pDC->SetPixel(CPoint(9,1),RGB(133,158,175));
	pDC->SetPixel(CPoint(10,1),RGB(180,196,207));


	pDC->SetPixel(CPoint(1,2),RGB(181,196,207));
	pDC->SetPixel(CPoint(2,2),RGB(87,124,156));
	pDC->SetPixel(CPoint(3,2),RGB(169,185,195));
	pDC->SetPixel(CPoint(9,2),RGB(169,185,195));
    pDC->SetPixel(CPoint(10,2),RGB(87,124,156));
	pDC->SetPixel(CPoint(11,2),RGB(181,196,207));
	
	
	//pDC->SetPixel(CPoint(0,3),RGB(223,228,229));
	pDC->SetPixel(CPoint(1,3),RGB(133,158,175));
	pDC->SetPixel(CPoint(2,3),RGB(169,185,195));
	pDC->SetPixel(CPoint(10,3),RGB(169,185,195));
	pDC->SetPixel(CPoint(11,3),RGB(133,158,175));
	//pDC->SetPixel(CPoint(12,3),RGB(223,228,229));
	
	pDC->SetPixel(CPoint(0,4),RGB(164,183,198));
	pDC->SetPixel(CPoint(1,4),RGB(102,135,163));
	pDC->SetPixel(CPoint(11,4),RGB(102,135,163));
	pDC->SetPixel(CPoint(12,4),RGB(164,183,198));
	
	pDC->SetPixel(CPoint(0,5),RGB(102,135,163));
	pDC->SetPixel(CPoint(1,5),RGB(164,183,198));
	pDC->SetPixel(CPoint(11,5),RGB(164,183,198));
	pDC->SetPixel(CPoint(12,5),RGB(102,135,163));
	
	pDC->SetPixel(CPoint(0,6),RGB(133,158,175));
	pDC->SetPixel(CPoint(12,6),RGB(133,158,175));

	pDC->SetPixel(CPoint(0,7),RGB(102,135,163));
	pDC->SetPixel(CPoint(1,7),RGB(164,183,198));
	pDC->SetPixel(CPoint(11,7),RGB(164,183,198));
	pDC->SetPixel(CPoint(12,7),RGB(102,135,163));
	
	pDC->SetPixel(CPoint(0,8),RGB(164,183,198));
	pDC->SetPixel(CPoint(1,8),RGB(102,135,163));
	pDC->SetPixel(CPoint(11,8),RGB(102,135,163));
	pDC->SetPixel(CPoint(12,8),RGB(164,183,198));
	
	//pDC->SetPixel(CPoint(0,9),RGB(223,228,229));
	pDC->SetPixel(CPoint(1,9),RGB(133,158,175));
	pDC->SetPixel(CPoint(2,9),RGB(169,185,195));
	pDC->SetPixel(CPoint(10,9),RGB(169,185,195));
	pDC->SetPixel(CPoint(11,9),RGB(133,158,175));
	//pDC->SetPixel(CPoint(12,9),RGB(223,228,229));
	
	pDC->SetPixel(CPoint(1,10),RGB(181,196,207));
	pDC->SetPixel(CPoint(2,10),RGB(87,124,156));
	pDC->SetPixel(CPoint(3,10),RGB(169,185,195));
	pDC->SetPixel(CPoint(9,10),RGB(169,185,195));
    pDC->SetPixel(CPoint(10,10),RGB(87,124,156));
	pDC->SetPixel(CPoint(11,10),RGB(181,196,207));
	
	pDC->SetPixel(CPoint(2,11),RGB(180,196,207));
	pDC->SetPixel(CPoint(3,11),RGB(133,158,175));
	pDC->SetPixel(CPoint(4,11),RGB(102,135,163));
	pDC->SetPixel(CPoint(5,11),RGB(171,186,197));
	pDC->SetPixel(CPoint(7,11),RGB(171,186,197));
	pDC->SetPixel(CPoint(8,11),RGB(102,135,163));
	pDC->SetPixel(CPoint(9,11),RGB(133,158,175));
	pDC->SetPixel(CPoint(10,11),RGB(180,196,207));

	//pDC->SetPixel(CPoint(3,12),RGB(222,228,229));
	pDC->SetPixel(CPoint(4,12),RGB(164,184,198));
	pDC->SetPixel(CPoint(5,12),RGB(90,128,160));
	pDC->SetPixel(CPoint(6,12),RGB(133,158,175));
	pDC->SetPixel(CPoint(7,12),RGB(90,128,160));
	pDC->SetPixel(CPoint(8,12),RGB(164,184,198));
	//pDC->SetPixel(CPoint(9,12),RGB(223,228,229));

	
}	
//*******************************************************************
void CGuiRadioButton::CheckRadio(CDC* pDC,CRect m_rc) 
{
	CRect m_rcTemp=m_rc;
	m_rcTemp.DeflateRect(6,6);
	pDC->SetPixel(m_rc.left+6,3,RGB(242,237,215));
	
	pDC->SetPixel(m_rc.left+5,4,RGB(160,209,148));
	pDC->SetPixel(m_rc.left+6,4,RGB(77,191,72));
	pDC->SetPixel(m_rc.left+7,4,RGB(160,209,148));

	pDC->SetPixel(m_rc.left+4,5,RGB(172,222,160));
	pDC->SetPixel(m_rc.left+5,5,RGB(85,213,81));
	pDC->SetPixel(m_rc.left+6,5,RGB(67,195,63));
	pDC->SetPixel(m_rc.left+7,5,RGB(41,168,38));
	pDC->SetPixel(m_rc.left+8,5,RGB(172,222,160));

	pDC->SetPixel(m_rc.left+4,6,RGB(77,191,72));
	pDC->SetPixel(m_rc.left+5,6,RGB(66,195,63));
	pDC->SetPixel(m_rc.left+6,6,RGB(56,185,53));
	pDC->SetPixel(m_rc.left+7,6,RGB(33,161,33));
	pDC->SetPixel(m_rc.left+8,6,RGB(37,149,32));

	pDC->SetPixel(m_rc.left+4,7,RGB(172,222,160));
	pDC->SetPixel(m_rc.left+5,7,RGB(67,195,63));
	pDC->SetPixel(m_rc.left+6,7,RGB(34,162,32));
	pDC->SetPixel(m_rc.left+7,7,RGB(34,162,32));
	pDC->SetPixel(m_rc.left+8,7,RGB(172,222,160));

	pDC->SetPixel(m_rc.left+5,8,RGB(160,209,148));
	pDC->SetPixel(m_rc.left+6,8,RGB(35,149,33));
	pDC->SetPixel(m_rc.left+7,8,RGB(160,209,148));

	
}

void CGuiRadioButton::DrawOrange(CDC* pDC,CRect m_rc)
{
	
	pDC->SetPixel(CPoint(6,1),RGB(244,212,140));
	
	pDC->SetPixel(CPoint(3,2),RGB(181,196,207));
	pDC->SetPixel(CPoint(4,2),RGB(181,196,207));
	pDC->SetPixel(CPoint(5,2),RGB(253,214,132));
	pDC->SetPixel(CPoint(6,2),RGB(253,214,132));
	pDC->SetPixel(CPoint(7,2),RGB(253,214,132));
    pDC->SetPixel(CPoint(8,2),RGB(253,214,132));
	//pDC->SetPixel(CPoint(9,2),RGB(253,214,132));
	
	
	pDC->SetPixel(CPoint(3,3),RGB(252,220,152));
	pDC->SetPixel(CPoint(4,3),RGB(252,220,152));
	pDC->SetPixel(CPoint(5,3),RGB(247,227,179));
	pDC->SetPixel(CPoint(6,3),RGB(242,237,215));
	pDC->SetPixel(CPoint(7,3),RGB(247,227,179));
	pDC->SetPixel(CPoint(8,3),RGB(251,200,99));
	pDC->SetPixel(CPoint(9,3),RGB(251,200,99));
	
	pDC->SetPixel(CPoint(2,4),RGB(254,223,156));
	pDC->SetPixel(CPoint(3,4),RGB(254,220,152));
	pDC->SetPixel(CPoint(4,4),RGB(233,236,210));
	pDC->SetPixel(CPoint(8,4),RGB(233,236,210));
	pDC->SetPixel(CPoint(9,4),RGB(251,200,99));
	pDC->SetPixel(CPoint(10,4),RGB(251,200,99));
	
	
	pDC->SetPixel(CPoint(2,5),RGB(253,217,140));
	pDC->SetPixel(CPoint(3,5),RGB(247,227,179));
	pDC->SetPixel(CPoint(9,5),RGB(247,227,179));
	pDC->SetPixel(CPoint(10,5),RGB(251,200,99));
	

	pDC->SetPixel(CPoint(1,6),RGB(254,223,156));
	pDC->SetPixel(CPoint(2,6),RGB(254,220,152));
	pDC->SetPixel(CPoint(3,6),RGB(233,236,210));
	pDC->SetPixel(CPoint(9,6),RGB(233,236,210));
	pDC->SetPixel(CPoint(10,6),RGB(251,200,99));
	pDC->SetPixel(CPoint(11,6),RGB(251,200,99));

	
	pDC->SetPixel(CPoint(2,7),RGB(252,211,124));
	pDC->SetPixel(CPoint(3,7),RGB(246,224,172));
	pDC->SetPixel(CPoint(9,7),RGB(251,200,99));
	pDC->SetPixel(CPoint(10,7),RGB(251,200,99));
	
	pDC->SetPixel(CPoint(2,8),RGB(254,223,156));
	pDC->SetPixel(CPoint(3,8),RGB(254,220,152));
	pDC->SetPixel(CPoint(4,8),RGB(233,236,210));
	pDC->SetPixel(CPoint(8,8),RGB(233,236,210));
	pDC->SetPixel(CPoint(9,8),RGB(251,200,99));
	pDC->SetPixel(CPoint(10,8),RGB(251,200,99));

	pDC->SetPixel(CPoint(3,9),RGB(253,217,140));
	pDC->SetPixel(CPoint(4,9),RGB(253,217,140));
	pDC->SetPixel(CPoint(5,9),RGB(247,227,179));
	pDC->SetPixel(CPoint(7,9),RGB(247,227,179));
	pDC->SetPixel(CPoint(8,9),RGB(251,200,99));
	pDC->SetPixel(CPoint(9,9),RGB(251,200,99));
	
	pDC->SetPixel(CPoint(4,10),RGB(251,200,99));
	pDC->SetPixel(CPoint(5,10),RGB(251,200,99));
	pDC->SetPixel(CPoint(6,10),RGB(251,200,99));
	pDC->SetPixel(CPoint(7,10),RGB(251,200,99));
	pDC->SetPixel(CPoint(8,10),RGB(251,200,99));

	pDC->SetPixel(CPoint(6,11),RGB(251,200,99));
	

}

//*******************************************************************
void CGuiRadioButton::UnCheckRadio()
{
	CWnd *pParent = GetParent();
	ASSERT(pParent);

	
	CWnd *pWnd = pParent->GetNextDlgGroupItem((CWnd *)this);
	while (pWnd && (pWnd != this))
	{
		
		
		if ((((CButton*)pWnd)->GetButtonStyle() & BS_AUTORADIOBUTTON) && 
			pWnd->IsKindOf( RUNTIME_CLASS( CGuiRadioButton ) ))
		{
			((CGuiRadioButton *)pWnd)->SetCheck(0);
			pWnd->Invalidate();
		}
		pWnd = pParent->GetNextDlgGroupItem(pWnd);
	}
	
	
}	

//*******************************************************************
BOOL CGuiRadioButton::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CButton::PreTranslateMessage(pMsg);
}
//*******************************************************************
void CGuiRadioButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CButton::PreSubclassWindow();
	ModifyStyle(0,BS_OWNERDRAW);


}


BOOL CGuiRadioButton::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
}
