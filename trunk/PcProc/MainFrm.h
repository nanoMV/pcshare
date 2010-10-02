// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once

#include "MyProcessListView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;

	//������
	CLIENTDATA			m_MissionData;			//���ݴ��ͽṹ

	//ͼ��
	BOOL				m_CurSorStatus;
	HCURSOR				m_WaitCur;

	CMyProcessListView* pProcessListView;

	void ShowResponse(UINT m_Response);

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

	afx_msg void OnProcessFlush();
	afx_msg void OnUpdateProcessFlush(CCmdUI* pCmdUI);
	afx_msg void OnProcessKill();
	afx_msg void OnUpdateProcessKill(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMyFiles(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnUserRClickProcess(WPARAM wParam,LPARAM lParam);

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnClose();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnSetMyCursor(WPARAM wParam,LPARAM lParam);
};


