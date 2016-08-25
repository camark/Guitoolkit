// DialUndo.cpp : implementation file
//

#include "stdafx.h"
#include "gui_devstudio.h"
#include "DialUndo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DialUndo dialog


DialUndo::DialUndo(CWnd* pParent /*=NULL*/)
	: CDialog(DialUndo::IDD, pParent)
{
	//{{AFX_DATA_INIT(DialUndo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DialUndo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DialUndo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DialUndo, CDialog)
	//{{AFX_MSG_MAP(DialUndo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DialUndo message handlers
