/*
*	��������,��������
*/

#include "resource.h"

//˽�ж���
#define WM_USERRCLICKPROCESS	WM_USER + 901		//�û����Ҽ�(����)
#define WM_SETMYCURSOR			WM_USER + 902		//������

//��������

#define TRAN_DATA_LEN			2048 * 1024			//���ݽ�������

#define CLIENT_PROCESS_KILL		5010				//��ֹ�û�����
#define CLIENT_PROCESS_LIST		5018				//ˢ�½����б�

#define NOT_FIND_ANY_FILE		7000				//�Ҳ����κ��ļ�
#define GET_PROCESS_LIST_ERR	7006				//ȡ�����б�ʧ��
#define KILL_PROCESS_ERR		7007				//��ֹ����ʧ��

#define TRANS_DATA_ERR			8000				//ͨ�Ŵ���

#define CONN_FILE_PROC_SEND		4009				//���̹����͹ܵ�
#define CONN_FILE_PROC_RECV		4010				//���̹�����չܵ�

typedef struct _PROCESSLIST_
{
	char  szExeFile[256]; 
	DWORD th32ProcessID; 
	LONG  pcPriClassBase; 
	DWORD cntThreads; 
}PROCESSLIST,*LPPROCESSLIST;


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

void TransBagThread(LPVOID lPvoid);
BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);
BOOL ProcessOneTrans(LPCLIENTDATA pData);
BOOL SendBag(SOCKET s,char *Data,DWORD &len,UINT &command);
BOOL ReadBag(SOCKET s,char *Data,DWORD &len,UINT &command);
void BcdToAsc(unsigned char *BcdStr,unsigned char *AscStr,int BcdStrLen);
void AscToBcd(unsigned char *AscStr,unsigned char *BcdStr,int AscStrLen);
