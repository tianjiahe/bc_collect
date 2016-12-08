// CommSet.cpp : implementation file
//

#include "stdafx.h"
#include "collect.h"
#include "CommSet.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommSet



IMPLEMENT_DYNCREATE(CCommSet, CFormView)

CCommSet::CCommSet()
	: CFormView(CCommSet::IDD)
{
	//{{AFX_DATA_INIT(CCommSet)
	m_nComPort     = -1;
	m_nCommRate    = -1;
	m_bCommFlow = FALSE;
	m_nDataBits = -1;                   //  ref to  combox serial num 
	m_sComStateTip = _T("����״̬");
	m_sFrameHead = _T("");
	m_sFrameTail = _T("");
	m_sFrameDisp   = _T("֡������ʾ");
	m_wCurWaveLen = 0;
	m_wAngle      = 0;
	m_wStartAngle = 0;
	m_wEndAngle   = 0;
	m_wUseWaveLen = 0;
	m_bFrameChk   = 0;
	m_bStepLen    = 0;
	m_bClockWise  = FALSE;
	m_sRxDisp = _T("");
	//}}AFX_DATA_INIT

// ͨѶЭ��������,
	// ���ԣ�ֻ�о���ӳ��ļ򵥱����������ڳ�ʼ�������и�ֵ�����ڸ���ʱ������ʾ�����ݡ�	
    // �ؼ��������������ʼ������ͼ��C++�������ڼ��в��ܲ������ڶ���
	CString  str;
	str.Format("0x%02XH",thePtl.getFrameHead() );
    m_sFrameHead = str;
    str.Format("0x%02XH",thePtl.getFrameTail() );
	m_sFrameTail = str;
   

}

CCommSet::~CCommSet()
{
}

