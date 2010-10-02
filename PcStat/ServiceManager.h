// ServiceManager.h: interface for the ServiceManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICEMANAGER_H__5CAA3541_4D6D_4EEE_979B_2B45E4596128__INCLUDED_)
#define AFX_SERVICEMANAGER_H__5CAA3541_4D6D_4EEE_979B_2B45E4596128__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <WinSvc.h>

// Windows系统服务管理类
class ServiceManager  
{
public:
	ServiceManager();
	virtual ~ServiceManager();

	BOOL IsInstalled();  // 判断是否安装服务
	BOOL InstallService(); // 安装服务
	BOOL UninstallService(); // 删除服务
	void LogEvent(LPCTSTR pszFormat, ...); // 系统日志记录
	void WINAPI ServiceMain(); // 服务主函数，这在里进行控制对服务控制的注册
	void WINAPI ServiceControl(DWORD dwOpcode);
	static void WINAPI _ServiceMain();  // 直接调用ServiceMain
	static void WINAPI _ServiceControl(DWORD dwOpcode); // 直接调用ServiceControl

	BOOL StartService(); // 启动服务
	BOOL TerminateService(); // 终止服务
	BOOL IsServiceRunning(); // 判断服务是否正在运行
	BOOL SetServiceAutoRun(); // 设置服务启动类型为自动

	void HideServiceProcess(); // 隐藏服务进程
	void ShowServiceProcess(); // 显示服务进程

	void SetServiceName(const char *serviceName); // 设置服务名称
	void SetServiceFilePath(const char *filePath); //服务程序路径
	void SetThreadId(DWORD dwThreadId); // app thread

	static DWORD WINAPI ServiceThreadFunc(LPVOID lpVoid);

public:
	char m_szServiceName[20]; // 服务名称
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
