#if !defined(AFX_OPERTETOOLBAR_H__53E0910E_9E0E_4DB3_A003_44682E5F85C1__INCLUDED_)
#define AFX_OPERTETOOLBAR_H__53E0910E_9E0E_4DB3_A003_44682E5F85C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperteToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COperteToolBar dialog，因为向导不提供，这里由对话框派生的，需要改到CDialogBar为基类，
// 属性页的设置,child,visible=false,border= none,其他的都不要选。否则不能做。
//class COperteToolBar : public CDialog
class COperteToolBar : public CDialogBar
{
// Construction
public:
	COperteToolBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COperteToolBar)
	enum { IDD = IDD_DIALOG_OPERATE_TOOLBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperteToolBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COperteToolBar)
	virtual BOOL OnInitDialog(UINT, LONG );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERTETOOLBAR_H__53E0910E_9E0E_4DB3_A003_44682E5F85C1__INCLUDED_)
