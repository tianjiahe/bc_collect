// collect.cpp : Defines the class behaviors for the application.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "collect.h"

#include "mainfrm.h"
#include "colledoc.h"
#include "strlstvw.h"
#include "Splash.h"
#include "CommSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCollectApp

BEGIN_MESSAGE_MAP(CCollectApp, CWinApp)
	//{{AFX_MSG_MAP(CCollectApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCollectApp construction

CCollectApp::CCollectApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCollectApp object
//////////////////////////////////////////////////////////////////////////
// 全程对象定义区域
//////////////////////////////////////////////////////////////////////////

//CComOp         theCom;                                     // 串口通讯缓存对象

CSerialCom     theCom;
//

CProtocol      thePtl;                                     // 串口通讯协议
CIniOp         theIni;                                     // 读写ini文件 
CTools         theTools;                                   // 其他工具
CTokenizer     strHelper;                                  // 字符串分解操作工具
CUsers         users;                                       // 用户和权限信息加载


CCollectApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCollectApp initialization

BOOL CCollectApp::InitInstance()
{

//	{	// BLOCK: doc template registration
//		// Register the document template.  Document templates serve
//		// as the connection between documents, frame windows and views.
//		// Attach this form to another document or frame window by changing
//		// the document or frame class in the constructor below.
//		CSingleDocTemplate* pNewDocTemplate = new CSingleDocTemplate(
//			IDR_COMMSET_TMPL,
//			RUNTIME_CLASS(CCollectDoc),		// document class
//			RUNTIME_CLASS(CMainFrame),		// frame class
//			RUNTIME_CLASS(CCommSet));		// view class
//		AddDocTemplate(pNewDocTemplate);
//	}

	// CG: The following block was added by the Splash Screen component.

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

	// Standard initialization

	Enable3dControls();

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register document templates

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCollectDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CStringListView));
	
	AddDocTemplate(pDocTemplate);


	// create a new (empty) document
	OnFileNew();

	 

	//if (m_lpCmdLine[0] != '\0')	{	}
	//if(theCom.CreateCom())      {	theCom.InitCom(); 	                                    }
	//else	                    {   AfxMessageBox( "打开默认串口失败 \n 请配置串口参数!"); 	}
	
    m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CCollectApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCollectApp commands

BOOL CCollectApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}

int CCollectApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	//theCom.CloseCom();
	return CWinApp::ExitInstance();
}

void CAboutDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}
