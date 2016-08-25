#pragma once


// CGuiGridLayout

class CControls 
{
public:
	CControl(int nRow, int nCol, CWnd* pWnd);
	~CControl();
	int GetRows();
	int GetCols();
	CWnd* GetCWnd(int nRows,int nCol);
protected:
	CWnd* m_pWnd:
	int m_nRow;
	int m_nCol;
};


class CGuiGridLayout : public CWnd
{
	DECLARE_DYNAMIC(CGuiGridLayout)
public:
	enum GRIDBORDER{ GRIDFLAT=0,GRIDNORMAL=1,GRIDUNDER=2};
public:
	CGuiGridLayout();
	virtual ~CGuiGridLayout();
public:
	void SetBorders(GRIDBORDER GridBorder);
	void SetColors(COLORREF m_clrColor);
	void SetInsets(int nInsets);
	void Add(CWnd* pWnd);
	void Add(int nRow,int nCol, CWnd* pWnd);
	void RecalLayout();
protected:
	int m_NumRows;
	int m_NumCols;
	int m_NumRowsAc;
	int m_NumColsAc;
	int m_nInsets;
	GRIDBORDER m_GridBorder;
	CPtrArray  m_pArray;
	COLORREF   m_clr;
	int nNumItems;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(CWnd* pParentWnd,int nNumRows, int nNumCols);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
};


