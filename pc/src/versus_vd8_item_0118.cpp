// Work item 0118 (w4): Versus RVA 0x155740-0x155b01, UGUIController profile natives.
//   0x155740 UGUIController::execGetProfileName
//   0x1557f0 UGUIController::execRequestUseProfile
//   0x155850 UGUIController::execIsUseProfileFinished
//   0x155900 UGUIController::execRequestWriteProfile
//   0x1559b0 UGUIController::execIsRemoveProfileFinished
//   0x155a60 UGUIController::execRequestRemoveProfile

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
#define RESULT_DECL void *const Result

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};

template <class T> class TArray : public FArray {
public:
    TArray() {}
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const FString &Other);
    ~FString();
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
    INT Len() const { return ArrayNum ? ArrayNum - 1 : 0; }
};

class UObject;
class UProperty;
struct FFrame;

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];
extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

class UObject {
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20();
    virtual void NetDirty(UProperty *Property); // +0x54
};

struct FFrame {
    void *VfTable;
    void *Node;         // +0x04
    UObject *Object;    // +0x08
    BYTE *Code;         // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
    __forceinline void StepRef(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        GPropAddr = 0;
        (Context->*GNatives[B])(*this, Result);
    }
};

class UPCSaveGameDevice {
public:
    virtual void Vf00(); virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54(); virtual void Vf58(); virtual void Vf5c();
    virtual void Vf60(); virtual void Vf64(); virtual void Vf68(); virtual void Vf6c();
    virtual void StartNextOperation();          // +0x70

    INT unk_04[12];                             // +0x04
    INT Done[7];                                // +0x34
    INT Current;                                // +0x50
    INT unk_54[8];                              // +0x54
    TArray<FString> Items;                      // +0x74
    FString Text;                               // +0x80
    INT unk_8c[3];                              // +0x8c
    INT Status[7];                              // +0x98
    INT Stack[16];                              // +0xb4
    INT Values[16];                             // +0xf4
    INT Depth;                                  // +0x134

    void Push(INT Mode, INT Which)
    {
        Stack[Depth] = Mode;
        Values[Depth] = 0;
        Depth++;
        Done[Which] = 0;
        if (Depth == 1) {
            Current = 0;
            Status[Which] = 0;
            StartNextOperation();
        }
    }

    __declspec(noinline) void Pop(INT Mode);
    __declspec(noinline) FString GetItem(INT i);
    __declspec(noinline) UBOOL SelectItem(INT i);
    __declspec(noinline) UBOOL SetText(FString S);
    __declspec(noinline) UBOOL QueueOp3(FString Name);

    UBOOL IsOpFinished(INT Mode, INT &OutStatus)
    {
        if (Done[Mode]) {
            OutStatus = Status[Mode];
            Pop(Mode);
            return 1;
        }
        return 0;
    }
};

extern UPCSaveGameDevice *GPCSaveGameDevice;

void UPCSaveGameDevice::Pop(INT Mode)
{
    if (Depth) {
        if (Stack[0] != Mode)
            return;
        Done[Mode] = 1;
        for (INT i = 1; i < Depth; i++) {
            Stack[i - 1] = Stack[i];
            Values[i - 1] = Values[i];
        }
        Depth--;
        if (Depth) {
            Status[Stack[0]] = 0;
            Current = Values[0];
        }
    }
    StartNextOperation();
}

FString UPCSaveGameDevice::GetItem(INT i)
{
    return Items(i);
}

UBOOL UPCSaveGameDevice::SelectItem(INT i)
{
    Text = Items(i);
    Push(6, 6);
    return 1;
}

UBOOL UPCSaveGameDevice::SetText(FString S)
{
    FString &T = Text;
    T = S;
    if (S.Len() > 15) {
        INT Count = S.Len() - 15;
        if (Count >= T.ArrayNum) {
            T.ArrayNum = 0;
            if (T.Data) {
                GMalloc->Free(T.Data);
                T.Data = 0;
                T.ArrayMax = 0;
            }
        } else {
            T.ArrayNum -= Count;
            ((TCHAR *)T.Data)[T.ArrayNum - 1] = 0;
        }
    }
    Push(2, 2);
    return 1;
}

UBOOL UPCSaveGameDevice::QueueOp3(FString Name)
{
    Text = Name;
    Push(3, 3);
    return 1;
}

