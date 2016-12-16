// DlgUser.cpp : implementation file
//

#include "stdafx.h"
#include "collect.h"
#include "DlgUser.h"
#include "DlgNewUser.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUser dialog


CDlgUser::CDlgUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUser)
	m_nRoal = -1;
	m_sPassword = _T("");
	m_sUsername = _T("");
	//}}AFX_DATA_INIT
}


void CDlgUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUser)
	DDX_Control(pDX, IDC_CMB_USER, m_oUsers);
	DDX_CBIndex(pDX, IDC_CMB_ROAL, m_nRoal);
	DDX_Text(pDX, IDC_EDIT1_USER_PASSWORD, m_sPassword);
	DDX_CBString(pDX, IDC_CMB_USER, m_sUsername);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUser, CDialog)
	//{{AFX_MSG_MAP(CDlgUser)
	ON_CBN_SELCHANGE(IDC_CMB_ROAL, OnSelchangeCmbRoal)
	ON_BN_CLICKED(IDC_BTN_USER_LOGINOUT, OnBtnUserLoginout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUser message handlers


BOOL CDlgUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgUser::OnSelchangeCmbRoal()
{
	tagUser  user;
    UpdateData(TRUE);
	m_oUsers.ResetContent();


    for (int i=0;i<users.m_list.GetSize();i++)
    {
         if (users.m_list[i].roalIndex==this->m_nRoal)
         {
			 m_oUsers.AddString(users.m_list[i].username);
         }
    }
}

void CDlgUser::OnBtnUserLoginout() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	for ( int i = 0; i < users.m_list.GetSize(); i++ )
	{
        if (users.m_list[i].username==m_sUsername)
		{
			if (users.m_list[i].password==m_sPassword)
			{
				if( MessageBox( " 确定要删除当前用户吗 ? ", "提示", MB_ICONQUESTION | MB_OKCANCEL ) == IDOK )
				{
					users.m_list.RemoveAt(i,1);
					OnSelchangeCmbRoal();                 //刷新列表
					users.Save();            // 保存列表			
					break;    
				}
				else
					break;
			}
			else
			{
				MessageBox("密码错误","提示",MB_OK);
			}
		}
	}
   
	if (i>=users.m_list.GetSize())
	{
		MessageBox("用户未定义","提示",MB_OK);
	}
	if ( (m_nRoal==2) && (m_sUsername=="administrator") && (m_sPassword=="administrator") )
       {
		   users.m_sUser.Empty();
		   users.m_nRoal = 0;
		   return;
    }
    m_sPassword.Empty();
	m_sUsername.Empty();
	UpdateData(FALSE);
   

	



}