void CCommSet::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommSet)
	DDX_Control(pDX, IDC_LIST_TX_DATA, m_listTxData);
	DDX_Control(pDX, IDC_LIST_RX_DATA, m_listRxData);
	DDX_Control(pDX, IDC_EDIT_CURWAVE_LEN,		m_otxtCurWaveLen);
	DDX_Control(pDX, IDC_BUTTON_DOWN_FRAME_CMD, m_obtnDownCmd);
	DDX_Control(pDX, IDC_CHECK_CLCOKWISE,		m_ochkClockWise);
	DDX_Control(pDX, IDC_EDIT_USEWAVE_LEN,		m_otxtUseWaveLen);
	DDX_Control(pDX, IDC_EDIT_STEP_LEN,			m_otxtStepLen);
	DDX_Control(pDX, IDC_EDIT_START_ANGLE,		m_otxtStartAngle);
	DDX_Control(pDX, IDC_EDIT_END_ANGLE,		m_otxtEndAngle);
	DDX_Control(pDX, IDC_EDIT_ANGLE,			m_otxtAngle);
	DDX_Control(pDX, IDC_COMBO_FRAME_CMD,		m_oFrameCmd);
	DDX_Control(pDX, IDC_COMBO_COM_NUM,			m_oCommPort);
	DDX_Control(pDX, IDC_COMBO_COM_STOPBIT,		m_oStopBit );
	DDX_Control(pDX, IDC_COMBO_PARITY,			m_oParity  );
	DDX_Control(pDX, IDC_COMBO_COM_DATABIT,		m_oDataBits);
	DDX_Control(pDX, IDC_COMBO_COM_RATE,		m_oBandRate);
	DDX_CBIndex(pDX, IDC_COMBO_COM_NUM,			m_nComPort );
	DDX_CBIndex(pDX, IDC_COMBO_COM_RATE,		m_nCommRate);
	DDX_Check(  pDX, IDC_CHECK_COM_FLOW,		m_bCommFlow);
	DDX_CBIndex(pDX, IDC_COMBO_COM_DATABIT,		m_nDataBits);
	DDX_Text(pDX, IDC_STATIC_COMM_STATE_TIP,    m_sComStateTip); 
	DDV_MaxChars(pDX, m_sComStateTip, 128);
	DDX_Text(pDX, IDC_STATIC_FRAME_HEAD,        m_sFrameHead);   
	DDV_MaxChars(pDX, m_sFrameHead,   16);
	DDX_Text(pDX, IDC_STATIC_FRAME_TAIL,		m_sFrameTail);   
	DDV_MaxChars(pDX, m_sFrameTail,   16);
	DDX_Text(pDX, IDC_STATIC_FRAME_DISP,		m_sFrameDisp);   
	DDV_MaxChars(pDX, m_sFrameDisp, 128);
	DDX_Text(pDX, IDC_EDIT_CURWAVE_LEN,			m_wCurWaveLen);
	DDX_Text(pDX, IDC_EDIT_ANGLE,				m_wAngle);
	DDX_Text(pDX, IDC_EDIT_START_ANGLE,			m_wStartAngle);
	DDX_Text(pDX, IDC_EDIT_END_ANGLE,			m_wEndAngle);
	DDX_Text(pDX, IDC_EDIT_USEWAVE_LEN,			m_wUseWaveLen);
	DDX_Text(pDX, IDC_EDIT_FRAME_CHK,			m_bFrameChk);
	DDX_Text(pDX, IDC_EDIT_STEP_LEN,			m_bStepLen);
	DDX_Check(pDX, IDC_CHECK_CLCOKWISE,			m_bClockWise);
	DDX_Text(pDX, IDC_EDIT_RX_DATA, m_sRxDisp);
	DDV_MaxChars(pDX, m_sRxDisp, 256);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommSet, CFormView)
	//{{AFX_MSG_MAP(CCommSet)
	ON_BN_CLICKED(IDC_BUTTON_COMM_APPLY,     OnButtonCommApply)
	ON_BN_CLICKED(IDC_BUTTON_DOWN_FRAME_CMD, OnButtonDownFrameCmd)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAME_CMD,    OnSelchangeComboFrameCmd)
	ON_WM_TIMER()
	ON_MESSAGE(WM_COMM_RXCHAR,               OnReceiveChar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommSet diagnostics

#ifdef _DEBUG
void CCommSet::AssertValid() const
{
	CFormView::AssertValid();
}

void CCommSet::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

#ifndef _DEBUG
CCollectDoc* CCommSet:GetDocument()
 { return (CCollectDoc*)m_pDocument; }
#endif
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommSet message handlers


void CCommSet::OnButtonCommApply() 
{
	// TODO: Add your control notification handler code here
		// ����ʹ�õ���Դ����ʼ������
	// �������ڲ���,���ڲ���
	char szbuf[32]; 
	ZeroMemory(szbuf,sizeof(32));

	UpdateData(TRUE);
	
    int selport  =  m_oCommPort.GetItemData( m_oCommPort.GetCurSel());
    int bandrate =  m_oBandRate.GetItemData( m_oBandRate.GetCurSel());
	int databits =  m_oDataBits.GetItemData( m_oDataBits.GetCurSel());
	int stopbits =  m_oStopBit.GetItemData(  m_oStopBit.GetCurSel() );
	int parity   =  m_oParity.GetItemData(   m_oParity.GetCurSel()  );

	theCom.InitPort( this, MaxSerialPortNum );  // ����δ����Ĵ��ںų�ʼ�����ڣ����رմ���

	if (theCom.InitPort( this, selport, bandrate, parity, databits,stopbits ))
	{
        

		theCom.setComPort( selport  );
        theCom.setBandRate(bandrate );
    	theCom.setDataBits(databits );
		theCom.setStopBit( stopbits );
		theCom.setParity(  parity   );

        theCom.SaveComToIni();                // �������
		
		theCom.StartMonitoring();             // ���������߳�
        
		m_sComStateTip = "���ڴ򿪳ɹ�\n�����ѱ���!";

	}
	else	               
	{
		m_sComStateTip = "���ڴ�ʧ��\n�����������������!"; 
	}
    UpdateData(FALSE);

}

void CCommSet::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	char szbuf[16];
	ZeroMemory(szbuf,sizeof(szbuf));
    CString str;

//  ���ش���ȫ������ѡ������ͼ�ؼ������ֲ�����ʽ��Ҫӳ��
    int i = 0;
	for ( i = COM0;       i<=COM9;        i++ )  
	{
		m_oCommPort.AddString( theCom.m_szPort[i] ); 
		m_oCommPort.SetItemData( i,  i );         // �˿�˳��� 
	}
	for ( i = CBR2400;    i<=CBR256000;   i++ )	
	{
		m_oBandRate.AddString(            theCom.m_szBandRate[i] );  
        m_oBandRate.SetItemData( i,  atoi(theCom.m_szBandRate[i]));         // data ����ʵ�ʴ�������
	}
    for ( i = DATABIT5;   i<=DATABIT8;    i++ )  
	{
		m_oDataBits.AddString(theCom.m_szDataBit[i]);  
        m_oDataBits.SetItemData( i, atoi(theCom.m_szDataBit[i]) );
	}	
	
	for ( i = STOPBIT1; i <= STOPBIT2; i++ )	
	{
		m_oStopBit.AddString(theCom.m_szStopBit[i]); 
        m_oStopBit.SetItemData( i, atoi(theCom.m_szStopBit[i] ) );
	}	
	for ( i = NOPARITY;   i<=SPACEPARITY; i++ )	
	{
		m_oParity.AddString(      theCom.m_szParity[i]    );	
		m_oParity.SetItemData( i, theCom.m_szParity[i][0] );   // parity���ݱ����ַ������ַ���N��O��E
	}

  	// ��ǰ���ݲ������µ�����ؼ���ѡ����
	m_oCommPort.SetCurSel( theCom.getComPort() );

	str.Format( "%d", theCom.getBandRate());
    m_oBandRate.SetCurSel( m_oBandRate.FindString( 0, str ));  
	
	str.Format( "%d",theCom.getDataBits() );
	m_oDataBits.SetCurSel( m_oDataBits.FindString( 0, str));

	str.Format( "%d",theCom.getStopBit());
	m_oStopBit.SetCurSel( m_oStopBit.FindString( 0, str ));	
	
	str.Format("%c", theCom.getParity() );
	m_oParity.SetCurSel(  m_oParity.FindString(0,str) );

	
	 //ͨѶЭ��������
   	for ( i = FRAME_CMD_00; i < FRAME_CMD_15+1; i++ )
   	{
   		if((thePtl.m_szFrameCmd[i][0]=='-') ||     // ���� ������
   		   (thePtl.m_szFrameCmd[i][1]=='R'))       // ���� ��������
   		     continue;
           m_oFrameCmd.AddString(thePtl.m_szFrameCmd[i]);
   		m_oFrameCmd.SetItemData( i, i );
   	}
      


	OnButtonCommApply();

	//CString t;	t.Format("%d",m_oCommPort.GetCurSel());	MessageBox(t); //�����ҵĲ��Խ��,û���� 
    UpdateData(TRUE);                   // ���ݱ仯�ȸ��µ�����, �ٸ��µ���ʾ��������ʾ����ˢ������


}


