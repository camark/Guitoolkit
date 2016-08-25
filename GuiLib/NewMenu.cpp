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
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/

//------------------------------------------------------------------------------
// File    : NewMenu.cpp 
// Version : 1.0
// Date    : Mai 2002
// Author  : Bruno Podetti
// Email   : Podetti@gmx.net
// Systems : VC6.0 and VC7.0 (Run under (Window 98/ME), Windows Nt 2000/XP)
//
// Bug Fixes and portions of code from previous version supplied by:
//
// Brent Corkum, Ben Ashley, Girish Bharadwaj, Jean-Edouard Lachand-Robert,
// Robert Edward Caldecott, Kenny Goers, Leonardo Zide, Stefan Kuhr, 
// Reiner Jung, Martin Vladic, Kim Yoo Chul, Oz Solomonovich, Tongzhe Cui, 
// Stephane Clog, Warren Stevens, Damir Valiulin
// 
// You are free to use/modify this code but leave this header intact.
// This class is public domain so you are free to use it any of your 
// applications (Freeware, Shareware, Commercial). 
// All I ask is that you let me know so that if you have a real winner I can
// brag to my buddies that some of my code is in your app. I also wouldn't 
// mind if you sent me a copy of your application since I like to play with
// new stuff.
//------------------------------------------------------------------------------

#include "stdafx.h"        // Standard windows header file
#include "NewMenu.h"       // CNewMenu class declaration
#include "GuiDrawLayer.h"
#include "MenuBar.h"
//#define _TRACE_MENU_

#ifdef _TRACE_MENU_
#include "MyTrace.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#endif

#ifndef IS_INTRESOURCE
#define IS_INTRESOURCE(hh) (HIWORD(hh)==NULL)
#endif 

#define GAP 2

#ifndef ODS_HOTLIGHT
#define ODS_HOTLIGHT        0x0040
#endif

#ifndef ODS_INACTIVE
#define ODS_INACTIVE        0x0080
#endif

#ifndef COLOR_MENUBAR
#define COLOR_MENUBAR       30
#endif

#ifndef SPI_GETDROPSHADOW
#define SPI_GETDROPSHADOW   0x1024
#endif

#ifndef SPI_GETFLATMENU
#define SPI_GETFLATMENU     0x1022
#endif
extern int		gbintHorz;			//Horz=0, Vert=1
extern CRect	rcMenu;				//CRect of button

/////////////////////////////////////////////////////////////////////////////
#include "GuiDrawLayer.h"
// Helpers for casting
__inline HMENU UIntToHMenu(const unsigned int ui )
{
  return( (HMENU)(UINT_PTR)ui );
}

__inline HMENU HWndToHmenu(const HWND hwnd )
{
  return( (HMENU)hwnd );
}

__inline UINT HWndToUInt(const HWND hWnd )
{
  return( (UINT)(UINT_PTR) hWnd);
}

__inline HWND UIntToHWnd(const UINT hWnd )
{
  return( (HWND)(UINT_PTR) hWnd);
}

__inline UINT HMenuToUInt(const HMENU hMenu )
{
  return( (UINT)(UINT_PTR) hMenu);
}

//static CMenuBar* pBar=CNewMenu::m_pBar;
CMenuButton* pb;
static void ShowLastError()
{
  DWORD error = GetLastError();
  if(error)
  {
    LPVOID lpMsgBuf=NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_FROM_SYSTEM | 
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  error,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (LPTSTR) &lpMsgBuf,
                  0,
                  NULL );
    if(lpMsgBuf)
    {
      // Display the string.
      MessageBox( NULL, (LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION );
      // Free the buffer.
      LocalFree( lpMsgBuf );
    }
    else
    {
      CString temp;
      temp.Format(_T("Error message 0x%lx not found"),error);
      // Display the string.
      MessageBox( NULL,temp, _T("Error"), MB_OK | MB_ICONINFORMATION );
    }
  }
}

enum Win32Type
{
  Win32s,
  WinNT3,
  Win95,
  Win98,
  WinME,
  WinNT4,
  Win2000,
  WinXP
};

Win32Type IsShellType()
{
  Win32Type  ShellType;
  DWORD winVer;
  OSVERSIONINFO *osvi;

  winVer=GetVersion();
  if(winVer<0x80000000)
  {/*NT */
    ShellType=WinNT3;
    osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
    if (osvi!=NULL)
    {
      ZeroMemory(osvi,sizeof(OSVERSIONINFO));
      osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
      if(!GetVersionEx(osvi))
      {
        ShowLastError();
      }
      if(osvi->dwMajorVersion==4L)
      {
        ShellType=WinNT4;
      }
      else if(osvi->dwMajorVersion==5L && osvi->dwMinorVersion==0L)
      {
        ShellType=Win2000;
      }
      else if(osvi->dwMajorVersion==5L && osvi->dwMinorVersion==1L)
      {
        ShellType=WinXP;
      }
      free(osvi);
    }
  }
  else if (LOBYTE(LOWORD(winVer))<4)
  {
    ShellType=Win32s;
  }
  else
  {
    ShellType=Win95;
    osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
    if (osvi!=NULL)
    {
      memset(osvi,0,sizeof(OSVERSIONINFO));
      osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
      GetVersionEx(osvi);
      if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==10L)
      {
        ShellType=Win98;
      }
      else if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==90L)
      {
        ShellType=WinME;
      }
      free(osvi);
    }
  }
  return ShellType;
}

BOOL IsShadowEnabled()
{
  BOOL bEnabled=FALSE;
  if(SystemParametersInfo(SPI_GETDROPSHADOW,0,&bEnabled,0))
  {
    return bEnabled;
  }
  return FALSE;
}

COLORREF DarkenColorXP(COLORREF ColA)
{
  return RGB( MulDiv(GetRValue(ColA),7,10),
              MulDiv(GetGValue(ColA),7,10),
              MulDiv(GetBValue(ColA)+55,7,10));
}

// Function splits a color into its RGB components and
// transforms the color using a scale 0..255
COLORREF DarkenColor( long lScale, COLORREF lColor)
{ 
  long R = MulDiv(GetRValue(lColor),(255-lScale),255);
  long G = MulDiv(GetGValue(lColor),(255-lScale),255);
  long B = MulDiv(GetBValue(lColor),(255-lScale),255);

  return RGB(R, G, B); 
}

COLORREF MixedColor(COLORREF ColA,COLORREF ColB)
{
  // ( 86a + 14b ) / 100
  int Red   = MulDiv(86,GetRValue(ColA),100) + MulDiv(14,GetRValue(ColB),100);
  int Green = MulDiv(86,GetGValue(ColA),100) + MulDiv(14,GetGValue(ColB),100);
  int Blue  = MulDiv(86,GetBValue(ColA),100) + MulDiv(14,GetBValue(ColB),100);

  return RGB( Red,Green,Blue);
}

COLORREF MidColor(COLORREF ColA,COLORREF ColB)
{ 
  // (7a + 3b)/10
  int Red   = MulDiv(7,GetRValue(ColA),10) + MulDiv(3,GetRValue(ColB),10);
  int Green = MulDiv(7,GetGValue(ColA),10) + MulDiv(3,GetGValue(ColB),10);
  int Blue  = MulDiv(7,GetBValue(ColA),10) + MulDiv(3,GetBValue(ColB),10);

  return RGB( Red,Green,Blue);
}

// used for function gradientfill.
//#pragma comment(lib,"Msimg32.lib")

void DrawGradient(CDC* pDC,CRect& Rect,
                  COLORREF StartColor,COLORREF EndColor, 
                  BOOL bHorizontal)
{
  /*TRIVERTEX vert[2] ;
  GRADIENT_RECT gRect;

  vert [0].y = Rect.top;
  vert [0].x = Rect.left;

  vert [0].Red    = COLOR16(COLOR16(GetRValue(StartColor))<<8);
  vert [0].Green  = COLOR16(COLOR16(GetGValue(StartColor))<<8);
  vert [0].Blue   = COLOR16(COLOR16(GetBValue(StartColor))<<8);
  vert [0].Alpha  = 0x0000;

  vert [1].y = Rect.bottom;
  vert [1].x = Rect.right;

  vert [1].Red    = COLOR16(COLOR16(GetRValue(EndColor))<<8);
  vert [1].Green  = COLOR16(COLOR16(GetGValue(EndColor))<<8);
  vert [1].Blue   = COLOR16(COLOR16(GetBValue(EndColor))<<8);
  vert [1].Alpha  = 0x0000;

  gRect.UpperLeft  = 0;
  gRect.LowerRight = 1;

  if(bHorizontal)
    GradientFill(pDC->m_hDC,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);
  else
    GradientFill(pDC->m_hDC,vert,2,&gRect,1,GRADIENT_FILL_RECT_V);*/
}

/////////////////////////////////////////////////////////////////////////////
// CMenuTheme for drawing border and the rest

typedef void (CNewMenu::*pItemMeasureFkt) (LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenubar);
typedef void (CNewMenu::*pItemDrawFkt) (LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenubar);
typedef BOOL (CNewMenu::*pEraseBkgndFkt) (HWND hWnd, HDC hDC);

typedef void (CMenuTheme::*pDrawMenuBorder)( HWND hWnd, HDC hDC, CPoint screen);

class CMenuTheme
{
public:
  CMenuTheme();

  CMenuTheme(DWORD dwThemeId, 
             pItemMeasureFkt pMeasureItem,
             pItemDrawFkt pDrawItem,
             pItemDrawFkt pDrawTitle,
             DWORD dwFlags=0);

  virtual ~CMenuTheme();
  virtual BOOL OnInitWnd(HWND hWnd);
  virtual BOOL OnUnInitWnd(HWND hWnd);

  virtual BOOL DoDrawBorder();

  virtual BOOL OnDrawBorder(HWND hWnd, HDC hDC);
  virtual BOOL OnEraseBkgnd(HWND hWnd, HDC hDC);
  virtual BOOL OnNcCalcSize(HWND hWnd, NCCALCSIZE_PARAMS* pCalc);
  virtual BOOL OnWindowPosChanging(HWND hWnd, LPWINDOWPOS pPos);

  void DrawShade( HWND hWnd, HDC hDC, CPoint screen);
  void DrawSmalBorder( HWND hWnd, HDC hDC);

public:
  DWORD m_dwThemeId;
  DWORD m_dwFlags;

  pItemMeasureFkt m_pMeasureItem;
  pItemDrawFkt m_pDrawItem;
  pItemDrawFkt m_pDrawTitle;

  CSize m_BorderTopLeft;
  CSize m_BorderBottomRight;
};

/////////////////////////////////////////////////////////////////////////////
// CMenuThemeXP for drawing border and the rest

class CMenuThemeXP :public CMenuTheme
{
public:
  CMenuThemeXP(DWORD dwThemeId, 
                pItemMeasureFkt pMeasureItem,
                pItemDrawFkt pDrawItem,
                pItemDrawFkt pDrawTitle,
                DWORD dwFlags=0);
		
  virtual BOOL OnDrawBorder(HWND hWnd, HDC hDC);
  virtual BOOL OnEraseBkgnd(HWND hWnd, HDC hDC);
  
};

/////////////////////////////////////////////////////////////////////////////
// CNewMenuHook important class for subclassing menus!

class CNewMenuHook
{
public:
	
  class CMenuHookData 
  {
  public:
    CMenuHookData(HWND hWnd,BOOL bSpecialWnd) 
      : m_dwData(bSpecialWnd),m_bDrawBorder(TRUE),m_Point(0,0)
    {
      // Safe actual menu
      m_hMenu = CNewMenuHook::m_hLastMenu;
      // Reset for the next menu
      CNewMenuHook::m_hLastMenu = NULL;

      // Save actual border setting etc.
      m_dwStyle = GetWindowLong(hWnd, GWL_STYLE) ;
      m_dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE); 
    }

    DWORD m_dwStyle;
    DWORD m_dwExStyle;

    CPoint m_Point;
    DWORD m_dwData;

    BOOL m_bDrawBorder;
    HMENU m_hMenu;
  }; 

public:
  CNewMenuHook();
  ~CNewMenuHook();

public:
  static CMenuHookData* GetMenuHookData(HWND hWnd);

  static BOOL AddTheme(CMenuTheme*);
  static CMenuTheme* RemoveTheme(DWORD dwThemeId);
  static CMenuTheme* FindTheme(DWORD dwThemeId);
	
private:
  static LRESULT CALLBACK NewMenuHook(int code, WPARAM wParam, LPARAM lParam);
  static BOOL CheckSubclassing(HWND hWnd,BOOL bSpecialWnd);
  static LRESULT CALLBACK SubClassMenu(HWND hWnd,  UINT uMsg, WPARAM wParam,  LPARAM lParam );
  static void UnsubClassMenu(HWND hWnd);
 
  static BOOL SubClassMenu2(HWND hWnd,  UINT uMsg, WPARAM wParam,  LPARAM lParam, DWORD* pResult);

public:
  static HMENU m_hLastMenu;
  static DWORD m_dwMsgPos; 
  	
private:
  static HHOOK HookOldMenuCbtFilter;
  // an map of actual opened Menu and submenu
  static CTypedPtrMap<CMapPtrToPtr,HWND,CMenuHookData*> m_MenuHookData;
  // Stores list of all defined Themes
  static CTypedPtrList<CPtrList, CMenuTheme*>* m_pRegisteredThemesList; 
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CNewMenuItemData,CObject); 

CNewMenuItemData::CNewMenuItemData()
: m_nTitleFlags(0),
  m_nFlags(0),
  m_nID(0),
  m_nSyncFlag(0),
  m_nxOffset(-1),
  m_pBitmap(NULL),
  m_nMenuIconNormal(-1),
  m_pData(NULL)
{
}

CNewMenuItemData::~CNewMenuItemData()
{
  if(m_pBitmap)
  {
    delete m_pBitmap;
    m_pBitmap = NULL;
  }
}

LPCTSTR CNewMenuItemData::GetString()
{
  return m_szMenuText;
}
 
void CNewMenuItemData::SetString(LPCTSTR szMenuText)
{
  m_szMenuText = szMenuText;
}

#if defined(_DEBUG) || defined(_AFXDLL)
// Diagnostic Support
void CNewMenuItemData::AssertValid() const
{
  CObject::AssertValid();
}

void CNewMenuItemData::Dump(CDumpContext& dc) const
{
  CObject::Dump(dc);
  dc << _T("MenuItem: ") << m_szMenuText << _T("\n"); 
}

#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CNewMenu,CMenu);

// Stores list of all sub-menus
CTypedPtrArray<CPtrArray, HMENU> CNewMenu::m_AllSubMenus;

// actual selectet menu-draw mode
CMenuTheme* CNewMenu::m_pActMenuDrawing = NULL;

// one instance of the hook for menu-subclassing
static CNewMenuHook MyNewMenuHookInstance;

// color for drawing menubar
int CNewMenu::cCOLOR_MENUBAR = COLOR_MENU;
DWORD CNewMenu::m_StyleMenu= GUISTYLE_XP;

// how the menu's are drawn in winXP
BOOL CNewMenu::m_bSelectDisable=TRUE;

static Win32Type g_Shell=IsShellType();

CNewMenu::CNewMenu(HMENU hParent)
: m_hParentMenu(hParent),
  m_bIsPopupMenu(FALSE),
  m_dwOpenMenu(NULL),
  m_LastActiveMenuRect(0,0,0,0)
{
  // O.S. - no dynamic icons by default
  m_bDynIcons = FALSE;
  // Icon sizes default to 16 x 16
  m_iconX = 16;
  m_iconY = 15;
  m_selectcheck = -1;
  m_unselectcheck = -1;
  checkmaps=NULL;
  checkmapsshare=FALSE;
  CMenuButton* m_pBar=NULL;	
  // set the color used for the transparent background in all bitmaps
  m_bitmapBackground = CLR_DEFAULT;
}

CNewMenu::~CNewMenu()
{
  DestroyMenu();
}

void CNewMenu::SetLastMenuRect(HDC hDC, LPRECT pRect)
{
  if(!m_bIsPopupMenu)
  {
    HWND hWnd = WindowFromDC(hDC);
    if(hWnd && pRect)
    {
      CRect Temp;
      GetWindowRect(hWnd,Temp);
      m_LastActiveMenuRect = *pRect;
      m_LastActiveMenuRect.OffsetRect(Temp.TopLeft());
    }
  }
}

BOOL CNewMenu::IsNewShell ()
{
  return (g_Shell>=Win95);
}

BOOL CNewMenu::OnMeasureItem(const MSG* pMsg)
{
  if(pMsg->message==WM_MEASUREITEM)
  {
    LPMEASUREITEMSTRUCT lpMIS = (LPMEASUREITEMSTRUCT)pMsg->lParam;
    if(lpMIS->CtlType==ODT_MENU)
    {
      CMenu* pMenu=NULL;
      if(::IsMenu(UIntToHMenu(lpMIS->itemID)) )
      {
        pMenu = CMenu::FromHandlePermanent(UIntToHMenu(lpMIS->itemID) );
      }
      else
      {
        _AFX_THREAD_STATE* pThreadState = AfxGetThreadState ();
        if (pThreadState->m_hTrackingWindow == pMsg->hwnd)
        {
          // start from popup
          pMenu = FindPopupMenuFromIDData(pThreadState->m_hTrackingMenu,lpMIS->itemID,lpMIS->itemData);
        }
        if(pMenu==NULL)
        {
          // start from menubar
          pMenu = FindPopupMenuFromIDData(::GetMenu(pMsg->hwnd),lpMIS->itemID,lpMIS->itemData);
          if(pMenu==NULL)
          {
            // finaly start from system menu.
            pMenu = FindPopupMenuFromIDData(::GetSystemMenu(pMsg->hwnd,FALSE),lpMIS->itemID,lpMIS->itemData);
          }
        }
      }
      if(pMenu!=NULL)
      {
        pMenu->MeasureItem(lpMIS);
        return TRUE;
      }
    }
  }
  return FALSE;
}

CMenu* CNewMenu::FindPopupMenuFromID(HMENU hMenu, UINT nID)
{
  // check for a valid menu-handle
  if ( ::IsMenu(hMenu))
  {
    CMenu *pMenu = CMenu::FromHandlePermanent(hMenu);
    if(pMenu)
    {
      return FindPopupMenuFromID(pMenu,nID);
    }
  }
  return NULL; 
}

CMenu* CNewMenu::FindPopupMenuFromIDData(HMENU hMenu, UINT nID, ULONG_PTR pData)
{
  // check for a valid menu-handle
  if ( ::IsMenu(hMenu))
  {
    CMenu *pMenu = CMenu::FromHandlePermanent(hMenu);
    if(pMenu)
    {
      return FindPopupMenuFromIDData(pMenu,nID,pData);
    }
  }
  return NULL; 
}

