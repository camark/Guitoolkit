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
 * -igor1960																*	
 ****************************************************************************/

#if !defined(AFX_STDAFX_H__42A0B087_D792_11D4_B90C_000000000000__INCLUDED_)
#define AFX_STDAFX_H__42A0B087_D792_11D4_B90C_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

//#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
//#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxrich.h>

// GUILIB_EXPORTS should normally be defined in the compiler preprocessor setting,
// if not define it here to export the class(es) or functions in this dll.
#if defined _AFXDLL && !defined _GUILIB_STATIC_
	#ifndef GUILIB_EXPORTS
		#define GUILIB_EXPORTS
	#endif //GUILIB_EXPORTS
#endif // _AFXDLL && !defined _GUILIB_STATIC_

// Automatic library selection macro, will not be defined in the dll user-application,
// and will make sure the correct export library is automatically linked to the
// application.
#define _GUILIB_NOAUTOLIB

#define 	GUISTYLE_XP   0x08001 	
#define		GUISTYLE_2003 0x08002
#define		GUISTYLE_2003MENUBTN 0x08021
#define		WIN_NT		  0x08003 	
#define		WIN_2000	0x08004
#define		WIN_XP		0x08005
#define		WIN_95		0x08006
#define		WIN_98		0x08007
#define		WIN_32		0x08008
#define		WIN_ME		0x08009
#define		WIN_95OSR2	0x0800A
#define		WIN_98_SE	0x0800B
 	
#include "GuiLib.h"
#include "GuiLibRes.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__42A0B087_D792_11D4_B90C_000000000000__INCLUDED_)
