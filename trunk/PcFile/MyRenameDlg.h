#pragma once


// CMyRenameDlg �Ի���

class CMyRenameDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyRenameDlg)

public:
	CMyRenameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyRenameDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_RENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_FileName;
};
