# Microsoft Developer Studio Project File - Name="GuiLibDllStatic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GuiLibDllStatic - Win32 Debug Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GuiLibDllStatic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GuiLibDllStatic.mak" CFG="GuiLibDllStatic - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GuiLibDllStatic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GuiLibDllStatic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "GuiLibDllStatic - Win32 Debug Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "GuiLibDllStatic - Win32 Release Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GuiLibDllStatic - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "ReleaseDllStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_GUILIB_STATIC_" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\bin\GuiTk114Statics.lib"

!ELSEIF  "$(CFG)" == "GuiLibDllStatic - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "DebugDllStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_GUILIB_STATIC_" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\bin\GuiTk114Staticds.lib"

!ELSEIF  "$(CFG)" == "GuiLibDllStatic - Win32 Debug Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GuiLibDllStatic___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "GuiLibDllStatic___Win32_Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "DebugDllStaticU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_GUILIB_STATIC_" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "_GUILIB_STATIC_" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\bin\GuiTk114Staticds.lib"
# ADD LIB32 /nologo /out:"..\bin\GuiTk114Staticuds.lib"

!ELSEIF  "$(CFG)" == "GuiLibDllStatic - Win32 Release Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "GuiLibDllStatic___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "GuiLibDllStatic___Win32_Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "ReleaseDllStaticU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_GUILIB_STATIC_" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "_GUILIB_STATIC_" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\bin\GuiTk114Statics.lib"
# ADD LIB32 /nologo /out:"..\bin\GuiTk114Staticus.lib"

!ENDIF 

# Begin Target

# Name "GuiLibDllStatic - Win32 Release"
# Name "GuiLibDllStatic - Win32 Debug"
# Name "GuiLibDllStatic - Win32 Debug Unicode"
# Name "GuiLibDllStatic - Win32 Release Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CoolMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiButtonTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiCapOutBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GuicheckBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiComboBoxExt.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiComboFont.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiDocBarExten.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiDocBarExtenEx.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiDockContext.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiDockToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiDockToolBarEx.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiDocSpecial.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiDrawLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiDropDownEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiFDir.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiFolderFlat.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiGroupBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiImageLinkButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiLabelButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiLib.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiLinkButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiListEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiMDIFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiMDITabbed.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiMDIWindowsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiMiniFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiMiniFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiMiniSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiMiniTool.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiNormalButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiOfficeBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiOutLook.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiOutLookView.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiPanelAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiPowerPointView.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiRadioButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiSliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiSplitterWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiStaticStandar.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiSysTray.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiTabbed.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiTabPowerPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiTabWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiToolBarWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiToolButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiView.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiViewWorkTab.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiVisioFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiWorkPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\GuiWorkTab.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\NewMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Subclass.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CBaseTab.h
# End Source File
# Begin Source File

SOURCE=.\CGuiEditView.h
# End Source File
# Begin Source File

SOURCE=.\CoolMenu.h
# End Source File
# Begin Source File

SOURCE=.\GuiBaseTab.h
# End Source File
# Begin Source File

SOURCE=.\GuiButton.h
# End Source File
# Begin Source File

SOURCE=.\GuiButtonTimer.h
# End Source File
# Begin Source File

SOURCE=.\GuiCapOutBar.h
# End Source File
# Begin Source File

SOURCE=.\GuicheckBox.h
# End Source File
# Begin Source File

SOURCE=.\GuiColors.h
# End Source File
# Begin Source File

SOURCE=.\GuiComboBoxExt.h
# End Source File
# Begin Source File

SOURCE=.\GuiComboFont.h
# End Source File
# Begin Source File

SOURCE=.\GuiContainer.h
# End Source File
# Begin Source File

SOURCE=.\GuiControlBar.h
# End Source File
# Begin Source File

SOURCE=.\GuiDocBarExten.h
# End Source File
# Begin Source File

SOURCE=.\GuiDocBarExtenEx.h
# End Source File
# Begin Source File

SOURCE=.\GuiDockBar.h
# End Source File
# Begin Source File

