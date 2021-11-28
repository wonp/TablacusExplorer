#pragma once

#include "common.h"

TEmethod methodTE[] = {
	{ 1001, "Data" },
	{ 1002, "hwnd" },
	{ 1004, "About" },
	{ TE_METHOD + 1005, "Ctrl" },
	{ TE_METHOD + 1006, "Ctrls" },
	{ TE_METHOD + 1008, "ClearEvents" },
	{ TE_METHOD + 1009, "Reload" },
	{ TE_METHOD + 1010, "CreateObject" },
	{ TE_METHOD + 1020, "GetObject" },
	{ TE_METHOD + 1025, "AddEvent" },
	{ TE_METHOD + 1026, "RemoveEvent" },
	{ 1030, "WindowsAPI" },
	{ 1031, "WindowsAPI0" },
	{ 1131, "CommonDialog" },
	{ 1132, "WICBitmap" },
	{ 1132, "GdiplusBitmap" },//Deprecated
	{ 1136, "Arguments" },
	{ 1137, "ProgressDialog" },
	{ 1138, "DateTimeFormat" },
	{ 1139, "HiddenFilter" },
//	{ 1140, "Background" },//Deprecated
//	{ 1150, "ThumbnailProvider" },//Deprecated
	{ 1160, "DragIcon" },
	{ 1180, "ExplorerBrowserFilter" },
	{ TE_METHOD + 1133, "FolderItems" },
	{ TE_METHOD + 1134, "Object" },
	{ TE_METHOD + 1135, "Array" },
//	{ TE_METHOD + 1136, "Collection" },//Deprecated
	{ TE_METHOD + 1050, "CreateCtrl" },
	{ TE_METHOD + 1040, "CtrlFromPoint" },
	{ TE_METHOD + 1060, "MainMenu" },
	{ TE_METHOD + 1070, "CtrlFromWindow" },
	{ TE_METHOD + 1080, "LockUpdate" },
	{ TE_METHOD + 1090, "UnlockUpdate" },
	{ TE_METHOD + 1091, "ArrangeCB" },
	{ TE_METHOD + 1100, "HookDragDrop" },//Deprecated
#ifdef _USE_TESTOBJECT
	{ 1200, "TestObj" },
#endif
	{ TE_OFFSET + TE_Type   , "Type" },
	{ TE_OFFSET + TE_Left   , "offsetLeft" },
	{ TE_OFFSET + TE_Top    , "offsetTop" },
	{ TE_OFFSET + TE_Right  , "offsetRight" },
	{ TE_OFFSET + TE_Bottom , "offsetBottom" },
	{ TE_OFFSET + TE_Tab, "Tab" },
	{ TE_OFFSET + TE_CmdShow, "CmdShow" },
	{ TE_OFFSET + TE_Layout, "Layout" },
	{ TE_OFFSET + TE_NetworkTimeout, "NetworkTimeout" },
	{ TE_OFFSET + TE_SizeFormat, "SizeFormat" },
	{ TE_OFFSET + TE_Version, "Version" },
	{ TE_OFFSET + TE_UseHiddenFilter, "UseHiddenFilter" },
	{ TE_OFFSET + TE_ColumnEmphasis, "ColumnEmphasis" },
	{ TE_OFFSET + TE_ViewOrder, "ViewOrder" },
	{ TE_OFFSET + TE_LibraryFilter, "LibraryFilter" },
	{ TE_OFFSET + TE_AutoArrange, "AutoArrange" },
	{ TE_OFFSET + TE_ShowInternet, "ShowInternet" },

	{ START_OnFunc + TE_Labels, "Labels" },
	{ START_OnFunc + TE_ColumnsReplace, "ColumnsReplace" },
	{ START_OnFunc + TE_OnBeforeNavigate, "OnBeforeNavigate" },
	{ START_OnFunc + TE_OnViewCreated, "OnViewCreated" },
	{ START_OnFunc + TE_OnKeyMessage, "OnKeyMessage" },
	{ START_OnFunc + TE_OnMouseMessage, "OnMouseMessage" },
	{ START_OnFunc + TE_OnCreate, "OnCreate" },
	{ START_OnFunc + TE_OnDefaultCommand, "OnDefaultCommand" },
	{ START_OnFunc + TE_OnItemClick, "OnItemClick" },
	{ START_OnFunc + TE_OnGetPaneState, "OnGetPaneState" },
	{ START_OnFunc + TE_OnMenuMessage, "OnMenuMessage" },
	{ START_OnFunc + TE_OnSystemMessage, "OnSystemMessage" },
	{ START_OnFunc + TE_OnShowContextMenu, "OnShowContextMenu" },
	{ START_OnFunc + TE_OnSelectionChanged, "OnSelectionChanged" },
	{ START_OnFunc + TE_OnClose, "OnClose" },
	{ START_OnFunc + TE_OnDragEnter, "OnDragEnter" },
	{ START_OnFunc + TE_OnDragOver, "OnDragOver" },
	{ START_OnFunc + TE_OnDrop, "OnDrop" },
	{ START_OnFunc + TE_OnDragLeave, "OnDragLeave" },
	{ START_OnFunc + TE_OnAppMessage, "OnAppMessage" },
	{ START_OnFunc + TE_OnStatusText, "OnStatusText" },
	{ START_OnFunc + TE_OnToolTip, "OnToolTip" },
	{ START_OnFunc + TE_OnNewWindow, "OnNewWindow" },
	{ START_OnFunc + TE_OnWindowRegistered, "OnWindowRegistered" },
	{ START_OnFunc + TE_OnSelectionChanging, "OnSelectionChanging" },
	{ START_OnFunc + TE_OnClipboardText, "OnClipboardText" },
	{ START_OnFunc + TE_OnCommand, "OnCommand" },
	{ START_OnFunc + TE_OnInvokeCommand, "OnInvokeCommand" },
	{ START_OnFunc + TE_OnArrange, "OnArrange" },
	{ START_OnFunc + TE_OnHitTest, "OnHitTest" },
	{ START_OnFunc + TE_OnVisibleChanged, "OnVisibleChanged" },
	{ START_OnFunc + TE_OnTranslatePath, "OnTranslatePath" },
	{ START_OnFunc + TE_OnNavigateComplete, "OnNavigateComplete" },
	{ START_OnFunc + TE_OnILGetParent, "OnILGetParent" },
	{ START_OnFunc + TE_OnViewModeChanged, "OnViewModeChanged" },
	{ START_OnFunc + TE_OnColumnsChanged, "OnColumnsChanged" },
	{ START_OnFunc + TE_OnItemPrePaint, "OnItemPrePaint" },
	{ START_OnFunc + TE_OnColumnClick, "OnColumnClick" },
	{ START_OnFunc + TE_OnBeginDrag, "OnBeginDrag" },
	{ START_OnFunc + TE_OnBeforeGetData, "OnBeforeGetData" },
	{ START_OnFunc + TE_OnIconSizeChanged, "OnIconSizeChanged" },
	{ START_OnFunc + TE_OnFilterChanged, "OnFilterChanged" },
	{ START_OnFunc + TE_OnBeginLabelEdit, "OnBeginLabelEdit" },
	{ START_OnFunc + TE_OnEndLabelEdit, "OnEndLabelEdit" },
	{ START_OnFunc + TE_OnReplacePath, "OnReplacePath" },
	{ START_OnFunc + TE_OnBeginNavigate, "OnBeginNavigate" },
	{ START_OnFunc + TE_OnSort, "OnSort" },
	{ START_OnFunc + TE_OnGetAlt, "OnGetAlt" },
	{ START_OnFunc + TE_OnEndThread, "OnEndThread" },
	{ START_OnFunc + TE_OnItemPostPaint, "OnItemPostPaint" },
	{ START_OnFunc + TE_OnHandleIcon, "OnHandleIcon" },
	{ START_OnFunc + TE_OnSorting, "OnSorting" },
	{ START_OnFunc + TE_OnSetName, "OnSetName" },
	{ START_OnFunc + TE_OnIncludeItem, "OnIncludeItem" },
	{ START_OnFunc + TE_OnContentsChanged, "OnContentsChanged" },
	{ START_OnFunc + TE_OnFilterView, "OnFilterView" },
#ifdef _USE_SYNC
	{ START_OnFunc + TE_FN, "fn" },
#endif
};

