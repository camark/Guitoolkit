; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGuiPanelWnd
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "guilib.h"
LastPage=0

ClassCount=27
Class1=CGuiEditView
Class2=CGuiButtonDoc
Class3=GuiCapOutBar
Class4=CGuiCheckBox
Class5=CGuiComboBoxExt
Class6=CGuiComboFont
Class7=CGuiContainer
Class8=CGuiDockBar
Class9=CGuiDockToolBar
Class10=CGuiDockToolBarEx
Class11=CGuiEdit
Class12=CGuiGroupBox
Class13=CGuiHeaderCtrl
Class14=CGuiLinkButton
Class15=CGuiMDIFrame
Class16=CGuiMDIWindowsDlg
Class17=CGuiMiniFrameWnd
Class18=CGuiMiniSplitter
Class19=CGuiMiniTool
Class20=CGuiOutLook
Class21=CGuiRadioButton
Class22=CGuiSliderCtrl
Class23=CGuiStaticStandar
Class24=CGuiTabWnd
Class25=CGuiView
Class26=CMenuBar

ResourceCount=3
Resource1=IDR_GUI_DEFAULT
Resource2=IDD_GUI_WINDOW_MANAGE
Class27=CGuiPanelWnd
Resource3=IDR_GUI_MENUSYS

[CLS:CGuiEditView]
Type=0
BaseClass=CRichEditView
HeaderFile=CGuiEditView.h
ImplementationFile=CGuiEditView.cpp

[CLS:CGuiButtonDoc]
Type=0
BaseClass=CWnd
HeaderFile=GuiButtonDoc.h
ImplementationFile=GuiButtonDoc.cpp
Filter=W
VirtualFilter=WC
LastObject=CGuiButtonDoc

[CLS:GuiCapOutBar]
Type=0
BaseClass=CControlBar
HeaderFile=GuiCapOutBar.h
ImplementationFile=GuiCapOutBar.cpp

[CLS:CGuiCheckBox]
Type=0
BaseClass=CButton
HeaderFile=GuicheckBox.h
ImplementationFile=GuicheckBox.cpp

[CLS:CGuiComboBoxExt]
Type=0
BaseClass=CComboBox
HeaderFile=GuiComboBoxExt.h
ImplementationFile=GuiComboBoxExt.cpp

[CLS:CGuiComboFont]
Type=0
BaseClass=CComboBox
HeaderFile=GuiComboFont.h
ImplementationFile=GuiComboFont.cpp

[CLS:CGuiContainer]
Type=0
BaseClass=CWnd
HeaderFile=GuiContainer.h
ImplementationFile=GuiContainer.cpp

[CLS:CGuiDockBar]
Type=0
BaseClass=CDockBar
HeaderFile=GuiDockBar.h
ImplementationFile=GuiDockBar.cpp

[CLS:CGuiDockToolBar]
Type=0
BaseClass=CControlBar
HeaderFile=GuiDockToolBar.h
ImplementationFile=GuiDockToolBar.cpp

[CLS:CGuiDockToolBarEx]
Type=0
BaseClass=CControlBar
HeaderFile=GuiDockToolBarEx.h
ImplementationFile=GuiDockToolBarEx.cpp

[CLS:CGuiEdit]
Type=0
BaseClass=CEdit
HeaderFile=GuiEdit.h
ImplementationFile=GuiEdit.cpp

[CLS:CGuiGroupBox]
Type=0
BaseClass=CButton
HeaderFile=GuiGroupBox.h
ImplementationFile=GuiGroupBox.cpp

[CLS:CGuiHeaderCtrl]
Type=0
BaseClass=CHeaderCtrl
HeaderFile=GuiHeaderCtrl.h
ImplementationFile=GuiHeaderCtrl.cpp

[CLS:CGuiLinkButton]
Type=0
BaseClass=CButton
HeaderFile=GuiLinkButton.h
ImplementationFile=GuiLinkButton.cpp

