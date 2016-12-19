#if !defined(AFX_DLGNEWUSER_H__CC327530_16A6_43A8_9D49_0C8D24936C97__INCLUDED_)
#define AFX_DLGNEWUSER_H__CC327530_16A6_43A8_9D49_0C8D24936C97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNewUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNewUser dialog

class CDlgNewUser : public CDialog
{
// Construction
public:
	CDlgNewUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNewUser)
	enum { IDD = IDD_DIALOG_NEW_USER };
	CButton	m_oIsAdmin;
	CString	m_sPassword2;
	CString	m_sPassword;
	CString	m_sNewUser;
	BOOL	m_bIsAdmin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewUser)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWUSER_H__CC327530_16A6_43A8_9D49_0C8D24936C97__INCLUDED_)
