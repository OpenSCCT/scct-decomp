// Work item 0218: Versus RVA 0xedb20-0xedc7c.
//   0xedb20 UGameEngine vtable slot 33 (name not recovered: Slot33_edb20)
//   0xedb80 UGameEngine vtable slot 34 (name not recovered: Slot34_edb80)
//   0xedba0 TMapBase<FString,FString>::operator= (LTCG: this ESI, Other EAX)
//   0xedbc0 TMap<FString,FString>::Set (LTCG: this EBX)
//   0xedc40 ConstructObject<T> with StaticConstructObject inlined (LTCG:
//           Class EDI, Outer EAX, SetFlags EDX, Name on the stack)

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

DWORD appStrihash(const TCHAR *Data);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *A, const TCHAR *B);
extern const TCHAR EmptyString[];   // L"" shared in retail

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);                 // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);              // RVA 0x4550
};

class FString : public FArray
{
public:
    FString(const FString &Other);                       // RVA 0x4640
    ~FString();                                          // RVA 0x48b0
    FString &operator=(const TCHAR *Other);              // RVA 0x4750
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : EmptyString; }
    UBOOL operator==(const TCHAR *Other) const { return _wcsicmp(**this, Other) == 0; }
};

struct TPairStringString
{
    INT HashNext;
    FString Key;
    FString Value;
    TPairStringString(const TPairStringString &Other);   // RVA 0x151f0
    ~TPairStringString();                                // RVA 0x14e00
};

class TPairStringStringArray : public FArray
{
public:
    TPairStringString &operator()(INT i) const { return ((TPairStringString *)Data)[i]; }
    TPairStringStringArray &operator=(const TPairStringStringArray &Other);   // RVA 0x150f0
    void Empty(INT Slack);                                                   // RVA 0x149f0
};

// TMapBase<FString,FString>
class TMapBaseStringString
{
public:
    TPairStringStringArray Pairs;
    INT *Hash;
    INT HashCount;
    void Rehash();                                       // RVA 0x14850
    FString &Add(const TCHAR *InKey, const TCHAR *InValue);   // RVA 0x14900
    TMapBaseStringString &operator=(const TMapBaseStringString &Other);
    FString &Set(const TCHAR *InKey, const TCHAR *InValue);
};

// RVA 0xedba0
__declspec(noinline) TMapBaseStringString &TMapBaseStringString::operator=(const TMapBaseStringString &Other)
{
    Pairs = Other.Pairs;
    HashCount = Other.HashCount;
    Rehash();
    return *this;
}

// RVA 0xedbc0
FString &TMapBaseStringString::Set(const TCHAR *InKey, const TCHAR *InValue)
{
    for (INT i = Hash[appStrihash(InKey) & (HashCount - 1)]; i != -1; )
    {
        TPairStringString &Pair = Pairs(i);
        if (Pair.Key == InKey)
        {
            Pair.Value = InValue;
            return Pair.Value;
        }
        i = Pair.HashNext;
    }
    return Add(InKey, InValue);
}

// ---- Objects ----
class FOutputDevice;
extern FOutputDevice *GError;
class UClass;
struct FName
{
    INT Index;
};

class UObject
{
public:
    virtual ~UObject();
    static UObject *StaticAllocateObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                                         UObject *Template, FOutputDevice *Error, UObject *Ptr,
                                         UObject *SubobjectRoot);    // RVA 0x1d380
    static UObject *StaticConstructObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                                          UObject *Template, FOutputDevice *Error, UObject *SubobjectRoot);
    static UObject *GObjTransientPkg;
};

class UClass : public UObject
{
public:
    DWORD Pad[(0x104 - 0x4) / 4];
    void (*ClassConstructor)(void *);       // +0x104
};

inline UObject *UObject::StaticConstructObject(UClass *InClass, UObject *InOuter, FName InName, DWORD SetFlags,
                                               UObject *InTemplate, FOutputDevice *Error, UObject *SubobjectRoot)
{
    UObject *Result = StaticAllocateObject(InClass, InOuter, InName, SetFlags, InTemplate, Error, 0, SubobjectRoot);
    if (Result)
        (*InClass->ClassConstructor)(Result);
    return Result;
}

// RVA 0xedc40
__declspec(noinline) UObject *ConstructObject(UClass *Class, UObject *Outer, FName Name, DWORD SetFlags)
{
    if (Outer == (UObject *)-1)
        Outer = UObject::GObjTransientPkg;
    return UObject::StaticConstructObject(Class, Outer, Name, SetFlags, 0, GError, 0);
}

// ---- UGameEngine vtable slots 33 and 34 (names not recovered) ----
// Viewport (Client->Viewports(0)); slot 0x98 not recovered.
class UnnamedViewport_edb20
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c(); virtual void V10(); virtual void V14();
    virtual void V18(); virtual void V1c(); virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c(); virtual void V40(); virtual void V44();
    virtual void V48(); virtual void V4c(); virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6c(); virtual void V70(); virtual void V74();
    virtual void V78(); virtual void V7c(); virtual void V80(); virtual void V84(); virtual void V88(); virtual void V8c();
    virtual void V90(); virtual void V94();
    virtual UBOOL Slot98();
};
class UnnamedClient_edb20
{
public:
    DWORD Pad[0x2c / 4];
    UnnamedViewport_edb20 **ViewportsData;   // +0x2c Viewports TArray
    INT ViewportsNum;                        // +0x30
    UnnamedViewport_edb20 *Viewport(INT i) { return ViewportsData[i]; }
};
// Object at UGameEngine+0x130; its method at RVA 0x130c80 not recovered.
class UnnamedObject130_edb20
{
public:
    UBOOL Check_130c80();
};
// First argument of slot 33; slot 0xbc not recovered.
class UnnamedArg_edb20
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c(); virtual void V10(); virtual void V14();
    virtual void V18(); virtual void V1c(); virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c(); virtual void V40(); virtual void V44();
    virtual void V48(); virtual void V4c(); virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6c(); virtual void V70(); virtual void V74();
    virtual void V78(); virtual void V7c(); virtual void V80(); virtual void V84(); virtual void V88(); virtual void V8c();
    virtual void V90(); virtual void V94(); virtual void V98(); virtual void V9c(); virtual void Va0(); virtual void Va4();
    virtual void Va8(); virtual void Vac(); virtual void Vb0(); virtual void Vb4(); virtual void Vb8();
    virtual void SlotBC(INT A, INT B, INT C);
    DWORD Pad[(0x38 - 4) / 4];
    DWORD Flags;                             // +0x38
};

