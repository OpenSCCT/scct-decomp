// versus_gui_classes.h -- classes of the GUI package as the Versus executable builds them
#ifndef VERSUS_GUI_CLASSES_H
#define VERSUS_GUI_CLASSES_H

#include "versus_build.h"
#include "unreal_containers.h"
#include "unreal_object.h"
#include "versus_ltcg.h"

// GUI.GUI: 0x2c bytes, 22 virtual functions
class UGUI : public UObject {
public:
    virtual ~UGUI();

    BYTE unk_28[0x4];
};

// GUI.GUIComponent: 0x190 bytes, 44 virtual functions
class UGUIComponent : public UGUI {
public:
    virtual ~UGUIComponent();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();

    BYTE    unk_2c[0x8];
    FString unk_34;
    FString unk_40;
    BYTE    unk_4c[0x18];
    FString unk_64;
    BYTE    unk_70[0x120];
};

// GUI.GUIImage: 0x1ac bytes, 44 virtual functions
class UGUIImage : public UGUIComponent {
public:
    virtual ~UGUIImage();

    BYTE unk_190[0x1c];
};

// GUI.GUIMultiComponent: 0x1a0 bytes, 44 virtual functions
class UGUIMultiComponent : public UGUIComponent {
public:
    virtual ~UGUIMultiComponent();

    TArrayLtcg<UnkType_4> unk_190;
    BYTE                  unk_19c[0x4];
};

// GUI.GUIPage: 0x2e0 bytes, 44 virtual functions
class UGUIPage : public UGUIMultiComponent {
public:
    virtual ~UGUIPage();

    BYTE                  unk_1a0[0x18];
    FString               unk_1b8;
    FString               unk_1c4;
    FString               unk_1d0;
    FString               unk_1dc;
    BYTE                  unk_1e8[0x14];
    TArrayLtcg<UnkType_4> unk_1fc;
    BYTE                  unk_208[0x78];
    FString               unk_280;
    BYTE                  unk_28c[0x54];
};

// GUI.GUIFont: 0x58 bytes, 22 virtual functions
class UGUIFont : public UGUI {
public:
    virtual ~UGUIFont();

    FString               unk_2c;
    BYTE                  unk_38[0x4];
    TArray<UnkType_4>     unk_3c;
    TArrayLtcg<UnkType_4> unk_48;
    BYTE                  unk_54[0x4];
};

// GUI.GUILabel: 0x1c4 bytes, 44 virtual functions
class UGUILabel : public UGUIComponent {
public:
    virtual ~UGUILabel();

    FString unk_190;
    BYTE    unk_19c[0x10];
    FString unk_1ac;
    BYTE    unk_1b8[0xc];
};

// GUI.GUILabelPad: 0x1c8 bytes, 44 virtual functions
class UGUILabelPad : public UGUILabel {
public:
    virtual ~UGUILabelPad();

    BYTE unk_1c4[0x4];
};

// GUI.GUIButton: 0x1b0 bytes, 44 virtual functions
class UGUIButton : public UGUIComponent {
public:
    virtual ~UGUIButton();

    BYTE    unk_190[0x4];
    FString unk_194;
    BYTE    unk_1a0[0x10];
};

// GUI.GUIGFXButton: 0x1cc bytes, 44 virtual functions
class UGUIGFXButton : public UGUIButton {
public:
    virtual ~UGUIGFXButton();

    BYTE unk_1b0[0x1c];
};

// GUI.GUISpinnerButton: 0x1d0 bytes, 44 virtual functions
class UGUISpinnerButton : public UGUIGFXButton {
public:
    virtual ~UGUISpinnerButton();

    BYTE unk_1cc[0x4];
};

// GUI.GUICheckBoxButton: 0x1cc bytes, 44 virtual functions
class UGUICheckBoxButton : public UGUIGFXButton {
public:
    virtual ~UGUICheckBoxButton();
};

// GUI.GUICheckBox: 0x1b4 bytes, 44 virtual functions
class UGUICheckBox : public UGUIComponent {
public:
    virtual ~UGUICheckBox();

    BYTE    unk_190[0x8];
    FString unk_198;
    BYTE    unk_1a4[0x10];
};

