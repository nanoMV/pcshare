/*
*	��������,��������
*/

#include "resource.h"

#define CONN_FILE_MULT_SEND		4015				//��Ƶ��ط��͹ܵ�
#define CONN_FILE_MULT_RECV		4016				//��Ƶ��ؽ��չܵ�

#define WM_GETONEFRAME		WM_USER + 401 

//��������

typedef struct _THREADINFO_
{
	HWND	hWnd;
	SOCKET	soRecv;
	SOCKET  soSend;
	char*	pSrcData;
	char*	pDesData;
}THREADINFO,*LPTHREADINFO;

void TransMuiltThread(LPVOID lPvoid);
BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);


