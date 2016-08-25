// ToolBarsDemoDoc.cpp : implementation of the CToolBarsDemoDoc class
//

#include "stdafx.h"
#include "ToolBarsDemo.h"

#include "ToolBarsDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoDoc

IMPLEMENT_DYNCREATE(CToolBarsDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolBarsDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CToolBarsDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoDoc construction/destruction

CToolBarsDemoDoc::CToolBarsDemoDoc()
{
	// TODO: add one-time construction code here

}

CToolBarsDemoDoc::~CToolBarsDemoDoc()
{
}

BOOL CToolBarsDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoDoc serialization

void CToolBarsDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoDoc diagnostics

#ifdef _DEBUG
void CToolBarsDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToolBarsDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolBarsDemoDoc commands
