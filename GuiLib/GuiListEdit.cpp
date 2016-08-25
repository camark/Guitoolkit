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
#include "GuiListEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define  LST_DELETE	555
#define  LST_INSERT 556
#define  LST_UP     557
#define  LST_DOWN   558
#define  LST_LIST	559
#define  DROPBUTTON 560
// CGuiListEdit

IMPLEMENT_DYNAMIC(CGuiListEdit, CStatic)

CGuiListEdit::CGuiListEdit()
{
	m_border=STYLEFRAME;
	m_clrface=GuiDrawLayer::GetRGBColorFace();
}

CGuiListEdit::~CGuiListEdit()
{
}


BEGIN_MESSAGE_MAP(CGuiListEdit, CStatic)
	ON_COMMAND(LST_DELETE,Delete)
	ON_COMMAND(LST_INSERT,Insert)
	ON_COMMAND(LST_UP,Up)
	ON_COMMAND(LST_DOWN,Down)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_ENDLABELEDIT, LST_LIST, OnEndlabeleditList)
	ON_NOTIFY(NM_DBLCLK, LST_LIST, OnClickList)
	ON_NOTIFY(LVN_BEGINLABELEDIT, LST_LIST, OnBeginlabeleditList)
	
END_MESSAGE_MAP()



// CGuiListEdit message handlers
void CGuiListEdit::Delete()
{
	//solo nos interesa el seleccionado actualmente
	int nItem=m_list->GetNextItem(-1,LVNI_SELECTED);
	m_list->DeleteItem(nItem);
}

void CGuiListEdit::OnBeginlabeleditList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

CString CGuiListEdit::GetText(int nItem)
{
	if (nItem < 0) return _T("");
	if (nItem > m_list->GetItemCount()) return _T("");
	CString m_szA=m_list->GetItemText(nItem,0);
	return m_szA;
}

int CGuiListEdit::GetNumItem()
{
	return m_list->GetItemCount();
}


void CGuiListEdit::AddItem(CString m_szCad)
{
	int nItem=m_list->GetItemCount();
	nItem=m_list->InsertItem(nItem,m_szCad);
	m_list->SetItemData (nItem, 0);
}



void CGuiListEdit::OnClickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	int nActual=m_list->GetNextItem(-1,LVNI_SELECTED);
	if (nActual == -1) 
		Insert();

}
void CGuiListEdit::Insert()
{
	CRect rc;
	m_list->SetFocus();
	int nItem=m_list->GetItemCount();
	nItem=m_list->InsertItem(nItem,_T(""));
	m_list->SetItemData (nItem, 0);
    m_list->GetItemRect(0,&rc,LVIS_SELECTED | LVIS_FOCUSED);
	CEdit* mEdit=m_list->EditLabel(nItem);
	CSize szBtn=m_toolBtn.GetSizeButton();
	mEdit->SetWindowPos (NULL, -1, -1,
		rc.Width () - 10, rc.Height (),
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	
}

void CGuiListEdit::OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	LV_ITEM* pItem = &((LV_DISPINFO*)pNMHDR)->item;
	CString m_sz=pItem->pszText;
	if (!m_sz.IsEmpty())
		m_list->SetItemText(pItem->iItem,0,m_sz);

	*pResult = 0;
}



void CGuiListEdit::Up()
{
	int nActual=m_list->GetNextItem(-1,LVNI_SELECTED);
	if (nActual == -1) return;
	if (nActual > 0)
	{
		CString m_szA=m_list->GetItemText(nActual,0);
		CString m_sz=m_list->GetItemText(nActual-1,0);
		m_list->SetItemText(nActual,0,m_sz);
		m_list->SetItemText(nActual-1,0,m_szA);
		m_list->SetItemState (nActual-1,	LVIS_SELECTED | LVIS_FOCUSED, 
								LVIS_SELECTED | LVIS_FOCUSED);
	}
	m_list->SetFocus();
}