[CLS:CGuiMDIFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=GuiMDIFrame.h
ImplementationFile=GuiMDIFrame.cpp

[CLS:CGuiMDIWindowsDlg]
Type=0
BaseClass=CDialog
HeaderFile=GuiMDIWindowsDlg.h
ImplementationFile=GuiMDIWindowsDlg.cpp

[CLS:CGuiMiniFrameWnd]
Type=0
BaseClass=CMiniFrameWnd
HeaderFile=GuiMiniFrameWnd.h
ImplementationFile=GuiMiniFrameWnd.cpp

[CLS:CGuiMiniSplitter]
Type=0
BaseClass=CWnd
HeaderFile=GuiMiniSplitter.h
ImplementationFile=GuiMiniSplitter.cpp

[CLS:CGuiMiniTool]
Type=0
BaseClass=CStatic
HeaderFile=GuiMiniTool.h
ImplementationFile=GuiMiniTool.cpp

[CLS:CGuiOutLook]
Type=0
BaseClass=CWnd
HeaderFile=GuiOutLook.h
ImplementationFile=GuiOutLook.cpp

[CLS:CGuiRadioButton]
Type=0
BaseClass=CButton
HeaderFile=GuiRadioButton.h
ImplementationFile=GuiRadioButton.cpp

[CLS:CGuiSliderCtrl]
Type=0
BaseClass=CSliderCtrl
HeaderFile=GuiSliderCtrl.h
ImplementationFile=GuiSliderCtrl.cpp

[CLS:CGuiStaticStandar]
Type=0
BaseClass=CStatic
HeaderFile=GuiStaticStandar.h
ImplementationFile=GuiStaticStandar.cpp

[CLS:CGuiTabWnd]
Type=0
BaseClass=CWnd
HeaderFile=GuiTabWnd.h
ImplementationFile=GuiTabWnd.cpp

[CLS:CGuiView]
Type=0
BaseClass=CView
HeaderFile=GuiView.h
ImplementationFile=GuiView.cpp

[CLS:CMenuBar]
Type=0
BaseClass=CControlBar
HeaderFile=MenuBar.h
ImplementationFile=MenuBar.cpp

[DLG:IDD_GUI_WINDOW_MANAGE]
Type=1
Class=CGuiMDIWindowsDlg
ControlCount=11
Control1=IDC_GUI_WINDOWLIST_LIST,listbox,1352731091
Control2=IDC_GUI_WINDOWLIST_ACTIVATE,button,1342242817
Control3=IDOK,button,1342242816
Control4=IDC_GUI_WINDOWLIST_SAVE,button,1342242816
Control5=IDC_GUI_WINDOWLIST_CLOSE,button,1342242816
Control6=IDC_GUI_WINDOWLIST_CASCADE,button,1342242816
Control7=IDC_GUI_WINDOWLIST_TILEHORZ,button,1342242816
Control8=IDC_GUI_WINDOWLIST_TILEVERT,button,1342242816
Control9=IDC_GUI_WINDOWLIST_MINIMIZE,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_GUI_WINDOWLIST_HELP,button,1342242816

[MNU:IDR_GUI_MENUSYS]
Type=1
Class=?
CommandCount=0

[TB:IDR_GUI_DEFAULT]
Type=1
Class=?
Command1=ID_GUI_FILE_CLOSE
Command2=ID_GUI_FILE_CLOSE
Command3=ID_GUI_WINDOW_CLOSE_ALL
Command4=ID_GUI_FILE_SAVE
Command5=ID_GUI_WINDOW_CLOSE_ALL
Command6=ID_GUI_WINDOW_NEW
Command7=ID_GUI_WINDOW_NEXT
Command8=ID_GUI_WINDOW_PREVIOUS
Command9=ID_GUI_WINDOW_CASCADE
Command10=ID_GUI_WINDOW_TILE_HORZ
Command11=ID_GUI_WINDOW_TILE_VERT
CommandCount=11

[CLS:CGuiPanelWnd]
Type=0
HeaderFile=GuiPanelWnd.h
ImplementationFile=GuiPanelWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CGuiPanelWnd