CMenu* CNewMenu::FindPopupMenuFromIDData(CMenu* pMenu, UINT nID, ULONG_PTR pData)
{
  ASSERT_VALID(pMenu);
  // walk through all items, looking for ID match
  UINT nItems = pMenu->GetMenuItemCount();
  for (int iItem = 0; iItem < (int)nItems; iItem++)
  {
    CMenu* pPopup = pMenu->GetSubMenu(iItem);
    if (pPopup != NULL)
    {
      // recurse to child popup
      pPopup = FindPopupMenuFromIDData(pPopup, nID, pData);
      // check popups on this popup
      if (pPopup != NULL)
        return pPopup;
    }
    else if (pMenu->GetMenuItemID(iItem) == nID)
    { 
      MENUITEMINFO MenuItemInfo;
      ::ZeroMemory(&MenuItemInfo,sizeof(MenuItemInfo));
      MenuItemInfo.cbSize = sizeof(MenuItemInfo);
      MenuItemInfo.fMask = MIIM_DATA;

      if(pMenu->GetMenuItemInfo(iItem,&MenuItemInfo,TRUE))
      {
        if(MenuItemInfo.dwItemData==pData)
        {
          // it is a normal item inside our popup
          return pMenu;
        }
      }
    }
  }
  // not found
  return NULL;
}

CMenu* CNewMenu::FindPopupMenuFromID(CMenu* pMenu, UINT nID)
{
  ASSERT_VALID(pMenu);
  // walk through all items, looking for ID match
  UINT nItems = pMenu->GetMenuItemCount();
  for (int iItem = 0; iItem < (int)nItems; iItem++)
  {
    CMenu* pPopup = pMenu->GetSubMenu(iItem);
    if (pPopup != NULL)
    {
      // recurse to child popup
      pPopup = FindPopupMenuFromID(pPopup, nID);
      // check popups on this popup
      if (pPopup != NULL)
        return pPopup;
    }
    else if (pMenu->GetMenuItemID(iItem) == nID)
    {
      // it is a normal item inside our popup
      return pMenu;
    }
  }
  // not found
  return NULL;
}

BOOL CNewMenu::DestroyMenu()
{
  // Destroy Sub menus:
  int m,n;
  int numAllSubMenus = (int)m_AllSubMenus.GetUpperBound();
  for(n = numAllSubMenus; n>= 0; n--)
  {
    if(m_AllSubMenus[n]==this->m_hMenu)
      m_AllSubMenus.RemoveAt(n);
  }
  int numSubMenus = (int)m_SubMenus.GetUpperBound();
  for(m = numSubMenus; m >= 0; m--)
  {
    numAllSubMenus = (int)m_AllSubMenus.GetUpperBound();
    for(n = numAllSubMenus; n>= 0; n--)
    {
      if(m_AllSubMenus[n]==m_SubMenus[m])
        m_AllSubMenus.RemoveAt(n);
    }
    delete((CNewMenu *)FromHandle(m_SubMenus[m]));
  }
  m_SubMenus.RemoveAll();
  // Destroy menu data
  int numItems = (int)m_MenuList.GetUpperBound();
  for(m = 0; m <= numItems; m++)
  {
    delete(m_MenuList[m]);
  }
  
  m_MenuList.RemoveAll();
  if(checkmaps&&!checkmapsshare)
  {
    delete checkmaps;
    checkmaps=NULL;
  }
  // Call base-class implementation last:
  return(CMenu::DestroyMenu());
};

int CNewMenu::GetMenuDrawMode()
{
  ASSERT(m_pActMenuDrawing);
  return m_pActMenuDrawing->m_dwThemeId;
}

void CNewMenu::SetMenuDrawMode(UINT mode)
{
  CMenuTheme* pTheme = CNewMenuHook::FindTheme(mode);
  if(pTheme)
  {
    m_pActMenuDrawing = pTheme;
  }
}

HMENU CNewMenu::GetParent()
{
  return m_hParentMenu;
}

BOOL CNewMenu::IsPopup()
{
  return m_bIsPopupMenu;
}

BOOL CNewMenu::SetSelectDisableMode(BOOL mode)
{
  BOOL bOldMode = m_bSelectDisable;
  m_bSelectDisable=mode;

  return bOldMode;
}

BOOL CNewMenu::GetSelectDisableMode()
{
  return m_bSelectDisable;
}

void CNewMenu::MeasureItem( LPMEASUREITEMSTRUCT lpMIS )
{
  ASSERT(m_pActMenuDrawing);

  BOOL bIsMenuBar = IsMenuBar(UIntToHMenu(lpMIS->itemID));

  ((*this).*m_pActMenuDrawing->m_pMeasureItem)(lpMIS,bIsMenuBar);
}

void CNewMenu::DrawItem (LPDRAWITEMSTRUCT lpDIS)
{
  ASSERT(m_pActMenuDrawing);
  
  BOOL bIsMenuBar = m_hParentMenu ? FALSE: ((m_bIsPopupMenu)?FALSE:TRUE);

  (this->*m_pActMenuDrawing->m_pDrawItem)(lpDIS,bIsMenuBar);
}

// Erase the Background of the menu
BOOL CNewMenu::EraseBkgnd(HWND hWnd, HDC hDC)
{
  CDC* pDC = CDC::FromHandle (hDC);
  CRect Rect;
  //  Get the size of the menu... 
  GetClientRect(hWnd, Rect );

  pDC->FillSolidRect (Rect,GetSysColor(cCOLOR_MENUBAR));

  return TRUE;
}

void CNewMenu::DrawTitle(LPDRAWITEMSTRUCT lpDIS,BOOL bIsMenuBar)
{
  ASSERT(m_pActMenuDrawing);
  (this->*m_pActMenuDrawing->m_pDrawTitle)(lpDIS,bIsMenuBar);
}

void CNewMenu::DrawMenuTitle(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  UNREFERENCED_PARAMETER(bIsMenuBar);

  CDC* pDC = CDC::FromHandle(lpDIS->hDC);

  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpDIS->itemData);
  ASSERT(pMenuData);

  COLORREF ColA = GetSysColor(COLOR_WINDOW);
  COLORREF ColB = GetSysColor(cCOLOR_MENUBAR);
  
  COLORREF colorMenu = MixedColor(ColA,ColB);

  CRect rcClipBox;
  pDC->GetClipBox(rcClipBox);

  // draw the title bar
  CRect rect = lpDIS->rcItem;
  CPoint TextPoint;

  CFont Font;
  if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
  {
    rect.top = rcClipBox.top;
    rect.bottom = rcClipBox.bottom;
    rect.right += GetSystemMetrics(SM_CXMENUCHECK);
    Font.CreateFont(16, 0, 900, 900, FW_BOLD,
                        0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                        DEFAULT_PITCH,_T("Arial"));

    TextPoint = CPoint(rect.left+2, rect.bottom-4);
    // DrawGradient(pDC,rect,colorMenu,::GetSysColor(COLOR_ACTIVECAPTION),false);
  }
  else
  {
    Font.CreateFont(16, 0, 0, 0, FW_BOLD,
                        0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                        DEFAULT_PITCH,_T("Arial"));

    TextPoint = CPoint(rect.left+2, rect.top);

    // DrawGradient(pDC,rect,::GetSysColor(COLOR_ACTIVECAPTION),colorMenu,true);
  }
  if(pMenuData->m_nTitleFlags&MFT_GRADIENT)
  {
    if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
    {
      DrawGradient(pDC,rect,colorMenu,::GetSysColor(COLOR_ACTIVECAPTION),false);
    }
    else
    {
      DrawGradient(pDC,rect,::GetSysColor(COLOR_ACTIVECAPTION),colorMenu,true);
    }
  }
  else
  {
    if(pMenuData->m_nTitleFlags&MFT_ROUND)
    {
      if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
      {
        TextPoint.y-=2;
        rect.right = rect.left+21;
      }
      else
      {
        TextPoint.x+=10;
      }

      CBrush brush(GetSysColor(COLOR_ACTIVECAPTION));
      CPen* pOldPen = (CPen*)pDC->SelectStockObject(WHITE_PEN);
      CBrush* pOldBrush = pDC->SelectObject(&brush);

      pDC->RoundRect(rect,CPoint(10,10));
      pDC->SelectObject(pOldBrush);
      pDC->SelectObject(pOldPen); 
      
    }
    else
    {
      pDC->FillSolidRect(rect,GetSysColor(COLOR_ACTIVECAPTION));
    }
  }
  if (pMenuData->m_nTitleFlags&MFT_SUNKEN)
  {
    pDC->Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
  }

  CFont *pOldFont = pDC->SelectObject(&Font);
  COLORREF oldColor = pDC->SetTextColor(::GetSysColor(COLOR_CAPTIONTEXT));
  int OldMode = pDC->SetBkMode(TRANSPARENT);

  if (pMenuData->m_nTitleFlags&MFT_CENTER)
  {
    SIZE size;
    VERIFY(::GetTextExtentPoint32(pDC->m_hDC,pMenuData->m_szMenuText,pMenuData->m_szMenuText.GetLength(),&size));
    if (pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
    {
      TextPoint.y = rect.bottom - ((rect.Height()-size.cx)>>1);
    }
    else
    {
      TextPoint.x = rect.left + ((rect.Width()-size.cx)>>1);
    }
  }

  pDC->TextOut(TextPoint.x,TextPoint.y, pMenuData->GetString());

  if(pMenuData->m_nTitleFlags&MFT_LINE)
  {
    if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
    {
      CRect rect2(rect.left+20,rect.top+5,rect.left+22,rect.bottom-5);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
      rect2.OffsetRect(3,0);
      rect2.InflateRect(0,-10);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
    }
    else
    {
      CRect rect2(rect.left+2,rect.bottom-7,rect.right-2,rect.bottom-5);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
      rect2.OffsetRect(0,3);
      rect2.InflateRect(-10,0);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
    }
  }
  
  pDC->SetBkMode(OldMode);
  pDC->SetTextColor(oldColor);  
  pDC->SelectObject(pOldFont);
}

void CNewMenu::DrawItem_WinXP(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  ASSERT(lpDIS != NULL);
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
  CRect rect;

  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpDIS->itemData);
  ASSERT(pMenuData);

  UINT state = pMenuData->m_nFlags;

  COLORREF ColA = GetSysColor(COLOR_WINDOW);
  COLORREF ColB = GetSysColor(cCOLOR_MENUBAR);

  COLORREF colorMenu = MixedColor(ColA,ColB);
  COLORREF colorBitmap = MixedColor(ColB,ColA);

  COLORREF colorSel = MidColor(ColA,GetSysColor(COLOR_HIGHLIGHT));

  CPen Pen(PS_SOLID,0,GetSysColor(COLOR_HIGHLIGHT));

  if(bIsMenuBar)
  {
#ifdef _TRACE_MENU_
    TRACE(_T("BarState: 0x%lX Menus %ld\n"),lpDIS->itemState,m_dwOpenMenu);
#endif
    if(!m_dwOpenMenu && lpDIS->itemState&ODS_SELECTED)
    {
      lpDIS->itemState = (lpDIS->itemState&~ODS_SELECTED)|ODS_HOTLIGHT;
    }
    if(!(lpDIS->itemState&ODS_HOTLIGHT))
    { 
      colorSel = colorBitmap;
    }
    colorMenu = ColB;
  }

  CBrush m_brBackground(colorMenu);
  CBrush m_brSel(colorSel);
  CBrush m_brBitmap(colorBitmap);

  CRect RectL(lpDIS->rcItem);
  CRect RectR(lpDIS->rcItem);
  CRect RectSel(lpDIS->rcItem);

  if(bIsMenuBar)
  {
    RectR.InflateRect (0,0,0,0);
    RectSel.InflateRect (0,0,-2 -2,0);
  }  
  else
  {
    RectL.right = RectL.left + m_iconX + 8;
    RectR.left  = RectL.right;
    // Draw for Bitmapbackground
    pDC->FillSolidRect (RectL,colorBitmap);
  }
  // Draw for Textbackground
  pDC->FillSolidRect (RectR,colorMenu);

  // Spacing for submenu only in popups
  if(!bIsMenuBar)
  {
    RectR.left += 4;
    RectR.right-= 15;
  }

  //  Flag for highlighted item
  if(lpDIS->itemState & (ODS_HOTLIGHT|ODS_INACTIVE) )
  {
    lpDIS->itemState |= ODS_SELECTED;
  }

  if(bIsMenuBar && (lpDIS->itemState&ODS_SELECTED) )
  {
    if(!(lpDIS->itemState&ODS_INACTIVE) )
    {
      SetLastMenuRect(lpDIS->hDC,RectSel);
      if(!(lpDIS->itemState&ODS_HOTLIGHT) )
      { 
        int X,Y;
        CRect rect = RectR;
        int winH = rect.Height(); 

        // Simulate a shadow on right edge... 
        for (X=1; X<=4 ;X++)
        { 
          for (Y=0; Y<4 ;Y++)
          {
            pDC->SetPixel(rect.right-X,Y+rect.top, ColB );
          }
          for (Y=4; Y<8 ;Y++)
          {
            pDC->SetPixel(rect.right-X,Y+rect.top,DarkenColor(3 * X * (Y - 3), ColB)) ;
          }
          for (Y=8; Y<=(winH-1) ;Y++)
          {
            pDC->SetPixel(rect.right - X, Y+rect.top, DarkenColor(15 * X, ColB) );
          }
        }
      }
    }
  }
  // For keyboard navigation only
  BOOL bDrawSmalSelection = FALSE;
  // remove the selected bit if it's grayed out
  if( (lpDIS->itemState&ODS_GRAYED) && !m_bSelectDisable)
  {
    if( lpDIS->itemState & ODS_SELECTED )
    {
      lpDIS->itemState=lpDIS->itemState & ~ODS_SELECTED;
      DWORD MsgPos = ::GetMessagePos();
      if(MsgPos==CNewMenuHook::m_dwMsgPos)
      {
        bDrawSmalSelection = TRUE;
      }
      else
      {
        CNewMenuHook::m_dwMsgPos = MsgPos;
      }
    }
  }

  // Draw the seperator
  if(state & MF_SEPARATOR)
  {
    if(pMenuData->m_nTitleFlags&MFT_TITLE)
    {
      DrawTitle(lpDIS,bIsMenuBar);
    }
    else
    {
      // Draw only the seperator
      CRect rect;
      rect.top = RectR.CenterPoint().y;
      rect.bottom = rect.top+1;
      rect.right = lpDIS->rcItem.right+1;
      rect.left = RectR.left;
      pDC->FillSolidRect(rect,GetSysColor(COLOR_GRAYTEXT));
    }
  }
  else
  {
    if( (lpDIS->itemState & ODS_SELECTED) && !(lpDIS->itemState&ODS_INACTIVE) )
    {
      // Draw the selection
      CPen* pOldPen = pDC->SelectObject(&Pen);
      CBrush* pOldBrush = pDC->SelectObject(&m_brSel);
      pDC->Rectangle(RectSel);
      pDC->SelectObject(pOldBrush);
      pDC->SelectObject(pOldPen);
    }
    else if (bDrawSmalSelection)
    {
      // Draw the selection for keyboardnavigation
      CPen* pOldPen = pDC->SelectObject(&Pen);
      CBrush* pOldBrush = pDC->SelectObject(&m_brBackground);
      pDC->Rectangle(RectSel);
      pDC->SelectObject(pOldBrush);
      pDC->SelectObject(pOldPen);
    }

    UINT state = lpDIS->itemState;

    BOOL standardflag=FALSE;
    BOOL selectedflag=FALSE;
    BOOL disableflag=FALSE;
    BOOL checkflag=FALSE;

    CBrush m_brSelect;
    CPen m_penBack;

    CImageList* bitmap = pMenuData->m_pBitmap;
    CString strText = pMenuData->GetString();

    if((state&ODS_CHECKED) && (pMenuData->m_nMenuIconNormal<0))
    {
      if(state&ODS_SELECTED && m_selectcheck>0)
      {
        checkflag=TRUE;
      }
      else if(m_unselectcheck>0)
      {
        checkflag=TRUE;
      }
    }
    else if(pMenuData->m_nMenuIconNormal != -1)
    {
      standardflag=TRUE;
      if(state&ODS_SELECTED)
      {
        selectedflag=TRUE;
      }
      else if(state&ODS_GRAYED) 
      {
        disableflag=TRUE;
      }
    }

    // draw the menutext
    if(!strText.IsEmpty())
    {
      LOGFONT LogFontMenu;
      CFont FontMenu;

      NONCLIENTMETRICS nm;
      ::ZeroMemory(&nm,sizeof(nm));
      nm.cbSize = sizeof (nm);
      VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
      LogFontMenu =  nm.lfMenuFont;

      // Default selection?
      if(state&ODS_DEFAULT)
      {
        // Make the font bold
        LogFontMenu.lfWeight = FW_BOLD;
      }
      FontMenu.CreateFontIndirect(&LogFontMenu);

      CString leftStr;
      CString rightStr;
      leftStr.Empty();
      rightStr.Empty();

      int tablocr=strText.ReverseFind(_T('\t'));
      if(tablocr!=-1)
      {
        rightStr=strText.Mid(tablocr+1);
        leftStr=strText.Left(strText.Find(_T('\t')));
      }
      else 
        leftStr=strText;

      // Draw the text in the correct colour:
      UINT nFormat  = DT_LEFT| DT_SINGLELINE|DT_VCENTER;
      UINT nFormatr = DT_RIGHT|DT_SINGLELINE|DT_VCENTER;

      int iOldMode = pDC->SetBkMode( TRANSPARENT);
      CFont* pOldFont = pDC->SelectObject (&FontMenu);

      COLORREF OldTextColor;
      if( (lpDIS->itemState&ODS_GRAYED) || 
          (bIsMenuBar && lpDIS->itemState&ODS_INACTIVE) )
      {
        // Draw the text disabled? 
        OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
      }
      else
      {
        // Draw the text normal
        OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_MENUTEXT));
      }
      if(bIsMenuBar)
      {
        pDC->DrawText(leftStr,RectSel, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
      }
      else
      {
        pDC->DrawText(leftStr,RectR, nFormat);
        if(tablocr!=-1) 
          pDC->DrawText (rightStr,RectR,nFormatr);
      }
      pDC->SetTextColor(OldTextColor);
      pDC->SelectObject(pOldFont);
      pDC->SetBkMode(iOldMode);
    }

    // Draw the Bitmap or checkmarks
    if(!bIsMenuBar)
    {
      CRect rect2 = RectR;
      
      if(checkflag||standardflag||selectedflag||disableflag)
      {
        if(checkflag && checkmaps)
        {
          CPoint ptImage(RectL.left+3,RectL.top+4);
          
          if(state&ODS_SELECTED)
            checkmaps->Draw(pDC,1,ptImage,ILD_TRANSPARENT);
          else 
            checkmaps->Draw(pDC,0,ptImage,ILD_TRANSPARENT);
        }
        else
        {
          //CPoint ptImage(rect.left+3,rect.top+2+dy);
          HICON hDrawIcon = bitmap->ExtractIcon(0);
          int cx,cy;
          ::ImageList_GetIconSize(*bitmap, &cx, &cy);
          CSize size(cx,cy);

          CPoint ptImage(RectL.left+3,RectL.top+4);

          CBrush* pBrush = &m_brBitmap; 

          // Need to draw the checked state
          if (state&ODS_CHECKED)
          {
            CRect rect = RectL;
            rect.InflateRect (-1,-1);

            CBrush Brush;
            if(selectedflag)
              Brush.CreateSolidBrush(DarkenColorXP(colorSel));
            else
              Brush.CreateSolidBrush(DarkenColorXP(colorMenu));

            CPen* pOldPen = pDC->SelectObject(&Pen);
            CBrush* pOldBrush = pDC->SelectObject(&Brush);

            pDC->Rectangle(rect);

            pDC->SelectObject(pOldBrush);
            pDC->SelectObject(pOldPen);
          } 
          else if(selectedflag)
          {
            CBrush Brush;
            Brush.CreateSolidBrush(DarkenColorXP(colorSel));

            ptImage.x++; ptImage.y++;
            pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL | DSS_MONO, &Brush);
            ptImage.x-=2; ptImage.y-=2;
          }

          if(state & ODS_DISABLED)
            pDC->DrawState(ptImage, size, hDrawIcon, DSS_DISABLED, pBrush);
          else
            pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL,(HBRUSH)NULL);
        }
      }
      if(pMenuData->m_nMenuIconNormal<0 && state&ODS_CHECKED && !checkflag)
      {
        MENUITEMINFO info;
        ZeroMemory(&info,sizeof(info));

        info.cbSize = sizeof(info);
        info.fMask = MIIM_CHECKMARKS;

        ::GetMenuItemInfo(HWndToHmenu(lpDIS->hwndItem),lpDIS->itemID,MF_BYCOMMAND, &info);

        if(state&ODS_CHECKED || info.hbmpUnchecked) 
        {
          CRect rect = RectL;
          rect.InflateRect (-1,-1);

          COLORREF transparentcol;
          if(state&ODS_SELECTED)
            transparentcol = DarkenColorXP(colorSel);
          else
            transparentcol = DarkenColorXP(colorMenu);

          CBrush Brush;
          Brush.CreateSolidBrush(transparentcol);

          CPen* pOldPen = pDC->SelectObject(&Pen);
          CBrush* pOldBrush = pDC->SelectObject(&Brush);

          pDC->Rectangle(rect);

          pDC->SelectObject(pOldBrush);
          pDC->SelectObject(pOldPen);
          if (state&ODS_CHECKED)
          {
            rect.InflateRect (-1,-1);
            if (!info.hbmpChecked)
            { // Checkmark
              DrawSpecialCharStyle(pDC,rect,98,state);
            }
            else
            { // Bullet
              DrawSpecialCharStyle(pDC,rect,105,state);
            }
          }
          else
          {
            CSize size = rect.Size();
            CPoint ptImage = rect.TopLeft();
            if(state & ODS_DISABLED)
              pDC->DrawState(ptImage, size, info.hbmpUnchecked, DSS_DISABLED, (HBRUSH)NULL);
            else
              pDC->DrawState(ptImage, size, info.hbmpUnchecked, DSS_NORMAL,(HBRUSH)NULL);
          }
        }
      }
      else if (lpDIS->itemID>=SC_SIZE && lpDIS->itemID<=SC_HOTKEY )
      {
        DrawSpecial_WinXP(pDC,RectL,lpDIS->itemID,state);
      }
    }
  }
}

