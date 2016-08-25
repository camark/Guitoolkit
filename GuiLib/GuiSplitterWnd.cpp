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
#include "GuiSplitterWnd.h"
#include "GuiDrawLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// CGuiSplitterWnd
#define BTNHILITE ::GetSysColor(COLOR_3DFACE)
#define BTNSHADOW ::GetSysColor(COLOR_3DSHADOW)
#define BTNHIGH   ::GetSysColor(COLOR_3DHIGHLIGHT)
#define CX_BORDER  1
#define CY_BORDER  1


IMPLEMENT_DYNAMIC(CGuiSplitterWnd, CSplitterWnd)

CGuiSplitterWnd::CGuiSplitterWnd()
{
	m_bBorder=FALSE;
	m_StyleDisplay=GUISTYLE_XP;
}

CGuiSplitterWnd::~CGuiSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CGuiSplitterWnd, CSplitterWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////
// CGuiSplitterWnd message handlers

void CGuiSplitterWnd::OnPaint()
{
	//vil plagio del original

	ASSERT_VALID(this);
	CPaintDC dc(this);

	CRect rectClient;
	GetClientRect(&rectClient);
	rectClient.InflateRect(-m_cxBorder, -m_cyBorder);

	CRect rectInside;
	GetInsideRect(rectInside);

	// draw the splitter boxes
	if (m_bHasVScroll && m_nRows < m_nMaxRows)
	{
		OnDrawSplitter(&dc, splitBox,
			CRect(rectInside.right , rectClient.top,
				rectClient.right, rectClient.top + m_cySplitter));
	}

	if (m_bHasHScroll && m_nCols < m_nMaxCols)
	{
		OnDrawSplitter(&dc, splitBox,
			CRect(rectClient.left, rectInside.bottom,
				rectClient.left + m_cxSplitter, rectClient.bottom));
	}

	// extend split bars to window border (past margins)
	DrawAllSplitBars(&dc, rectInside.right, rectInside.bottom);
}


void CGuiSplitterWnd::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	COLORREF clr = GuiDrawLayer::GetRGBColorFace(m_StyleDisplay);
	if (pDC == NULL)
	{
		RedrawWindow(rect, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}
	ASSERT_VALID(pDC);

	CRect rc = rect;

	switch (nType)
	{
	case splitBorder:
		if (!m_bBorder)
		{
			/*pDC->Draw3dRect(rc, BTNHILITE, BTNHILITE);
			rc.InflateRect(-CX_BORDER, -CY_BORDER);
			pDC->Draw3dRect(rc, BTNSHADOW, BTNHIGH);
			*/
			pDC->Draw3dRect(rc,GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style),GuiDrawLayer::GetRGBColorShadow(GuiDrawLayer::m_Style));
			rc.InflateRect(-CX_BORDER, -CY_BORDER);
			pDC->Draw3dRect(rc, clr, clr);
		}
		else
		{
			CPen cp(PS_SOLID,1,GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
			pDC->Draw3dRect(rc, GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style), GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style));
			rc.InflateRect(-CX_BORDER, -CY_BORDER);
			pDC->Draw3dRect(rc, GuiDrawLayer::GetRGBColorFace(GuiDrawLayer::m_Style), GuiDrawLayer::GetRGBColorBTNHigh());
			CPen* cpOld=pDC->SelectObject(&cp);
			pDC->MoveTo(rc.left,rc.bottom-1);
			pDC->LineTo(rc.right,rc.bottom-1);
			pDC->SelectObject(cpOld);
		}
		return;

	case splitIntersection:
		break;

	case splitBox:
			break;
	case splitBar:
		break;

	default:
		ASSERT(FALSE);  // unknown splitter type
	}

	// fill the middle
	
	pDC->FillSolidRect(rc, clr);
}

void CGuiSplitterWnd::SetBorderFlat(BOOL bBorder)
{
	m_bBorder=bBorder;
}


