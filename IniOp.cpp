// IniOp.cpp: implementation of the CIniOp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "collect.h"
#include "IniOp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/********************************************************************
    created:      20011/04/26
    created:      9:17
    filename:     IniOp.cpp
    file base:    IniOp
    file ext:     cpp
    author:      
    purpose:    ��ȡINI�ļ���
*********************************************************************/ 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CIniOp::CIniOp()  { }
CIniOp::~CIniOp() { }
/*****************************************************************************
Function:       // 
Description:    // д�ַ�����INI�ļ�
Calls:          // 
Called By:      // 
Table Accessed: // 
Table Updated:  // 
Input:          // 
Output:         // 
Return:         // �ɹ������棬ʧ�ܷ��ؼ�.ʧ�ܺ󣬿���DWORD GetLastError(VOID)
                   ��ѯʧ��ԭ��
Others:         // 
author:         // alantop
date:           // 2007.07.19
******************************************************************************/
/*
void error(LPSTR lpszFunction) 
{ 
    CHAR szBuf[80]; 
    DWORD dw = GetLastError(); 
    sprintf(szBuf, "%s failed: GetLastError returned %u\n", 
        lpszFunction, dw); 
    MessageBox(NULL, szBuf, "Error", MB_OK); 
    ExitProcess(dw); 
} 

*/
BOOL CIniOp::WriteString(LPCTSTR section, LPCTSTR key, char *stringtoadd, char *filename)
{
    CHAR FilePath[255]; 
    GetModuleFileName(NULL,FilePath,255); 
    //Scan a string for the last occurrence of a character.
    (strrchr(FilePath,'\\'))[1] = 0; 
    strcat(FilePath,filename);
    return ::WritePrivateProfileString(section,key,stringtoadd,FilePath);
} 

/*****************************************************************************
Function:       // 
Description:    // ��INI�ļ��ж�ȡ�ַ���
Calls:          // 
Called By:      // 
Table Accessed: // 
Table Updated:  // 
Input:          // 
Output:         // 
Return:         // ��ȡ�˶��ٸ��ֽڵ��ַ�
Others:         // 
author:         // alantop
date:           // 2007.07.19
******************************************************************************/
DWORD CIniOp::ReadString(char *section, char * key,  char stringtoread[],  char * filename)
{
    CHAR FilePath[255]; 
    GetModuleFileName(NULL,FilePath,255); 
    (strrchr(FilePath,'\\'))[1] = 0; 
    strcat(FilePath,filename);
    return ::GetPrivateProfileString(section, key,NULL,stringtoread,255,FilePath);
} 


// ʾ��
// #include <stdio.h>
// #include "opini.h" 
// 
// void main()
// {
//     char stringtoread[200];
//     COPini::ReadString("group", "item", stringtoread, "test.ini");
//     char stringtoadd[] = "hello1";
//     COPini::WriteString("group", "item",  stringtoadd, "test.ini");
//     return;
// }



/* ==========================================================================
	Class :			CTokenizer
	Date :			06/18/04
	Purpose :		"CTokenizer" is a very simple class to tokenize a string into a string array.
	Description :	The string is chopped up and put into an internal "CStringArray". With "GetAt", different types of data can 
					be read from the different elements.
	Usage :			Create an instance of "CTokenizer" on the stack. Set the string to parse in the "ctor", and the delimiter if 
					not a comma. The "ctor" automatically tokenize the input string.
					Call "GetSize" to get the number of	tokens, and "GetAt" to get a specific token.
					You can also reuse the tokenizer by calling "Init".
   ========================================================================
	Changes :		28/8  2004	Changed a char to TCHAR to allow UNICODE building (Enrico Detoma)
   ========================================================================*/


////////////////////////////////////////////////////////////////////
// Public functions
//
CTokenizer::CTokenizer( CString strInput, const CString & strDelimiter )
/* ============================================================
	Function :		CTokenizer::CTokenizer
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	CString strInput				-	String to tokenize
					const CString & strDelimiter	-	Delimiter,defaults to comma.
	Usage :			Should normally be created on the stack.
   ============================================================*/
{
	Init(strInput, strDelimiter);
}

void CTokenizer::Init( const CString & strInput, const CString & strDelimiter )
/* ============================================================
	Function :		CTokenizer::Init
	Description :	Reinitializes and tokenizes the tokenizer with "strInput". "strDelimiter" is the delimiter to use.
	Access :		Public					
	Return :		void
	Parameters :	const CString & strInput		-	New string
					const CString & strDelimiter	-	Delimiter,
														defaults to 
														comma
	Usage :			Call to reinitialize the tokenizer.
 ============================================================*/
{

	CString copy( strInput );
	m_stra.RemoveAll();
	int nFound = copy.Find( strDelimiter );

	while(nFound != -1)
	{
		CString strLeft;
		strLeft = copy.Left( nFound );
		copy = copy.Right( copy.GetLength() - ( nFound + 1 ) );

		m_stra.Add( strLeft );
		nFound = copy.Find( strDelimiter );
	}

	m_stra.Add( copy );

}