void CNewMenu::DrawItem_SpecialStyle (LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  if(!bIsMenuBar)
  {
    DrawItem_OldStyle(lpDIS,bIsMenuBar);
    return;
  }

  ASSERT(lpDIS != NULL);
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);

  ASSERT(lpDIS->itemData);
  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpDIS->itemData);

  CRect rect(lpDIS->rcItem);
  //rect.InflateRect(0,-1);

  COLORREF ColorBack;
  if(lpDIS->itemState&(ODS_SELECTED|ODS_HOTLIGHT))
  {
    ColorBack = GetSysColor(COLOR_HIGHLIGHT);
    SetLastMenuRect(lpDIS->hDC,rect);
  }
  else
  {
    ColorBack = GetSysColor(cCOLOR_MENUBAR);
  }
  pDC->FillSolidRect(rect,ColorBack);

  int iOldMode = pDC->SetBkMode( TRANSPARENT);
  CString strText = pMenuData->GetString();
  COLORREF crTextColor;
  if(!(lpDIS->itemState & ODS_GRAYED))
  {
    if(lpDIS->itemState&(ODS_SELECTED|ODS_HOTLIGHT)) 
      crTextColor = GetSysColor(COLOR_HIGHLIGHTTEXT);
    else
      crTextColor = GetSysColor(COLOR_MENUTEXT);
  }
  else
  {
    crTextColor = GetSysColor(COLOR_GRAYTEXT);
  }
  COLORREF oldColor = pDC->SetTextColor(crTextColor);
  
  pDC->DrawText(strText,rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
  
  pDC->SetTextColor(oldColor);
  pDC->SetBkMode( iOldMode);
}

void CNewMenu::DrawItem_OldStyle (LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  ASSERT(lpDIS != NULL);
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
  CRect rect;

  ASSERT(lpDIS->itemData);
  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpDIS->itemData);

  UINT state = pMenuData->m_nFlags;
  CBrush m_brBackground;

  COLORREF ColorBack = bIsMenuBar?GetSysColor(cCOLOR_MENUBAR):GetSysColor(COLOR_MENU);

  m_brBackground.CreateSolidBrush(ColorBack);

  CRect RectL(lpDIS->rcItem);
  CRect RectR(lpDIS->rcItem);
  CRect RectSel(lpDIS->rcItem);

  RectL.InflateRect (-1,0,0,0);
  RectR.InflateRect (-1,0,0,0);
  RectSel.InflateRect (0,0,0,0);

  if(!bIsMenuBar)
  {
    RectL.right = RectL.left + m_iconX + 6 + GAP;
    RectR.left  = RectL.right;
    // Draw for Bitmapbackground
    pDC->FillSolidRect (RectL,ColorBack);
  }
  else
  {
#ifdef _TRACE_MENU_
    TRACE(_T("BarState: 0x%lX Menus %ld\n"),lpDIS->itemState,m_dwOpenMenu);
#endif
    if(!m_dwOpenMenu && lpDIS->itemState&ODS_SELECTED)
    {
      lpDIS->itemState = (lpDIS->itemState&~ODS_SELECTED)|ODS_HOTLIGHT;
    }

    RectR.InflateRect (1,0,0,0);
    RectSel.InflateRect (0,0,-5,0);
    RectSel.OffsetRect(1,-1);

    SetLastMenuRect(lpDIS->hDC,RectSel);
  }

   // For keyboard navigation only
  BOOL bDrawSmalSelection = FALSE;

  // remove the selected bit if it's grayed out
  if( (lpDIS->itemState&ODS_GRAYED) && !m_bSelectDisable )
  {
    if(lpDIS->itemState & ODS_SELECTED)
    {
      lpDIS->itemState &= ~ODS_SELECTED;
      DWORD MsgPos = ::GetMessagePos();
      if(MsgPos==CNewMenuHook::m_dwMsgPos)
      {
        bDrawSmalSelection = TRUE;
      }
      else
      {
        CNewMenuHook::m_dwMsgPos = MsgPos;
      }
    }
  }

  if(state & MF_SEPARATOR)
  {
    if(pMenuData->m_nTitleFlags&MFT_TITLE)
    {
      DrawTitle(lpDIS,bIsMenuBar);
    }
    else
    {
      rect = lpDIS->rcItem; 
      rect.left += 1;
      pDC->FillSolidRect(rect,ColorBack);
      pDC->DrawEdge(&rect,EDGE_ETCHED,BF_TOP);
    }
  }
  else
  {
    CRect rect2;
    BOOL standardflag=FALSE,selectedflag=FALSE,disableflag=FALSE;
    BOOL checkflag=FALSE;

    CBrush m_brSelect;
    int nIconNormal=-1,xoffset=-1;
    CImageList *bitmap=NULL;

    // set some colors and the font
    m_brSelect.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));

    // draw the colored rectangle portion
    rect.CopyRect(&lpDIS->rcItem);
    rect.OffsetRect (1,1);
    rect2=rect=RectSel;

    // draw the up/down/focused/disabled state

    UINT state = lpDIS->itemState;
    CString strText;

    nIconNormal = pMenuData->m_nMenuIconNormal;
    xoffset = pMenuData->m_nxOffset;
    bitmap = pMenuData->m_pBitmap;
    strText = pMenuData->GetString();

    if( (state&ODS_CHECKED) && nIconNormal<0)
    {
      if(state&ODS_SELECTED && m_selectcheck>0)
        checkflag=TRUE;
      else if(m_unselectcheck>0) 
        checkflag=TRUE;
    }
    else if(nIconNormal != -1)
    {
      standardflag=TRUE;
      if(state&ODS_SELECTED && !(state&ODS_GRAYED))
        selectedflag=TRUE;
      else if(state&ODS_GRAYED)
        disableflag=TRUE;
    }

    if(bIsMenuBar)
    {
      //rect.InflateRect (1,0,0,0);
      rect.OffsetRect(-1,1);
      rect2=rect;
      pDC->FillSolidRect (rect,ColorBack);
    }
    else
    {
      // Draw the background
      pDC->FillSolidRect (rect,ColorBack);
    }
    // Draw the selection
    if(state&ODS_SELECTED)
    {
      // You need only Text highlight and thats what you get
      if(!bIsMenuBar)
      {
        if(checkflag||standardflag||selectedflag||disableflag||state&ODS_CHECKED)
        {
          rect2.SetRect(rect.left+m_iconX+4+GAP,rect.top,rect.right,rect.bottom);
        }
        pDC->FillRect(rect2,&m_brSelect);
      }
      else
      {
        pDC->Draw3dRect(rect ,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
      }
    }
    else if(bIsMenuBar && (state&ODS_HOTLIGHT) && !(state&ODS_INACTIVE))
    {
      pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
    }
    else if (bDrawSmalSelection)
    {
      pDC->DrawFocusRect(rect);
    }

    // Draw the Bitmap or checkmarks
    if(!bIsMenuBar)
    {
      CRect IconRect(rect.TopLeft(),CSize(m_iconX,m_iconY));
      IconRect.OffsetRect(GAP+1,1+((rect.Height()-m_iconY)>>2));

      CPoint ptImage = IconRect.TopLeft();
      IconRect.InflateRect(2,2);
      if(checkflag||standardflag||selectedflag||disableflag)
      {
        if(checkflag && checkmaps)
        {
          if(state&ODS_SELECTED)
            checkmaps->Draw(pDC,1,ptImage,ILD_TRANSPARENT);
          else 
            checkmaps->Draw(pDC,0,ptImage,ILD_TRANSPARENT);
        }
        else
        {
          // Need to draw the checked state
          if (IsNewShell())
          {
            if(state&ODS_CHECKED)
            {
              pDC->Draw3dRect(IconRect,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
            }
            else if (selectedflag)
            {
              pDC->Draw3dRect(IconRect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
            }
          }

          if(state & ODS_DISABLED)
          {
            HICON hDrawIcon = bitmap->ExtractIcon(0);
            int cx,cy;
            ::ImageList_GetIconSize(*bitmap, &cx, &cy);
            CSize size(cx,cy);
          
            pDC->DrawState(ptImage, size, hDrawIcon, DSS_DISABLED, (HBRUSH)NULL);
          }
          else
          {
            bitmap->Draw(pDC,0,ptImage,ILD_TRANSPARENT);
          }
        }
      }
      if(pMenuData->m_nMenuIconNormal<0 && state&ODS_CHECKED && !checkflag)
      {
        MENUITEMINFO info;
        ZeroMemory(&info, sizeof(info));

        info.cbSize = sizeof(info);
        info.fMask = MIIM_CHECKMARKS;

        ::GetMenuItemInfo(HWndToHmenu(lpDIS->hwndItem),lpDIS->itemID,MF_BYCOMMAND, &info);

        if(state&ODS_CHECKED || info.hbmpUnchecked) 
        {
          // Rectangle for checkmarks
          CRect rect = IconRect;
          if (state&ODS_CHECKED)
            Draw3DCheckmark(pDC, IconRect,info.hbmpChecked,state);
          else
            Draw3DCheckmark(pDC, IconRect,info.hbmpUnchecked,state);
        }
      }
      else if (lpDIS->itemID>=SC_SIZE && lpDIS->itemID<=SC_HOTKEY)
      {
        DrawSpecial_OldStyle(pDC,IconRect,lpDIS->itemID,state);
      } 
    }

    if(!strText.IsEmpty())
    {
      COLORREF crText = GetSysColor(COLOR_MENUTEXT);

      if(bIsMenuBar)
      {
        rect.left += 6;
        if(lpDIS->itemState&ODS_INACTIVE) 
          crText = GetSysColor(COLOR_GRAYTEXT);
      }
      else
      {
        if(lpDIS->itemState&ODS_SELECTED) 
          crText = GetSysColor(COLOR_HIGHLIGHTTEXT);

        rect.left += m_iconX + 12;
      }
      CRect rectt(rect.left,rect.top-1,rect.right,rect.bottom-1);
      
      // Find tabs
      CString leftStr,rightStr;
      leftStr.Empty();rightStr.Empty();

      int tablocr=strText.ReverseFind(_T('\t'));
      if(tablocr!=-1)
      {
        rightStr=strText.Mid(tablocr+1);
        leftStr=strText.Left(strText.Find(_T('\t')));
        rectt.right-=m_iconX;
      }
      else
        leftStr=strText;

      int iOldMode = pDC->SetBkMode( TRANSPARENT);
      // Draw the text in the correct colour:
      UINT nFormat  = DT_LEFT|DT_SINGLELINE|DT_VCENTER;
      UINT nFormatr = DT_RIGHT|DT_SINGLELINE|DT_VCENTER;

      if(bIsMenuBar)
      {
        rectt = RectSel;
        if(state & ODS_SELECTED)
        {
          rectt.OffsetRect(1,1);
        } 
        nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
      }

      if(!(lpDIS->itemState & ODS_GRAYED))
      {
        pDC->SetTextColor(crText);
        pDC->DrawText (leftStr,rectt,nFormat);
        if(tablocr!=-1)
          pDC->DrawText (rightStr,rectt,nFormatr);
      }
      else
      {
        // Draw the disabled text
        if(!(state & ODS_SELECTED))
        {
          CRect offset = rectt;
          offset.OffsetRect (1,1);

          pDC->SetTextColor(GetSysColor(COLOR_BTNHILIGHT));
          pDC->DrawText(leftStr,&offset, nFormat);
          if(tablocr!=-1) 
            pDC->DrawText (rightStr,&offset,nFormatr);

          pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
          pDC->DrawText(leftStr,rectt, nFormat);
          if(tablocr!=-1)
            pDC->DrawText(rightStr,rectt,nFormatr);
        }
        else
        {
          // And the standard Grey text:
          pDC->SetTextColor(ColorBack);
          pDC->DrawText(leftStr,rectt, nFormat);
          if(tablocr!=-1) 
            pDC->DrawText (rightStr,rectt,nFormatr);
        }
      }
      pDC->SetBkMode( iOldMode );
    }
    m_brSelect.DeleteObject();
  }
  m_brBackground.DeleteObject();
}

BOOL CNewMenu::IsMenuBar(HMENU hMenu)
{
  BOOL bIsMenuBar = ::IsMenu(hMenu);
  if(bIsMenuBar)
  {
    CNewMenu* pMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(m_hParentMenu));
    if (pMenu!=NULL && pMenu->m_hParentMenu!=NULL)
    {
      bIsMenuBar = FALSE;
    }
  }
  return bIsMenuBar;
}

