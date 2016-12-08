; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCommSet
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "collect.h"
LastPage=0

ClassCount=21
Class1=CCmdToolBar
Class2=CCollectApp
Class3=CAboutDlg
Class4=CCollectDoc
Class5=CCollectView
Class6=CCommSet
Class7=CDlgUser
Class8=CDWordArrayView
Class9=CGraphicView
Class10=CIntListView
Class11=CMainFrame
Class12=CMapDWordToMyStructView
Class13=CMapStringToStringView
Class14=COperteToolBar
Class15=CPointArrayView
Class16=CRealGraphView
Class17=CSplashWnd
Class18=CStringListView
Class19=CTypedPtrArrayView
Class20=CTypedPtrListView
Class21=CTypedPtrMapView

ResourceCount=16
Resource1=IDD_ABOUTBOX
Resource2=IDD_DIALOG_USER
Resource3=IDD_TYPED_PTR_LIST (English (U.S.))
Resource4=IDD_STRING_LIST
Resource5=IDD_MAP_DWORD_TO_MYSTRUCT (English (U.S.))
Resource6=IDD_POINT_ARRAY (English (U.S.))
Resource7=IDD_TYPED_PTR_ARRAY
Resource8=IDR_MAINFRAME
Resource9=IDD_DWORD_ARRAY
Resource10=IDD_TYPED_PTR_MAP (English (U.S.))
Resource11=IDD_DIALOG_COM
Resource12=IDD_DIALOG_OPERATE_TOOLBAR
Resource13=IDD_MAP_STRING_TO_STRING (English (U.S.))
Resource14=IDD_DIALOG_COMMAND_TOOLBAR
Resource15=IDD_INT_LIST
Resource16=IDR_MAINFRAME (English (U.S.))

[CLS:CCmdToolBar]
Type=0
BaseClass=CDialogBar
HeaderFile=CmdToolBar.h
ImplementationFile=CmdToolBar.cpp

[CLS:CCollectApp]
Type=0
BaseClass=CWinApp
HeaderFile=collect.h
ImplementationFile=collect.cpp
LastObject=CCollectApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=collect.cpp
ImplementationFile=collect.cpp
Filter=D
VirtualFilter=dWC
LastObject=CAboutDlg

[CLS:CCollectDoc]
Type=0
BaseClass=CDocument
HeaderFile=colledoc.h
ImplementationFile=colledoc.cpp

[CLS:CCollectView]
Type=0
BaseClass=CView
HeaderFile=collevw.h
ImplementationFile=collevw.cpp

[CLS:CCommSet]
Type=0
BaseClass=CFormView
HeaderFile=CommSet.h
ImplementationFile=CommSet.cpp
LastObject=IDC_STATIC_FRAME_DISP
Filter=D
VirtualFilter=VWC

[CLS:CDlgUser]
Type=0
BaseClass=CDialog
HeaderFile=DlgUser.h
ImplementationFile=DlgUser.cpp

[CLS:CDWordArrayView]
Type=0
BaseClass=CFormView
HeaderFile=dwarryvw.h
ImplementationFile=dwarryvw.cpp

[CLS:CGraphicView]
Type=0
BaseClass=CView
HeaderFile=GraphicView.h
ImplementationFile=GraphicView.cpp

[CLS:CIntListView]
Type=0
BaseClass=CFormView
HeaderFile=intlstvw.h
ImplementationFile=intlstvw.cpp
LastObject=CIntListView

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:CMapDWordToMyStructView]
Type=0
BaseClass=CFormView
HeaderFile=mapdwvw.h
ImplementationFile=mapdwvw.cpp

[CLS:CMapStringToStringView]
Type=0
BaseClass=CFormView
HeaderFile=mapssvw.h
ImplementationFile=mapssvw.cpp
LastObject=65535

[CLS:COperteToolBar]
Type=0
BaseClass=CDialogBar
HeaderFile=OperteToolBar.h
ImplementationFile=OperteToolBar.cpp

[CLS:CPointArrayView]
Type=0
BaseClass=CFormView
HeaderFile=ptarryvw.h
ImplementationFile=ptarryvw.cpp

