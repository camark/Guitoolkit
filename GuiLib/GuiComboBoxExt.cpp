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
#include "GuiComboBoxExt.h"
#include "resource.h"
#include <atlbase.h>  
#include "Guicomboboxext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiComboBoxExt

CGuiComboBoxExt::CGuiComboBoxExt()
{
	m_clrBtnFace= GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	m_clrBtnLight=::GetSysColor(COLOR_3DHILIGHT);
	m_clrBtnDark=::GetSysColor(COLOR_3DSHADOW);
	m_iWidthDrowDown=GetSystemMetrics(SM_CXHTHUMB);
	m_bOverCombo=FALSE;
	m_Font.CreateStockObject (DEFAULT_GUI_FONT);
	m_bPress=FALSE;
	m_imgArrow.Create(IDB_GUI_DOCKBAR,9,10,RGB(255,0,255));
	CBitmap cbmp;
	BITMAP bmp;
	cbmp.LoadBitmap(IDB_GUI_DOCKBAR);
	cbmp.GetBitmap(&bmp);
	mHeight=CPoint(bmp.bmWidth,bmp.bmHeight);	
	m_bFondoXp=FALSE;
	m_IsCallMiniTool=FALSE;
	bColor=TRUE;
	bhistory=FALSE;

	
}

BOOL CGuiComboBoxExt::PreTranslateMessage(MSG* pMsg) 
{
	
	if (pMsg->message == WM_KEYDOWN)
	{
		int nVirtKey = (int) pMsg->wParam;
		if (nVirtKey == VK_RETURN )
		{
			//if (!(GetStyle( ) & CBS_DROPDOWNLIST))
			//{
				CString sCad;
				GetWindowText(sCad);
				AddString(sCad);
			//}
			GetParent()->SendMessage(WM_COMMAND,GetDlgCtrlID());
			return 1;//nonzero so app does not get the esc key and exit
		}
	}
	return CComboBox::PreTranslateMessage(pMsg);
}

void CGuiComboBoxExt::OnSysColorChange( )
{
	CComboBox::OnSysColorChange( );
	m_clrBtnLight=::GetSysColor(COLOR_3DHILIGHT);
	m_clrBtnDark=::GetSysColor(COLOR_3DSHADOW);
	if (bColor)
		m_clrBtnFace= GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
}

void CGuiComboBoxExt::AutoColor(BOOL bAColor)
{
	bColor=bAColor;
}

CGuiComboBoxExt::~CGuiComboBoxExt()
{
}


BEGIN_MESSAGE_MAP(CGuiComboBoxExt, CComboBox)
	//{{AFX_MSG_MAP(CGuiComboBoxExt)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnCbnKillfocus)
//    ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillFocus)
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	//}}AFX_MSG_MAP
	
	ON_CONTROL_REFLECT(CBN_EDITUPDATE, OnCbnEditupdate)
//	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnCbnSelchange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiComboBoxExt message handlers


void CGuiComboBoxExt::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_bOverCombo=TRUE;
	m_bPress=TRUE;
	CClientDC dc(this);
	DrawCombo(CM_SELECCIONADO,&dc);			
	CComboBox::OnLButtonDown(nFlags, point);
}
void CGuiComboBoxExt::ActiveHistory(BOOL bHistory)
{
	bhistory=bHistory;
}

void CGuiComboBoxExt::SaveHistory(CString szHistory,BOOL bSaveCurrent)
{
	int nSize=GetCount();
	if (szHistory.IsEmpty()) return;
	if (nSize == 0) return;
	DeleteHistory(szHistory);
	int nCurs=GetCurSel();
	CString sKey=szHistory;
	CString sCad;
	CWinApp* pAppWin = AfxGetApp();
	if(bSaveCurrent)
	{
		if(nCurs < 0) return;
		GetLBText(nCurs,sCad);
		CString nKeyHist=szHistory+"SaveCurrent";
		pAppWin->WriteProfileString("ComboHistory",nKeyHist,sCad);
	}
	
	for(int i=0; i< nSize; i++)
	{
		GetLBText(i,sCad);
		sKey.Format("%s%d",szHistory,i);
		pAppWin->WriteProfileString("ComboHistory",sKey,sCad);
	}
}

void CGuiComboBoxExt::LoadHistory(CString szHistory,BOOL bLoadCurrent)
{
	if (szHistory.IsEmpty()) return;
	CString sKey=szHistory;
	CString sCad;
	CWinApp* pAppWin = AfxGetApp();
	int i=0;
	while(1){
		sKey.Format("%s%d",szHistory,i++);
		sCad=pAppWin->GetProfileString("ComboHistory",sKey);
		if (sCad.IsEmpty())
			break;
		AddString(sCad);
	}
	if (bLoadCurrent)
	{
		CString sKeyHist=szHistory+"SaveCurrent";
		sCad=pAppWin->GetProfileString("ComboHistory",sKeyHist);
		if (sCad.IsEmpty())
			return;
		AddString(sCad);

	}

}


