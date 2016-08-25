/****************************************************************************
 *																			*		 
 *								GuiToolKit  								*	
 * (MFC extension)								*			 
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

#if !defined(AFX_GUIDOCKCONTEXT_H__B30C848F_0A82_46A1_BAE2_E2C73CE5C2BB__INCLUDED_)
#define AFX_GUIDOCKCONTEXT_H__B30C848F_0A82_46A1_BAE2_E2C73CE5C2BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GUILIBDLLEXPORT CGuiDockContext: public CDockContext
{
public:
	// Construction
	CGuiDockContext(CControlBar* pBar);
	
	// Attributes
	
	virtual void StartDrag(CPoint pt);
	void Move(CPoint pt);       // called when mouse has moved
	void EndDrag();             // drop
	void OnKey(int nChar, BOOL bDown);
	void AdjustWindowForFloat(CRect& rect);
	// Resize Operations
	virtual void StartResize(int nHitTest, CPoint pt);
	void Stretch(CPoint pt);
	void EndResize();
	int  VerLeft(int i, int nSize, CDockBar* pDockBar, CControlBar* pBar);
	int  VerRight(int i, int nSize, CDockBar* pDockBar, CControlBar* pBar);
	// Double Click Operations
	virtual void ToggleDocking();
	
	// Operations
	void InitLoop();
	void CancelLoop();
	DWORD CanDock(CRect rect, DWORD dwDockStyle,
		CDockBar** ppDockBar = NULL); // called 
	// Implementation
public:
	~CGuiDockContext();
	BOOL Track();
	BOOL bFirstClic;
	BOOL bSecondClic;
	void DrawFocusRect(BOOL bRemoveRect = FALSE);
	// draws the correct outline
	void UpdateState(BOOL* pFlag, BOOL bNewValue);
	DWORD CanDock();
	CDockBar* GetDockBar(DWORD dwOverDockStyle);
};

#endif // !defined(AFX_GUIDOCKCONTEXT_H__B30C848F_0A82_46A1_BAE2_E2C73CE5C2BB__INCLUDED_)