// GUI.GUIEditBox: 0x208 bytes, 44 virtual functions
class UGUIEditBox : public UGUIButton {
public:
    virtual ~UGUIEditBox();

    FString unk_1b0;
    FString unk_1bc;
    BYTE    unk_1c8[0x40];
};

// GUI.GUINumericEdit: 0x1c4 bytes, 44 virtual functions
class UGUINumericEdit : public UGUIMultiComponent {
public:
    virtual ~UGUINumericEdit();

    FString unk_1a0;
    BYTE    unk_1ac[0x18];
};

// GUI.GUIScrollBarBase: 0x1a4 bytes, 44 virtual functions
class UGUIScrollBarBase : public UGUIMultiComponent {
public:
    virtual ~UGUIScrollBarBase();

    BYTE unk_1a0[0x4];
};

// GUI.GUIVertScrollZone: 0x198 bytes, 44 virtual functions
class UGUIVertScrollZone : public UGUIComponent {
public:
    virtual ~UGUIVertScrollZone();

    BYTE unk_190[0x8];
};

// GUI.GUIVertScrollButton: 0x1d0 bytes, 44 virtual functions
class UGUIVertScrollButton : public UGUIGFXButton {
public:
    virtual ~UGUIVertScrollButton();

    BYTE unk_1cc[0x4];
};

// GUI.GUIVertGripButton: 0x1cc bytes, 44 virtual functions
class UGUIVertGripButton : public UGUIGFXButton {
public:
    virtual ~UGUIVertGripButton();
};

// GUI.GUIVertScrollBar: 0x1b0 bytes, 44 virtual functions
class UGUIVertScrollBar : public UGUIScrollBarBase {
public:
    virtual ~UGUIVertScrollBar();

    BYTE unk_1a4[0xc];
};

// GUI.GUIHorzScrollZone: 0x198 bytes, 44 virtual functions
class UGUIHorzScrollZone : public UGUIComponent {
public:
    virtual ~UGUIHorzScrollZone();

    BYTE unk_190[0x8];
};

// GUI.GUIHorzScrollButton: 0x1d0 bytes, 44 virtual functions
class UGUIHorzScrollButton : public UGUIGFXButton {
public:
    virtual ~UGUIHorzScrollButton();

    BYTE unk_1cc[0x4];
};

// GUI.GUIHorzGripButton: 0x1cc bytes, 44 virtual functions
class UGUIHorzGripButton : public UGUIGFXButton {
public:
    virtual ~UGUIHorzGripButton();
};

// GUI.GUIHorzScrollBar: 0x1ac bytes, 44 virtual functions
class UGUIHorzScrollBar : public UGUIScrollBarBase {
public:
    virtual ~UGUIHorzScrollBar();

    BYTE unk_1a4[0x8];
};

// GUI.GUIListBoxBase: 0x1a8 bytes, 44 virtual functions
class UGUIListBoxBase : public UGUIMultiComponent {
public:
    virtual ~UGUIListBoxBase();

    BYTE unk_1a0[0x8];
};

// GUI.GUIListBox: 0x1ac bytes, 44 virtual functions
class UGUIListBox : public UGUIListBoxBase {
public:
    virtual ~UGUIListBox();

    BYTE unk_1a8[0x4];
};

// GUI.GUIMultiColumnListBox: 0x1b0 bytes, 44 virtual functions
class UGUIMultiColumnListBox : public UGUIListBoxBase {
public:
    virtual ~UGUIMultiColumnListBox();

    BYTE unk_1a8[0x8];
};

// GUI.GUIPanel: 0x1a8 bytes, 44 virtual functions
class UGUIPanel : public UGUIMultiComponent {
public:
    virtual ~UGUIPanel();

    BYTE unk_1a0[0x8];
};

// GUI.GUIListBase: 0x1d0 bytes, 45 virtual functions
class UGUIListBase : public UGUIComponent {
public:
    virtual ~UGUIListBase();
    virtual void VirtualSlot44();

    BYTE unk_190[0x40];
};

