// Work item 0344: Versus RVA 0x110100-0x11050a.
//
// UnrealScript event thunks (UE2 generated-header shape) on an unnamed
// UObject subclass, plus the destructor of one parameter block. The object
// was built with /GL and linked with /LTCG: the thunks take `this` on the
// stack, the TArray copy (retail 0x100b0) takes `this` in ESI and the source
// in EDI, and the TArray destructor (retail 0x7bf30) takes `this` on the
// stack. Event names are not recovered: the FName indices are retail values.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayMax = 0;
        ArrayNum = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
    void Realloc(INT ElementSize);

    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    void Remove(INT Index, INT Count = 1)
    {
        FArray::Remove(Index, Count, sizeof(T));
    }
    __declspec(noinline) TArray &operator=(const TArray &Other)
    {
        if (this != &Other)
        {
            ArrayNum = 0;
            ArrayMax = Other.ArrayNum;
            Realloc(sizeof(T));
            for (INT i = 0; i < Other.ArrayNum; i++)
                ((T *)Data)[ArrayNum++] = ((T *)Other.Data)[i];
        }
        return *this;
    }
};

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    ~FString();
    FString &operator=(const FString &Other);
};

enum EName
{
    NAME_Unnamed_13ff = 0x13ff,  // names not recovered
    NAME_Unnamed_1400 = 0x1400,
    NAME_Unnamed_1401 = 0x1401,
    NAME_Unnamed_1402 = 0x1402,
    NAME_Unnamed_1403 = 0x1403,
};

class FName
{
public:
    FName(EName N) : Index(N) {}
    INT Index;
};

class UFunction;

class UObject
{
public:
    virtual ~UObject();
    virtual void V1();
    virtual void V2();
    virtual void V3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0); // slot 4
    UFunction *FindFunctionChecked(FName Name, UBOOL Global = 0);                   // retail 0x16830
};

// Unnamed UObject subclass (no class name recovered).
class UnnamedClass_110100 : public UObject
{
public:
    void event_1402(TArray<INT> Data, INT Value);
    void event_1401(TArray<INT> Data, INT Value);
    void event_1403(TArray<INT> Data, INT Value);
    INT event_1400(TArray<INT> Data, BYTE &A, BYTE &B, INT Value);
    INT event_13ff(TArray<INT> Data, BYTE &A, const FString &S);
};

struct FParms_1402
{
    TArray<INT> Data;
    INT Value;
};

// Retail 0x1104c0: parameter block destructor (this on the stack).
struct FParms_13ff
{
    TArray<INT> Data;
    BYTE A;
    FString S;
    INT ReturnValue;
    __declspec(noinline) ~FParms_13ff() {}
};

// Retail 0x110100.
__declspec(noinline) void UnnamedClass_110100::event_1402(TArray<INT> Data, INT Value)
{
    FParms_1402 Parms;
    Parms.Data = Data;
    Parms.Value = Value;
    ProcessEvent(FindFunctionChecked(NAME_Unnamed_1402), &Parms);
}

// Retail 0x1101b0.
__declspec(noinline) void UnnamedClass_110100::event_1401(TArray<INT> Data, INT Value)
{
    FParms_1402 Parms;
    Parms.Data = Data;
    Parms.Value = Value;
    ProcessEvent(FindFunctionChecked(NAME_Unnamed_1401), &Parms);
}

// Retail 0x110260.
__declspec(noinline) void UnnamedClass_110100::event_1403(TArray<INT> Data, INT Value)
{
    FParms_1402 Parms;
    Parms.Data = Data;
    Parms.Value = Value;
    ProcessEvent(FindFunctionChecked(NAME_Unnamed_1403), &Parms);
}

// Retail 0x110310.
__declspec(noinline) INT UnnamedClass_110100::event_1400(TArray<INT> Data, BYTE &A, BYTE &B, INT Value)
{
    struct FParms_1400
    {
        TArray<INT> Data;
        BYTE A;
        BYTE B;
        INT Value;
        INT ReturnValue;
    } Parms;
    Parms.ReturnValue = 0;
    Parms.Data = Data;
    Parms.A = A;
    Parms.B = B;
    Parms.Value = Value;
    ProcessEvent(FindFunctionChecked(NAME_Unnamed_1400), &Parms);
    A = Parms.A;
    B = Parms.B;
    return Parms.ReturnValue;
}

// Retail 0x1103e0.
__declspec(noinline) INT UnnamedClass_110100::event_13ff(TArray<INT> Data, BYTE &A, const FString &S)
{
    struct FParms_13ff_Local
    {
        TArray<INT> Data;
        BYTE A;
        FString S;
        INT ReturnValue;
    } Parms;
    Parms.ReturnValue = 0;
    Parms.Data = Data;
    Parms.A = A;
    Parms.S = S;
    ProcessEvent(FindFunctionChecked(NAME_Unnamed_13ff), &Parms);
    A = Parms.A;
    return Parms.ReturnValue;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_110100(UnnamedClass_110100 *O, TArray<INT> *D, BYTE *A, BYTE *B, FString *S, INT V)
{
    Escape(&GMalloc);
    O->event_1402(*D, V);
    O->event_1401(*D, V);
    O->event_1403(*D, V);
    V = O->event_1400(*D, *A, *B, V);
    O->event_13ff(*D, *A, *S);
}
void Driver_1104c0(FParms_13ff *P) { Escape(&GMalloc); P->~FParms_13ff(); }
