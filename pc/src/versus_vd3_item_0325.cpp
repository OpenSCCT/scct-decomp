// Work item 0325: Versus RVA 0x8fc90 (APlayerReplicationInfo vtable slot 36).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef DWORD UBOOL;

enum EName { NAME_None = 0 };
class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

class FString {
public:
    TCHAR *Data; INT ArrayNum; INT ArrayMax;
    FString &operator=(const FString &Other);
    INT operator!=(const FString &Other) const;
};

class UFunction;

class UObject {
public:
    virtual void VSlot0();
    virtual void VSlot1();
    virtual void VSlot2();
    virtual void VSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    UFunction *FindFunctionChecked(FName Name, INT Global = 0);
};

// Engine classes reached by offset. Names follow UE2 (Level at 0x1a0, XLevel at
// 0x1a4, ULevel NetDriver/Engine, UClient Viewports, UViewport Actor); the
// Versus offsets are inferred, not confirmed by symbols.
template<class T> class TArray {
public:
    T *Data; INT ArrayNum; INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
};
class APlayerReplicationInfo;
struct APlayerController_ { BYTE Pad[0x388]; APlayerReplicationInfo *PlayerReplicationInfo; };
struct UViewport { BYTE Pad[0x30]; APlayerController_ *Actor; };
struct UClient { BYTE Pad[0x2c]; TArray<UViewport *> Viewports; };
struct UEngine { BYTE Pad[0x30]; UClient *Client; };
struct UNetConnection { BYTE Pad[0x230]; double Latency; };   // field name guessed
struct UNetDriver { BYTE Pad[0x38]; UNetConnection *ServerConnection; };
// NetDriver is volatile here: retail re-reads it after the viewport test instead
// of reusing the first load.
struct ULevel { BYTE Pad[0xec]; UNetDriver *volatile NetDriver; UEngine *Engine; };
struct ALevelInfo { BYTE Pad[0x4a8]; BYTE NetMode; };

class AActor : public UObject {
public:
    void UnnamedVirtual36(INT Arg); // AActor vtable slot 36
};

class APlayerReplicationInfo : public AActor {
public:
    BYTE Pad4[0x1a0 - 4];
    ALevelInfo *Level;                // 0x1a0
    ULevel *XLevel;                   // 0x1a4
    BYTE Pad1a8[0x310 - 0x1a8];
    FString String310;                // 0x310
    FString String31C;                // 0x31c
    FString String328;                // 0x328
    FString String334;                // 0x334
    FString String340;                // 0x340
    BYTE Pad34c[0x3e8 - 0x34c];
    INT Score;                        // 0x3e8 (name guessed)
    void UnnamedVirtual36(INT Arg);
    // Inline helper (name guessed): is this the local viewport player's PRI?
    int IsLocalPlayerPRI() { return XLevel->Engine->Client->Viewports(0)->Actor->PlayerReplicationInfo == this; }
};

void APlayerReplicationInfo::UnnamedVirtual36(INT Arg)
{
    AActor::UnnamedVirtual36(Arg);
    if (Level->NetMode == 3) {
        if (XLevel->NetDriver && IsLocalPlayerPRI())
            Score += (INT)(-0.5 * (XLevel->NetDriver->ServerConnection->Latency * 1000.0));
        if (Score < 0)
            Score = 0;
        if (String340 != String310) {
            FString &Old = String334;
            Old = String340;
            String340 = String310;
            ProcessEvent(FindFunctionChecked(FName((EName)0xbba)), 0);
        }
        if (String31C != String328) {
            String328 = String31C;
            ProcessEvent(FindFunctionChecked(FName((EName)0xbb7)), 0);
        }
    }
}

// ---------------------------------------------------------------------------
// RVA 0x8fdb0: link-time-optimised (this in ESI, the argument in EAX).
// Neutral names: the two classes are known only by their offsets. The item
// keeps a back pointer at 0x30 to its owner; the owner keeps the item at 0x4a4.
// 0x10cbc930 is a class's static UClass object, tested with the inline UE2 IsA.

class UClass;
class UObjectHdr {
public:
    void *VTable; BYTE Pad4[0x24 - 4];
    UClass *Class;                    // 0x24
};
class UClass : public UObjectHdr {
public:
    UClass *SuperField;               // 0x28 (UField::SuperField)
};
extern UClass UnnamedClass_cbc930;    // privateStaticClass of an unidentified class

class UnnamedOwner_8fdb0;
class UnnamedItem_8fdb0 : public UObjectHdr {
public:
    BYTE Pad28[0x30 - 0x28];
    UnnamedOwner_8fdb0 *Owner;        // 0x30
    int IsA(UClass *SomeBase)
    {
        for (UClass *C = Class; C; C = C->SuperField)
            if (C == SomeBase)
                return 1;
        return 0;
    }
};

class UnnamedOwner_8fdb0 : public UObject {
public:
    BYTE Pad4[0x4a4 - 4];
    UnnamedItem_8fdb0 *Item;          // 0x4a4
    void SetItem(UnnamedItem_8fdb0 *NewItem);
};

void UnnamedOwner_8fdb0::SetItem(UnnamedItem_8fdb0 *NewItem)
{
    if (NewItem->Owner)
        NewItem->Owner->Item = 0;
    Item = NewItem;
    NewItem->Owner = this;
    if (NewItem->IsA(&UnnamedClass_cbc930))
        ProcessEvent(FindFunctionChecked(FName((EName)0xf2c)), 0);
}

// Scaffolding for the link, not part of the unit.
void Driver_8fdb0(UnnamedOwner_8fdb0 *O, UnnamedItem_8fdb0 *A) { O->SetItem(A); }
