// intlstvw.cpp : implementation file
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
#include "colledoc.h"
#include "intlstvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntListView

IMPLEMENT_DYNCREATE(CIntListView, CFormView)

CIntListView::CIntListView()
	: CFormView(CIntListView::IDD)
{
	//{{AFX_DATA_INIT(CIntListView)
	m_sTest = _T("10101010");
	m_sOutput = _T("");
	m_sOnLineState = _T("USB未连接,USB未初始化");
	m_sCurWavelen = _T("");
	m_dCollectGet = 0.0;
	//}}AFX_DATA_INIT
	m_nBackCount = 0;        // 倒计数，与定时器结合实现倒计时
}

CIntListView::~CIntListView()
{
}

void CIntListView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	m_oSpeedSet.SetCurSel(0);
	m_oWavelenSet.SetCurSel(1);
	m_oWavelenOffset.SetCurSel(0);

	m_listArgs.SetExtendedStyle( m_listArgs.GetExtendedStyle() 
		                         | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );
	
	m_listArgs.InsertColumn(0,"光栅序号", LVCFMT_CENTER,4*32);
    m_listArgs.InsertColumn(1,"刻线数",   LVCFMT_CENTER,3*32);
    m_listArgs.InsertColumn(2,"闪耀波长", LVCFMT_CENTER,4*32);

	//m_listArgs.InsertItem( m_listArgs.GetItemCount(), " 1号 ");
	//m_listArgs.InsertItem( m_listArgs.GetItemCount(), " 2号 ");
	//m_listArgs.InsertItem( m_listArgs.GetItemCount(), " 3号 ");


    InitForm();
	

}


void CIntListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntListView)
	DDX_Control(pDX, IDC_LIST2, m_listArgs);
	DDX_Control(pDX, IDC_EDIT_TEST, m_oTest);
	DDX_Control(pDX, IDC_CMB_WAVELEN_OFFSET, m_oWavelenOffset);
	DDX_Control(pDX, IDC_CMB_WAVELEN, m_oWavelenSet);
	DDX_Control(pDX, IDC_CMB_SPEED, m_oSpeedSet);
	DDX_Text(pDX, IDC_EDIT_TEST, m_sTest);
	DDV_MaxChars(pDX, m_sTest, 8);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_sOutput);
	DDV_MaxChars(pDX, m_sOutput, 16);
	DDX_Text(pDX, IDC_EDIT_ONLINE, m_sOnLineState);
	DDV_MaxChars(pDX, m_sOnLineState, 32);
	DDX_Text(pDX, IDC_EDIT_CURWAVELEN, m_sCurWavelen);
	DDV_MaxChars(pDX, m_sCurWavelen, 16);
	DDX_Text(pDX, IDC_EDIT_COLLECT, m_dCollectGet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIntListView, CFormView)
	//{{AFX_MSG_MAP(CIntListView)
	ON_BN_CLICKED(IDC_BTN_TEST_, OnBtnTest)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_COLLECT, OnBtnCollect)
	ON_BN_CLICKED(IDC_BTN_SPEED_SET, OnBtnSpeedSet)
	ON_BN_CLICKED(IDC_BTN_WAVELEN_GOTO, OnBtnWavelenGoto)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_WAVELEN_OFFSET, OnDeltaposSpinWavelenOffset)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CIntListView diagnostics

#ifdef _DEBUG
void CIntListView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIntListView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCollectDoc* CIntListView::GetDocument() // non-debug version is inline
{
	return STATIC_DOWNCAST(CCollectDoc, m_pDocument);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIntListView internal implementation


void CIntListView::OnBtnTest() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);



	CString str;
    int  Num=0,ch=0;	  
	char buf[10];

	sprintf(buf,"%s", m_sTest );
	for( int i = 0 ; i< 8; i++) 
	{
		buf[i];
		if (buf[i]=='1') ch=1 ;
		if (buf[i]=='0') ch=0 ;
		Num += (int)(ch*pow(2,8-(i+1)));	
	}

	CSendCmdData( CMD_TEST,  Num );

	WaitforDone(10);

	
    
}

void CIntListView::OnTimer(UINT nIDEvent) 
{

	UCHAR command;
	LONG  data;
	// TODO: Add your message handler code here and/or call default
    if (nIDEvent==1)
    {
		// "USB未连接,USB未初始化";
      	if(!CUsbLinked())
		{
			m_sOnLineState = "USB未连接,USB未初始化";//		return;
		}
		else
		{
			if(!CIfUsbinited())
			{
				m_sOnLineState = "USB已连接,USB未初始化";
				COpenDev();
				if(CDevInit())
				{
                    m_sOnLineState = "USB已连接,USB已初始化";
                    // 下位机连接成功，取下位机的数据，显示在控件上
					InitForm();
             		UpdateData(FALSE);
					SetTimer(2,20,NULL);			//定时器2一定要在GDevInit()之后打开    
				}
			}
			//return;
		}
    }

	
	if(nIDEvent == 2)
	{
       if(!UsbInited)  return;
		
		// Read Data, TimeOut = 0	// Process the Coming Data
		if(CReadCmdData( command, data)) 
		{   // Process the Packet
			switch(command) 
			{
			case VAL_GRID:
			
				m_sCurWavelen.Format("%0.2f",NowWave);
				UpdateData(FALSE);
				break;
			case CMD_TEST:
				int   j;
				ULONG k;
				char  Number[10], string[33];
				k = data;						  						   						
				ltoa( k, string, 2 );
				for ( j = 0; j < 8; j++ )	{	Number[j]=string[24+j];		}
				Number[8] = '\0';
				m_sOutput = Number;					
				UpdateData(FALSE);
				break;
			case VAL_ADC:
				//long value;
				//value = data;
				m_dCollectGet = data;//value;
				UpdateData(FALSE);
			case CMD_OK:
				//BtnEnable(TRUE);
				break;						
			case CMD_ERROR:
				break;
			}
		}
		
	}

	CFormView::OnTimer(nIDEvent);
}

