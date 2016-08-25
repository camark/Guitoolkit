/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *                            (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software; so you are free to use it any of your		*
 * applications(Freeware, Shareware, Commercial), but leave this header		*
 * intact.																	*
 *																			*
 * These files are provided "as is" without warranty of any kind.			*
 *																			*
 *			       GuiToolKit is forever FREE CODE !!!!!					*
 *																			*
 *--------------------------------------------------------------------------*
 * Created by: Francisco Campos G.											*
 * Bug Fixes and improvements :(Add your name)								*
 * -Francisco Campos														*				
 *																			*	
 ****************************************************************************/



////////////////////////////////////////////////////////////////
// 199 Microsoft Systems Journal. 
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// ==========================================================================  
// HISTORY:	  
// ==========================================================================  
//		1.01	13 Aug 1998 - Andrew Bancroft [ABancroft@lgc.com] - Since we've already 
//							  added the entire toolbar to the imagelist we need to 
//							  increment nNextImage even if we didn't add this button to 
//							  m_mapIDtoImage in the LoadToolbar() method.
//		1.01a	13 Aug 1998	- Peter Tewkesbury - Added AddSingleBitmap(...)
//							  method for adding a single bitmap to a pulldown
//							  menu item.
//		1.02	13 Aug 1998 - Omar L Francisco - Fixed bug with lpds->CtlType
//							  and lpds->itemData item checking.
//		1.03	12 Nov 1998	- Fixes debug assert in system menu. - Wang Jun
//		1.04	17 Nov 1998 - Fixes debug assert when you maximize a view - Wang Jun
//							  window, then try to use the system menu for the view.
//		1.05	09 Jan 1998 - Seain B. Conover [sc@tarasoft.com] - Fix for virtual 
//							  key names.
//		1.06	24 Feb 1999 - Michael Lange [michael.home@topdogg.com] - Fix for memory 
//							  leak in CMyItemData structure, added a destructor that 
//							  calls text.Empty().
//							- Boris Kartamishev [kbv@omegasoftware.com] - Fix for resource
//							  ID bug.
//							- Jeremy Horgan [jeremyhorgan@hotmail.com] - During 
//							  accelerator key processing OnInitMenuPopup() calls 
//							  ConvertMenu() which allocates a new CMyItemData for each 
//						      menu item. This is memory is normally freed by a call to 
//						      OnMenuSelect(), which is not called when processing 
//							  accelerator keys. This results in a memory leak. This was
//							  fixed by modifying the ~CCoolMenuManager() destructor.
//		1.07	24 Feb 1999 - Koji MATSUNAMI [kmatsu@inse.co.jp] - Fixed problem with 
//							  popup menus being drawn correctly as cool menus.
// ==========================================================================
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __COOLMENU_H__
#define __COOLMENU_H__

#include "StdAfx.h"
#include "SubClass.h"

//////////////////
// CCoolMenuManager implements "cool" menus with buttons in them. To use:
//
//  *	Instantiate in your CMainFrame.
//	 * Call Install to install it
//  * Call LoadToolbars or LoadToolbar to load toolbars
//
//  Don't forget to link with CoolMenu.cpp, Subclass.cpp and DrawTool.cpp!
//
class GUILIBDLLEXPORT CCoolMenuManager : private CSubclassWnd 
{
	DECLARE_DYNAMIC(CCoolMenuManager)
public:
	CCoolMenuManager();
	virtual ~CCoolMenuManager();
	
	// You can set these any time
	BOOL m_bShowButtons;			// use to control whether buttons are shown
	BOOL m_bAutoAccel;			// generate auto accelerators
	BOOL m_bUseDrawState;		// use ::DrawState for disabled buttons
	BOOL m_bDrawDisabledButtonsInColor; // draw disabled buttons in color
	// (only if m_bUseDrawState = FALSE)
	
	// public functions to use
	void Install(CFrameWnd* pFrame);					// connect to main frame
	BOOL LoadToolbars(const UINT* arIDs, int n);	// load multiple toolbars
	BOOL LoadToolbar(UINT nID);						// load one toolbar
	BOOL AddSingleBitmap(UINT nBitmapID, UINT n, UINT *nID);
	void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{m_StyleDisplay=dwDsp;}
	// should never need to call:
	virtual void Destroy(); // destroys everything--to re-load new toolbars?
	virtual void Refresh(); // called when system colors, etc change
	static  HBITMAP GetMFCDotBitmap();	// get..
	static  void    FixMFCDotBitmap();	// and fix MFC's dot bitmap
	
	static BOOL bTRACE;	// Set TRUE to see extra diagnostics in DEBUG code
	
protected:
	CFrameWnd*		m_pFrame;		// frame window I belong to
	CUIntArray		m_arToolbarID;	// array of toolbar IDs loaded
	CImageList		m_ilButtons;	// image list for all buttons
	CMapWordToPtr	m_mapIDtoImage;// maps command ID -> image list index
	CMapWordToPtr	m_mapIDtoAccel;// maps command ID -> ACCEL*
	HACCEL			m_hAccel;		// current accelerators, if any
	ACCEL*			m_pAccel;		// ..and table in memory
	CPtrList			m_menuList;		// list of HMENU's initialized
	CSize				m_szBitmap;		// size of button bitmap
	CSize				m_szButton;		// size of button (including shadow)
	CFont				m_fontMenu;		// menu font
	DWORD			m_StyleDisplay;
	// helpers
	void DestroyAccel();
	void DrawMenuText(CDC& dc, CRect rc, CString text, COLORREF color);
	BOOL Draw3DCheckmark(CDC& dc, const CRect& rc, BOOL bSelected,
		HBITMAP hbmCheck = NULL);
	void ConvertMenu(CMenu* pMenu, UINT nIndex, BOOL bSysMenu, BOOL bShowButtons);
	void LoadAccel(HACCEL hAccel);
	CString GetVirtualKeyName(const CString strVirtKey) const;
	BOOL AppendAccelName(CString& sItemName, UINT nID);
	CFont* GetMenuFont();
	void PLSelectRect(CDC& dc, const CRect& rc);
	void DrawSeparator(CRect& rc, CDC& dc);
	void PLNormalRect(CDC& dc, const CRect& rc);
	// Get button index for given command ID, or -1 if not found
	int  GetButtonIndex(WORD nID) 
	{
		void* val;
		return m_mapIDtoImage.Lookup(nID, val) ?(int)val : -1;
	}
	
	// Get ACCEL structure associated with a given command ID
	ACCEL* GetAccel(WORD nID) 
	{
		void* val;
		return m_mapIDtoAccel.Lookup(nID, val) ?(ACCEL*)val : NULL;
	}
	
	// window proc to hook frame using CSubclassWnd implementation
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);
	
	// CSubclassWnd message handlers 
	virtual void OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu);
	virtual BOOL OnMeasureItem(LPMEASUREITEMSTRUCT lpms);
	virtual BOOL OnDrawItem(LPDRAWITEMSTRUCT lpds);
	virtual LONG OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	virtual void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
};

