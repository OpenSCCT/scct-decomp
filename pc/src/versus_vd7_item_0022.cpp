// w4_item_0022.cpp -- Versus AActor network/platform script natives (RVA 0x126630-0x12675e)
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

#define RESULT_DECL void *const Result

struct FGuid;
struct FFrame;
class UObject;
class UProperty;

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];
extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;

    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();
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
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void NetDirty(UProperty *Property);
};

class AActor : public UObject {
public:
    void execConvertToGamertag(FFrame &Stack, RESULT_DECL);
    void execConnectionAsServerOnly(FFrame &Stack, RESULT_DECL);
    void execGetPersistentData(FFrame &Stack, RESULT_DECL);
    void execEnablePB(FFrame &Stack, RESULT_DECL);
};

struct FFrame {
    void *VfTable;
    class UStruct *Node;
    UObject *Object;
    BYTE *Code;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
    void StepRef(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        GPropAddr = 0;
        (Context->*GNatives[B])(*this, Result);
    }
};

struct UGameEngine {
    BYTE unk_0[0x184];
    UObject *PersistentData;
};

extern UBOOL GConnectionAsServerOnly;
extern UGameEngine *GEngine;

#define P_GET_UBOOL(Var) DWORD Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_STR_REF(Var) \
    FString Var##T; Stack.StepRef(Stack.Object, &Var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    FString *Var = GPropAddr ? (FString *)GPropAddr : &Var##T
#define P_FINISH Stack.Code++

// AActor::execConvertToGamertag (RVA 0x126630)
void AActor::execConvertToGamertag(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR_REF(Str);
    P_FINISH;
}

// AActor::execConnectionAsServerOnly (RVA 0x1266c0)
void AActor::execConnectionAsServerOnly(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(bServerOnly);
    P_FINISH;
    GConnectionAsServerOnly = bServerOnly;
}

// AActor::execGetPersistentData (RVA 0x126700)
void AActor::execGetPersistentData(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(UObject **)Result = GEngine->PersistentData;
}

// AActor::execEnablePB (RVA 0x126720)
// Also COMDAT-folded with UObject::execPSX2NetCnfSelectCombination and
// USXBoxLiveRef::execIsVoiceBanned.
void AActor::execEnablePB(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(bEnable);
    P_FINISH;
    *(UBOOL *)Result = 0;
}
