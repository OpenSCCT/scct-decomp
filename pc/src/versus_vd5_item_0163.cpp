// Work item w3 0163: Versus RVA 0xca9b0-0xcacc5 (LTCG object).
//   0xca9b0 implicit copy constructor of an unnamed record of FStrings
//           (this on stack, Other in EBX)
//   0xcaa40 UNetPendingLevel member (NetDriver at 0xec; neutral name)
//   0xcaac0 UNetPendingLevel::SendJoin-style: Connection->Logf("JOIN"), FlushNet
//   0xcab00 script event thunk with one BYTE parameter (this in ESI, byte in AL)
//   0xcab30 constructor (this on stack). NOT matched: retail keeps an EH frame
//           (16-state unwind map) with every state store removed; VC7.0 LTCG
//           here either drops the frame (callees seen as nothrow) or keeps the
//           stores (callees external). Its unwind map also shows 8-byte members
//           at 0xe8/0xf0 and 0x124/0x12c that this layout does not model yet.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef char *va_list;
typedef unsigned int size_t;

#pragma pack(push, 4) // UE2 packs its classes to 4 bytes

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *Dest, size_t Count, const TCHAR *Fmt, va_list Args);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *A, const TCHAR *B);
extern "C" size_t __cdecl wcslen(const TCHAR *S);
void appMemcpy(void *Dest, const void *Src, INT Count);

extern const TCHAR FArray_ProtectedCstorTag[];
extern const TCHAR Text_FStringAssign[];  // L"FString::="
extern const TCHAR Text_FArray[];         // L"FArray"
extern const TCHAR Text_Empty[];          // L"" (0x10c10928)

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_ProtectedCstorTag);
    }
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);                // RVA 0x44e0
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    // Retail 0xc550 for FString (Other in EDI, this on stack).
    TArray(const TArray &Other) : FArray(Other.ArrayNum, sizeof(T))
    {
        ArrayNum = 0;
        for (INT i = 0; i < Other.ArrayNum; i++)
            new (*this) T(((T *)Other.Data)[i]);
    }
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1);
};

template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    FString(const FString &Other); // RVA 0x4640
    ~FString();                    // RVA 0x48b0
    FString &operator=(const TCHAR *Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : Text_Empty; }
};

#pragma auto_inline(off)
// Retail 0x4750 (this in ESI, Other in EDI); defined for its convention.
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != (const TCHAR *)Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), Text_FStringAssign);
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), Text_FArray);
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}
#pragma auto_inline(on)

// ---------------------------------------------------------------- 0xca9b0
// Record type not identified (neutral name).
struct UnnamedRecord_ca9b0
{
    FString A;              // 0x00
    FString B;              // 0x0c
    INT C;                  // 0x18
    FString D;              // 0x1c
    TArray<FString> E;      // 0x28
    FString F;              // 0x34
    INT G;                  // 0x40
};

// ---------------------------------------------------------------- objects
enum EName { NAME_Log = 0x24c, NAME_Unnamed_1411 = 0x1411 };

class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
};

class UFunction;

class UObject
{
public:
    virtual ~UObject();
    virtual void Vf04();
    virtual void Vf08();
    virtual void Vf0c();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    BYTE PadObj[0x24];
    UFunction *FindFunctionChecked(FName InName, INT Global = 0); // retail 0x16830
};

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
    virtual void Flush();
    void Logf(const TCHAR *Fmt, ...);
};

extern UBOOL GLogFilterActive;
struct FLogFilter { INT Pad[1]; DWORD Flags; };
struct FLogOwner { unsigned char Pad[0x930]; FLogFilter *Filter; };
extern FLogOwner *GLogOwner;
extern TCHAR GCmdLine[];
extern const TCHAR Text_LogFlushParam[];
extern const TCHAR Text_Logf[];
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);

#pragma auto_inline(off)
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
    {
        while ((Start = appStrfind(Start + 1, Param)) != 0)
        {
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
        }
    }
    return 0;
}

// Retail 0x118d0 (`this` in EBX); approximation defined for its convention.
void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    if (!GLogFilterActive || !(GLogOwner->Filter->Flags & 0x1000))
    {
        TCHAR *Buffer = (TCHAR *)GMalloc->Malloc(0x10000, Text_Logf);
        _vsnwprintf(Buffer, 0x8000, Fmt, (va_list)&Fmt + sizeof(Fmt));
        Serialize(Buffer, NAME_Log);
        GMalloc->Free(Buffer);
    }
    if (!ParseParam(GCmdLine, Text_LogFlushParam))
        Flush();
}
#pragma auto_inline(on)

