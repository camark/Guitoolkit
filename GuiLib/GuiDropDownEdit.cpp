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
#include "GuiLib.h"
#include "guidropdownedit.h"
#include "GuiDrawLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define DROPBUTTON 0x8888
#define DROPEDIT   0x8881

// CGuiDropDownEdit

IMPLEMENT_DYNAMIC(CGuiDropDownEdit, CStatic)
CGuiDropDownEdit::CGuiDropDownEdit()
{
	bShowButton=TRUE;
	m_border=STYLEPRESS;
}

CGuiDropDownEdit::~CGuiDropDownEdit()
{
}


BEGIN_MESSAGE_MAP(CGuiDropDownEdit, CStatic)
	ON_WM_NCPAINT()
	ON_WM_CREATE()
	ON_COMMAND(DROPBUTTON,OnDropButton)
END_MESSAGE_MAP()



// CGuiDropDownEdit message handlers
void CGuiDropDownEdit::OnDropButton()
{
	GetParent()->SendMessage(WM_COMMAND,GetDlgCtrlID());
}

void CGuiDropDownEdit::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);
	m_cfont.CreateFont(-11,0,0,0,400,0,0,0,0,1,2,1,34,_T("MS Sans Serif"));
	
	CreateControls();
	CStatic::PreSubclassWindow();
}

void CGuiDropDownEdit::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CStatic::OnNcPaint() for painting messages
	CBrush cbr;
	CRect m_rectDraw;
	CPaintDC	dc(this);
	GetClientRect(&m_rectDraw);
	cbr.CreateSolidBrush(GuiDrawLayer::GetRGBColorFace());
	dc.FillRect(&m_rectDraw,&cbr);
	if (m_border == STYLE3D)
		dc.Draw3dRect(m_rectDraw,GuiDrawLayer::GetRGBColorBTNHigh(),
			GuiDrawLayer::GetRGBColorShadow());
	if (m_border == STYLEPRESS)
	{
		dc.Draw3dRect(m_rectDraw,GuiDrawLayer::GetRGBColorShadow(),
			GuiDrawLayer::GetRGBColorBTNHigh());
	}
	if (m_border == STYLEFRAME)
	{
		dc.Draw3dRect(m_rectDraw,GuiDrawLayer::GetRGBColorShadow(),
			GuiDrawLayer::GetRGBColorShadow());
	}
	CSize szBtn=CSize(0,0);
	if (bShowButton)
	{
		if (!m_toolBtn.GetSafeHwnd()) return;
		szBtn=m_toolBtn.GetSizeButton();
	}
	m_rectDraw.DeflateRect(1,1);
	m_Edit.MoveWindow(m_rectDraw.left,m_rectDraw.top,m_rectDraw.Width()-(szBtn.cx+1),m_rectDraw.Height());
	if (bShowButton)
		m_toolBtn.MoveWindow(m_rectDraw.Width()-(szBtn.cx-1),m_rectDraw.top,szBtn.cx,m_rectDraw.Height());
	
}

int CGuiDropDownEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	CreateControls();
	return 0;
}

void CGuiDropDownEdit::SetStyle(Border border)
{
	m_border=border;
}

void CGuiDropDownEdit::SetLimitText(int numText)
{
	m_Edit.SetLimitText(numText);
}

void CGuiDropDownEdit::CreateControls()
{
	m_Edit.Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL,CRect(0,0,0,0),this,DROPEDIT);
	m_Edit.ModifyStyle(WS_BORDER,0);
	m_Edit.SetFont(&m_cfont);
	m_Edit.SetLimitText(100);
	m_toolBtn.Create(_T(""),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0),this,DROPBUTTON);
	m_toolBtn.SetCaption(_T(" ... "));
	m_toolBtn.SetStyleButton(CGuiNormalButton::STL_SEMIFLAT);
}

void CGuiDropDownEdit::ShowButton(BOOL bShow)
{
	bShowButton=bShow;
	m_toolBtn.ShowWindow(bShow?SW_SHOW:SW_HIDE);
}

void CGuiDropDownEdit::SetImageButton(HICON hIcon)
{
	m_toolBtn.SethIcon(hIcon);
	m_toolBtn.SetCaption(_T(""));
}

void CGuiDropDownEdit::SetMask(CString mszMask,CString mszShowMask,CGuiEdit::Mask enTypeMask)
{
	m_Edit.SetMask(mszMask,mszShowMask,enTypeMask);
}

void CGuiDropDownEdit::SetToolTipEdit(CString szToolTip)
{
	m_Edit.SetToolTip(szToolTip);

}
void CGuiDropDownEdit::SetToolTipBtn(CString szToolTip)
{
	m_toolBtn.SetToolTip(szToolTip);
}


CString CGuiDropDownEdit::GetText()
{
	if (!m_Edit.m_szMask.IsEmpty())
		return m_Edit.m_cadResult;
	else
	{
		CString cad;
		m_Edit.GetWindowText(cad);
		return cad;
	}
}

void CGuiDropDownEdit::SetText(CString szCaption)
{
	m_Edit.SetWindowText(szCaption);
}
