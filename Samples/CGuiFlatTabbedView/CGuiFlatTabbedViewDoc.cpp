// CGuiFlatTabbedViewDoc.cpp : implementation of the CCGuiFlatTabbedViewDoc class
//

#include "stdafx.h"
#include "CGuiFlatTabbedView.h"

#include "CGuiFlatTabbedViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGuiFlatTabbedViewDoc

IMPLEMENT_DYNCREATE(CCGuiFlatTabbedViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGuiFlatTabbedViewDoc, CDocument)
	//{{AFX_MSG_MAP(CCGuiFlatTabbedViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGuiFlatTabbedViewDoc construction/destruction

CCGuiFlatTabbedViewDoc::CCGuiFlatTabbedViewDoc()
{
	// TODO: add one-time construction code here

}

CCGuiFlatTabbedViewDoc::~CCGuiFlatTabbedViewDoc()
{
}

BOOL CCGuiFlatTabbedViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCGuiFlatTabbedViewDoc serialization

void CCGuiFlatTabbedViewDoc::Serialize(CArchive& ar)
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
// CCGuiFlatTabbedViewDoc diagnostics

#ifdef _DEBUG
void CCGuiFlatTabbedViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGuiFlatTabbedViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGuiFlatTabbedViewDoc commands
