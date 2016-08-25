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
 * -CodeJunkie																*	
 ****************************************************************************/



#include "stdafx.h"
#include "GuiContainer.h"
#include "GuiVisioFolder.h"
#include "Guicontainer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiContainer

CGuiContainer::CGuiContainer()
{
	m_arrContainer.RemoveAll();
	m_nItems=0;
	m_nItems = -1;
	m_bUseWin=FALSE;
	m_bDrawBorder=TRUE;
	m_StyleDisplay=GUISTYLE_XP;
	m_clrface=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
}

CGuiContainer::~CGuiContainer()
{
	m_arrContainer.RemoveAll();
}


BEGIN_MESSAGE_MAP(CGuiContainer, CWnd)
	//{{AFX_MSG_MAP(CGuiContainer)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiContainer message handlers

int CGuiContainer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

//THANKS to CodeJunkie

BOOL CGuiContainer::OnCommand(WPARAM wParam, LPARAM lParam)
{
	CWnd* pParent= GetParent();
	while (pParent)
	{
		pParent->PostMessage (WM_COMMAND,wParam, lParam);
		pParent= pParent->GetParent();
	}
	return TRUE;
} 


//********************************************************************************
void CGuiContainer::OnPaint()  
{
	CPaintDC dc(this); // device context for painting
	CBrush cbr;
	CRect m_rectDraw;
	GetClientRect(&m_rectDraw);
	m_clrface=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	cbr.CreateSolidBrush(m_clrface);
	dc.FillRect(&m_rectDraw,&cbr);
	if (m_enBorder == STYLE3D)
		dc.Draw3dRect(m_rectDraw,GuiDrawLayer::GetRGBColorBTNHigh(),
			GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	if (m_enBorder == STYLEPRESS)
	{
		dc.Draw3dRect(m_rectDraw,GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style),
			GuiDrawLayer::GetRGBColorBTNHigh());
	}
	RecalLayout();
	cbr.DeleteObject();

}


BOOL CGuiContainer::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID) 
{
	// TODO: Add your specialized code here and/or call the base class
	pParent= pParentWnd;
	return CWnd::Create(NULL, _T(""), dwStyle|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, rect, pParentWnd, nID);
}

//********************************************************************************

void CGuiContainer::OnSysColorChange() 
{
	CWnd::OnSysColorChange();
	m_clrface=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	for (int i=0; i < m_nItems;i++)
	{
		
		CComponents* m_cwnd=(CComponents*) m_arrContainer[i];
		if(m_cwnd->bMiniTool==TRUE)
			m_cwnd->m_guiMini->SetColor(m_clrface);
	}
	RecalLayout();
}

//********************************************************************************
void CGuiContainer::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	RecalLayout();
}

//********************************************************************************
BOOL CGuiContainer::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}
void CGuiContainer::UsedAllWindow(BOOL bUseWindow)
{
	m_bUseWin=bUseWindow;
}
//********************************************************************************
/*void CGuiContainer::PreSubclassWindow() 
{
	CWnd::PreSubclassWindow();
	RecalLayout();
}
*/
//********************************************************************************
void  CGuiContainer::RecalLayout()
{
	if (!GetSafeHwnd()) return;
	CRect rcClient;
	CClientDC dc(this);
	GetClientRect(rcClient);
	rcClient.DeflateRect(1,1);
	CRect rctemp=rcClient;
	int nTipo=0;
	CalcAutoSize(rcClient);
	for (int i=0; i < m_nItems;i++)
	{
		
		CComponents* m_cwnd=(CComponents*) m_arrContainer[i];
		
		if(m_cwnd->bMiniTool==TRUE || m_cwnd->bTypeSmall == TRUE)
			nTipo=24;
		else
			nTipo=m_nResultCWnd;
		
		rctemp.bottom=rctemp.top+nTipo;
		
		if (m_cwnd->bMiniTool==TRUE)
			m_cwnd->m_guiMini->MoveWindow(rctemp);
		else if (nTipo != 0)
		{
			if (m_bDrawBorder)
				dc.Draw3dRect(rctemp,GuiDrawLayer::GetRGBColorShadow(),
				GuiDrawLayer::GetRGBColorShadow());
				
				if (m_bUseWin==FALSE)
					rctemp.DeflateRect(2,2);
				
				m_cwnd->m_cwnd->MoveWindow(rctemp);
				
				if (m_bUseWin==FALSE)
					rctemp.InflateRect(2,2);
		}
		rctemp.top+=nTipo;

	}
}

//********************************************************************************
void CGuiContainer::CalcAutoSize(CRect m_rc)
{

	if (m_nItems == -1) return;
	m_nResultCWnd=0;
    m_nResultTools=0; 	
	int m_numCWnd=0;
	BOOL m_bExisteCWnd=FALSE;
	for (int i=0; i < m_nItems;i++)
	{
		if (((CComponents*) m_arrContainer [i])->bMiniTool==TRUE ||
			((CComponents*) m_arrContainer [i])->bTypeSmall ==TRUE)
			m_nResultTools+=24;
		else
		{
				m_bExisteCWnd=TRUE;	
				m_numCWnd++;
		}
	}

	
	if (m_bExisteCWnd)
	{
		if (m_nResultTools > m_rc.Height())  //el espacio no alcanza para los botones
			m_nResultCWnd=0;
		else
		{
			m_nResultCWnd=m_rc.Height()-m_nResultTools;
			m_nResultCWnd/=m_numCWnd;
		}
	}

}
//********************************************************************************
BOOL CGuiContainer::AddComponen(CGuiMiniTool* m_miniTool)
{
	
	if (!m_miniTool->Create(_T(""),WS_VISIBLE | WS_CHILD |SS_OWNERDRAW, 
						CRect(0,0,0,0), this))
		return FALSE;
	if (m_nItems==-1) m_nItems=0;
	m_arrContainer.SetAtGrow(m_nItems, new CComponents(m_miniTool));
	m_nItems++;
	RecalLayout();
	return TRUE;

}
//********************************************************************************
void CGuiContainer::SetBorder(Borders m_enborder)
{
	m_enBorder=m_enborder;
}


