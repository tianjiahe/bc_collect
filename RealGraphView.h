#if !defined(AFX_REALGRAPHVIEW_H__BE580670_2752_4CAF_AB99_6647932CD617__INCLUDED_)
#define AFX_REALGRAPHVIEW_H__BE580670_2752_4CAF_AB99_6647932CD617__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RealGraphView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRealGraphView view

class CRealGraphView : public CView
{
protected:
	CRealGraphView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRealGraphView)

// Attributes
	int		m_nRealTimeCounter;
    int		m_nSinCounter;
	HWND	m_hPE;
	BOOL	m_canReal;
	BOOL	m_Real;

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
	//{{AFX_VIRTUAL(CRealGraphView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRealGraphView();
	void     drawRealCur();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRealGraphView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALGRAPHVIEW_H__BE580670_2752_4CAF_AB99_6647932CD617__INCLUDED_)
