/*
*	��������,��������
*/

#include "resource.h"

#define WM_ONEFRAME				WM_USER + 915		//һ֡ͼ��

#define CONN_FILE_FRAM_SEND		4003				//��Ļ��ط��͹ܵ�
#define CONN_FILE_FRAM_RECV		4004				//��Ļ��ؽ��չܵ�

#define CMD_FRAME_MOUSE_STATE	1					//���״̬
#define CMD_FRAME_KEY_STATE		2					//����״̬
#define CMD_FRAME_KEY_ALL		3					//����CTRL+ALT+DEL

//��������

typedef struct _FRAMINFO_
{
	HWND	hWnd;
	SOCKET	soRecv;
	SOCKET	soSend;
	char*	pDesData;
	char*	pSrcData;
}FRAMINFO,*LPFRAMINFO;

typedef struct _MOUSEINFO_
{
	WORD x;
	WORD y;
	WORD state;
	char ch;
	char cmd;
}MOUSEINFO,*LPMOUSEINFO;

void TransFrameThread(LPVOID lPvoid);
BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);


