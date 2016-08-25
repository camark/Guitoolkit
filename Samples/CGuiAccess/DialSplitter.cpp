// DialSplitter.cpp : implementation file
//

#include "stdafx.h"
#include "CGuiAccess.h"
#include "DialSplitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialSplitter dialog


CDialSplitter::CDialSplitter(CWnd* pParent /*=NULL*/)
	: CDialog(CDialSplitter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialSplitter)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialSplitter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialSplitter)
	DDX_Control(pDX, IDC_SPLITTER, m_Splitter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialSplitter, CDialog)
	//{{AFX_MSG_MAP(CDialSplitter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialSplitter message handlers

BOOL CDialSplitter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	const DWORD dwStyle =WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS ;

	if(!m_TreeServerExplorer.Create(dwStyle,CRect(0,0,0,0),&m_Splitter,3 ))
		return -1;
	if(!m_TreeServerExplorer1.Create(dwStyle,CRect(0,0,0,0),&m_Splitter,4 ))
		return -1;

	m_Splitter.SeTypeALing(CGuiSplitter::ALINGHORZ);//ALINGHORZ
	m_Splitter.SetPixelWidht(2);
	m_Splitter.AddLeftCtrl(&m_TreeServerExplorer,3);
	m_Splitter.AddRightCtrl(&m_TreeServerExplorer1,4);
	m_Splitter.SetStyleSeparator(CGuiSplitter::STYLE3D,
		GuiDrawLayer::GetRGBColorShadow(),GuiDrawLayer::GetRGBColorShadow());
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
