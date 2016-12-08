// mainfrm.cpp : implementation of the CMainFrame class
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
#include "typlstvw.h"
#include "intlstvw.h"
#include "dwarryvw.h"
#include "typaryvw.h"
#include "ptarryvw.h"
#include "mapssvw.h"
#include "typtrmap.h"
#include "mapdwvw.h"
#include "CommSet.h"

#include "DlgUser.h"                  // 用户登录，注册对话框


#include "GraphicView.h"              // 图形曲线视图
#include "RealGraphView.h"            // 实时动态曲线视图
#include "Splash.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_RANGE(          ID_STRINGLIST, ID_ON_REAL, OnExample)
	ON_UPDATE_COMMAND_UI_RANGE(ID_STRINGLIST, ID_ON_REAL, OnUpdateExampleUI)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_DATA_SAVE, OnButtonDataSave)
	ON_COMMAND(ID_VIEW_OPER_BAR, OnViewOperBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OPER_BAR, OnUpdateViewOperBar)
	ON_COMMAND(ID_MENU_USER, OnMenuUser)
	ON_BN_CLICKED(IDC_CHECK_START_SCAN, OnCheckStartScan)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_COMMAND(ID_COMMSET, OnCommset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
		ID_SEPARATOR,
	ID_FILE_PRINT,
	ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nCurrentExample = ID_STRINGLIST;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
    EnableDocking(CBRS_ALIGN_ANY);						 // 框架允许控件停泊在任意位置


/**/
    // 自定义的工具框
	if (!m_wndOpBar.Create(this, m_wndOpBar.IDD,  //IDD_DIALOG_OPERATE_TOOLBAR,
		                   WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,
						   IDD_DIALOG_OPERATE_TOOLBAR))
	{
		TRACE0("Failed to create COperateTool bar!\n");
		return -1;
    }
    m_wndOpBar.SetWindowText(_T("操作工具栏"));


/**/
	if (!m_wndCmdBar.Create(this, m_wndCmdBar.IDD,   //IDD_DIALOG_COMMAND_TOOLBAR,
		                    WS_CHILD|WS_VISIBLE|CBRS_RIGHT|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC,
		                    IDD_DIALOG_COMMAND_TOOLBAR))
	{
		TRACE0("Failed to create CCommand Tool bar!\n");
		return -1;
    }
    m_wndCmdBar.SetWindowText(_T("命令工具栏"));

    if(!m_wndReBar.Create(this))
	{
        TRACE0("Failed to create CReBar tool bar!\n");
		return -1;
	}
    // 暂不用reBar,导致主框架出现洞Bar出现
	//m_wndReBar.AddBar(&m_wndToolBar, NULL,NULL, RBBS_GRIPPERALWAYS|RBBS_FIXEDBMP);
    //m_wndReBar.AddBar(&m_wndCmdBar,NULL,NULL, RBBS_GRIPPERALWAYS|RBBS_FIXEDBMP);  

    
	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);                 // 工具栏只允许停泊在顶部
	m_wndCmdBar.EnableDocking(CBRS_ALIGN_TOP);                  // 命令栏只允许停泊在顶部 
	m_wndOpBar.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT); // 操作栏允许停泊在左右
	
    //作用： 双击控件可浮出框架外
	DockControlBar(&m_wndToolBar);                              // 工具栏按照顺序最先停泊在顶区域
    DockControlBar(&m_wndCmdBar,AFX_IDW_DOCKBAR_TOP);             // 命令栏次之
	//DockControlBar(&m_wndOpBar);                                  //                       
	DockControlBar(&m_wndOpBar, AFX_IDW_DOCKBAR_RIGHT);
    
    


    
	// 状态栏
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
    

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
	Sleep(2000);
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnExample(UINT nCmdID)
{
	if (nCmdID == m_nCurrentExample)                       // 菜单中选中一个不同的视图选项后
		return;  // already selected

	// Set the child window ID of the active view to AFX_IDW_PANE_FIRST.
	// This is necessary so that CFrameWnd::RecalcLayout will allocate
	// this "first pane" to that portion of the frame window's client
	// area not allocated to control bars.  Set the child ID of
	// the previously active view to some other ID; we will use the
	// command ID as the child ID.
	CView* pOldActiveView = GetActiveView();               // 框架返回当前活动的视图
		::SetWindowLong(pOldActiveView->m_hWnd, GWL_ID, m_nCurrentExample);  //set command ID as the child ID

	CRuntimeClass* pNewViewClass;
	switch (nCmdID)
	{
		case ID_STRINGLIST:			pNewViewClass = RUNTIME_CLASS(CStringListView);			break;
		case ID_TYPEDLIST:			pNewViewClass = RUNTIME_CLASS(CTypedPtrListView);		break;
		case ID_INTLIST:			pNewViewClass = RUNTIME_CLASS(CIntListView);			break;
		case ID_DWORDARRAY:			pNewViewClass = RUNTIME_CLASS(CDWordArrayView);			break;
		case ID_TYPEDPTRARRAY:		pNewViewClass = RUNTIME_CLASS(CTypedPtrArrayView);		break;
		case ID_POINTARRAY:			pNewViewClass = RUNTIME_CLASS(CPointArrayView);			break;
		case ID_MAPSTRINGTOSTRING:	pNewViewClass = RUNTIME_CLASS(CMapStringToStringView);	break;
		case ID_TYPEDPTRMAP:		pNewViewClass = RUNTIME_CLASS(CTypedPtrMapView);		break;
		case ID_MAPDWORDTOMYSTRUCT:	pNewViewClass = RUNTIME_CLASS(CMapDWordToMyStructView);	break;
		case ID_GRAPH_VIEW:			pNewViewClass = RUNTIME_CLASS(CGraphicView);			break;
        case ID_ON_REAL:			pNewViewClass = RUNTIME_CLASS(CRealGraphView);			break;
			
		default:			ASSERT(0);			return;
	}

	// create the new view
	CCreateContext context;											// 包括一套框架、视图和文档的指针
	context.m_pNewViewClass = pNewViewClass;						// 新视图的类信息
	context.m_pCurrentDoc   = GetActiveDocument();					// 得到相关文档
	CView* pNewView = STATIC_DOWNCAST(CView, CreateView(&context)); //构造视图对象，由文档和视频类信息
	if (pNewView != NULL)
	{
		pNewView->ShowWindow(SW_SHOW);                             // 新的视图已经构造了,但是未激活显示
        //pNewView->ShowWindow(SW_SHOWMAXIMIZED);
		pNewView->OnInitialUpdate();
		SetActiveView(pNewView);									// 框架显示新构造的视图对象，并激活视图
		RecalcLayout();
		m_nCurrentExample = nCmdID;
		pOldActiveView->DestroyWindow();                            // finally destroy the old view...
	}
}

