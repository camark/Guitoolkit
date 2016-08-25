// GuiFolderVisio.h: interface for the CGuiFolderVisio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUIFOLDERVISIO_H__1FF06CA7_9692_4721_AA4A_39B001F58236__INCLUDED_)
#define AFX_GUIFOLDERVISIO_H__1FF06CA7_9692_4721_AA4A_39B001F58236__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiControlBar.h"
#include "GuiContainer.h"
#include "GuiVisioFolder.h"
class CGuiFolderVisio : public CGuiControlBar  
{
protected:
	CGuiVisioFolder   m_fv;
	CGuiContainer     m_ctServer;
	CTreeCtrl m_tree;
public:
	CGuiFolderVisio();
	virtual ~CGuiFolderVisio();

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#endif // !defined(AFX_GUIFOLDERVISIO_H__1FF06CA7_9692_4721_AA4A_39B001F58236__INCLUDED_)