[CLS:CRealGraphView]
Type=0
BaseClass=CView
HeaderFile=RealGraphView.h
ImplementationFile=RealGraphView.cpp

[CLS:CSplashWnd]
Type=0
BaseClass=CWnd
HeaderFile=Splash.h
ImplementationFile=Splash.cpp

[CLS:CStringListView]
Type=0
BaseClass=CFormView
HeaderFile=strlstvw.h
ImplementationFile=strlstvw.cpp

[CLS:CTypedPtrArrayView]
Type=0
BaseClass=CFormView
HeaderFile=typaryvw.h
ImplementationFile=typaryvw.cpp

[CLS:CTypedPtrListView]
Type=0
BaseClass=CFormView
HeaderFile=typlstvw.h
ImplementationFile=typlstvw.cpp

[CLS:CTypedPtrMapView]
Type=0
BaseClass=CFormView
HeaderFile=typtrmap.h
ImplementationFile=typtrmap.cpp

[DLG:IDD_DIALOG_COMMAND_TOOLBAR]
Type=1
Class=CCmdToolBar
ControlCount=7
Control1=IDC_COMBO_SCAN_MODEL_SELECT,combobox,1344339971
Control2=IDC_BUTTON_DATA_SAVE,button,1342242816
Control3=IDC_CHECK1,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CHECK_START_SCAN,button,1342246915

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_COM]
Type=1
Class=CCommSet
ControlCount=46
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO_COM_NUM,combobox,1344339971
Control7=IDC_COMBO_COM_DATABIT,combobox,1344339971
Control8=IDC_COMBO_COM_RATE,combobox,1344339971
Control9=IDC_COMBO_COM_STOPBIT,combobox,1344339971
Control10=IDC_STATIC,button,1342177287
Control11=IDC_CHECK_COM_FLOW,button,1342246915
Control12=IDC_BUTTON_COMM_APPLY,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_COMBO_PARITY,combobox,1344339971
Control15=IDC_STATIC,button,1342177287
Control16=IDC_BUTTON_DOWN_FRAME_CMD,button,1476460544
Control17=IDC_STATIC,static,1350696960
Control18=IDC_COMBO_FRAME_CMD,combobox,1344339971
Control19=IDC_STATIC_FRAME_DISP,static,1342308352
Control20=IDC_STATIC_FRAME_TAIL,static,1350696960
Control21=IDC_STATIC,static,1350696960
Control22=IDC_STATIC,static,1350696960
Control23=IDC_STATIC,static,1350696960
Control24=IDC_STATIC,static,1350696960
Control25=IDC_STATIC,static,1350696960
Control26=IDC_STATIC_FRAME_HEAD,static,1350696960
Control27=IDC_EDIT_FRAME_CHK,edit,1350633601
Control28=IDC_STATIC_COMM_STATE_TIP,static,1350696960
Control29=IDC_CHECK_CLCOKWISE,button,1476460547
Control30=IDC_EDIT_CURWAVE_LEN,edit,1484857472
Control31=IDC_STATIC,button,1342177287
Control32=IDC_STATIC,button,1342177287
Control33=IDC_STATIC,button,1342177287
Control34=IDC_EDIT_USEWAVE_LEN,edit,1484857472
Control35=IDC_STATIC,button,1342177287
Control36=IDC_EDIT_ANGLE,edit,1484849280
Control37=IDC_EDIT_START_ANGLE,edit,1484857472
Control38=IDC_STATIC,static,1350696960
Control39=IDC_EDIT_STEP_LEN,edit,1484857472
Control40=IDC_STATIC,static,1350696960
Control41=IDC_EDIT_END_ANGLE,edit,1484857472
Control42=IDC_LIST_TX_DATA,listbox,1352728841
Control43=IDC_LIST_RX_DATA,listbox,1352728841
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352
Control46=IDC_EDIT_RX_DATA,edit,1352728644

[DLG:IDD_DIALOG_USER]
Type=1
Class=CDlgUser
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177294
Control4=IDC_COMBO1,combobox,1344340226
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350639776
Control8=IDC_STATIC,static,1342308364

