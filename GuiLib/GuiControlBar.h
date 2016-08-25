/****************************************************************************
 *																			*
 *								GuiToolKit  								*
 *                           (MFC extension)								*
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


#if _MSC_VER > 1000
#pragma once
#endif

#define NORMAL 0
#define OVER   1
#define PRESS  2

#include "GuiDrawLayer.h"

class GUILIBDLLEXPORT   CGuiControlBar : public CControlBar
{
	DECLARE_DYNAMIC(CGuiControlBar)
protected:
	int			nGapGripper;
	UINT		nDockBarAling;
	CSize		m_sizeMinFloating;
	CSize		m_sizeMinFloating1;
	CSize		m_sizeMinFloatingBck; //save the position before/after autohide
	CSize		m_sizeHorz;
	CSize		m_sizeVert;
	CSize		m_sizeHorzt;
	CSize		m_sizeVertt;
	CSize		m_sizeMinV;
	CSize		m_sizeMinH;
	int			m_pos;
	int			m_Last;
	int			m_First;
	CRect		m_rcBorder;
	CRect		m_rcOldBorder;
	BOOL		m_bTracking;
	UINT		m_SideMove;  // Que lado se arrastra
	CPoint		m_ptOld; // la ultima posicion del mouse
	BOOL		m_Initialize; // es cierto si no se ha inicializado esta ventana
	CPoint		m_ptPos;
	CPoint		m_ptStartPos;
	CPoint		m_ptActualPos;
	UINT		m_Orient;
	BOOL		m_bForcepaint;
	CGuiControlBarButton m_CloseBtn; // arreglo de botones para control de la barra
	CGuiControlBarButton m_AutoHideBtn; // arreglo de botones para control de la barra
	CRect		m_rcCloseBtn;
	CRect		m_rcAutoHideBtn;
	int			m_stateBtn;
	int			m_stateAHBtn;
	COLORREF	m_clrFondo;			// para el color de fondo de la barra
	BOOL		m_bAutoHide;
	BOOL		m_bComplete;
	UINT		m_nLastAlingDocking;  //ultimo docking
	UINT		m_nLastAlingDockingBck;
	BOOL		m_IsLoadDocking;
	int			m_nSizeMed;
	CWnd*		pMf;
	HICON		m_hIcon;	//icono para las ventanas autohide
	CImageList  m_Imglist;

public:

	CSize CalcWinPos();

	void SetIcon(UINT hIcon, int cx, int nGrow, COLORREF crMask, int pos=0)
	{
			CBitmap cbmp;
			BITMAP bmp;
			m_Imglist.Create(hIcon,cx,nGrow,crMask);
			cbmp.LoadBitmap(hIcon);
			cbmp.GetBitmap(&bmp);
			m_Imglist.Add(&cbmp,crMask);
			m_hIcon=m_Imglist.ExtractIcon(pos);
		    
	}

	HICON GetIcon(){ return m_hIcon;}

	void SetAutoHide(BOOL bAutoH=FALSE)
	{
		m_bAutoHide=bAutoH;
	}

	void InitAutoHide();

	BOOL GetComplete(){return m_bComplete;}

	UINT GetLastDocking()
	{
		return m_nLastAlingDocking;
	}

	BOOL IsAutoHide() {return m_bAutoHide==TRUE;}
	BOOL IsTracking() {return m_bTracking;}

	UINT  GetDlgID()
	{
		if (m_IsLoadDocking!=TRUE)
			return GetParent()->GetDlgCtrlID();
		else
		{
			m_IsLoadDocking=FALSE;
			switch(m_nLastAlingDocking)
			{
				case CBRS_ALIGN_RIGHT:
					return AFX_IDW_DOCKBAR_RIGHT;
 					break;
				case CBRS_ALIGN_LEFT:
					return AFX_IDW_DOCKBAR_LEFT;
					break;
			
				case CBRS_ALIGN_TOP:
					return AFX_IDW_DOCKBAR_TOP;
					break;
				
				case CBRS_ALIGN_BOTTOM:
					return AFX_IDW_DOCKBAR_BOTTOM;
					break;
			}

		}
		return AFX_IDW_DOCKBAR_LEFT;
	}

	void ScrollOff();
	void ScrollOn();
	void ScrollOnEfect(BOOL On=TRUE);
	virtual void DrawGripper(CDC* pDC, CRect* rc);
	BOOL IsLegal(UINT uAlin);
	CGuiControlBar* GetGuiControlBar(int nPos, BOOL bAll = FALSE) const;
	void AjustReDinSize(CPoint cp);
	void OnActiveWindow();
	void SetEqualWidth();
	int GetHiWid();
	int GetWidthMax();
	int  GetFirstPos();
	int  GetLastPos();

    BOOL IsLeft();
	BOOL IsRight();
	BOOL IsTop();
	BOOL IsBottom();
	BOOL IsVert();
	BOOL IsHorz();
	BOOL IsFloating();
	//autohide
	BOOL IsHideVert();
	BOOL IsHideLeft();
	BOOL IsHideRight();
	BOOL IsHideTop();
	BOOL IsHideBottom();

	void OnInvertTracker(const CRect& rect);
	void OnInvertTrackerH(const CRect& rect);
	void RecalWindowPos();
	void AjustVert(BOOL bGrow, int nDif);
	void AjustHorz(BOOL bGrow, int nDif);
	CRect GetDockRect();
	CRect GetDockRectBck();
	void ActiveCaption();
	void SetColorFondo(COLORREF clrFondo);
	void SaveBar(CString sProfile);
	void LoadStateBar(CString sProfile);
	// esta funcion permite soportar multiples vistas
	void SetSupporMultiView(BOOL bMultiView = TRUE){	m_bSupportMultiView = bMultiView;}
	void StyleDispl(DWORD dwDsp=GUISTYLE_XP)
	{
		m_StyleDisplay=dwDsp;
		m_clrFondo=GuiDrawLayer::GetRGBColorFace(m_StyleDisplay);
		SendMessage(WM_NCPAINT);Invalidate(); UpdateWindow();
	}

	BOOL m_bSupportMultiView;
	void SetMenuContext(UINT MnuContext)
	{
		m_MenuContext = MnuContext;
	};


protected:
	BOOL m_bActive; // esta ventana tiene el foco
	BOOL m_bOldActive;
	UINT m_MenuContext;
	DWORD m_StyleDisplay;
	float	Porc;
public:
	CGuiControlBar();
	virtual ~CGuiControlBar();
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	virtual BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, CWnd* pParentWnd, UINT nID);
	void OnShowTitle();
public:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg void OnNcCalcSize(BOOL, NCCALCSIZE_PARAMS*);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT, CPoint);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysColorChange();
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};