void CCommSet::OnSelchangeComboFrameCmd() 
{
	// TODO: Add your control notification handler code here
	
    UpdateData(true);

	m_otxtUseWaveLen.EnableWindow(FALSE);       // ÿ�ν���Ĭ��ȫ�����ã����ݺ���ı仯����ѡ��ʹ��ָ���ؼ�
	m_otxtStepLen.EnableWindow(FALSE);
	m_otxtStartAngle.EnableWindow(FALSE);
	m_otxtEndAngle.EnableWindow(FALSE);
	m_otxtCurWaveLen.EnableWindow(FALSE);
	m_otxtAngle.EnableWindow(FALSE);       		
	m_ochkClockWise.EnableWindow(FALSE);
	m_obtnDownCmd.EnableWindow(FALSE);

	int cmd = m_oFrameCmd.GetItemData(m_oFrameCmd.GetCurSel());
    
	switch( cmd ) 
	{
	 
    case FRAME_CMD_01:  //= "͸���ʲ���";
	case FRAME_CMD_03:  //= "����ɨ��";
		m_otxtCurWaveLen.EnableWindow(TRUE);
		break;
    case FRAME_CMD_02:  //= "�Ƕ�ɨ��";
		m_otxtStartAngle.EnableWindow(TRUE);
		m_otxtStepLen.EnableWindow(TRUE);
		m_otxtUseWaveLen.EnableWindow(TRUE);  
		m_otxtEndAngle.EnableWindow(TRUE);
		break;

	case FRAME_CMD_04: //= "��Ƭ̨��ת"; 
	case FRAME_CMD_05: //= "��������ת"; 
		m_otxtAngle.EnableWindow(TRUE);       		
	    m_ochkClockWise.EnableWindow(TRUE);
		break;


	case FRAME_CMD_06: //= "�ղ��׼";
		m_otxtUseWaveLen.EnableWindow(TRUE); 
		break; 
		
	case FRAME_CMD_07:				//= "ƽ̨��λ";
	case FRAME_CMD_08:				//= "����ֱ��";
	case FRAME_CMD_0E:				//= "�˳�ֱ��";
	case FRAME_CMD_10:				//= "����ɨ�����";
	case FRAME_CMD_15: break;		//= "��դ�������";
	
	
	case FRAME_CMD_00:	            //= "          ";
	case CB_ERR :
		m_sComStateTip = "��ѡ����ȷ��֡����!";
		break;
	default:          break;
	}

	if( cmd > FRAME_CMD_00 ) 
	{
		m_obtnDownCmd.EnableWindow(TRUE); 
		return;
	}
    
}