// GUI.GUIVertList: 0x1d0 bytes, 45 virtual functions
class UGUIVertList : public UGUIListBase {
public:
    virtual ~UGUIVertList();
};

// GUI.GUIList: 0x1ec bytes, 45 virtual functions
class UGUIList : public UGUIVertList {
public:
    virtual ~UGUIList();

    BYTE                       unk_1d0[0x4];
    TArrayLtcg<UnkType_163C20> unk_1d4;
    BYTE                       unk_1e0[0xc];
};

// GUI.GUIListFriends: 0x1f8 bytes, 45 virtual functions
class UGUIListFriends : public UGUIList {
public:
    virtual ~UGUIListFriends();

    BYTE unk_1ec[0xc];
};

// GUI.GUIMultiColumnListHeader: 0x19c bytes, 44 virtual functions
class UGUIMultiColumnListHeader : public UGUIComponent {
public:
    virtual ~UGUIMultiColumnListHeader();

    BYTE unk_190[0xc];
};

// GUI.GUITabControl: 0x1d0 bytes, 44 virtual functions
class UGUITabControl : public UGUIMultiComponent {
public:
    virtual ~UGUITabControl();

    BYTE                  unk_1a0[0x4];
    TArrayLtcg<UnkType_4> unk_1a4;
    BYTE                  unk_1b0[0x4];
    FString               unk_1b4;
    BYTE                  unk_1c0[0x10];
};

// GUI.GUITabButton: 0x1b8 bytes, 44 virtual functions
class UGUITabButton : public UGUIButton {
public:
    virtual ~UGUITabButton();

    BYTE unk_1b0[0x8];
};

// GUI.GUITabPanel: 0x1b0 bytes, 44 virtual functions
class UGUITabPanel : public UGUIPanel {
public:
    virtual ~UGUITabPanel();

    BYTE unk_1a8[0x8];
};

// GUI.GUIComboBox: 0x1c8 bytes, 44 virtual functions
class UGUIComboBox : public UGUIMultiComponent {
public:
    virtual ~UGUIComboBox();

    BYTE    unk_1a0[0xc];
    FString unk_1ac;
    BYTE    unk_1b8[0x10];
};

// GUI.GUIMenuOption: 0x1e4 bytes, 44 virtual functions
class UGUIMenuOption : public UGUIMultiComponent {
public:
    virtual ~UGUIMenuOption();

    BYTE    unk_1a0[0xc];
    FString unk_1ac;
    FString unk_1b8;
    BYTE    unk_1c4[0x4];
    FString unk_1c8;
    BYTE    unk_1d4[0x10];
};

// GUI.GUITitleBar: 0x1a8 bytes, 44 virtual functions
class UGUITitleBar : public UGUIComponent {
public:
    virtual ~UGUITitleBar();

    FString unk_190;
    BYTE    unk_19c[0xc];
};

// GUI.GUISplitter: 0x1b8 bytes, 44 virtual functions
class UGUISplitter : public UGUIPanel {
public:
    virtual ~UGUISplitter();
    void SplitterUpdatePositions();

    BYTE unk_1a8[0x10];
};

// GUI.GUISlider: 0x1b8 bytes, 44 virtual functions
class UGUISlider : public UGUIComponent {
public:
    virtual ~UGUISlider();

    BYTE    unk_190[0x8];
    FString unk_198;
    BYTE    unk_1a4[0x14];
};

// GUI.GUIHorzList: 0x1d0 bytes, 45 virtual functions
class UGUIHorzList : public UGUIListBase {
public:
    virtual ~UGUIHorzList();
};

// GUI.GUICircularList: 0x1d8 bytes, 45 virtual functions
class UGUICircularList : public UGUIListBase {
public:
    virtual ~UGUICircularList();

    BYTE unk_1d0[0x8];
};

// GUI.GUIScrollText: 0x244 bytes, 45 virtual functions
class UGUIScrollText : public UGUIList {
public:
    virtual ~UGUIScrollText();

    FString unk_1ec;
    FString unk_1f8;
    BYTE    unk_204[0x18];
    FString unk_21c;
    BYTE    unk_228[0x1c];
};

