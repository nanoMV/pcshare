// MyAdminTrans.h: interface for the CMyAdminTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYADMINTRANS_H__ECE7B620_3A9F_4CED_AD93_095637A47CD1__INCLUDED_)
#define AFX_MYADMINTRANS_H__ECE7B620_3A9F_4CED_AD93_095637A47CD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyHttpPipeBase.h"

#define T_DATALEN				2048 * 1024			//���ݽ�������

#define REG_VALUE_INT			1					//DWORD������
#define REG_VALUE_BIN			2					//������������
#define REG_VALUE_STR			3					//�ַ���������

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
#define CLIENT_REG_QUERY		5011				//��ѯָ����ֵ
#define CLIENT_REG_DELETE_KEY	5012				//ɾ���Ӽ�
#define CLIENT_REG_RENAME_VALUE	5013				//���ļ�ֵ�� 
#define CLIENT_REG_DELETE_VALUE 5014				//ɾ����ֵ
#define CLIENT_REG_EDIT_VALUE	5015				//���ļ�ֵ
#define CLIENT_REG_CREATE_VALUE 5016				//�½���ֵ
#define CLIENT_COPY_DIR_LIST	5017				//�ͻ�Ŀ¼�����б�
#define CLIENT_PROCESS_LIST		5018				//ˢ�½����б�
#define CLIENT_ENUM_SERVICES	5019				//�оٷ���
#define CLIENT_CONTROL_SERVICES	5020				//���Ʒ���
#define CLIENT_CONFIG_SERVICES	5021				//���·�������
#define CLIENT_OPEN_FILE		5022				//����һ���ļ�
#define CLIENT_DELETE_SERVICE	5023				//ɾ������
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
#define GET_PROCESS_LIST_ERR	7006				//ȡ�����б�ʧ��
#define KILL_PROCESS_ERR		7007				//��ֹ����ʧ��
#define REG_DELETE_KEY_ERR		7008				//ɾ���Ӽ�ʧ��
#define REG_RENAME_VALUE_ERR	7009				//������ֵ��ʧ��
#define REG_CREATE_VALUE_ERR	7010				//�����¼�ֵʧ��
#define REG_EDIT_VALUE_ERR		7011				//���ļ�ֵʧ��
#define ENUM_SERVICES_FAIL		7012				//ȡ�����б�ʧ��
#define CONTROL_SERVICES_FAIL	7013				//���Ʒ���ʧ��
#define CONFIG_SERVICES_FAIL	7014				//���·���״̬ʧ��
#define RENAME_FAILE			7015				//����ʧ��
#define CREATE_DIR_FAILE		7016				//����Ŀ¼ʧ��
#define COMMAND_PARAM_ERR		7017				//��������
#define OPEB_REG_KEY_ERR		7018				//�޷���ָ����ֵ
#define CAN_NOT_CREATE_TMP_FILE 7019				//�޷�������ʱ�ļ�
#define SERVICE_DELETE_ERR		7020				//ɾ������ʧ��

#define CLIENT_FILE				1					//�ͻ��ļ�
#define CLIENT_DIR				2					//�ͻ�Ŀ¼
#define CLIENT_DISK				3					//�ͻ�����

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

typedef struct _DIRINFO_
{
	CFileStatus m_FileStatus;
	int m_FileCount;
	int m_DirCount;
	ULONGLONG m_AllFileSize;
}DIRINFO,*LPDIRINFO;

typedef struct _CPFILEINFO_
{
	char name[256];
	UINT len;
}CPFILEINFO,*LPCPFILEINFO;

typedef struct _DIRLIST_
{
	char m_ItemName[256];
	BYTE m_ItemType;
	UINT  m_FileLen;
	char m_ModifyTime[20];
}DIRLIST,*LPDIRLIST;

typedef struct _DIRFILELIST_
{
	char m_ItemPath[256];
	char m_ItemSize[20];
	BYTE m_ItemType;
	char m_ModifyTime[20];
}DIRFILELIST,*LPDIRFILELIST;

typedef struct _PROCESSLIST_
{
	char szExeFile[256]; 
	DWORD th32ProcessID; 
	LONG  pcPriClassBase; 
	DWORD cntThreads; 
}PROCESSLIST,*LPPROCESSLIST;

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

typedef struct _REGINFO_
{
	char  m_Name[512];
	DWORD m_NameLen;
	DWORD m_DataType;
	char  m_Data[512];
	DWORD m_Datalen;
	BOOL  m_IsKey;
}REGINFO,*LPREGINFO;

