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
#include "GuiDrawLayer.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning( disable : 4244 )

DWORD GuiDrawLayer::m_SO=-1;
BOOL  GuiDrawLayer::m_Theme=FALSE;
DWORD GuiDrawLayer::m_Style=GUISTYLE_XP;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(GuiTabbedButton, CGuiToolButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SYSCOLORCHANGE()
END_MESSAGE_MAP()

void GuiTabbedButton::OnSysColorChange( )
{
	CGuiToolButton::OnSysColorChange( );
}

GuiTabbedButton::GuiTabbedButton()
{
	bPress=FALSE;
	m_iMilliseconds=50;

}

GuiTabbedButton::~GuiTabbedButton()
{

}


void GuiTabbedButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CGuiToolButton::OnLButtonUp(nFlags, point);
	if (!bPress) return;
	bPress=FALSE;
	KillTimer(1001);
	
	
}
void GuiTabbedButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CGuiToolButton::OnLButtonDown(nFlags, point);
	if (bPress) return;
	bPress=TRUE;
	SetTimer(1001,m_iMilliseconds,NULL);
	
	
}

void GuiTabbedButton::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CGuiToolButton::OnTimer(nIDEvent);
	if (bPress == FALSE) return;
	CRect rc;
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	GetClientRect(rc);
	if (rc.PtInRect(pt))
	{
		CWnd* pParent=GetParent();
		if (IsWindowEnabled())
			pParent->SendMessage(WM_COMMAND,GetDlgCtrlID());
		//bPress=FALSE;
		//KillTimer(1);
	}
	else
	{
		bPress=FALSE;
		KillTimer(1001);
		CGuiToolButton::OnTimer(nIDEvent);
	}
	
}

//------------------------------------------------------------------------------






COLORREF GuiDrawLayer::DarkenColor( long lScale, COLORREF lColor)
{ 
  long R = MulDiv(GetRValue(lColor),(255-lScale),255);
  long G = MulDiv(GetGValue(lColor),(255-lScale),255);
  long B = MulDiv(GetBValue(lColor),(255-lScale),255);

  return RGB(R, G, B); 
}

GuiDrawLayer::GuiDrawLayer()
{
	if (!m_img.Create(IDB_DOCKBAR,9,10,RGB(255,0,255)))
	{
		TRACE0("error");
	}
	m_iWidthDrowDown=GetSystemMetrics(SM_CXHTHUMB);
	CBitmap cbmp;
	BITMAP bmp;
	cbmp.LoadBitmap(IDB_GUI_DOCKBAR);
	cbmp.GetBitmap(&bmp);
	mHeight=CPoint(bmp.bmWidth,bmp.bmHeight);	
	

}

COLORREF GuiDrawLayer::GetRGBColorWhite()
{
	return RGB(255,255,255);
}

COLORREF GuiDrawLayer::GetRGBColorTabs()
{
	BYTE byRvalue =GetRValue(GetRGBColorXP());
	BYTE byGvalue =GetGValue(GetRGBColorXP());
	BYTE byBvalue =GetBValue(GetRGBColorXP());
//	byRvalue =byRvalue>>2;
//	byGvalue =byGvalue>>2;
//	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.51);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	
}

/*BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
	byRvalue =byRvalue>>2;
	byGvalue =byGvalue>>2;
	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.14);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
*/

COLORREF GuiDrawLayer::GetRGBSkinMenu()
{
	BYTE byRvalue =GetRValue(GuiDrawLayer::GetRGBColorFace());
	BYTE byGvalue =GetGValue(GuiDrawLayer::GetRGBColorFace());
	BYTE byBvalue =GetBValue(GuiDrawLayer::GetRGBColorFace());
	byRvalue =byRvalue>>2;
	byGvalue =byGvalue>>2;
	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.018);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	
}

COLORREF GuiDrawLayer::GetRGBColorBTNHigh()
{
	return ::GetSysColor(COLOR_BTNHIGHLIGHT);
}



COLORREF GuiDrawLayer::GetRGBColorGrayText()
{
	BYTE byRvalue =0;
	BYTE byGvalue =0;
	BYTE byBvalue =0;
	byRvalue =byRvalue>>1;
	byGvalue =byGvalue>>1;
	byBvalue =byBvalue>>1;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.60);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	
}


COLORREF GuiDrawLayer::GetRGBColorFace(DWORD dwStyle)
{
	if (GuiDrawLayer::m_Theme && dwStyle!=GUISTYLE_XP)
	{
		
		HDC hdc=GetDC(NULL);
		COLORREF clrNear=GetNearestColor(hdc,GuiDrawLayer::GetRGBCaptionXP());
		ReleaseDC(NULL,hdc);
		if (clrNear==13595707)
			return RGB(173,201,243);
		else if(clrNear==8039069)
			return RGB(220,222,185);
		else if(clrNear==13221564)
			return RGB(231,227,241);

	}
	return ::GetSysColor(COLOR_BTNFACE);
	
}

COLORREF GuiDrawLayer::GetRGBColorShadow(DWORD  IsTh2003)
{
	HDC hdc=GetDC(NULL);
	COLORREF clrNear=GetNearestColor(hdc,GuiDrawLayer::GetRGBCaptionXP());
	ReleaseDC(NULL,hdc);

	if (IsTh2003== GUISTYLE_2003)
		return GuiDrawLayer::m_Theme && clrNear != 13221564 ? GuiDrawLayer::GetRGBCaptionXP() : clrNear == 13221564 ? RGB(124,120,141): ::GetSysColor(COLOR_BTNSHADOW);
	return  ::GetSysColor(COLOR_BTNSHADOW);
}

COLORREF GuiDrawLayer::GetRGBPressBXP()
{
	COLORREF clrPress = ::GetSysColor (COLOR_HIGHLIGHT);

	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
	byRvalue =byRvalue>>2;
	byGvalue =byGvalue>>2;
	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.21);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	
}

COLORREF GuiDrawLayer::GetRGBMenu()
{
	COLORREF clrPress = ::GetSysColor (COLOR_BTNSHADOW);

	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
	byRvalue =byRvalue>>3;
	byGvalue =byGvalue>>3;
	byBvalue =byBvalue>>3;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.47);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	
}

COLORREF GuiDrawLayer::GetRGBTitleMenu()
{
	COLORREF clrPress = ::GetSysColor (COLOR_BTNSHADOW);

	BYTE byRvalue =GetRValue(::GetSysColor(clrPress));
	BYTE byGvalue =GetGValue(::GetSysColor(clrPress));
	BYTE byBvalue =GetBValue(::GetSysColor(clrPress));
	byRvalue =byRvalue>>2;
	byGvalue =byGvalue>>2;
	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.8);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	
}

COLORREF GuiDrawLayer::GetRGBCaptionXP()
{

	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
	return RGB(byRvalue+10,byGvalue+10,byBvalue+10);	
}

COLORREF GuiDrawLayer::GetRGBFondoXP()
{
	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
	byRvalue =byRvalue>>2;
	byGvalue =byGvalue>>2;
	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.14);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
}

BOOL GuiDrawLayer::IsGrayed()
{
	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_3DFACE));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_3DFACE));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_3DFACE));
	if ((byRvalue ==byGvalue) && (byGvalue == byBvalue) &&
		 (byBvalue > 190 && byBvalue < 193) || (byBvalue == 216))
		return TRUE;
	else
		return FALSE;
}

COLORREF GuiDrawLayer::GetRGBColorXP()
{

	
	COLORREF clr3DFace = ::GetSysColor (COLOR_3DFACE);
	return RGB (((3*GetRValue (clr3DFace)+240)/4)+1,
				((3*GetGValue (clr3DFace)+240)/4)+1,
				((3*GetBValue (clr3DFace)+240)/4)+1);

}

GuiDrawLayer::~GuiDrawLayer()
{

}

HICON GuiDrawLayer::LoadIconLib(UINT uIcon)
{
	HINSTANCE hIrs = AfxFindResourceHandle(MAKEINTRESOURCE(uIcon),
											RT_GROUP_ICON);
	return (HICON)::LoadImage(hIrs, MAKEINTRESOURCE(uIcon), IMAGE_ICON,16, 16, 0);
}

void GuiDrawLayer::DrawArrow(CDC* pDC,CRect m_rc,BOOL m_bDown)
{
	int difh =m_rc.Height()-mHeight.y;
	difh/=2;
	m_rc.left=m_rc.right-m_iWidthDrowDown;
	m_img.Draw(pDC,m_bDown?0:2,CPoint(m_rc.left+2,m_rc.top+difh),ILD_TRANSPARENT);		

}

