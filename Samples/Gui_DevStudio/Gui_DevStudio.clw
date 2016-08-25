; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=SplashView
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gui_devstudio.h"
LastPage=0

ClassCount=10
Class1=CChildFrame
Class2=DialUndo
Class3=CGui_DevStudioApp
Class4=CAboutDlg
Class5=CGui_DevStudioDoc
Class6=CGui_DevStudioView
Class7=CMainFrame
Class8=CMyBar
Class9=COutputList

ResourceCount=11
Resource1=IDR_NEWITEM (Spanish (Castilian) (unknown sub-lang: 0x9))
Resource2=IDR_TOOLBARS (Spanish (Castilian) (unknown sub-lang: 0x9))
Resource3=IDR_TOOLCOMBOS
Resource4=IDD_ABOUTBOX
Resource5=IDR_MENUNEW
Resource6=IDR_MENUTABS
Resource7=IDR_MENUNEWITEM (Spanish (Castilian) (unknown sub-lang: 0x9))
Resource8=IDR_MENUTOOLBARS (Spanish (Castilian) (unknown sub-lang: 0x9))
Resource9=IDR_GUI_DETYPE
Resource10=IDR_MAINFRAME
Class10=SplashView
Resource11=IDD_DIALOG1

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:DialUndo]
Type=0
BaseClass=CDialog
HeaderFile=DialUndo.h
ImplementationFile=DialUndo.cpp

[CLS:CGui_DevStudioApp]
Type=0
BaseClass=CWinApp
HeaderFile=Gui_DevStudio.h
ImplementationFile=Gui_DevStudio.cpp
Filter=N
VirtualFilter=AC
LastObject=ID_FILE_NEW

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Gui_DevStudio.cpp
ImplementationFile=Gui_DevStudio.cpp
LastObject=CAboutDlg

[CLS:CGui_DevStudioDoc]
Type=0
BaseClass=CDocument
HeaderFile=Gui_DevStudioDoc.h
ImplementationFile=Gui_DevStudioDoc.cpp

[CLS:CGui_DevStudioView]
Type=0
BaseClass=CEditView
HeaderFile=Gui_DevStudioView.h
ImplementationFile=Gui_DevStudioView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CGuiMDIFrame
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CMyBar]
Type=0
HeaderFile=OutputWindow.h
ImplementationFile=OutputWindow.cpp

[CLS:COutputList]
Type=0
BaseClass=CListBox
HeaderFile=OutputWindow.h
ImplementationFile=OutputWindow.cpp

[DLG:IDD_DIAL]
Type=1
Class=DialUndo

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_NEW_ITEM
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_FILE_PRINT
Command9=ID_UNDO
Command10=ID_REDO
Command11=ID_NAVIBACK
Command12=ID_START
Command13=ID_FINDINFILES
Command14=ID_SOLUTION
Command15=ID_CLASSVIEW
CommandCount=15

[TB:IDR_TOOLCOMBOS]
Type=1
Class=?
Command1=ID_COMBO1
Command2=ID_COMBO3
Command3=ID_COMBO2
CommandCount=3

[TB:IDR_NEWITEM (Spanish (Castilian) (unknown sub-lang: 0x9))]
Type=1
Class=?
Command1=ID_NEXT_PANE
Command2=ID_EXISTITEM
Command3=ID_ADDCLASS
CommandCount=3

[TB:IDR_TOOLBARS (Spanish (Castilian) (unknown sub-lang: 0x9))]
Type=1
Class=?
Command1=ID_WORKSPACE
Command2=ID_HELP
Command3=ID_OUTPUTNORMAL
Command4=ID_OUTPUT
Command5=ID_SERVER
CommandCount=5

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_GUI_DETYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_VIEW_LOOK_XP
Command18=ID_VIEW_LOOK_2003
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

[MNU:IDR_MENUNEW]
Type=1
Class=?
Command1=ID_FILE_NEW
CommandCount=1

[MNU:IDR_MENUTABS]
Type=1
Class=?
Command1=ID_FILE_SAVE
Command2=ID_FILE_SAVE_AS
Command3=ID_FILE_CLOSE
CommandCount=3

[MNU:IDR_MENUNEWITEM (Spanish (Castilian) (unknown sub-lang: 0x9))]
Type=1
Class=?
CommandCount=0

[MNU:IDR_MENUTOOLBARS (Spanish (Castilian) (unknown sub-lang: 0x9))]
Type=1
Class=?
CommandCount=0

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=2
Control1=IDC_LIST1,listbox,1352728835
Control2=IDC_STATIC,static,1342312448

[CLS:SplashView]
Type=0
HeaderFile=SplashView.h
ImplementationFile=SplashView.cpp
BaseClass=CView
Filter=C

