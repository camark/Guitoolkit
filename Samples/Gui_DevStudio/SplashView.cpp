// SplashView.cpp : implementation file
//

#include "stdafx.h"
#include "gui_devstudio.h"
#include "SplashView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SplashView

IMPLEMENT_DYNCREATE(SplashView, CView)

SplashView::SplashView()
{
}

SplashView::~SplashView()
{
}


BEGIN_MESSAGE_MAP(SplashView, CView)
	//{{AFX_MSG_MAP(SplashView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SplashView drawing

void SplashView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	CDC			m_dc;		
	CBitmap		m_bitmap;
	CRect		rcClient;

	//la idea es tomar el area de la ventana y area  cliente , luego debemos
	//igualar el area de coordenadas de ventana al cliente
	
	GetClientRect(&rcClient);
	m_dc.CreateCompatibleDC(pDC);
	m_bitmap.CreateCompatibleBitmap(&m_dc,rcClient.Width(),rcClient.Height());
	
	CBitmap *m_OldBitmap=m_dc.SelectObject(&m_bitmap);
	CBitmap m_bmp;
	
	if (!m_bmp.LoadBitmap( IDB_SPLASHVIEW ) )
		return;
		
		
	CBitmap* p_bmpOld = m_dc.SelectObject( &m_bmp);

	BITMAP bmInfo;
	
	if ( m_bmp.GetObject( sizeof( bmInfo ), &bmInfo ) != 0 )
	{
		pDC->BitBlt( 0,0, bmInfo.bmWidth, bmInfo.bmHeight, &m_dc, 0,0, SRCCOPY );
	}
	
	m_dc.SelectObject( p_bmpOld );
	m_dc.SelectObject( m_OldBitmap );
	m_bmp.DeleteObject();
	m_dc.DeleteDC();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// SplashView diagnostics

#ifdef _DEBUG
void SplashView::AssertValid() const
{
	CView::AssertValid();
}

void SplashView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// SplashView message handlers
