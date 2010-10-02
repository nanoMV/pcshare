// PcRegedit.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PcRegedit.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPcRegeditApp

BEGIN_MESSAGE_MAP(CPcRegeditApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()


// CPcRegeditApp ����

CPcRegeditApp::CPcRegeditApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPcRegeditApp ����

CPcRegeditApp theApp;

// CPcRegeditApp ��ʼ��

BOOL CPcRegeditApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	//��ʼ��SOCKET����
	WSADATA		data;
	if(WSAStartup(MAKEWORD(2, 2), &data))
	{
		return FALSE;
	}
	if (LOBYTE(data.wVersion) !=2 || 
		HIBYTE(data.wVersion) != 2)
	{
		WSACleanup();
		return FALSE;
	}

	if(strlen(m_lpCmdLine) == 0) return FALSE;

	//ȡ��ʼ������
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME);
	
	//����
	char m_Title[256] = {0};
	strcpy(m_Title, m_lpCmdLine);
	char m_Id[256] = {0};
	char* pFind = strrchr(m_Title,':');
	if(pFind != NULL)
	{
		//ȡID
		memcpy(m_Id, pFind + 1,16);
		*(pFind + 9) = 0;
	}
	pFrame->SetWindowText(m_Title);
	
	//�鿴�Ƿ����ļ�����
	strcat(m_Id,".Ini");
	char m_FileName[256] = {0};
	GetModuleFileName(NULL,m_FileName,200);
	pFind = strrchr(m_FileName,'\\');
	if(pFind != NULL) *pFind = 0;
	SetCurrentDirectory(m_FileName);
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();
	pFrame->BringWindowToTop();
	return TRUE;
}


// CPcRegeditApp ��Ϣ�������



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CPcRegeditApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CPcRegeditApp ��Ϣ�������

