// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently

#define VC_EXTRALEAN

#include <afxwin.h>      // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)
#include <afxtempl.h>

#include "Pegrpagi.h"
#include "math.h"


//#include "ComOp.h"				// ����ͨѶ�����࣬�򵥵Ĳ������������Ʊ򲩿�

#include "SerialPort.h"             //   ����ͨѶ������  AUTHOR Remon Spekreijse
#include "protocol.h"
#include "IniOp.h"				   // ini �ļ�����

#include "CSPVC.h"                 // ���˵�ɫ�ǳ����ṩ��������λ�����

#define  CONFIG_FILE	"BC.ini"      //ϵͳ�����ļ�����



#pragma comment(lib, "CSPVC.lib")
