// MyFileTransView.cpp : implementation file
//

#include "stdafx.h"
#include "PcFile.h"
#include "MyFileTransView.h"
#include ".\myfiletransview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileTransView

IMPLEMENT_DYNCREATE(CMyFileTransView, CListView)

CMyFileTransView::CMyFileTransView()
{
	
}

CMyFileTransView::~CMyFileTransView()
{
}


BEGIN_MESSAGE_MAP(CMyFileTransView, CListView)
	//{{AFX_MSG_MAP(CMyFileTransView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(NM_RCLICK, OnNMRclick)
	ON_NOTIFY_REFLECT(LVN_INSERTITEM, OnLvnInsertitem)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFileTransView drawing

void CMyFileTransView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyFileTransView diagnostics

#ifdef _DEBUG
void CMyFileTransView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyFileTransView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFileTransView message handlers

int CMyFileTransView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT);
	GetListCtrl().InsertColumn(0,"�����ļ�����",LVCFMT_LEFT,280);
	GetListCtrl().InsertColumn(1,"    ",LVCFMT_LEFT,30);
	GetListCtrl().InsertColumn(2,"Զ���ļ�����",LVCFMT_LEFT,280);
	GetListCtrl().InsertColumn(3,"�ܳ���",LVCFMT_RIGHT,100);
	GetListCtrl().InsertColumn(4,"����ɳ���(�ֽ�)",LVCFMT_RIGHT,140);
	GetListCtrl().InsertColumn(5,"����״̬",LVCFMT_RIGHT,60);
	GetListCtrl().GetHeaderCtrl()->ModifyStyle(HDS_BUTTONS ,HDS_HOTTRACK);

	return 0;
}

BOOL CMyFileTransView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style ^= LVS_REPORT;		
	return CListView::PreCreateWindow(cs);
}

void CMyFileTransView::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	AfxGetMainWnd()->PostMessage(WM_FILETRANSRCLICK,
		(WPARAM) NULL,(LPARAM) NULL);
	*pResult = 0;
}

int CMyFileTransView::CheckValidFile(void)
{
	int m_Count = GetListCtrl().GetItemCount();
	for(int i = 0; i < m_Count; i++)
	{
		if(GetListCtrl().GetItemText(i, 5) == "���ڴ���")
		{
			//�Ѿ��ڹ���
			return -1;
		}
	}
	for(i = 0; i < m_Count; i++)
	{
		if(GetListCtrl().GetItemText(i, 5) == " ")
		{
			//�ȴ�����
			return i;
		}
	}
	return -1;
}

void CMyFileTransView::OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CMyFileTransView::SetItemFlag(int nItem, BOOL nFlag)
{
	
}

BOOL CMyFileTransView::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	LPMYLISTFILEINFO pInfo = (LPMYLISTFILEINFO) pCopyDataStruct->lpData;
	
	//����ָ������Ŀ
	int nItem = -1;
	int nCount = GetListCtrl().GetItemCount();
	for(int i = 0; i < nCount; i++)
	{
		if(GetListCtrl().GetItemText(i, 0) == pInfo->m_LocalFile)
		{
			nItem = i;
			break;
		}
	}
	if(nItem == -1) return FALSE;

	if(pCopyDataStruct->dwData == 0)
	{
		//�������
		char m_Text[256] = {0};
		sprintf(m_Text, "%d",((DWORD) GetListCtrl().GetItemData(nItem)));
		GetListCtrl().SetItemText(nItem, 4, m_Text);
		GetListCtrl().SetItemText(nItem, 5, "�������");
	}
	else if(pCopyDataStruct->dwData == 1)
	{
		//�Ѿ����䳤��
		char m_Text[256] = {0};
		sprintf(m_Text, "%d", 
			((DWORD) GetListCtrl().GetItemData(nItem)) - pInfo->m_FileLen);
		GetListCtrl().SetItemText(nItem, 4, m_Text);
	}
	else if(pCopyDataStruct->dwData == 2)
	{
		GetListCtrl().SetItemData(nItem, pInfo->m_FileLen + pInfo->m_FilePoint);
	}
	else if(pCopyDataStruct->dwData == 3)
	{
		GetListCtrl().SetItemText(nItem, 5, "����ʧ��");
	}
	else
		return CListView::OnCopyData(pWnd, pCopyDataStruct);
	return TRUE;
}