//********************************************************************************
void  CGuiContainer::AddComponen(CWnd* m_pParent)
{
	BOOL btype=FALSE; //only object small
	ASSERT_VALID(pParent);
	if (m_pParent->IsKindOf(RUNTIME_CLASS(CComboBox)))
		btype=TRUE;
	if (m_pParent->IsKindOf(RUNTIME_CLASS(CEdit)))
		btype=TRUE;
	if (m_pParent->IsKindOf(RUNTIME_CLASS(CGuiImageLinkButton)))
		btype=TRUE;
	if (m_pParent->IsKindOf(RUNTIME_CLASS(CGuiLabelButton)))
		btype=TRUE;
	else if (m_pParent->IsKindOf(RUNTIME_CLASS(CGuiToolButton)))
		btype=TRUE;

	if (m_nItems==-1) m_nItems=0;
	m_arrContainer.SetAtGrow(m_nItems, new CComponents(m_pParent,btype));
	m_nItems++;
	RecalLayout();


}
//********************************************************************************
CWnd*  CGuiContainer::AddComponen(CRuntimeClass* m_rtcwnd,UINT nID,DWORD dwStyle)
{
	
	CWnd* m_cwnd=NULL;
	BOOL btype=FALSE; //only object small
	if (m_rtcwnd->IsDerivedFrom(RUNTIME_CLASS(CComboBox)))
	{
		 m_cwnd = new CGuiComboBoxExt();
		 if (!((CGuiComboBoxExt*)m_cwnd)->Create(dwStyle|WS_CHILD|WS_VISIBLE, CRect(1,1,100,100), this, nID))
		 {
			m_cwnd=NULL;
			return NULL;
		 }
		 btype=TRUE;
		 goto crear;
	}

	else if ( m_rtcwnd->IsDerivedFrom(RUNTIME_CLASS(CListBox)))
	{
		 m_cwnd = new CListBox();
		 if (!((CListBox*)m_cwnd)->Create(dwStyle|WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, nID))
		 {
			m_cwnd=NULL;
			return NULL;
		 }
		 goto crear;
	}
	else if ( m_rtcwnd->IsDerivedFrom(RUNTIME_CLASS(CEdit)))
	{
		 m_cwnd = new CEdit();
		 if (!((CEdit*)m_cwnd)->Create(dwStyle|WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, nID))
		 { 
			m_cwnd=NULL;
			return NULL;
		 }
		 
		 btype=TRUE;
		 goto crear;
	}
	
	else if ( m_rtcwnd->IsDerivedFrom(RUNTIME_CLASS(CListCtrl)))
	{
		 m_cwnd = new CListCtrl();
		 if (!((CListCtrl*)m_cwnd)->Create(dwStyle|WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, nID))
		 {
			m_cwnd=NULL;
			return NULL;
		 }
		 
		 btype=FALSE;
		 goto crear;
	}
	else if ( m_rtcwnd->IsDerivedFrom(RUNTIME_CLASS(CGuiVisioFolder)))
	{
		 m_cwnd = new CGuiVisioFolder();
		 if (!((CGuiVisioFolder*)m_cwnd)->Create(dwStyle|WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, nID))
		 {
			m_cwnd=NULL;
			return NULL;
		 }
		 goto crear;
	}
	else
		return NULL;
	
crear:
	if (m_nItems==-1) m_nItems=0;
	m_arrContainer.SetAtGrow(m_nItems, new CComponents(m_cwnd,btype));
	m_nItems++;
	RecalLayout();
	return m_cwnd;

}

//*************************************************************************
CComponents::CComponents(CGuiMiniTool* m_GuiMini)
{
	m_guiMini=m_GuiMini;
	bMiniTool=TRUE;
}

//*************************************************************************
CComponents::CComponents(CWnd* m_wnd,BOOL bType)
{
	ASSERT(::IsWindow(m_wnd->m_hWnd));
	m_cwnd=m_wnd;
	bMiniTool=FALSE;
	bTypeSmall=bType;
}


BOOL CGuiContainer::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd* pParent= GetParent();
	
	if (pParent->GetSafeHwnd())
		pParent->SendMessage(WM_NOTIFY, wParam, lParam);
	
	return TRUE;
}

//thanks to  Ernesto Garcia	
void CGuiContainer::OnDestroy()
{
	for( int i=0; i<m_nItems; i++ )
    {
    CComponents *pArr = (CComponents*)m_arrContainer.GetAt(i);
    if( pArr )
        delete pArr;
    }
	
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
}
