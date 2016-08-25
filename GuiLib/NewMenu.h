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
 *																			*
 * Bug Fixes and improvements : (Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/


//------------------------------------------------------------------------------
// File    : NewMenu.h 
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



#ifndef __CNewMenu_H_
#define __CNewMenu_H_

#pragma warning(push)
#pragma warning(disable : 4211)

// Flagdefinitions 
#define MFT_TITLE       0x0001
#define MFT_TOP_TITLE   0x0000
#define MFT_SIDE_TITLE  0x0002
#define MFT_GRADIENT    0x0004
#define MFT_SUNKEN      0x0008
#define MFT_LINE        0x0010
#define MFT_ROUND       0x0020
#define MFT_CENTER      0x0040

// Typedefinition for compatibility to MFC 7.0
#ifndef DWORD_PTR
typedef DWORD DWORD_PTR, *PDWORD_PTR;
#endif

#ifndef ULONG_PTR
typedef unsigned long ULONG_PTR, *PULONG_PTR;
#endif

#ifndef LONG_PTR
typedef long LONG_PTR, *PLONG_PTR;
#endif

#include "MenuBar.h"

/////////////////////////////////////////////////////////////////////////////
// Forwarddeclaration for drawing purpose
class CMenuTheme;

/////////////////////////////////////////////////////////////////////////////
// CNewMenuItemData menu item data for drawing

class CNewMenuItemData : public CObject
{
  DECLARE_DYNCREATE(CNewMenuItemData)

public:
  CNewMenuItemData();
  virtual ~CNewMenuItemData();

public:
  LPCTSTR GetString();
  void SetString(LPCTSTR szMenuText);

#if defined(_DEBUG) || defined(_AFXDLL)
  // Diagnostic Support
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:
  CString m_szMenuText;

  UINT m_nTitleFlags;
  UINT m_nFlags;
  UINT m_nID;
  UINT m_nSyncFlag;

  int m_nxOffset;
  int m_nMenuIconNormal;

  CImageList* m_pBitmap;

  void* m_pData;
};

/////////////////////////////////////////////////////////////////////////////
// CNewMenu the new menu class

class GUILIBDLLEXPORT  CNewMenu : public CMenu
{
  friend class CNewMenuHook;

  DECLARE_DYNCREATE(CNewMenu)

public:
  // how the menu's are drawn, either original or XP style
  typedef enum 
  { 
    STYLE_ORIGINAL,
    STYLE_ORIGINAL_NOBORDER,

    STYLE_XP,
    STYLE_XP_NOBORDER,

    STYLE_SPECIAL,
    STYLE_SPECIAL_NOBORDER
  } EDrawStyle;

  // how seperators are handled when removing a menu (Tongzhe Cui)
  typedef enum {NONE, HEAD, TAIL, BOTH} ESeperator;

public:
  CNewMenu(HMENU hParent=0); 
  virtual ~CNewMenu();

  // Functions for loading and applying bitmaps to menus (see example application)
  virtual BOOL LoadMenu(HMENU hMenu);
  virtual BOOL LoadMenu(LPCTSTR lpszResourceName);
  virtual BOOL LoadMenu(int nResource);

  BOOL LoadToolBar(WORD* pToolInfo, COLORREF crTransparent=CLR_NONE);
  BOOL LoadToolBar(LPCTSTR lpszResourceName);
  BOOL LoadToolBar(UINT nToolBar);
  BOOL LoadToolBars(const UINT *arID,int n);

  void AddFromToolBar(CToolBar* pToolBar, int nResourceID);
  BOOL LoadFromToolBar(UINT nID,UINT nToolBar,int& xoffset);
  BOOL AddBitmapToImageList(CImageList *list,UINT nResourceID);

  static HBITMAP LoadSysColorBitmap(int nResourceId);
  // custom check mark bitmaps
  void LoadCheckmarkBitmap(int unselect, int select); 

  // functions for appending a menu option, use the AppendMenu call
  BOOL AppendMenu(UINT nFlags,UINT nIDNewItem=0,LPCTSTR lpszNewItem=NULL,int nIconNormal=-1);
  BOOL AppendMenu(UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CImageList *il,int xoffset);
  BOOL AppendMenu(UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CBitmap *bmp);

  BOOL AppendODMenu(LPCTSTR lpstrText,UINT nFlags = MF_OWNERDRAW,UINT nID = 0,int nIconNormal = -1);  
  BOOL AppendODMenu(LPCTSTR lpstrText,UINT nFlags,UINT nID,CImageList *il,int xoffset);

  // for appending a popup menu (see example application)
  CNewMenu* AppendODPopupMenu(LPCTSTR lpstrText);

  // functions for inserting a menu option, use the InsertMenu call (see above define)
  BOOL InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem=0,LPCTSTR lpszNewItem=NULL,int nIconNormal=-1);
  BOOL InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CImageList *il,int xoffset);
  BOOL InsertMenu(UINT nPosition,UINT nFlags,UINT nIDNewItem,LPCTSTR lpszNewItem,CBitmap *bmp);

  BOOL InsertODMenu(UINT nPosition,LPCTSTR lpstrText,UINT nFlags = MF_OWNERDRAW,UINT nID = 0,int nIconNormal = -1);  
  BOOL InsertODMenu(UINT nPosition,LPCTSTR lpstrText,UINT nFlags,UINT nID,CImageList *il,int xoffset);

  // functions for modifying a menu option, use the ModifyODMenu call (see above define)
  BOOL ModifyODMenu(LPCTSTR lpstrText,UINT nID=0,int nIconNormal=-1);
  BOOL ModifyODMenu(LPCTSTR lpstrText,UINT nID,CImageList *il,int xoffset);
  BOOL ModifyODMenu(LPCTSTR lpstrText,UINT nID,CBitmap *bmp);
  BOOL ModifyODMenu(LPCTSTR lpstrText,LPCTSTR OptionText,int nIconNormal);
  // use this method for adding a solid/hatched colored square beside a menu option
  // courtesy of Warren Stevens
  BOOL ModifyODMenu(LPCTSTR lpstrText,UINT nID,COLORREF fill,COLORREF border,int hatchstyle=-1);

  // for deleting and removing menu options
  BOOL  DeleteMenu(UINT uiId,UINT nFlags);
  BOOL  RemoveMenu(UINT uiId,UINT nFlags);
  int RemoveMenu(LPCTSTR pText, ESeperator sPos=CNewMenu::NONE);

  // function for retrieving and setting a menu options text (use this function
  // because it is ownerdrawn)
  BOOL GetMenuText(UINT id,CString &string,UINT nFlags = MF_BYPOSITION);
  BOOL SetMenuText(UINT id,CString string, UINT nFlags = MF_BYPOSITION);

  // Getting a submenu from it's name or position
  CMenu* GetSubMenu (LPCTSTR lpszSubMenuName);
  CMenu* GetSubMenu (int nPos);
  int GetMenuPosition(LPCTSTR pText);

  // Destoying
  virtual BOOL DestroyMenu();

  // Drawing: 
  // Draw an item
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
  // Measure an item  
  virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
  // Draw title of the menu
  virtual void DrawTitle(LPDRAWITEMSTRUCT lpDIS,BOOL bIsMenuBar);
  // Erase the Background of the menu
  virtual BOOL EraseBkgnd(HWND hWnd,HDC hDC);

  BOOL SetMenuTitle(LPCTSTR pTitle,UINT nTitleFlags=MFT_TOP_TITLE);
  BOOL RemoveMenuTitle();

  // Function to set how menu is drawn, either original or XP style
  static int  GetMenuDrawMode();
  static void SetMenuDrawMode(UINT mode);
  // Function to set how disabled items are drawn 
  //(mode=FALSE means they are not drawn selected)
  static BOOL SetSelectDisableMode(BOOL mode);
  static BOOL GetSelectDisableMode();

  // Static functions used for handling menu's in the mainframe
  static LRESULT FindKeyboardShortcut(UINT nChar,UINT nFlags,CMenu *pMenu);
  static BOOL OnMeasureItem(const MSG* pMsg);
  static void OnInitMenuPopup(HWND hWnd, CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);

  static CMenu* FindPopupMenuFromID(CMenu* pMenu, UINT nID);
  static CMenu* FindPopupMenuFromID(HMENU hMenu, UINT nID);

  static CMenu* FindPopupMenuFromIDData(CMenu* pMenu, UINT nID, ULONG_PTR pData);
  static CMenu* FindPopupMenuFromIDData(HMENU hMenu, UINT nID, ULONG_PTR pData);

  virtual void OnInitMenuPopup();
  virtual BOOL OnUnInitPopupMenu();

  // Customizing:
  // Set icon size
  void SetIconSize (int, int); 
  // set the color in the bitmaps that is the background transparent color
  COLORREF SetBitmapBackground(COLORREF newColor);
  COLORREF GetBitmapBackground(); 

  CRect GetLastActiveMenuRect();
  HMENU GetParent();
  BOOL IsPopup();
  void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
  {
		m_StyleMenu=dwDsp;
  }  

