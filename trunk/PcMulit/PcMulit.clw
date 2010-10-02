; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyFrame
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PcMulit.h"

ClassCount=3
Class1=CPcMulitApp
Class2=CPcMulitDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CMyFrame
Resource2=IDD_PCMULIT_DIALOG

[CLS:CPcMulitApp]
Type=0
HeaderFile=PcMulit.h
ImplementationFile=PcMulit.cpp
Filter=N

[CLS:CPcMulitDlg]
Type=0
HeaderFile=PcMulitDlg.h
ImplementationFile=PcMulitDlg.cpp
Filter=T
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_SAVE_IMG



[DLG:IDD_PCMULIT_DIALOG]
Type=1
Class=CPcMulitDlg
ControlCount=2
Control1=IDC_STATIC_FRAME,static,1342312704
Control2=IDC_STATIC,static,1342308352

[CLS:CMyFrame]
Type=0
HeaderFile=MyFrame.h
ImplementationFile=MyFrame.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CMyFrame

