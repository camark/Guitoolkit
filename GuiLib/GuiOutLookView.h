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


#if !defined(AFX_GUIOUTLOOKVIEW_H__C539A48F_9650_4AE2_861F_D208728C60A1__INCLUDED_)
#define AFX_GUIOUTLOOKVIEW_H__C539A48F_9650_4AE2_861F_D208728C60A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiFolder.h"


class GUILIBDLLEXPORT CGuiOutLookView : public CView  
{

public:
	DECLARE_DYNCREATE(CGuiOutLookView)

	//*********************************************	
		CGuiOutLookView();
		virtual ~CGuiOutLookView();
	//*********************************************

public:
		CGuiFolder cf;
protected:

		virtual void OnInitialUpdate();
		virtual void OnDraw(CDC* pDC);      // overridden to draw this view

protected:
	
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	//{{AFX_MSG(CGuiOutLookView)
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GUIOUTLOOKVIEW_H__C539A48F_9650_4AE2_861F_D208728C60A1__INCLUDED_)