// Miscellaneous Protected Member functions
protected:
  BOOL Replace(UINT nID,UINT nNewID);

  static BOOL IsNewShell();
  BOOL IsMenuBar(HMENU hMenu=NULL);

  void SetLastMenuRect(HDC hDC, LPRECT pRect);

  CNewMenuItemData* FindMenuItem(UINT nID);
  CNewMenu* FindMenuOption(int nId, int& nLoc);
  CNewMenu* FindMenuOption(LPCTSTR lpstrText, int& nLoc);

  CNewMenu* FindAnotherMenuOption(int nId,int& nLoc,CArray<CNewMenu*,CNewMenu*>&newSubs,CArray<int,int&>&newLocs);

  void DrawCheckMark(CDC* pDC,int x,int y,COLORREF color);
  void DrawRadioDot(CDC* pDC,int x,int y,COLORREF color);
  CNewMenuItemData* NewODMenu(UINT pos,UINT nFlags,UINT nID,LPCTSTR string);

  void SynchronizeMenu();
  void InitializeMenuList(int value);
  void DeleteMenuList();
  
  CNewMenuItemData* FindMenuList(UINT nID);

  void DrawSpecial_OldStyle(CDC* pDC, LPCRECT pRect, UINT nID, DWORD dwStyle);
  void DrawSpecial_WinXP(CDC* pDC, LPCRECT pRect, UINT nID, DWORD dwStyle);
  void DrawSpecialCharStyle(CDC* pDC, LPCRECT pRect, TCHAR Sign, DWORD dwStyle);
  void DrawSpecialChar(CDC* pDC, LPCRECT pRect, TCHAR Sign, BOOL bBold);

  void DrawMenuTitle(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar);

  // Measure an item
  void MeasureItem_OldStyle( LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenuBar); 
  void DrawItem_OldStyle (LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenubar);
  BOOL Draw3DCheckmark(CDC* dc, const CRect& rc,HBITMAP hbmCheck, DWORD dwStyle);

  void MeasureItem_WinXP( LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenuBar); 
  void DrawItem_WinXP (LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar);

  void DrawItem_SpecialStyle (LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenubar);

  BOOL ImageListDuplicate(CImageList* il,int xoffset,CImageList* newlist);
  static WORD NumBitmapColors(LPBITMAPINFOHEADER lpBitmap);
  void ColorBitmap(CDC* pDC, CBitmap& bmp,CSize size,COLORREF fill,COLORREF border,int hatchstyle=-1);
  void SetMBar(CMenuButton *pBar);
  