class UGameEngine
{
public:
    DWORD Pad0[0x30 / 4];
    UnnamedClient_edb20 *Client;             // +0x30
    DWORD Pad1[(0x130 - 0x34) / 4];
    UnnamedObject130_edb20 *Obj130;          // +0x130
    void Slot33_edb20(UnnamedArg_edb20 *Arg, DWORD Flags, INT A, INT B);
    void Slot34_edb80(UnnamedArg_edb20 *Arg, DWORD Flags, INT A, INT B);
};

// RVA 0xedb20
void UGameEngine::Slot33_edb20(UnnamedArg_edb20 *Arg, DWORD Flags, INT A, INT B)
{
    if ((Flags & 8) && Client && Client->ViewportsNum == 1 && Obj130
        && !Client->Viewport(0)->Slot98() && !Obj130->Check_130c80() && !(Arg->Flags & 2))
        Arg->SlotBC(1, 1, 1);
}

// RVA 0xedb80
struct UnnamedTarget_edb80
{
    DWORD Pad[0x3c / 4];
    INT X;                                   // +0x3c
    INT Y;                                   // +0x40
};
void UGameEngine::Slot34_edb80(UnnamedArg_edb20 *Arg, DWORD Flags, INT A, INT B)
{
    UnnamedTarget_edb80 *T = (UnnamedTarget_edb80 *)Arg;
    if (T)
    {
        T->X = A;
        T->Y = B;
    }
}

// Scaffolding for the LTCG link, not part of the unit: callees retail
// compiled into the same LTCG module, given bodies so the linker picks
// their register conventions.
void Escape(void *);
extern "C" unsigned int __cdecl wcslen(const TCHAR *);
void appMemcpy(void *Dest, const void *Src, INT Count);
INT FArray_Add(FArray *A, INT Count, INT ElementSize);
void FArray_Empty(FArray *A, INT ElementSize, INT Slack);
void TPair_Construct(void *Mem, const TCHAR *K, const TCHAR *V);
__declspec(noinline) FString &FString::operator=(const TCHAR *Other)
{
    if (Other != (const TCHAR *)Data) {
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
inline void *operator new(unsigned int Size, TPairStringStringArray &Array)
{
    INT Index = Array.Add(1, Size);
    return &Array(Index);
}
__declspec(noinline) TPairStringStringArray &TPairStringStringArray::operator=(const TPairStringStringArray &Other)
{
    if (this != &Other)
    {
        Empty(Other.ArrayNum);
        for (INT i = 0; i < Other.ArrayNum; i++)
            new(*this) TPairStringString(Other(i));
    }
    return *this;
}
TPairStringString::TPairStringString(const TPairStringString &Other)
    : HashNext(Other.HashNext), Key(Other.Key), Value(Other.Value)
{
}
void TPairStringStringArray::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~TPairStringString();
    FArray::Empty(sizeof(TPairStringString), Slack);
}
extern DWORD GCRCTable[256];
TCHAR appToUpper(TCHAR c);
__declspec(noinline) DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data)
    {
        TCHAR Ch = appToUpper(*Data++);
        unsigned char B = (unsigned char)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (unsigned char)(Ch >> 8);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}
__declspec(noinline) void TMapBaseStringString::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.ArrayNum; i++)
    {
        TPairStringString &Pair = Pairs(i);
        INT iHash = appStrihash(*Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}
__declspec(noinline) FString &TMapBaseStringString::Add(const TCHAR *InKey, const TCHAR *InValue)
{
    INT Index = FArray_Add(&Pairs, 1, sizeof(TPairStringString));
    TPairStringString &Pair = Pairs(Index);
    TPair_Construct(&Pair, InKey, InValue);
    INT iHash = appStrihash(*Pair.Key) & (HashCount - 1);
    Pair.HashNext = Hash[iHash];
    Hash[iHash] = Pairs.ArrayNum - 1;
    if (HashCount * 2 + 8 < Pairs.ArrayNum)
    {
        HashCount *= 2;
        Rehash();
    }
    return Pair.Value;
}
void Driver_edba0(TMapBaseStringString *A, const TMapBaseStringString *B, TMapBaseStringString *C)
{
    Escape(&GMalloc);
    Escape(&(*A = *B));
    Escape(&(*C = *A));
}
void Driver_edbc0(TMapBaseStringString *M, const TCHAR *K, const TCHAR *V)
{
    Escape(&GMalloc);
    Escape(&M->Set(K, V));
    Escape(&M->Set(V, K));
}
UObject *Driver_edc40(UClass *C, UObject *O, FName N, DWORD F)
{
    Escape(&UObject::GObjTransientPkg); Escape(&GError);
    Escape(ConstructObject(C, O, N, F));
    Escape(ConstructObject(C, (UObject *)-1, N, F | 1));
    return ConstructObject(C, O, N, 0);
}
