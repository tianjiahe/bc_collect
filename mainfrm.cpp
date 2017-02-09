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

#include "DlgUser.h"                  // �û���¼
#include "DlgNewUser.h"               // ע��Ի���

#include "GraphicView.h"              // ͼ��������ͼ
#include "RealGraphView.h"            // ʵʱ��̬������ͼ
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
	ON_BN_CLICKED(IDC_BUTTON_DATA_SAVE,		OnButtonDataSave)
	ON_COMMAND(ID_VIEW_OPER_BAR,			OnViewOperBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OPER_BAR,	OnUpdateViewOperBar)
	ON_COMMAND(ID_MENU_USER,				OnMenuUser)
	ON_BN_CLICKED(IDC_CHECK_START_SCAN,		OnCheckStartScan)
	ON_BN_CLICKED(IDC_BUTTON1,				OnButton1)
	ON_COMMAND(ID_COMMSET,					OnCommset)
	ON_COMMAND(ID_MENU_NEW_USER,            OnMenuNewUser)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
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
	
    EnableDocking(CBRS_ALIGN_ANY);						 // �������ؼ�ͣ��������λ��


/**/
    // �Զ���Ĺ��߿�
	if (!m_wndOpBar.Create(this, m_wndOpBar.IDD,  //IDD_DIALOG_OPERATE_TOOLBAR,
		                   WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,
						   IDD_DIALOG_OPERATE_TOOLBAR))
	{
		TRACE0("Failed to create COperateTool bar!\n");
		return -1;
    }
    m_wndOpBar.SetWindowText(_T("����������"));


/**/
	if (!m_wndCmdBar.Create(this, m_wndCmdBar.IDD,   //IDD_DIALOG_COMMAND_TOOLBAR,
		                    WS_CHILD|WS_VISIBLE|CBRS_RIGHT|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC,
		                    IDD_DIALOG_COMMAND_TOOLBAR))
	{
		TRACE0("Failed to create CCommand Tool bar!\n");
		return -1;
    }
    m_wndCmdBar.SetWindowText(_T("�������"));

    if(!m_wndReBar.Create(this))
	{
        TRACE0("Failed to create CReBar tool bar!\n");
		return -1;
	}
    // �ݲ���reBar,��������ܳ��ֶ�Bar����
	//m_wndReBar.AddBar(&m_wndToolBar, NULL,NULL, RBBS_GRIPPERALWAYS|RBBS_FIXEDBMP);
    //m_wndReBar.AddBar(&m_wndCmdBar,NULL,NULL, RBBS_GRIPPERALWAYS|RBBS_FIXEDBMP);  

    
	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);                 // ������ֻ����ͣ���ڶ���
	m_wndCmdBar.EnableDocking(CBRS_ALIGN_TOP);                  // ������ֻ����ͣ���ڶ��� 
	m_wndOpBar.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT); // ����������ͣ��������
	
    //���ã� ˫���ؼ��ɸ��������
	DockControlBar(&m_wndToolBar);                              // ����������˳������ͣ���ڶ�����
    DockControlBar(&m_wndCmdBar,AFX_IDW_DOCKBAR_TOP);             // ��������֮
	//DockControlBar(&m_wndOpBar);                                  //                       
	DockControlBar(&m_wndOpBar, AFX_IDW_DOCKBAR_RIGHT);
    
    


    
	// ״̬��
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

	GetWindowText(m_sWinTitle);            // ���洰�ڱ���
	
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
	if (nCmdID == m_nCurrentExample)
	{
		return;  // already selected
	}

	// Set the child window ID of the active view to AFX_IDW_PANE_FIRST.
	// This is necessary so that CFrameWnd::RecalcLayout will allocate
	// this "first pane" to that portion of the frame window's client
	// area not allocated to control bars.  Set the child ID of
	// the previously active view to some other ID; we will use the
	// command ID as the child ID.
	CView* pOldActiveView = GetActiveView();               // ��ܷ��ص�ǰ�����ͼ
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
	CCreateContext context;											// ����һ�׿�ܡ���ͼ���ĵ���ָ��
	context.m_pNewViewClass = pNewViewClass;						// ����ͼ������Ϣ
	context.m_pCurrentDoc   = GetActiveDocument();					// �õ�����ĵ�
	CView* pNewView = STATIC_DOWNCAST(CView, CreateView(&context)); //������ͼ�������ĵ�����Ƶ����Ϣ
	if (pNewView != NULL)
	{
		pNewView->ShowWindow(SW_SHOW);                             // �µ���ͼ�Ѿ�������,����δ������ʾ
        //pNewView->ShowWindow(SW_SHOWMAXIMIZED);
		pNewView->OnInitialUpdate();
		SetActiveView(pNewView);									// �����ʾ�¹������ͼ���󣬲�������ͼ
		RecalcLayout();
		m_nCurrentExample = nCmdID;
		pOldActiveView->DestroyWindow();                            // finally destroy the old view...
	}
}

void CMainFrame::OnUpdateExampleUI(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrentExample);
}

// �Ի�����������Ϣ·�ɣ������ɿ�ܴ��ڵ�������Ϣ�����ݵ��Ի��������İ�ť�ϵģ����ﴦ��·��
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
	MessageBox("��ǰû����Ҫ����������ļ�\n process in MainFrame::OnButtonDataSave()");
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