/*
==========================================================================
void CNewMenu::MeasureItem(LPMEASUREITEMSTRUCT)
---------------------------------------------

  Called by the framework when it wants to know what the width and height
  of our item will be.  To accomplish this we provide the width of the
  icon plus the width of the menu text, and then the height of the icon.
  
==========================================================================
*/
void CNewMenu::MeasureItem_OldStyle( LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenuBar )
{
  ASSERT(lpMIS->itemData);
  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpMIS->itemData);

  UINT state = pMenuData->m_nFlags;
  if(state & MF_SEPARATOR)
  {
    if(pMenuData->m_nTitleFlags&MFT_TITLE)
    {
      // DC of the desktop
      CClientDC myDC(NULL);          

      CFont font;
      font.CreatePointFont(160,_T("Arial"));
      CFont* pOldFont = myDC.SelectObject (&font);
      LPCTSTR lpstrText = pMenuData->GetString();
      SIZE size;
      VERIFY(::GetTextExtentPoint32(myDC.m_hDC,lpstrText,(int)_tcslen(lpstrText),&size));
      // Select old font in
      myDC.SelectObject(pOldFont);  

      if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
      {
        lpMIS->itemWidth = size.cy*3/4 -GetSystemMetrics(SM_CXMENUCHECK);
        // Don't make the menu higher than menuitems in it
        lpMIS->itemHeight = 0;
        if(pMenuData->m_nTitleFlags&MFT_LINE)
        {
          lpMIS->itemWidth += 6;
        }
       }
      else
      {
        lpMIS->itemWidth = size.cx*3/4;
        lpMIS->itemHeight = size.cy*3/4;
        if(pMenuData->m_nTitleFlags&MFT_LINE)
        {
          lpMIS->itemHeight += 6;
        }
      }
    }
    else
    {
      lpMIS->itemHeight = 3;
    }
  }
  else
  {
    CFont m_fontMenu;
    LOGFONT m_lf;
    ZeroMemory ((PVOID) &m_lf,sizeof (LOGFONT));
    NONCLIENTMETRICS nm;
    nm.cbSize = sizeof (NONCLIENTMETRICS);
    VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, nm.cbSize,&nm,0)); 
    m_lf =  nm.lfMenuFont;
    // Default selection?
    if(state&ODS_DEFAULT)
    {
      // Make the font bold
      m_lf.lfWeight = FW_BOLD;
    }

    m_fontMenu.CreateFontIndirect (&m_lf);
    
    // DC of the desktop
    CClientDC myDC(NULL);
    
    // Select menu font in...    
    CFont* pOldFont = myDC.SelectObject (&m_fontMenu);
    //Get pointer to text SK
    const LPCTSTR lpstrText = pMenuData->GetString();
    SIZE size;
    VERIFY(::GetTextExtentPoint32(myDC.m_hDC,lpstrText,(int)_tcslen(lpstrText),&size));
    // Select old font in
    myDC.SelectObject(pOldFont);  
  
    // Set width and height:
    if(bIsMenuBar)
    {
      lpMIS->itemWidth = size.cx ;
    }
    else
    {
      lpMIS->itemWidth = m_iconX + size.cx + m_iconX + GAP;
    }

    // Check the Key-Shortcut
    if(_tcsstr(lpstrText, _T("\t")) != NULL)
      lpMIS->itemWidth += 15;

    int temp = GetSystemMetrics(SM_CYMENU);
    lpMIS->itemHeight = (temp>(m_iconY+4)) ? temp : (m_iconY+4);
    
    m_fontMenu.DeleteObject();

    // set status bar as appropriate
    UINT nItemID = (lpMIS->itemID & 0xFFF0);
    // Special case for system menu
    if (nItemID>=SC_SIZE && nItemID<=SC_HOTKEY) 
    {
      BOOL bGetNext = FALSE;
      // search the actual menu item
      for (int j=0;j<m_MenuList.GetUpperBound();++j)
      {
        CNewMenuItemData* pTemp = m_MenuList[j];
        if(pTemp==pMenuData || bGetNext==TRUE)
        {
          bGetNext = TRUE;
          pTemp = m_MenuList[j+1];
          if(pTemp->m_nID)
          {
            lpMIS->itemData = (ULONG_PTR)pTemp;
            lpMIS->itemID = pTemp->m_nID; 
            UINT nOrgWidth = lpMIS->itemWidth;
            MeasureItem_OldStyle(lpMIS,bIsMenuBar);
            // Restore old values
            lpMIS->itemData = (ULONG_PTR)pMenuData;
            lpMIS->itemID = pMenuData->m_nID;
            lpMIS->itemWidth = max(lpMIS->itemWidth,nOrgWidth);
            break;
          }
        }
      }
      lpMIS->itemHeight = temp;
    } 
  }
}
void CNewMenu::MeasureItem_WinXP( LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenuBar )
{
  ASSERT(lpMIS->itemData);
  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpMIS->itemData);

  UINT state = pMenuData->m_nFlags;
  if(state & MF_SEPARATOR)
  {
    if(pMenuData->m_nTitleFlags&MFT_TITLE)
    {
      // DC of the desktop
      CClientDC myDC(NULL);

      CFont font;
      font.CreatePointFont(160,_T("Arial"));
      CFont* pOldFont = myDC.SelectObject (&font);
      LPCTSTR lpstrText = pMenuData->GetString();
      SIZE size;
      VERIFY(::GetTextExtentPoint32(myDC.m_hDC,lpstrText,(int)_tcslen(lpstrText),&size));
      // Select old font in
      myDC.SelectObject(pOldFont);  

      if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
      {
        lpMIS->itemWidth = size.cy*3/4 -GetSystemMetrics(SM_CXMENUCHECK);
        // Don't make the menu higher than menuitems in it
        lpMIS->itemHeight = 0;
        if(pMenuData->m_nTitleFlags&MFT_LINE)
        {
          lpMIS->itemWidth += 6;
        }
      }
      else
      {
        lpMIS->itemWidth = size.cx*3/4;
        lpMIS->itemHeight = size.cy*3/4;
        if(pMenuData->m_nTitleFlags&MFT_LINE)
        {
          lpMIS->itemHeight += 6;
        }
      }
    }
    else
    {
      lpMIS->itemHeight = 3;
    }
  }
  else
  {
    CFont m_fontMenu;
    LOGFONT m_lf;
    ZeroMemory ((PVOID) &m_lf,sizeof (LOGFONT));
    NONCLIENTMETRICS nm;
    nm.cbSize = sizeof (NONCLIENTMETRICS);
    VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, nm.cbSize,&nm,0)); 
    m_lf =  nm.lfMenuFont;
    // Default selection?
    if(state&ODS_DEFAULT)
    {
      // Make the font bold
      m_lf.lfWeight = FW_BOLD;
    }

    m_fontMenu.CreateFontIndirect (&m_lf);
    
    // DC of the desktop
    CClientDC myDC(NULL);
    
    // Select menu font in...    
    CFont* pOldFont = myDC.SelectObject (&m_fontMenu);
    //Get pointer to text SK
    const LPCTSTR lpstrText = pMenuData->GetString();
    SIZE size;
    VERIFY(::GetTextExtentPoint32(myDC.m_hDC,lpstrText,(int)_tcslen(lpstrText),&size));
    // Select old font in
    myDC.SelectObject(pOldFont);  
  
    // Set width and height:
    if(bIsMenuBar)
    {
      lpMIS->itemWidth = size.cx ;
    }
    else
    {
      lpMIS->itemWidth = m_iconX + size.cx + m_iconX + GAP;
    }

    // Check the Key-Shortcut
    if(_tcsstr(lpstrText, _T("\t")) != NULL)
      lpMIS->itemWidth += 15;

    int temp = GetSystemMetrics(SM_CYMENU);
    lpMIS->itemHeight = temp>m_iconY+8 ? temp : m_iconY+8;
    
    m_fontMenu.DeleteObject();

    // set status bar as appropriate
    UINT nItemID = (lpMIS->itemID & 0xFFF0);
    // Special case for system menu
    if (nItemID>=SC_SIZE && nItemID<=SC_HOTKEY) 
    {
      BOOL bGetNext = FALSE;
      // search the actual menu item
      for (int j=0;j<m_MenuList.GetUpperBound();++j)
      {
        CNewMenuItemData* pTemp = m_MenuList[j];
        if(pTemp==pMenuData || bGetNext==TRUE)
        {
          bGetNext = TRUE;
          pTemp = m_MenuList[j+1];
          if(pTemp->m_nID)
          {
            lpMIS->itemData = (ULONG_PTR)pTemp;
            lpMIS->itemID = pTemp->m_nID; 
            UINT nOrgWidth = lpMIS->itemWidth;
            MeasureItem_WinXP(lpMIS,bIsMenuBar);
            // Restore old values
            lpMIS->itemData = (ULONG_PTR)pMenuData;
            lpMIS->itemID = pMenuData->m_nID;
            lpMIS->itemWidth = max(lpMIS->itemWidth,nOrgWidth);
            break;
          }
        }
      }
      lpMIS->itemHeight = temp;
    } 
  }
}

void CNewMenu::SetIconSize (int width, int height)
{
  m_iconX = width;
  m_iconY = height;
}

BOOL CNewMenu::AppendODMenu(LPCTSTR lpstrText,UINT nFlags,UINT nID,int nIconNormal)
{
  // Add the MF_OWNERDRAW flag if not specified:
  if(!nID)
  {
    if(nFlags&MF_BYPOSITION)
      nFlags=MF_SEPARATOR|MF_OWNERDRAW|MF_BYPOSITION;
    else
      nFlags=MF_SEPARATOR|MF_OWNERDRAW;
  }
  else if(!(nFlags & MF_OWNERDRAW))nFlags |= MF_OWNERDRAW;
  
  if(nFlags & MF_POPUP)
  {
    m_AllSubMenus.Add(UIntToHMenu(nID));
    m_SubMenus.Add(UIntToHMenu(nID));
  }
  
  CNewMenuItemData *mdata = new CNewMenuItemData;
  m_MenuList.Add(mdata);
  mdata->SetString(lpstrText);
  
  mdata->m_nMenuIconNormal = nIconNormal;
  mdata->m_nxOffset=-1;
  if(nIconNormal>=0)
  {
    mdata->m_nxOffset=0;
    LoadFromToolBar(nID,nIconNormal,mdata->m_nxOffset);
    if(mdata->m_pBitmap)
      mdata->m_pBitmap->DeleteImageList();
    else
      mdata->m_pBitmap=new(CImageList);
    mdata->m_pBitmap->Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);
    if(!AddBitmapToImageList(mdata->m_pBitmap,nIconNormal))
    {
      mdata->m_pBitmap->DeleteImageList();
      delete mdata->m_pBitmap;
      mdata->m_pBitmap=NULL;
      mdata->m_nMenuIconNormal = nIconNormal = -1;
      mdata->m_nxOffset = -1;
    }
  }
  mdata->m_nFlags = nFlags;
  mdata->m_nID = nID;
  return(CMenu::AppendMenu(nFlags, nID, (LPCTSTR)mdata));
}

BOOL CNewMenu::AppendODMenu(LPCTSTR lpstrText,UINT nFlags,UINT nID,
                           CImageList *il,int xoffset)
{
  // Add the MF_OWNERDRAW flag if not specified:
  if(!nID)
  {
    if(nFlags&MF_BYPOSITION)
      nFlags=MF_SEPARATOR|MF_OWNERDRAW|MF_BYPOSITION;
    else 
      nFlags=MF_SEPARATOR|MF_OWNERDRAW;
  }
  else if(!(nFlags & MF_OWNERDRAW))
    nFlags |= MF_OWNERDRAW;
  
  if(nFlags & MF_POPUP)
  {
    m_AllSubMenus.Add(UIntToHMenu(nID));
    m_SubMenus.Add(UIntToHMenu(nID));
  }

  CNewMenuItemData* mdata = new CNewMenuItemData;
  m_MenuList.Add(mdata);
  mdata->SetString(lpstrText);

  if(il)
  {
    mdata->m_nMenuIconNormal = 0;
    mdata->m_nxOffset=0;
    if(mdata->m_pBitmap)
      mdata->m_pBitmap->DeleteImageList();
    else 
      mdata->m_pBitmap=new(CImageList);
    
    ImageListDuplicate(il,xoffset,mdata->m_pBitmap);
  }
  else
  {
    mdata->m_nMenuIconNormal = -1;
    mdata->m_nxOffset = -1;
  }
  mdata->m_nFlags = nFlags;
  mdata->m_nID = nID;
  return(CMenu::AppendMenu(nFlags, nID, (LPCTSTR)mdata));
}

BOOL CNewMenu::InsertODMenu(UINT nPosition,LPCTSTR lpstrText,UINT nFlags,UINT nID,
                           int nIconNormal)
{
  if(!(nFlags & MF_BYPOSITION))
  {
    int iPosition =0;
    CNewMenu* pMenu = FindMenuOption(nPosition,iPosition);
    if(pMenu)
    {
      return(pMenu->InsertODMenu(iPosition,lpstrText,nFlags|MF_BYPOSITION,nID,nIconNormal));
    }
    else 
      return(FALSE);
  }
  
  if(!nID)
    nFlags=MF_SEPARATOR|MF_OWNERDRAW|MF_BYPOSITION;
  else if(!(nFlags & MF_OWNERDRAW))
    nFlags |= MF_OWNERDRAW;
  
  if(nFlags & MF_POPUP)
  {
    m_AllSubMenus.Add(UIntToHMenu(nID));
    m_SubMenus.InsertAt(nPosition,UIntToHMenu(nID));
  }

  //Stephane Clog suggested adding this, believe it or not it's in the help 
  if(nPosition==(UINT)-1)
    nPosition=GetMenuItemCount();

  CNewMenuItemData *mdata = new CNewMenuItemData;
  m_MenuList.InsertAt(nPosition,mdata);
  mdata->SetString(lpstrText);
  
  mdata->m_nMenuIconNormal = nIconNormal;
  mdata->m_nxOffset=-1;
  if(nIconNormal>=0)
  {
    mdata->m_nxOffset=0;
    LoadFromToolBar(nID,nIconNormal,mdata->m_nxOffset);
    if(mdata->m_pBitmap)
      mdata->m_pBitmap->DeleteImageList();
    else
      mdata->m_pBitmap=new(CImageList);

    mdata->m_pBitmap->Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);
    if(!AddBitmapToImageList(mdata->m_pBitmap,nIconNormal))
    {
      mdata->m_pBitmap->DeleteImageList();
      delete mdata->m_pBitmap;
      mdata->m_pBitmap=NULL;
      mdata->m_nMenuIconNormal = nIconNormal = -1;
      mdata->m_nxOffset = -1;
    }
  }
  mdata->m_nFlags = nFlags;
  mdata->m_nID = nID;
  return(CMenu::InsertMenu(nPosition,nFlags,nID,(LPCTSTR)mdata));
}

BOOL CNewMenu::InsertODMenu(UINT nPosition,LPCTSTR lpstrText,UINT nFlags,UINT nID,
                           CImageList *il,int xoffset)
{
  if(!(nFlags & MF_BYPOSITION))
  {
    int iPosition =0;
    CNewMenu* pMenu = FindMenuOption(nPosition,iPosition);
    if(pMenu)
    {
      return(pMenu->InsertODMenu(iPosition,lpstrText,nFlags|MF_BYPOSITION,nID,il,xoffset));
    }
    else 
      return(FALSE);
  }
  
  if(!nID)
    nFlags=MF_SEPARATOR|MF_OWNERDRAW|MF_BYPOSITION;
  else if(!(nFlags & MF_OWNERDRAW))
    nFlags |= MF_OWNERDRAW;
  
  if(nFlags & MF_POPUP)
  {
    m_AllSubMenus.Add(UIntToHMenu(nID));
    m_SubMenus.InsertAt(nPosition,UIntToHMenu(nID));
  }
  
  //Stephane Clog suggested adding this, believe it or not it's in the help 
  if(nPosition==(UINT)-1)
    nPosition=GetMenuItemCount();
  
  CNewMenuItemData *mdata = new CNewMenuItemData;
  m_MenuList.InsertAt(nPosition,mdata);
  mdata->SetString(lpstrText);

  if(il)
  {
    mdata->m_nMenuIconNormal = 0;
    mdata->m_nxOffset=0;
    if(mdata->m_pBitmap)
      mdata->m_pBitmap->DeleteImageList();
    else
      mdata->m_pBitmap=new(CImageList);
    ImageListDuplicate(il,xoffset,mdata->m_pBitmap);
  }
  else
  {
    mdata->m_nMenuIconNormal = -1;
    mdata->m_nxOffset = -1;
  }
  mdata->m_nFlags = nFlags;
  mdata->m_nID = nID;
  return(CMenu::InsertMenu(nPosition,nFlags,nID,(LPCTSTR)mdata));
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText,UINT nID,int nIconNormal)
{
  int nLoc;
  CNewMenuItemData *mdata;
  CArray<CNewMenu*,CNewMenu*>newSubs;
  CArray<int,int&>newLocs;

  // Find the old CNewMenuItemData structure:
  CNewMenu *psubmenu = FindMenuOption(nID,nLoc);
  do {
    if(psubmenu && nLoc>=0)
      mdata = psubmenu->m_MenuList[nLoc];
    else
    {
      // Create a new CNewMenuItemData structure:
      mdata = new CNewMenuItemData;
      m_MenuList.Add(mdata);
    }

    ASSERT(mdata);
    if(lpstrText)
      mdata->SetString(lpstrText);
    mdata->m_nMenuIconNormal = nIconNormal;
    mdata->m_nxOffset=-1;
    if(nIconNormal>=0)
    {
      mdata->m_nxOffset=0;
      LoadFromToolBar(nID,nIconNormal,mdata->m_nxOffset);
      if(mdata->m_pBitmap)
        mdata->m_pBitmap->DeleteImageList();
      else
        mdata->m_pBitmap=new CImageList;

      mdata->m_pBitmap->Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);
      if(!AddBitmapToImageList(mdata->m_pBitmap,nIconNormal))
      {
        mdata->m_pBitmap->DeleteImageList();
        delete mdata->m_pBitmap;
        mdata->m_pBitmap=NULL;
        mdata->m_nMenuIconNormal = nIconNormal = -1;
        mdata->m_nxOffset = -1;
      }
    }
    mdata->m_nFlags &= ~(MF_BYPOSITION);
    mdata->m_nFlags |= MF_OWNERDRAW;
    mdata->m_nID = nID;
    newSubs.Add(psubmenu);
    newLocs.Add(nLoc);
    if(psubmenu && nLoc>=0)
      psubmenu = FindAnotherMenuOption(nID,nLoc,newSubs,newLocs);
    else 
      psubmenu=NULL;
  
  }while(psubmenu);

  return (CMenu::ModifyMenu(nID,mdata->m_nFlags,nID,(LPCTSTR)mdata));
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText,UINT nID,CImageList *pil,int xoffset)
{
  int nLoc;
  CNewMenuItemData *mdata;
  CArray<CNewMenu*,CNewMenu*>newSubs;
  CArray<int,int&>newLocs;
  
  // Find the old CNewMenuItemData structure:
  CNewMenu *psubmenu = FindMenuOption(nID,nLoc);
  do {
    if(psubmenu && nLoc>=0)
    {
      mdata = psubmenu->m_MenuList[nLoc];
    }
    else
    {
      // Create a new CNewMenuItemData structure:
      mdata = new CNewMenuItemData;
      m_MenuList.Add(mdata);
    }

    ASSERT(mdata);
    if(lpstrText)
    {
      mdata->SetString(lpstrText);
    }

    if(pil)
    {
      mdata->m_nMenuIconNormal = 0;
      mdata->m_nxOffset=0;
      if(mdata->m_pBitmap)
        mdata->m_pBitmap->DeleteImageList();
      else 
        mdata->m_pBitmap=new(CImageList);

      ImageListDuplicate(pil,xoffset,mdata->m_pBitmap);
      int x=0;
      int y=0;
      if(psubmenu && ImageList_GetIconSize(pil->m_hImageList,&x,&y))
      {
        // Correct the size of the menuitem
        psubmenu->m_iconX = max(psubmenu->m_iconX,x);
        psubmenu->m_iconY = max(psubmenu->m_iconY,y);
      }
    }
    else
    {
      mdata->m_nMenuIconNormal = -1;
      mdata->m_nxOffset = -1;
    }
    mdata->m_nFlags &= ~(MF_BYPOSITION);
    mdata->m_nFlags |= MF_OWNERDRAW;
    mdata->m_nID = nID;
    newSubs.Add(psubmenu);
    newLocs.Add(nLoc);
    if(psubmenu && nLoc>=0)
      psubmenu = FindAnotherMenuOption(nID,nLoc,newSubs,newLocs);
    else 
      psubmenu=NULL;
  } while(psubmenu);

  return (CMenu::ModifyMenu(nID,mdata->m_nFlags,nID,(LPCTSTR)mdata));
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText,UINT nID,CBitmap *bmp)
{
  if (bmp)
  {
    CImageList temp;
    temp.Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);
    
    temp.Add(bmp,GetBitmapBackground());

    return ModifyODMenu(lpstrText,nID,&temp,0);
  }
  return ModifyODMenu(lpstrText,nID,NULL,0);
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText,UINT nID,COLORREF fill,COLORREF border,int hatchstyle)
{
  // Get device context
  CClientDC DC(0);
  CSize bitmap_size(m_iconX,m_iconY);
  CBitmap bmp;
  ColorBitmap(&DC,bmp,bitmap_size,fill,border,hatchstyle);  
  return ModifyODMenu(lpstrText,nID,&bmp);
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText,LPCTSTR OptionText, int nIconNormal)
{
  int nIndex = 0;
  CNewMenu* pOptionMenu = FindMenuOption(OptionText,nIndex);

  if(pOptionMenu!=NULL && nIndex>=0)
  {
    CNewMenuItemData* pmdata = pOptionMenu->m_MenuList[nIndex];
    if(lpstrText)
    {
      pmdata->SetString(lpstrText);
    }
    pmdata->m_nMenuIconNormal = nIconNormal;
    pmdata->m_nxOffset=-1;
    if(nIconNormal>=0)
    {
      pmdata->m_nxOffset=0;
      if(pmdata->m_pBitmap)
        pmdata->m_pBitmap->DeleteImageList();
      else
        pmdata->m_pBitmap=new(CImageList);

      if (!m_bDynIcons)
      {
        CBitmap temp;
        // Try to load the bitmap for getting dimension
        if(temp.LoadBitmap(nIconNormal))
        {
          BITMAP bitmap;
          ZeroMemory(&bitmap,sizeof(bitmap));
          if(temp.GetBitmap(&bitmap))
          {
            pOptionMenu->m_iconX = max(pOptionMenu->m_iconX,bitmap.bmWidth);
            pOptionMenu->m_iconY = max(pOptionMenu->m_iconY,bitmap.bmHeight);
          }
        }
      }

      pmdata->m_pBitmap->Create(pOptionMenu->m_iconX,pOptionMenu->m_iconY,ILC_COLORDDB|ILC_MASK,1,1);

      if(!AddBitmapToImageList(pmdata->m_pBitmap,nIconNormal))
      {
        pmdata->m_pBitmap->DeleteImageList();
        delete pmdata->m_pBitmap;
        pmdata->m_pBitmap=NULL;
        pmdata->m_nMenuIconNormal = nIconNormal = -1;
        pmdata->m_nxOffset = -1;
      }
    }
    return TRUE;
  }
  return FALSE;
}

