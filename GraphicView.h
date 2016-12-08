#if !defined(AFX_GRAPHICVIEW_H__ADEA40D8_79D2_4A22_8A7A_0A27E38CA011__INCLUDED_)
#define AFX_GRAPHICVIEW_H__ADEA40D8_79D2_4A22_8A7A_0A27E38CA011__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphicView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphicView view

class CGraphicView : public CView
{
protected:
	CGraphicView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGraphicView)

// Attributes
	int		m_nRealTimeCounter;
    int		m_nSinCounter;
	HWND	m_hPE;

	double	StartTime;
	double	ZoomStart;
	double	ZoomEnd;
	double	ZoomInterval;
	double	ZoomSmallInterval;

public:

// Operations
public:
    
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGraphicView();
	void OnDrawgraph();
	void CreateSimpleSGraph();
	void CreateSimpleGraph();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTest();
	afx_msg void OnButtonDataSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICVIEW_H__ADEA40D8_79D2_4A22_8A7A_0A27E38CA011__INCLUDED_)