void CGuiListEdit::Down()
{
	int nActual=m_list->GetNextItem(-1,LVNI_SELECTED);
	if (nActual == -1) return;

	if (nActual+1 < m_list->GetItemCount())
	{
		CString m_szA=m_list->GetItemText(nActual,0);
		CString m_sz=m_list->GetItemText(nActual+1,0);
		m_list->SetItemText(nActual,0,m_sz);
		m_list->SetItemText(nActual+1,0,m_szA);
		m_list->SetItemState (nActual+1,	LVIS_SELECTED | LVIS_FOCUSED, 
								LVIS_SELECTED | LVIS_FOCUSED);
	}
	m_list->SetFocus();

}


void CGuiListEdit::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);
	if ( !m_Conta.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,0x9999))
		return ;
	
	m_Conta.AddComponen(&m_MiniTool);
	/*m_toolBtn.Create(_T(""),WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,CRect(0,0,0,0),this,DROPBUTTON);
	m_toolBtn.SetCaption(_T(" ... "));
	m_toolBtn.SetStyleButton(CGuiNormalButton::STL_SEMIFLAT);
	*/
	
	m_list=(CListCtrl*) m_Conta.AddComponen(RUNTIME_CLASS(CListCtrl),LST_LIST,WS_VISIBLE | WS_CHILD);
	m_MiniTool.SetImageList(IDB_GUI_DOCKBAROFFICE,14,12,RGB(255,0,255));
	m_MiniTool.AddButton(9,LST_DOWN,NULL,_T(""),_T("Item Down"));
	m_MiniTool.AddButton(11,LST_UP,NULL,_T(""),_T("Item Up"));
	m_MiniTool.AddButton(8,LST_DELETE,NULL,_T(""),_T("Delete"));
	m_MiniTool.AddButton(10,LST_INSERT,NULL,_T(""),_T("Insert"));
	m_MiniTool.AutoSize(TRUE);
	m_MiniTool.SetBorder(CGuiMiniTool::STYLEPRESS);
	m_MiniTool.SetCaption(_T("Options:"),CGuiMiniTool::ALIGN_LEFT);
	m_MiniTool.AlingButtons(CGuiMiniTool::ALIGN_RIGHT);
	m_MiniTool.SetColorCaption(RGB(0,0,0));
	m_list->ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	m_list->ModifyStyle(0,WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SINGLESEL | 
						LVS_NOCOLUMNHEADER | LVS_EDITLABELS | LVS_SHOWSELALWAYS);
	m_list->SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE , 0, LVS_EX_FULLROWSELECT);

	m_list->InsertColumn(0,_T(""));
	m_Conta.UsedAllWindow(TRUE);
	//m_MiniTool.SetColor(GuiDrawLayer::GetRGBColorXP());
	
	CStatic::PreSubclassWindow();
}


void CGuiListEdit::SetStyle(Border border)
{
	m_border=border;
}
void CGuiListEdit::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
	
	CBrush cbr;
	CRect m_rectDraw;
	GetClientRect(&m_rectDraw);
	cbr.CreateSolidBrush(m_clrface);
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
	m_Conta.MoveWindow(0,0,m_rectDraw.Width(),m_rectDraw.Height());
	m_list->SetColumnWidth (0, m_rectDraw.Width ()-10);
	
}

int CGuiListEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO:  Add your specialized creation code here

	return 0;
}

void CGuiListEdit::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	CWnd* pWnd = GetWindow(GW_CHILD);
        if (pWnd != NULL)
        {
            pWnd->MoveWindow(0, 0, cx, cy);
            ASSERT(pWnd->GetWindow(GW_HWNDNEXT) == NULL);
		}
	//m_Conta.MoveWindow(0,0,cx,cy);
	// TODO: Add your message handler code here
}


CListCtrl* CGuiListEdit::GetListCtrl()
{
	return m_list;
} 