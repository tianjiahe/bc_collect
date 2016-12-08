#if !defined(AFX_COMMSET_H__80121CE0_314B_452B_918B_731DFF0C37B5__INCLUDED_)
#define AFX_COMMSET_H__80121CE0_314B_452B_918B_731DFF0C37B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommSet form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CCommSet : public CFormView
{
protected:
	CCommSet();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCommSet)

// Form Data
public:
	//{{AFX_DATA(CCommSet)
	enum { IDD = IDD_DIALOG_COM };
	CListBox	m_listTxData;
	CListBox	m_listRxData;
	CEdit	m_otxtCurWaveLen;
	CButton	m_obtnDownCmd;
	CButton	m_ochkClockWise;
	CEdit	m_otxtUseWaveLen;
	CEdit	m_otxtStepLen;
	CEdit	m_otxtStartAngle;
	CEdit	m_otxtEndAngle;
	CEdit	m_otxtAngle;
	CComboBox	m_oFrameCmd;
	CComboBox	m_oCommPort;
	CComboBox	m_oStopBit;
	CComboBox	m_oParity;
	CComboBox	m_oDataBits;
	CComboBox	m_oBandRate;
	int			m_nComPort;
	int			m_nCommRate;
	BOOL		m_bCommFlow;
	int			m_nDataBits;
	CString		m_sComStateTip;
	CString	m_sFrameHead;
	CString	m_sFrameTail;
	CString	m_sFrameDisp;
    SHORT	m_wCurWaveLen;
	SHORT	m_wAngle;
    SHORT	m_wStartAngle;
	SHORT	m_wEndAngle;
	SHORT	m_wUseWaveLen;
	BYTE	m_bFrameChk;
	BYTE	m_bStepLen;
	BOOL	m_bClockWise;
	CString	m_sRxDisp;
	//}}AFX_DATA

// Attributes
public:

   
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommSet)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCommSet();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCommSet)
	afx_msg void OnButtonCommApply();
	afx_msg void OnButtonDownFrameCmd();
	afx_msg void OnSelchangeComboFrameCmd();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnReceiveChar(UINT ch, LONG port);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMSET_H__80121CE0_314B_452B_918B_731DFF0C37B5__INCLUDED_)
