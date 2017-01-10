#if !defined(AFX_DLGUSER_H__7E1AED1E_09B9_4CC7_9CED_CFF9D9F7E65C__INCLUDED_)
#define AFX_DLGUSER_H__7E1AED1E_09B9_4CC7_9CED_CFF9D9F7E65C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUser dialog

class CDlgUser : public CDialog
{
// Construction
public:
	CDlgUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUser)
	enum { IDD = IDD_DIALOG_USER };
	CComboBox	m_oUsers;
	int		m_nRoal;
	CString	m_sPassword;
	CString	m_sUsername;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUser)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCmbRoal();
	afx_msg void OnBtnUserLoginout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSER_H__7E1AED1E_09B9_4CC7_9CED_CFF9D9F7E65C__INCLUDED_)
