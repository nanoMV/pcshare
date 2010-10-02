#include "stdafx.h"
#include "zlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void TransFrameThread(LPVOID lPvoid)
{
	//�߳��������
	LPFRAMINFO pInfo = (LPFRAMINFO) lPvoid;
	DWORD dSrcLen = 0;
	DWORD dDesLen = 0;

	char* pBitInfo = new char[65535];
	DWORD m_FrameLen = 
		(1 << 8) * sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);

	//���հ�ͷ
	if(!RecvData(pInfo->soRecv, pBitInfo, m_FrameLen))
	{
		closesocket(pInfo->soSend);
		closesocket(pInfo->soRecv);
		delete [] pBitInfo;
		return;
	}
	SendMessage(pInfo->hWnd , WM_ONEFRAME ,
		(WPARAM) pBitInfo , 1);
	delete [] pBitInfo;
	

	//��ʼ������������
	while(1)
	{
		//���ճ���
		if(!RecvData(pInfo->soRecv , (char*) &dSrcLen , sizeof(DWORD)))
			break;

		//������Ļ����
		if(!RecvData(pInfo->soRecv , pInfo->pSrcData , dSrcLen))
			break;

		//��ѹ����
		dDesLen = 3145728;
		if(uncompress((BYTE*) pInfo->pDesData,
			&dDesLen, (BYTE*) pInfo->pSrcData,dSrcLen))
			continue;
	
		//֪ͨˢ����Ļ
		SendMessage(pInfo->hWnd , WM_ONEFRAME ,(WPARAM) pInfo->pDesData , 0);
	}

	closesocket(pInfo->soSend);
	closesocket(pInfo->soRecv);
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

