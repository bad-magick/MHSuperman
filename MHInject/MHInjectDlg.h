
// MHInjectDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

extern CString cUpdate;

// CMHInjectDlg dialog
class CMHInjectDlg : public CDialogEx
{
// Construction
public:
	CMHInjectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MHINJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void AddDllToList(wchar_t *path, wchar_t* filename);
	void CreateIni(void);
	void ReadIni(void);
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEditprocess();
	CEdit m_Process;
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtonremove();
	afx_msg void OnBnClickedButtonclear();
	CEdit m_Temp;
	CListCtrl m_InjectList;
	afx_msg void OnLvnItemchangedListdlls(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedHelp();
};