int	 CGuiComboBoxExt::AddString(LPCTSTR lpszString)
{
	CString szCadAdd;
	szCadAdd=lpszString;
	if (szCadAdd.IsEmpty()) return -1;
	if(bhistory!=TRUE)
		return CComboBox::AddString(lpszString);
	szCadAdd.TrimLeft(" ");
	szCadAdd.TrimRight(" ");
	int nret=CComboBox::InsertString(0,szCadAdd);
	int nFindCad=FindStringExact(0, szCadAdd);
	if (nFindCad != -1 && nFindCad != 0)
		DeleteString(nFindCad );
	SetCurSel(nret);	
	return nret;
}

void CGuiComboBoxExt::DeleteHistory(CString szHistory)
{
	//m_pszRegistryKey=_tcsdup(_T("HKEY_CURRENT_USER\\Software\\mycompany\\myapp\\thissection\\thisvalue"));
	CWinApp* pAppWin = AfxGetApp();
	CString sKey ;
	CRegKey rk;
    if (pAppWin->m_pszRegistryKey == NULL || pAppWin->m_pszAppName == NULL)
      return;
    CString sPath = "SOFTWARE\\";
	sPath+= pAppWin->m_pszRegistryKey + CString("\\");
    sPath+= pAppWin->m_pszAppName + CString("\\");
    sPath+= szHistory;
    if (rk.Open(HKEY_CURRENT_USER, sPath) != ERROR_SUCCESS)
      return;
	int nCount = GetCount();
    for (int i = 0; i < nCount; i++)
    {
	  sKey.Format("%s%d", szHistory,i);
      rk.DeleteValue(sKey);
    }
  CString nKeyHist=szHistory+"SaveCurrent";
  pAppWin->WriteProfileString("ComboHistory",nKeyHist,"");
  ResetContent();
}
void CGuiComboBoxExt::PreSubclassWindow() 
{
	CComboBox::PreSubclassWindow();
}

void CGuiComboBoxExt::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_IsCallMiniTool==TRUE)
		m_bPress=FALSE;
	CComboBox::OnLButtonUp(nFlags, point);
}

void CGuiComboBoxExt::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	/*
	 * Se hace un llamamdo a la función definida por defecto
	 * para el procesamiento de mensajes que la aplicación definitivamente
	 * no esta interesado en manejar
	 **/ 
	m_clrBtnFace=GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style);
	CComboBox::DefWindowProc(WM_PAINT,(WPARAM)dc.m_hDC,0);
	if (m_bPress != TRUE)
		DrawCombo(CM_NORMAL,&dc);
	else
		DrawCombo(CM_SELECCIONADO,&dc);
	// Do not call CComboBox::OnPaint() for painting messages
}

void CGuiComboBoxExt::OnSetFocus(CWnd* pOldWnd) 
{
	CComboBox::OnSetFocus(pOldWnd);
	CClientDC dc(this);
	DrawCombo(CM_SELECCIONADO,&dc);			
	
}

BOOL CGuiComboBoxExt::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptCurPos;
	CRect m_rcCli;
	GetCursorPos (&ptCurPos);
	ScreenToClient (&ptCurPos);
	GetClientRect(&m_rcCli);
	if (m_rcCli.PtInRect (ptCurPos) && m_bOverCombo==FALSE && m_bPress==FALSE)
		{
			m_bOverCombo=TRUE;
			CClientDC dc(this);
			DrawCombo(CM_ONFOCUS,&dc);			
			SetTimer(1,10,NULL);
			OnTimer(1);
			return TRUE;
		}
			
	return CComboBox::OnSetCursor(pWnd, nHitTest, message);
}

void CGuiComboBoxExt::SetColor(COLORREF clrFace)
{
	m_clrBtnFace=clrFace;
	Invalidate();
	UpdateWindow();
	
}