// �·���������֡
void CCommSet::OnButtonDownFrameCmd() 
{
   // �������
   // ��������֡
   // �������ڻ������
   UpdateData();
   
   int cmd = m_oFrameCmd.GetItemData(m_oFrameCmd.GetCurSel());

   thePtl.setCommand(cmd);        
   
   switch( cmd )
   {
	case FRAME_CMD_01:  //= "͸���ʲ���";
	case FRAME_CMD_03:  //= "����ɨ��";
		thePtl.setCurWaveLen(m_wCurWaveLen);
		break; 
    case FRAME_CMD_02:  //= "�Ƕ�ɨ��";
		thePtl.setStartAngle( m_wStartAngle  );
		thePtl.setStepLen(    m_bStepLen     );
		thePtl.setUseWaveLen( m_wUseWaveLen  );
		thePtl.setEndAngle(   m_wEndAngle    );
		break;
		
	case FRAME_CMD_04: //= "��Ƭ̨��ת"; 
	case FRAME_CMD_05: //= "��������ת"; 
		thePtl.setAngle(m_wAngle);
		thePtl.setClockWise(m_bClockWise?0:1);
		break;

	case FRAME_CMD_06: //= "�ղ��׼";
		thePtl.setUseWaveLen(m_wUseWaveLen);
		break; 
	case FRAME_CMD_07:				//= "ƽ̨��λ";
	case FRAME_CMD_08:				//= "����ֱ��";
	case FRAME_CMD_0E:				//= "�˳�ֱ��";
	case FRAME_CMD_10:				//= "����ɨ�����";
	case FRAME_CMD_15: break;		//= "��դ�������";
        
    default: m_sFrameDisp = "��Ч֡����!";  break;

   }

   if(thePtl.MarshFrame())
   {
	   thePtl.SendFrame();
	   
       thePtl.FormatTx(m_sFrameDisp); 

	   if (m_listTxData.GetCount()>100)	   {   m_listTxData.ResetContent( );	   }
	   m_listTxData.InsertString( 0, m_sFrameDisp);
	   m_listTxData.SetCurSel(0);
   }
     

   UpdateData(FALSE);
	
}


void CCommSet::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFormView::OnTimer(nIDEvent);
}


void CCommSet::OnReceiveChar(UINT ch, LONG port)
{
	UpdateData(true);

    //theCom.m_nBytesRead++;
	//CString temp;
	//temp.Format("%d",theCom.m_nBytesRead);
	//m_strReceiveBytes = temp;
	//if(m_bHexR)
	//	m_sFrameDisp += theCom.DevideHexChar(ch)+_T(" ");
	//else
	if (m_sRxDisp.GetLength()>250)   
	{
		m_sRxDisp.Empty();
	}
	m_sRxDisp += ch;
	
	UpdateData(false);


}
