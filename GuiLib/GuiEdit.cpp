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
#include "GuiEdit.h"
#include "GuiDrawLayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiEdit

CGuiEdit::CGuiEdit()
{
	m_szMask=_T("");
	m_szShowMask=_T("");
	StrToUse=_T("()-,.@#AaXx/:\\"); //caracteres para armar la mascara
	m_cadResult=_T("");
	m_enMask=MASK_FREEMASK;
	m_KeySpecial=0;
}

CGuiEdit::~CGuiEdit()
{
}


BEGIN_MESSAGE_MAP(CGuiEdit, CEdit)
	//{{AFX_MSG_MAP(CGuiEdit)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_NCPAINT()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiEdit message handlers

void CGuiEdit::PreSubclassWindow() 
{
	CEdit::PreSubclassWindow();
}

int CGuiEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_tooltipCtrl.Create(this,TTS_ALWAYSTIP);
	m_tooltipCtrl.Activate(TRUE);
	m_tooltipCtrl.BringWindowToTop();
	return 0;
}

void CGuiEdit::OnPaint() 
{
	CClientDC dc(this);
    Default();
	RecalLayout();
}

void CGuiEdit::OnSysColorChange() 
{
	CEdit::OnSysColorChange();
}
 


BOOL CGuiEdit::AddButton(HICON hIcon,UINT nID,CMenu* m_menu,CString mToolTip)
{
	if (!m_bnt.Create(_T(""), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 
		CRect(0,0,0,0), this, nID))
		return FALSE;

	m_bnt.SetImage(hIcon);
	m_bnt.SetToolTip(mToolTip);
	m_bnt.SetStyleBorder(CGuiButton::STYLE_SEMIFLAT);
	m_bnt.SetMenu(m_menu);
	RecalLayout();
	return TRUE;

	
}

void CGuiEdit::RecalLayout()
{
	CRect rc;
	GetClientRect(rc);
	if (!m_bnt.GetSafeHwnd()) return;
	CSize msz= m_bnt.GetSizeButton();
	rc.left=rc.right-msz.cx+1;
	m_bnt.MoveWindow(&rc);
}


void CGuiEdit::SetToolTip(LPCTSTR lpMsg)
{
	CRect rc;
	LPCTSTR m_lpMsg=lpMsg;
	if (GetSafeHwnd ()== NULL) return;
	if (m_lpMsg != NULL)
	{
		if (m_tooltipCtrl.GetSafeHwnd () == NULL) 
		{
			m_tooltipCtrl.Create(this,TTS_ALWAYSTIP);
			m_tooltipCtrl.Activate(TRUE);
			m_tooltipCtrl.AddTool(this,lpMsg);
		}
		else
		{
			m_tooltipCtrl.UpdateTipText(lpMsg,this);	
		}
	}
	else
	{
		if (m_tooltipCtrl.GetSafeHwnd () == NULL) 
		{
			m_tooltipCtrl.Create(this,TTS_ALWAYSTIP);
			m_tooltipCtrl.AddTool(this,lpMsg);
		}
		else
			m_tooltipCtrl.UpdateTipText(lpMsg,this);	
		m_tooltipCtrl.Activate(FALSE);
	}
	

}

void CGuiEdit::OnNcPaint() 
{
	CRect rcWindow;
	CRect rcClient;
	CWindowDC	dc(this);
	GetWindowRect(&rcWindow);
	GetClientRect(&rcClient);
	CBrush cbr;
	cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace());
	rcClient.OffsetRect(-rcWindow.TopLeft());
    rcWindow.OffsetRect(-rcWindow.TopLeft());
    ScreenToClient(rcWindow);
	rcClient.OffsetRect(-rcWindow.left,-rcWindow.top);
	dc.ExcludeClipRect(rcClient);   
	rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);
	int ibotton=rcWindow.bottom;
	rcWindow.top=rcWindow.bottom;
	dc.FillRect(rcWindow,&cbr); 
	rcWindow.top=0;
	dc.FillRect(rcWindow,&cbr); 
	dc.Draw3dRect(rcWindow,GuiDrawLayer::GetRGBColorFace(),GuiDrawLayer::GetRGBColorFace()); 
	rcWindow.DeflateRect(1,1);
	dc.Draw3dRect(rcWindow,GuiDrawLayer::GetRGBCaptionXP(),GuiDrawLayer::GetRGBCaptionXP()); 
}


void CGuiEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_szMask.IsEmpty())
	{
		ValidMask(nChar);
		if (nChar == 8) return;
		switch(m_enMask)
		{
		
		case MASK_HOUR12:
//			EvalHour(nChar,12);
				break;
		case MASK_HOUR24:
//			EvalHour(nChar,24);
			break;
		case	MASK_HOURFREE:
		//	EvalHour(nChar);
			break;
		case	MASK_IPADDRESS:
			break;
		case	MASK_DATEDDMMYYYY:
			break;
		case 	MASK_DATEMMDDYYYY:
			break;
		case	MASK_DATEYYYYDDMM:
			break;
		case	MASK_DATEYYYYMMDD:
			break;
		case	MASK_FREEMASK:
			break;
		}
		return;
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CGuiEdit::DeleteString(int nStartPos,int  nEndPos )
{
	for (int i=nStartPos; i <= nEndPos; i++)
		m_szShowMask.SetAt(i,m_cadResult.GetAt(i));	
	int nNext = GetNextPos(nStartPos);
	SetWindowText(m_szShowMask);
	if (nNext > 0)
		SetSel(nNext-1,nNext-1);	
	m_KeySpecial=0;

}

void CGuiEdit::DeleteAndAjust(int nStartPos,int  nEndPos )
{
	int nNext=nStartPos;
	int difchar=DifCharReal(nStartPos, nEndPos);

	if (IsPosMask(nStartPos))
		nNext = GetNextPos(nStartPos);	
	while(nNext < nNext+difchar)
	{
		AjustaCadena(nNext,nNext+difchar);
		difchar-=1;
	}

}

void CGuiEdit::AjustaCadena(int nStartPos,int  nEndPos )
{
	
	int numCharMove=0;
	int LastChar=FindLasCharR(); //el ultimo caracter valido de la cadena
	int LastCharDel=LastChar;
	int init =nStartPos;
	for (int i=nStartPos; i <= LastChar; i++)
	{
			int nNext = GetNextPos(nStartPos);
			if (IsValidChar(m_szShowMask.GetAt(nNext),nNext) || m_szShowMask.GetAt(nNext)==m_cadResult.GetAt(i))//el caracter se puede mover a esa posicion			
			{
				//se mueve el caracter
				m_szShowMask.SetAt(nStartPos,m_szShowMask.GetAt(nNext));			
				//se reemplaza la ultima posicion despues del ultimo caracter con el
				//equivalente en la mascara
				//obtenemos la proxima posicion donde se moveria el proximo caracter
				nStartPos = GetNextPos(nStartPos);
				numCharMove++;
			}
		
	}
	DeleteString(LastCharDel,LastCharDel);
	SetSel(init,init);	
	m_KeySpecial=0;

}

int CGuiEdit::FindLasCharR()
{
	for (int i=m_szShowMask.GetLength()-1;i> -1; i--)
	{
		if (m_szShowMask.GetAt(i) ==' ' || IsPosMask(i))
			continue;
		else
			return i;
	}
	
	return i;	
}



int CGuiEdit::NumCharNoMask()
{
	int numEfect=0;
	for (int i=0;i<m_cadResult.GetLength()-1; i++)
		if (!IsPosMask(m_cadResult.GetAt(i)))
			numEfect++;
	return numEfect;
}

int CGuiEdit::DifCharReal(int start, int fin)
{
	int numEfect=0;
	for (int i=start;i<fin; i++)
		if (!IsPosMask(i))
			numEfect++;
	return numEfect;
}

//1 -- DEL
//2 -- BACK
void CGuiEdit::ValidMask(UINT nChar)
{
	int nStartPos;
	int ntempStartpos;
	int nEndPos;
	int nNext;
	GetSel( nStartPos, nEndPos ); 
	ntempStartpos=nStartPos;

	if (nStartPos != nEndPos)
		if (m_KeySpecial == 1)
		{
			DeleteAndAjust(nStartPos,nEndPos);
			return;
		}

		

	if (ntempStartpos > m_cadResult.GetLength()-1)
		ntempStartpos=m_cadResult.GetLength()-1;
	if (!IsValidChar(nChar,ntempStartpos) && m_KeySpecial ==0 || 
		             nChar == 32 || nChar == 8) 
	{
		if (m_KeySpecial == 1)
		{
			//si esta un caracter no valido de la mascara
			//emita un pito y ubique el proximo valido.
			if (IsPosMask(ntempStartpos))
			{
				Beep(500,1);
				nNext = GetNextPos(ntempStartpos);
				SetSel(nNext,nNext);	
				m_KeySpecial=0;
				return;
			}
			else
			{
				AjustaCadena(nStartPos,nEndPos );	
				m_KeySpecial=0;
			}
		}
		else if(m_KeySpecial == 0)
		{
			//primero verificar que no sea un caracter de la mascara por 
			//ejemplo ( - etc..
			nNext = GetNextPos(ntempStartpos);
			if (IsValidChar(nChar,nNext))
			{
				m_szShowMask.SetAt(nNext,nChar);
				nNext = GetNextPos(nNext);
				SetWindowText(m_szShowMask);
				SetSel(nNext,nNext);	
			}
			else //el caracter se desconoce
				SetSel(ntempStartpos,ntempStartpos);	
		}
		else
		{  //si es back se debe encontrar la proxima posición y 
		   //eliminar dicho espacio
				nNext = GetNextPos(nStartPos);
				m_szShowMask.SetAt(nNext,m_cadResult.GetAt(nNext));
				SetWindowText(m_szShowMask);
				SetSel(nNext,nNext);	
				m_KeySpecial=0;			
		}
		
	}
	else
	{	
		//entrada de datos normal
		if (!IsValPos(nChar,ntempStartpos))
			return;
		m_szShowMask.SetAt(ntempStartpos,nChar);
		nNext = GetNextPos(ntempStartpos);
		SetWindowText(m_szShowMask);
		SetSel(nNext, nNext);
		if (ntempStartpos==m_szMask.GetLength()-1)
			SetSel(nNext+1, nNext+1);
		
	}
}

BOOL CGuiEdit::IsPosMask(int nStartPos)
{
	TCHAR Char =m_szMask.GetAt(nStartPos);
	if (Char == '#' || Char == '0')
			return FALSE;
	else if (Char == 'A' || Char == 'a')
			return FALSE;
	return TRUE;

}

BOOL CGuiEdit::IsValidChar(UINT nChar,int nStartPos)
{
	
	TCHAR Char =m_szMask.GetAt(nStartPos);
	
	if (Char == '#' || Char == '0')
	{
		if( !isdigit( nChar ))
			return FALSE;
	}
	else if (Char == 'A' || Char == 'a')
	{
		if( !isalpha( nChar ))
			return FALSE;
	}
	else
		return FALSE;
	return TRUE;	
}

int CGuiEdit::GetNextPos(int start)
{
	if (m_KeySpecial == 2)
	{
		for (int i= start-1; i>-1;i--)
		{
			if (m_szMask.GetAt(i) == '#' || 
				m_szMask.GetAt(i) == '0' ||
				m_szMask.GetAt(i) == 'A' ||
				m_szMask.GetAt(i) == 'a' 
				)
			return i;
		}

	}

	
	for (int i= start+1; i< m_szMask.GetLength();i++)
	{
		TCHAR m=m_szMask.GetAt(i);
		if (m_szMask.GetAt(i) == '#' || 
			m_szMask.GetAt(i) == '0' ||
			m_szMask.GetAt(i) == 'A' ||
			m_szMask.GetAt(i) == 'a' 
			)
			return i;
	}
	return start;
}


void CGuiEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_szMask.IsEmpty())
	{
		
		if (nChar == VK_DELETE) 
		{
			m_KeySpecial=1;
			AfxCallWndProc(this, m_hWnd, WM_CHAR, ' ', 1);
			return;
		}
		if (nChar == VK_BACK) 
		{
			m_KeySpecial=2;
			return;
		}
		if(nChar == VK_RIGHT)
		{
			int nStartPos, nEndPos;
			GetSel( nStartPos, nEndPos ); 
			m_KeySpecial=3;
			//controlar que si no existen caracteres validos hacia
			//adelante el cursor debe detenerce.
			if (!ValSpecialKey(nStartPos,nEndPos))
			{
				SetSel(nStartPos,nStartPos);	
				return;
			}
			
		}

	
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL  CGuiEdit::ValSpecialKey(int nStartPos,	int nEndPos)
{
	int nNext=nStartPos;
	TCHAR Char =m_szMask.GetAt(nStartPos);
	if (m_KeySpecial == 3)
	{
		nNext = GetNextPos(nStartPos);
		if (m_szShowMask.GetAt(nNext) == m_cadResult.GetAt(nNext))	
		{
			m_KeySpecial=0;	
			return FALSE;
		}
	}
	m_KeySpecial=0;	
	return TRUE;


}
void CGuiEdit::SetMask(CString mszMask,CString mszShowMask,Mask enTypeMask)
{
	m_szMask=mszMask;
	m_szShowMask=mszShowMask;
	m_enMask=enTypeMask;
	m_cadResult=mszShowMask;
	SetWindowText(m_szShowMask);
	SetLimitText( m_szMask.GetLength()+1);
	int nNext = GetNextPos(0);
	SetSel(nNext, nNext);
}

BOOL CGuiEdit::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->lParam == WM_MOUSEMOVE)
		m_tooltipCtrl.RelayEvent(pMsg);
	return CEdit::PreTranslateMessage(pMsg);
}

void CGuiEdit::OnSize(UINT nType, int cx, int cy) 
{
	CEdit::OnSize(nType, cx, cy);
	RecalLayout();	
	// TODO: Add your message handler code here
	
}

BOOL CGuiEdit::IsValPos(UINT nChar,int pos)
{
	if (IsValidChar(nChar,pos))
	{
		if (pos > 0)
		{
			m_KeySpecial=2;
			int nNext=GetNextPos(pos);
			m_KeySpecial=0;
			if (m_szShowMask.GetAt(nNext) == m_cadResult.GetAt(nNext) && pos > nNext)			
			{
				SetSel(nNext,nNext);
				return FALSE;
			}
			else
				return TRUE;	//todo Ok
		}
		else return TRUE;
	}
	return FALSE;
}

void CGuiEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	int nNext=GetNextPos(0);
	SetSel(nNext,nNext);
	
}