[DLG:IDD_DWORD_ARRAY]
Type=1
Class=CDWordArrayView
ControlCount=18
Control1=IDC_DWORD,edit,1350631552
Control2=IDC_LIST,listbox,1352728833
Control3=IDC_ADD,button,1342242817
Control4=IDC_UPDATE,button,1342242816
Control5=IDC_REMOVE,button,1342242816
Control6=IDC_REMOVE_ALL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_CHECK1,button,1342242819
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CHECK2,button,1342242819
Control13=IDC_EDIT1,edit,1350631424
Control14=IDC_STATIC,static,1342308352
Control15=IDC_CHECK3,button,1342242819
Control16=IDC_EDIT3,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_CHECK4,button,1342242819

[DLG:IDD_INT_LIST]
Type=1
Class=CIntListView
ControlCount=15
Control1=IDC_ELEMENT,edit,1350631552
Control2=IDC_LIST,listbox,1352728833
Control3=IDC_ADD,button,1342242817
Control4=IDC_INSERT_BEFORE,button,1342242816
Control5=IDC_UPDATE,button,1342242816
Control6=IDC_REMOVE,button,1342242816
Control7=IDC_REMOVE_ALL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308364
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_COMBO1,combobox,1344340226
Control15=IDC_COMBO2,combobox,1344340226

[DLG:IDD_MAP_DWORD_TO_MYSTRUCT]
Type=1
Class=CMapDWordToMyStructView

[DLG:IDD_MAP_STRING_TO_STRING]
Type=1
Class=CMapStringToStringView

[DLG:IDD_DIALOG_OPERATE_TOOLBAR]
Type=1
Class=COperteToolBar
ControlCount=2
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BUTTON1,button,1342242816

[DLG:IDD_POINT_ARRAY]
Type=1
Class=CPointArrayView

[DLG:IDD_STRING_LIST]
Type=1
Class=CStringListView
ControlCount=13
Control1=IDC_ELEMENT,edit,1350631552
Control2=IDC_LIST,listbox,1352728833
Control3=IDC_ADD,button,1342242817
Control4=IDC_INSERT_BEFORE,button,1342242816
Control5=IDC_UPDATE,button,1342242816
Control6=IDC_REMOVE,button,1342242816
Control7=IDC_REMOVE_ALL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CHECK1,button,1342242819
Control11=IDC_CHECK2,button,1342242819
Control12=IDC_STATIC,button,1342177287
Control13=IDC_CHECK3,button,1342242819

[DLG:IDD_TYPED_PTR_ARRAY]
Type=1
Class=CTypedPtrArrayView
ControlCount=42
Control1=IDC_INT,edit,1350631552
Control2=IDC_FLOAT,edit,1350631552
Control3=IDC_STRING,edit,1350631552
Control4=IDC_LIST,listbox,1352728833
Control5=IDC_ADD,button,1342242817
Control6=IDC_UPDATE,button,1342242816
Control7=IDC_REMOVE,button,1342242816
Control8=IDC_REMOVE_ALL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_COMBO_SCAN_MODEL,combobox,1344339971
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT1,edit,1350631552
Control17=IDC_STRING2,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_SPIN1,msctls_updown32,1342177312
Control23=IDC_SPIN2,msctls_updown32,1342177312
Control24=IDC_SPIN3,msctls_updown32,1342177312
Control25=IDC_SPIN4,msctls_updown32,1342177312
Control26=IDC_STATIC,button,1342177287
Control27=IDC_EDIT2,edit,1350631552
Control28=IDC_STATIC,static,1342308352
Control29=IDC_EDIT3,edit,1350631552
Control30=IDC_EDIT4,edit,1350631552
Control31=IDC_STATIC,static,1342308352
Control32=IDC_EDIT5,edit,1350631552
Control33=IDC_SPIN5,msctls_updown32,1342177312
Control34=IDC_SPIN6,msctls_updown32,1342177312
Control35=IDC_SPIN7,msctls_updown32,1342177312
Control36=IDC_SPIN8,msctls_updown32,1342177312
Control37=IDC_COMBO1,combobox,1344339971
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_COMBO2,combobox,1344340226
Control42=IDC_COMBO3,combobox,1344340226

