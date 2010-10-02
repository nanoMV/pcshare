; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyFileTransView
LastTemplate=CListView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PcFile.h"
LastPage=0

ClassCount=4
Class1=CPcFileApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=13
Resource1=IDR_MENU_MANA
Class2=CMyFileTransView
Resource2=IDD_ABOUTBOX
Resource3=IDD_DIALOG_FILEINFO
Resource4=IDR_MAINFRAME
Resource5=IDD_DIALOG_FILE_TRANS
Resource6=IDD_DIALOG_DISKINFO
Resource7=IDD_DIALOG_FINDFILE
Resource8=IDR_MENU_FINDFILE
Resource9=IDR_MENU_DIR_RIGHT_EMPTY
Resource10=IDR_MENU_DIR_RIGHT
Resource11=IDD_DIALOG_DIRINFO
Resource12=IDR_MENU_FILE_TRANS
Resource13=IDD_DIALOG_RENAME

[CLS:CPcFileApp]
Type=0
HeaderFile=PcFile.h
ImplementationFile=PcFile.cpp
Filter=N

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
HeaderFile=PcFile.cpp
ImplementationFile=PcFile.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_DIR_FLUSH
Command2=ID_DIR_RIGHT_SELALL
CommandCount=2

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_DIR_PREV
Command2=ID_DIR_FLUSH
Command3=ID_DIR_FIND_FILE
Command4=ID_DIR_CREATE
Command5=ID_DIR_RIGHT_DELETE
Command6=ID_DIR_RIGHT_DOWNLOAD
Command7=ID_DIR_RIGHT_RENAME
CommandCount=7

[CLS:CMyFileTransView]
Type=0
HeaderFile=MyFileTransView.h
ImplementationFile=MyFileTransView.cpp
BaseClass=CListView
Filter=C
LastObject=CMyFileTransView
VirtualFilter=VWC

[MNU:IDR_MENU_DIR_RIGHT]
Type=1
Class=?
Command1=ID_DIR_RIGHT_OPEN
Command2=ID_DIR_RIGHT_DELETE
Command3=ID_DIR_RIGHT_DOWNLOAD
Command4=ID_DIR_RIGHT_RENAME
Command5=ID_DIR_RIGHT_EXEC_SHOW
Command6=ID_DIR_RIGHT_ATTRIB
CommandCount=6

[MNU:IDR_MENU_DIR_RIGHT_EMPTY]
Type=1
Class=?
Command1=ID_DIR_FLUSH
Command2=ID_DIR_RIGHT_SELALL
Command3=ID_DIR_CREATE
Command4=ID_DIR_RIGHT_UPLOAD_EXEC
Command5=ID_DIR_ATTRIB
CommandCount=5

[DLG:IDD_DIALOG_FINDFILE]
Type=1
Class=?
ControlCount=7
Control1=IDC_EDIT_FILE,edit,1350631552
Control2=IDC_EDIT_DIR,edit,1350633600
Control3=IDOK,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_LIST_FILE,SysListView32,1350631429
Control7=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOG_FILE_TRANS]
Type=1
Class=?
ControlCount=7
Control1=IDCANCEL,button,1342242817
Control2=IDC_PROGRESS_FILE,msctls_progress32,1350565888
Control3=ID_FILE_SRC,static,1342308352
Control4=ID_FILE_DES,static,1342308352
Control5=IDC_ANIMATE_FILE,SysAnimate32,1342177286
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_FILEINFO]
Type=1
Class=?
ControlCount=18
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_PATH,edit,1350633600
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC_LEN,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_CREATETIME,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_TYPE,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342181384
Control11=IDC_STATIC,static,1342181384
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC_MODIFYTIME,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC_ACCESSTIME,static,1342308352
Control16=IDC_CHECK1,button,1342242819
Control17=IDC_CHECK2,button,1342242819
Control18=IDC_CHECK3,button,1342242819

[DLG:IDD_DIALOG_DISKINFO]
Type=1
Class=?
ControlCount=13
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_VOLUM,edit,1350633600
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC_USE,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_TYPE,static,1342308352
Control7=IDC_STATIC,static,1342181384
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC_FAT_TYPE,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC_UNUSE,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC_CONTENT,static,1342308352

[DLG:IDD_DIALOG_DIRINFO]
Type=1
Class=?
ControlCount=19
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_PATH,edit,1350633600
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC_LEN,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_CREATETIME,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_FILECOUNT,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC_TYPE,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CHECK_READONLY,button,1342181155
Control13=IDC_CHECK_HIDE,button,1342177315
Control14=IDC_CHECK_ARICH,button,1342177315
Control15=IDC_STATIC,static,1342181384
Control16=IDC_STATIC,static,1342181384
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352

[MNU:IDR_MENU_MANA]
Type=1
Class=?
Command1=ID_EXIT
Command2=ID_DIR_PREV
Command3=ID_DIR_FLUSH
Command4=ID_DIR_FIND_FILE
Command5=ID_DIR_CREATE
Command6=ID_DIR_RIGHT_DELETE
Command7=ID_DIR_RIGHT_DOWNLOAD
Command8=ID_DIR_RIGHT_RENAME
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MENU_FINDFILE]
Type=1
Class=?
Command1=ID_FIND_RIGHT_OPEN
Command2=ID_FIND_DELETE
Command3=ID_FIND_DOWNLOAD
Command4=ID_FIND_EXEC_SHOW
Command5=ID_FIND_ATTRIB
CommandCount=5

[MNU:IDR_MENU_FILE_TRANS]
Type=1
Class=?
Command1=ID_FILE_TRANS_START
Command2=ID_FILE_TRANS_STOP
Command3=ID_FILE_TRANS_DELETE
Command4=ID_FILE_TRANS_DELETE_ALL
CommandCount=4

[DLG:IDD_DIALOG_RENAME]
Type=1
Class=?
ControlCount=3
Control1=IDC_EDIT_VALUE,edit,1350631552
Control2=IDOK,button,1342242816
Control3=IDC_STATIC,static,1342308352

