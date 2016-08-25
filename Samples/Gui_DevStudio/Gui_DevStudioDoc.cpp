// Gui_DevStudioDoc.cpp : implementation of the CGui_DevStudioDoc class
//

#include "stdafx.h"
#include "Gui_DevStudio.h"

#include "Gui_DevStudioDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioDoc

IMPLEMENT_DYNCREATE(CGui_DevStudioDoc, CDocument)

BEGIN_MESSAGE_MAP(CGui_DevStudioDoc, CDocument)
	//{{AFX_MSG_MAP(CGui_DevStudioDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioDoc construction/destruction

CGui_DevStudioDoc::CGui_DevStudioDoc()
{
	// TODO: add one-time construction code here

}

CGui_DevStudioDoc::~CGui_DevStudioDoc()
{
}

BOOL CGui_DevStudioDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioDoc serialization

void CGui_DevStudioDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioDoc diagnostics

#ifdef _DEBUG
void CGui_DevStudioDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGui_DevStudioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGui_DevStudioDoc commands