CNewMenuItemData* CNewMenu::NewODMenu(UINT pos,UINT nFlags,UINT nID,LPCTSTR string)
{
  CNewMenuItemData* mdata;

  mdata = new CNewMenuItemData;
  mdata->m_nMenuIconNormal = -1;
  mdata->m_nxOffset=-1;
  mdata->m_nFlags = nFlags;
  mdata->m_nID = nID;
  mdata->SetString (string);

  //  if(nFlags & MF_POPUP)m_AllSubMenus.Add(UIntToHMenu(nID));

  if (nFlags&MF_OWNERDRAW)
  {
    ASSERT(!(nFlags&MF_STRING));
    ModifyMenu(pos,nFlags,nID,(LPCTSTR)mdata);
  }
  else if (nFlags&MF_BITMAP)
  {
    ModifyMenu(pos,nFlags,nID,(CBitmap*)string);
  }
  else if (nFlags&MF_SEPARATOR)
  {
    ASSERT(nFlags&MF_SEPARATOR);
    ModifyMenu(pos,nFlags,nID);
  }
  else // (nFlags&MF_STRING)
  {
    ASSERT(!(nFlags&MF_OWNERDRAW));
    ModifyMenu(pos,nFlags,nID,mdata->GetString());
  }
  
  return(mdata);
};

BOOL CNewMenu::LoadToolBars(const UINT* arID, int n)
{
  ASSERT(arID);
  BOOL returnflag=TRUE;
  for(int i=0;i<n;++i)
  {
    if(!LoadToolBar(arID[i]))
      returnflag=FALSE;
  }
  return(returnflag);
}

struct CToolBarData
{
  WORD wVersion;
  WORD wWidth;
  WORD wHeight;
  WORD wItemCount;
  //WORD aItems[wItemCount]

  WORD* items()
    { return (WORD*)(this+1); }
};

BOOL CNewMenu::LoadToolBar(LPCTSTR lpszResourceName)
{
  ASSERT_VALID(this);
  ASSERT(lpszResourceName != NULL);

  // determine location of the bitmap in resource
  HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, RT_TOOLBAR);
  HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
  if (hRsrc == NULL)
    return FALSE;

  HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
  if (hGlobal == NULL)
    return FALSE;

  CToolBarData* pData = (CToolBarData*)LockResource(hGlobal);
  if (pData == NULL)
    return FALSE;
  ASSERT(pData->wVersion == 1);

  CImageList myImageList;
  myImageList.Create(pData->wWidth,pData->wHeight,ILC_COLORDDB|ILC_MASK,0,10);
  // load bitmap now that sizes are known by the toolbar control
  BOOL bResult = AddBitmapToImageList(&myImageList,(UINT)(UINT_PTR)lpszResourceName);
  
  if (bResult)
  {
    m_iconX = max(pData->wWidth,m_iconX);
    m_iconY = max(pData->wHeight,m_iconY);

    int xoffset=0;
    for (int i = 0; i < pData->wItemCount; i++)
    { 
      UINT nID = pData->items()[i];
      if (nID)
      {
        ModifyODMenu(NULL,nID,&myImageList,xoffset++);
      }
    }
  }

  UnlockResource(hGlobal);
  FreeResource(hGlobal);

  return bResult;
}

struct SToolInfo
{
  WORD wBitmapID;
  WORD wWidth;
  WORD wHeight;

  WORD* ids(){ return (WORD*)(this+1); }
};

BOOL CNewMenu::LoadToolBar(WORD* pToolInfo, COLORREF crTransparent)
{
  COLORREF oldColor = m_bitmapBackground;
  if(crTransparent!=CLR_NONE)
  { 
    oldColor = SetBitmapBackground(crTransparent);
  }  
  SToolInfo* pInfo = (SToolInfo*)pToolInfo; 
  CImageList myImageList;
  myImageList.Create(pInfo->wWidth,pInfo->wHeight,ILC_COLORDDB|ILC_MASK,0,10);
  // load bitmap now that sizes are known by the toolbar control
  BOOL bResult = AddBitmapToImageList(&myImageList,pInfo->wBitmapID);
  
  if (bResult)
  {
    WORD* pID = pInfo->ids();
    int nIndex=0;
    while(*pID)
    {
      ModifyODMenu(NULL,*pID++,&myImageList,nIndex++);
    }
  }
  SetBitmapBackground(oldColor);
  return bResult;
}

BOOL CNewMenu::LoadToolBar(UINT nToolBar)
{
  return LoadToolBar((LPCTSTR)(UINT_PTR)nToolBar);
}

BOOL CNewMenu::LoadFromToolBar(UINT nID,UINT nToolBar,int& xoffset)
{
  int xset,offset;
  UINT nStyle;
  BOOL returnflag=FALSE;
  CToolBar bar;

  CWnd* pWnd = AfxGetMainWnd();
  if (pWnd == NULL)
  {
    pWnd = CWnd::GetDesktopWindow();
  }
  bar.Create(pWnd);

  if(bar.LoadToolBar(nToolBar))
  {
    offset=bar.CommandToIndex(nID);
    if(offset>=0)
    {
      bar.GetButtonInfo(offset,nID,nStyle,xset);
      if(xset>0)
        xoffset=xset;
      returnflag=TRUE;
    }
  }
  return returnflag;
}

// O.S.
CNewMenuItemData* CNewMenu::FindMenuItem(UINT nID)
{
  CNewMenuItemData *pData = NULL;
  int i;
  
  for(i = 0; i <= m_MenuList.GetUpperBound(); i++)
  {
    if (m_MenuList[i]->m_nID == nID)
    {
      pData = m_MenuList[i];
      break;
    }
  }
  if (!pData)
  {
    int loc;
    CNewMenu *pMenu = FindMenuOption(nID, loc);
    ASSERT(pMenu != this);
    if (loc >= 0)
    {
      return pMenu->FindMenuItem(nID);
    }
  }
  return pData;
}


CNewMenu* CNewMenu::FindAnotherMenuOption(int nId,int& nLoc,
                                          CArray<CNewMenu*,CNewMenu*>&newSubs,
                                          CArray<int,int&>&newLocs)
{
  int i,numsubs,j;
  CNewMenu *psubmenu,*pgoodmenu;
  BOOL foundflag;
  
  for(i=0;i<(int)(GetMenuItemCount());++i)
  {
    psubmenu = DYNAMIC_DOWNCAST(CNewMenu,GetSubMenu(i));
    if(psubmenu)
    {
      pgoodmenu=psubmenu->FindAnotherMenuOption(nId,nLoc,newSubs,newLocs);
      if(pgoodmenu)
        return(pgoodmenu);
    }
    else if(nId==(int)GetMenuItemID(i))
    {
      numsubs = (int)newSubs.GetSize();
      foundflag=TRUE;
      for(j=0;j<numsubs;++j)
      {
        if(newSubs[j]==this&&newLocs[j]==i)
        {
          foundflag=FALSE;
          break;
        }
      }
      if(foundflag)
      {
        nLoc=i;
        return(this);
      }
    }
  }
  nLoc = -1;
  return(NULL);
}

CNewMenu* CNewMenu::FindMenuOption(int nId, int& nLoc)
{
  int i;
  CNewMenu *psubmenu,*pgoodmenu;
  
  for(i=0;i<(int)(GetMenuItemCount());++i)
  {
    psubmenu = DYNAMIC_DOWNCAST(CNewMenu,GetSubMenu(i));
    if(psubmenu)
    {
      pgoodmenu=psubmenu->FindMenuOption(nId,nLoc);
      if(pgoodmenu)
        return(pgoodmenu);
    }
    else if(nId==(int)GetMenuItemID(i))
    {
      nLoc=i;
      return(this);
    }
  }
  nLoc = -1;
  return NULL;
}

CNewMenu* CNewMenu::FindMenuOption(LPCTSTR lpstrText, int& nLoc)
{ 
  int i;
  // First look for all item text.
  for(i=0;i<=(int)m_MenuList.GetUpperBound();++i)
  {  
    if(m_MenuList[i]->m_szMenuText.Compare(lpstrText)==NULL)
    {
      nLoc = i;
      return this;
    }
  }
  CNewMenu* psubmenu;
  // next, look in all submenus
  for(i=0; i<(int)(GetMenuItemCount());++i)
  {
    psubmenu = DYNAMIC_DOWNCAST(CNewMenu,GetSubMenu(i));
    if(psubmenu)
    {
      psubmenu = psubmenu->FindMenuOption(lpstrText,nLoc);
      if(psubmenu)
      {
        return psubmenu;
      }
    }
  }
  nLoc = -1;
  return NULL;
} 

BOOL CNewMenu::LoadMenu(HMENU hMenu)
{
  if(!::IsMenu(hMenu) || !Attach(hMenu))
  {
    return FALSE;
  } 
  for(int i=0;i<(int)(GetMenuItemCount());++i)
  { 
    HMENU hSubMenu = ::GetSubMenu(m_hMenu,i);
    if(hSubMenu)
    {
      CNewMenu* pMenu = new CNewMenu(m_hMenu);
      m_SubMenus.Add(hSubMenu);
      pMenu->LoadMenu(hSubMenu); 
    }
  }  
  SynchronizeMenu();
  return TRUE;
}

BOOL CNewMenu::LoadMenu(int nResource)
{
  return(CNewMenu::LoadMenu(MAKEINTRESOURCE(nResource)));
}

BOOL CNewMenu::LoadMenu(LPCTSTR lpszResourceName)
{
  ASSERT_VALID(this);
  ASSERT(lpszResourceName != NULL);
  
  // Find the Menu Resource:
  HINSTANCE m_hInst = AfxFindResourceHandle(lpszResourceName,RT_MENU);
  HRSRC hRsrc = ::FindResource(m_hInst,lpszResourceName,RT_MENU);
  if(hRsrc == NULL)
    return FALSE;
  
  // Load the Menu Resource:
  HGLOBAL hGlobal = LoadResource(m_hInst, hRsrc);
  if(hGlobal == NULL)
    return FALSE;
  
  // Attempt to create us as a menu...  
  if(!CMenu::CreateMenu())
    return FALSE;

  // Get Item template Header, and calculate offset of MENUITEMTEMPLATES
  MENUITEMTEMPLATEHEADER* pTpHdr= (MENUITEMTEMPLATEHEADER*)LockResource(hGlobal);
  BYTE* pTp=(BYTE*)pTpHdr +  (sizeof(MENUITEMTEMPLATEHEADER) + pTpHdr->offset);
  
  MENUITEMTEMPLATE* pTemplate = (MENUITEMTEMPLATE*)pTp;
  // Variables needed during processing of Menu Item Templates:
  
  // ID of the Menu Item
  WORD dwID  = 0;
  CString  szCaption;
  // Popup menu stack
  CTypedPtrArray<CPtrArray, CNewMenu*>  m_Stack;
  // Popup menu stack
  CArray<BOOL,BOOL>  m_StackEnd;
  // Add it to this...
  m_Stack.Add(this);
  m_StackEnd.Add(FALSE);
  
  do{
    WORD wFlags = pTemplate->mtOption; 
    // Obtain Flags and (if necessary), the ID...
    if(!(wFlags & MF_POPUP))
    {
      dwID = pTemplate->mtID;
      #ifdef UNICODE
        szCaption = pTemplate->mtString;
      #else
        szCaption.Format("%S",pTemplate->mtString);
      #endif 
          
      pTemplate = (MENUITEMTEMPLATE*)(DWORD_PTR)((DWORD)(DWORD_PTR)(pTemplate+1) +
                                      wcslen(pTemplate->mtString)*sizeof(wchar_t));
    }
    else
    {
      dwID = 0;

      #ifdef UNICODE
        szCaption = (wchar_t*)&pTemplate->mtID;
      #else
        szCaption.Format("%S",(wchar_t*)&pTemplate->mtID);
      #endif 
          
      pTemplate = (MENUITEMTEMPLATE*)(DWORD_PTR)((DWORD)(DWORD_PTR)(pTemplate+1) +
                                      wcslen(pTemplate->mtString)*sizeof(wchar_t));
    }
    // Handle popup menus first....
    if(wFlags & MF_POPUP)
    {
      if(wFlags & MF_END)
      {
        m_StackEnd.SetAt(m_Stack.GetUpperBound(),TRUE);
        wFlags &= ~MF_END;
      }

      CNewMenu* pParent = m_Stack[m_Stack.GetUpperBound()];
      CNewMenu* pSubMenu = new CNewMenu(pParent->m_hMenu);

      pSubMenu->m_unselectcheck=m_unselectcheck;
      pSubMenu->m_selectcheck=m_selectcheck;
      pSubMenu->checkmaps=checkmaps;
      pSubMenu->checkmapsshare=TRUE;
      pSubMenu->CreatePopupMenu();

      // Append it to the top of the stack:
      pParent->AppendODMenu(szCaption,wFlags,HMenuToUInt(pSubMenu->m_hMenu), -1);
      m_Stack.Add(pSubMenu);
      m_StackEnd.Add(FALSE);
    }
    else
    {
      m_Stack[m_Stack.GetUpperBound()]->AppendODMenu(szCaption,wFlags&~MF_END,dwID,-1);

      if(wFlags & MF_END)
        m_StackEnd.SetAt(m_Stack.GetUpperBound(),TRUE);

      for(int j=(int)m_Stack.GetUpperBound(); j>=0 && m_StackEnd.GetAt(j) ; --j)
      {
        m_Stack.RemoveAt(j);
        m_StackEnd.RemoveAt(j);
      }
    }
  }
  while(m_Stack.GetUpperBound() != -1);
  return(TRUE);
}

void CNewMenu::LoadCheckmarkBitmap(int unselect, int select)
{
  if(unselect>0 && select>0)
  {
    m_selectcheck=select;
    m_unselectcheck=unselect;
    if(checkmaps)
      checkmaps->DeleteImageList();
    else
      checkmaps=new(CImageList);

    checkmaps->Create(m_iconX,m_iconY,ILC_MASK,2,1);
    BOOL flag1=AddBitmapToImageList(checkmaps,unselect);
    BOOL flag2=AddBitmapToImageList(checkmaps,select);

    if(!flag1||!flag2)
    {
      checkmaps->DeleteImageList();
      delete checkmaps;
      checkmaps=NULL;
    }
  }
}

BOOL CNewMenu::GetMenuText(UINT id, CString& string, UINT nFlags/*= MF_BYPOSITION*/)
{
  BOOL returnflag=FALSE;

  if(MF_BYPOSITION&nFlags)
  {
    UINT numMenuItems = (int)m_MenuList.GetUpperBound();
    if(id<=numMenuItems)
    {
      string=m_MenuList[id]->GetString();
      returnflag=TRUE;
    }
  }
  else
  {
    int uiLoc;
    CNewMenu* pMenu = FindMenuOption(id,uiLoc);
    if(NULL!=pMenu)
    {
      returnflag = pMenu->GetMenuText(uiLoc,string);
    }
  }
  return returnflag;
}

CNewMenuItemData *CNewMenu::FindMenuList(UINT nID)
{
  for(int i=0;i<=m_MenuList.GetUpperBound();++i)
  {
    if(m_MenuList[i]->m_nID==nID && !m_MenuList[i]->m_nSyncFlag)
    {
      m_MenuList[i]->m_nSyncFlag=1;
      return(m_MenuList[i]);
    }
  }
  return(NULL);
}

void CNewMenu::InitializeMenuList(int value)
{
  for(int i=0;i<=m_MenuList.GetUpperBound();++i)
  {
    m_MenuList[i]->m_nSyncFlag=value;
  }
}

void CNewMenu::DeleteMenuList()
{
  for(int i=0;i<=m_MenuList.GetUpperBound();++i)
  {
    if(!m_MenuList[i]->m_nSyncFlag)
    {
      delete m_MenuList[i];
    }
  }
}

void CNewMenu::SynchronizeMenu()
{
  CTypedPtrArray<CPtrArray, CNewMenuItemData*> temp;
  CNewMenuItemData *mdata;
  CString string;
  UINT submenu,nID=0,state,j;

  InitializeMenuList(0);
  for(j=0;j<GetMenuItemCount();++j)
  {
    mdata=NULL;
    state=GetMenuState(j,MF_BYPOSITION);

    if(state&MF_POPUP)
    {
      submenu=HMenuToUInt(GetSubMenu(j)->m_hMenu);
      mdata=FindMenuList(submenu);
      GetMenuString(j,string,MF_BYPOSITION);

      if(!mdata)
      {
        mdata=NewODMenu(j,(state&0xFF)|MF_BYPOSITION|MF_POPUP|MF_OWNERDRAW,submenu,string);
      }
      else if(!string.IsEmpty ())
      { 
        mdata->SetString(string);  
      }
    }
    else if(state&MF_SEPARATOR)
    {
      mdata=FindMenuList(0);
      if(!mdata)
        mdata=NewODMenu(j,state|MF_BYPOSITION|MF_SEPARATOR|MF_OWNERDRAW,0,_T(""));
      else 
        ModifyMenu(j,mdata->m_nFlags,nID,(LPCTSTR)mdata);
    }
    else
    {
      nID=GetMenuItemID(j);
      mdata=FindMenuList(nID);
      GetMenuString(j,string,MF_BYPOSITION);
      
      if(!mdata)
      {
        mdata=NewODMenu(j,state|MF_BYPOSITION|MF_OWNERDRAW,nID,string);
      }
      else
      {
        mdata->m_nFlags=state|MF_BYPOSITION|MF_OWNERDRAW;
        if(string.GetLength()>0)
        {
          mdata->SetString(string);
        }
        ModifyMenu(j,mdata->m_nFlags,nID,(LPCTSTR)mdata);
      }
    }
    if(mdata)
      temp.Add(mdata);
  }
  DeleteMenuList();
  m_MenuList.RemoveAll();
  m_MenuList.Append(temp);
  temp.RemoveAll(); 
}

