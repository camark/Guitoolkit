// GuiToolBar.cpp: implementation of the GuiToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OutlookDemo.h"
#include "GuiToolBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(GuiToolBar, CControlBar)
	//{{AFX_MSG_MAP(GuiToolBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
    ON_WM_PAINT()
    ON_WM_NCPAINT()
    ON_WM_NCCALCSIZE()
    ON_WM_WINDOWPOSCHANGING()
    ON_WM_CAPTURECHANGED()
    ON_WM_SETTINGCHANGE()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_RBUTTONDOWN()
    ON_WM_NCMOUSEMOVE()
    ON_WM_NCHITTEST()
    ON_WM_CLOSE()
    ON_WM_SIZE()
  
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


GuiToolBar::GuiToolBar()
{
	m_iBorder=4;
	cb.CreateSysColorBrush(COLOR_BTNFACE);
}

GuiToolBar::~GuiToolBar()
{

}

BOOL GuiToolBar::Create (CWnd* pParentWnd,CString m_szTitle, UINT uID,DWORD dwStyle)
{
	ASSERT_VALID(pParentWnd);
	//	return FALSE;
	
	CString m_szClassName=::AfxRegisterWndClass(CS_DBLCLKS,LoadCursor(NULL,IDC_ARROW),cb);

	if (!CWnd::Create(m_szClassName,m_szTitle,dwStyle,CRect(0,0,0,0),pParentWnd,uID))
		return FALSE;

	return TRUE;

}

void GuiToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	//in this moment nothing to do
}

CSize GuiToolBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	//incialmente esta barra no flotara lo que nos obliga
	//a ignorar los parametros de la función
	CRect rcWindow;
	//necesitamos hallar el ancho de la ventana, por que el Alto
	//le indicamos al sistema que lo tome total
	m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT)->GetWindowRect(&rcWindow);
	return CSize(rcWindow.Width(),32767);
	
}
int GuiToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CControlBar::OnCreate(lpCreateStruct)==-1)
		return -1;
	return 0;
}

void GuiToolBar::OnNcPaint()
{
	CRect rcWindow;
	CWindowDC	dc(this);
	EraseNonClient();	
	GetWindowRect(&rcWindow);
	dc.FillSolidRect(rcWindow.right,rcWindow.top,rcWindow.right+1,rcWindow.bottom,::GetSysColor(COLOR_BTNSHADOW)); 

}

void GuiToolBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	//esta función si es muy importante, porque le daremos
	//el tamaño del area cliente
	lpncsp->rgrc[0].top+=m_iBorder;
	lpncsp->rgrc[0].bottom-=m_iBorder;
	lpncsp->rgrc[0].left+=m_iBorder;
	lpncsp->rgrc[0].right-=m_iBorder;
	GetWindowRect(&mrcBorder);
	mrcBorder.left=mrcBorder.right-m_iBorder;

}

UINT GuiToolBar::OnNcHitTest(CPoint point)
{
	CRect m_rcWindow;
	GetWindowRect(&m_rcWindow);
	point.Offset(-m_rcWindow.left,-m_rcWindow.top);
	if (m_rcWindow.PtInRect(point))
		return HTSIZE;
    else
        return CControlBar::OnNcHitTest(point);
}


void GuiToolBar::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
/*	if (nHitTest == HTSIZE)
	{
		//CPoint  cp;
		//GetCursorPos(&cp);
		//if (mrcBorder.PtInRect(point))
		//	; //permita redimensionar la ventana
	}
	else
		CControlBar::OnNcLButtonDown(UINT nHitTest, CPoint point);*/
}


void GuiToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	//m_pDockSite->RecalcLayout();
}




