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
// COperteToolBar dialog, ��Ϊ�򵼲��ṩ�������ɶԻ��������ģ���Ҫ�ĵ�CDialogBarΪ���࣬

COperteToolBar::COperteToolBar(CWnd* pParent /*=NULL*/)
	
{
	//{{AFX_DATA_INIT(COperteToolBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COperteToolBar::DoDataExchange(CDataExchange* pDX)
{
	//CDialog::DoDataExchange(pDX);                           //�ģ���DDX�󶨺����еļ̳й�ϵȥ��
	//{{AFX_DATA_MAP(COperteToolBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(COperteToolBar, CDialogBar)
	//{{AFX_MSG_MAP(COperteToolBar)
		ON_MESSAGE(WM_INITDIALOG,OnInitDialog)     // �ģ������Ϣӳ�亯������ʼ��������Ϣ��δ���ص���Ϣӳ���ڣ���Ҫ�ֹ�
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperteToolBar message handlers
//�޸�OnInitDialog�������˺�����δ���ݲ���������������������Ҫ�������ݲ���
BOOL COperteToolBar::OnInitDialog(UINT wParam,LONG lParam)
{
	//CDialogBar::OnInitDialog();
	// TODO: Add extra initialization here
	
	BOOL bRet = HandleInitDialog(wParam,lParam);
	
	if (!UpdateData(FALSE))
	{
		TRACE("InitOperteToolBar Failed��");
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	
	// EXCEPTION: OCX Property Pages should return FALSE
	
}

