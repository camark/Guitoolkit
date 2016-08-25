#include "stdafx.h"
#include "guibaroffice.h"
#include "resource.h"



CGuiBarOffice::CGuiBarOffice(void)
{
}

CGuiBarOffice::~CGuiBarOffice(void)
{
}

#define ID_DOC 992
#define ID_DOCBLAN 994
#define ID_DOCWEB  995

BEGIN_MESSAGE_MAP(CGuiBarOffice, CGuiOfficeBar)
	//{{AFX_MSG_MAP(CMyBar)
	ON_WM_CREATE()
	ON_COMMAND(ID_DOC,OnOpenDoc)
	ON_COMMAND(ID_DOCBLAN,OnNuevoDoc)
	ON_COMMAND(ID_DOCWEB,OnNuevoWeb)
	//}}AFX_MSG_MAP
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CGuiBarOffice::OnMenu()
{
	AfxMessageBox("Menu");
}

void CGuiBarOffice::OnBack()
{
	m_wndPanel.ShowWindow(SW_HIDE);
	m_ctClassView.ShowWindow(SW_SHOW);
	ShowTitle("Lista de Colecciones");
}

void CGuiBarOffice::OnForWard()
{
	m_ctClassView.ShowWindow(SW_HIDE);
	m_wndPanel.ShowWindow(SW_SHOW);
	ShowTitle("Nuevo Documento");
}

void CGuiBarOffice::OnOpenDoc()
{
	
}
void CGuiBarOffice::OnNuevoDoc()
{
	//GetParentFrame()->SendMessage(ID_FILE_NEW);
}
void CGuiBarOffice::OnNuevoWeb(){}


int CGuiBarOffice::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	
	if (CGuiOfficeBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetSupporMultiView();
	
	
	
	const DWORD dwStyle =WS_CHILD | WS_VISIBLE;
	//m_ArrButtons[0].SetEnabled(FALSE);
	//m_ArrButtons[1].SetEnabled(FALSE);
	//Usted puede tener multiples ventanas hijas
	//y controlarlas con SW_HIDE y SW_SHOW

	if (!m_wndPanel.Create(dwStyle,CRect(0,0,0,0),this,9992))
		return -1;

	if (!m_ctClassView.Create(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,124))
		return -1;
	m_TreeGaleria=(CTreeCtrl* )m_ctClassView.AddComponen(RUNTIME_CLASS(CTreeCtrl),3, TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS );
	m_ctClassView.ShowWindow(SW_HIDE);
	m_wndPanel.SetImageList(IDB_FILEVIEW,16, 0, RGB (255, 0, 0));
	m_wndPanel.Addlabel(991,&m_ArrLabels[0]);
	m_ArrLabels[0].SetCaption("Abrir un nuevo Documento");
	m_wndPanel.AddImageLink(992,0,&m_ArrLinks[0]);	
	m_ArrLinks[0].SetCaption("Documentos...");
	m_wndPanel.Addlabel(993,&m_ArrLabels[1]);
	m_ArrLabels[1].SetCaption("Nuevo");
	m_wndPanel.AddImageLink(ID_FILE_NEW,1,&m_ArrLinks[1]);	
	m_ArrLinks[1].SetCaption("Documento en blanco");
	m_wndPanel.AddImageLink(995,2,&m_ArrLinks[2]);	
	m_ArrLinks[2].SetCaption("Pagina Web en blanco");
	m_wndPanel.AddImageLink(996,0,&m_ArrLinks[3]);	
	m_ArrLinks[3].SetCaption("Mensaje de correo electronico");
	m_wndPanel.Addlabel(997,&m_ArrLabels[2]);
	m_ArrLabels[2].SetCaption("Nuevo a partir de un documento existente");
	m_wndPanel.AddImageLink(998,1,&m_ArrLinks[4]);	
	m_ArrLinks[4].SetCaption("Elegir documento");
	m_wndPanel.AddImageLink(999,-1,&m_ArrLinks[5]);	
	m_ArrLinks[5].SetCaption("Mi nuevo documento 1");
	m_ArrLinks[5].AjustRightText(16);
	m_wndPanel.AddImageLink(998,-1,&m_ArrLinks[6]);	
	m_ArrLinks[6].SetCaption("Mi nuevo documento 2");
	m_ArrLinks[6].AjustRightText(16);
	m_wndPanel.AddImageLink(998,-1,&m_ArrLinks[7]);	
	m_ArrLinks[7].SetCaption("Mi nuevo documento 3");
	m_ArrLinks[7].AjustRightText(16);
	ShowTitle("Nuevo Documento");
	return 0;
}
void CGuiBarOffice::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	UpdateChilds();
	CGuiOfficeBar::OnWindowPosChanged(lpwndpos);
	// TODO: Add your message handler code here
}

void CGuiBarOffice::UpdateChilds()
{
	CRect rc;
	GetClientRect(rc);
	CWnd* pWnd = GetWindow(GW_CHILD);
	while (pWnd != NULL)
    {
        if (pWnd->IsWindowVisible())
		{
			pWnd->MoveWindow(rc);
			break;
		}
            pWnd=pWnd->GetWindow(GW_HWNDNEXT);
	}
}
void CGuiBarOffice::OnSize(UINT nType, int cx, int cy)
{
	
	UpdateChilds();
	CGuiOfficeBar::OnSize(nType, cx, cy);
	//nunca utilice el timer 1 porque es utilizado por la ventana padre
	//para manejar los botones de control
	SetTimer(100,100,NULL);
	// TODO: Add your message handler code here
}

void CGuiBarOffice::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(100);
	UpdateChilds();
	CGuiOfficeBar::OnTimer(nIDEvent);
}