void CGuiComboBoxExt::DrawCombo(enTypeShow enShow,CDC* pDC)
{

    CRect m_rcClient;
	CRect m_rcDropDown;
	GetClientRect(&m_rcClient);
	//primero eliminamos los bordes 3D del combobox
	pDC->Draw3dRect(&m_rcClient,m_clrBtnFace,m_clrBtnFace);
	m_rcClient.DeflateRect(1,1);
	if (IsWindowEnabled())
	{
		if (enShow==CM_NORMAL)
			pDC->Draw3dRect(&m_rcClient,GuiDrawLayer::GetRGBPressBXP(),GuiDrawLayer::GetRGBPressBXP());
	}
    else
	pDC->Draw3dRect(&m_rcClient,m_clrBtnLight,m_clrBtnLight);	

	if (enShow==CM_NORMAL)
		pDC->Draw3dRect(&m_rcClient,m_clrBtnFace,m_clrBtnFace);
	else // && !XP
		pDC->Draw3dRect(&m_rcClient,GuiDrawLayer::GetRGBCaptionXP(),GuiDrawLayer::GetRGBCaptionXP());
	//debemos pintar el borde del boton drawDwon
	m_rcClient.DeflateRect(1,1);
	m_rcClient.left=m_rcClient.right-m_iWidthDrowDown;
	pDC->Draw3dRect(&m_rcClient,m_clrBtnFace,m_clrBtnFace);
	m_rcClient.DeflateRect(1,1);
	pDC->Draw3dRect(&m_rcClient,GuiDrawLayer::GetRGBCaptionXP(),GuiDrawLayer::GetRGBCaptionXP());
	m_rcClient.InflateRect(0,1);
	if (enShow==CM_NORMAL)
	{
		//el boton no esta seleccionado
		
		m_rcClient.right += 1;
		m_rcClient.left  -= 1;
		pDC->Draw3dRect(&m_rcClient,m_clrBtnLight,m_clrBtnLight);
		m_rcClient.DeflateRect(1,1);
		CBrush cblu;
		cblu.CreateSolidBrush( m_clrBtnFace);
		pDC->FillRect(&m_rcClient,&cblu);
		m_rcClient.left += 2;
		m_rcClient.right+= 2;
		DrawArrow(pDC,m_rcClient);
	}
	else

	{
		m_rcClient.InflateRect(1,1);
		CBrush cblu;
		cblu.CreateSolidBrush(enShow == CM_ONFOCUS? GuiDrawLayer::GetRGBFondoXP():GuiDrawLayer::GetRGBPressBXP());
		pDC->FillRect(&m_rcClient,&cblu);
		m_rcClient.right += 1;
		pDC->Draw3dRect(&m_rcClient,GuiDrawLayer::GetRGBCaptionXP(),GuiDrawLayer::GetRGBCaptionXP());
		DrawArrow(pDC,m_rcClient);
	
	}
	
}

void CGuiComboBoxExt::DrawArrow(CDC* pDC,CRect m_rc)
{
	int difh =m_rc.Height()-mHeight.y;
	difh/=2;
	
	m_rc.left=m_rc.right-m_iWidthDrowDown;
	m_imgArrow.Draw(pDC,0,CPoint(m_rc.left+2,m_rc.top+difh),ILD_TRANSPARENT);		
	
}

void CGuiComboBoxExt::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent== 1)
	{
		CPoint pt(GetMessagePos());
		CRect m_rc;
		ScreenToClient(&pt);
		GetClientRect(m_rc);
		if (!m_rc.PtInRect(pt) && m_bPress!=TRUE)
		{
		 	KillTimer(1);
			m_bOverCombo=FALSE;
			CClientDC dc(this);
			if (m_bPress==FALSE)
		 		DrawCombo(CM_NORMAL,&dc);			
			else
				DrawCombo(CM_ONFOCUS,&dc);	
			m_bPress=FALSE;
		}		
	}
	
	CComboBox::OnTimer(nIDEvent);
}

void  CGuiComboBoxExt::OnCloseup() 
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);
	m_bPress=FALSE;
	OnTimer(1);
	
}

//void CGuiComboBoxExt::OnKillFocus(CWnd* pNewWnd) //version 6
void CGuiComboBoxExt::OnCbnKillfocus() //version 7.0
{
    CClientDC dc(this);
	DrawCombo(CM_NORMAL,&dc);

	if (!(GetStyle( ) & CBS_DROPDOWNLIST))
	{
		CString sCad;
		GetWindowText(sCad);
		AddString(sCad);
	}
	
	m_bPress=FALSE;
	m_bOverCombo=FALSE;
	// TODO: Add your message handler code here
	
}

int CGuiComboBoxExt::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetFont (&m_Font);	
	return 0;
}

void CGuiComboBoxExt::OnCbnEditupdate()
{
  CString m_szCad;
  GetWindowText(m_szCad);
  
  DWORD m_dwCurRange=GetEditSel();
  DWORD m_dwStart=LOWORD(m_dwCurRange);
  DWORD m_dwEnd = HIWORD(m_dwCurRange);
  //se busca la cadena aprox, si no existe se debe insertar
 
	if (SelectString(-1,m_szCad) == CB_ERR)
	{
		SetWindowText(m_szCad);
		SetEditSel(m_dwStart,m_dwEnd);
	}
	else
	{
		if (m_dwCurRange != CB_ERR)
		{
			if (m_dwEnd <(DWORD) m_szCad.GetLength())
				SetEditSel(m_dwStart,m_dwEnd);
			else
				SetEditSel(m_szCad.GetLength(),-1);
		}
	}
}

void CGuiComboBoxExt::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
}

void CGuiComboBoxExt::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
}
void CGuiComboBoxExt::OnCbnSelchange()
{
//	OnCbnKillfocus();
	// TODO: Add your control notification handler code here
}