TEmethod methodSB[] = {
	{ TE_PROPERTY + 0xf001, "Data" },
	{ TE_PROPERTY + 0xf002, "hwnd" },
	{ TE_PROPERTY + 0xf003, "Type" },
	{ TE_METHOD + 0xf004, "Navigate" },
	{ TE_METHOD + 0xf007, "Navigate2" },
	{ TE_PROPERTY + 0xf008, "Index" },
	{ TE_PROPERTY + 0xf009, "FolderFlags" },
	{ TE_PROPERTY + 0xf00B, "History" },
	{ TE_PROPERTY + 0xf010, "CurrentViewMode" },
	{ TE_METHOD + 0xf010, "SetViewMode" },
	{ TE_PROPERTY + 0xf011, "IconSize" },
	{ TE_PROPERTY + 0xf012, "Options" },
	{ TE_PROPERTY + 0xf013, "SizeFormat" },
	{ TE_PROPERTY + 0xf014, "NameFormat" }, //Deprecated
	{ TE_PROPERTY + 0xf016, "ViewFlags" },
	{ TE_PROPERTY + 0xf017, "Id" },
	{ TE_PROPERTY + 0xf018, "FilterView" },
	{ TE_METHOD + 0xf018, "Search" },
	{ TE_PROPERTY + 0xf020, "FolderItem" },
	{ TE_PROPERTY + 0xf021, "TreeView" },
	{ TE_PROPERTY + 0xf024, "Parent" },
	{ TE_METHOD + 0xf026, "Focus" },
	{ TE_METHOD + 0xf031, "Close" },
	{ TE_PROPERTY + 0xf032, "Title" },
	{ TE_METHOD + 0xf033, "Suspend" },
	{ TE_METHOD + 0xf040, "Items" },
	{ TE_METHOD + 0xf041, "SelectedItems" },
	{ TE_PROPERTY + 0xf050, "ShellFolderView" },
	{ TE_PROPERTY + 0xf058, "Droptarget" },
	{ TE_PROPERTY + 0xf059, "Columns" },
	{ TE_METHOD + 0xf059, "GetColumns" },
//	{ TE_PROPERTY + 0xf05A, "Searches" },
	{ TE_METHOD + 0xf05B, "MapColumnToSCID" },
	{ TE_PROPERTY + 0xf102, "hwndList" },
	{ TE_PROPERTY + 0xf103, "hwndView" },
	{ TE_PROPERTY + 0xf104, "SortColumn" },
	{ TE_METHOD + 0xf104, "GetSortColumn" },
	{ TE_PROPERTY + 0xf105, "GroupBy" },
	{ TE_METHOD + 0xf107, "HitTest" },
	{ TE_PROPERTY + 0xf108, "hwndAlt" },
	{ TE_METHOD + 0xf110, "ItemCount" },
	{ TE_METHOD + 0xf111, "Item" },
	{ TE_METHOD + 0xf206, "Refresh" },
	{ TE_METHOD + 0xf207, "ViewMenu" },
	{ TE_METHOD + 0xf208, "TranslateAccelerator" },
	{ TE_METHOD + 0xf209, "GetItemPosition" },
	{ TE_METHOD + 0xf20A, "SelectAndPositionItem" },
	{ TE_METHOD + 0xf280, "SelectItem" },
	{ TE_PROPERTY + 0xf281, "FocusedItem" },
	{ TE_PROPERTY + 0xf282, "GetFocusedItem" },
	{ TE_METHOD + 0xf283, "GetItemRect" },
	{ TE_METHOD + 0xf300, "Notify" },
	{ TE_METHOD + 0xf400, "NavigateComplete" },
	{ TE_METHOD + 0xf501, "AddItem" },
	{ TE_METHOD + 0xf502, "RemoveItem" },
	{ TE_METHOD + 0xf503, "AddItems" },
	{ TE_METHOD + 0xf504, "RemoveAll" },
	{ TE_PROPERTY + 0xf505, "SessionId" },
	{ START_OnFunc + SB_TotalFileSize, "TotalFileSize" },
	{ START_OnFunc + SB_ColumnsReplace, "ColumnsReplace" },
	{ START_OnFunc + SB_OnIncludeObject, "OnIncludeObject" },
	{ START_OnFunc + SB_AltSelectedItems, "AltSelectedItems" },
	{ START_OnFunc + SB_VirtualName, "VirtualName" }, //Deprecated
};

