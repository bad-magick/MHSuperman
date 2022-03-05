// MHWalkerDlg.cpp : implementation file
//
#ifdef _USE_MFC

#include "stdafx.h"
#include "MHSuperman.h"
#include "MHWalkerDlg.h"
//#include "afxdialog.h"

IMPLEMENT_DYNAMIC(MHWalkerDlg, CDialog)

MHWalkerDlg::MHWalkerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MHWalkerDlg::IDD, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

MHWalkerDlg::~MHWalkerDlg()
{
}

void MHWalkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabStrip);
}


BEGIN_MESSAGE_MAP(MHWalkerDlg, CDialog)
END_MESSAGE_MAP()

BOOL MHWalkerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		/*CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}*/
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//m_TabStrip.Create

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// MHWalkerDlg message handlers

#endif