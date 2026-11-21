// Work item 0339: Versus RVA 0x92dc0-0x92f63.
// AActor probe events (LTCG copies), FRotator/FVector inequality, and two
// by-value comparison helpers.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *A, const TCHAR *B);
inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }

enum EName { NAME_None = 0 };

class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};

// UE2 FStateFrame: probe mask lives at +0x1c.
#pragma pack(push, 4)
struct FStateFrame
{
    BYTE Pad[0x1c];
    QWORD ProbeMask;
};
#pragma pack(pop)

class UFunction;

class UObject
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);

    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
};

class AActor : public UObject
{
public:
    void eventProbe13b(INT A);
    void eventProbe144(INT A);
};

struct ProbeEvent_Parms
{
    INT A;
};

// RVA 0x92dc0 (LTCG: this in ESI). Probe event for name index 0x13b (probe bit 15).
__declspec(noinline) void AActor::eventProbe13b(INT A)
{
    if (!StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << 15)))
    {
        ProbeEvent_Parms Parms;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(FName((EName)0x13b)), &Parms);
    }
}

// RVA 0x92e70 (LTCG: this in ESI). Probe event for name index 0x144 (probe bit 24).
__declspec(noinline) void AActor::eventProbe144(INT A)
{
    if (!StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << 24)))
    {
        ProbeEvent_Parms Parms;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(FName((EName)0x144)), &Parms);
    }
}

class FRotator
{
public:
    INT Pitch, Yaw, Roll;
    UBOOL operator!=(const FRotator &R) const;
};

// RVA 0x92e20 (LTCG: this in ECX, R in EAX).
__declspec(noinline) UBOOL FRotator::operator!=(const FRotator &R) const
{
    return Pitch != R.Pitch || Yaw != R.Yaw || Roll != R.Roll;
}

class FVector
{
public:
    FLOAT X, Y, Z;
    UBOOL operator!=(const FVector &V) const;
};

// RVA 0x92e40 (LTCG: this in EDX, V in ECX).
__declspec(noinline) UBOOL FVector::operator!=(const FVector &V) const
{
    return X != V.X || Y != V.Y || Z != V.Z;
}

extern const TCHAR EmptyString[]; // L""

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? Data : EmptyString; }
};

// RVA 0x92ec0. Case-insensitive string inequality, strings passed by value.
// Unnamed free function.
UBOOL StringsDiffer_92ec0(FString A, FString B)
{
    return appStricmp(*A, *B) != 0;
}

// Unnamed 8-byte key: an INT followed by two bytes.
struct UnnamedKey_92f40
{
    INT Value;
    BYTE A;
    BYTE B;
};

// RVA 0x92f40. Unnamed free function.
UBOOL KeysDiffer_92f40(UnnamedKey_92f40 X, UnnamedKey_92f40 Y)
{
    return X.Value != Y.Value || X.B != Y.B || X.A != Y.A;
}

// Scaffolding for the LTCG link, not part of the unit. __declspec(noinline)
// above stands in for retail call sites the LTCG inliner declined.
void Driver_92dc0(AActor *A, AActor *B, AActor *C, INT X) { A->eventProbe13b(X); B->eventProbe13b(X + 1); C->eventProbe13b(0); }
void Driver_92e70(AActor *A, AActor *B, AActor *C, INT X) { A->eventProbe144(X); B->eventProbe144(X + 1); C->eventProbe144(0); }
UBOOL Driver_92e20(const FRotator *A, const FRotator *B, const FRotator *C, const FRotator *D) { return (*A != *B) + (*C != *D) + (*B != *C) + (*D != *A); }
UBOOL Driver_92e40(const FVector *A, const FVector *B, const FVector *C, const FVector *D) { return (*A != *B) + (*C != *D) + (*B != *C) + (*D != *A); }
