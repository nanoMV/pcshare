; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyEditView
LastTemplate=CEditView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pckeymon.h"
LastPage=0

ClassCount=2

ResourceCount=3
Resource1=IDR_RIGHT
Class1=CMyEdit
Class2=CMyEditView
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_SAVE
Command2=ID_APP_EXIT
Command3=ID_EMPTY
Command4=ID_EDIT_COPY
Command5=ID_APP_ABOUT
CommandCount=5

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EMPTY
Command3=ID_SAVE
CommandCount=3

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CMyEdit]
Type=0
HeaderFile=MyEdit.h
ImplementationFile=MyEdit.cpp
BaseClass=CEdit
Filter=C
LastObject=CMyEdit
VirtualFilter=WC

[CLS:CMyEditView]
Type=0
HeaderFile=MyEditView.h
ImplementationFile=MyEditView.cpp
BaseClass=CEditView
Filter=C
LastObject=ID_APP_ABOUT
VirtualFilter=VWC

[MNU:IDR_RIGHT]
Type=1
Class=?
Command1=ID_EMPTY
Command2=ID_EDIT_COPY
Command3=ID_SAVE
CommandCount=3

