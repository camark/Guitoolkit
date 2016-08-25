// CGuiAccessDoc.cpp : implementation of the CCGuiAccessDoc class
//

#include "stdafx.h"
#include "CGuiAccess.h"

#include "CGuiAccessDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessDoc

IMPLEMENT_DYNCREATE(CCGuiAccessDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGuiAccessDoc, CDocument)
	//{{AFX_MSG_MAP(CCGuiAccessDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessDoc construction/destruction

CCGuiAccessDoc::CCGuiAccessDoc()
{
	// TODO: add one-time construction code here

}

CCGuiAccessDoc::~CCGuiAccessDoc()
{
}

BOOL CCGuiAccessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessDoc serialization

void CCGuiAccessDoc::Serialize(CArchive& ar)
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
// CCGuiAccessDoc diagnostics

#ifdef _DEBUG
void CCGuiAccessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGuiAccessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGuiAccessDoc commands
