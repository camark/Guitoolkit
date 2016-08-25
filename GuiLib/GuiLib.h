/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 *							 (MFC extension)								*			 
 * Created by Francisco Campos G. www.beyondata.com fcampos@beyondata.com	*
 *--------------------------------------------------------------------------*		   
 *																			*
 * This program is free software; so you are free to use it any of your		*
 * applications (Freeware, Shareware, Commercial), but leave this header	*
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

#ifndef __GUILIB_H
#define __GUILIB_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Additional MFC headers
#ifndef __AFXTEMPL_H__
	#include <afxtempl.h>
#endif //__AFXTEMPL_H__

#ifndef __AFXPRIV_H__
	#include <afxpriv.h>
#endif //__AFXPRIV_H__

#if _MSC_VER >= 1300
	#include <..\atlmfc\src\mfc\afximpl.h>
#else
	#include <..\src\afximpl.h>
#endif


#if defined _AFXDLL && !defined _GUILIB_STATIC_
	#ifdef GUILIB_EXPORTS
	   #define GUILIBDLLEXPORT  _declspec(dllexport)
	#else
	   #define GUILIBDLLEXPORT  _declspec(dllimport)
	#endif
#else
	#define GUILIBDLLEXPORT
#endif	 


#ifndef _GUILIB_NOAUTOLIB

#if defined _AFXDLL && !defined _GUILIB_STATIC_
	// MFC shared DLL with GuiToolKit shared DLL
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"GuiTk115ud.lib") 
			#pragma message("Automatically linking with GuiTk115ud.dll")
		#else
			#pragma comment(lib,"GuiTk115d.lib") 
			#pragma message("Automatically linking with GuiTk115d.dll")
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"GuiTk115u.lib") 
			#pragma message("Automatically linking with GuiTk115u.dll") 
		#else
			#pragma comment(lib,"GuiTk115.lib") 
			#pragma message("Automatically linking with GuiTk115.dll") 
		#endif
	#endif
#elif defined _GUILIB_STATIC_
	// MFC shared DLL with GuiToolKit static library
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"GuiTk115Staticuds.lib") 
			#pragma message("Automatically linking with static GuiTk115Staticuds.lib") 
		#else
			#pragma comment(lib,"GuiTk115Staticds.lib") 
			#pragma message("Automatically linking with static GuiTk115Staticds.lib") 
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"GuiTk115Staticus.lib") 
			#pragma message("Automatically linking with static GuiTk115Staticus.lib") 
		#else
			#pragma comment(lib,"GuiTk115Statics.lib") 
			#pragma message("Automatically linking with static GuiTk115Statics.lib") 
		#endif
	#endif
#else
	// MFC static library with GuiToolKit static library
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"GuiTk115Staticud.lib") 
			#pragma message("Automatically linking with static GuiTk115Staticud.lib") 
		#else
			#pragma comment(lib,"GuiTk115Staticd.lib") 
			#pragma message("Automatically linking with static GuiTk115Staticd.lib") 
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"GuiTk115Staticu.lib") 
			#pragma message("Automatically linking with static GuiTk115Staticu.lib") 
		#else
			#pragma comment(lib,"GuiTk115Static.lib") 
			#pragma message("Automatically linking with static GuiTk115Static.lib") 
		#endif
	#endif
#endif

//Thanks to Juno Kampstra for this suggestion 

////////////////////////////////////////////////////////////////////////////////
// Export class headers

#include "GuiLibRes.h"

#include "CBaseTab.h"
#include "CoolMenu.h"
#include "GuiBaseTab.h"
#include "GuiButton.h"
#include "GuiCapOutBar.h"
#include "GuicheckBox.h"
#include "GuiColors.h"
#include "GuiComboBoxExt.h"
#include "GuiContainer.h"
#include "GuiControlBar.h"
#include "GuiDocBarExten.h"
#include "GuiDocBarExtenEx.h"
#include "GuiDockBar.h"
#include "GuiDockContext.h"
#include "GuiDockToolBar.h"
#include "GuiDocSpecial.h"
#include "GuiDrawLayer.h"
#include "GuiDropDownEdit.h"
#include "GuiEdit.h"
#include "GuiFDir.h"
#include "GuiFile.h"
#include "GuiFolder.h"
#include "GuiFrameWnd.h"
#include "GuiGroupBox.h"
#include "GuiheaderCtrl.h"
#include "GuiImageLinkButton.h"
#include "GuiLabelButton.h"
#include "GuiLib.h"
#include "GuiLinkButton.h"
#include "GuiListEdit.h"
#include "GuiMDIFrame.h"
#include "GuiMDITabbed.h"
#include "GuiMiniSplitter.h"
#include "GuiMiniTool.h"
#include "GuiNormalButton.h"
#include "GuiOfficeBar.h"
#include "GuiOutLook.h"
#include "GuiOutLookView.h"
#include "GuiPowerPointView.h"
#include "GuiRadioButton.h"
#include "GuiSliderCtrl.h"
#include "GuiSplitterWnd.h"
#include "GuiStatusBar.h"
#include "GuiTabbed.h"
#include "GuiTabPowerPoint.h"
#include "GuiTabWnd.h"
#include "GuiToolBarWnd.h"
#include "GuiToolButton.h"
#include "GuiVisioFolder.h"
#include "GuiWorkPanel.h"
#include "GuiWorkTab.h"
#include "MenuBar.h"
#include "Subclass.h"
#include "VisualStylesXP.h"
#include "GuiViewWorkTab.h"
#include "GuiView.h"
#include "GuiPanelAccess.h"
#include "GuiMiniFrame.h"
#include "GuiFolderFlat.h"
#include "GuiMiniFrameWnd.h"
#include "GuiSplitter.h"
#include "GuiSysTray.h"

#endif // _GUILIB_NOAUTOLIB

#ifdef _GUILIB_IN_OTHER_DLL
	GUILIBDLLEXPORT void GuiToolKitDllInitialize();
#endif // _GUILIB_IN_OTHER_DLL

#endif //__GUILIB_H


