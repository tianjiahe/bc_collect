#if !defined(AFX_CMDTOOLBAR_H__66F2E017_79D1_4259_97C7_506C467C1750__INCLUDED_)
#define AFX_CMDTOOLBAR_H__66F2E017_79D1_4259_97C7_506C467C1750__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CmdToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCmdToolBar dialog

class CCmdToolBar : public CDialogBar
{
// Construction
public:
	CCmdToolBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCmdToolBar)
	enum { IDD = IDD_DIALOG_COMMAND_TOOLBAR };
	CButton	m_btnStartScan;
	BOOL	m_bStartScan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmdToolBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCmdToolBar)
	virtual BOOL OnInitDialog( UINT, LONG );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDTOOLBAR_H__66F2E017_79D1_4259_97C7_506C467C1750__INCLUDED_)
