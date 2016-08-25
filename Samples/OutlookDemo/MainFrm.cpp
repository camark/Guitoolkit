// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "OutlookDemo.h"
#include "resource.h"
#include "MainFrm.h"
#include "GOut.h"
#include "Cajon.h"
#include "GuiDrawLayer.h"
#include "GuiToolButton.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define IDT_BACK 5555
#define IDT_FORW 5556
#define IDT_GO	 5557 
#define IDT_DEL  5558
#define IDT_UNDO 5559
#define IDT_STANDAR 5560
#define ID_VIEWCAPTION 5000

#define IDO_OUTODAY	   5600
#define IDO_CALENDARIO 5601
#define IDO_CONTACTO   5602
#define IDO_TAREAS     5603
#define IDO_NOTAS	   5604	
#define IDO_ELIMINAR   5605

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(IDT_BACK,OnBack)
	ON_COMMAND(ID_2003, On2003)
	ON_COMMAND(ID_XP, OnXP)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDO_OUTODAY,  OnToday)
	ON_COMMAND(IDO_CALENDARIO, OnCalendario)
	ON_COMMAND(IDO_CONTACTO, OnContacto)
	ON_COMMAND(IDO_TAREAS, OnTareas)
	ON_COMMAND(IDO_NOTAS, OnNotas)
	ON_COMMAND(IDO_ELIMINAR, OnEliminar)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

void CMainFrame::OnBack()
{
	AfxMessageBox("Back");
	
}

void CMainFrame::OnToday()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("OutLook Today");
	pBtn->SetToolTip("OutLook Today");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(0));
	m_guiMiniToolLeft.RecalLayout();
}




void CMainFrame::OnCalendario()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("Calendario");
	pBtn->SetToolTip("Calendario");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(1));
	m_guiMiniToolLeft.RecalLayout();
}


void CMainFrame::OnContacto()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("Contacto");
	pBtn->SetToolTip("Contacto");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(2));
	m_guiMiniToolLeft.RecalLayout();
}

void CMainFrame::OnTareas()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("Tareas");
	pBtn->SetToolTip("Tareas");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(3));
	m_guiMiniToolLeft.RecalLayout();
}

void CMainFrame::OnNotas()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("Notas");
	pBtn->SetToolTip("Notas");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(4));
	m_guiMiniToolLeft.RecalLayout();
}

void CMainFrame::OnEliminar()
{
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetCaption("Eliminar");
	pBtn->SetToolTip("Eliminar");
	pBtn->SethIcon(m_guiMiniToolLeft.GetImagIcon(15));
	m_guiMiniToolLeft.RecalLayout();
}

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	InitMenu(IDR_MAINFRAME);
	InitToolBar(IDR_MAINFRAME);
	InitStatusBar(indicators,sizeof(indicators)/sizeof(UINT));
	EnableDocking(CBRS_ALIGN_ANY);
