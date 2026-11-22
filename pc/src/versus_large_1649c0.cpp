// versus_large_1649c0.cpp -- Versus RVA 0x1649c0-0x165fc2: a block of 64 native UClass
// registrations, in the order of the retail calls. Each call constructs one class's stock
// UClass object in place with the UClass constructor. Names come from the unit records
// (see the unit's identification).

#include "versus_large_1649c0.h"

typedef unsigned long DWORD;
typedef int INT;
typedef unsigned char BYTE;

enum ENativeConstructor { EC_NativeConstructor };

// Name indices (EName). Indices whose names are not recovered are written as casts.
enum EName
{
    NAME_System            = 0x256,
};

#define RF_Native_Flags 0x4084004

struct FName
{
    INT Index;
    FName(EName N) : Index(N) {}
};

struct FGuid
{
    DWORD A, B, C, D;
    FGuid(DWORD InA, DWORD InB, DWORD InC, DWORD InD) : A(InA), B(InB), C(InC), D(InD) {}
};

class UObject;
typedef void (UObject::*StaticConstructorType)();

class UClass
{
public:
    UClass(ENativeConstructor, DWORD InSize, DWORD InClassFlags, UClass *InBaseClass,
           UClass *InWithinClass, FGuid InGuid, FName InNameString, FName InPackageName,
           FName InClassConfigName, DWORD InFlags, void (*InClassConstructor)(void *),
           StaticConstructorType InClassStaticConstructor);
    BYTE unk_0[0x118];      // size not recovered
};

class UObject
{
public:
    static UClass PrivateStaticClass;
    static FName StaticConfigName() { return NAME_System; }
    void StaticConstructor();
};

inline void *operator new(unsigned int, void *Mem) { return Mem; }

// Placement callbacks (InClassConstructor): matched units by their symbols, unmatched ones
// as FUN_<VA>.
extern "C" {
void FUN_10a692f0(void *Storage);
void place_UGUI(void *Storage);
void place_UGUIComponent(void *Storage);
void place_UGUIImage(void *Storage);
void place_UGUIPage(void *Storage);
void place_UGUIFont(void *Storage);
void place_UGUILabel(void *Storage);
void place_UGUILabelPad(void *Storage);
void place_UGUIButton(void *Storage);
void place_UGUIGFXButton(void *Storage);
void place_UGUISpinnerButton(void *Storage);
void place_UGUICheckBoxButton(void *Storage);
void place_UGUICheckBox(void *Storage);
void place_UGUIEditBox(void *Storage);
void place_UGUINumericEdit(void *Storage);
void place_UGUIMultiComponent(void *Storage);
void place_UGUIScrollBarBase(void *Storage);
void place_UGUIVertScrollZone(void *Storage);
void place_UGUIVertScrollButton(void *Storage);
void place_UGUIVertGripButton(void *Storage);
void place_UGUIVertScrollBar(void *Storage);
void place_UGUIHorzScrollZone(void *Storage);
void place_UGUIHorzScrollButton(void *Storage);
void place_UGUIHorzGripButton(void *Storage);
void place_UGUIHorzScrollBar(void *Storage);
void place_UGUIListBoxBase(void *Storage);
void place_UGUIListBox(void *Storage);
void place_UGUIMultiColumnListBox(void *Storage);
void place_UGUIPanel(void *Storage);
void place_UGUIListBase(void *Storage);
void place_UGUIList(void *Storage);
void place_UGUIListFriends(void *Storage);
void FUN_10a68310(void *Storage);
void place_UGUIMultiColumnListHeader(void *Storage);
void FUN_10a680f0(void *Storage);
void place_UGUITabControl(void *Storage);
void place_UGUITabButton(void *Storage);
void place_UGUITabPanel(void *Storage);
void place_UGUIComboBox(void *Storage);
void place_UGUIMenuOption(void *Storage);
void place_UGUITitleBar(void *Storage);
void place_UGUISplitter(void *Storage);
void place_UGUISlider(void *Storage);
void place_UGUIVertList(void *Storage);
void place_UGUIHorzList(void *Storage);
void place_UGUICircularList(void *Storage);
void place_UGUIScrollText(void *Storage);
void place_UGUIScrollTextBox(void *Storage);
void place_UGUIProgressBar(void *Storage);
void place_UmoImageListMap(void *Storage);
void place_UGUICadre(void *Storage);
void place_UGUISearchFilterBox(void *Storage);
void place_UGUISessionInfoBox(void *Storage);
void place_UGUIMOTDInfoBox(void *Storage);
void place_UGUIMultiPageLabelBox(void *Storage);
void place_UGUIVertScrollBarLabel(void *Storage);
void place_UGUIMultiPageLabel(void *Storage);
void place_UGUIChatBox(void *Storage);
void FUN_10a66750(void *Storage);
void place_UGUIPageWaitLaunch(void *Storage);
void place_UStrategicMap(void *Storage);
void place_UmoEditBox(void *Storage);
void place_UmoListEditBox(void *Storage);
void FUN_10a65fd0(void *Storage);
}

