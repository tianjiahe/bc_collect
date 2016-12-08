// OperteToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "collect.h"
#include "OperteToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperteToolBar dialog, 因为向导不提供，这里由对话框派生的，需要改到CDialogBar为基类，

COperteToolBar::COperteToolBar(CWnd* pParent /*=NULL*/)
	
{
	//{{AFX_DATA_INIT(COperteToolBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COperteToolBar::DoDataExchange(CDataExchange* pDX)
{
	//CDialog::DoDataExchange(pDX);                           //改：将DDX绑定函数中的继承关系去掉
	//{{AFX_DATA_MAP(COperteToolBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(COperteToolBar, CDialogBar)
	//{{AFX_MSG_MAP(COperteToolBar)
		ON_MESSAGE(WM_INITDIALOG,OnInitDialog)     // 改：添加消息映射函数，初始化函数消息并未加载到消息映射内，需要手工
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperteToolBar message handlers
//修改OnInitDialog函数，此函数并未传递参数，但是在这里我们需要让它传递参数
BOOL COperteToolBar::OnInitDialog(UINT wParam,LONG lParam)
{
	//CDialogBar::OnInitDialog();
	// TODO: Add extra initialization here
	
	BOOL bRet = HandleInitDialog(wParam,lParam);
	
	if (!UpdateData(FALSE))
	{
		TRACE("InitOperteToolBar Failed！");
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	
	// EXCEPTION: OCX Property Pages should return FALSE
	
}

