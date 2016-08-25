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
#include "GuiDocSpecial.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#define _AfxSetDlgCtrlID(hWnd, nID)     SetWindowLong(hWnd, GWL_ID, nID)
#define _AfxGetDlgCtrlID(hWnd)          ((UINT)(WORD)::GetDlgCtrlID(hWnd))

BEGIN_MESSAGE_MAP(CGuiDocSpecial,CDockBar)
 //{{AFX_MSG_MAP(CGuiDocSpecial)
 ON_WM_SIZE()
 ON_WM_CREATE()
 //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGuiDocSpecial::CGuiDocSpecial()
{
}

CGuiDocSpecial::~CGuiDocSpecial()
{
}

CSize CGuiDocSpecial::CalcDynamicLayout(int nLength,DWORD nMode)
{
	CSize sz=CControlBar::CalcDynamicLayout(nLength,nMode);
//	sz.cx+=1;
//	sz.cy+=1;
	return sz;
}

int CGuiDocSpecial::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CGuiDocSpecial::OnNcPaint()
{
	CRect rcWindow;
	CRect rcClient;
	int m_iBorder=2; 
	CWindowDC	dc(this);
	GetWindowRect(&rcWindow);
	GetClientRect(&rcClient);
	CBrush cbr;
	cbr.CreateSysColorBrush(GuiDrawLayer::GetRGBColorTabs());
	rcClient.OffsetRect(-rcWindow.TopLeft());
    rcWindow.OffsetRect(-rcWindow.TopLeft());
    ScreenToClient(rcWindow);
	rcClient.OffsetRect(-rcWindow.left,-rcWindow.top);
	dc.ExcludeClipRect(rcClient);   
	rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);
	int ibotton=rcWindow.bottom;
	rcWindow.top=rcWindow.bottom-m_iBorder;
	dc.FillRect(rcWindow,&cbr); 
	rcWindow.top=0;
	rcWindow.bottom+=3;
	dc.FillRect(rcWindow,&cbr); 
	//un truco primitivo que evita el efecto estar a un nivel encima de la otra barra
	dc.FillSolidRect(0,rcWindow.top,rcWindow.right+1,1,::GetSysColor(COLOR_BTNSHADOW)); 
	dc.FillSolidRect(0,rcWindow.top+1,rcWindow.right+1,1,::GetSysColor(COLOR_BTNHIGHLIGHT)); 

}


void CGuiDocSpecial::OnSize(UINT nType,int cx,int cy)
{
	CDockBar::OnSize(nType,cx,cy);
	Invalidate();
}


/*
void CGuiDocSpecial::RecalTabs()
{
	int inumTabs=GetDockedCount();
	if (inumTabs > 1)
	{

		for (int i=0; i< inumTabs; i++)
		{
			//GetNumWnd(int m_numtab)
			CString m_caption;
			CWnd* pParent=(CWnd*)m_arrBars[i];
			ASSERT(pParent);
			int j=0;
			BOOL bFound=FALSE;
			while(j< m_tabwnd.GetCount())
			{
				if (m_tabwnd.GetNumWnd(j) == pParent)
				{
					bFound=TRUE;
					break;
				}
				j++;
			}
			if (bFound == FALSE)
			{
				pParent->GetWindowText(m_caption);
				m_tabwnd.Addtab(pParent,m_caption,i);		
			}
		}
	}

}


*/