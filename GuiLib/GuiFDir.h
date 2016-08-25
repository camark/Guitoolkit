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

#if !defined(AFX_FDIR_H__25E4B82F_FB23_45B2_B475_91668BFF681B__INCLUDED_)
#define AFX_FDIR_H__25E4B82F_FB23_45B2_B475_91668BFF681B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FDir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFDir dialog

class  CFWnd: public CWnd
{
public:
	void OnOpen();
	void OnReSize();
	
	DECLARE_MESSAGE_MAP()
};

class GUILIBDLLEXPORT CGuiFDir : public CFileDialog
{
	DECLARE_DYNAMIC(CGuiFDir)
		
public:
	CGuiFDir(CWnd* parent);
	void OnInitDone();
	void OnFolderChange();
	
public:
	CWnd*		cw;
	CString		m_GetPath;
	CEdit		m_cedit;
	CFWnd		cfwn;

protected:
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FDIR_H__25E4B82F_FB23_45B2_B475_91668BFF681B__INCLUDED_)