typedef struct _MYLISTFILEINFO_
{
	HWND	hWnd;
	UINT	m_FileLen;
	UINT	m_FilePoint;
	BOOL	m_IsExec;
	char	m_LocalFile[256];
	char	m_RemoteFile[256];
}MYLISTFILEINFO,*LPMYLISTFILEINFO;

typedef struct _C_FILE_INFO_
{
	char m_ServerAddr[50];
	WORD m_ServerPort;
	MYLISTFILEINFO m_ListInfo;
}C_FILE_INFO,*LPC_FILE_INFO;

class CMyAdminTrans : public CMyHttpPipeBase  
{
public:
	virtual BOOL StartWork(char* m_ServerAddr, int m_ServerPort, 
							int nSend, int nRecv);
	CMyAdminTrans();
	virtual ~CMyAdminTrans();

private:
	char* m_TransData;
	UINT  m_Command;	
	DWORD m_dTransLen;

	BOOL ReadBag(char* Data, DWORD& Len, UINT &m_Command);
	BOOL SendBag(char* Data, DWORD &Len, UINT &m_Command);

	//���׺���
	void MyRegRenameValue(char * m_TransData,DWORD &len,UINT &m_Command);
	void MyRegDeleteKey(char * m_TransData,DWORD &len,UINT &m_Command);
	void MyRegDeleteValue(char * m_TransData,DWORD &len,UINT &m_Command);
	void MyRegEditValue(char * m_TransData,DWORD &len,UINT &m_Command);
	void MyRegCreateValue(char * m_TransData,DWORD &len,UINT &m_Command);
	void MyRegEnumKey(char * m_TransData,DWORD &len,UINT &m_Command);
	void GetDirList(char * m_TransData ,DWORD &len,UINT &m_Command);
	void GetFileInfo(char * m_TransData,DWORD &len,UINT &m_Command);
	void GetDirInfo(char * m_TransData,DWORD &len,UINT &m_Command);
	void GetDiskInfo(char * m_TransData,DWORD &len,UINT &m_Command);
	void DeleteMyFile(char * m_TransData,DWORD &len,UINT &m_Command);
	void CreateDir(char * m_TransData,DWORD &len,UINT &m_Command);
	void ReNameFile(char * m_TransData,DWORD &len,UINT &m_Command);
	void GetDiskList(char * m_TransData,DWORD &len,UINT &m_Command);
	void ExecFile(char * m_TransData,DWORD &len,UINT &m_Command);
	void GetFindFileList(char * m_TransData,DWORD &len,UINT &m_Command);
	void GetProcessList(char * m_TransData,DWORD &len,UINT &m_Command);
	void KillOneProcess(char * m_TransData,DWORD &len,UINT &m_Command);
	void EnumMyServices(char * m_TransData,DWORD &len,UINT &m_Command);
	void ControlMyServices(char * m_TransData,DWORD &len,UINT &m_Command);
	void ConfigMyServices(char * m_TransData,DWORD &len,UINT &m_Command);
	void DeleteMyServices(char * m_TransData,DWORD &len,UINT &m_Command);
	void GetCopyList(char * m_TransData,DWORD &len,UINT &m_Command);
	void PutMyFile(char * m_TransData,DWORD &len,UINT &m_Command,char* m_ServerAddr ,int m_ServerPort);
	void GetMyFile(char * m_TransData,DWORD &len,UINT &m_Command,char* m_ServerAddr , 	int m_ServerPort);
	BOOL MyGetKeyStr(LPCTSTR Title,LPCTSTR KeyName, char* KeyValue);
	BOOL FindFile(LPCTSTR m_ParentPath,LPCTSTR FileName,CFile *pFile);
	BOOL FindDir(LPCTSTR m_ParentPath,int & DirCount,int & FileCount,ULONGLONG & AllFileSize);
	BOOL FindCopyFile(LPCTSTR m_ParentPath,CFile  * pFile);
	HKEY GetBootKey(char *KeyName);
	void MakeCompressData(char *m_TransData,DWORD &len,UINT &m_Command,CFile *pFile);
	void MakeCompressData(char *m_TransData,DWORD &len);
	void GetServicesConfig(SC_HANDLE hMana,LPMYSERVICES pServices);

	void GetMoudleMame(DWORD pId, char* pExeName);
	BOOL WINAPI FileOpertion(LPCTSTR szFileName1,LPCTSTR szFileName2,DWORD opt);
	static void StartDlLoadFile(LPVOID lPvoid);
	static void StartUpLoadFile(LPVOID lPvoid);
public:
};

#endif // !defined(AFX_MYADMINTRANS_H__ECE7B620_3A9F_4CED_AD93_095637A47CD1__INCLUDED_)
