// MyRenameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PcRegedit.h"
#include "MyRenameDlg.h"


// CMyRenameDlg �Ի���

IMPLEMENT_DYNAMIC(CMyRenameDlg, CDialog)
CMyRenameDlg::CMyRenameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyRenameDlg::IDD, pParent)
	, m_RegName(_T(""))
{
}

CMyRenameDlg::~CMyRenameDlg()
{
}

void CMyRenameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, 1000, m_RegName);
	DDV_MaxChars(pDX, m_RegName, 250);
}

BEGIN_MESSAGE_MAP(CMyRenameDlg, CDialog)
END_MESSAGE_MAP()


// CMyRenameDlg ��Ϣ�������
