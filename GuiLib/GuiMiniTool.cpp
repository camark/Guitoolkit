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
 * -Ernesto Garcia															*	
 ****************************************************************************/

#include "stdafx.h"
#include "GuiMiniTool.h"
#include "GuiDrawLayer.h"
#include "GuiToolButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiMiniTool

CGuiMiniTool::CGuiMiniTool()
{
	m_arrButtons.RemoveAll();
	nNumItems=0;
	m_AlingButton=ALIGN_LEFT;
	m_AlinTexto=ALIGN_LEFT;
	m_clrface=GuiDrawLayer::GetRGBColorXP();
	m_bAutoSize=FALSE;
	m_bExisteCombo=FALSE;
	m_cfont.CreateFont(-11,0,0,0,400,0,0,0,0,1,2,1,34,_T("MS Sans Serif"));
	m_clrCaption=GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style);
	m_Caption=_T("");
	msz=CSize(0,0);
	m_StyleDisplay=GUISTYLE_XP;
	
}

CGuiMiniTool::~CGuiMiniTool()
{
	m_arrButtons.RemoveAll();
}


BEGIN_MESSAGE_MAP(CGuiMiniTool, CStatic)
	//{{AFX_MSG_MAP(CGuiMiniTool)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiMiniTool message handlers

int CGuiMiniTool::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CGuiMiniTool::OnSysColorChange( )
{
	CStatic::OnSysColorChange( );
	StyleDispl(m_StyleDisplay);
	
	
}

//********************************************************************************
void  CGuiMiniTool::PreSubclassWindow()
{
	CStatic::PreSubclassWindow();
}

//********************************************************************************
void  CGuiMiniTool::AddButton(int nIndex,UINT Cmd,CMenu* pMenu,CString m_szCaption,CString m_ToolTip)
{
	
	m_arrButtons.SetAtGrow(nNumItems, new CArrButton
			(this,m_imgList.ExtractIcon(nIndex),Cmd,&m_cfont,m_szCaption,pMenu,m_ToolTip));
	
	nNumItems++;
	RecalLayout();

}

//**************************************************************************
HICON CGuiMiniTool::GetImagIcon(int nNum)
{
	return m_imgList.ExtractIcon(nNum);
}
//****************************************************************************
BOOL  CGuiMiniTool::CreateCombo(CGuiComboBoxExt* pControl,UINT nID,int iSize,
				DWORD dwStyle)
{
	ASSERT(pControl);
	if (!pControl->Create(dwStyle, 
			  CRect(1,1,iSize,250), this, nID))
	   return FALSE;
	pControl->m_IsCallMiniTool=TRUE;
	m_arrButtons.SetAtGrow(nNumItems, new CArrButton(pControl));
	nNumItems++;
	RecalLayout();
	return TRUE;

}

//********************************************************************************
void  CGuiMiniTool::SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	CBitmap cbmp;
	BITMAP bmp;
	m_imgList.Create(nBitmapID,cx,nGrow,crMask);
	cbmp.LoadBitmap(nBitmapID);
	cbmp.GetBitmap(&bmp);
	m_imgList.Add(&cbmp,crMask);

}

//********************************************************************************
void CGuiMiniTool::AutoSize(BOOL mbAutosize)
{  
	m_bAutoSize=mbAutosize;
	RecalLayout();
}	

//********************************************************************************
void  CGuiMiniTool::DelButton(int nIndex)
{
	nNumItems--;
	m_arrButtons.RemoveAt(nIndex,nNumItems);
	RecalLayout();
}

//********************************************************************************	
int   CGuiMiniTool::GetCountButton()
{
	return m_arrButtons.GetSize();
}

//********************************************************************************	
void  CGuiMiniTool::RecalLayout()
{
	if (!GetSafeHwnd()) return;
	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.DeflateRect(1,1);
	CRect rctemp=rcClient;
	int nTipo=0;
	if (m_bAutoSize)
		CalcAutoSize(rcClient);
	if (msz.cx > 0)
	{
		if (m_AlinTexto==ALIGN_LEFT)
			rctemp.left+=msz.cx;
		else
			rctemp.right-=msz.cx;
	}

	for (int i=0; i < nNumItems;i++)
	{
		
		CArrButton* m_cwnd=(CArrButton*) m_arrButtons [i];
		
		if(m_cwnd->m_btipo== TRUE)  //es un boton
		{
			CSize sztemp=((CArrButton*) m_arrButtons [i])->m_bt.GetSizeButton();
			nTipo=sztemp.cx;
		}
		else
		{
			CRect rctemp;
			m_cwnd->m_pwnd->GetWindowRect(rctemp);
			if (m_bAutoSize)
			{
				nTipo=m_nResultCombo;
				rctemp.right=rctemp.left+nTipo;
			}
			else
				nTipo=rctemp.Width();
		}
		if (m_AlingButton == ALIGN_RIGHT)
			rctemp.left=rctemp.right-nTipo;
		else
			rctemp.right=rctemp.left+nTipo;
		if (m_cwnd->m_btipo==TRUE)
			m_cwnd->m_bt.MoveWindow(rctemp);
		else
			m_cwnd->m_pwnd->MoveWindow(rctemp);
		if (m_AlingButton == ALIGN_RIGHT)
			rctemp.right-=nTipo;
		else
			rctemp.left+=nTipo;

	}
	m_rcDrawTexto=rctemp;
	Drawtext();
}

//*********************************************************************
void CGuiMiniTool::AlingButtons(Aling Alingsb)
{
	m_AlingButton=Alingsb;	
}

void CGuiMiniTool::SetCaption(CString mSzCaption,Aling AlinText)
{
	CClientDC dc(this);
	m_Caption=mSzCaption;
	msz=dc.GetTextExtent(m_Caption,m_Caption.GetLength());
	m_AlinTexto=AlinText;
}

void CGuiMiniTool::SetColorCaption(COLORREF	clrCaption)
{
	m_clrCaption=clrCaption;
}
//*********************************************************************
void CGuiMiniTool::CalcAutoSize(CRect m_rc)
{

	m_nResultCombo=0;
    m_nResultButtons=0; 	
	int m_numCombo=0;
	for (int i=0; i < nNumItems;i++)
	{
		if (((CArrButton*) m_arrButtons [i])->m_btipo ==TRUE)
		{
			CArrButton* mt=(CArrButton*) m_arrButtons [i];
			CSize sztemp=((CArrButton*) m_arrButtons [i])->m_bt.GetSizeButton();
			m_nResultButtons+=sztemp.cx;
		}
		else
		{
			m_bExisteCombo=TRUE;	
			m_numCombo++;
		}
	}

	//calculamos el espacio para los combobox

	if (m_bExisteCombo)
	{
		if (m_nResultButtons+msz.cx > m_rc.Width())  //el espacio no alcanza para los botones
			m_nResultCombo=0;
		else
		{
			if ((GetSystemMetrics(SM_CXHTHUMB)+msz.cx) > m_rc.Width()-50)
				m_nResultCombo=0;
			else
				{
					m_nResultCombo=m_rc.Width()-(m_nResultButtons+msz.cx);
					m_nResultCombo/=m_numCombo;
				}
				
		}
	}

}

//********************************************************************************

void CGuiMiniTool::SetBorder(Borders Style)
{
	m_border=Style;
}  


//********************************************************************************
void CGuiMiniTool::OnPaint() 
{

	CPaintDC dc(this); // device context for painting
	CBrush cbr;
	CRect rcClient;
	GetClientRect(&rcClient);
	cbr.CreateSolidBrush(m_clrface);
	
	CDC			MemDC;
	CBitmap		m_BitmapMemDC;
	MemDC.CreateCompatibleDC(&dc);
	m_BitmapMemDC.CreateCompatibleBitmap(&dc,
				  rcClient.Width(),rcClient.Height());	

	CBitmap* m_bitmapOld=MemDC.SelectObject(&m_BitmapMemDC);
	if(m_StyleDisplay==GUISTYLE_XP)
		MemDC.FillRect(&rcClient,&cbr);
	
	if(m_StyleDisplay== GUISTYLE_2003)
	{
		CGradient M(CSize(rcClient.Width(),rcClient.Height()+1));	
		M.PrepareVertical(&MemDC,GUISTYLE_2003);
		M.Draw(&MemDC,0,0,0,0,rcClient.Width(),rcClient.Height(),SRCCOPY);	
	}	
	
	
	if (m_border == STYLE3D)
		MemDC.Draw3dRect(rcClient,GuiDrawLayer::GetRGBColorBTNHigh(),
		GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	if (m_border == STYLEPRESS)
	{
		MemDC.Draw3dRect(rcClient,GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style),
			GuiDrawLayer::GetRGBColorBTNHigh());
	}
	if (m_border == STYLEFRAME)
	{
		MemDC.Draw3dRect(rcClient,GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style),
			GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	}

	
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&MemDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();
	Drawtext();
	cbr.DeleteObject();

/*



	CPaintDC dc(this); // device context for painting
	CBrush cbr;
	CRect m_rectDraw;
	GetClientRect(&m_rectDraw);
	cbr.CreateSolidBrush(m_clrface);
	dc.FillRect(&m_rectDraw,&cbr);
	
*/		//el flat ya esta
}


