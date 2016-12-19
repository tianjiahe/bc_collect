// DlgNewUser.cpp : implementation file
//

#include "stdafx.h"
#include "collect.h"
#include "DlgNewUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewUser dialog


CDlgNewUser::CDlgNewUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewUser)
	m_sPassword2 = _T("");
	m_sPassword = _T("");
	m_sNewUser = _T("");
	m_bIsAdmin = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgNewUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewUser)
	DDX_Control(pDX, IDC_CHK_REG_ROAL, m_oIsAdmin);
	DDX_Text(pDX, IDC_EDIT_PASSWORD2, m_sPassword2);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_EDIT_NEWUSER, m_sNewUser);
	DDX_Check(pDX, IDC_CHK_REG_ROAL, m_bIsAdmin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewUser, CDialog)
	//{{AFX_MSG_MAP(CDlgNewUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewUser message handlers

BOOL CDlgNewUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_oIsAdmin.EnableWindow((users.m_nRoal>=1));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNewUser::OnOK() 
{
	// TODO: Add extra validation here

	CDlgNewUser::OnOK();
}