void CMainFrame::OnUpdateExampleUI(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrentExample);
}

// 对话工具栏的消息路由，是先由框架窗口的命令消息链传递到对话工具栏的按钮上的，这里处理路由
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_wndOpBar.OnCmdMsg(nID,nCode,pExtra,pHandlerInfo))
	{
        return  TRUE;
	}

	if (m_wndCmdBar.OnCmdMsg(nID,nCode,pExtra,pHandlerInfo))
	{
		return TRUE;
	}
	
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnButtonDataSave() 
{
	// TODO: Add your control notification handler code here
	MessageBox("主框架再处理 保存");
}



void CMainFrame::OnViewOperBar() 
{
	// TODO: Add your command handler code here
	DockControlBar(&m_wndOpBar);
	
}

void CMainFrame::OnUpdateViewOperBar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

// 打开用户登录，设置登录信息
void CMainFrame::OnMenuUser() 
{
	// TODO: Add your command handler code here
    CDlgUser   dlg;
	if(dlg.DoModal()==IDOK)	{	MessageBox(_T("当前用户登录成功."));	}
	else					{   MessageBox(_T("当前用户登录失败!"));	}
}


void CMainFrame::OnCheckStartScan() 
{
	// TODO: Add your control notification handler code here
	MessageBox(_T(" MainFrame 处理\n 检测通讯端口\n 检测命令工具条的‘扫描’命令按钮状态\n 启动或停止实时扫描过程"));
	
	OnExample(ID_ON_REAL);									// 启动实时扫描视图

	BOOL btnState = m_wndCmdBar.m_btnStartScan.GetCheck();   // 工具栏命令按钮，为按下状态
	if(  btnState )
	{
		m_bIsScan = 1;
		m_wndCmdBar.m_bStartScan = m_bIsScan;
		(CRealGraphView *)GetActiveView()->SetTimer( 1, 100, NULL );
	}
	else 
	{
		m_bIsScan = 0;
		m_wndCmdBar.m_bStartScan = m_bIsScan;
        (CRealGraphView *)GetActiveView()->KillTimer( 1 );
	}
  	
}

void CMainFrame::OnButton1() 
{
	// TODO: Add your control notification handler code here
	MessageBox("打开当前的扫描的样品曲线图\n带游标带点显示，显示参考曲线");
	OnExample(ID_GRAPH_VIEW);
	
	
}

void CMainFrame::OnCommset() 
{
	// TODO: Add your command handler code here
	
	UINT nCmdID = ID_COMMSET; 
		if ( nCmdID == m_nCurrentExample)                       // 菜单中选中一个不同的视图选项后
		    return;                                                 // already selected

	CView* pOldActiveView = GetActiveView();               // 框架返回当前活动的视图
		::SetWindowLong(pOldActiveView->m_hWnd, GWL_ID, m_nCurrentExample);  //set command ID as the child ID

	CRuntimeClass* pNewViewClass = RUNTIME_CLASS(CCommSet);	
	// create the new view
	CCreateContext context;											// 包括一套框架、视图和文档的指针
	context.m_pNewViewClass = pNewViewClass;						// 新视图的类信息
	context.m_pCurrentDoc   = GetActiveDocument();					// 得到相关文档

	CView* pNewView = STATIC_DOWNCAST(CView, CreateView(&context)); // 构造视图对象，由文档和视频类信息
	                                                                // 注意：FormView的对话框资源属性设置为
																	// 无边框+子窗体，否则创建视图会失败 
	if (pNewView != NULL)
	{
		pNewView->ShowWindow(SW_SHOW);                             // 新的视图已经构造了,但是未激活显示
        //pNewView->ShowWindow(SW_SHOWMAXIMIZED);
		pNewView->OnInitialUpdate();
		SetActiveView(pNewView);									// 框架显示新构造的视图对象，并激活视图
		RecalcLayout();
		m_nCurrentExample = nCmdID;
		pOldActiveView->DestroyWindow();                            // finally destroy the old view...
	}
}


