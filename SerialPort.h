/*
**	FILENAME			CSerialPort.h
**
**	PURPOSE				This class can read, write and watch one serial port.
**						It sends messages to its owner when something happends on the port
**						The class creates a thread for reading and writing so the main
**						program is not blocked.
**
**	CREATION DATE		15-09-1997
**	LAST MODIFICATION	12-11-1997
**
**	AUTHOR				Remon Spekreijse
**
**
*/
/********************************************************************
	created:	2016/12/21
	created:	21:12:2016   10:35
	filename: 	D:\kinggsoft\SerialPort.h
	file path:	D:\kinggsoft
	file base:	SerialPort
	file ext:	h
	author:		
	
	purpose:	使用开源串口源码，使用多线程方式接收数据，
*********************************************************************/

#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#define WM_COMM_BREAK_DETECTED		WM_USER+1	// A break was detected on input.
#define WM_COMM_CTS_DETECTED		WM_USER+2	// The CTS (clear-to-send) signal changed state. 
#define WM_COMM_DSR_DETECTED		WM_USER+3	// The DSR (data-set-ready) signal changed state. 
#define WM_COMM_ERR_DETECTED		WM_USER+4	// A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. 
#define WM_COMM_RING_DETECTED		WM_USER+5	// A ring indicator was detected. 
#define WM_COMM_RLSD_DETECTED		WM_USER+6	// The RLSD (receive-line-signal-detect) signal changed state. 
#define WM_COMM_RXCHAR				WM_USER+7	// A character was received and placed in the input buffer. 
#define WM_COMM_RXFLAG_DETECTED		WM_USER+8	// The event character was received and placed in the input buffer.  
#define WM_COMM_TXEMPTY_DETECTED	WM_USER+9	// The last character in the output buffer was sent.  
#define MaxSerialPortNum			11

class CSerialPort
{														 
public:
	int GetPortNO();
	// contruction and destruction
	CSerialPort();
	virtual		~CSerialPort();

	// port initialisation											
	BOOL		InitPort(CWnd* pPortOwner, UINT portnr = 1, UINT baud = 9600, char parity = 'N', UINT databits = 8, UINT stopsbits = 1, DWORD dwCommEvents = EV_RXCHAR|EV_CTS, UINT nBufferSize = 512);

	// start/stop comm watching
	BOOL		StartMonitoring();
	BOOL		RestartMonitoring();
	BOOL		StopMonitoring();

	DWORD		GetWriteBufferSize();
	DWORD		GetCommEvents();
	DCB			GetDCB();

	void		WriteToPort(char* string);
	void		WriteToPort(char* string,int length);
protected:
	// protected memberfunctions
	void		ProcessErrorMessage(char* ErrorText);
	static UINT	CommThread(LPVOID pParam);
	static void	ReceiveChar(CSerialPort* port, COMSTAT comstat);
	static void	WriteChar(CSerialPort* port,int length);

	// thread
	CWinThread*			m_Thread;

	// synchronisation objects
	CRITICAL_SECTION	m_csCommunicationSync;
	BOOL				m_bThreadAlive;

	// handles
	HANDLE				m_hShutdownEvent;
	HANDLE				m_hComm;
	HANDLE				m_hWriteEvent;

	// Event array. 
	// One element is used for each event. There are two event handles for each port.
	// A Write event and a receive character event which is located in the overlapped structure (m_ov.hEvent).
	// There is a general shutdown when the port is closed. 
	HANDLE				m_hEventArray[3];

	// structures
	OVERLAPPED			m_ov;
	COMMTIMEOUTS		m_CommTimeouts;
	DCB					m_dcb;

	// owner window
	CWnd*				m_pOwner;

	// misc
	UINT				m_nPortNr;
	char*				m_szWriteBuffer;
	DWORD				m_dwCommEvents;
	DWORD				m_nWriteBufferSize;
};


//////////////////////////////////////////////////////////////////////////
//
#define RX_BUF_LEN                        (1024)                     // 接收缓冲区长度
#define TX_BUF_LEN                        ( 128)                     // 发送缓冲区长度

#define JT_HEAD                           (0x08)                     // 监听帧头标记
#define JT_MIN_OFFSET                     (11)                       // 在找到监听帧表头后，能判断有效信息的最少剩余字节数