//////////////////
// Friendly version of MENUITEMINFO initializes itself
//

//
// There is a BUG in GeMenuItemInfo => doesn't want to work with WINVER = 5000, => 48 bytes
// we are redifining it here:
// Garbaged Menu Strings and how to Fix it...   igor1960  19:53 31 Jul '02  
 
#ifndef __MENUITEMINFO_LOCAL_DEFINED
#define __MENUITEMINFO_LOCAL_DEFINED
typedef struct tagMENUITEMINFO_LOCAL
{
	UINT cbSize;
	UINT fMask;
	UINT fType; // used if MIIM_TYPE (4.0) or MIIM_FTYPE (>4.0)
	UINT fState; // used if MIIM_STATE
	UINT wID; // used if MIIM_ID
	HMENU hSubMenu; // used if MIIM_SUBMENU
	HBITMAP hbmpChecked; // used if MIIM_CHECKMARKS
	HBITMAP hbmpUnchecked; // used if MIIM_CHECKMARKS
	DWORD dwItemData; // used if MIIM_DATA
	LPTSTR dwTypeData; // used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
	UINT cch; // used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
} MENUITEMINFO_LOCAL;
#endif


struct CMenuItemInfo : public MENUITEMINFO_LOCAL 
{
	CMenuItemInfo()
	{
		memset(this, 0, sizeof(MENUITEMINFO_LOCAL));
		cbSize = sizeof(MENUITEMINFO_LOCAL);
	}
};

#endif // __COOLMENU_H__