// ServiceManager.cpp: implementation of the ServiceManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceManager.h"
#include <stdio.h>
#include <tchar.h>
#include "PcStat.h"

ServiceManager serviceManger;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ServiceManager::ServiceManager()
{
	memset(m_szServiceName, 0, sizeof(m_szServiceName));
	strcpy(m_szServiceName, "Ĭ��(serviceofmine)"); // ��������
	m_bInstall = FALSE;
	m_dwThreadID = 0;

	m_hServiceStatus = NULL;
	m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	m_status.dwCurrentState = SERVICE_STOPPED;
	m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	m_status.dwWin32ExitCode = 0;
	m_status.dwServiceSpecificExitCode = 0;
	m_status.dwCheckPoint = 0;
	m_status.dwWaitHint = 0;
}

ServiceManager::~ServiceManager()
{

}

// ��װ����
BOOL ServiceManager::InstallService()
{
	if (IsInstalled())
	{
		if (IsServiceRunning())
		{
			return TRUE;
		}
		else
		{
			SetServiceAutoRun();
			StartService();
		}
        return TRUE;
	}
	
	//�򿪷�����ƹ�����
    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        return FALSE;
    }
	
	//��������
    SC_HANDLE hService = ::CreateService(
        hSCM, m_szServiceName, m_szServiceName,
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
        m_szServiceFilePath, NULL, NULL, "", NULL, NULL);
	
    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        return FALSE;
    }
	
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
    return TRUE;
}

// ɾ������
BOOL ServiceManager::UninstallService()
{
    if (!IsInstalled())
        return TRUE;
	
    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	
    if (hSCM == NULL)
    {
        return FALSE;
    }
	
    SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);
	
    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        return FALSE;
    }
    SERVICE_STATUS status;
    ::ControlService(hService, SERVICE_CONTROL_STOP, &status);
	
	//ɾ������
    BOOL bDelete = ::DeleteService(hService);
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
	
    if (bDelete)
        return TRUE;
	
    LogEvent("Service could not be deleted");
    return FALSE;
}

void ServiceManager::LogEvent(LPCTSTR pFormat, ...)
{
    char  chMsg[256];
    HANDLE  hEventSource;
    LPTSTR  lpszStrings[1];
    va_list pArg;
	
    va_start(pArg, pFormat);
    _vstprintf(chMsg, pFormat, pArg);
    va_end(pArg);
	
    lpszStrings[0] = chMsg;
	
	hEventSource = RegisterEventSource(NULL, m_szServiceName);
	if (hEventSource != NULL)
	{
		ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR*) &lpszStrings[0], NULL);
		DeregisterEventSource(hEventSource);
	}
}

// �ж��Ƿ�װ�˷���
BOOL ServiceManager::IsInstalled()
{
    BOOL bResult = FALSE;
	
	//�򿪷�����ƹ�����
    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	
    if (hSCM != NULL)
    {
		//�򿪷���
        SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_QUERY_CONFIG);
        if (hService != NULL)
        {
            bResult = TRUE;
            ::CloseServiceHandle(hService);
        }
        ::CloseServiceHandle(hSCM);
    }
    return bResult;
}

BOOL ServiceManager::SetServiceAutoRun()
{
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        return FALSE;
    }
	
    SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_ALL_ACCESS);
    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        return FALSE;
    }

	if (!ChangeServiceConfig(hService, 
		SERVICE_NO_CHANGE, 
		SERVICE_AUTO_START,
		SERVICE_NO_CHANGE,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL))
	{
		DWORD dwError = GetLastError();
	//	CString str;
	//	str.Format("[%d]", dwError);
	//	AfxMessageBox(str);
	}

    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);

    return TRUE;
}

// �������������������ʵ�ֶԷ���Ŀ���
// ���ڷ����������ֹͣ����������ʱ���������д˴�����
void WINAPI ServiceManager::ServiceControl(DWORD dwOpcode)
{
    switch (dwOpcode)
    {
    case SERVICE_CONTROL_STOP:
		SetEvent(m_hThreadEvent); // ֪ͨ�̸߳ý�����
		m_status.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(m_hServiceStatus, &m_status);
        PostThreadMessage(m_dwThreadID, WM_CLOSE, 0, 0);
        break;
    case SERVICE_CONTROL_PAUSE:
		m_status.dwCurrentState = SERVICE_PAUSED;
		SetServiceStatus(m_hServiceStatus, &m_status);
        break;
    case SERVICE_CONTROL_CONTINUE:
		m_status.dwCurrentState = SERVICE_RUNNING;
		SetServiceStatus(m_hServiceStatus, &m_status);
        break;
    case SERVICE_CONTROL_INTERROGATE:
        break;
    case SERVICE_CONTROL_SHUTDOWN:
        break;
    default:
        LogEvent("Bad service request");
		break;
    }
}

