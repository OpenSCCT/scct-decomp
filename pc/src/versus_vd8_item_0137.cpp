// w4_item_0137.cpp -- Versus RVA 0x15a3b0 (UGUIPage::UpdateTimers)

typedef unsigned char      BYTE;
typedef unsigned short     TCHAR;
typedef int                INT;
typedef unsigned long      DWORD;
typedef unsigned __int64   QWORD;
typedef float              FLOAT;
typedef DWORD                UBOOL;
typedef DWORD              BITFIELD;

enum EName {
    NAME_None     = 0,
    NAME_PROBEMIN = 300,
    NAME_Timer    = 308,
    NAME_PROBEMAX = 364
};

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
};

struct FGuid;
class UFunction;

#pragma pack(push, 4)
struct FStateFrame {
    BYTE  unk_0[0x1c];
    QWORD ProbeMask;
};
#pragma pack(pop)

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *UnusedResult = 0);

    INT          Index;
    BYTE         unk_8[0x4];
    FStateFrame *StateFrame;
    BYTE         unk_10[0x18];

    UBOOL IsProbing(FName ProbeName)
    {
        return (ProbeName.GetIndex() < NAME_PROBEMIN ||
                ProbeName.GetIndex() >= NAME_PROBEMAX ||
                !StateFrame ||
                (StateFrame->ProbeMask &
                 ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN))) != 0);
    }

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
};

class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;

    INT Num() const { return ArrayNum; }
    void Remove(INT Index, INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1)
    {
        FArray::Remove(Index, Count, sizeof(T));
    }
};

class UGUI : public UObject {
public:
    BYTE unk_28[0x4];
};

class UGUIComponent : public UGUI {
public:
    BYTE     unk_2c[0x98];
    INT      TimerIndex;
    BITFIELD bTimerRepeat : 1;
    FLOAT    TimerCountdown;
    FLOAT    TimerInterval;
    BYTE     unk_d4[0xbc];

    void eventTimer()
    {
        if (IsProbing(NAME_Timer))
            ProcessEvent(FindFunctionChecked(NAME_Timer), 0);
    }
};

class UGUIMultiComponent : public UGUIComponent {
public:
    BYTE unk_190[0x10];
};

class UGUIPage : public UGUIMultiComponent {
public:
    BYTE                   unk_1a0[0x5c];
    TArray<UGUIComponent *> Timers;
    BYTE                   unk_208[0xd8];

    void UpdateTimers(FLOAT DeltaTime);
};

// UGUIPage::UpdateTimers (RVA 0x15a3b0)
void UGUIPage::UpdateTimers(FLOAT DeltaTime)
{
    INT Num = Timers.Num();
    for (INT i = 0; i < Num; i++) {
        UGUIComponent *Timer = Timers(i);
        Timer->TimerIndex = i;
        Timer->TimerCountdown -= DeltaTime;
        if (Timer->TimerCountdown <= 0.0 && Timer->TimerInterval > 0.0) {
            Timer->eventTimer();
            if (Timer->bTimerRepeat) {
                Timer->TimerCountdown += Timer->TimerInterval;
                if (Timer->TimerCountdown <= 0.0)
                    Timer->TimerCountdown = Timer->TimerInterval;
            } else {
                Timer->TimerInterval = 0.0f;
                Timer->TimerCountdown = 0.0f;
            }
        }
        if (Timer->TimerInterval <= 0.0) {
            Timer->TimerIndex = -1;
            Timers.Remove(i);
            i--;
            Num--;
        }
    }
}

// Scaffolding for the LTCG link, not part of the unit.
void Driver_15a3b0(UGUIPage *A, UGUIPage *B, FLOAT Dt)
{
    A->UpdateTimers(Dt);
    B->UpdateTimers(Dt);
}
