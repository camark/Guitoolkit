// CGuiOfficeDemoDoc.cpp : implementation of the CCGuiOfficeDemoDoc class
//

#include "stdafx.h"
#include "CGuiOfficeDemo.h"

#include "CGuiOfficeDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoDoc

IMPLEMENT_DYNCREATE(CCGuiOfficeDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGuiOfficeDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CCGuiOfficeDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoDoc construction/destruction

CCGuiOfficeDemoDoc::CCGuiOfficeDemoDoc()
{
	// TODO: add one-time construction code here

}

CCGuiOfficeDemoDoc::~CCGuiOfficeDemoDoc()
{
}

BOOL CCGuiOfficeDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoDoc serialization

void CCGuiOfficeDemoDoc::Serialize(CArchive& ar)
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
// CCGuiOfficeDemoDoc diagnostics

#ifdef _DEBUG
void CCGuiOfficeDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGuiOfficeDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGuiOfficeDemoDoc commands
