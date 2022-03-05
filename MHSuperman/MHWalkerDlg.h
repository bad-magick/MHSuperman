#pragma once

#ifdef _USE_MFC
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"

;
// MHWalkerDlg dialog

class MHWalkerDlg : public CDialog
{
	DECLARE_DYNAMIC(MHWalkerDlg)

public:
	MHWalkerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~MHWalkerDlg();

// Dialog Data
	enum { IDD = IDD_MHWALKERDIALOG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabStrip;
};
#endif