// UnkType_10a649c0::Unk_10a649c0 -- RVA 0x1649c0: registers 64 native classes, the UGUI and
// Umo classes among them. guess: the owning class is unknown; the name is from the address.
class UnkType_10a649c0
{
public:
    static void Unk_10a649c0();
};

void UnkType_10a649c0::Unk_10a649c0()
{
    new(&class_object_UGUIController) UClass(EC_NativeConstructor, 0xe9c, 0x4,
        (UClass *)&class_object_UBaseGUIController, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xe7, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10a692f0,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUI) UClass(EC_NativeConstructor, 0x2c, 0x0,
        (UClass *)&UObject::PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x18, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUI,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIComponent) UClass(EC_NativeConstructor, 0x190, 0x0,
        (UClass *)&class_object_UGUI, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d08, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIComponent,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIImage) UClass(EC_NativeConstructor, 0x1ac, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d31, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIImage,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIPage) UClass(EC_NativeConstructor, 0x2e0, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d30, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIPage,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIFont) UClass(EC_NativeConstructor, 0x58, 0x0,
        (UClass *)&class_object_UGUI, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x183, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIFont,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUILabel) UClass(EC_NativeConstructor, 0x1c4, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d2f, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUILabel,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUILabelPad) UClass(EC_NativeConstructor, 0x1c8, 0x0,
        (UClass *)&class_object_UGUILabel, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x70e10, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUILabelPad,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIButton) UClass(EC_NativeConstructor, 0x1b0, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d1a, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIButton,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIGFXButton) UClass(EC_NativeConstructor, 0x1cc, 0x0,
        (UClass *)&class_object_UGUIButton, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d24, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIGFXButton,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUISpinnerButton) UClass(EC_NativeConstructor, 0x1d0, 0x0,
        (UClass *)&class_object_UGUIGFXButton, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d2e, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUISpinnerButton,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUICheckBoxButton) UClass(EC_NativeConstructor, 0x1cc, 0x0,
        (UClass *)&class_object_UGUIGFXButton, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d2d, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUICheckBoxButton,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUICheckBox) UClass(EC_NativeConstructor, 0x1b4, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x57648, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUICheckBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIEditBox) UClass(EC_NativeConstructor, 0x208, 0x0,
        (UClass *)&class_object_UGUIButton, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d2c, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIEditBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUINumericEdit) UClass(EC_NativeConstructor, 0x1c4, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d2b, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUINumericEdit,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIMultiComponent) UClass(EC_NativeConstructor, 0x1a0, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d0b, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIMultiComponent,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIScrollBarBase) UClass(EC_NativeConstructor, 0x1a4, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d22, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIScrollBarBase,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIVertScrollZone) UClass(EC_NativeConstructor, 0x198, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d2a, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIVertScrollZone,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIVertScrollButton) UClass(EC_NativeConstructor, 0x1d0, 0x0,
        (UClass *)&class_object_UGUIGFXButton, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d29, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIVertScrollButton,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIVertGripButton) UClass(EC_NativeConstructor, 0x1cc, 0x0,
        (UClass *)&class_object_UGUIGFXButton, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d28, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIVertGripButton,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIVertScrollBar) UClass(EC_NativeConstructor, 0x1b0, 0x0,
        (UClass *)&class_object_UGUIScrollBarBase, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d27, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIVertScrollBar,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIHorzScrollZone) UClass(EC_NativeConstructor, 0x198, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d26, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIHorzScrollZone,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIHorzScrollButton) UClass(EC_NativeConstructor, 0x1d0, 0x0,
        (UClass *)&class_object_UGUIGFXButton, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d25, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIHorzScrollButton,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIHorzGripButton) UClass(EC_NativeConstructor, 0x1cc, 0x0,
        (UClass *)&class_object_UGUIGFXButton, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d23, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIHorzGripButton,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIHorzScrollBar) UClass(EC_NativeConstructor, 0x1ac, 0x0,
        (UClass *)&class_object_UGUIScrollBarBase, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d21, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIHorzScrollBar,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIListBoxBase) UClass(EC_NativeConstructor, 0x1a8, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d0a, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIListBoxBase,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIListBox) UClass(EC_NativeConstructor, 0x1ac, 0x0,
        (UClass *)&class_object_UGUIListBoxBase, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d20, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIListBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIMultiColumnListBox) UClass(EC_NativeConstructor, 0x1b0, 0x0,
        (UClass *)&class_object_UGUIListBoxBase, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d1f, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIMultiColumnListBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIPanel) UClass(EC_NativeConstructor, 0x1a8, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d14, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIPanel,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIListBase) UClass(EC_NativeConstructor, 0x1d0, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d0f, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIListBase,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIList) UClass(EC_NativeConstructor, 0x1ec, 0x0,
        (UClass *)&class_object_UGUIVertList, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d0d, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIList,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIListFriends) UClass(EC_NativeConstructor, 0x1f8, 0x0,
        (UClass *)&class_object_UGUIList, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x5ae88, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIListFriends,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIMultiColumnList) UClass(EC_NativeConstructor, 0x27c, 0x0,
        (UClass *)&class_object_UGUIVertList, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d1e, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10a68310,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIMultiColumnListHeader) UClass(EC_NativeConstructor, 0x19c, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d1d, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIMultiColumnListHeader,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIStyles) UClass(EC_NativeConstructor, 0xf8, 0x0,
        (UClass *)&class_object_UGUI, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d1c, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10a680f0,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUITabControl) UClass(EC_NativeConstructor, 0x1d0, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d1b, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUITabControl,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUITabButton) UClass(EC_NativeConstructor, 0x1b8, 0x0,
        (UClass *)&class_object_UGUIButton, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d19, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUITabButton,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUITabPanel) UClass(EC_NativeConstructor, 0x1b0, 0x0,
        (UClass *)&class_object_UGUIPanel, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d18, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUITabPanel,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIComboBox) UClass(EC_NativeConstructor, 0x1c8, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d17, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIComboBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIMenuOption) UClass(EC_NativeConstructor, 0x1e4, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d16, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIMenuOption,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUITitleBar) UClass(EC_NativeConstructor, 0x1a8, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d15, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUITitleBar,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUISplitter) UClass(EC_NativeConstructor, 0x1b8, 0x0,
        (UClass *)&class_object_UGUIPanel, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d13, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUISplitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUISlider) UClass(EC_NativeConstructor, 0x1b8, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d12, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUISlider,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIVertList) UClass(EC_NativeConstructor, 0x1d0, 0x0,
        (UClass *)&class_object_UGUIListBase, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d0e, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIVertList,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIHorzList) UClass(EC_NativeConstructor, 0x1d0, 0x0,
        (UClass *)&class_object_UGUIListBase, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d11, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIHorzList,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUICircularList) UClass(EC_NativeConstructor, 0x1d8, 0x0,
        (UClass *)&class_object_UGUIListBase, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d10, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUICircularList,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIScrollText) UClass(EC_NativeConstructor, 0x244, 0x0,
        (UClass *)&class_object_UGUIList, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d0c, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIScrollText,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIScrollTextBox) UClass(EC_NativeConstructor, 0x1c4, 0x0,
        (UClass *)&class_object_UGUIListBoxBase, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d09, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIScrollTextBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIProgressBar) UClass(EC_NativeConstructor, 0x1e4, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9d07, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIProgressBar,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UmoImageListMap) UClass(EC_NativeConstructor, 0x1f0, 0x0,
        (UClass *)&class_object_UGUIMenuOption, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x87ea9, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UmoImageListMap,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUICadre) UClass(EC_NativeConstructor, 0x190, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x8aac0, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUICadre,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUISearchFilterBox) UClass(EC_NativeConstructor, 0x1a0, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x8aaca, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUISearchFilterBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUISessionInfoBox) UClass(EC_NativeConstructor, 0x1a0, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x8aacb, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUISessionInfoBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIMOTDInfoBox) UClass(EC_NativeConstructor, 0x1a0, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x8f54a, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIMOTDInfoBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIMultiPageLabelBox) UClass(EC_NativeConstructor, 0x1ac, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x8f4d0, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIMultiPageLabelBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIVertScrollBarLabel) UClass(EC_NativeConstructor, 0x1b4, 0x0,
        (UClass *)&class_object_UGUIScrollBarBase, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x8f4d9, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIVertScrollBarLabel,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIMultiPageLabel) UClass(EC_NativeConstructor, 0x1cc, 0x0,
        (UClass *)&class_object_UGUIComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x8f4cf, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIMultiPageLabel,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIChatBox) UClass(EC_NativeConstructor, 0x1f0, 0x0,
        (UClass *)&class_object_UGUIMultiComponent, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x92a8c, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIChatBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UBrowser_Keys) UClass(EC_NativeConstructor, 0x1178, 0x0,
        (UClass *)&class_object_UGUIMultiColumnList, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xa17d8, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10a66750,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UGUIPageWaitLaunch) UClass(EC_NativeConstructor, 0x2f0, 0x0,
        (UClass *)&class_object_UGUIPage, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xfb26d, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UGUIPageWaitLaunch,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UStrategicMap) UClass(EC_NativeConstructor, 0x31c, 0x0,
        (UClass *)&class_object_UGUIPageWaitLaunch, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xfb2e7, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UStrategicMap,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UmoEditBox) UClass(EC_NativeConstructor, 0x1ec, 0x0,
        (UClass *)&class_object_UGUIMenuOption, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x10ac05, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UmoEditBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UmoListEditBox) UClass(EC_NativeConstructor, 0x200, 0x0,
        (UClass *)&class_object_UmoEditBox, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x10ac08, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_UmoListEditBox,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&class_object_UmoListEditBox_GameMode) UClass(EC_NativeConstructor, 0x200, 0x0,
        (UClass *)&class_object_UmoListEditBox, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x10ac09, (EName)0x18, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10a65fd0,
        (StaticConstructorType)&UObject::StaticConstructor);
}