void GuiDrawLayer::DrawCheck(CDC* pDC,CRect m_rcTemp)
{
	int iMediaAltura=(m_rcTemp.Height()/2)-2;
	int iMedioBox= m_rcTemp.Width()/2;
	CPen cp(PS_SOLID,1,GuiDrawLayer::GetRGBCaptionXP());
	CPen *pOld=pDC->SelectObject(&cp);
	pDC->MoveTo(m_rcTemp.left+1,m_rcTemp.top+iMediaAltura+3);
	pDC->LineTo(m_rcTemp.left+3,m_rcTemp.bottom-2);
	pDC->MoveTo(m_rcTemp.left+3,m_rcTemp.bottom-2);
	pDC->LineTo(m_rcTemp.right-1,m_rcTemp.top+2);
				
	pDC->MoveTo(m_rcTemp.left+1,m_rcTemp.top+iMediaAltura+2);
	pDC->LineTo(m_rcTemp.left+3,m_rcTemp.bottom-3);
	pDC->MoveTo(m_rcTemp.left+3,m_rcTemp.bottom-3);
	pDC->LineTo(m_rcTemp.right-1,m_rcTemp.top+1);

	pDC->MoveTo(m_rcTemp.left+1,m_rcTemp.top+iMediaAltura+1);
	pDC->LineTo(m_rcTemp.left+3,m_rcTemp.bottom-4);
	pDC->MoveTo(m_rcTemp.left+3,m_rcTemp.bottom-4);
	pDC->LineTo(m_rcTemp.right-1,m_rcTemp.top);
	pDC->SelectObject(pOld);
}

HICON GuiDrawLayer::GetIcon(int nIcon)
{
	return m_img.ExtractIcon(nIcon);
}

//function of Bruno Podetti

void GuiDrawLayer::DrawShade( CRect Rect,CPoint screen,CDC* pDC)
{ 
//  if(!SystemParametersInfo(SPI_GETDROPSHADOW,0,&bEnabled,0))
  //  return;

  // Get the size of the menu... 
  
  long winW = Rect.Width(); 
  long winH = Rect.Height(); 
  long xOrg = screen.x;  
  long yOrg = screen.y;

  // Get the desktop hDC... 
  HDC hDcDsk = GetWindowDC(0) ;
  
  int X,Y;
  // Simulate a shadow on right edge... 
  for (X=1; X<=2 ;X++)
  { 
    for (Y=0; Y<2 ;Y++)
    {
      SetPixel(pDC->m_hDC,winW-X,Y, GetPixel(hDcDsk,xOrg+winW-X,yOrg+Y) );
    }
    for (Y=4; Y<8 ;Y++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
      SetPixel(pDC->m_hDC,winW-X,Y,DarkenColor(3 * X * (Y - 3), c)) ;
    }
    for (Y=8; Y<=(winH-5) ;Y++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
      SetPixel(pDC->m_hDC, winW - X, Y, DarkenColor(15 * X, c) );
    }
    for (Y=(winH-4); Y<=(winH-1) ;Y++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
      SetPixel( pDC->m_hDC, winW - X, Y, DarkenColor(3 * X * -(Y - winH), c)) ;
    }
  } 

  // Simulate a shadow on the bottom edge... 
  for(Y=1; Y<=2 ;Y++)
  {
    for(X=0; X<=2 ;X++)
    {
      SetPixel(pDC->m_hDC,X,winH-Y, GetPixel(hDcDsk,xOrg+X,yOrg+winH-Y)) ;
    }
    for(X=4; X<=7 ;X++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y) ;
      SetPixel(pDC->m_hDC, X, winH - Y, DarkenColor(3 * (X - 3) * Y, c)) ;
    }
    for(X=8; X<=(winW-5) ;X++)
    {
      COLORREF  c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y); 
      SetPixel(pDC->m_hDC, X, winH - Y, DarkenColor(15 * Y, c)) ;
    }
  }   
  // Release the desktop hDC... 
  ReleaseDC(0,hDcDsk);
}



CGuiControlBarButton::CGuiControlBarButton()
{
	bTypeButton=GUINORMAL;
	m_bEnabled=TRUE;
}


CGuiControlBarButton::~CGuiControlBarButton()
{

}

