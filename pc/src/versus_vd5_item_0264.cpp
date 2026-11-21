/* Work item 0264: Versus RVA 0xf8240-0xf8443. These functions were compiled
   with /GL and linked with /LTCG (custom register conventions); check with
   try_ltcg.py and the drivers at the end of the file. */
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

extern "C" double pow(double, double);
#pragma intrinsic(pow)

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag) = 0;
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag) = 0;
    virtual void Free(void* Original) = 0;
};
extern FMalloc* GMalloc;

template<class T> class TArray
{
public:
    T* Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T& operator()(INT i) { return Data[i]; }
    void Empty()
    {
        ArrayNum = 0;
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

class UClass;
class UField;

class UObject
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void PostLoad();
    INT Index;
    UObject* HashNext;
    void* StateFrame;
    void* _Linker;
    INT _LinkerIndex;
    UObject* Outer;
    DWORD ObjectFlags;
    INT Name;
    UClass* Class;
    UBOOL IsA(UClass* SomeBase) const;
};

class UField : public UObject
{
public:
    UField* SuperField;
};

class UClass : public UField
{
};

inline UBOOL UObject::IsA(UClass* SomeBase) const
{
    for (UClass* TempClass = Class; TempClass; TempClass = (UClass*)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

/* ---------------------------------------------------------------------------
   RVA 0xf8410: an object iterator's operator++ (TObjectIterator style), the
   iterator in EAX. The class it filters for is a global class object at
   0x10cc0848 whose name is not recovered. */
extern UClass UnnamedClass_10cc0848;

class FUnnamedObjectIterator_f8410
{
public:
    TArray<UObject*>* Array;
    INT Index;
    FUnnamedObjectIterator_f8410& operator++();
};

FUnnamedObjectIterator_f8410& FUnnamedObjectIterator_f8410::operator++()
{
    while (++Index < Array->Num() && (!(*Array)(Index) || !(*Array)(Index)->IsA(&UnnamedClass_10cc0848)))
        ;
    return *this;
}
/* ---------------------------------------------------------------------------
   RVA 0xf82a0: pow(Base, Value*Value) over a byte table [N][64] at +0x3a68.
   Row arrives in EAX, the object in ECX. Neutral names. */
class UnnamedClass_f82a0
{
public:
    BYTE Pad[0x3a68];
    BYTE Table[1][64];
    // Retail callers live in other objects; noinline stands in for them.
    __declspec(noinline) FLOAT Scale(INT Row, INT Col, FLOAT Base);
};

FLOAT UnnamedClass_f82a0::Scale(INT Row, INT Col, FLOAT Base)
{
    INT V = Table[Row][Col];
    return (FLOAT)pow(Base, (double)(V * V));
}

/* ---------------------------------------------------------------------------
   RVA 0xf82d0: empties an array member at +0x3a3c, asks a sub-object at
   +0x39e8 to fill it and returns it. The object arrives in EAX. Neutral names;
   the third argument is not read but retail still pops it (ret 0xc). */
class UnnamedSub_a7a930
{
public:
    INT Count;
    __declspec(noinline) void Collect(INT A, INT B, TArray<INT>* Out);
};

class UnnamedClass_f82d0
{
public:
    BYTE Pad[0x39e8];
    UnnamedSub_a7a930 Sub;
    BYTE Pad2[0x3a3c - 0x39e8 - sizeof(UnnamedSub_a7a930)];
    TArray<INT> Results;
    __declspec(noinline) TArray<INT>& Gather(INT A, INT B, INT Unused);
};

TArray<INT>& UnnamedClass_f82d0::Gather(INT A, INT B, INT Unused)
{
    Results.Empty();
    Sub.Collect(A, B, &Results);
    return Results;
}

/* ---------------------------------------------------------------------------
   RVA 0xf8330: forwards to one of two handlers depending on whether the
   object at +0xec has a delegate at +0x38. Owner in EAX, the two forwarded
   arguments in ECX and EDX. Neutral names. */
class UnnamedDelegate_f8330
{
public:
    __declspec(noinline) INT Handle(void* A, void* B);
};

class UnnamedTarget_f8330
{
public:
    BYTE Pad[0x38];
    UnnamedDelegate_f8330* Delegate;

    __declspec(noinline) INT DefaultHandle(void* A, void* B, INT Flags);
};

class UnnamedOwner_f8330
{
public:
    BYTE Pad[0xec];
    UnnamedTarget_f8330* Target;
};

__declspec(noinline) INT UnnamedDispatch_f8330(UnnamedOwner_f8330* Owner, void* B, void* A)
{
    UnnamedTarget_f8330* T = Owner->Target;
    if (T)
    {
        if (!T->Delegate)
            return T->DefaultHandle(A, B, 0);
        if (T->Delegate)
            return T->Delegate->Handle(A, B);
    }
    return 0;
}

/* ---------------------------------------------------------------------------
   RVA 0xf8390: ULevelSummary::PostLoad (vtable slot 8 of ULevelSummary).
   UObject::PostLoad is inlined: it sets flag 0x20000000 and, when the object
   still has 0x100 set, calls the helper at 0x16f70 (this in ESI). */
class FString : public TArray<TCHAR>
{
public:
    __declspec(noinline) FString& operator=(const TCHAR* Other);
};

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry* HashNext;
    TCHAR Name[64];
};
extern TArray<FNameEntry*> FName_Names; // FName::Names

class UObjectPL : public UObject
{
public:
    __declspec(noinline) void UnnamedPostLoadHelper_16f70();
    const TCHAR* GetName() const { return FName_Names(Name)->Name; }
    UObjectPL* GetOuter() const { return (UObjectPL*)Outer; }
    void PostLoad()
    {
        ObjectFlags |= 0x20000000;
        if (ObjectFlags & 0x100)
            UnnamedPostLoadHelper_16f70();
    }
};

__declspec(noinline) const TCHAR* Localize(const TCHAR* Section, const TCHAR* Key, const TCHAR* Package, const TCHAR* LangExt, UBOOL Optional);
extern const TCHAR TEXT_LevelInfo0[]; // L"LevelInfo0"
extern const TCHAR TEXT_Title[];      // L"Title"

class ULevelSummary : public UObjectPL
{
public:
    FString Title;
    virtual void PostLoad();
};

void ULevelSummary::PostLoad()
{
    UObjectPL::PostLoad();
    const TCHAR* Text = Localize(TEXT_LevelInfo0, TEXT_Title, GetOuter()->GetName(), 0, 1);
    if (*Text)
        Title = Text;
}

/* ---------------------------------------------------------------------------
   RVA 0xf8240: a mode switch. Modes 0 and 2 ask the component at +0x13c
   (0x141ef0, this in EAX, the vector in ECX); mode 3 calls 0x11d200 on the
   object with a 56-byte scratch buffer and line 0x286; other modes return 1.
   The object arrives in ESI and the mode in EAX. Neutral names. */
struct FVector
{
    FLOAT X, Y, Z;
};

class UnnamedComponent_141ef0
{
public:
    BYTE Pad[0x54];
    INT Field54;
    INT Field58;
    BYTE Pad2[0x104 - 0x5c];
    BYTE Flag104;
    __declspec(noinline) BYTE Query(const FVector& V, INT Extra);
};

struct FUnnamedScratch_f8240
{
    BYTE Data[56];
};

extern INT GUnnamed_10ccacc0;

class UnnamedClass_f8240
{
public:
    BYTE Pad[0x13c];
    UnnamedComponent_141ef0* Component;
    INT Handle_11d200(FUnnamedScratch_f8240* Scratch, INT C, const FVector& V, INT B, INT Line, INT G);
    __declspec(noinline) INT Exec(INT Mode, const FVector& V, INT B, INT C);
};

INT UnnamedClass_f8240::Exec(INT Mode, const FVector& V, INT B, INT C)
{
    FUnnamedScratch_f8240 Scratch;
    switch (Mode)
    {
    case 0:
    case 2:
        return Component->Query(V, B);
    case 3:
        return Handle_11d200(&Scratch, C, V, B, 0x286, GUnnamed_10ccacc0);
    }
    return 1;
}

// Scaffolding for the link, not part of the unit.
void Escape(void*);
void Use(UObject*);
FUnnamedObjectIterator_f8410* GetIt(INT);
void Driver_f8410()
{
    ++(*GetIt(0)); ++(*GetIt(1)); ++(*GetIt(2)); ++(*GetIt(3)); ++(*GetIt(4)); ++(*GetIt(5));
    ++(*GetIt(6)); ++(*GetIt(7)); ++(*GetIt(8)); ++(*GetIt(9)); ++(*GetIt(10)); ++(*GetIt(11));
}
UnnamedClass_f82a0* GetObj_f82a0(INT);
INT GetInt(INT);
void UseF(FLOAT);
void Driver_f82a0(FLOAT B)
{
    UseF(GetObj_f82a0(0)->Scale(GetInt(0), GetInt(50), B));
    UseF(GetObj_f82a0(1)->Scale(GetInt(1), GetInt(51), B));
}
UnnamedClass_f82d0* GetObj_f82d0(INT);
void UseArr(TArray<INT>&);
void Driver_f82d0()
{
    Escape(&GMalloc);
    UseArr(GetObj_f82d0(0)->Gather(1, 2, 3));
    UseArr(GetObj_f82d0(1)->Gather(4, 5, 6));
}
// Stand-in body so the linker gives Collect its retail convention (this in EDI).
void Probe(INT, INT, void*);
INT Check(void*, void*, void*);
void UnnamedSub_a7a930::Collect(INT A, INT B, TArray<INT>* Out)
{
    INT Local[6];
    if (Count)
    {
        if (Check(Local, &Count, this))
            Probe(A, B, Local);
        for (INT i = Count; i < Count + 4; i++)
            Probe(i, Count, Local);
        Probe(Count, 0, Out);
    }
}
// Stand-in bodies for the two handlers (their retail conventions: all
// arguments on the stack; the delegate's this in ESI).
void Probe2(void*, void*);
INT Probe3(void*);
INT UnnamedTarget_f8330::DefaultHandle(void* A, void* B, INT Flags)
{
    INT Local[8];
    if (Probe3(Local))
    {
        Probe2(this, Local);
        Probe2(A, Local);
        if (Flags) Probe2(B, Local);
    }
    return Local[0];
}
INT UnnamedDelegate_f8330::Handle(void* A, void* B)
{
    INT Local[8];
    if (Probe3(this))
    {
        Probe2(this, Local);
        Probe2(A, Local);
        Probe2(B, this);
    }
    return Local[0];
}
UnnamedOwner_f8330* GetOwner_f8330(INT);
void* GetPtr(INT);
void UseI(INT);
void Driver_f8330()
{
    UseI(UnnamedDispatch_f8330(GetOwner_f8330(0), GetPtr(2), GetPtr(1)));
    UseI(UnnamedDispatch_f8330(GetOwner_f8330(3), GetPtr(5), GetPtr(4)));
}
// Stand-in bodies for the callees, so the linker gives them their retail
// conventions (Localize: LangExt in EAX, Key in EDI, Package in EBX;
// FString::operator=: this in ESI, Other in EDI; the hook: this in ESI).
extern "C" unsigned int wcslen(const TCHAR*);
void appMemcpy(void*, const void*, INT);
FString& FString::operator=(const TCHAR* Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) { ArrayNum = 0; ArrayMax = 0; GMalloc->Free(Data); Data = 0; }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR*)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), 0);
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR*)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), 0);
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}
class FConfigCache
{
public:
    virtual void S0();
    virtual void S1();
    virtual void S2();
    virtual const TCHAR* Get(const TCHAR* Section, INT Flags, const TCHAR* Key, const TCHAR* Filename);
};
extern DWORD GIsStarted;
extern FConfigCache* GConfig;
extern const TCHAR TEXT_DefaultLang[];
extern const TCHAR TEXT_Fmt[];
extern const TCHAR TEXT_int[];
extern const TCHAR TEXT_Empty[];
int appSprintf(TCHAR*, const TCHAR*, ...);
extern "C" int _wcsicmp(const TCHAR*, const TCHAR*);
const TCHAR* Localize(const TCHAR* Section, const TCHAR* Key, const TCHAR* Package, const TCHAR* LangExt, UBOOL Optional)
{
    if (!GIsStarted || !GConfig)
        return Key;
    if (!LangExt)
        LangExt = TEXT_DefaultLang;
    TCHAR Filename[256];
    for (;;)
    {
        appSprintf(Filename, TEXT_Fmt, Package, LangExt);
        if (const TCHAR* R = GConfig->Get(Section, 0, Key, Filename))
            return R;
        if (_wcsicmp(LangExt, TEXT_int) == 0)
            break;
        LangExt = TEXT_int;
    }
    return Optional ? TEXT_Empty : Key;
}
void UObjectPL::UnnamedPostLoadHelper_16f70()
{
    Probe3(Class);
    if (Index != -1 && (ObjectFlags & 0x100))
        Probe2(Outer, this);
    Probe2(this, Class);
}
inline void* operator new(unsigned int, void* Mem) { return Mem; }
ULevelSummary* GetSummary(INT);
void Driver_f8390()
{
    Escape(&FName_Names);
    new (GetPtr(9)) ULevelSummary;
    ((UObject*)GetSummary(0))->PostLoad();
    UseI((INT)Localize(TEXT_Fmt, TEXT_int, TEXT_Empty, (const TCHAR*)GetPtr(1), 0));
    FString S; S = (const TCHAR*)GetPtr(2); FString T; T = (const TCHAR*)GetPtr(3);
    UseArr(*(TArray<INT>*)&S); UseArr(*(TArray<INT>*)&T);
}
// Stand-in for the component query (its retail body, roughly), so the
// linker gives it its convention (this in EAX, the vector in ECX).
extern INT GUnnamed_10c8bc0c;
INT UnnamedTrace_141d90(INT Flags, FVector V, INT Extra, INT Flag);
BYTE UnnamedComponent_141ef0::Query(const FVector& V, INT Extra)
{
    GUnnamed_10c8bc0c = Field54;
    if (Field58)
        return (BYTE)UnnamedTrace_141d90(0, V, Extra, Flag104);
    return Flag104;
}
UnnamedClass_f8240* GetObj_f8240(INT);
FVector* GetVec(INT);
void Driver_f8240()
{
    Escape(&GUnnamed_10ccacc0);
    UseI(GetObj_f8240(0)->Exec(GetInt(0), *GetVec(1), GetInt(2), GetInt(3)));
    UseI(GetObj_f8240(1)->Exec(GetInt(4), *GetVec(5), GetInt(6), GetInt(7)));
    UseI(((UnnamedComponent_141ef0*)GetPtr(1))->Query(*GetVec(8), 3));
}