BOOL CIntListView::WaitforDone(int backCount )
{
    theApp.DoWaitCursor(1);             // 撒漏光标
    while(Busy  && backCount)
    {
		//theApp.PumpMessage();

		Sleep(100);
		backCount--;
	}
	
	theApp.DoWaitCursor(0);
	
	if(backCount<=0) return FALSE;        // 下位机超时
    return TRUE;
}

void CIntListView::OnBtnCollect() 
{
	// TODO: Add your control notification handler code here
    CSendCmd(ADC_DATA);
	WaitforDone(5);
}



void CIntListView::OnBtnSpeedSet() 
{
	// TODO: Add your control notification handler code here
	    ULONG Speed;
    if(m_oSpeedSet.GetCurSel()==0) Speed = 0;
    if(m_oSpeedSet.GetCurSel()==1) Speed = 3;
    if(m_oSpeedSet.GetCurSel()==2) Speed = 6;
	
    CSetSpeed(Speed);
	WaitforDone(5);
}



void CIntListView::OnBtnWavelenGoto() 
{
	// TODO: Add your control notification handler code here
	CString  str;
	double wave;
	m_oWavelenSet.GetWindowText( str );
	wave = strtod( str, NULL);
	
	CGotoWave( 0, wave);
	
	WaitforDone(5);
}

void CIntListView::OnDeltaposSpinWavelenOffset(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString str;
//    HWND	hwndFrom;
//    UINT	idFrom;
//    UINT	code;         
//	str.Format("hwnd=%d,idFrom=%d,code=%d, iDelta=%d,iPos=%d\n",
//		        pNMUpDown->hdr.hwndFrom,pNMUpDown->hdr.idFrom,pNMUpDown->hdr.code,
//				pNMUpDown->iDelta,pNMUpDown->iPos);
//	OutputDebugString(str);

    double wave;
	m_oWavelenOffset.GetWindowText(str);
	wave = NowWave + (pNMUpDown->iDelta) * strtod( str, NULL);   // spin up click  iDelta is -1, down is -1
	CGotoWave(GridIndex,wave);

	WaitforDone(5);
	*pResult = 0;
}

void CIntListView::OnBtnReset() 
{
	CGotoZero(0);
	WaitforDone(5);
}

void CIntListView::OnBtnStop() 
{
	CStop();
}

//
void CIntListView::InitForm()
{
//	if     ( G1 == 0) 		    m_arg5 = "无";
//    else if( G1 % 10 == 0)  	m_arg5.Format("%d",(G1/ 10));	
//	else            			m_arg5.Format("%0.1f",G1 / 10.0);
//    
//
//    if(G1Wave== 0) 				m_arg9 = "无";
//    else						m_arg9.Format("%d",G1Wave);    
//
//    if     ( G2 == 0) 		    m_arg6 = "无";
//    else if( G2 % 10 == 0)   	m_arg6.Format("%d",  ( G2 / 10  ));
//	else			            m_arg6.Format("%0.1f", G2 / 10.0);
//    
//
//    if(G2Wave == 0) 		    m_arg10 = "无";
//    else 		                m_arg10.Format("%d",G2Wave );
//
//    if     ( G3 == 0) 		    m_arg7 = "无";
//    else if( G3 % 10 == 0)		m_arg7.Format("%d",  (G3 / 10  ));
//	else			            m_arg7.Format("%0.1f",G3 / 10.0);
//
//    if(G3Wave == 0) 		    m_arg11 = "无";
//    else              		    m_arg11.Format("%d", G3Wave );

//	extern CSP_API LONG   G1;							//1号光栅的刻线数，如该变量为0，说明相应光栅不存在
//	extern CSP_API LONG   G2;							//2号光栅的刻线数，如该变量为0，说明相应光栅不存在
//	extern CSP_API LONG   G3;							//3号光栅的刻线数，如该变量为0，说明相应光栅不存在
//	extern CSP_API LONG   G1Wave;						//1号光栅的闪耀波长，如该变量为0，说明该光栅不存在
//	extern CSP_API LONG   G2Wave;						//2号光栅的闪耀波长，如该变量为0，说明该光栅不存在
//	extern CSP_API LONG   G3Wave;						//3号光栅的闪耀波长，如该变量为0，说明该光栅不存在

	LONG  buf[3][2] = {{G1,G1Wave},{G2,G2Wave},{G3,G3Wave}}; //LONG  buf[3][2] = {{1,2},{3,4},{5,6}}; 
	LONG  temp;
	CString  str0,str1,str2;
	m_listArgs.DeleteAllItems();
	for (int i=0; i <3 ; i++)
	{
        
		str0.Format( "%d号",    i+1   );

        temp = buf[i][0];		
		if ( temp == 0)  	 {   str1= "无";   		}// 刻线数
		else if (temp%10==0) {   str1.Format("%d",(temp/10));     }
		else                 {   str1.Format("%0.1f",(temp/10.0));} 
        temp =  buf[i][1];
		if ( temp == 0)  	 {   str2= "无";   		     }// 闪耀波长
		else                 {   str2.Format("%d",temp); } 
        
		m_listArgs.InsertItem( i,    str0 );
		
		m_listArgs.SetItemText(i, 1,  str1 );
		m_listArgs.SetItemText(i, 2,  str2 );
	}
	
	
}
