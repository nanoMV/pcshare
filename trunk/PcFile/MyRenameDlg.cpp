// MyRenameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PcFile.h"
#include "MyRenameDlg.h"


// CMyRenameDlg �Ի���

IMPLEMENT_DYNAMIC(CMyRenameDlg, CDialog)
CMyRenameDlg::CMyRenameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyRenameDlg::IDD, pParent)
	, m_FileName(_T(""))
{
}

CMyRenameDlg::~CMyRenameDlg()
{
}

void CMyRenameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_FileName);
	DDV_MaxChars(pDX, m_FileName, 250);
}


BEGIN_MESSAGE_MAP(CMyRenameDlg, CDialog)
END_MESSAGE_MAP()


// CMyRenameDlg ��Ϣ�������
