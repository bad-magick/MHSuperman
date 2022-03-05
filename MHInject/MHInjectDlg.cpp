
// MHInjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MHInject.h"
#include "MHInjectDlg.h"
#include "afxdialogex.h"
#include "Inject.h"
#include <string>
#include "imagehlp.h"
#include "direct.h"
#include <fstream>
#include <vector>
#include <wchar.h>
#include <HtmlHelp.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

wstring procName2 = L"";
CString cUpdate = L"";
bool bCanWriteIni = false;
vector<wstring> vPaths;
vector<wstring> vFiles;
vector<wstring> vTypes;
CEdit cStatus;
HLOCAL hStatus;

BOOL FolderExists(CString strFolderName)
{   
    return GetFileAttributes(strFolderName) != INVALID_FILE_ATTRIBUTES;   
}

void gen_random_file(wchar_t *s, const int len)
{
	srand(GetTickCount());
    static const wchar_t alphanum[] =
        L"012345ABCDEF";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (wcslen(alphanum) - 1)];
    }

    s[len] = 0;
}


void ProgramProcessCheck(void)
{
	while (1) {
		if (GetTargetProcessIdFromProcname((wchar_t*)procName2.c_str()) != 0) {
			Sleep(2000);
			for (vector<wstring>::size_type i = 0; i < vFiles.size(); i++) {
				wchar_t update[100];
				swprintf(update, L"Injecting %i/%i...", (i+1), vFiles.size());
				cUpdate = update;
				SendMessage((HWND)hStatus, WM_SETTEXT, 0, (LPARAM)&update);
				//cStatus.SetWindowText(cUpdate);
				if (wcscmp(vTypes[i].c_str(), L"0") == 0) {
					//injected
					wstring temp = vPaths[i] + L"\\" + vFiles[i];
					LoadDll(procName2.c_str(), temp.c_str());
				}
				if (wcscmp(vTypes[i].c_str(), L"1") == 0) {
					//plugin
					wstring path = GetTargetPathFromProcname((wchar_t*)procName2.c_str());
					path = path + L"Addons\\";
					CString cPath = path.c_str();
					wchar_t newfilename[50];
					gen_random_file(newfilename, 32);
					wstring sNewFileName = newfilename;
					path = path + + L"mmds-" + sNewFileName + L".vdf";
					if (!FolderExists(cPath)) {
						::CreateDirectory(cPath, NULL);
						fstream File;
						File.open(path, ios::out);
						char sPath[2048];
						char sFile[200];
						wcstombs(sPath, vPaths[i].c_str(), 2048);
						wcstombs(sFile, vFiles[i].c_str(), 2048);
						File << "Plugin\n{\n\tfile \"" << sPath << "\\" << sFile << "\"\n}\n";
						File.close();
					}
				}
				Sleep(100);
			}

			//LoadDll(procName2.GetBuffer(0), "C:\\Users\\Den\\Documents\\Visual Studio 2010\\Projects\\MHSuperman\\bin\\Public\\PubConsole.dll");
			Sleep(1000);
			exit(0);
		}
		Sleep(50);
	}
}


// CMHInjectDlg dialog




CMHInjectDlg::CMHInjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMHInjectDlg::IDD, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMHInjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITPROCESS, m_Process);
	DDX_Control(pDX, IDC_EDIT2, m_Temp);
	DDX_Control(pDX, IDC_LISTDLLS, m_InjectList);
}

BEGIN_MESSAGE_MAP(CMHInjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDITPROCESS, &CMHInjectDlg::OnEnChangeEditprocess)
	ON_BN_CLICKED(IDCANCEL, &CMHInjectDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTONADD, &CMHInjectDlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTONREMOVE, &CMHInjectDlg::OnBnClickedButtonremove)
	ON_BN_CLICKED(IDC_BUTTONCLEAR, &CMHInjectDlg::OnBnClickedButtonclear)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTDLLS, &CMHInjectDlg::OnLvnItemchangedListdlls)
	ON_BN_CLICKED(IDC_HELP, &CMHInjectDlg::OnBnClickedHelp)
END_MESSAGE_MAP()


// CMHInjectDlg message handlers

BOOL CMHInjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	hStatus = m_Temp.GetSafeHwnd();

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ProgramProcessCheck, 0, 0, 0);
	m_InjectList.InsertColumn(0, NULL, 0, 136, -1);
	m_InjectList.InsertColumn(1, NULL, 0, 0, 0);
	m_InjectList.InsertColumn(2, NULL, 0, 0, 1);

	ReadIni();
	bCanWriteIni = true;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMHInjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMHInjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMHInjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMHInjectDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CreateIni();
	CDialogEx::OnCancel();
}

void CMHInjectDlg::OnEnChangeEditprocess()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString proc(procName2.c_str());
	m_Process.GetWindowText(proc);
	//m_Temp.SetWindowTextA(procName2);
	CreateIni();
}

