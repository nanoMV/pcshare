#pragma once


// CMySocketDlg �Ի���

class CMySocketDlg : public CDialog
{
	DECLARE_DYNAMIC(CMySocketDlg)

public:
	CMySocketDlg(char* pTitle, HANDLE hEvnet);   // ��׼���캯��
	virtual ~CMySocketDlg();

	SOCKET	m_soSend;
	SOCKET	m_soRecv;

// �Ի�������
	enum { IDD = IDD_DIALOG_SOCKET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	char	m_Title[256];
	HANDLE	hExitEvent;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	virtual BOOL OnInitDialog();
};
