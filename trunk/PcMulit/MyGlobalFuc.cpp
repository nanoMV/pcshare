#include "stdafx.h"
#include "zlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void TransMuiltThread(LPVOID lPvoid)
{
	THREADINFO m_Info = {0};
	memcpy(&m_Info, lPvoid, sizeof(THREADINFO));

	//���հ�ͷ��Ϣ
	BITMAPINFO m_BmpInfo;
	if(!RecvData(m_Info.soRecv, (char*) &m_BmpInfo,
		sizeof(BITMAPINFO)))
	{
		closesocket(m_Info.soRecv);
		closesocket(m_Info.soSend);
	}

	//ͼ����Ϣ
	SendMessage(m_Info.hWnd, WM_GETONEFRAME,
		(WPARAM) &m_BmpInfo, TRUE);

	DWORD dSrcLen = 0;
	DWORD dDesLen = 0;
	while(1)
	{
		//���ճ���
		if(!RecvData(m_Info.soRecv , (char*) &dSrcLen , sizeof(DWORD)))
			break;

		//������Ļ����
		if(!RecvData(m_Info.soRecv , m_Info.pSrcData , dSrcLen))
			break;

		//��ѹ����
		dDesLen = 101950;
		if(uncompress((BYTE*) m_Info.pDesData,
			&dDesLen, (BYTE*) m_Info.pSrcData,dSrcLen))
			continue;
	
		//֪ͨˢ����Ļ
		SendMessage(m_Info.hWnd , WM_GETONEFRAME , 0, 0);
	}
	closesocket(m_Info.soRecv);
}

//��������
BOOL SendData(SOCKET s, char *data, int len)
{
	char * p = data;
	int i = 0;
	int k = len;
	int ret = 0;

	if(len <= 0) return TRUE;
	while(1)
	{
		ret = send(s,p,k,0);
		if(ret == 0 || ret == SOCKET_ERROR)
		{
			TRACE("SendData OUT,%d\n",WSAGetLastError());
			return FALSE;
		}
		i += ret;
		p += ret;
		k -= ret;
		if(i >= len) break;
	}
	return TRUE;
}

//��������
BOOL RecvData(SOCKET s, char *data, int len)
{
	char * p = data;
	int i = 0;
	int k = len;
	int ret = 0;

	if(len <= 0) return TRUE;
	while(1)
	{
		ret = recv(s,p,k,0);
		if(ret == 0 || ret == SOCKET_ERROR)
		{
			TRACE("RecvData OUT,%d\n",WSAGetLastError());
			return FALSE;
		}
		i += ret;
		p += ret;
		k -= ret;
		if(i >= len) return TRUE;
	}
	return TRUE;
}