class UNetObjectBase
{
public:
    virtual void Vf00(); virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54(); virtual void Vf58(); virtual void Vf5c();
    virtual void Vf60(); virtual void Vf64(); virtual void Vf68();
    virtual void Vf6c();
    virtual void FlushNet(); // 0x70
    BYTE PadObj[0x24];
};

class UNetConnection : public UNetObjectBase, public FOutputDevice
{
public:
    BYTE Pad2c[0x6c - 0x2c];
    INT State;              // 0x6c
};

class UNetDriver
{
public:
    virtual void Vf00(); virtual void Vf04(); virtual void Vf08(); virtual void Vf0c();
    virtual void Vf10(); virtual void Vf14(); virtual void Vf18(); virtual void Vf1c();
    virtual void Vf20(); virtual void Vf24(); virtual void Vf28(); virtual void Vf2c();
    virtual void Vf30(); virtual void Vf34(); virtual void Vf38(); virtual void Vf3c();
    virtual void Vf40(); virtual void Vf44(); virtual void Vf48(); virtual void Vf4c();
    virtual void Vf50(); virtual void Vf54(); virtual void Vf58(); virtual void Vf5c();
    virtual void Vf60(); virtual void Vf64(); virtual void Vf68();
    virtual void Vf6c();
    virtual void Vf70(void *Arg);
    BYTE Pad4[0x38 - 4];
    UNetConnection *ServerConnection; // 0x38
};

extern const TCHAR Text_c92534[];  // compared string (retail 0x10c92534)
extern const TCHAR Text_c4d89c[];  // replacement string (retail 0x10c4d89c)
extern const TCHAR Text_JOIN[];    // L"JOIN" (retail 0x10c4d8c0)

// Pending level; layout by offsets (neutral name for the methods).
class UNetPendingLevel
{
public:
    BYTE Pad4[0xec - 4];
    UNetDriver *NetDriver;  // 0xec
    BYTE Padf0[0x140 - 0xf0];
    UBOOL bSentJoin;        // 0x140
    BYTE Pad144[0x148 - 0x144];
    FString ConnectionError; // 0x148
    virtual void Unnamed_caa40(void *Arg);
    virtual void SendJoin();
};

// 0xcaa40
void UNetPendingLevel::Unnamed_caa40(void *Arg)
{
    INT State = NetDriver->ServerConnection->State;
    if ((State == 1 || State == 4) && _wcsicmp(*ConnectionError, Text_c92534) == 0) {
        ConnectionError = Text_c4d89c;
        return;
    }
    NetDriver->Vf70(Arg);
    NetDriver->Vf6c();
}

// 0xcaac0
void UNetPendingLevel::SendJoin()
{
    bSentJoin = 1;
    NetDriver->ServerConnection->Logf(Text_JOIN);
    NetDriver->ServerConnection->FlushNet();
}

// 0xcab00
class UnnamedObject_cab00 : public UObject
{
public:
    void eventUnnamed_1411(BYTE B);
};

#pragma auto_inline(off)
void UnnamedObject_cab00::eventUnnamed_1411(BYTE B)
{
    struct { BYTE B; } Parms;
    Parms.B = B;
    ProcessEvent(FindFunctionChecked(NAME_Unnamed_1411), &Parms);
}
#pragma auto_inline(on)

// ---------------------------------------------------------------- 0xcab30
// Classes not identified (neutral names, named after their vtables or
// constructors). The handle-like members carry a 64-bit serial built from a
// global counter (retail 0x10c96930) and a per-class tag.
struct FVector { float X, Y, Z; };
extern FVector *GUnnamedVector_ccacc4;
extern FVector *GUnnamedVector_ccacc0;
extern unsigned __int64 GUnnamedSerial_c96930;

class UnnamedHandle_cda60      // vtable 0x10c04898, constructor 0xcda60
{
public:
    TArray<INT> Items;          // 0x04
    unsigned __int64 Serial;    // 0x10
    INT Extra;                  // 0x18
    UnnamedHandle_cda60();
    virtual ~UnnamedHandle_cda60();
};

class UnnamedHandle_1128d0     // vtable 0x10c037ac, constructor 0x1128d0
{
public:
    TArray<INT> Items;
    unsigned __int64 Serial;
    INT Extra;
    UnnamedHandle_1128d0();
    virtual ~UnnamedHandle_1128d0();
};

class UnnamedHandle_48e4 : public UnnamedHandle_1128d0 // vtable 0x10c048e4
{
public:
    UnnamedHandle_48e4() {}
    virtual ~UnnamedHandle_48e4();
};

