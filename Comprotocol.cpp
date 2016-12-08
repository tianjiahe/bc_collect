//////////////////////////////////////////////////////////////////////////
// 串口通讯协议类
// 功能： 处理串口通讯数据帧，收发数据帧 
//////////////////////////////////////////////////////////////////////////
CComProtocol::CComProtocol()
{
    m_szFrameCmd[FRAME_CMD_00] = "          ";
    m_szFrameCmd[FRAME_CMD_01] = "透过率测量";
    m_szFrameCmd[FRAME_CMD_02] = "角度扫测";
	m_szFrameCmd[FRAME_CMD_03] = "波段扫测";
	m_szFrameCmd[FRAME_CMD_04] = "镜片台旋转";
	m_szFrameCmd[FRAME_CMD_05] = "传感器旋转";
	m_szFrameCmd[FRAME_CMD_06] = "空测基准";
	m_szFrameCmd[FRAME_CMD_07] = "平台复位";
	m_szFrameCmd[FRAME_CMD_08] = "数据直读";
	m_szFrameCmd[FRAME_CMD_09] = "[R]调整波长";       // 返回帧
    m_szFrameCmd[FRAME_CMD_0A] = "[R]角度扫测完成";   // 返回帧
	m_szFrameCmd[FRAME_CMD_0B] = "[R]返回结果";       // 返回结果
	m_szFrameCmd[FRAME_CMD_0C] = "--------";
	m_szFrameCmd[FRAME_CMD_0D] = "--------";
	m_szFrameCmd[FRAME_CMD_0E] = "退出直读";
	m_szFrameCmd[FRAME_CMD_0F] = "--------";
	m_szFrameCmd[FRAME_CMD_10] = "波段扫描完成";
	m_szFrameCmd[FRAME_CMD_11] = "--------";
	m_szFrameCmd[FRAME_CMD_12] = "--------";
	m_szFrameCmd[FRAME_CMD_13] = "--------";
	m_szFrameCmd[FRAME_CMD_14] = "--------";
	m_szFrameCmd[FRAME_CMD_15] = "光栅调整完成";

    ZeroMemory(m_bFrame, FRAME_MAX_LEN);
	m_bFrame[HEAD]    = FRAME_HEAD;
	m_bFrame[TAIL]    = FRAME_TAIL;
	m_bFrame[COMMAND] = FRAME_CMD_00;              // 
	
	//Init(theCom);
   
}

CComProtocol::~CComProtocol()  { }


// 下发前，准备命令帧的编组
BOOL CComProtocol::MarshFrame()
{
    BOOL  ret =TRUE;

	ZeroMemory(m_bFrame,sizeof(m_bFrame));
	m_bFrameLen =  FRAME_MAX_LEN;                // 默认 发长帧
	
	m_bFrame[HEAD]    =  FRAME_HEAD;
	m_bFrame[COMMAND] =  m_bCmd;                // 命令
   
    switch( m_bCmd )
	{
	case FRAME_CMD_01:  //= "透过率测量";
	case FRAME_CMD_03:  //= "波段扫测";

		m_bFrame[REF1_0]  = HIBYTE(m_wCurWaveLen);
        m_bFrame[REF1_1]  = LOBYTE(m_wCurWaveLen);
		break; 

    case FRAME_CMD_02:  //= "角度扫测";

        m_bFrame[REF1_0]  = HIBYTE(m_wStartAngle); 
        m_bFrame[REF1_1]  = LOBYTE(m_wStartAngle); 
		m_bFrame[REF2]    = m_bStepLen; 
        m_bFrame[REF3_0]  = HIBYTE(m_wUseWaveLen); 
		m_bFrame[REF3_1]  = LOBYTE(m_wUseWaveLen); 
        m_bFrame[REF4_0]  = HIBYTE(m_wEndAngle); 
		m_bFrame[REF4_1]  = LOBYTE(m_wEndAngle); 
		break;
		
	case FRAME_CMD_04: //= "镜片台旋转"; 
	case FRAME_CMD_05: //= "传感器旋转"; 
	
		m_bFrame[REF1_0]  = HIBYTE(m_wAngle);
		m_bFrame[REF1_1]  = LOBYTE(m_wAngle);
		m_bFrame[REF2]    = m_bClockWise;
		break;

	case FRAME_CMD_06: //= "空测基准";

		m_bFrame[REF1_0]  = HIBYTE(m_wUseWaveLen);
		m_bFrame[REF1_1]  = LOBYTE(m_wUseWaveLen);
		break; 

    case FRAME_CMD_07:
    case FRAME_CMD_08:
	case FRAME_CMD_09:
    case FRAME_CMD_0E:
	case FRAME_CMD_10:
	case FRAME_CMD_15: 
		               m_bFrameLen = FRAME_MIN_LEN;    // 这些帧的长度4字节，
					   break;

	default:   ret = FALSE;   break;
    }

	// 有2种长度不同的下发命令帧
    
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

// 计算校验和
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