void CGuiControlBarButton::SetTypeButton(GuiType bTypeb)
{
	bTypeButton=bTypeb;
}


void CGuiControlBarButton::SetEnabled(BOOL bEnabled)
{
	m_bEnabled=bEnabled;
}

void CGuiControlBarButton::Paint(CDC* pDC,int st,CRect rc,COLORREF clrFondo,BOOL isBackDark)
{
	CBrush cb;
	if (clrFondo==NULL_BRUSH)
		cb.CreateStockObject(NULL_BRUSH);
	else if(bTypeButton==GUINORMAL) 
		cb.CreateSolidBrush(clrFondo);
	else
	{
		if (m_bEnabled)
			if (st == OVERBTN)
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBFondoXP());
			else if(st == PRESSBTN)
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBPressBXP());
			else
				cb.CreateSolidBrush(clrFondo);
	}

	if (m_bEnabled)
	{
		pDC->FillRect(rc,&cb);
		if (st == OVERBTN)
			pDC->Draw3dRect(rc,bTypeButton==GUINORMAL?::GetSysColor(COLOR_BTNHIGHLIGHT):GuiDrawLayer::GetRGBCaptionXP(),
							   bTypeButton==GUINORMAL?::GetSysColor(COLOR_BTNSHADOW):GuiDrawLayer::GetRGBCaptionXP());
		if (st == PRESSBTN)
			pDC->Draw3dRect(rc,bTypeButton==GUINORMAL?::GetSysColor(COLOR_BTNSHADOW):GuiDrawLayer::GetRGBCaptionXP(),
			bTypeButton==GUINORMAL?::GetSysColor(COLOR_BTNHIGHLIGHT):GuiDrawLayer::GetRGBCaptionXP());
	}
	if(bTypeButton==GUINORMAL) 
		m_imgList.Draw(pDC,isBackDark? m_nIcon+1:m_nIcon, 
						CPoint(rc.left+1,rc.top+2), ILD_TRANSPARENT);				
	else
	{
		HICON m_Icon=m_imgList.ExtractIcon(!isBackDark?m_nIcon:m_nIcon+1);
		//if (m_bEnabled)
		IMAGEINFO* pImageInfo = new IMAGEINFO;
		m_imgList.GetImageInfo(m_nIcon,pImageInfo);
		CRect rcbt=pImageInfo->rcImage;
		int difh= rc.Height()-rcbt.Height();
		int difw= rc.Width()-rcbt.Width();
		if (difh< 0) difh=0;
		if (difw< 0) difw=1;
		difh/=2;
		difw/=2;
		m_imgList.Draw(pDC,m_nIcon, CPoint(rc.left+1+difw,bTypeButton==GUINORMAL?rc.top+difh+1:rc.top+difh+1),m_bEnabled?ILD_TRANSPARENT:ILD_BLEND25);				
		delete pImageInfo;
		DestroyIcon (m_Icon);

	}
	cb.DeleteObject();
}

void CGuiControlBarButton::SetData(int nIcon,LPCTSTR lpMsg)
{
	m_nIcon=nIcon;
	m_lpMsg=lpMsg;
}

void  CGuiControlBarButton::SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	CBitmap cbmp;
	BITMAP bmp;
	m_imgList.Create(nBitmapID,cx,nGrow,crMask);
	cbmp.LoadBitmap(nBitmapID);
	cbmp.GetBitmap(&bmp);
	m_imgList.Add(&cbmp,crMask);

}


//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
CGradient::CGradient(CSize Size)
{
	m_Size=Size;
	m_dcMem=NULL;
}

CGradient::~CGradient()
{
	if(m_dcMem!=NULL)
		delete m_dcMem;
}
CSize CGradient::GetDimensions()
{
	return m_Size;
}

void  CGradient::SetDimensions(CSize Size)
{
	m_Size=Size;
}