void CMHInjectDlg::AddDllToList(wchar_t *path, wchar_t* filename)
{
	wchar_t me[2048];
	swprintf(me, L"%s\\%s", path, filename);

	ifstream fLC(me);

	if (!fLC.good()) {
		return;
	}
	fLC.close();

	int nIndex = m_InjectList.InsertItem(m_InjectList.GetItemCount(), filename);
	m_InjectList.SetItemText(nIndex, 1, path);
	wchar_t fullpath[2048];
	swprintf(fullpath, L"%s\\%s", path, filename);
	bool bIsPlugin = false;
	bool bFuckNexon = false;

	_LOADED_IMAGE LoadedImage;
	_IMAGE_EXPORT_DIRECTORY *ImageExportDirectory;
	unsigned long cDirSize;
	DWORD *dNameRVAs(0);
	string sName;
	char fp[2048];
	wcstombs(fp, fullpath, 2048);
	MapAndLoad(fp, NULL, &LoadedImage, true, true);
	ImageExportDirectory = (_IMAGE_EXPORT_DIRECTORY*)ImageDirectoryEntryToData(LoadedImage.MappedAddress, false, IMAGE_DIRECTORY_ENTRY_EXPORT, &cDirSize);
	if (ImageExportDirectory != NULL) {
		dNameRVAs = (DWORD *)ImageRvaToVa(LoadedImage.FileHeader, LoadedImage.MappedAddress, ImageExportDirectory->AddressOfNames, NULL);
		for(size_t i = 0; i < ImageExportDirectory->NumberOfNames; i++) {
			sName = (char*)ImageRvaToVa(LoadedImage.FileHeader, LoadedImage.MappedAddress, dNameRVAs[i], NULL);
			if (strcmp(sName.c_str(), "FuckNexon") == 0) {
				bFuckNexon = true;
			}
			if (strcmp(sName.c_str(), "CreateInterface") == 0) {
				bIsPlugin = true;
			}
		}
	}
	UnMapAndLoad(&LoadedImage);

	vPaths.push_back(path);
	vFiles.push_back(filename);
	
	if (bIsPlugin && bFuckNexon) {
		//we have a plugin
		m_InjectList.SetItemText(nIndex, 2, L"1");
		vTypes.push_back(L"1");
	} else {
		//normal injection
		m_InjectList.SetItemText(nIndex, 2, L"0");
		vTypes.push_back(L"0");
	}
}

void CMHInjectDlg::CreateIni(void)
{
	if (!bCanWriteIni) {return;}
	wchar_t filename[2048];
	wchar_t file1[2048];
	_wgetcwd(file1, 2048);
	swprintf(filename, L"%s\\MHInject.ini", file1);
	wchar_t count[50];
	wchar_t temp[2048];
	wchar_t key[20];
	char fn[2048];
	wcstombs(fn, filename, 2048);
	remove(fn);
	WritePrivateProfileString(NULL, NULL, NULL, filename);

	vPaths.clear();
	vFiles.clear();
	vTypes.clear();

	swprintf(temp, L"%s", procName2);
	WritePrivateProfileString(L"Options", L"Process", temp, filename);

	swprintf(count, L"%i", m_InjectList.GetItemCount());
	WritePrivateProfileString(L"Inject", L"Count", count, filename);
	for (int i = 0; i < m_InjectList.GetItemCount(); i++) {
		swprintf(key, L"%i_Path", (i+1));
		m_InjectList.GetItemText(i, 1, temp, 2048);
		WritePrivateProfileString(L"Inject", key, temp, filename);

		swprintf(key, L"%i_File", (i+1));
		m_InjectList.GetItemText(i, 0, temp, 2048);
		WritePrivateProfileString(L"Inject", key, temp, filename);

		m_InjectList.GetItemText(i, 2, temp, 2048);
	}
}

void CMHInjectDlg::ReadIni(void)
{
	wchar_t filename[2048];
	wchar_t file1[2048];
	_wgetcwd(file1, 2048);
	swprintf(filename, L"%s\\MHInject.ini", file1);
	wchar_t count[50];
	wchar_t path[2048];
	wchar_t file[2048];
	wchar_t key[20];
	wchar_t temp[2048];


	ifstream fLC(filename);
	if (fLC.good()) {
		//ini exists
		GetPrivateProfileString(L"Options", L"Process", L"Vindictus.exe", temp, 2048, filename);
		m_Process.SetWindowText(temp);
		procName2 = temp;

		GetPrivateProfileString(L"Inject", L"Count", L"0", count, 50, filename);
		for (int i = 0; i < stoi(count); i++) {
			swprintf(key, L"%i_Path", (i+1));
			GetPrivateProfileString(L"Inject", key, L"", path, 2048, filename);
			swprintf(key, L"%i_File", (i+1));
			GetPrivateProfileString(L"Inject", key, L"", file, 2048, filename);
	
			AddDllToList(path, file);
		}
	} else {
		//ini missing
		m_Process.SetWindowText(L"Vindictus.exe");
		procName2 = L"Vindictus.exe";
		AddDllToList(file1, L"MHSuperman.dll");
		CreateIni();
	}
}
	
void CMHInjectDlg::OnBnClickedButtonadd()
{
	// TODO: Add your control notification handler code here
	CFileDialog openDll(true, L".dll", NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, L"Dynamic Link Libraries (*.dll)|*.dll||", NULL);
	if (openDll.DoModal() == IDOK) {
		AddDllToList(openDll.GetFolderPath().GetBuffer(0), openDll.GetFileName().GetBuffer(0));
		CreateIni();
	}
}


void CMHInjectDlg::OnBnClickedButtonremove()
{
	int nSelected = m_InjectList.GetSelectionMark();
	m_InjectList.DeleteItem(nSelected);
	CreateIni();
}


void CMHInjectDlg::OnBnClickedButtonclear()
{
	m_InjectList.DeleteAllItems();
	CreateIni();
}


void CMHInjectDlg::OnLvnItemchangedListdlls(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CMHInjectDlg::OnBnClickedHelp()
{
	// TODO: Add your control notification handler code here
	HWND WINAPI HtmlHelp(HWND hwndCaller, LPCTSTR pszFile, UINT uCommand, WORD* dwData);
	HWND hwndHelp = HtmlHelpA(NULL, "MHSuperman.chm::MHInject.htm", HH_DISPLAY_TOPIC, NULL);
}