void CNewMenu::OnInitMenuPopup(HWND hWnd, CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
  UNREFERENCED_PARAMETER(nIndex);
  UNREFERENCED_PARAMETER(bSysMenu);

#ifdef _TRACE_MENU_
  TRACE(_T("InitMenuPopup: 0x%lx from Wnd 0x%lx\n"),HMenuToUInt(pPopupMenu->m_hMenu),HWndToUInt(hWnd));
#endif
  CNewMenuHook::m_hLastMenu = pPopupMenu->m_hMenu;

  if(pPopupMenu->m_hMenu)
  {
    CNewMenu* pSubmenu = DYNAMIC_DOWNCAST(CNewMenu,pPopupMenu);
    if(pSubmenu)
    {
      pSubmenu->OnInitMenuPopup();
      HMENU hMenu = pSubmenu->GetParent();
      CNewMenu* pParent = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(hMenu));
      if(pParent)
      {
        pParent->m_dwOpenMenu += 1;
        if(pParent->m_dwOpenMenu==1 && !pParent->m_bIsPopupMenu)
        {
          // Redraw the menubar for the shade
          DrawMenuBar(hWnd);
        }
      }
    }
  }
}

BOOL CNewMenu::Replace(UINT nID,UINT nNewID)
{
  int nLoc=0;
  CNewMenu* pTempMenu = FindMenuOption(nID,nLoc);
  if(pTempMenu && nLoc >= 0)
  {
    CNewMenuItemData* pData = pTempMenu->m_MenuList[nLoc];
    UINT nFlags = pData->m_nFlags|MF_OWNERDRAW|MF_BYPOSITION;
    pData->m_nID = nNewID;
    pTempMenu->ModifyMenu(nLoc,nFlags,nNewID,(LPCTSTR)pData);
    return TRUE;
  }
  return FALSE;
}

void CNewMenu::OnInitMenuPopup()
{
  m_bIsPopupMenu = true;
  SynchronizeMenu();
  // Special purpose for windows XP with themes!!!
  Replace(SC_RESTORE,SC_RESTORE+1);
  Replace(SC_CLOSE,SC_CLOSE+1);
  Replace(SC_MINIMIZE,SC_MINIMIZE+1);
}

BOOL CNewMenu::OnUnInitPopupMenu()
{
  // Special purpose for windows XP with themes!!!
  // Restore old values otherwise you have disabled windowbuttons
  Replace(SC_RESTORE+1,SC_RESTORE);
  Replace(SC_CLOSE+1,SC_CLOSE);
  Replace(SC_MINIMIZE+1,SC_MINIMIZE);

  HMENU hMenu = GetParent();
  CNewMenu* pParent = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(hMenu));
  if(pParent)
  {
    pParent->m_dwOpenMenu -= 1;
    if(pParent->m_dwOpenMenu==NULL && !pParent->m_bIsPopupMenu)
    {
      return TRUE;
    }
  }
  return FALSE;
}

LRESULT CNewMenu::FindKeyboardShortcut(UINT nChar, UINT nFlags, CMenu *pMenu)
{
  UNREFERENCED_PARAMETER(nFlags);

  CNewMenu* pNewMenu = DYNAMIC_DOWNCAST(CNewMenu,pMenu);
  if(pNewMenu)
  {
    //SK: modified for Unicode correctness
    CString key(_T('&'),2);
    key.SetAt(1,(TCHAR)nChar);
    key.MakeLower();
    CString menutext;
    int menusize = (int)pNewMenu->GetMenuItemCount();
    if(menusize!=(pNewMenu->m_MenuList.GetUpperBound()+1))
    {
      pNewMenu->SynchronizeMenu();
    }
    for(int i=0;i<menusize;++i)
    {
      if(pNewMenu->GetMenuText(i,menutext))
      {
        menutext.MakeLower();
        if(menutext.Find(key)>=0)
        {
          return(MAKELRESULT(i,2));
        }
      }
    }
  }
  return NULL;
}

BOOL CNewMenu::AddBitmapToImageList(CImageList *bmplist,UINT nResourceID)
{
  // O.S.
  if (m_bDynIcons)
  {
    bmplist->Add((HICON)(UINT_PTR)nResourceID);
    return TRUE;
  }

  CBitmap mybmp;
  HBITMAP hbmp = LoadSysColorBitmap(nResourceID);
  if(hbmp)
  {
    // Object will be destroyd by destructor of CBitmap
    mybmp.Attach(hbmp);
  }
  else
  {  
    mybmp.LoadBitmap(nResourceID);
  }

  if (mybmp.m_hObject && bmplist->Add(&mybmp,GetBitmapBackground())>=0 )
  {
    return TRUE;
  }

  return FALSE;
}

COLORREF CNewMenu::SetBitmapBackground(COLORREF newColor)
{
  COLORREF oldColor = m_bitmapBackground;
  m_bitmapBackground = newColor;
  return oldColor;
}

COLORREF CNewMenu::GetBitmapBackground()
{
  if(m_bitmapBackground==CLR_DEFAULT)
    return GetSysColor(COLOR_3DFACE);

  return m_bitmapBackground;
}


// Given a toolbar, append all the options from it to this menu
// Passed a ptr to the toolbar object and the toolbar ID
// Author : Robert Edward Caldecott
void CNewMenu::AddFromToolBar(CToolBar* pToolBar, int nResourceID)
{
  for (int i = 0; i < pToolBar->GetCount(); i++) 
  {
    UINT nID = pToolBar->GetItemID(i);
    // See if this toolbar option
    // appears as a command on this
    // menu or is a separator
    if (nID == 0 || GetMenuState(nID, MF_BYCOMMAND) == 0xFFFFFFFF)
      continue; // Item doesn't exist
    UINT nStyle;
    int nImage;
    // Get the toolbar button info
    pToolBar->GetButtonInfo(i, nID, nStyle, nImage);
    // OK, we have the command ID of the toolbar
    // option, and the tollbar bitmap offset
    int nLoc;
    CNewMenuItemData* pData;
    CNewMenu *pSubMenu = FindMenuOption(nID, nLoc);
    if (pSubMenu && nLoc >= 0)
    {
      pData = pSubMenu->m_MenuList[nLoc];
    }
    else 
    {
      // Create a new CNewMenuItemData structure
      pData = new CNewMenuItemData;
      m_MenuList.Add(pData);
    }
    // Set some default structure members
    pData->m_nMenuIconNormal = nResourceID;
    pData->m_nID = nID;
    pData->m_nFlags =  MF_BYCOMMAND | MF_OWNERDRAW;
    pData->m_nxOffset = nImage;
    if (pData->m_pBitmap)
      pData->m_pBitmap->DeleteImageList();
    else
      pData->m_pBitmap = new CImageList;

    pData->m_pBitmap->Create(m_iconX, m_iconY,ILC_COLORDDB|ILC_MASK, 1, 1);

    if(!AddBitmapToImageList(pData->m_pBitmap, nResourceID))
    {
      pData->m_pBitmap->DeleteImageList();
      delete pData->m_pBitmap;
      pData->m_pBitmap=NULL;
      pData->m_nMenuIconNormal = -1;
      pData->m_nxOffset = -1;
    }    
    // Modify our menu
    ModifyMenu(nID,pData->m_nFlags,nID,(LPCTSTR)pData);
  }
}

BOOL CNewMenu::Draw3DCheckmark(CDC *pDC, const CRect& rc, HBITMAP hbmCheck, DWORD dwStyle)
{
  CRect rect(rc);
  rect.InflateRect (-1,-1);

  if (IsNewShell()) //SK: looks better on the old shell
    pDC->DrawEdge(rect, BDR_SUNKENOUTER, BF_RECT);

  rect.InflateRect (2,2);
  if (!hbmCheck)
  {
    // Checkmark
    rect.OffsetRect(1,2);
    DrawSpecialCharStyle(pDC,rect,98,dwStyle);
  }
  else
  {
    // Bullet
    DrawSpecialCharStyle(pDC,rect,105,dwStyle);
  }
  return TRUE;
}

WORD CNewMenu::NumBitmapColors(LPBITMAPINFOHEADER lpBitmap)
{
  if ( lpBitmap->biClrUsed != 0)
    return (WORD)lpBitmap->biClrUsed;
  
  switch (lpBitmap->biBitCount)
  {
  case 1:
    return 2;
  case 4:
    return 16;
  case 8:
    return 256;
  }
  return 0;
}

HBITMAP CNewMenu::LoadSysColorBitmap(int nResourceId)
{
  HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(nResourceId),RT_BITMAP);
  HRSRC hRsrc = ::FindResource(hInst,MAKEINTRESOURCE(nResourceId),RT_BITMAP);
  if (hRsrc == NULL)
    return NULL;

  // determine how many colors in the bitmap
  HGLOBAL hglb;
  if ((hglb = LoadResource(hInst, hRsrc)) == NULL)
    return NULL;
  LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)LockResource(hglb);
  if (lpBitmap == NULL)
    return NULL;
  WORD numcol = NumBitmapColors(lpBitmap);
  ::FreeResource(hglb);

  if(numcol!=16)
  {
    return(NULL);
  }
  return AfxLoadSysColorBitmap(hInst, hRsrc, FALSE);
}

BOOL CNewMenu::RemoveMenu(UINT uiId,UINT nFlags)
{
  if(MF_BYPOSITION&nFlags)
  {
    UINT uint = GetMenuState(uiId,MF_BYPOSITION);
    if(uint&MF_SEPARATOR && !(uint&MF_POPUP))
    {
      delete m_MenuList.GetAt(uiId);
      m_MenuList.RemoveAt(uiId);
    }
    else
    {
      CNewMenu* pSubMenu = (CNewMenu*) GetSubMenu(uiId);
      if(NULL==pSubMenu)
      {
        UINT uiCommandId = GetMenuItemID(uiId);
        for(int i=0;i<m_MenuList.GetSize(); i++)
        {
          if(m_MenuList[i]->m_nID==uiCommandId)
          {
            delete m_MenuList.GetAt(i);
            m_MenuList.RemoveAt(i);
            break;
          }
        }
      }
      else
      {
        int numSubMenus = (int)m_SubMenus.GetUpperBound();
        for(int m = numSubMenus; m >= 0; m--)
        {
          if(m_SubMenus[m]==pSubMenu->m_hMenu)
          {
            int numAllSubMenus = (int)m_AllSubMenus.GetUpperBound();
            for(int n = numAllSubMenus; n>= 0; n--)
            {
              if(m_AllSubMenus[n]==m_SubMenus[m])
                m_AllSubMenus.RemoveAt(n);
            }
            m_SubMenus.RemoveAt(m);
          }
        }
        int num = pSubMenu->GetMenuItemCount();
        for(int i=num-1;i>=0;--i)
        {
          pSubMenu->RemoveMenu(i,MF_BYPOSITION);
        }
        for(i=(int)m_MenuList.GetUpperBound();i>=0;i--)
        {
          if(m_MenuList[i]->m_nID==HMenuToUInt(pSubMenu->m_hMenu) )
          {
            delete m_MenuList.GetAt(i);
            m_MenuList.RemoveAt(i);
            break;
          }
        }
        delete pSubMenu;
      }
    }
  }
  else
  {
    int iPosition =0;
    CNewMenu* pMenu = FindMenuOption(uiId,iPosition);
    if(pMenu)
    {
      return pMenu->RemoveMenu(iPosition,MF_BYPOSITION);
    }
  }
  return CMenu::RemoveMenu(uiId,nFlags);
}

BOOL CNewMenu::DeleteMenu(UINT uiId,UINT nFlags)
{
  if(MF_BYPOSITION&nFlags)
  {
    UINT uint = GetMenuState(uiId,MF_BYPOSITION);
    if(uint&MF_SEPARATOR && !(uint&MF_POPUP))
    {
      delete m_MenuList.GetAt(uiId);
      m_MenuList.RemoveAt(uiId);
    }
    else
    {
      CNewMenu* pSubMenu = (CNewMenu*) GetSubMenu(uiId);
      if(NULL==pSubMenu)
      {
        UINT uiCommandId = GetMenuItemID(uiId);
        for(int i=0;i<m_MenuList.GetSize(); i++)
        {
          if(m_MenuList[i]->m_nID==uiCommandId)
          {
            delete m_MenuList.GetAt(i);
            m_MenuList.RemoveAt(i);
            break;
          }
        }
      }
      else
      {
        int numSubMenus = (int)m_SubMenus.GetUpperBound();
        for(int m = numSubMenus; m >= 0; m--)
        {
          if(m_SubMenus[m]==pSubMenu->m_hMenu)
          {
            int numAllSubMenus = (int)m_AllSubMenus.GetUpperBound();
            for(int n = numAllSubMenus; n>= 0; n--)
            {
              if(m_AllSubMenus[n]==m_SubMenus[m])
              {
                m_AllSubMenus.RemoveAt(n);
              }
            }
            m_SubMenus.RemoveAt(m);
          }
        }
        int num = pSubMenu->GetMenuItemCount();
        for(int i=num-1;i>=0;--i)
        {
          pSubMenu->DeleteMenu(i,MF_BYPOSITION);
        }
        for(i=(int)m_MenuList.GetUpperBound();i>=0;i--)
        {
          if(m_MenuList[i]->m_nID==HMenuToUInt(pSubMenu->m_hMenu) )
          {
            delete m_MenuList.GetAt(i);
            m_MenuList.RemoveAt(i);
            break;
          }
        }
        delete pSubMenu;
      }
    }
  }
  else
  {
    int iPosition =0;
    CNewMenu* pMenu = FindMenuOption(uiId,iPosition);
    if(pMenu)
    {
      pMenu->DeleteMenu(iPosition,MF_BYPOSITION);
    }
  }
  return CMenu::DeleteMenu(uiId,nFlags);
} 

BOOL CNewMenu::AppendMenu(UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,int nIconNormal)
{
  return AppendODMenu(lpszNewItem,nFlags,nIDNewItem,nIconNormal);
}

BOOL CNewMenu::AppendMenu(UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CImageList *il,int xoffset)
{
  return AppendODMenu(lpszNewItem,nFlags,nIDNewItem,il,xoffset);
}

BOOL CNewMenu::AppendMenu(UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CBitmap *bmp)
{
  if(bmp)
  {
    CImageList temp;
    temp.Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);
    temp.Add(bmp,GetBitmapBackground());

    return AppendODMenu(lpszNewItem,nFlags,nIDNewItem,&temp,0);
  }
  return AppendODMenu(lpszNewItem,nFlags,nIDNewItem,NULL,0);
}

BOOL CNewMenu::InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,int nIconNormal)
{
  return InsertODMenu(nPosition,lpszNewItem,nFlags,nIDNewItem,nIconNormal);
}

BOOL CNewMenu::InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CImageList *il,int xoffset)
{
  return InsertODMenu(nPosition,lpszNewItem,nFlags,nIDNewItem,il,xoffset);
}

BOOL CNewMenu::InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CBitmap *bmp)
{
  if(bmp)
  {
    CImageList temp;
    temp.Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);
    temp.Add(bmp,GetBitmapBackground());
    return InsertODMenu(nPosition,lpszNewItem,nFlags,nIDNewItem,&temp,0);
  }
  return InsertODMenu(nPosition,lpszNewItem,nFlags,nIDNewItem,NULL,0);
}

CNewMenu* CNewMenu::AppendODPopupMenu(LPCTSTR lpstrText)
{
  CNewMenu* pSubMenu = new CNewMenu(m_hMenu);
  pSubMenu->m_unselectcheck=m_unselectcheck;
  pSubMenu->m_selectcheck=m_selectcheck;
  pSubMenu->checkmaps=checkmaps;
  pSubMenu->checkmapsshare=TRUE;
  pSubMenu->CreatePopupMenu();
  AppendODMenu(lpstrText,MF_POPUP,HMenuToUInt(pSubMenu->m_hMenu), -1);
  return pSubMenu;
}

BOOL CNewMenu::ImageListDuplicate(CImageList *il,int xoffset,CImageList *newlist)
{
  if (il == NULL||newlist==NULL||xoffset<0)
    return FALSE;
  
  HICON hIcon = il->ExtractIcon(xoffset);
  int cx, cy;
  ImageList_GetIconSize(il->m_hImageList, &cx, &cy);
  newlist->Create(cx,cy,ILC_COLORDDB|ILC_MASK,1,1);
  newlist->Add(hIcon);
  ::DestroyIcon(hIcon);
  return TRUE;
}

CMenu* CNewMenu::GetSubMenu(int nPos)
{
  return CMenu::GetSubMenu (nPos);
}

CMenu* CNewMenu::GetSubMenu(LPCTSTR lpszSubMenuName)
{
  int num = GetMenuItemCount ();
  CString name;

  for (int i=0; i<num; i++)
  {
    GetMenuString (i, name, MF_BYPOSITION);
    if (name.Compare (lpszSubMenuName) == 0)
    {
      return CMenu::GetSubMenu (i);
    }
  }
  return NULL;
}

// Tongzhe Cui, Functions to remove a popup menu based on its name. Seperators
// before and after the popup menu can also be removed if they exist.
int CNewMenu::GetMenuPosition(LPCTSTR pText)
{
  for(int i=0;i<(int)(GetMenuItemCount());++i)
  {
    if(!GetSubMenu(i))
    { 
      for(int j=0;j<=m_MenuList.GetUpperBound();++j)
      {  
        if(m_MenuList[j]->m_szMenuText.Compare(pText)==NULL)
          return j;
      }
    }
  }
  // means no found;
  return -1;
}

