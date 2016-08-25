// CGuiTabbedDemoDoc.cpp : implementation of the CCGuiTabbedDemoDoc class
//

#include "stdafx.h"
#include "CGuiTabbedDemo.h"

#include "CGuiTabbedDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoDoc

IMPLEMENT_DYNCREATE(CCGuiTabbedDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGuiTabbedDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CCGuiTabbedDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoDoc construction/destruction

CCGuiTabbedDemoDoc::CCGuiTabbedDemoDoc()
{
	// TODO: add one-time construction code here

}

CCGuiTabbedDemoDoc::~CCGuiTabbedDemoDoc()
{
}

BOOL CCGuiTabbedDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoDoc serialization

void CCGuiTabbedDemoDoc::Serialize(CArchive& ar)
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
// CCGuiTabbedDemoDoc diagnostics

#ifdef _DEBUG
void CCGuiTabbedDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGuiTabbedDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGuiTabbedDemoDoc commands
