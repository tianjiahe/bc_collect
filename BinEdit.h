#if !defined(AFX_BINEDIT_H__0D095E17_3EB1_4C07_AB49_A3F2817A8D0D__INCLUDED_)
#define AFX_BINEDIT_H__0D095E17_3EB1_4C07_AB49_A3F2817A8D0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BinEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBinEdit window

class CBinEdit : public CEdit
{
// Construction
public:
	CBinEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBinEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBinEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBinEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINEDIT_H__0D095E17_3EB1_4C07_AB49_A3F2817A8D0D__INCLUDED_)
