
#if !defined(AFX_COMPROTOCOL__INCLUDED_)
#define AFX_COMPROTOCOL__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////////////////////////////////////////
// 串口数据帧CComPrototol类声明， 使用的数据、宏定义
//////////////////////////////////////////////////////////////////////////

// 透反仪通信协议

#define   FRAME_HEAD          0x14            // 帧头
#define   FRAME_TAIL          0x07            // 帧尾

        //PC端发给下位机
#define   FRAME_CMD_00        0x00             // 0基数组占位，暂无意义
#define   FRAME_CMD_01        (0x01)  
#define   FRAME_CMD_02        (0x02)  
#define   FRAME_CMD_03        (0x03)  
#define   FRAME_CMD_04        (0x04)  
#define   FRAME_CMD_05        (0x05)  
#define   FRAME_CMD_06        (0x06)  
#define   FRAME_CMD_07        (0x07)
#define   FRAME_CMD_08        (0x08)  
#define   FRAME_CMD_09        (0x09)             // 下位机发回上位机 
#define   FRAME_CMD_0A        (0x0a)             // 下位机发回上位机 
#define   FRAME_CMD_0B        (0x0b)             // 下位机发回上位机 
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

// 帧的字节顺序

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

#define   FRAME_MIN_LEN        (4)            // 短命令帧的长度4字节
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
    BOOL MarshFrame(void);                      // 帧编组

    
	//CComOp  *pCom;                    // 串口缓冲区对象

   
	inline void  Init(void)     { ; }

	inline BYTE  getFrameHead(void)      { return m_bFrame[HEAD]; }
	inline void  setFrameHead(BYTE head) { m_bFrame[HEAD] = head; }
	inline BYTE  getFrameTail(void)      { return m_bFrame[TAIL]; }
	inline void  setFrameTail(BYTE tail) { m_bFrame[TAIL] = tail; }
    inline BYTE  getCommand(void)        { return m_bCmd; }
	inline void  setCommand(BYTE cmd)    { m_bCmd = cmd;  }
          
    inline WORD  getCurWaveLen(void)     { return  m_wCurWaveLen;}					  // 当前波长
    inline WORD  getUseWaveLen(void )    { return  m_wUseWaveLen;}					  // 应用波长
    inline WORD  getAngle(void )         { return  m_wAngle;     }                      // 角度
	inline WORD  getStartAngle(void)     { return  m_wStartAngle;}                      // 起始角度
    inline WORD  getEndAngle(void )      { return  m_wEndAngle;  }                      // 终点角度
    inline BYTE  getStepLen(void )       { return  m_bStepLen;   }                      // 步长 
	inline BYTE  getClockWise(void )	 { return  m_bClockWise; }                      // 顺时针、逆时针antiClockWise 
    inline void  setCurWaveLen(WORD cwl) { m_wCurWaveLen = cwl;  }                    // 当前波长
    inline void  setUseWaveLen(WORD uwl) { m_wUseWaveLen = uwl;  }                     // 应用波长
    inline void  setAngle(WORD angle )   { m_wAngle      = angle;}                     // 角度
	inline void  setStartAngle(WORD sa)  { m_wStartAngle = sa;   }
    inline void  setEndAngle(WORD ea )   { m_wEndAngle   = ea;   }                     // 终点角度
    inline void  setStepLen(BYTE step)   { m_bStepLen    = step; }                     // 步长 
	inline void  setClockWise(BYTE cw)   { m_bClockWise  = cw;   }                     // 顺时针、逆时针antiClockWise 
    inline BYTE  getFrameLen( void)      { return m_bFrameLen;   }                     // 步长 
	inline void  setFrameLen(BYTE len)   { m_bFrameLen  = len;   }                     // 顺时针、逆时针antiClockWise 

private:

	BYTE        checkSum(void);              // 校验和，帧头在内
	BYTE        m_bFrame[FRAME_MAX_LEN];     // 帧头              
	BYTE        m_bCmd;                      // 帧命令
	WORD        m_wCurWaveLen;               // 当前波长
    WORD        m_wUseWaveLen;               // 应用波长
    WORD        m_wAngle;                    // 角度
	WORD        m_wStartAngle;
    WORD        m_wEndAngle;                 // 终点角度
    BYTE        m_bStepLen;                  // 步长 
	BYTE        m_bClockWise;                // 顺时针、逆时针antiClockWise 
    BYTE        m_bFrameLen;                 // 当前发生的数据帧长度 
 
};

#endif // !defined(AFX_COMPROTOCOL__INCLUDED_)