class UGUIController : public UObject {
public:
    void execGetProfileName(FFrame &Stack, RESULT_DECL);
    void execRequestUseProfile(FFrame &Stack, RESULT_DECL);
    void execIsUseProfileFinished(FFrame &Stack, RESULT_DECL);
    void execRequestWriteProfile(FFrame &Stack, RESULT_DECL);
    void execIsRemoveProfileFinished(FFrame &Stack, RESULT_DECL);
    void execRequestRemoveProfile(FFrame &Stack, RESULT_DECL);
};

#define P_GET_INT(var) INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_STR(var) FString var; Stack.Step(Stack.Object, &var);
#define P_GET_INT_REF(var) \
    INT var##T = 0; \
    Stack.StepRef(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    INT &var = GPropAddr ? *(INT *)GPropAddr : var##T;
#define P_FINISH Stack.Code++;

// RVA 0x155740
void UGUIController::execGetProfileName(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    UPCSaveGameDevice *Device = GPCSaveGameDevice;
    if (Device) {
        *(FString *)Result = Device->GetItem(Index);
    } else {
        *(DWORD *)Result = 0;
    }
}

// RVA 0x1557f0
void UGUIController::execRequestUseProfile(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Index);
    P_FINISH;
    UPCSaveGameDevice *Device = GPCSaveGameDevice;
    if (Device) {
        *(UBOOL *)Result = Device->SelectItem(Index);
    } else {
        *(UBOOL *)Result = 0;
    }
}

// RVA 0x155850
void UGUIController::execIsUseProfileFinished(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT_REF(Error);
    P_FINISH;
    UPCSaveGameDevice *Device = GPCSaveGameDevice;
    if (Device) {
        *(UBOOL *)Result = Device->IsOpFinished(6, Error);
    } else {
        *(UBOOL *)Result = 1;
    }
}

// RVA 0x155900
void UGUIController::execRequestWriteProfile(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(ProfileName);
    UPCSaveGameDevice *Device = GPCSaveGameDevice;
    P_FINISH;
    if (Device) {
        *(UBOOL *)Result = Device->SetText(ProfileName);
    } else {
        *(UBOOL *)Result = 0;
    }
}

// RVA 0x1559b0
void UGUIController::execIsRemoveProfileFinished(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT_REF(Error);
    P_FINISH;
    UPCSaveGameDevice *Device = GPCSaveGameDevice;
    if (Device) {
        *(UBOOL *)Result = Device->IsOpFinished(3, Error);
    } else {
        *(UBOOL *)Result = 1;
    }
}

// RVA 0x155a60
void UGUIController::execRequestRemoveProfile(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(ProfileName);
    P_FINISH;
    UPCSaveGameDevice *Device = GPCSaveGameDevice;
    if (Device) {
        *(UBOOL *)Result = Device->QueueOp3(ProfileName);
    } else {
        *(UBOOL *)Result = 0;
    }
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
typedef void (UGUIController::*GUINative)(FFrame &Stack, RESULT_DECL);

void Driver_155740(GUINative *Out)
{
    Escape(&GNatives);
    Escape(&GPCSaveGameDevice);
    *Out = &UGUIController::execGetProfileName;
}

void Driver_1557f0(GUINative *Out)
{
    Escape(&GNatives);
    Escape(&GPCSaveGameDevice);
    *Out = &UGUIController::execRequestUseProfile;
}

void Driver_155850(GUINative *Out)
{
    Escape(&GNatives);
    Escape(&GPropAddr);
    Escape(&GPropObject);
    Escape(&GProperty);
    Escape(&GPCSaveGameDevice);
    *Out = &UGUIController::execIsUseProfileFinished;
}

void Driver_155900(GUINative *Out)
{
    Escape(&GNatives);
    Escape(&GMalloc);
    Escape(&GPCSaveGameDevice);
    *Out = &UGUIController::execRequestWriteProfile;
}

void Driver_1559b0(GUINative *Out)
{
    Escape(&GNatives);
    Escape(&GPropAddr);
    Escape(&GPropObject);
    Escape(&GProperty);
    Escape(&GPCSaveGameDevice);
    *Out = &UGUIController::execIsRemoveProfileFinished;
}

void Driver_155a60(GUINative *Out)
{
    Escape(&GNatives);
    Escape(&GPCSaveGameDevice);
    *Out = &UGUIController::execRequestRemoveProfile;
}