//	m_wndToolBar.SetTextButton(0,"&New"); 
//	m_wndToolBar.SetTextButton(1,"&Send/Receiver"); 
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);	
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);

	
	DockControlBar(&m_wndMenuBar,m_dockTop);
	DockControlBar(&m_wndToolBar,m_dockTop);
	
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	
	if (!m_CapOutBar.Create (WS_CHILD | WS_VISIBLE , 
			this,ID_VIEWCAPTION))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;
	}

	if (!m_CapOutBar.SetSplitter(&m_MiniSplitter))
		return FALSE;

	m_MiniSplitter.AddMiniToolLeft(&m_guiMiniToolLeft);
	m_MiniSplitter.AddMiniToolRight(&m_guiMiniToolRight);
	m_guiMiniToolLeft.SetImageList(IDB_BITMAP2,16,11,RGB (255, 0, 0));
	m_guiMiniToolRight.SetImageList(IDB_BITMAP2,16,11,RGB (255, 0, 0));
	
	//Left MiniTool 
	m_guiMiniToolLeft.AddButton(11,IDT_BACK,NULL,"Back ","Back");
	m_guiMiniToolLeft.AddButton(12,IDT_FORW,NULL,"Forward","Forward");
	m_guiMiniToolLeft.AddButton(0,IDT_STANDAR,NULL,"OutLook Today","OutLook Today");
	CGuiToolButton* pBtn=m_guiMiniToolLeft.GetButton(IDT_STANDAR);
	pBtn->SetFontColor(RGB(0,0,0));

	//Right MiniTool
	m_guiMiniToolRight.CreateCombo(&m_cb,333,100);
	m_guiMiniToolRight.AddButton(13,IDT_GO,NULL,"Go  ","Go  ");
	m_guiMiniToolRight.AddButton(15,IDT_UNDO,NULL,"Undo  ","Undo  ");
	//m_MiniSplitter.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style),GuiDrawLayer::GetRGBColorBTNHigh());
	m_guiMiniToolRight.SetCaption("&Direccion:",CGuiMiniTool::ALIGN_LEFT);
	m_guiMiniToolRight.SetColorCaption(GuiDrawLayer::GetRGBColorBTNHigh());
	m_guiMiniToolRight.AutoSize(TRUE);
	
	m_cb.AddString("outlook:Tareas");
	m_cb.AddString("outlook:Notas");
	m_cb.AddString("Toolbar Combobox item four");
	m_cb.AddString("Toolbar Combobox item five");
	m_cb.AddString("Toolbar Combobox item six");
	
	m_guiMiniToolLeft.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	m_guiMiniToolRight.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	m_cb.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	
//	On2003();
	sProfile = _T("DevOutLook");
	//LoadBars();
	//active las las siguientes lineas para ver la etiqueta a la derecha
	//m_guiMiniToolLeft.SetCaption("Fecha del dia de hoy",CGuiMiniTool::ALIGN_RIGHT);
	//m_guiMiniToolLeft.SetColorCaption(GuiDrawLayer::GetRGBColorBTNHigh());
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}
	
	// Outlook bar view.
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CGOut),
		CSize(150, 0), pContext))
	{
		TRACE0("Failed to create CGOut\n"); 
		return FALSE;
	}	
	if (!m_wndSplitter.CreateView(0,1, RUNTIME_CLASS(CCajon),
		CSize(90, 0), pContext))
	{
		TRACE0("Failed to create CGOut\n"); 
		return FALSE;
	}	

	return TRUE; //CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnSysColorChange() 
{
	CFrameWnd::OnSysColorChange();
	GuiDrawLayer::IsThemeXP();
	m_MiniSplitter.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style),GuiDrawLayer::GetRGBColorBTNHigh());	
	m_guiMiniToolLeft.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
	m_guiMiniToolRight.SetColor(GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
}

void CMainFrame::OnEditCut()
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::On2003()
{
	GuiDrawLayer::m_Style=GUISTYLE_2003;
	StyleDispl(GUISTYLE_2003);
	m_guiMiniToolLeft.StyleDispl(GUISTYLE_2003);
	m_guiMiniToolRight.StyleDispl(GUISTYLE_2003);
	m_CapOutBar.StyleDispl(GUISTYLE_2003);
	m_wndSplitter.StyleDispl(GUISTYLE_2003);
	CGOut* pWnd =(CGOut*)m_wndSplitter.GetPane(0, 0);
	pWnd->out.StyleDispl(GUISTYLE_2003);
	pWnd->cf.StyleDispl(GUISTYLE_2003);
	
}

void CMainFrame::OnXP()
{
	GuiDrawLayer::m_Style=GUISTYLE_XP;
	StyleDispl(GUISTYLE_XP);
	m_guiMiniToolLeft.StyleDispl(GUISTYLE_XP);
	m_guiMiniToolRight.StyleDispl(GUISTYLE_XP);
	m_CapOutBar.StyleDispl(GUISTYLE_XP);
	m_wndSplitter.StyleDispl(GUISTYLE_XP);
	CGOut* pWnd =(CGOut*)m_wndSplitter.GetPane(0, 0);
	pWnd->out.StyleDispl(GUISTYLE_XP);
	pWnd->cf.StyleDispl(GUISTYLE_XP);
}