// GUI.GUIScrollTextBox: 0x1c4 bytes, 44 virtual functions
class UGUIScrollTextBox : public UGUIListBoxBase {
public:
    virtual ~UGUIScrollTextBox();

    BYTE unk_1a8[0x1c];
};

// GUI.GUIProgressBar: 0x1e4 bytes, 44 virtual functions
class UGUIProgressBar : public UGUIComponent {
public:
    virtual ~UGUIProgressBar();

    BYTE    unk_190[0x20];
    FString unk_1b0;
    FString unk_1bc;
    FString unk_1c8;
    BYTE    unk_1d4[0x10];
};

// GUI.moImageListMap: 0x1f0 bytes, 44 virtual functions
class UmoImageListMap : public UGUIMenuOption {
public:
    virtual ~UmoImageListMap();

    BYTE unk_1e4[0xc];
};

// GUI.GUICadre: 0x190 bytes, 44 virtual functions
class UGUICadre : public UGUIComponent {
public:
    virtual ~UGUICadre();
};

// GUI.GUISearchFilterBox: 0x1a0 bytes, 44 virtual functions
class UGUISearchFilterBox : public UGUIMultiComponent {
public:
    virtual ~UGUISearchFilterBox();
};

// GUI.GUISessionInfoBox: 0x1a0 bytes, 44 virtual functions
class UGUISessionInfoBox : public UGUIMultiComponent {
public:
    virtual ~UGUISessionInfoBox();
};

// GUI.GUIMOTDInfoBox: 0x1a0 bytes, 44 virtual functions
class UGUIMOTDInfoBox : public UGUIMultiComponent {
public:
    virtual ~UGUIMOTDInfoBox();
};

// GUI.GUIMultiPageLabelBox: 0x1ac bytes, 44 virtual functions
class UGUIMultiPageLabelBox : public UGUIMultiComponent {
public:
    virtual ~UGUIMultiPageLabelBox();

    BYTE unk_1a0[0xc];
};

// GUI.GUIVertScrollBarLabel: 0x1b4 bytes, 44 virtual functions
class UGUIVertScrollBarLabel : public UGUIScrollBarBase {
public:
    virtual ~UGUIVertScrollBarLabel();

    BYTE unk_1a4[0x10];
};

// GUI.GUIMultiPageLabel: 0x1cc bytes, 44 virtual functions
class UGUIMultiPageLabel : public UGUIComponent {
public:
    virtual ~UGUIMultiPageLabel();

    FString         unk_190;
    TArray<FString> unk_19c;
    BYTE            unk_1a8[0x24];
};

// GUI.GUIChatBox: 0x1f0 bytes, 44 virtual functions
class UGUIChatBox : public UGUIMultiComponent {
public:
    virtual ~UGUIChatBox();

    BYTE    unk_1a0[0x14];
    FString unk_1b4;
    FString unk_1c0;
    FString unk_1cc;
    FString unk_1d8;
    FString unk_1e4;
};

// GUI.GUIPageWaitLaunch: 0x2f0 bytes, 44 virtual functions
class UGUIPageWaitLaunch : public UGUIPage {
public:
    virtual ~UGUIPageWaitLaunch();

    FString unk_2e0;
    BYTE    unk_2ec[0x4];
};

// GUI.StrategicMap: 0x31c bytes, 44 virtual functions
class UStrategicMap : public UGUIPageWaitLaunch {
public:
    virtual ~UStrategicMap();

    BYTE unk_2f0[0x2c];
};

// GUI.moEditBox: 0x1ec bytes, 44 virtual functions
class UmoEditBox : public UGUIMenuOption {
public:
    virtual ~UmoEditBox();

    BYTE unk_1e4[0x8];
};

// GUI.moListEditBox: 0x200 bytes, 44 virtual functions
class UmoListEditBox : public UmoEditBox {
public:
    virtual ~UmoListEditBox();

    BYTE unk_1ec[0x14];
};

// GUI.moListEditBox_GameMode: 0x200 bytes, 44 virtual functions
class UmoListEditBox_GameMode : public UmoListEditBox {
public:
    virtual ~UmoListEditBox_GameMode();
};

#endif // VERSUS_GUI_CLASSES_H
