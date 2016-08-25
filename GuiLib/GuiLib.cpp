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

#ifndef _GUILIB_STATIC_

#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE GuiLibDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
	
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("GUILIB.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(GuiLibDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		#ifndef _GUILIB_IN_OTHER_DLL
			new CDynLinkLibrary(GuiLibDLL);
		#endif	// _GUILIB_IN_OTHER_DLL

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("GUILIB.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(GuiLibDLL);
	}

	return 1;   // ok
}


#ifdef _GUILIB_IN_OTHER_DLL
	GUILIBDLLEXPORT void GuiToolKitDllInitialize()
	{
		new CDynLinkLibrary(GuiLibDLL);
	}
#endif	// _GUILIB_IN_OTHER_DLL

#endif //_GUILIB_STATIC_