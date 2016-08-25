// GuiButtonDoc.cpp : implementation file
//

#include "stdafx.h"
#include "GuiButtonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiButtonDoc

CGuiButtonDoc::CGuiButtonDoc()
{
}

CGuiButtonDoc::~CGuiButtonDoc()
{
}


BEGIN_MESSAGE_MAP(CGuiButtonDoc, CWnd)
	//{{AFX_MSG_MAP(CGuiButtonDoc)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGuiButtonDoc message handlers

BOOL CGuiButtonDoc::Create(DWORD dwStyle, CWnd* pParentWnd, UINT nID)
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(NULL, NULL, dwStyle, CRect(0,0,0,0), pParentWnd, nID, NULL);
}

int CGuiButtonDoc::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CGuiButtonDoc::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}
