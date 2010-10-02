// ServiceManager.h: interface for the ServiceManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICEMANAGER_H__5CAA3541_4D6D_4EEE_979B_2B45E4596128__INCLUDED_)
#define AFX_SERVICEMANAGER_H__5CAA3541_4D6D_4EEE_979B_2B45E4596128__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <WinSvc.h>

// Windowsϵͳ���������
class ServiceManager  
{
public:
	ServiceManager();
	virtual ~ServiceManager();

	BOOL IsInstalled();  // �ж��Ƿ�װ����
	BOOL InstallService(); // ��װ����
	BOOL UninstallService(); // ɾ������
	void LogEvent(LPCTSTR pszFormat, ...); // ϵͳ��־��¼
	void WINAPI ServiceMain(); // ��������������������п��ƶԷ�����Ƶ�ע��
	void WINAPI ServiceControl(DWORD dwOpcode);
	static void WINAPI _ServiceMain();  // ֱ�ӵ���ServiceMain
	static void WINAPI _ServiceControl(DWORD dwOpcode); // ֱ�ӵ���ServiceControl

	BOOL StartService(); // ��������
	BOOL TerminateService(); // ��ֹ����
	BOOL IsServiceRunning(); // �жϷ����Ƿ���������
	BOOL SetServiceAutoRun(); // ���÷�����������Ϊ�Զ�

	void HideServiceProcess(); // ���ط������
	void ShowServiceProcess(); // ��ʾ�������

	void SetServiceName(const char *serviceName); // ���÷�������
	void SetServiceFilePath(const char *filePath); //�������·��
	void SetThreadId(DWORD dwThreadId); // app thread

	static DWORD WINAPI ServiceThreadFunc(LPVOID lpVoid);

public:
	char m_szServiceName[20]; // ��������
	char m_szServiceFilePath[MAX_PATH];
	BOOL m_bInstall;
	SERVICE_STATUS_HANDLE m_hServiceStatus;
	SERVICE_STATUS m_status;
	DWORD m_dwThreadID;
	HANDLE m_hServiceThread;
	HANDLE m_hServiceEvent;
	HANDLE m_hThreadEvent;
};

extern ServiceManager serviceManger;

#endif // !defined(AFX_SERVICEMANAGER_H__5CAA3541_4D6D_4EEE_979B_2B45E4596128__INCLUDED_)