void CMainFrame::OnCheckStartScan() 
{
	// TODO: Add your control notification handler code here
	MessageBox(_T(" MainFrame ����\n ���ͨѶ�˿�\n �����������ġ�ɨ�衯���ť״̬\n ������ֹͣʵʱɨ�����"));
	
	OnExample(ID_ON_REAL);									// ����ʵʱɨ����ͼ

	BOOL btnState = m_wndCmdBar.m_btnStartScan.GetCheck();   // ���������ť��Ϊ����״̬
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


void CMainFrame::OnCommset() 
{
	// TODO: Add your command handler code here
	
	// Ȩ�޼��
	if( users.m_nRoal < 1 )  { MessageBox(" ��ǰ�û���Ȩ��ʵʩ����!"); return;  }


	UINT nCmdID = ID_COMMSET; 
		if ( nCmdID == m_nCurrentExample)                       // �˵���ѡ��һ����ͬ����ͼѡ���
		    return;                                                 // already selected

	CView* pOldActiveView = GetActiveView();               // ��ܷ��ص�ǰ�����ͼ
		::SetWindowLong(pOldActiveView->m_hWnd, GWL_ID, m_nCurrentExample);  //set command ID as the child ID

	CRuntimeClass* pNewViewClass = RUNTIME_CLASS(CCommSet);	
	// create the new view
	CCreateContext context;											// ����һ�׿�ܡ���ͼ���ĵ���ָ��
	context.m_pNewViewClass = pNewViewClass;						// ����ͼ������Ϣ
	context.m_pCurrentDoc   = GetActiveDocument();					// �õ�����ĵ�

	CView* pNewView = STATIC_DOWNCAST(CView, CreateView(&context)); // ������ͼ�������ĵ�����Ƶ����Ϣ
	                                                                // ע�⣺FormView�ĶԻ�����Դ��������Ϊ
																	// �ޱ߿�+�Ӵ��壬���򴴽���ͼ��ʧ�� 
	if (pNewView != NULL)
	{
		pNewView->ShowWindow(SW_SHOW);                             // �µ���ͼ�Ѿ�������,����δ������ʾ
        //pNewView->ShowWindow(SW_SHOWMAXIMIZED);
		pNewView->OnInitialUpdate();
		SetActiveView(pNewView);									// �����ʾ�¹������ͼ���󣬲�������ͼ
		RecalcLayout();
		m_nCurrentExample = nCmdID;
		pOldActiveView->DestroyWindow();                            // finally destroy the old view...
	}
}


// ���û���¼�����õ�¼��Ϣ
void CMainFrame::OnMenuUser() 
{
	// TODO: Add your command handler code here
    CDlgUser   dlg;
	if(dlg.DoModal()==IDOK)	
	{
		// �����¼��ť����
       for (int i = 0; i < users.m_list.GetSize(); i++ )
       {
          if (users.m_list[i].username==dlg.m_sUsername)   
		  {
			  if  (users.m_list[i].password==dlg.m_sPassword)
			  {
				  // login OK
				  SetWindowText(m_sWinTitle + "_�û�:" + dlg.m_sUsername );
				  users.m_sUser = dlg.m_sUsername;
				  users.m_nRoal = dlg.m_nRoal;
			  }
			  else
			  {
				  MessageBox("�û��������!");
			  }
			  return;
		  }
       }


	   // ϵͳ����Ա�����б��еǼǣ��ǳ����û� only one,�û���������д��
       if ( (dlg.m_nRoal==2) && 
		    (dlg.m_sUsername=="administrator") && 
			(dlg.m_sPassword=="administrator") )
       {
		   users.m_sUser = dlg.m_sUsername;
		   users.m_nRoal = dlg.m_nRoal;
           SetWindowText(m_sWinTitle + "_�û�:" + dlg.m_sUsername );
		   return;
       }
	   
	   MessageBox("�û�Ȩ��δ����");
	}

	else
	{
		if ((users.m_nRoal==0) && users.m_sUser.IsEmpty() )
		{
			SetWindowText(m_sWinTitle);
		}
	}
	
}
void CMainFrame::OnMenuNewUser()
{
	CDlgNewUser   dlg;
	tagUser       user;

	if(dlg.DoModal()==IDOK)
	{

		if (dlg.m_sNewUser.IsEmpty())          { MessageBox("�û�������Ϊ��!"); return; }
		if (dlg.m_sPassword!=dlg.m_sPassword2) { MessageBox("�����������!");   return; }	
		
		user.username  = dlg.m_sNewUser;
		user.password  = dlg.m_sPassword;
		user.roalIndex = dlg.m_bIsAdmin; 

		users.m_list.Add(user);
        
		users.Save();      // �����û�Ȩ����Ϣ
        int ret = MessageBox("��ӭ���û�:\n"+ dlg.m_sNewUser+"\n �Ƿ��õ�ǰ�û���¼?","�Ƿ��¼",MB_ICONQUESTION|MB_OKCANCEL  );
		if(ret==IDOK)
		{
		   users.m_sUser = dlg.m_sNewUser;
		   users.m_nRoal = dlg.m_bIsAdmin;
		}
		
	}

	
}


void CMainFrame::OnButton2() 
{
	// TODO: Add your control notification handler code here
	MessageBox(" ���л���������ʾ״̬ͼ \n\n in CMainFrame::OnButton2()");
    OnExample(ID_GRAPH_VIEW);
}

void CMainFrame::OnButton1() 
{
	// TODO: Add your control notification handler code here
	MessageBox(" ����ģ���������ݲ���ʾ \n \n in CMainFrame::OnButton1()");
    
	((CCollectDoc *)GetActiveDocument())->SetCurveData();   // Doc ����ģ������

	GetActiveView()->SendMessage(WM_SIZE,NULL,NULL);        // 
    
	
	

}