// Member Variables
public:
  static int cCOLOR_MENUBAR;
  static DWORD m_StyleMenu;		//new variable for guitoolkit
 
protected: 
  // Stores list of menu items
  CTypedPtrArray<CPtrArray, CNewMenuItemData*> m_MenuList;   
  // When loading an owner-drawn menu using a Resource, CNewMenu must keep track of
  // the popup menu's that it creates. Warning, this list *MUST* be destroyed
  // last item first :)
  // Stores list of sub-menus
  CTypedPtrArray<CPtrArray, HMENU>  m_SubMenus;
  // Stores a list of all CNewMenu's ever created 
  static CTypedPtrArray<CPtrArray, HMENU>  m_AllSubMenus;
  static BOOL m_bSelectDisable;
  static CMenuTheme* m_pActMenuDrawing;
  	
  int m_iconX;
  int m_iconY;

  COLORREF m_bitmapBackground;

  CImageList* checkmaps;
  BOOL checkmapsshare;

  int m_selectcheck;
  int m_unselectcheck;

  BOOL m_bDynIcons;

  HMENU m_hParentMenu;

  BOOL m_bIsPopupMenu;

  CRect m_LastActiveMenuRect;

  DWORD m_dwOpenMenu;
};


#pragma warning(pop)

#endif // __CNewMenu_H_