int CTokenizer::GetSize(  ) const
/* ============================================================
	Function :		CTokenizer::GetSize
	Description :	Gets the number of tokens in the tokenizer.
	Access :		Public
	Return :		int	-	Number of tokens.
	Parameters :	none
	Usage :			Call to get the number of tokens in the 
					tokenizer.

   ============================================================*/
{
	return m_stra.GetSize();
}

void CTokenizer::GetAt( int nIndex, CString & str ) const
/* ============================================================
	Function :		CTokenizer::GetAt
	Description :	Get the token at "nIndex" and put it in "str".
	Access :		Public
	Return :		void
	Parameters :	int nIndex		- Index to get token from
					CString & str	- Result
	Usage :			Call to get the value of the token at "index".
   ============================================================*/
{

		if( nIndex < m_stra.GetSize() )
			str = m_stra.GetAt( nIndex );
		else
			str = _T( "" );
}

void CTokenizer::GetAt( int nIndex, int & var ) const
/* ============================================================
	Function :		CTokenizer::GetAt
	Description :	Get the token at "nIndex" and put it in "var".
	Access :		Public
	Return :		void
	Parameters :	int nIndex	- Index to get token from
					int & var	- Result
	Usage :			Call to get the value of the token at "index".
   ============================================================*/
{

		if( nIndex < m_stra.GetSize() )
			var = _ttoi( m_stra.GetAt( nIndex ) );
		else
			var = 0;

}

void CTokenizer::GetAt( int nIndex, BYTE & var ) const
/* ============================================================
	Function :		CTokenizer::GetAt
	Description :	Get the token at "nIndex" and put it in "var".
	Access :		Public
					
	Return :		void
	Parameters :	int nIndex	- Index to get token from
					WORD & var	- Result

	Usage :			Call to get the value of the token at "index".
   ============================================================*/
{

		if( nIndex < m_stra.GetSize() )
			var = static_cast< BYTE >( _ttoi( m_stra.GetAt( nIndex ) ) );
		else
			var = 0;

}

void CTokenizer::GetAt( int nIndex, double & var ) const
/* ============================================================
	Function :		CTokenizer::GetAt
	Description :	Get the token at "nIndex" and put it in "var".
	Access :		Public
	Return :		void
	Parameters :	int nIndex		- Index to get token from 
	                double & var	- Result
	Usage :			Call to get the value of the token at "index".
   ============================================================*/
{
		TCHAR   *stop;
		if( nIndex < m_stra.GetSize() )
			var = _tcstod( m_stra.GetAt( nIndex ), &stop );
		else
			var = 0.0;

}

void CTokenizer::GetAt( int nIndex, DWORD & var ) const
/* ============================================================
	Function :		CTokenizer::GetAt
	Description :	Get the token at "nIndex" and put it in "var".
	Access :		Public
	Return :		void
	Parameters :	int nIndex	- Index to get token from
					DWORD & var	- Result
	Usage :			Call to get the value of the token at "index".
   ============================================================*/
{

		if( nIndex < m_stra.GetSize() )
			var = static_cast< DWORD >( _ttoi( m_stra.GetAt( nIndex ) ) );
		else
			var = 0;

}

//  [6/20/2014 Administrator]
//  ����һ��WORD���͵Ľ���-
//////////////////////////////////////////////////////////////////////////
void CTokenizer::GetAt( int nIndex,  WORD & var)  const
{
      if ( nIndex < m_stra.GetSize() )
      
		   var  = static_cast< WORD >( _ttoi( m_stra.GetAt( nIndex) ) );
      else
		   var  = 0;  
}


// ʱ���ַ�����ʱ�����ʽ��ת������
 
DWORD  CTools::Init( const CString &strInput)
{
	BYTE   hour, minute, second;
	CTokenizer  token(strInput,':');          // 08:06:09
    token.GetAt(	0,	hour   ); 
	token.GetAt(	1,	minute );
	token.GetAt(	2,	second );
	return (hour * 3600 + minute * 60 + second);     //ʱ���Ӧ������ 
}

// ����ת��ʱ������ʾ
CString CTools::Init( const DWORD &seconds )
{
    BYTE   hour,minute,second;
	hour   = seconds / 3600;
	minute = (seconds / 60) % 60;
	second = seconds % 60;
    m_strtime.Format("%02d:%02d:%02d", hour, minute, second );
	return  m_strtime;
}


// ��ʽ��ʱ�䣬��������ת��Ϊʱ�����ַ���
CString CTools::Init( const DWORD &seconds,BOOL fulltime)
{
    BYTE   hour,minute,second;
	hour   = (BYTE)(seconds  / 3600);
	minute = (BYTE)((seconds / 60) % 60);
	second = (BYTE)(seconds  % 60);
    if (fulltime) {
		m_strtime.Format("%d-%02d:%02d:%02d", hour/24,hour%24, minute, second );
    }
	else{
		m_strtime.Format("%02d:%02d:%02d", hour, minute, second );
	}
    
	return  m_strtime;
}    