void CGradient::PrepareVertical(CDC* pDC,DWORD m_StyleDisplay,COLORREF m_clr, int nRate)
{
	BYTE byRvalue =GetRValue(m_clr);//+(nRate==30 ?10:(15));
	BYTE byGvalue =GetGValue(m_clr);//+(nRate==30 ?10:(15));
	BYTE byBvalue =GetBValue(m_clr);//+(nRate==30 ?10:(15));
	if (GuiDrawLayer::m_Theme && m_StyleDisplay!= GUISTYLE_XP )
	{
		COLORREF clrNear=pDC->GetNearestColor(GuiDrawLayer::GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareVertical(pDC,222,234,253,141,178,223);
		else if(clrNear==8039069)
			PrepareVertical(pDC,243,251,221,179,194,138);
		else if(clrNear==13221564)
			PrepareVertical(pDC,248,248,250,165,160,184);
	}
	else
		PrepareVertical(pDC,250,250,249,byRvalue-30,byGvalue-30,byBvalue-30);
}

void CGradient::PrepareCaption(CDC* pDC,DWORD m_StyleDisplay)
{
	BYTE byRvalue ;
	BYTE byGvalue ;
	BYTE byBvalue ;
	
	if (GuiDrawLayer::m_Theme && m_StyleDisplay!= GUISTYLE_XP)
	{
		PrepareVertical(pDC,248,248,205,249,200,102);
		return;
	}
	else if (m_StyleDisplay == GUISTYLE_2003)
	{
		byRvalue =GetRValue(GuiDrawLayer::GetRGBPressBXP());
		byGvalue =GetGValue(GuiDrawLayer::GetRGBPressBXP());
		byBvalue =GetBValue(GuiDrawLayer::GetRGBPressBXP());
	}
	else
	{
		byRvalue =GetRValue(GuiDrawLayer::GetRGBColorShadow());
		byGvalue =GetGValue(GuiDrawLayer::GetRGBColorShadow());
		byBvalue =GetBValue(GuiDrawLayer::GetRGBColorShadow());
	}
	PrepareVertical(pDC,byRvalue,byGvalue,byBvalue,byRvalue-30,byGvalue-30,byBvalue-30);
}

void CGradient::PrepareCaptionVert(CDC* pDC,DWORD m_StyleDisplay)
{
	BYTE byRvalue ;
	BYTE byGvalue ;
	BYTE byBvalue ;
	
	if (GuiDrawLayer::m_Theme && m_StyleDisplay!= GUISTYLE_XP)
	{
		PrepareHorizontal(pDC,249,200,102,248,248,205);
		return;
	}
	else if (m_StyleDisplay == GUISTYLE_2003)
	{
		byRvalue =GetRValue(GuiDrawLayer::GetRGBPressBXP());
		byGvalue =GetGValue(GuiDrawLayer::GetRGBPressBXP());
		byBvalue =GetBValue(GuiDrawLayer::GetRGBPressBXP());
	}
	else
	{
		byRvalue =GetRValue(GuiDrawLayer::GetRGBColorShadow());
		byGvalue =GetGValue(GuiDrawLayer::GetRGBColorShadow());
		byBvalue =GetBValue(GuiDrawLayer::GetRGBColorShadow());
	}
	PrepareHorizontal(pDC,byRvalue,byGvalue,byBvalue,byRvalue-30,byGvalue-30,byBvalue-30);
}

void CGradient::PrepareTabs(CDC* pDC, COLORREF m_clrL,COLORREF m_clrH)
{

	BYTE byRvalueL =GetRValue(m_clrL);
	BYTE byGvalueL =GetGValue(m_clrL);
	BYTE byBvalueL =GetBValue(m_clrL);

	BYTE byRvalueH =GetRValue(m_clrH);
	BYTE byGvalueH =GetGValue(m_clrH);
	BYTE byBvalueH =GetBValue(m_clrH);
	PrepareVertical(pDC,byRvalueL,byGvalueL,byBvalueL,byRvalueH,byGvalueH,byBvalueH);
}

void CGradient::PrepareReverseVert(CDC* pDC,DWORD m_StyleDisplay,COLORREF m_clr)
{

	BYTE byRvalue =GetRValue(m_clr)+10;
	BYTE byGvalue =GetGValue(m_clr)+10;
	BYTE byBvalue =GetBValue(m_clr)+10;
	if (GuiDrawLayer::m_Theme && m_StyleDisplay!= GUISTYLE_XP)
	{
		COLORREF clrNear=pDC->GetNearestColor(GuiDrawLayer::GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareVertical(pDC,141,178,223,222,234,253);
		else if(clrNear==8039069)
			PrepareVertical(pDC,179,194,138,243,251,221);
		else if(clrNear==13221564)
			PrepareVertical(pDC,165,160,184,248,248,250);
	}
	else
	PrepareVertical(pDC,byRvalue-30,byGvalue-30,byBvalue-30,byRvalue,byGvalue,byBvalue);
}


void CGradient::PrepareReverseVertTab(CDC* pDC,DWORD m_StyleDisplay,COLORREF m_clr)
{

	BYTE byRvalue =GetRValue(m_clr)+10;
	BYTE byGvalue =GetGValue(m_clr)+10;
	BYTE byBvalue =GetBValue(m_clr)+10;
	if (GuiDrawLayer::m_Theme && m_StyleDisplay!= GUISTYLE_XP)
	{
		COLORREF clrNear=pDC->GetNearestColor(GuiDrawLayer::GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareVertical(pDC,216,228,243,255,255,255);
		else if(clrNear==8039069)
			PrepareVertical(pDC,233,237,220,255,255,255);
		else if(clrNear==13221564)
			PrepareVertical(pDC,234,233,239,255,255,255);
	}
	else
	PrepareVertical(pDC,byRvalue-30,byGvalue-30,byBvalue-30,byRvalue,byGvalue,byBvalue);
}

void CGradient::PrepareReverseColorTab(CDC* pDC,DWORD m_StyleDisplay, COLORREF m_clrL, COLORREF m_clrH)
{

	BYTE byRvalueL =GetRValue(m_clrL);
	BYTE byGvalueL =GetGValue(m_clrL);
	BYTE byBvalueL =GetBValue(m_clrL);

	BYTE byRvalueH =GetRValue(m_clrH);
	BYTE byGvalueH =GetGValue(m_clrH);
	BYTE byBvalueH =GetBValue(m_clrH);

	PrepareVertical(pDC,byRvalueL,byGvalueL,byBvalueL,byRvalueH,byGvalueH,byBvalueH);
}
	

void CGradient::PrepareReverseHor(CDC* pDC,DWORD m_StyleDisplay,COLORREF m_clr)
{
	BYTE byRvalue =GetRValue(m_clr)+10;
	BYTE byGvalue =GetGValue(m_clr)+10;
	BYTE byBvalue =GetBValue(m_clr)+10;
	if (GuiDrawLayer::m_Theme && m_StyleDisplay!= GUISTYLE_XP)
	{
		COLORREF clrNear=pDC->GetNearestColor(GuiDrawLayer::GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareHorizontal(pDC,222,234,253,141,178,223);
		else if(clrNear==8039069)
			PrepareHorizontal(pDC,243,251,221,179,194,138);
		else if(clrNear==13221564)
			PrepareHorizontal(pDC,248,248,250,165,160,184);
	}
	else
		PrepareHorizontal(pDC,byRvalue,byGvalue,byBvalue,byRvalue-30,byGvalue-30,byBvalue-30);
	
}
void CGradient::PrepareHorizontal(CDC* pDC,DWORD m_StyleDisplay,COLORREF m_clr)
{
	BYTE byRvalue =GetRValue(m_clr)+10;
	BYTE byGvalue =GetGValue(m_clr)+10;
	BYTE byBvalue =GetBValue(m_clr)+10;
	if (GuiDrawLayer::m_Theme && m_StyleDisplay!= GUISTYLE_XP)
	{
		COLORREF clrNear=pDC->GetNearestColor(GuiDrawLayer::GetRGBCaptionXP());
		if (clrNear==13595707)
			PrepareHorizontal(pDC,141,178,223,222,234,253);
		else if(clrNear==8039069)
			PrepareHorizontal(pDC,179,194,138,243,251,221);
		else if(clrNear==13221564)
			PrepareHorizontal(pDC,165,160,184,248,248,250);
	}
	else
		PrepareHorizontal(pDC,byRvalue-30,byGvalue-30,byBvalue-30,byRvalue,byGvalue,byBvalue);
}
void CGradient::PrepareVertical(CDC *pDC,UINT RTop,UINT GTop,UINT BTop,UINT RBot,UINT GBot,UINT BBot)
{
	//Here we will create a memory bitmap and draw the colored bitmap on it
	//using my pretty Algorithm for generating colors.

	//if we have already a drawn DC then delete it so we will not have a
	//memory leak

	if(m_dcMem!=NULL)
	{
		delete m_dcMem;
		
	}

	//create the Memory Bitmap
	CBitmap Bitmap;
	m_dcMem=new CDC;	//new Device Context
	m_dcMem->CreateCompatibleDC(pDC);	//Make it Compatible with pDC
	m_dcMem->SetMapMode(MM_TEXT);		//Pixels Mapping Mode
	//Make the Bitmap compatible with the memory DC
	Bitmap.CreateCompatibleBitmap(pDC,m_Size.cx,m_Size.cy);	
	//Select the bitmap into the memory DC
	m_dcMem->SelectObject(&Bitmap);
	////////////////////////////////////////////////////////////////
	////Drawing The Gradient in a MemDC
	////////////////////////////////////////////////////////////////
	//ALGORITHM:
	//We will have the RGB values of the color at which we will start
	//and the RGB values of the color at which we will end
	//we will fill 256 rectangles using all colors that lie between
	//these two colors. this is done by moving the R,G, and B values slowly
	//from the Starting color to the Ending Color.
	//For example: if we have RTop=100 and RBot=150 then we will draw 256
	//rectangles colored with the R-values of 100,100+(150-100)/256,
	//100+2*(150-100)/256,100+3*(150-100)/256,...
	//and the same will happen to G and B values.
	
	//rStep,gStep, and bStep are variables that will be used
	//to hold the values at which R,G,B will be changed respectivily
	//For example: if we have RTop=100 and RBot=150 then 
	//rStep=(150-100)/256 so when we start at R=100 and draw 256 rectangles
	//we will end at R=150 when we finish drawing these rectangles
	double rStep,gStep,bStep;
	double rCount,gCount,bCount;
	double RectHeight=m_Size.cy/256.0;
	const int NUM_COLORS=256;
	//We will start counting from TopColor to BottomColor
	//So we give an initial value of the TopColor
	rCount=RTop;
	gCount=GTop;
	bCount=BTop;
	//Calcualte the step of R,G,B values
	rStep=-((double)RTop-RBot)/NUM_COLORS;
	gStep=-((double)GTop-GBot)/NUM_COLORS;
	bStep=-((double)BTop-BBot)/NUM_COLORS;
	
	for(int ColorCount=0;ColorCount<NUM_COLORS;ColorCount++)
	{
		//Draw using current RGB values and Change RGB values
		//to represent the next color in the chain
		m_dcMem->FillRect(CRect(0,ColorCount*RectHeight,m_Size.cx,(ColorCount+1)*RectHeight),&CBrush(RGB(rCount,gCount,bCount)));
		rCount+=rStep;
		gCount+=gStep;
		bCount+=bStep;
	}
	
}

void CGradient::PrepareHorizontal(CDC *pDC,UINT RLeft,UINT GLeft,UINT BLeft,UINT RRight,UINT GRight,UINT BRight)
{
	if(m_dcMem!=NULL)
	{
		delete m_dcMem;
		
	}
	CBitmap Bitmap;
	m_dcMem=new CDC;
	m_dcMem->CreateCompatibleDC(pDC);
	m_dcMem->SetMapMode(MM_TEXT);
	Bitmap.CreateCompatibleBitmap(pDC,m_Size.cx,m_Size.cy);
	m_dcMem->SelectObject(&Bitmap);
	////////////////////////////////////////////////////////////////
	////Drawing The Gradient in a MemDC
	double rStep,gStep,bStep;
	double rCount,gCount,bCount;
	double RectWidth=m_Size.cx/256.0;
	const int NUM_COLORS=256;
	rCount=RRight;
	gCount=GRight;
	bCount=BRight;
	rStep=-((double)RRight-RLeft)/NUM_COLORS;
	gStep=-((double)GRight-GLeft)/NUM_COLORS;
	bStep=-((double)BRight-BLeft)/NUM_COLORS;
	
	for(int ColorCount=0;ColorCount<NUM_COLORS;ColorCount++)
	{
		m_dcMem->FillRect(CRect(ColorCount*RectWidth,0,(ColorCount+1)*RectWidth,m_Size.cy),&CBrush(RGB(rCount,gCount,bCount)));
		rCount+=rStep;
		gCount+=gStep;
		bCount+=bStep;
	}
}

void CGradient::Draw(CDC *pDC, int xDest,int yDest,int xSrc, int ySrc, int Width, int Height,DWORD Rop)
{
	//Use BitBlt to Draw on a DC
	
	pDC->BitBlt(xDest,yDest,Width,Height,m_dcMem,xSrc,ySrc,Rop);

	
}
