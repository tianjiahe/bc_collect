// CmdToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "collect.h"
#include "CmdToolBar.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmdToolBar dialog


CCmdToolBar::CCmdToolBar(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CCmdToolBar)
	m_bStartScan = FALSE;
	//}}AFX_DATA_INIT
}


void CCmdToolBar::DoDataExchange(CDataExchange* pDX)
{
	//CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCmdToolBar)
	DDX_Control(pDX, IDC_CHECK_START_SCAN, m_btnStartScan);
	DDX_Check(pDX, IDC_CHECK_START_SCAN, m_bStartScan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCmdToolBar, CDialogBar)
	//{{AFX_MSG_MAP(CCmdToolBar)
	    ON_MESSAGE(WM_INITDIALOG,OnInitDialog) 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmdToolBar message handlers

BOOL CCmdToolBar::OnInitDialog(UINT wParam,LONG lParam) 
{
	//CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	BOOL bRet = HandleInitDialog(wParam,lParam);
	
	if (!UpdateData(FALSE))
	{
		TRACE("Init OperteToolBar Failed£¡");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

