// w4_item_0035.cpp -- AActor::ProcessState (Versus RVA 0x129470)

#include "versus_build.h"
#include "unreal_containers.h"
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef unsigned short TCHAR;
typedef unsigned __int64 QWORD;

#define NULL 0

#pragma pack(push, 4)

enum EName {
    NAME_None = 0
};

enum ENetRole {
    ROLE_None      = 0,
    ROLE_Authority = 4
};

enum EStateFlags {
    STATE_Simulated = 0x00000004
};

struct FGuid;
class UObject;
class UStruct;
class UState;
class UFunction;
struct FFrame;
struct FStateFrame;

class FName {
public:
    INT Index;
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = NULL);
    virtual void VirtualSlot5();
    virtual void ProcessState(FLOAT DeltaSeconds);
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual UBOOL IsPendingKill();

    INT          Index;
    UObject     *HashNext;
    FStateFrame *StateFrame;
    BYTE         unk_10[0x18];

    FStateFrame *GetStateFrame() const { return StateFrame; }
};

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    UStruct *Node;
    UObject *Object;
    BYTE    *Code;
    BYTE    *Locals;

    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

struct FStateFrame : public FFrame {
    FFrame *CurrentFrame;
    UState *StateNode;
    QWORD   ProbeMask;
    INT     LatentAction;
};

class UField : public UObject {
public:
    UField *SuperField;
    UField *Next;
};

class UStruct : public UField {
public:
    UField       *Children;
    INT           PropertiesSize;
    FName         FriendlyName;
    TArray<BYTE>  Script;
    BYTE          unk_48[0x20];
};

class UState : public UStruct {
public:
    QWORD ProbeMask;
    QWORD IgnoreMask;
    DWORD StateFlags;
};

class AActor : public UObject {
public:
    virtual void ProcessState(FLOAT DeltaSeconds);

    BYTE     unk_28[0x2b6];
    BYTE     Role;
    BYTE     unk_2df[0x9];
    BITFIELD unk_2e8_0 : 15;
    BITFIELD bDeleteMe : 1;
    BITFIELD unk_2e8_16 : 16;
};

#pragma pack(pop)

// AActor::ProcessState
void AActor::ProcessState(FLOAT DeltaSeconds)
{
    if (GetStateFrame()
        && GetStateFrame()->Code
        && (Role >= ROLE_Authority || (GetStateFrame()->StateNode->StateFlags & STATE_Simulated))
        && !IsPendingKill()) {
        UState *OldStateNode = GetStateFrame()->StateNode;
        if (GetStateFrame()->LatentAction != 0) {
            (this->*GNatives[GetStateFrame()->LatentAction])(
                *GetStateFrame(), (BYTE *)&DeltaSeconds);
        }

        BYTE Buffer[32];
        INT NumStates = 0;
        while (!bDeleteMe && GetStateFrame()->Code && GetStateFrame()->LatentAction == 0) {
            GetStateFrame()->Step(this, Buffer);
            if (GetStateFrame()->StateNode != OldStateNode) {
                OldStateNode = GetStateFrame()->StateNode;
                if (++NumStates > 4) {
                    break;
                }
            }
        }
    }
}