#define OUT_BUF_LEN                       ( 128)                     //输入缓冲区len，用于写write
#define DISP_BUF_LEN                      ( 256)					 //显示值缓冲区长度256

#define JT_COMM_TIMER                     ( 1000)                    // 监听需要较高的频率，在框架中使用定时器
#define UP_COMM_TIMER                     ( 1001)                    // 上传的定时发送时间
#define JT_COMM_TIMESPAN                  ( 64)                      // 监听需要较高的频率，在框架中使用定时器
#define UP_COMM_TIMESPAN                  ( 200)                     // 上传的定时发送时间

#define COMM_NO_ANSWER                    "读卡站无应答"



#define CBR2400         (0)   //"2400"
#define CBR4800         (1)   //"4800"
#define CBR9600         (2)   //"9600"
#define CBR14400        (3)   //"14400"
#define CBR19200        (4)   //19200
#define CBR38400        (5)   //38400
#define CBR56000        (6)   //56000
#define CBR57600        (7)   //57600
#define CBR115200       (8)   //115200
#define CBR128000       (9)   //128000
#define CBR256000       (10)  // 256000


#define COM0            (0)
#define COM1            (1)
#define COM2            (2)
#define COM3            (3)
#define COM4            (4)
#define COM5            (5)
#define COM6            (6)
#define COM7            (7)
#define COM8            (8)
#define COM9            (9)

#define DATABIT5        (0)     // 标题+序号，显示标记在构造函数中赋值，对象使用的值是经过解析的序号或标题或标记或经过
#define DATABIT6        (1)
#define DATABIT7        (2)
#define DATABIT8        (3)

#define STOPBIT1       (0)
#define STOPBIT2       (1)


class CSerialCom :  public CSerialPort
{
public:
	CSerialCom();
	~CSerialCom();
public:
	
	char * m_szPort[COM9+1];
    char * m_szStopBit[STOPBIT2+1];
	char * m_szParity[SPACEPARITY+1];
	char * m_szBandRate[CBR256000+1];
	char * m_szDataBit[DATABIT8+1];

	char  m_dispbuf[DISP_BUF_LEN];			      // 串口数据帧，显示值缓冲区长度256
	BYTE  m_rxbuf[RX_BUF_LEN];                    // 串口接收缓冲区
    BYTE  m_txbuf[TX_BUF_LEN];					  // 串口发送缓冲区


	CString DevideHexChar(  char HexChar);        // 字节操作转换工具
	char    CombineHexChar( char CharH,char CharL);
	void    HexStringFilter(CString &str);
	CString ChangeCharstr2Hexstr(CString Charstr);



	void LoadComFromIni(void);
	void SaveComToIni(void);

	char * FormatRec();  //格式化接收缓冲区,格式化为16进制数用于显示出串口通讯的数据帧的格式化，分析帧内容非Com模块的职能
	char * FormatSend(); //格式化发送缓冲区

	inline   int    getComPort(void)            { return m_nComPort;       }      // 存实际串口编号
	inline   void   setComPort(int comport)     { m_nComPort = comport;    }
	inline   int    getBandRate(void)           { return m_nBandRate;      }      // 存实际波特率
	inline   void   setBandRate(int bandrate)   { m_nBandRate = bandrate;  }
	inline   int    getDataBits(void)           { return m_nDataBits;      }      // 存实际数据  
	inline   void   setDataBits(int databits)   { m_nDataBits = databits;  }
	inline   int    getStopBit(void)            { return m_nStopBit;       }      // 存显示序号
	inline   void   setStopBit( int stopbit)    { m_nStopBit = stopbit;    }
	inline   int    getParity( void)            { return m_nParity;        }      // 存序号
	inline   void   setParity(int parity)       { m_nParity = parity;      }
	
private:

	DWORD			m_nBytesWrite;                                                 // 当前需要发送到串口 输出的字节数
	DWORD			m_nBytesRead;                                                  // 当前读入的串口数据字节数
	
    int             m_nComPort;
	int             m_nBandRate;
	int             m_nDataBits;                                                   // 数据位
	int             m_nStopBit;                                                    // 停止位
	int             m_nParity;													   // 奇偶校验	 

}; // 丢分号，会引起紧跟在下一个类定义提示错误，错误可能出现在下一个类定义文件中




#endif __SERIALPORT_H__


