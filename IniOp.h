// IniOp.h: interface for the CIniOp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIOP_H__754C77D5_7CD1_46A1_8457_07734A1E7FE2__INCLUDED_)
#define AFX_INIOP_H__754C77D5_7CD1_46A1_8457_07734A1E7FE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniOp  
{
public:
	CIniOp();
	virtual ~CIniOp();

public:	
	static DWORD ReadString (char *section, char * key,  char stringtoread[],  char * filename);
    static BOOL  WriteString(LPCTSTR section, LPCTSTR key,char* stringtoadd, char *filename);
};


//////////////////////////////////////////////////////////////////////////
// File :		Tokenizer.h
// Created :	06/18/04
// 字符串操作类，用于读取ini 等类型的文本文件
//////////////////////////////////////////////////////////////////////////
class CTokenizer
{
public:
	// Construction/destruction
	inline CTokenizer(){}
	CTokenizer( CString strInput, const CString & strDelimiter = _T(",") );
	
	// Operations
	void Init( const CString & strInput, const CString & strDelimiter = _T(",") );
	int  GetSize( ) const;
	void GetAt( int nIndex, CString & str ) const;
	void GetAt( int nIndex, int  & var    ) const;
	void GetAt( int nIndex, BYTE & var    ) const;
	void GetAt( int nIndex, double & var  ) const;
	void GetAt( int nIndex, DWORD & var   ) const;
	void GetAt( int nIndex, WORD  & var   ) const;
	// Attributes
private:
	CStringArray m_stra;
};

class CTools
{
public:
	inline  CTools() {}
	inline  CTools ( WORD seconds )     { m_wSeconds =  seconds; }
	inline  CTools ( CString strInput ) { m_strtime = strInput; }
//	     WORD  Init( const CString & strInput);                  // 字符串时间格式，转为秒数
static	DWORD  Init( const CString & strInput);
	  CString  Init( const DWORD   & seconds );                  // 字类型，秒数，转换为时间格式字符串
	  CString  Init( const DWORD   & seconds,BOOL fulltime );    // 双子类型  

    inline WORD    GetSeconds( void ) const  { return m_wSeconds; }
    inline CString GetDispTime(void ) const  { return m_strtime; }

    inline static time_t Chg2Time(time_t &timespan )
	{
		CTime  cur =  CTime::GetCurrentTime();
		CTime  day  = CTime(cur.GetYear(),cur.GetMonth(),cur.GetDay(),0,0,0);   // 当前0点
		return timespan = day.GetTime() + timespan;								// 0点时间 + 时间间隔 = 当前时间的time_t表示形式
	};
    
private:
    CString   m_strtime;
	WORD      m_wSeconds;
//	DWORD     m_dwSeconds;
};


#endif // !defined(AFX_INIOP_H__754C77D5_7CD1_46A1_8457_07734A1E7FE2__INCLUDED_)
