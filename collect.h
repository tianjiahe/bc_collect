// collect.h : main header file for the COLLECT application
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCollectApp:
// See collect.cpp for the implementation of this class
//

 
class CCollectApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CCollectApp();

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCollectApp)
	public:
	virtual BOOL InitInstance();
	virtual int  ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCollectApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



extern CCollectApp		theApp;
//extern CComOp			theCom;
extern CSerialCom       theCom;
extern CProtocol		thePtl;                                     // 串口通讯协议
extern CIniOp			theIni;                                     // 读写ini文件 
extern CTools			theTools;                                   // 其他工具
extern CTokenizer		strHelper;                                  // 字符串分解操作工具
extern CUsers           users;     
//CDBHelper  theDB;							           // 数据库访问工具

/////////////////////////////////////////////////////////////////////////////