TEmethod methodTC[] = {
	{ TE_PROPERTY + 1, "Data" },
	{ TE_PROPERTY + 2, "hwnd" },
	{ TE_PROPERTY + 3, "Type" },
	{ TE_METHOD + 6, "HitTest" },
	{ TE_METHOD + 7, "Move" },
	{ TE_PROPERTY + 8, "Selected" },
	{ TE_METHOD + 9, "Close" },
	{ TE_PROPERTY + 10, "SelectedIndex" },
	{ TE_PROPERTY + 11, "Visible" },
	{ TE_PROPERTY + 12, "Id" },
	{ TE_METHOD + 13, "LockUpdate" },
	{ TE_METHOD + 14, "UnlockUpdate" },
	{ TE_METHOD + 15, "SetOrder" },
	{ DISPID_NEWENUM, "_NewEnum" },
	{ DISPID_TE_ITEM, "Item" },
	{ DISPID_TE_COUNT, "Count" },
	{ DISPID_TE_COUNT, "length" },
	{ TE_OFFSET + TE_Left, "Left" },
	{ TE_OFFSET + TE_Top, "Top" },
	{ TE_OFFSET + TE_Width, "Width" },
	{ TE_OFFSET + TE_Height, "Height" },
	{ TE_OFFSET + TC_Flags, "Style" },
	{ TE_OFFSET + TC_Align, "Align" },
	{ TE_OFFSET + TC_TabWidth, "TabWidth" },
	{ TE_OFFSET + TC_TabHeight, "TabHeight" },
};

