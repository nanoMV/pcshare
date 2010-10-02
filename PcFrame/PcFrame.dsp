# Microsoft Developer Studio Project File - Name="PcFrame" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PcFrame - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PcFrame.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PcFrame.mak" CFG="PcFrame - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PcFrame - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "PcFrame - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PcFrame - Win32 Debug"

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
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib zlib.lib Ws2_32.lib /nologo /subsystem:windows /incremental:no /debug /machine:IX86 /out:"e:\pcshare\PcFrame.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib zlib.lib Ws2_32.lib /nologo /subsystem:windows /incremental:no /debug /machine:IX86 /out:"../Bin\PcFrame.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "PcFrame - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /GF /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /GF /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib zlib.lib Ws2_32.lib /nologo /subsystem:windows /machine:IX86 /out:"e:\pcshare\PcFrame.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib zlib.lib Ws2_32.lib /nologo /subsystem:windows /machine:IX86 /out:"..\Bin\PcFrame.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "PcFrame - Win32 Debug"
# Name "PcFrame - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=MyFrameView.cpp
DEP_CPP_MYFRA=\
	".\MyFrameView.h"\
	".\MyMarco.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFrame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFrame - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyFrameWnd.cpp
DEP_CPP_MYFRAM=\
	".\MyFrameView.h"\
	".\MyFrameWnd.h"\
	".\MyMarco.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFrame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFrame - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyGlobalFuc.cpp
DEP_CPP_MYGLO=\
	".\MyMarco.h"\
	".\StdAfx.h"\
	".\zconf.h"\
	".\zlib.h"\
	

!IF  "$(CFG)" == "PcFrame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFrame - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=PcFrame.cpp
DEP_CPP_PCFRA=\
	".\MyFrameView.h"\
	".\MyFrameWnd.h"\
	".\MyMarco.h"\
	".\PcFrame.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFrame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFrame - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=PcFrame.rc
# End Source File
# Begin Source File

SOURCE=StdAfx.cpp
DEP_CPP_STDAF=\
	".\MyMarco.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFrame - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yc"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFrame - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=MyFrameView.h
# End Source File
# Begin Source File

SOURCE=MyFrameWnd.h
# End Source File
# Begin Source File

SOURCE=MyMarco.h
# End Source File
# Begin Source File

SOURCE=PcFrame.h
# End Source File
# Begin Source File

SOURCE=Resource.h
# End Source File
# Begin Source File

SOURCE=StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\icon7.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon7.ico
# End Source File
# Begin Source File

SOURCE=.\res\payment.ico
# End Source File
# Begin Source File

SOURCE=res\PcFrame.ico
# End Source File
# Begin Source File

SOURCE=res\PcFrame.rc2
# End Source File
# Begin Source File

SOURCE=res\PcFrameDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Screen1.ico
# End Source File
# Begin Source File

SOURCE=res\Screen3.ico
# End Source File
# Begin Source File

SOURCE=res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Wait07.cur
# End Source File
# End Group
# Begin Source File

SOURCE=ReadMe.txt
# End Source File
# End Target
# End Project
