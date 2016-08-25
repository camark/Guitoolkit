// GuiVisioDemoDoc.cpp : implementation of the CGuiVisioDemoDoc class
//

#include "stdafx.h"
#include "GuiVisioDemo.h"

#include "GuiVisioDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuiVisioDemoDoc

IMPLEMENT_DYNCREATE(CGuiVisioDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CGuiVisioDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CGuiVisioDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiVisioDemoDoc construction/destruction

CGuiVisioDemoDoc::CGuiVisioDemoDoc()
{
	// TODO: add one-time construction code here

}

CGuiVisioDemoDoc::~CGuiVisioDemoDoc()
{
}

BOOL CGuiVisioDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGuiVisioDemoDoc serialization

void CGuiVisioDemoDoc::Serialize(CArchive& ar)
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
// CGuiVisioDemoDoc diagnostics

#ifdef _DEBUG
void CGuiVisioDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGuiVisioDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGuiVisioDemoDoc commands
