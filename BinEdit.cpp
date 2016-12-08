// BinEdit.cpp : implementation file
//

#include "stdafx.h"
#include "collect.h"
#include "BinEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBinEdit

CBinEdit::CBinEdit()
{
}

CBinEdit::~CBinEdit()
{
}


BEGIN_MESSAGE_MAP(CBinEdit, CEdit)
	//{{AFX_MSG_MAP(CBinEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBinEdit message handlers

void CBinEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	static  int count=0, a;

	if(nChar==VK_BACK)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		count--;
		if(count<0)   {  count = 0;}
	}
	if(nChar=='0' || nChar=='1')
	{
		if( count<8 )	  	  {	a = 0; }
		if( count<8 && a==0 )
		{		
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			count++;
		}	
	}	
	else
	{
		if(count==8)	{	a = 1; }
	}
}
