//////////////////////////////////////////////////////////////////////////
// ����ͨѶЭ����
// ���ܣ� ������ͨѶ����֡���շ�����֡ 
//////////////////////////////////////////////////////////////////////////
CComProtocol::CComProtocol()
{
    m_szFrameCmd[FRAME_CMD_00] = "          ";
    m_szFrameCmd[FRAME_CMD_01] = "͸���ʲ���";
    m_szFrameCmd[FRAME_CMD_02] = "�Ƕ�ɨ��";
	m_szFrameCmd[FRAME_CMD_03] = "����ɨ��";
	m_szFrameCmd[FRAME_CMD_04] = "��Ƭ̨��ת";
	m_szFrameCmd[FRAME_CMD_05] = "��������ת";
	m_szFrameCmd[FRAME_CMD_06] = "�ղ��׼";
	m_szFrameCmd[FRAME_CMD_07] = "ƽ̨��λ";
	m_szFrameCmd[FRAME_CMD_08] = "����ֱ��";
	m_szFrameCmd[FRAME_CMD_09] = "[R]��������";       // ����֡
    m_szFrameCmd[FRAME_CMD_0A] = "[R]�Ƕ�ɨ�����";   // ����֡
	m_szFrameCmd[FRAME_CMD_0B] = "[R]���ؽ��";       // ���ؽ��
	m_szFrameCmd[FRAME_CMD_0C] = "--------";
	m_szFrameCmd[FRAME_CMD_0D] = "--------";
	m_szFrameCmd[FRAME_CMD_0E] = "�˳�ֱ��";
	m_szFrameCmd[FRAME_CMD_0F] = "--------";
	m_szFrameCmd[FRAME_CMD_10] = "����ɨ�����";
	m_szFrameCmd[FRAME_CMD_11] = "--------";
	m_szFrameCmd[FRAME_CMD_12] = "--------";
	m_szFrameCmd[FRAME_CMD_13] = "--------";
	m_szFrameCmd[FRAME_CMD_14] = "--------";
	m_szFrameCmd[FRAME_CMD_15] = "��դ�������";

    ZeroMemory(m_bFrame, FRAME_MAX_LEN);
	m_bFrame[HEAD]    = FRAME_HEAD;
	m_bFrame[TAIL]    = FRAME_TAIL;
	m_bFrame[COMMAND] = FRAME_CMD_00;              // 
	
	//Init(theCom);
   
}

CComProtocol::~CComProtocol()  { }


// �·�ǰ��׼������֡�ı���
BOOL CComProtocol::MarshFrame()
{
    BOOL  ret =TRUE;

	ZeroMemory(m_bFrame,sizeof(m_bFrame));
	m_bFrameLen =  FRAME_MAX_LEN;                // Ĭ�� ����֡
	
	m_bFrame[HEAD]    =  FRAME_HEAD;
	m_bFrame[COMMAND] =  m_bCmd;                // ����
   
    switch( m_bCmd )
	{
	case FRAME_CMD_01:  //= "͸���ʲ���";
	case FRAME_CMD_03:  //= "����ɨ��";

		m_bFrame[REF1_0]  = HIBYTE(m_wCurWaveLen);
        m_bFrame[REF1_1]  = LOBYTE(m_wCurWaveLen);
		break; 

    case FRAME_CMD_02:  //= "�Ƕ�ɨ��";

        m_bFrame[REF1_0]  = HIBYTE(m_wStartAngle); 
        m_bFrame[REF1_1]  = LOBYTE(m_wStartAngle); 
		m_bFrame[REF2]    = m_bStepLen; 
        m_bFrame[REF3_0]  = HIBYTE(m_wUseWaveLen); 
		m_bFrame[REF3_1]  = LOBYTE(m_wUseWaveLen); 
        m_bFrame[REF4_0]  = HIBYTE(m_wEndAngle); 
		m_bFrame[REF4_1]  = LOBYTE(m_wEndAngle); 
		break;
		
	case FRAME_CMD_04: //= "��Ƭ̨��ת"; 
	case FRAME_CMD_05: //= "��������ת"; 
	
		m_bFrame[REF1_0]  = HIBYTE(m_wAngle);
		m_bFrame[REF1_1]  = LOBYTE(m_wAngle);
		m_bFrame[REF2]    = m_bClockWise;
		break;

	case FRAME_CMD_06: //= "�ղ��׼";

		m_bFrame[REF1_0]  = HIBYTE(m_wUseWaveLen);
		m_bFrame[REF1_1]  = LOBYTE(m_wUseWaveLen);
		break; 

    case FRAME_CMD_07:
    case FRAME_CMD_08:
	case FRAME_CMD_09:
    case FRAME_CMD_0E:
	case FRAME_CMD_10:
	case FRAME_CMD_15: 
		               m_bFrameLen = FRAME_MIN_LEN;    // ��Щ֡�ĳ���4�ֽڣ�
					   break;

	default:   ret = FALSE;   break;
    }

	// ��2�ֳ��Ȳ�ͬ���·�����֡
    
	if (m_bFrameLen==FRAME_MAX_LEN)
	{
		m_bFrame[CHK_SUM] = checkSum();
		m_bFrame[TAIL]    = FRAME_TAIL;
	}
	else if(m_bFrameLen==FRAME_MIN_LEN)
	{
        m_bFrame[CHK_SUM_SHROT] = checkSum();
		m_bFrame[TAIL_SHORT]    = FRAME_TAIL;
	}
    
	
	return ret;

}
void CComProtocol::SendFrame()
{
	ZeroMemory(pCom->m_txbuf,TX_BUF_LEN);
    memcpy( pCom->m_txbuf, m_bFrame, m_bFrameLen);
	pCom->WriteCom(m_bFrameLen);
}

// ����У���
BYTE CComProtocol::checkSum()
{
    WORD  total = 0;
	for(int i = HEAD; i <= m_bFrameLen-2; i++ )
    {
		total  += m_bFrame[i];
	}
	return LOBYTE(total);
}

void CComProtocol::FormatTx(CString &str)
{
   str.Format("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
	          m_bFrame[0],m_bFrame[1],m_bFrame[2],m_bFrame[3],m_bFrame[4],
			  m_bFrame[5],m_bFrame[6],m_bFrame[7],m_bFrame[8],m_bFrame[9],m_bFrame[10] );
			  
}

void CComProtocol::FormatRx(CString &str)
{
   BYTE *pbuf = theCom.m_rxbuf;
   str.Format("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
	   pbuf[0],pbuf[1],pbuf[2],pbuf[3],pbuf[4],pbuf[5],
	   pbuf[6],pbuf[7],pbuf[8],pbuf[9],pbuf[10]	   );
}