class UnnamedHandle_1126e0     // vtable 0x10c037f4, constructor 0x1126e0
{
public:
    TArray<INT> Items;
    unsigned __int64 Serial;
    INT Extra;
    UnnamedHandle_1126e0();
    virtual ~UnnamedHandle_1126e0();
};

class UnnamedList_48e0         // vtable 0x10c048e0
{
public:
    INT A;                      // 0x04
    INT B;                      // 0x08
    TArray<INT> Items;          // 0x0c
    UnnamedList_48e0() : A(0), B(0) {}
    virtual ~UnnamedList_48e0();
};

#pragma auto_inline(off)
UnnamedHandle_cda60::UnnamedHandle_cda60()
{
    Serial = GUnnamedSerial_c96930++ * 0x100 + 0xe1;
    Extra = 0;
}
UnnamedHandle_1128d0::UnnamedHandle_1128d0()
{
    Serial = GUnnamedSerial_c96930++ * 0x100 + 0xe1;
    Extra = 0;
}
UnnamedHandle_1126e0::UnnamedHandle_1126e0()
{
    Serial = GUnnamedSerial_c96930++ * 0x100 + 0xe2;
    Extra = 0;
}
#pragma auto_inline(on)

class UObjectBase
{
public:
    virtual ~UObjectBase();
    BYTE PadObj[0x24];
};

class UnnamedBase_cab30 : public UObjectBase // vtable 0x10c0bae8
{
public:
    FVector VecA;               // 0x28
    FVector VecB;               // 0x34
    INT Int40, Int44, Int48, Int4c;
    UnnamedBase_cab30()
        : VecA(*GUnnamedVector_ccacc4), VecB(*GUnnamedVector_ccacc0),
          Int40(0), Int44(0), Int48(0), Int4c(0) {}
    virtual ~UnnamedBase_cab30();
};

class UnnamedClass_cab30 : public UnnamedBase_cab30 // vtable 0x10c04820
{
public:
    TArray<INT> Array50;        // 0x50
    UnnamedHandle_cda60 Handle5c;   // 0x5c
    UnnamedHandle_48e4 Handle78;    // 0x78
    UnnamedHandle_48e4 Handle94;    // 0x94
    TArray<INT> ArrayB0;        // 0xb0
    INT IntBC;                  // 0xbc
    UnnamedHandle_1126e0 HandleC0;  // 0xc0
    TArray<INT> ArrayDC;        // 0xdc
    TArray<INT> ArrayE8;        // 0xe8
    TArray<INT> ArrayF4;        // 0xf4
    INT Int100;                 // 0x100
    INT Int104;                 // 0x104 (not initialised)
    UnnamedHandle_cda60 Handle108;  // 0x108
    TArray<INT> Array124;       // 0x124
    TArray<INT> Array130;       // 0x130
    INT Int13c;                 // 0x13c
    FVector Vec140;             // 0x140 (not initialised)
    UnnamedList_48e0 List14c;   // 0x14c
    UnnamedList_48e0 List164;   // 0x164
    INT Pad17c[4];              // 0x17c (not initialised)
    INT Int18c;                 // 0x18c
    INT Int190;                 // 0x190
    UnnamedClass_cab30() : IntBC(0), Int100(0), Int13c(0), Int18c(0), Int190(0) {}
    virtual ~UnnamedClass_cab30();
};

void *operator new(unsigned int Size, const TCHAR *Tag);
extern const TCHAR Text_UnnamedTag[];

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
struct UnnamedHolder_ca9b0 { BYTE Pad[0xcc]; UnnamedRecord_ca9b0 Rec; };
void UseRecord(UnnamedRecord_ca9b0 R, INT A, void *B);
void Driver_ca9b0(UnnamedHolder_ca9b0 *H, UnnamedHolder_ca9b0 *H2)
{
    Escape(&GMalloc);
    FString S;
    Escape(&S);
    UseRecord(H->Rec, 0, &S);
    UnnamedRecord_ca9b0 Local = H2->Rec;
    Escape(&Local);
    UseRecord(H2->Rec, 0, &Local);
}
TArray<FString> Driver_c550(TArray<FString> &L)
{
    Escape(&GMalloc);
    return L;
}
void Driver_caa40()
{
    UNetPendingLevel Local;   // references the vtable so the virtuals are kept
    Escape(&Local);
}
void Driver_cab00(UnnamedObject_cab00 *O, BYTE B) { O->eventUnnamed_1411(B); }
void Driver_cab30()
{
    Escape(new(Text_UnnamedTag) UnnamedClass_cab30);
}
