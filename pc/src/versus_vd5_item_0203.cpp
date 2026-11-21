// Work item 0203 (w3): Versus RVA 0xe5dc0-0xe60a8.
// A small mode-stack object: a stack of mode ids at +0xb4 with per-entry
// values at +0xf4 and a depth at +0x134, a list of FStrings at +0x74 and a
// current FString at +0x80. Changing the top of the stack calls virtual
// slot 0x70. Class and member names are neutral; the engine's names are not
// recovered. Most of these were compiled with /GL and linked with /LTCG
// (this in ECX/ESI/EDI, an index in EAX).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) int __cdecl wcscmp(const TCHAR *, const TCHAR *);

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
};

class FString : public FArray {
public:
    FString(const FString &Other);
    ~FString();
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
    INT Len() const { return ArrayNum ? ArrayNum - 1 : 0; }
};

template <class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

class UnnamedModeStack_e5dc0 {
public:
    virtual void Unused00();
    virtual void Unused04();
    virtual void Unused08();
    virtual void Unused0c();
    virtual void Unused10();
    virtual void Unused14();
    virtual void Unused18();
    virtual void Unused1c();
    virtual void Unused20();
    virtual void Unused24();
    virtual void Unused28();
    virtual void Unused2c();
    virtual void Unused30();
    virtual void Unused34();
    virtual void Unused38();
    virtual void Unused3c();
    virtual void Unused40();
    virtual void Unused44();
    virtual void Unused48();
    virtual void Unused4c();
    virtual void Unused50();
    virtual void Unused54();
    virtual void Unused58();
    virtual void Unused5c();
    virtual void Unused60();
    virtual void Unused64();
    virtual void Unused68();
    virtual void Unused6c();
    virtual void ModeChanged();               // slot 0x70

    INT Pad04[12];
    INT Done[7];                              // +0x34, per mode id
    INT Current;                              // +0x50
    INT Pad54[8];
    TArray<FString> Items;                    // +0x74
    FString Text;                             // +0x80
    INT Pad8c[3];
    INT Started[7];                           // +0x98, per mode id
    INT Stack[16];                            // +0xb4
    INT Values[16];                           // +0xf4
    INT Depth;                                // +0x134

    void Push(INT Mode, INT Which)
    {
        Stack[Depth] = Mode;
        Values[Depth] = 0;
        Depth++;
        Done[Which] = 0;
        if (Depth == 1) {
            Current = 0;
            Started[Which] = 0;
            ModeChanged();
        }
    }

    __declspec(noinline) void Pop(INT Mode);
    __declspec(noinline) UBOOL PushMode1();
    __declspec(noinline) UBOOL HasItem(FString S);
    __declspec(noinline) FString GetItem(INT i);
    __declspec(noinline) UBOOL SelectItem(INT i);
    __declspec(noinline) UBOOL SetText(FString S);
};

void UnnamedModeStack_e5dc0::Pop(INT Mode)
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
            Started[Stack[0]] = 0;
            Current = Values[0];
        }
    }
    ModeChanged();
}

UBOOL UnnamedModeStack_e5dc0::PushMode1()
{
    Push(1, 1);
    return 1;
}

UBOOL UnnamedModeStack_e5dc0::HasItem(FString S)
{
    for (INT i = 0; i < Items.Num(); i++)
        if (wcscmp(*Items(i), *S) == 0)
            return 1;
    return 0;
}

FString UnnamedModeStack_e5dc0::GetItem(INT i)
{
    return Items(i);
}

UBOOL UnnamedModeStack_e5dc0::SelectItem(INT i)
{
    Text = Items(i);
    Push(6, 6);
    return 1;
}

UBOOL UnnamedModeStack_e5dc0::SetText(FString S)
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

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_e5dc0(UnnamedModeStack_e5dc0 *M, INT Mode) { M->Pop(Mode); }
void Driver_e5e40(UnnamedModeStack_e5dc0 *M) { M->PushMode1(); }
void Driver_e5e90(UnnamedModeStack_e5dc0 *M, FString *S) { M->HasItem(*S); }
void Driver_e5f50(UnnamedModeStack_e5dc0 *M, INT i) { FString T = M->GetItem(i); Escape(&T); }
void Driver_e5f70(UnnamedModeStack_e5dc0 *M, INT i) { M->SelectItem(i); }
void Driver_e5fd0(UnnamedModeStack_e5dc0 *M, FString *S) { Escape(&GMalloc); M->SetText(*S); }