SOURCE=.\GuiDockContext.h
# End Source File
# Begin Source File

SOURCE=.\GuiDockToolBar.h
# End Source File
# Begin Source File

SOURCE=.\GuiDockToolBarEx.h
# End Source File
# Begin Source File

SOURCE=.\GuiDocSpecial.h
# End Source File
# Begin Source File

SOURCE=.\GuiDrawLayer.h
# End Source File
# Begin Source File

SOURCE=.\GuiDropDownEdit.h
# End Source File
# Begin Source File

SOURCE=.\GuiEdit.h
# End Source File
# Begin Source File

SOURCE=.\GuiFDir.h
# End Source File
# Begin Source File

SOURCE=.\GuiFile.h
# End Source File
# Begin Source File

SOURCE=.\GuiFolder.h
# End Source File
# Begin Source File

SOURCE=.\GuiFolderFlat.h
# End Source File
# Begin Source File

SOURCE=.\GuiFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\GuiGridLayout.h
# End Source File
# Begin Source File

SOURCE=.\GuiGroupBox.h
# End Source File
# Begin Source File

SOURCE=.\GuiHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GuiImageLinkButton.h
# End Source File
# Begin Source File

SOURCE=.\GuiLabelButton.h
# End Source File
# Begin Source File

SOURCE=.\GuiLib.h
# End Source File
# Begin Source File

SOURCE=.\GuiLibRes.h
# End Source File
# Begin Source File

SOURCE=.\GuiLinkButton.h
# End Source File
# Begin Source File

SOURCE=.\GuiListEdit.h
# End Source File
# Begin Source File

SOURCE=.\GuiMDIFrame.h
# End Source File
# Begin Source File

SOURCE=.\GuiMDITabbed.h
# End Source File
# Begin Source File

SOURCE=.\GuiMDIWindowsDlg.h
# End Source File
# Begin Source File

SOURCE=.\GuiMiniFrame.h
# End Source File
# Begin Source File

SOURCE=.\GuiMiniFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\GuiMiniSplitter.h
# End Source File
# Begin Source File

SOURCE=.\GuiMiniTool.h
# End Source File
# Begin Source File

SOURCE=.\GuiNormalButton.h
# End Source File
# Begin Source File

SOURCE=.\GuiOfficeBar.h
# End Source File
# Begin Source File

SOURCE=.\GuiOutLook.h
# End Source File
# Begin Source File

SOURCE=.\GuiOutLookView.h
# End Source File
# Begin Source File

SOURCE=.\GuiPanelAccess.h
# End Source File
# Begin Source File

SOURCE=.\GuiPowerPointView.h
# End Source File
# Begin Source File

SOURCE=.\GuiRadioButton.h
# End Source File
# Begin Source File

SOURCE=.\GuiSliderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GuiSplitter.h
# End Source File
# Begin Source File

SOURCE=.\GuiSplitterWnd.h
# End Source File
# Begin Source File

SOURCE=.\GuiStaticStandar.h
# End Source File
# Begin Source File

SOURCE=.\GuiStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\GuiSysTray.h
# End Source File
# Begin Source File

SOURCE=.\GuiTabbed.h
# End Source File
# Begin Source File

SOURCE=.\GuiTabPowerPoint.h
# End Source File
# Begin Source File

SOURCE=.\GuiTabWnd.h
# End Source File
# Begin Source File

SOURCE=.\GuiToolBarWnd.h
# End Source File
# Begin Source File

SOURCE=.\GuiToolButton.h
# End Source File
# Begin Source File

SOURCE=.\GuiView.h
# End Source File
# Begin Source File

SOURCE=.\GuiViewWorkTab.h
# End Source File
# Begin Source File

SOURCE=.\GuiVisioFolder.h
# End Source File
# Begin Source File

SOURCE=.\GuiWorkPanel.h
# End Source File
# Begin Source File

SOURCE=.\GuiWorkTab.h
# End Source File
# Begin Source File

SOURCE=.\MenuBar.h
# End Source File
# Begin Source File

SOURCE=.\NewMenu.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Subclass.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