TEmethod methodTV[] = {
	{ TE_PROPERTY + 0x1001, "Data" },
	{ TE_PROPERTY + 0x1002, "Type" },
	{ TE_PROPERTY + 0x1003, "hwnd" },
	{ TE_METHOD + 0x1004, "Close" },
	{ TE_PROPERTY + 0x1005, "hwndTree" },
	{ TE_PROPERTY + 0x1007, "FolderView" },
	{ TE_PROPERTY + 0x1008, "Align" },
	{ TE_PROPERTY + 0x1009, "Visible" },
	{ TE_METHOD + 0x1106, "Focus" },
	{ TE_METHOD + 0x1107, "HitTest" },
	{ TE_METHOD + 0x1206, "Refresh" },
	{ TE_METHOD + 0x1283, "GetItemRect" },
	{ TE_METHOD + 0x1300, "Notify" },
	{ TE_OFFSET + SB_TreeWidth, "Width" },
	{ TE_OFFSET + SB_TreeFlags, "Style" },
	{ TE_OFFSET + SB_EnumFlags, "EnumFlags" },
	{ TE_OFFSET + SB_RootStyle, "RootStyle" },
	{ TE_PROPERTY + 0x2000, "SelectedItem" },
	{ TE_METHOD + 0x2001, "SelectedItems" },
	{ TE_PROPERTY + 0x2002, "Root" },
	{ TE_METHOD + 0x2003, "SetRoot" },
	{ TE_METHOD + 0x2004, "Expand" },
	{ TE_PROPERTY + 0x2005, "Columns" },
	{ TE_PROPERTY + 0x2006, "CountViewTypes" },
	{ TE_PROPERTY + 0x2007, "Depth" },
	{ TE_PROPERTY + 0x2008, "EnumOptions" },
	{ TE_PROPERTY + 0x2009, "Export" },
	{ TE_PROPERTY + 0x200a, "Flags" },
	{ TE_PROPERTY + 0x200b, "Import" },
	{ TE_PROPERTY + 0x200c, "Mode" },
	{ TE_PROPERTY + 0x200d, "ResetSort" },
	{ TE_PROPERTY + 0x200e, "SetViewType" },
	{ TE_PROPERTY + 0x200f, "Synchronize" },
	{ TE_PROPERTY + 0x2010, "TVFlags" },
};

