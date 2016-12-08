
#if !defined(AFX_COMPROTOCOL__INCLUDED_)
#define AFX_COMPROTOCOL__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////////////////////////////////////////
// ��������֡CComPrototol�������� ʹ�õ����ݡ��궨��
//////////////////////////////////////////////////////////////////////////

// ͸����ͨ��Э��

#define   FRAME_HEAD          0x14            // ֡ͷ
#define   FRAME_TAIL          0x07            // ֡β

        //PC�˷�����λ��
#define   FRAME_CMD_00        0x00             // 0������ռλ����������
#define   FRAME_CMD_01        (0x01)  
#define   FRAME_CMD_02        (0x02)  
#define   FRAME_CMD_03        (0x03)  
#define   FRAME_CMD_04        (0x04)  
#define   FRAME_CMD_05        (0x05)  
#define   FRAME_CMD_06        (0x06)  
#define   FRAME_CMD_07        (0x07)
#define   FRAME_CMD_08        (0x08)  
#define   FRAME_CMD_09        (0x09)             // ��λ��������λ�� 
#define   FRAME_CMD_0A        (0x0a)             // ��λ��������λ�� 
#define   FRAME_CMD_0B        (0x0b)             // ��λ��������λ�� 
#define   FRAME_CMD_0C        (0x0c)  
#define   FRAME_CMD_0D        (0x0d)  
#define   FRAME_CMD_0E        (0x0e)  
#define   FRAME_CMD_0F        (0x0f)
#define   FRAME_CMD_10        (0x10)
#define   FRAME_CMD_11        (0x11)
#define   FRAME_CMD_12        (0x12)
#define   FRAME_CMD_13        (0x13)
#define   FRAME_CMD_14        (0x14)
#define   FRAME_CMD_15        (0x15)

// ֡���ֽ�˳��

#define   FRAME_MAX_LEN       (TAIL+1)
#define   HEAD                 (0)
#define   COMMAND              (1)
#define   REF1_0               (2)
#define   REF1_1               (3)
#define   REF2                 (4)
#define   REF3_0               (5)
#define   REF3_1               (6)
#define   REF4_0               (7)
#define   REF4_1               (8)
#define   CHK_SUM              (9)
#define   TAIL                 (10)

#define   FRAME_MIN_LEN        (4)            // ������֡�ĳ���4�ֽ�
#define   CHK_SUM_SHROT        (2)
#define   TAIL_SHORT           (3)

class CComProtocol : public CObject  
{
public:

	CComProtocol();
	virtual ~CComProtocol();

	
public:
	
    char * m_szFrameCmd[FRAME_CMD_15+1]; 

	void FormatRx(CString &str);
	void FormatTx(CString &str);
	void SendFrame(void);
    BOOL MarshFrame(void);                      // ֡����

    
	//CComOp  *pCom;                    // ���ڻ���������

   
	inline void  Init(void)     { ; }

	inline BYTE  getFrameHead(void)      { return m_bFrame[HEAD]; }
	inline void  setFrameHead(BYTE head) { m_bFrame[HEAD] = head; }
	inline BYTE  getFrameTail(void)      { return m_bFrame[TAIL]; }
	inline void  setFrameTail(BYTE tail) { m_bFrame[TAIL] = tail; }
    inline BYTE  getCommand(void)        { return m_bCmd; }
	inline void  setCommand(BYTE cmd)    { m_bCmd = cmd;  }
          
    inline WORD  getCurWaveLen(void)     { return  m_wCurWaveLen;}					  // ��ǰ����
    inline WORD  getUseWaveLen(void )    { return  m_wUseWaveLen;}					  // Ӧ�ò���
    inline WORD  getAngle(void )         { return  m_wAngle;     }                      // �Ƕ�
	inline WORD  getStartAngle(void)     { return  m_wStartAngle;}                      // ��ʼ�Ƕ�
    inline WORD  getEndAngle(void )      { return  m_wEndAngle;  }                      // �յ�Ƕ�
    inline BYTE  getStepLen(void )       { return  m_bStepLen;   }                      // ���� 
	inline BYTE  getClockWise(void )	 { return  m_bClockWise; }                      // ˳ʱ�롢��ʱ��antiClockWise 
    inline void  setCurWaveLen(WORD cwl) { m_wCurWaveLen = cwl;  }                    // ��ǰ����
    inline void  setUseWaveLen(WORD uwl) { m_wUseWaveLen = uwl;  }                     // Ӧ�ò���
    inline void  setAngle(WORD angle )   { m_wAngle      = angle;}                     // �Ƕ�
	inline void  setStartAngle(WORD sa)  { m_wStartAngle = sa;   }
    inline void  setEndAngle(WORD ea )   { m_wEndAngle   = ea;   }                     // �յ�Ƕ�
    inline void  setStepLen(BYTE step)   { m_bStepLen    = step; }                     // ���� 
	inline void  setClockWise(BYTE cw)   { m_bClockWise  = cw;   }                     // ˳ʱ�롢��ʱ��antiClockWise 
    inline BYTE  getFrameLen( void)      { return m_bFrameLen;   }                     // ���� 
	inline void  setFrameLen(BYTE len)   { m_bFrameLen  = len;   }                     // ˳ʱ�롢��ʱ��antiClockWise 

private:

	BYTE        checkSum(void);              // У��ͣ�֡ͷ����
	BYTE        m_bFrame[FRAME_MAX_LEN];     // ֡ͷ              
	BYTE        m_bCmd;                      // ֡����
	WORD        m_wCurWaveLen;               // ��ǰ����
    WORD        m_wUseWaveLen;               // Ӧ�ò���
    WORD        m_wAngle;                    // �Ƕ�
	WORD        m_wStartAngle;
    WORD        m_wEndAngle;                 // �յ�Ƕ�
    BYTE        m_bStepLen;                  // ���� 
	BYTE        m_bClockWise;                // ˳ʱ�롢��ʱ��antiClockWise 
    BYTE        m_bFrameLen;                 // ��ǰ����������֡���� 
 
};

#endif // !defined(AFX_COMPROTOCOL__INCLUDED_)