// intlstvw.h : header file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////
// CIntListView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include <afxcmn.h>
#include "BinEdit.h"

class CIntListView : public CFormView
{
public:
	CIntListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIntListView)

// Attributes
public:
	CCollectDoc* GetDocument();

// Overrides
public:
	void OnInitialUpdate();

// Form Data
public:
	//{{AFX_DATA(CIntListView)
	enum { IDD = IDD_INT_LIST };
	CListCtrl	m_listArgs;
	CBinEdit	m_oTest;
	CComboBox	m_oWavelenOffset;
	CComboBox	m_oWavelenSet;
	CComboBox	m_oSpeedSet;
	CString	m_sTest;
	CString	m_sOutput;
	CString	m_sOnLineState;
	CString	m_sCurWavelen;
	double	m_dCollectGet;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void InitForm(void);
	BOOL WaitforDone(int backCount );
	int  m_nBackCount;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CIntListView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	virtual ~CIntListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CIntListView)
	afx_msg void OnBtnTest();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnCollect();
	afx_msg void OnBtnSpeedSet();
	afx_msg void OnBtnWavelenGoto();
	afx_msg void OnDeltaposSpinWavelenOffset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnReset();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CCollectDoc* CIntListView::GetDocument()
   { return (CCollectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
