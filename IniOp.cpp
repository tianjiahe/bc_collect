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
    purpose:    读取INI文件。
*********************************************************************/ 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CIniOp::CIniOp()  { }
CIniOp::~CIniOp() { }
/*****************************************************************************
Function:       // 
Description:    // 写字符串到INI文件
Calls:          // 
Called By:      // 
Table Accessed: // 
Table Updated:  // 
Input:          // 
Output:         // 
Return:         // 成功返回真，失败返回假.失败后，可用DWORD GetLastError(VOID)
                   查询失败原因。
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
Description:    // 从INI文件中读取字符串
Calls:          // 
Called By:      // 
Table Accessed: // 
Table Updated:  // 
Input:          // 
Output:         // 
Return:         // 读取了多少个字节的字符
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


// 示例
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
//  增加一个WORD类型的解析-
//////////////////////////////////////////////////////////////////////////
void CTokenizer::GetAt( int nIndex,  WORD & var)  const
{
      if ( nIndex < m_stra.GetSize() )
      
		   var  = static_cast< WORD >( _ttoi( m_stra.GetAt( nIndex) ) );
      else
		   var  = 0;  
}


// 时间字符串，时分秒格式，转成秒数
 
DWORD  CTools::Init( const CString &strInput)
{
	BYTE   hour, minute, second;
	CTokenizer  token(strInput,':');          // 08:06:09
    token.GetAt(	0,	hour   ); 
	token.GetAt(	1,	minute );
	token.GetAt(	2,	second );
	return (hour * 3600 + minute * 60 + second);     //时间对应的秒数 
}

// 秒数转换时分秒显示
CString CTools::Init( const DWORD &seconds )
{
    BYTE   hour,minute,second;
	hour   = (BYTE)(seconds / 3600);
	minute = (BYTE)((seconds / 60) % 60);
	second = (BYTE)(seconds % 60);
    m_strtime.Format("%02d:%02d:%02d", hour, minute, second );
	return  m_strtime;
}


// 格式化时间，把秒数，转换为时分秒字符串
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



//////////////////////////////////////////////////////////////////////////
// CUsers 用户权限管理类
CUsers::~CUsers()  {  }
CUsers::CUsers()
{
    //ZeroMemory( m_list, sizeof(m_list) );        
	CFileFind finder;

    m_file = "C:\\windows\\system32\\collect.sys";

	BOOL bfined = finder.FindFile( m_file );
	if(bfined)
	{
		bfined = finder.FindNextFile();
        Load();
	}
	else
	{
       CFile file;
	   file.Open( m_file, CFile::modeCreate|CFile::modeWrite);   // 新建文件
       return;
	}

	
	//	用CFile声明一个对象，然后用这个对象的指针做参数声明一个CArchive对象，你就可以非常方便地存储各种复杂的数据类型了


}



void CUsers::Save()
{
	CString  strTemp;
	CFile    file;
    

    file.Open(  m_file,  CFile::modeWrite);
	CArchive ar( &file,  CArchive::store );

	TRY
	{
		ar<<m_list.GetSize();
        for (int i = 0; i < m_list.GetSize(); i++ )
        {
			ar<< m_list[i].username << m_list[i].password << m_list[i].roalIndex;
        }
	}
    CATCH( CArchiveException, e1)      {    OutputDebugString("archive operation error!" + e1->m_strFileName);   }
    AND_CATCH ( CFileException, e2 )   {	OutputDebugString("file operation error! "+ e2->m_strFileName );   }
    END_CATCH

    ar.Close();
    file.Close();

}


/*
　　CArchive的 << 和>> 操作符用于简单数据类型的读写，对于CObject派生类的对象的存取要使用ReadObject()和WriteObject()。使用CArchive的ReadClass()和WriteClass()还可以进行类的读写，如：
　　ar.WriteClass(RUNTIME_CLASS(CAboutDlg));		//存储CAboutDlg类
　　CRuntimeClass* mRunClass=ar.ReadClass();		//读取CAboutDlg类
　　CObject* pObject=mRunClass->CreateObject();		//使用CAboutDlg类
    ((CDialog* )pObject)->DoModal();
*/


void CUsers::Load()
{
	CString strTemp;
	CFile   file;
    file.Open(  m_file,  CFile::modeRead);
	CArchive ar( &file,   CArchive::load );
    int count;
	
	tagUser user;
   TRY
   {
        ar>>count;
		for (int i=0; i < count; i++ )
		{
			ar>>user.username>>user.password>>user.roalIndex;
		    m_list.Add(user);
		}
        
		
   }
   CATCH( CArchiveException, e1)    {   OutputDebugString("archive operation error!" + e1->m_strFileName); }
   AND_CATCH ( CFileException, e2 ) {   OutputDebugString("file operation error! " + e2->m_strFileName );  }
   END_CATCH

   ar.Close();
   file.Close();
   

}