TEmethod methodGB[] = {
	{ TE_METHOD + 1, "FromHBITMAP" },
	{ TE_METHOD + 2, "FromHICON" },
	{ TE_METHOD + 3, "FromResource" },
	{ TE_METHOD + 4, "FromFile" },
	{ TE_METHOD + 5, "FromStream" },
	{ TE_METHOD + 6, "FromArchive" },
	{ TE_METHOD + 7, "FromItem" },//Deprecated
	{ TE_METHOD + 8, "FromClipboard" },
	{ TE_METHOD + 9, "FromSource" },
	{ TE_METHOD + 90, "Create" },
	{ TE_METHOD + 99, "Free" },

	{ TE_METHOD + 100, "Save" },
	{ TE_METHOD + 101, "Base64" },
	{ TE_METHOD + 102, "DataURI" },
	{ TE_METHOD + 103, "GetStream" },
	{ TE_METHOD + 110, "GetWidth" },
	{ TE_METHOD + 111, "GetHeight" },
	{ TE_METHOD + 112, "GetPixel" },
	{ TE_METHOD + 113, "SetPixel" },
	{ TE_METHOD + 114, "GetPixelFormat" },
	{ TE_METHOD + 115, "FillRect" },
	{ TE_METHOD + 116, "Mask" },
	{ TE_METHOD + 117, "AlphaBlend" },
	{ TE_METHOD + 120, "GetThumbnailImage" },
	{ TE_METHOD + 130, "RotateFlip" },
	{ TE_METHOD + 140, "GetFrameCount" },
	{ TE_PROPERTY + 150, "Frame" },
	{ TE_METHOD + 160, "GetMetadata" },
	{ TE_METHOD + 161, "GetFrameMetadata" },

	{ TE_METHOD + 210, "GetHBITMAP" },
	{ TE_METHOD + 211, "GetHICON" },
	{ TE_METHOD + 212, "DrawEx" },

	{ TE_METHOD + 900, "GetCodecInfo" },
	{ START_OnFunc + WIC_OnGetAlt, "OnGetAlt" },
};

//vvv Sort by name vvv
TEmethod methodWB[] = {
	{ TE_PROPERTY + 5, "Application" },
	{ TE_METHOD + 9, "Close" },
	{ TE_PROPERTY + 1, "Data" },
	{ TE_PROPERTY + 6, "Document" },
	{ TE_PROPERTY + 12, "DropMode" },
	{ TE_METHOD + 8, "Focus" },
	{ TE_PROPERTY + 2, "hwnd" },
	{ START_OnFunc + WB_OnClose, "OnClose" },
	{ TE_METHOD + 10, "PreventClose" },
	{ TE_METHOD + 4, "TranslateAccelerator" },
	{ TE_PROPERTY + 3, "Type" },
	{ TE_PROPERTY + 11, "Visible" },
	{ TE_PROPERTY + 7, "Window" },
};

TEmethod methodFIs[] = {
	{ DISPID_NEWENUM, "_NewEnum" },
	{ TE_METHOD + 8, "AddItem" },
	{ TE_PROPERTY + 2, "Application" },
	{ DISPID_TE_COUNT, "Count" },
	{ TE_PROPERTY + 0x1003, "Data" },
	{ TE_PROPERTY + 0x1001, "dwEffect" },
	{ TE_METHOD + 10, "GetData" },
	{ TE_PROPERTY + 9, "hDrop" },
	{ DISPID_TE_INDEX, "Index" },
	{ DISPID_TE_ITEM, "Item" },
	{ DISPID_TE_COUNT, "length" },
	{ TE_PROPERTY + 3, "Parent" },
	{ TE_PROPERTY + 0x1002, "pdwEffect" },
	{ TE_METHOD + 11, "SetData" },
	{ TE_PROPERTY + 0x1004, "UseText" },
};

