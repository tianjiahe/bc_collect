// DlgUser.cpp : implementation file
//

#include "stdafx.h"
#include "collect.h"
#include "DlgUser.h"

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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUser)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUser, CDialog)
	//{{AFX_MSG_MAP(CDlgUser)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUser message handlers
