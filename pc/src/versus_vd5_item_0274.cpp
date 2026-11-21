// Work item w3_0274: Versus RVA 0xfc1a0-0xfc509.
// Class names are neutral: no strings or vtable labels identify them.
// UnnamedThreshold_fc1a0 (vtable 0x10c03ed4) holds a flag and four floats;
// 0xfc1d0 tests them against a constant and toggles byte flags on a target
// object (offsets 0xe44..0xe47 and 0xe6f..0xe72), calling its vtable slot 25.
// UnnamedNamed_fc430 (vtable 0x10c03ec4, base vtable 0x10c03dc0) holds an
// FString at +4.
// Status: 0xfc1d0 and 0xfc490 match (vc70 /O2 /Gy /GX); 0xfc430 matches with
// try_ltcg.py /O2 /Gy /GX. 0xfc1a0 (LTCG, this in EAX) is a near miss: under
// /O2 the linker inlines it into the driver; under /O2 /Ob1 it is kept but the
// linker passes the flag argument in ECX, while retail takes all five on the stack.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FString {
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FString();
    FString &operator=(const TCHAR *Other);
    void Empty()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

class UObject;
extern UObject *GLog_10c71aa4; // 0x10c71aa4

class UnnamedTarget_fc1d0 {
public:
    virtual void V0(); virtual void V1(); virtual void V2(); virtual void V3();
    virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7();
    virtual void V8(); virtual void V9(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23(); virtual void V24();
    virtual void Notify(UObject *Source, INT Code, INT A, INT B); // slot 25 (+0x64)
    BYTE Pad[0xe40];
    BYTE Active[4];     // 0xe44
    BYTE Pad2[0x27];
    BYTE Latched[4];    // 0xe6f
};

FLOAT FUN_1094f020(FLOAT X);

class UnnamedThreshold_fc1a0 {
public:
    UBOOL Flag;     // +4
    FLOAT A;        // +8
    FLOAT B;        // +c
    FLOAT Scale;    // +10
    FLOAT Limit;    // +14
    UnnamedThreshold_fc1a0(UBOOL InFlag, FLOAT InA, FLOAT InB, FLOAT InScale, FLOAT InLimit)
;
    virtual void Update(UnnamedTarget_fc1d0 *T);
};

UnnamedThreshold_fc1a0::UnnamedThreshold_fc1a0(UBOOL InFlag, FLOAT InA, FLOAT InB, FLOAT InScale, FLOAT InLimit)
    : Flag(InFlag), A(InA), B(InB), Scale(InScale), Limit(InLimit)
{
}

void UnnamedThreshold_fc1a0::Update(UnnamedTarget_fc1d0 *T)
{
    if (Flag) {
        if (A - B > 0.0f) {
            if (!T->Latched[0] && !T->Latched[2] && !T->Latched[1]
                && FUN_1094f020(Scale * A) > Limit) {
                T->Latched[1] = 1;
                T->Active[1] = 1;
                T->Notify(GLog_10c71aa4, 0xd5, 1, 0);
            }
        } else if (B + A < 0.0f) {
            if (!T->Latched[0] && !T->Latched[2] && !T->Latched[3]
                && FUN_1094f020(Scale * A) > Limit) {
                T->Latched[3] = 1;
                T->Active[3] = 1;
                T->Notify(GLog_10c71aa4, 0xd7, 1, 0);
            }
        } else {
            T->Latched[1] = 0;
            T->Latched[3] = 0;
            T->Active[1] = 0;
            T->Active[3] = 0;
        }
    } else {
        if (B + A < 0.0f) {
            if (!T->Latched[1] && !T->Latched[3] && !T->Latched[0]
                && FUN_1094f020(Scale * A) > Limit) {
                T->Latched[0] = 1;
                T->Active[0] = 1;
                T->Notify(GLog_10c71aa4, 0xd4, 1, 0);
            }
        } else if (A - B > 0.0f) {
            if (!T->Latched[1] && !T->Latched[3] && !T->Latched[2]
                && FUN_1094f020(Scale * A) > Limit) {
                T->Latched[2] = 1;
                T->Active[2] = 1;
                T->Notify(GLog_10c71aa4, 0xd6, 1, 0);
            }
        } else {
            T->Latched[0] = 0;
            T->Latched[2] = 0;
            T->Active[0] = 0;
            T->Active[2] = 0;
        }
    }
}

class UnnamedBase_fc490 {
public:
    virtual ~UnnamedBase_fc490() {}
};

class UnnamedNamed_fc430 : public UnnamedBase_fc490 {
public:
    FString Name;
    UnnamedNamed_fc430(const TCHAR *InName);
    virtual ~UnnamedNamed_fc430();
};

UnnamedNamed_fc430::UnnamedNamed_fc430(const TCHAR *InName)
{
    Name = InName;
}

UnnamedNamed_fc430::~UnnamedNamed_fc430()
{
    Name.Empty();
}

// Scaffolding for the link, not part of the unit.
// FString::operator= (retail 0x4750, published) is repeated here so the
// linker gives it its link-time register convention.
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}
void *operator new(unsigned int, void *P);
void Escape(void *);
void *operator new(unsigned int Size);
UnnamedThreshold_fc1a0 *Driver_fc1a0(INT Which, FLOAT *V)
{
    if (Which)
        return new UnnamedThreshold_fc1a0(1, V[0], V[1], V[2], V[3]);
    return new UnnamedThreshold_fc1a0(0, V[4], V[5], V[6], V[7]);
}
UnnamedNamed_fc430 *Driver_fc430(void *Mem, const TCHAR *S)
{
    return new(Mem) UnnamedNamed_fc430(S);
}
