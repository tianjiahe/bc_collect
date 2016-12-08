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
#define RX_BUF_LEN                        (1024)                     // ���ջ���������
#define TX_BUF_LEN                        ( 128)                     // ���ͻ���������

#define JT_HEAD                           (0x08)                     // ����֡ͷ���
#define JT_MIN_OFFSET                     (11)                       // ���ҵ�����֡��ͷ�����ж���Ч��Ϣ������ʣ���ֽ���

#define OUT_BUF_LEN                       ( 128)                     //���뻺����len������дwrite
#define DISP_BUF_LEN                      ( 256)					 //��ʾֵ����������256

#define JT_COMM_TIMER                     ( 1000)                    // ������Ҫ�ϸߵ�Ƶ�ʣ��ڿ����ʹ�ö�ʱ��
#define UP_COMM_TIMER                     ( 1001)                    // �ϴ��Ķ�ʱ����ʱ��
#define JT_COMM_TIMESPAN                  ( 64)                      // ������Ҫ�ϸߵ�Ƶ�ʣ��ڿ����ʹ�ö�ʱ��
#define UP_COMM_TIMESPAN                  ( 200)                     // �ϴ��Ķ�ʱ����ʱ��

#define COMM_NO_ANSWER                    "����վ��Ӧ��"



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

#define DATABIT5        (0)     // ����+��ţ���ʾ����ڹ��캯���и�ֵ������ʹ�õ�ֵ�Ǿ�����������Ż������ǻ򾭹�
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

	char  m_dispbuf[DISP_BUF_LEN];			      // ��������֡����ʾֵ����������256
	BYTE  m_rxbuf[RX_BUF_LEN];                    // ���ڽ��ջ�����
    BYTE  m_txbuf[TX_BUF_LEN];					  // ���ڷ��ͻ�����


	CString DevideHexChar(  char HexChar);        // �ֽڲ���ת������
	char    CombineHexChar( char CharH,char CharL);
	void    HexStringFilter(CString &str);
	CString ChangeCharstr2Hexstr(CString Charstr);



	void LoadComFromIni(void);
	void SaveComToIni(void);

	char * FormatRec();  //��ʽ�����ջ�����,��ʽ��Ϊ16������������ʾ������ͨѶ������֡�ĸ�ʽ��������֡���ݷ�Comģ���ְ��
	char * FormatSend(); //��ʽ�����ͻ�����

	inline   int    getComPort(void)            { return m_nComPort;       }      // ��ʵ�ʴ��ڱ��
	inline   void   setComPort(int comport)     { m_nComPort = comport;    }
	inline   int    getBandRate(void)           { return m_nBandRate;      }      // ��ʵ�ʲ�����
	inline   void   setBandRate(int bandrate)   { m_nBandRate = bandrate;  }
	inline   int    getDataBits(void)           { return m_nDataBits;      }      // ��ʵ������  
	inline   void   setDataBits(int databits)   { m_nDataBits = databits;  }
	inline   int    getStopBit(void)            { return m_nStopBit;       }      // ����ʾ���
	inline   void   setStopBit( int stopbit)    { m_nStopBit = stopbit;    }
	inline   int    getParity( void)            { return m_nParity;        }      // �����
	inline   void   setParity(int parity)       { m_nParity = parity;      }
	
private:

	DWORD			m_nBytesWrite;                                                 // ��ǰ��Ҫ���͵����� ������ֽ���
	DWORD			m_nBytesRead;                                                  // ��ǰ����Ĵ��������ֽ���
	
    int             m_nComPort;
	int             m_nBandRate;
	int             m_nDataBits;                                                   // ����λ
	int             m_nStopBit;                                                    // ֹͣλ
	int             m_nParity;													   // ��żУ��	 

}; // ���ֺţ��������������һ���ඨ����ʾ���󣬴�����ܳ�������һ���ඨ���ļ���




#endif __SERIALPORT_H__


