// MainFrm.h : CMainFrame ��Ľӿ�
//

#include "MyEditView.h"

#pragma once
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	BOOL				m_CurSorStatus;
	HCURSOR				m_WaitCur;
	CMyEditView*		pKeyView;
// ʵ��
public:
	CMainFrame();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
	THREADINFO  m_Info;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnClose();
	afx_msg void OnSave();
	afx_msg void OnEmpty();
	afx_msg void OnUpdateSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEmpty(CCmdUI *pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnCRclick();
	void StartWork(void);
};