// sPos means Seperator's position, since we have no way to find the 
// seperator's position in the menu we have to specify them when we call the 
// RemoveMenu to make sure the unused seperators are removed;
// sPos  = None no seperator removal;
//       = Head  seperator in front of this menu item;
//       = Tail  seperator right after this menu item;
//       = Both  seperators at both ends;
// remove the menu item based on their text, return -1 if not found, otherwise 
// return the menu position;
int CNewMenu::RemoveMenu(LPCTSTR pText, ESeperator sPos)
{
  int nPos = GetMenuPosition(pText);
  if(nPos != -1)
  {
    switch (sPos)
    {
    case CNewMenu::NONE:
      RemoveMenu(nPos, MF_BYPOSITION);
      break;

    case CNewMenu::HEAD:
      ASSERT(nPos - 1 >= 0);
      RemoveMenu(nPos-1, MF_BYPOSITION);
      break;

    case CNewMenu::TAIL:
      RemoveMenu(nPos+1, MF_BYPOSITION);
      break;

    case CNewMenu::BOTH:
      // remove the end first;
      RemoveMenu(nPos+1, MF_BYPOSITION);
      // remove the head;
      ASSERT(nPos - 1 >= 0);
      RemoveMenu(nPos-1, MF_BYPOSITION);
      break;
    }
  }
  return nPos;
}

BOOL CNewMenu::RemoveMenuTitle()
{
  int numMenuItems = (int)m_MenuList.GetSize();

  // We need a seperator at the beginning of the menu
  if(!numMenuItems || !((m_MenuList[0]->m_nFlags)&MF_SEPARATOR) )
  {
    return FALSE;
  }
  CNewMenuItemData* pMenuData = m_MenuList[0];
  // Check for title
  if(pMenuData->m_nTitleFlags&MFT_TITLE)
  {
    if(numMenuItems>0)
    {
      CNewMenuItemData* pMenuNextData = m_MenuList[1];
      if((pMenuNextData->m_nFlags&MF_MENUBREAK))
      {
        pMenuNextData->m_nFlags &= ~MF_MENUBREAK;
        CMenu::ModifyMenu(1,MF_BYPOSITION|pMenuNextData->m_nFlags,pMenuNextData->m_nID,(LPCTSTR)pMenuNextData);
      }
    }
    // Now remove the title
    RemoveMenu(0,MF_BYPOSITION);
    return TRUE;
  }
  return FALSE;
} 

BOOL CNewMenu::SetMenuTitle(LPCTSTR pTitle,UINT nTitleFlags)
{
  // Check the menu integrity
  if((int)GetMenuItemCount()!=(int)m_MenuList.GetSize())
  {
    SynchronizeMenu();
  }

  int numMenuItems = (int)m_MenuList.GetSize();

  // We need a seperator at the beginning of the menu
  if(!numMenuItems || !((m_MenuList[0]->m_nFlags)&MF_SEPARATOR) )
  {
    InsertMenu(0,MF_SEPARATOR|MF_BYPOSITION);
  }

  numMenuItems = (int)m_MenuList.GetSize();
  if(numMenuItems)
  {
    CNewMenuItemData* pMenuData = m_MenuList[0];
    if(pMenuData->m_nFlags&MF_SEPARATOR)
    {
      pMenuData->SetString(pTitle);
      pMenuData->m_nTitleFlags = nTitleFlags|MFT_TITLE;

      if(numMenuItems>1)
      {
        CNewMenuItemData* pMenuData = m_MenuList[1];

        if(nTitleFlags&MFT_SIDE_TITLE)
        {
          if(!(pMenuData->m_nFlags&MF_MENUBREAK))
          {
            pMenuData->m_nFlags |= MF_MENUBREAK;
            CMenu::ModifyMenu(1,MF_BYPOSITION|pMenuData->m_nFlags,pMenuData->m_nID,(LPCTSTR)pMenuData);
          }
        }
        else
        {
          if((pMenuData->m_nFlags&MF_MENUBREAK))
          {
            pMenuData->m_nFlags &= ~MF_MENUBREAK;
            CMenu::ModifyMenu(1,MF_BYPOSITION|pMenuData->m_nFlags,pMenuData->m_nID,(LPCTSTR)pMenuData);
          }
        }
        return TRUE;
      }
    }
  }
  return FALSE;
}

BOOL CNewMenu::SetMenuText(UINT id, CString string, UINT nFlags/*= MF_BYPOSITION*/ )
{
  BOOL returnflag=FALSE;

  if(MF_BYPOSITION&nFlags)
  {
    int numMenuItems = (int)m_MenuList.GetSize();
    if(id<UINT(numMenuItems))
    {
      m_MenuList[id]->SetString(string);
      returnflag=TRUE;
    }
  }
  else
  {
    int uiLoc;
    CNewMenu* pMenu = FindMenuOption(id,uiLoc);
    if(NULL!=pMenu)
    {
      returnflag = pMenu->SetMenuText(uiLoc,string);
    }
  }
  return returnflag;
}

// courtesy of Warren Stevens
void CNewMenu::ColorBitmap(CDC* pDC,CBitmap& bmp,CSize size,COLORREF fill,COLORREF border,int hatchstyle)
{
  // Create a memory DC
  CDC MemDC;
  MemDC.CreateCompatibleDC(pDC);  
  bmp.CreateCompatibleBitmap(pDC, size.cx, size.cy);  
  CPen border_pen(PS_SOLID, 1, border);

  CBrush fill_brush;
  if(hatchstyle!=-1) 
  { 
    fill_brush.CreateHatchBrush(hatchstyle, fill); 
  }
  else 
  {
    fill_brush.CreateSolidBrush(fill);
  }

  CBitmap* pOldBitmap = MemDC.SelectObject(&bmp);
  CPen*    pOldPen    = MemDC.SelectObject(&border_pen);
  CBrush*  pOldBrush  = MemDC.SelectObject(&fill_brush);

  MemDC.Rectangle(0,0, size.cx, size.cy);

  if(NULL!=pOldBrush)  { MemDC.SelectObject(pOldBrush);  }
  if(NULL!=pOldPen)    { MemDC.SelectObject(pOldPen);    }
  if(NULL!=pOldBitmap) { MemDC.SelectObject(pOldBitmap); }
}

void CNewMenu::DrawSpecial_OldStyle(CDC* pDC, LPCRECT pRect,UINT nID, DWORD dwStyle)
{
  COLORREF oldColor;
  if( (dwStyle&ODS_GRAYED) || (dwStyle&ODS_INACTIVE))
  {
    oldColor = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
  }
  else if (dwStyle&ODS_SELECTED)
  { 
    oldColor = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
  }
  else
  {
    oldColor = pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
  }
  BOOL bBold = (dwStyle&ODS_DEFAULT) ? TRUE : FALSE;

  switch(nID&0xfff0)
  {
  case SC_MINIMIZE:
    DrawSpecialChar(pDC,pRect,48,bBold); // Min
    break;
  case SC_MAXIMIZE:
    DrawSpecialChar(pDC,pRect,49,bBold); // Max
    break;
  case SC_CLOSE:
    DrawSpecialChar(pDC,pRect,114,bBold); // Close
    break;
  case SC_RESTORE:
    DrawSpecialChar(pDC,pRect,50,bBold); // restore
    break;
  }
  pDC->SetTextColor(oldColor);
}

void CNewMenu::DrawSpecial_WinXP(CDC* pDC, LPCRECT pRect,UINT nID, DWORD dwStyle)
{
  TCHAR cSign = 0;
  switch(nID&0xfff0)
  {
  case SC_MINIMIZE:
    cSign = 48; // Min
    break;
  case SC_MAXIMIZE:
    cSign = 49;// Max
    break;
  case SC_CLOSE:
    cSign = 114;// Close
    break;
  case SC_RESTORE:
    cSign = 50;// Restore
    break;
  }
  if(cSign)
  {
    COLORREF oldColor;
    BOOL bBold = (dwStyle&ODS_DEFAULT) ? TRUE : FALSE;
    CRect rect(pRect);

    if( (dwStyle&ODS_GRAYED) || (dwStyle&ODS_INACTIVE))
    {
      oldColor = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
    }
    else if(dwStyle&ODS_SELECTED)
    { 
      oldColor = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
      DrawSpecialChar(pDC,rect,cSign,bBold);
      pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
      rect.OffsetRect(-2,-2);
    }
    else
    { 
      oldColor = pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
    }
    DrawSpecialChar(pDC,rect,cSign,bBold);

    pDC->SetTextColor(oldColor);
  }
}

void CNewMenu::SetMBar(CMenuButton *pBar)
{	
	pb=pBar;
}

CRect CNewMenu::GetLastActiveMenuRect()
{
  return m_LastActiveMenuRect;
}

void CNewMenu::DrawSpecialCharStyle(CDC* pDC, LPCRECT pRect, TCHAR Sign, DWORD dwStyle)
{
  COLORREF oldColor;
  if( (dwStyle&ODS_GRAYED) || (dwStyle&ODS_INACTIVE))
  {
    oldColor = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
  }
  else
  { 
    oldColor = pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
  }

  DrawSpecialChar(pDC,pRect,Sign,(dwStyle&ODS_DEFAULT) ? TRUE : FALSE);

  pDC->SetTextColor(oldColor);
}

void CNewMenu::DrawSpecialChar(CDC* pDC, LPCRECT pRect, TCHAR Sign, BOOL bBold)
{
  //  48 Min
  //  49 Max
  //  50 Restore
  //  98 Checkmark 
  // 105 Bullet
  // 114 Close

  CFont MyFont;
  LOGFONT logfont;

  CRect rect(pRect) ;
  rect.DeflateRect(2,2);

  logfont.lfHeight = -rect.Height();
  logfont.lfWidth = 0;
  logfont.lfEscapement = 0;
  logfont.lfOrientation = 0;
  logfont.lfWeight = (bBold) ? FW_BOLD:FW_NORMAL;
  logfont.lfItalic = FALSE;
  logfont.lfUnderline = FALSE;
  logfont.lfStrikeOut = FALSE;
  logfont.lfCharSet = DEFAULT_CHARSET;
  logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
  logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  logfont.lfQuality = DEFAULT_QUALITY;
  logfont.lfPitchAndFamily = DEFAULT_PITCH;

  _tcscpy(logfont.lfFaceName,_T("Marlett"));

  MyFont.CreateFontIndirect (&logfont);

  CFont* pOldFont = pDC->SelectObject (&MyFont); 
  int OldMode = pDC->SetBkMode(TRANSPARENT);  

  pDC->DrawText (&Sign,1,rect,DT_CENTER|DT_SINGLELINE);

  pDC->SetBkMode(OldMode);
  pDC->SelectObject(pOldFont);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuTheme::CMenuTheme()
{ 
  ZeroMemory(this,sizeof(CMenuTheme));
}

CMenuTheme::CMenuTheme( DWORD dwThemeId, 
                        pItemMeasureFkt pMeasureItem,
                        pItemDrawFkt pDrawItem,
                        pItemDrawFkt pDrawTitle,
                        DWORD dwFlags)
  :m_dwThemeId(dwThemeId),
    m_dwFlags(dwFlags),
    m_pMeasureItem(pMeasureItem),
    m_pDrawItem(pDrawItem),
    m_pDrawTitle(pDrawTitle)
{
  m_BorderTopLeft = CSize(2,2);

  if(!IsShadowEnabled())
  {
    m_BorderBottomRight = CSize(5,6);
  }
  else
  {
    m_BorderBottomRight = CSize(2,2);
  }
}

CMenuTheme::~CMenuTheme()
{
}

BOOL CMenuTheme::DoDrawBorder()
{
  return (m_dwFlags&1)?TRUE:FALSE;
}

void CMenuTheme::DrawSmalBorder( HWND hWnd, HDC hDC)
{
  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
  if(pData!=NULL)
  {
	
    if(pData->m_hMenu)
    {   
      CNewMenu* pMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(pData->m_hMenu));
      if(pMenu && pMenu->GetParent())
      {
        CNewMenu* pParentMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(pMenu->GetParent()));
        if(pParentMenu && !pParentMenu->IsPopup())
        {
          CRect Rect;
          // Get the size of the menu... 
          GetWindowRect(hWnd, Rect );
          Rect.OffsetRect(pData->m_Point - Rect.TopLeft());
          Rect &= pParentMenu->GetLastActiveMenuRect();
          if(!Rect.IsRectEmpty())
          {
            if(Rect.Width()>Rect.Height())
            {
              Rect.InflateRect(-1,0);
            }
            else
            {
              Rect.InflateRect(0,-1);
            }
            Rect.OffsetRect(-pData->m_Point);
            CDC* pDC = CDC::FromHandle(hDC);
            pDC->FillSolidRect(Rect,GetSysColor(CNewMenu::cCOLOR_MENUBAR));
          }
        }
      }
    }
  }
}

void CMenuTheme::DrawShade( HWND hWnd, HDC hDC,CPoint screen)
{ 
  if(IsShadowEnabled())
    return;

  // Get the size of the menu... 
  CRect Rect;
  GetWindowRect(hWnd, Rect );

  long winW = Rect.Width(); 
  long winH = Rect.Height(); 
  long xOrg = screen.x;  
  long yOrg = screen.y;

  // Get the desktop hDC... 
  HDC hDcDsk = GetWindowDC(0) ;
  
  int X,Y;
  // Simulate a shadow on right edge... 
  for (X=1; X<=4 ;X++)
  { 
    for (Y=0; Y<4 ;Y++)
    {
      SetPixel(hDC,winW-X,Y, GetPixel(hDcDsk,xOrg+winW-X,yOrg+Y) );
    }
    for (Y=4; Y<8 ;Y++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
      SetPixel(hDC,winW-X,Y,DarkenColor(3 * X * (Y - 3), c)) ;
    }
    for (Y=8; Y<=(winH-5) ;Y++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
      SetPixel( hDC, winW - X, Y, DarkenColor(15 * X, c) );
    }
    for (Y=(winH-4); Y<=(winH-1) ;Y++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
      SetPixel( hDC, winW - X, Y, DarkenColor(3 * X * -(Y - winH), c)) ;
    }
  } 

  // Simulate a shadow on the bottom edge... 
  for(Y=1; Y<=4 ;Y++)
  {
    for(X=0; X<=3 ;X++)
    {
      SetPixel(hDC,X,winH-Y, GetPixel(hDcDsk,xOrg+X,yOrg+winH-Y)) ;
    }
    for(X=4; X<=7 ;X++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y) ;
      SetPixel( hDC, X, winH - Y, DarkenColor(3 * (X - 3) * Y, c)) ;
    }
    for(X=8; X<=(winW-5) ;X++)
    {
      COLORREF  c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y); 
      SetPixel( hDC, X, winH - Y, DarkenColor(15 * Y, c)) ;
    }
  }   
  // Release the desktop hDC... 
  ReleaseDC(0,hDcDsk);
}

BOOL CMenuTheme::OnInitWnd(HWND hWnd)
{
  if(DoDrawBorder())
  {
    CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
    ASSERT(pData);
    // Flag for changing styles
    pData->m_dwData |= 2;

    SetWindowLong (hWnd, GWL_STYLE, pData->m_dwStyle & (~WS_BORDER) );
    SetWindowLong (hWnd, GWL_EXSTYLE,pData->m_dwExStyle & ~(WS_EX_WINDOWEDGE|WS_EX_DLGMODALFRAME));

    return TRUE;
  }
  return FALSE;
}

BOOL CMenuTheme::OnUnInitWnd(HWND hWnd)
{
  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
  if(pData)
  {
    HMENU hMenu = pData->m_hMenu;
    CNewMenu* pNewMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(hMenu));
    if(pNewMenu)
    {
      if(pNewMenu->OnUnInitPopupMenu() && (pData->m_dwData&4) )
      {
        HWND hParenWnd = GetParent(hWnd);
        if(hParenWnd)
          DrawMenuBar(hParenWnd);
      }
    }
    // were windows-style changed?
    if(pData->m_dwData&2)
    {
      SetLastError(0);
      if(!(pData->m_dwData&1))
      {
        SetWindowLong (hWnd, GWL_STYLE,pData->m_dwStyle);
      }
      else
      {
        // Restore old Styles for special menu!! 
        // (Menu 0x10012!!!) special VISIBLE flag must be set
        SetWindowLong (hWnd, GWL_STYLE,pData->m_dwStyle|WS_VISIBLE);
      }

      ShowLastError();
      SetWindowLong (hWnd, GWL_EXSTYLE, pData->m_dwExStyle);
      ShowLastError();
      // Normaly when you change the style you shold call next function
      // but in this case you would lose the focus for the menu!!
      //SetWindowPos(hWnd,0,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED|SWP_HIDEWINDOW);
    }
  }
  return TRUE;
}

BOOL CMenuTheme::OnEraseBkgnd(HWND hWnd, HDC hDC)
{
  //  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);

  //  Get the size of the menu... 
  CDC* pDC = CDC::FromHandle (hDC);
  CRect Rect;
  GetClientRect(hWnd, Rect );
  pDC->FillSolidRect (Rect,GetSysColor(COLOR_MENU));

  return TRUE;
}

BOOL CMenuTheme::OnWindowPosChanging(HWND hWnd, LPWINDOWPOS pPos)
{
  UNREFERENCED_PARAMETER(hWnd);

  if(DoDrawBorder())
  {
    if(!IsShadowEnabled())
    {
      pPos->cx +=2;
      pPos->cy +=2;
    }
    else
    {
      pPos->cx -=2;
      pPos->cy -=2;
    }
    pPos->y -=1;

    return TRUE;
  }
  return FALSE;
}

BOOL CMenuTheme::OnNcCalcSize(HWND hWnd, NCCALCSIZE_PARAMS* pCalc)
{
  UNREFERENCED_PARAMETER(hWnd);

  if(DoDrawBorder())
  {
    pCalc->rgrc->top  += m_BorderTopLeft.cy;
    pCalc->rgrc->left += m_BorderTopLeft.cx; 

    pCalc->rgrc->bottom -= m_BorderBottomRight.cy;
    pCalc->rgrc->right  -= m_BorderBottomRight.cx;
  }
  return FALSE;
}

BOOL CMenuTheme::OnDrawBorder(HWND hWnd, HDC hDC)
{
  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
  if(DoDrawBorder() && pData)
  {
    CRect Rect;
    CDC* pDC = CDC::FromHandle (hDC);

    // Get the size of the menu... 
    GetWindowRect(hWnd, Rect );

    long winW = Rect.Width(); 
    long winH = Rect.Height(); 

    if(!IsShadowEnabled())
    {
      pDC->Draw3dRect(CRect(CPoint(1,1),CSize(winW-6,winH-6)),GetSysColor(CNewMenu::cCOLOR_MENUBAR),GetSysColor(CNewMenu::cCOLOR_MENUBAR));
      pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-4,winH-4)),GetSysColor(COLOR_HIGHLIGHT),GetSysColor(COLOR_HIGHLIGHT));
      
      DrawShade(hWnd,hDC,pData->m_Point);
    }
    else
    {
      pDC->Draw3dRect(CRect(CPoint(1,1),CSize(winW-2,winH-2)),GetSysColor(CNewMenu::cCOLOR_MENUBAR),GetSysColor(CNewMenu::cCOLOR_MENUBAR));
      pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-0,winH-0)),GetSysColor(COLOR_HIGHLIGHT),GetSysColor(COLOR_HIGHLIGHT));
    }
    //DrawSmalBorder(hWnd,hDC);
    return TRUE;
  }
  return FALSE;
}