TEmethod methodDT[] = {
	{ TE_METHOD + 1, "DragEnter" },
	{ TE_METHOD + 4, "DragLeave" },
	{ TE_METHOD + 2, "DragOver" },
	{ TE_METHOD + 3, "Drop" },
	{ TE_PROPERTY + 6, "FolderItem" },
	{ TE_PROPERTY + 5, "Type" },
};

TEmethod methodFI[] = {
	{ 9, "_BLOB" },	//To be necessary
	{ 3, "Alt" },
	{ 6, "Enum" },
//	{ 4, "FocusedItem" },
	{ 9, "FolderItem" }, // Reserved future
	{ 7, "Id" },
	{ 1, "Name" },
	{ 2, "Path" },
	{ 5, "Unavailable" },
};

TEmethod methodMem[] = {
	{ TE_PROPERTY + 0xfff9, "_BLOB" },
	{ DISPID_NEWENUM, "_NewEnum" },
	{ TE_METHOD + 8, "Clone" },
	{ DISPID_TE_COUNT, "Count" },
	{ TE_METHOD + 7, "Free" },
	{ DISPID_TE_ITEM, "Item" },
	{ DISPID_TE_COUNT, "length" },
	{ TE_PROPERTY + 0xfff1, "P" },
	{ TE_METHOD + 4, "Read" },
	{ TE_PROPERTY + 0xfff6, "Size" },
	{ TE_METHOD + 5, "Write" },
};

TEmethod methodMem2[] = {
	{ VT_UI1 << TE_VT, "BYTE" },
	{ VT_UI4 << TE_VT, "DWORD" },
	{ VT_PTR << TE_VT, "HANDLE" },
	{ VT_I4  << TE_VT, "int" },
	{ VT_PTR << TE_VT, "LPWSTR" },
	{ VT_UI2 << TE_VT, "WCHAR" },
	{ VT_UI2 << TE_VT, "WORD" },
};

TEmethod methodCM[] = {
	{ TE_PROPERTY + 5, "FolderView" },
	{ TE_METHOD + 4, "GetCommandString" },
	{ TE_METHOD + 6, "HandleMenuMsg" },
	{ TE_PROPERTY + 10, "hmenu" },
	{ TE_PROPERTY + 12, "idCmdFirst" },
	{ TE_PROPERTY + 13, "idCmdLast" },
	{ TE_PROPERTY + 11, "indexMenu" },
	{ TE_METHOD + 2, "InvokeCommand" },
	{ TE_METHOD + 3, "Items" },
	{ TE_METHOD + 1, "QueryContextMenu" },
	{ TE_PROPERTY + 14, "uFlags" },
};

TEmethod methodCD[] = {
	{ TE_PROPERTY + 21, "DefExt" },
	{ TE_PROPERTY + 10, "FileName" },
	{ TE_PROPERTY + 13, "Filter" },
	{ TE_PROPERTY + 32, "FilterIndex" },
	{ TE_PROPERTY + 31, "Flags" },
	{ TE_PROPERTY + 31, "FlagsEx" },
	{ TE_PROPERTY + 20, "InitDir" },
	{ TE_PROPERTY + 30, "MaxFileSize" },
	{ TE_METHOD + 40, "ShowOpen" },
	{ TE_METHOD + 41, "ShowSave" },
	{ TE_PROPERTY + 22, "Title" },
};

TEmethod methodPD[] = {
	{ TE_METHOD + 1, "HasUserCancelled" },
	{ TE_METHOD + 9, "SetAnimation" },
	{ TE_METHOD + 2, "SetCancelMsg" },
	{ TE_METHOD + 3, "SetLine" },
	{ TE_METHOD + 4, "SetProgress" },
	{ TE_METHOD + 5, "SetTitle" },
	{ TE_METHOD + 6, "StartProgressDialog" },
	{ TE_METHOD + 7, "StopProgressDialog" },
	{ TE_METHOD + 8, "Timer" },
};

TEmethod methodCO[] = {
	{ TE_METHOD + 1, "Free" },
};

TEmethod methodEN[] = {
	{ TE_METHOD + 1, "atEnd" },
	{ TE_METHOD + 2, "item" },
	{ TE_METHOD + 3, "moveFirst" },
	{ TE_METHOD + 4, "moveNext" },
};