// ��������������������п��ƶԷ�����Ƶ�ע��
void WINAPI ServiceManager::ServiceMain()
{
    // Register the control request handler
    m_status.dwCurrentState = SERVICE_START_PENDING;
	m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	
	//ע��������
    m_hServiceStatus = RegisterServiceCtrlHandler(m_szServiceName, (LPHANDLER_FUNCTION)_ServiceControl);
    if (m_hServiceStatus == NULL)
    {
        LogEvent("Handler not installed");
        return;
    }
    SetServiceStatus(m_hServiceStatus, &m_status);
	
    m_status.dwWin32ExitCode = S_OK;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;
	m_status.dwCurrentState = SERVICE_RUNNING;
	SetServiceStatus(m_hServiceStatus, &m_status);
	
	// ���������ź�
	m_hServiceEvent = CreateEvent(0, TRUE, FALSE, "");
	m_hThreadEvent = CreateEvent(0, TRUE, FALSE, "");
	//���������߳�
	m_hServiceThread = CreateThread(NULL, 0, ServiceThreadFunc, this, 0, NULL);
	if (m_hServiceThread == NULL)
		SetEvent(m_hServiceEvent);

	// �յ������߳̽����źž�ֹͣ����(û�յ�֮ǰһֱֹͣ������?)
	WaitForSingleObject(m_hServiceEvent, INFINITE); 

	m_status.dwCurrentState = SERVICE_STOPPED;
	SetServiceStatus(m_hServiceStatus, &m_status);
    LogEvent("Service stopped");
}

void ServiceManager::SetServiceName(const char *serviceName)
{
	if (strcmp(m_szServiceName, serviceName) == 0)
		return;

	strcpy(m_szServiceName, serviceName);
}

void ServiceManager::SetServiceFilePath(const char *filePath)
{
	if (strcmp(m_szServiceFilePath, filePath) == 0)
		return;
	
	strcpy(m_szServiceFilePath, filePath);
}

void WINAPI ServiceManager::_ServiceControl(DWORD dwOpcode)
{
	serviceManger.ServiceControl(dwOpcode);
}

void WINAPI ServiceManager::_ServiceMain()
{
	serviceManger.ServiceMain();
}

void ServiceManager::SetThreadId(DWORD dwThreadId)
{
	m_dwThreadID = dwThreadId;
}

BOOL ServiceManager::StartService()
{
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        return FALSE;
    }
	
    SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);
    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        return FALSE;
    }

	if (!::ControlService(hService, SERVICE_RUNNING, NULL))
	{
		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		return FALSE;
	}

	::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
	return TRUE;
}

BOOL ServiceManager::TerminateService()
{
/*	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        MessageBox(NULL, "Couldn't open service manager", m_szServiceName, MB_OK);
        return FALSE;
    }
	
    SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);
    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, "Couldn't open service", m_szServiceName, MB_OK);
        return FALSE;
    }
	
	if (!::ControlService(hService, SERVICE_STOP, NULL))
	{
		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		return FALSE;
	}

	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);*/
	
	// ���÷����߳��ź�
	SetEvent(m_hThreadEvent);
	return TRUE;
}

// �жϷ����Ƿ�����
BOOL ServiceManager::IsServiceRunning()
{
    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        return FALSE;
    }
	
    SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);
    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        return FALSE;
    }

	if(::QueryServiceStatus(hService, &m_status) == FALSE)
    {
        ::CloseServiceHandle(hService);
        ::CloseServiceHandle(hSCM);
        return FALSE;
    }

	if (m_status.dwCurrentState != SERVICE_RUNNING)
	{
		::CloseServiceHandle(hService);
		::CloseServiceHandle(hSCM);
		return FALSE;
	}
	
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
	
    return TRUE;
}

DWORD WINAPI ServiceManager::ServiceThreadFunc(LPVOID lpVoid)
{
	ServiceManager *sm = (ServiceManager*)lpVoid;
	theApp.GotoWork();
	SetEvent(sm->m_hServiceEvent); // �����ź�(ֱ����ֹ�˷���)
	
	return 0;
}