#ifndef VERSUS_GUI_LIST_TYPES_H
#define VERSUS_GUI_LIST_TYPES_H

#include "unreal_math.h"
#include "versus_script_delegate.h"

class UCanvas;
class UMaterial;
class UGUIStyles;
class UGUIController;
class UGUIScrollBarBase;

class UGUI : public UObject {
public:
    virtual ~UGUI();

    UGUIController *Controller;
};

class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual void PreDraw(UCanvas *Canvas);
    virtual void Draw(UCanvas *Canvas);
    virtual UBOOL PerformInBounds(INT MouseX, INT MouseY);
    virtual void UpdateBounds();
    virtual FLOAT ActualWidth();
    virtual FLOAT ActualHeight();
    virtual FLOAT ActualLeft();
    virtual FLOAT ActualTop();
    virtual void SaveCanvasState(UCanvas *Canvas);
    virtual void RestoreCanvasState(UCanvas *Canvas);
    virtual UGUIComponent *UnderCursor(FLOAT MouseX, FLOAT MouseY);
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual UBOOL MouseHover();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void Timer();
    virtual void VirtualSlot43();

    UGUIComponent *MenuOwner;
    BYTE MenuState;
    FString IniDefault;
    FString StyleName;
    FLOAT SelTop, SelLeft, SelWidth, SelHeight;
    DWORD bBoundToParent : 1;
    DWORD bScaleToParent : 1;
    DWORD bHasFocus : 1;
    DWORD bVisible : 1;
    DWORD bAcceptsInput : 1;
    DWORD bCaptureTabs : 1;
    DWORD bCaptureMouse : 1;
    DWORD bNeverFocus : 1;
    DWORD bRepeatClick : 1;
    DWORD bRequireReleaseClick : 1;
    UGUIComponent *FocusInstead;
    FString Hint;
    FLOAT WinTop, WinLeft, WinWidth, WinHeight;
    FLOAT ComponentLeft;
    INT MouseCursorIndex;
    BYTE unk_88[0x9c - 0x88];
    UGUIStyles *Style;
    FLOAT Bounds[4], ClientBounds[4];
    BYTE unk_c0[0x190 - 0xc0];
};

class UGUIListBase : public UGUIComponent {
public:
    virtual ~UGUIListBase();
    virtual void VirtualSlot44();

    DWORD bSorted : 1;
    FColor SelectedBKColor;
    UMaterial *SelectedImage;
    INT Top, Index, OldIndex;
    INT ItemsPerPage, ItemHeight, ItemWidth, ItemCount;
    DWORD bHotTrack : 1;
    DWORD bVisibleWhenEmpty : 1;
    DWORD bCanUnselect : 1;
    UGUIScrollBarBase *MyScrollBar;
    FScriptDelegate __OnDrawItem__Delegate;
    FScriptDelegate __OnAdjustTop__Delegate;

    void delegateOnDrawItem(UCanvas *Canvas, INT Item, FLOAT X, FLOAT Y,
        FLOAT W, FLOAT H, UBOOL bSelected);
};

class UGUIVertList : public UGUIListBase {
public:
    virtual ~UGUIVertList();
    virtual void Draw(UCanvas *Canvas);
};

struct FMultiColumnSortData {
    FString SortString;
    INT SortItem;
};

class UGUIMultiColumnList : public UGUIVertList {
public:
    virtual void Draw(UCanvas *Canvas);

    UMaterial *ArrowUp, *ArrowDown;
    FColor ArrowColor;
    DWORD bDrawColumn : 1;
    DWORD bDrawArrow : 1;
    TArray<FMultiColumnSortData> SortData;
    TArray<INT> InvSortData;
    FString ColumnHeadings[8];
    TArray<FLOAT> ColumnWidths;
    TArray<FLOAT> InitColumnPerc;
    FLOAT CellSpacing;
    INT SortColumn;
    DWORD SortDescending : 1;
    DWORD ExpandLastColumn : 1;
    DWORD bInitialised : 1;
    DWORD NeedsSorting : 1;
};

#endif
