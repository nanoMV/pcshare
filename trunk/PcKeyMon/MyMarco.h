/*
*	��������,��������
*/

#include "resource.h"

#define WM_GETSTR				WM_USER + 401		//�õ��ִ�
#define WM_CRCLICK				WM_USER + 402		//��ʾ�˵�

#define CONN_FILE_KEYM_SEND		4013				//���̼�ط��͹ܵ�
#define CONN_FILE_KEYM_RECV		4014				//���̼�ؽ��չܵ�

//��������

typedef struct _THREADINFO_
{
	HWND	hWnd;
	SOCKET	soRecv;
	SOCKET  soSend;
}THREADINFO,*LPTHREADINFO;

void TransCharThread(LPVOID lPvoid);
BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);