[DLG:IDD_TYPED_PTR_LIST]
Type=1
Class=CTypedPtrListView

[DLG:IDD_TYPED_PTR_MAP]
Type=1
Class=CTypedPtrMapView

[DLG:IDD_TYPED_PTR_LIST (English (U.S.))]
Type=1
Class=?
ControlCount=13
Control1=IDC_INT,edit,1350631552
Control2=IDC_FLOAT,edit,1350631552
Control3=IDC_STRING,edit,1350631552
Control4=IDC_LIST,listbox,1352728833
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_ADD,button,1342242817
Control10=IDC_INSERT_BEFORE,button,1342242816
Control11=IDC_UPDATE,button,1342242816
Control12=IDC_REMOVE,button,1342242816
Control13=IDC_REMOVE_ALL,button,1342242816

[DLG:IDD_POINT_ARRAY (English (U.S.))]
Type=1
Class=?
ControlCount=10
Control1=IDC_X,edit,1350631552
Control2=IDC_Y,edit,1350631552
Control3=IDC_LIST,listbox,1352728833
Control4=IDC_ADD,button,1342242817
Control5=IDC_UPDATE,button,1342242816
Control6=IDC_REMOVE,button,1342242816
Control7=IDC_REMOVE_ALL,button,1342242816
Control8=65535,static,1342308352
Control9=65535,static,1342308352
Control10=65535,static,1342308352

[DLG:IDD_MAP_STRING_TO_STRING (English (U.S.))]
Type=1
Class=?
ControlCount=10
Control1=IDC_KEY,edit,1350631552
Control2=IDC_VALUE,edit,1350631552
Control3=IDC_LIST,listbox,1352728835
Control4=IDC_ADD_OR_UPDATE,button,1342242817
Control5=IDC_FIND,button,1342242816
Control6=IDC_REMOVE,button,1342242816
Control7=IDC_REMOVE_ALL,button,1342242816
Control8=65535,static,1342308352
Control9=65535,static,1342308352
Control10=65535,static,1342308352

[DLG:IDD_TYPED_PTR_MAP (English (U.S.))]
Type=1
Class=?
ControlCount=14
Control1=IDC_KEY,edit,1350631552
Control2=IDC_INT,edit,1350631552
Control3=IDC_FLOAT,edit,1350631552
Control4=IDC_STRING,edit,1350631552
Control5=IDC_LIST,listbox,1352728835
Control6=IDC_ADD_OR_UPDATE,button,1342242817
Control7=IDC_FIND,button,1342242816
Control8=IDC_REMOVE,button,1342242816
Control9=IDC_REMOVE_ALL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_MAP_DWORD_TO_MYSTRUCT (English (U.S.))]
Type=1
Class=?
ControlCount=14
Control1=IDC_KEY,edit,1350631552
Control2=IDC_INT,edit,1350631552
Control3=IDC_FLOAT,edit,1350631552
Control4=IDC_STRING,edit,1350631552
Control5=IDC_LIST,listbox,1352728835
Control6=IDC_ADD_OR_UPDATE,button,1342242817
Control7=IDC_FIND,button,1342242816
Control8=IDC_REMOVE,button,1342242816
Control9=IDC_REMOVE_ALL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_STRINGLIST
Command15=ID_TYPEDLIST
Command16=ID_INTLIST
Command17=ID_DWORDARRAY
Command18=ID_TYPEDPTRARRAY
Command19=ID_POINTARRAY
Command20=ID_MAPSTRINGTOSTRING
Command21=ID_TYPEDPTRMAP
Command22=ID_MAPDWORDTOMYSTRUCT
Command23=ID_COMMSET
Command24=ID_VIEW_TOOLBAR
Command25=ID_VIEW_STATUS_BAR
Command26=ID_VIEW_OPER_BAR
Command27=ID_ON_REAL
Command28=ID_GRAPH_VIEW
Command29=ID_MENU_USER
Command30=ID_APP_ABOUT
Command31=ID_TEST
CommandCount=31

[ACL:IDR_MAINFRAME (English (U.S.))]
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

