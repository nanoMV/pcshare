// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once

#include "MyRegListCtrl.h"
#include "MyRegTreeCtrl.h"

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

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;

	//������
	CLIENTDATA			m_MissionData;			//���ݴ��ͽṹ

	//ͼ��
	BOOL				m_CurSorStatus;
	HCURSOR				m_WaitCur;
	CSplitterWnd		m_WndSplitter;
	CMyRegListCtrl*		pRegListView;
	CMyRegTreeCtrl*		pRegTreeView;
	
	void ShowResponse(UINT m_Response);
	void DisplayButton(CTreeCtrl *pTree,HTREEITEM hti,int nChild);
	BOOL GetMyRegLeftPath(HTREEITEM hItem,char *Path);
	int OnRegRightNewValue(int IsSz);

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

	afx_msg LRESULT OnSetMyCursor(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRegLeftDbClick(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRegLeftRClick(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRegRightRenameOk(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRegRightRClick(WPARAM wParam,LPARAM lParam);
	afx_msg void OnUpdateMyFiles(CCmdUI* pCmdUI);
	afx_msg void OnRegLeftDelete();
	afx_msg void OnRegRightCreateBin();
	afx_msg void OnRegRightCreateStr();
	afx_msg void OnRegRightFlush();
	afx_msg void OnRegRightModify();
	afx_msg void OnUpdateRegRightModify(CCmdUI* pCmdUI);
	afx_msg void OnRegRightRename();
	afx_msg void OnUpdateRegRightRename(CCmdUI* pCmdUI);
	afx_msg void OnRegRightCreateInt();
	afx_msg void OnRegrightRename();
	afx_msg void OnRegRightDelete();
	afx_msg void OnUpdateRegRightDelete(CCmdUI* pCmdUI);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
};