CMenuThemeXP::CMenuThemeXP(DWORD dwThemeId, 
                           pItemMeasureFkt pMeasureItem,
                           pItemDrawFkt pDrawItem,
                           pItemDrawFkt pDrawTitle,
                           DWORD dwFlags)
:CMenuTheme(dwThemeId,pMeasureItem,pDrawItem,pDrawTitle,dwFlags)
{
}

BOOL CMenuThemeXP::OnDrawBorder(HWND hWnd, HDC hDC)
{
  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
  if(DoDrawBorder() && pData)
  {
    CRect Rect;
    CDC* pDC = CDC::FromHandle (hDC);

    // Get the size of the menu... 
    GetWindowRect(hWnd, Rect );

    long winW = Rect.Width(); 
    long winH = Rect.Height(); 
	CRect rc=Rect;
    if(!IsShadowEnabled())
    {
      pDC->Draw3dRect(CRect(CPoint(1,1),CSize(winW-6,winH-6)),GetSysColor(COLOR_WINDOW),GetSysColor(COLOR_WINDOW));
      pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-4,winH-4)),GuiDrawLayer::GetRGBMenu(),GuiDrawLayer::GetRGBMenu());

      DrawShade(hWnd,hDC,pData->m_Point);
    }
    else
    {
      pDC->Draw3dRect(CRect(CPoint(1,1),CSize(winW-2,winH-2)),GetSysColor(COLOR_WINDOW),GetSysColor(COLOR_WINDOW));
      pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-0,winH-0)),GuiDrawLayer::GetRGBMenu(),GuiDrawLayer::GetRGBMenu());
    }
	pDC->Draw3dRect(CRect(CPoint(1,1),CSize(1,winH-4)),GuiDrawLayer::GetRGBColorFace(),GuiDrawLayer::GetRGBColorFace());
	if (CNewMenu::m_StyleMenu==GUISTYLE_2003 && GuiDrawLayer::m_Theme)
	{
		COLORREF clrNear=pDC->GetNearestColor(GuiDrawLayer::GetRGBCaptionXP());
		if(clrNear!=13221564)
		pDC->Draw3dRect(0,0,winW,winH,GuiDrawLayer::GetRGBCaptionXP(),GuiDrawLayer::GetRGBCaptionXP());
	}
	CRect rcDeskTop;
	CWnd* pDeskTop=CWnd::FromHandle(GetDesktopWindow());
	pDeskTop->GetWindowRect(rcDeskTop);
	if (gbintHorz!=-1 )
		if (gbintHorz==0 )
		{
			if ( rcDeskTop.bottom  > Rect.bottom)
				pDC->Draw3dRect(1,0,rcMenu.Width()-1,0,GetSysColor(CNewMenu::cCOLOR_MENUBAR),GetSysColor(CNewMenu::cCOLOR_MENUBAR));
		}
		else 
		{
			if ( rcDeskTop.right > Rect.right)
				pDC->Draw3dRect(0,1,0,rcMenu.Height()-1,GetSysColor(CNewMenu::cCOLOR_MENUBAR),GetSysColor(CNewMenu::cCOLOR_MENUBAR));
		}
	gbintHorz=-1;
	rcMenu=CRect(0,0,0,0);
	DrawSmalBorder(hWnd,hDC);
    
    return TRUE;
  }
  return FALSE;
}

BOOL CMenuThemeXP::OnEraseBkgnd(HWND hWnd, HDC hDC)
{
  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
  if(pData->m_hMenu==NULL)
  {
    return CMenuTheme::OnEraseBkgnd(hWnd,hDC);
  }
 
  //  Get the size of the menu... 
  CDC* pDC = CDC::FromHandle (hDC);
  CRect Rect;
  GetClientRect(hWnd, Rect );
  pDC->FillSolidRect (Rect,GetSysColor(CNewMenu::cCOLOR_MENUBAR));

  return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const TCHAR _OldMenuProc[] = _T("OldMenuProc");

HHOOK CNewMenuHook::HookOldMenuCbtFilter = NULL;
HMENU CNewMenuHook::m_hLastMenu = NULL;
DWORD CNewMenuHook::m_dwMsgPos = 0;

CTypedPtrList<CPtrList, CMenuTheme*>* CNewMenuHook::m_pRegisteredThemesList = NULL;

CTypedPtrMap<CMapPtrToPtr,HWND,CNewMenuHook::CMenuHookData*> CNewMenuHook::m_MenuHookData;

CNewMenuHook::CNewMenuHook()
{ 
  if(IsShellType()==WinXP)
  {
    BOOL bFlatMenu = FALSE;
    if(SystemParametersInfo(SPI_GETFLATMENU,0,&bFlatMenu,0) && bFlatMenu==TRUE)
    {
      CNewMenu::cCOLOR_MENUBAR = COLOR_MENUBAR;
    }
  }
  AddTheme(new CMenuTheme(CNewMenu::STYLE_ORIGINAL,
                          CNewMenu::MeasureItem_OldStyle,
                          CNewMenu::DrawItem_OldStyle,
                          CNewMenu::DrawMenuTitle,TRUE));

  AddTheme(new CMenuTheme(CNewMenu::STYLE_ORIGINAL_NOBORDER,
                          CNewMenu::MeasureItem_OldStyle,
                          CNewMenu::DrawItem_OldStyle,
                          CNewMenu::DrawMenuTitle));

  AddTheme(new CMenuThemeXP(CNewMenu::STYLE_XP,
                            CNewMenu::MeasureItem_WinXP,
                            CNewMenu::DrawItem_WinXP,
                            CNewMenu::DrawMenuTitle,TRUE));

  AddTheme(new CMenuThemeXP(CNewMenu::STYLE_XP_NOBORDER,
                            CNewMenu::MeasureItem_WinXP,
                            CNewMenu::DrawItem_WinXP,
                            CNewMenu::DrawMenuTitle));

  AddTheme(new CMenuTheme(CNewMenu::STYLE_SPECIAL,
                          CNewMenu::MeasureItem_OldStyle,
                          CNewMenu::DrawItem_SpecialStyle,
                          CNewMenu::DrawMenuTitle,TRUE));

  AddTheme(new CMenuTheme(CNewMenu::STYLE_SPECIAL_NOBORDER,
                          CNewMenu::MeasureItem_OldStyle,
                          CNewMenu::DrawItem_SpecialStyle,
                          CNewMenu::DrawMenuTitle));

//  CNewMenu::m_pActMenuDrawing = FindTheme(CNewMenu::STYLE_ORIGINAL);
//  CNewMenu::m_pActMenuDrawing = FindTheme(CNewMenu::STYLE_ORIGINAL_NOBORDER);
  CNewMenu::m_pActMenuDrawing = FindTheme(CNewMenu::STYLE_XP);
//  CNewMenu::m_pActMenuDrawing = FindTheme(CNewMenu::STYLE_XP_NOBORDER);

  if (HookOldMenuCbtFilter == NULL)
  {
    HookOldMenuCbtFilter = ::SetWindowsHookEx(WH_CALLWNDPROC, NewMenuHook, NULL, ::GetCurrentThreadId());
    if (HookOldMenuCbtFilter == NULL)
    {
      ShowLastError();
      AfxThrowMemoryException();
    }
  } 
}

CNewMenuHook::~CNewMenuHook()
{
  if (HookOldMenuCbtFilter != NULL)
  {
    if(!::UnhookWindowsHookEx(HookOldMenuCbtFilter))
    {
      ShowLastError();
    }
    HookOldMenuCbtFilter = NULL;
  }
  // Destroy all registered themes.
  if( m_pRegisteredThemesList!= NULL)
  {
    while(m_pRegisteredThemesList->GetCount())
    {
      CMenuTheme* pTheme = m_pRegisteredThemesList->RemoveTail();
      delete pTheme;
    }
    delete m_pRegisteredThemesList;
    m_pRegisteredThemesList = NULL;
  }
}

BOOL CNewMenuHook::AddTheme(CMenuTheme* pTheme)
{
  if( m_pRegisteredThemesList== NULL)
  {
    m_pRegisteredThemesList = new CTypedPtrList<CPtrList, CMenuTheme*>;
  }
  if(m_pRegisteredThemesList->Find(pTheme))
  {
    return FALSE;
  }
  m_pRegisteredThemesList->AddTail(pTheme);
  return TRUE;
}

CMenuTheme* CNewMenuHook::RemoveTheme(DWORD dwThemeId)
{
  CMenuTheme* pTheme = FindTheme(dwThemeId);
  if(pTheme==NULL)
  {
    return NULL;
  }
  POSITION pos = m_pRegisteredThemesList->Find(pTheme);
  ASSERT(pos);
  if(pos)
  {
    m_pRegisteredThemesList->RemoveAt(pos);
    if(m_pRegisteredThemesList->GetCount()==NULL)
    {
      // Destroy the empty list.
      delete m_pRegisteredThemesList;
      m_pRegisteredThemesList = NULL;
    }
  }
  return pTheme; 
}

CMenuTheme* CNewMenuHook::FindTheme(DWORD dwThemeId)
{
  if(m_pRegisteredThemesList==NULL)
  {
    return NULL;
  }

  POSITION pos = m_pRegisteredThemesList->GetHeadPosition();
  while(pos)
  { 
    CMenuTheme* pTheme = m_pRegisteredThemesList->GetNext(pos);
    if(pTheme->m_dwThemeId==dwThemeId)
    {
      return pTheme;
    }    
  }
  return NULL;
}   

CNewMenuHook::CMenuHookData* CNewMenuHook::GetMenuHookData(HWND hWnd)
{
  CMenuHookData* pData=NULL;
  if(m_MenuHookData.Lookup(hWnd,pData))
  {
    return pData;
  }
  return NULL;
}

void CNewMenuHook::UnsubClassMenu(HWND hWnd)
{
  AFX_MANAGE_STATE(AfxGetModuleState());

  WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, _OldMenuProc);
  ASSERT(oldWndProc != NULL);  

  SetLastError(0);
  if(!SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)(DWORD_PTR)oldWndProc))
  {
    ShowLastError();
  }
  RemoveProp(hWnd, _OldMenuProc);
  GlobalDeleteAtom(GlobalFindAtom(_OldMenuProc));

  // now Clean up
  HMENU hMenu = NULL;
  // Restore old Styles for special menu!! (Menu 0x10012!!!)
  CMenuHookData* pData = GetMenuHookData(hWnd);
  if(pData)
  {
    hMenu = pData->m_hMenu;
    CNewMenu::m_pActMenuDrawing->OnUnInitWnd(hWnd);

    m_MenuHookData.RemoveKey(hWnd);
    delete pData;
  }
  
#ifdef _TRACE_MENU_
  TRACE(_T("Unsubclass Menu=0x%lX, hwnd=0x%lX\n"),hMenu,hWnd);
#endif
}


LRESULT CALLBACK CNewMenuHook::SubClassMenu(HWND hWnd,      // handle to window
                                            UINT uMsg,      // message identifier
                                            WPARAM wParam,  // first message parameter
                                            LPARAM lParam   // second message parameter
                                            )
{
  AFX_MANAGE_STATE(AfxGetModuleState());

  WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, _OldMenuProc);
  LRESULT result = NULL;
  	
  static long NestedLevel = 0;
  BOOL bCallDefault = TRUE;

  NestedLevel++;

#ifdef _TRACE_MENU_
  MSG msg = {hWnd,uMsg,wParam,lParam,0,0,0};
  TCHAR Buffer[30]; 
  wsprintf(Buffer,_T("Level %02ld"),NestedLevel);
  MyTraceMsg(Buffer,&msg);
#endif

  switch(uMsg)
  {
  case WM_NCPAINT:
    {
      CMenuHookData* pData = GetMenuHookData(hWnd);
      if(pData && pData->m_bDrawBorder)
      {
        HDC hDC;
        if(wParam!=1)
          hDC = GetDCEx(hWnd, (HRGN)wParam, DCX_WINDOW|DCX_INTERSECTRGN);
        else
          hDC = GetWindowDC (hWnd);

        if(hDC)
        { 
		  
          if(CNewMenu::m_pActMenuDrawing->OnDrawBorder(hWnd,hDC))
          {
            bCallDefault=FALSE;
          }
		  ReleaseDC(hWnd,hDC);
        }
      }
      pData->m_bDrawBorder = TRUE;
    }
    break;

  case WM_PRINT:
    {
      CMenuHookData* pData = GetMenuHookData(hWnd);
      if(pData && CNewMenu::m_pActMenuDrawing->OnDrawBorder(hWnd,(HDC)wParam) )
      {
        pData->m_bDrawBorder = FALSE;
        // We need to create a bitmap for drawing
        // We can't clipp or make a offset to the DC because NT2000 (blue-screen!!)
        CRect rect;
        GetClientRect(hWnd, rect);

        CDC dc;
        CBitmap bitmap;

        CDC* pDC = CDC::FromHandle((HDC)wParam);
        dc.CreateCompatibleDC(pDC); 

        bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
        CBitmap* pOldBitmap = dc.SelectObject(&bitmap);
        // might as well clip to the same rectangle
        dc.IntersectClipRect(rect);

        CSize offset = CNewMenu::m_pActMenuDrawing->m_BorderTopLeft;
        SendMessage(hWnd,WM_ERASEBKGND,(WPARAM)dc.m_hDC,0);
        SendMessage(hWnd,WM_PRINTCLIENT,(WPARAM)dc.m_hDC,lParam);
        pDC->BitBlt(offset.cx,offset.cy, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);
        dc.SelectObject(pOldBitmap);

        bCallDefault=FALSE;
      } 
    }
    break;

  case WM_ERASEBKGND:
    {
      if(CNewMenu::m_pActMenuDrawing->OnEraseBkgnd(hWnd,(HDC)wParam))
      {
        bCallDefault=FALSE; 
        result = TRUE;
      }
    }
    break;

  case WM_WINDOWPOSCHANGED:
  case WM_WINDOWPOSCHANGING:
    {
      CMenuHookData* pData=GetMenuHookData(hWnd);
      ASSERT(pData);

      LPWINDOWPOS pPos = (LPWINDOWPOS)lParam;
      // Need for windows 98
      BOOL bSetPos = pPos->x!=NULL || pPos->y!=NULL;
      if(uMsg==WM_WINDOWPOSCHANGING)
      {
        CNewMenu::m_pActMenuDrawing->OnWindowPosChanging(hWnd,pPos);
      }
      if(bSetPos)
      {
        pData->m_Point = CPoint(pPos->x,pPos->y);
      }
    }
    break;

  case WM_KEYDOWN:
    if(wParam==VK_ESCAPE)
    {
      CMenuHookData* pData = GetMenuHookData(hWnd);
      if(pData)
      {
        pData->m_dwData |= 4;
      }
    }
    m_dwMsgPos = GetMessagePos();
    break;

  case WM_NCCALCSIZE:
    {
      NCCALCSIZE_PARAMS* pCalc = (NCCALCSIZE_PARAMS*)lParam;
      if(CNewMenu::m_pActMenuDrawing->OnNcCalcSize(hWnd,pCalc))
      {
        bCallDefault=FALSE; 
      }
    }
    break;

  case WM_SHOWWINDOW:
    // Hide the window ? Test for 98 and 2000
    if(wParam==NULL)
    { 
      // Special handling for NT 2000 and WND 0x10012.
      UnsubClassMenu(hWnd);
    }
    break;

  case WM_NCDESTROY:
    UnsubClassMenu (hWnd);
    break;
  }

  if( bCallDefault )
  {
    ASSERT(oldWndProc != NULL);
    // call original wndproc for default handling
    result = CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
  }

  NestedLevel--;

  return result;
} 

BOOL CNewMenuHook::CheckSubclassing(HWND hWnd, BOOL bSpecialWnd)
{
  TCHAR Name[20];
  int Count = GetClassName (hWnd,Name,ARRAY_SIZE(Name));
  if(Count!=6 || _tcscmp(Name,_T("#32768"))!=0)
  {
    // does not match to menuclass
    return false;
  }

  BOOL bDoNewSubclass = FALSE;
  CMenuHookData* pData=GetMenuHookData(hWnd);
  // check if we have allready some data
  if(pData==NULL)
  {
    WNDPROC oldWndProc;
    // subclass the window with the proc which does gray backgrounds
    oldWndProc = (WNDPROC)(LONG_PTR)GetWindowLong(hWnd, GWL_WNDPROC);
    if (oldWndProc != NULL && GetProp(hWnd, _OldMenuProc) == NULL)
    {
      ASSERT(oldWndProc!=SubClassMenu);

      if(!SetProp(hWnd, _OldMenuProc, oldWndProc))
      {
        ShowLastError();
      }
      if ((WNDPROC)GetProp(hWnd, _OldMenuProc) == oldWndProc)
      {
        GlobalAddAtom(_OldMenuProc);

        CMenuHookData* pData=GetMenuHookData(hWnd);
        ASSERT(pData==NULL);
        if(pData==NULL)
        { 
          pData = new CMenuHookData(hWnd,bSpecialWnd);
          m_MenuHookData.SetAt (hWnd,pData);

          SetLastError(0);
          if(!SetWindowLong(hWnd, GWL_WNDPROC,(DWORD)(DWORD_PTR)SubClassMenu))
          {
            ShowLastError();
          }
          bDoNewSubclass = TRUE;

  #ifdef _TRACE_MENU_
          TRACE(_T("Subclass Menu=0x%lX, hwnd=0x%lX\n"),pData->m_hMenu,hWnd);
  #endif 
          CNewMenu::m_pActMenuDrawing->OnInitWnd(hWnd);
        } 
      }
      else
      {
        ASSERT(0);
      }
    }
  }

  // Menu was set also assign it to this menu.
  if(m_hLastMenu)
  {
    CMenuHookData* pData = GetMenuHookData(hWnd);
    if(pData)
    {
      // Safe actual menu
      pData->m_hMenu = m_hLastMenu;
      // Reset for the next menu
      m_hLastMenu = NULL;
    }
  }
  return bDoNewSubclass;
}

LRESULT CALLBACK CNewMenuHook::NewMenuHook(int code, WPARAM wParam, LPARAM lParam)
{
  AFX_MANAGE_STATE(AfxGetModuleState());

  CWPSTRUCT* pTemp = (CWPSTRUCT*)lParam;
  if(code == HC_ACTION )
  {
    HWND hWnd = pTemp->hwnd;

    // Normal and special handling for menu 0x10012
    if(pTemp->message==WM_CREATE || pTemp->message==0x01E2)
    {
      CheckSubclassing(hWnd,pTemp->message==0x01E2);
    }
  }
  return CallNextHookEx(HookOldMenuCbtFilter, code,wParam, lParam);
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