//********************************************************************************
void CGuiMiniTool::SetColor(COLORREF m_clrFace)
{
	m_clrface=m_clrFace;
	for (int i=0; i < nNumItems;i++)
    	if (((CArrButton*) m_arrButtons [i])->m_btipo ==TRUE)
			((CArrButton*) m_arrButtons [i])->m_bt.SetColor(m_clrface);
		else
			((CArrButton*) m_arrButtons [i])->m_pwnd->SetColor(m_clrface);
	
}

//********************************************************************************
void CGuiMiniTool::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	RecalLayout();	
	// TODO: Add your message handler code here
	
}

//********************************************************************************
BOOL CGuiMiniTool::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}


//********************************************************************************
CArrButton::CArrButton(CGuiMiniTool* pParent,HICON m_hIcon,UINT Cmd,CFont* m_cfont,CString m_szCaption,
					   CMenu *pMenu,CString m_ToolTip)
{

	m_bt.Create(_T(""), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
		CRect(0,0,0,0), pParent, Cmd);
	if (!m_szCaption.IsEmpty())
	{
		m_bt.SetFont(m_cfont);
		m_bt.SetCaption(m_szCaption);
		
	}
//	m_bt=m_button;
	m_bt.SethIcon(m_hIcon);
	m_bt.SetToolTip(m_ToolTip);
	m_bt.SetMenu(pMenu);
	m_btipo=TRUE;
}

//********************************************************************************
CArrButton::CArrButton(CGuiComboBoxExt* m_pComponent)
{
	ASSERT(m_pComponent);
	m_pwnd=m_pComponent;
	m_btipo=FALSE;
}

//********************************************************************************
BOOL CGuiMiniTool::OnCommand(WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = (HWND) lParam;	
	for (int i=0; i < nNumItems;i++)
	{
		if (((CArrButton*) m_arrButtons [i])->m_btipo ==TRUE)
			if (((CArrButton*) m_arrButtons [i])->m_bt.m_hWnd
				== hwnd)
			{
				int x=((CArrButton*) m_arrButtons [i])->m_bt.GetDlgCtrlID();
				CWnd* pParent= GetParent();
				pParent->SendMessage (WM_COMMAND,x);
				AfxGetMainWnd()->SendMessage(WM_COMMAND,x);
				return TRUE;
			}
	
	}
	return FALSE;

}

CGuiToolButton*  CGuiMiniTool::GetButton(UINT uID_Object)//,CGuiToolButton* m_btn)
{
	
	for (int i=0; i < nNumItems;i++)
	{
		if (((CArrButton*) m_arrButtons [i])->m_btipo ==TRUE)
			if (((CArrButton*) m_arrButtons [i])->m_bt.GetDlgCtrlID()==(int signed )uID_Object)
			{
				
				CGuiToolButton* m_btn=&((CArrButton*) m_arrButtons [i])->m_bt;
				return m_btn;
				
			}
	
	}
	return NULL;//m_btn=NULL;
}


void CGuiMiniTool::Drawtext()
{
	CClientDC dc(this);
	CRect rc;
	GetClientRect(rc);
	CFont* m_fontOld=dc.SelectObject(&m_cfont);
	int nMode = dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(m_clrCaption);
	if(m_AlinTexto==ALIGN_LEFT)
	{
		rc.left+=5;
		dc.DrawText(m_Caption,rc,DT_SINGLELINE|DT_LEFT|DT_VCENTER) ;
	}
	else
	{
			m_rcDrawTexto.left=(long)(rc.right-msz.cx*1.1);
			m_rcDrawTexto.right=m_rcDrawTexto.left+msz.cx;
			dc.DrawText(m_Caption,m_rcDrawTexto,DT_SINGLELINE|DT_RIGHT|DT_VCENTER) ;
	}
	dc.SetBkMode(nMode);
	dc.SelectObject(m_fontOld);
	
}

//thanks to  Ernesto Garcia	

void CGuiMiniTool::OnDestroy()
{
	
	for( int i=0; i<nNumItems; i++ )
    {
    CArrButton *pArr = (CArrButton*)m_arrButtons.GetAt(i);
    if( pArr )
        delete pArr;
    }
	
	CStatic::OnDestroy();

	// TODO: Add your message handler code here
}
