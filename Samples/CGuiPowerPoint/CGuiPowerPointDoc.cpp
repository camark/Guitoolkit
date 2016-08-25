// CGuiPowerPointDoc.cpp : implementation of the CCGuiPowerPointDoc class
//

#include "stdafx.h"
#include "CGuiPowerPoint.h"

#include "CGuiPowerPointDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointDoc

IMPLEMENT_DYNCREATE(CCGuiPowerPointDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGuiPowerPointDoc, CDocument)
	//{{AFX_MSG_MAP(CCGuiPowerPointDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointDoc construction/destruction

CCGuiPowerPointDoc::CCGuiPowerPointDoc()
{
	// TODO: add one-time construction code here

}

CCGuiPowerPointDoc::~CCGuiPowerPointDoc()
{
}

BOOL CCGuiPowerPointDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointDoc serialization

void CCGuiPowerPointDoc::Serialize(CArchive& ar)
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
// CCGuiPowerPointDoc diagnostics

#ifdef _DEBUG
void CCGuiPowerPointDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGuiPowerPointDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGuiPowerPointDoc commands
