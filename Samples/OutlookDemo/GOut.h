// GOut.h: interface for the CGOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOUT_H__234E6903_71D2_4F19_B70D_216CA6097D32__INCLUDED_)
#define AFX_GOUT_H__234E6903_71D2_4F19_B70D_216CA6097D32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GuiOutLookView.h"
#include "GuiOutLook.h"
class CGOut : public CGuiOutLookView  
{
public:
	CGOut();
	DECLARE_DYNCREATE(CGOut)
	virtual ~CGOut();
public:
	CGuiOutLook out;
	CTreeCtrl tc;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP();
};

#endif // !defined(AFX_GOUT_H__234E6903_71D2_4F19_B70D_216CA6097D32__INCLUDED_)
