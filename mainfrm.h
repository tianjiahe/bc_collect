// mainfrm.h : interface of the CMainFrame class
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

#include "OperteToolBar.h"
#include "CmdToolBar.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	UINT m_nCurrentExample;

// Operations
public:

// Overrides
	void OnExample(UINT nCmdID);
	void OnUpdateExampleUI(CCmdUI* pCmdUI);
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_sWinTitle;
	BOOL m_bIsScan;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar      m_wndStatusBar;
	CToolBar        m_wndToolBar;
	CReBar          m_wndReBar;            // 自定义工具框容器，伸缩条
	COperteToolBar  m_wndOpBar;        // 自定义，操作界面工具对话框
	CCmdToolBar     m_wndCmdBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonDataSave();
	afx_msg void OnViewOperBar();
	afx_msg void OnUpdateViewOperBar(CCmdUI* pCmdUI);
	afx_msg void OnMenuUser();
	afx_msg void OnCheckStartScan();
	afx_msg void OnButton1();
	afx_msg void OnCommset();
	afx_msg void OnMenuNewUser();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
