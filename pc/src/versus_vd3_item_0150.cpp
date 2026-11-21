// Work item 0150: Versus RVA 0x402b0-0x40540 (Core: FArray, FString, UObject,
// UStruct helpers). Unreal Engine 2 builds with 4-byte structure packing (/Zp4).
//   0x402b0 FArray::InsertZeroed   LTCG: this on the stack, ret 0x10
//   0x40310 FString::Right         plain thiscall (vc70 /O2 /Gy /GX)
//   0x40370 FString::Caps          LTCG: this in ESI
//   0x40430 UObject event 0x13d    LTCG: this in ESI (neutral name)
//   0x40450 UObject::IsProbing     plain thiscall (vc70 /O2 /Gy)
//   0x404a0 UStruct::StructCompare LTCG: this in EAX, B in EBX
#pragma pack(push, 4)
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned __int64 QWORD;

extern TCHAR GEmptyTCHAR[]; // 0x10c10928, the empty string ""

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag) = 0;
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag) = 0;
    virtual void Free(void* Original) = 0;
};
extern FMalloc* GMalloc;
extern "C" __declspec(dllimport) void* __cdecl memmove(void* Dest, const void* Src, unsigned int Count);

inline void appMemzero(void* Dest, INT Count)
{
    BYTE* D = (BYTE*)Dest;
    for (INT i = 0; i < Count; i++) D[i] = 0;
}

inline TCHAR appToUpper(TCHAR c)
{
    return (c < 'a' || c > 'z') ? c : c - ('a' - 'A');
}

template<class T> inline T Clamp(T X, T Min, T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    __declspec(noinline) void Insert(INT Index, INT Count, INT ElementSize);
    __declspec(noinline) void InsertZeroed(INT Index, INT Count, INT ElementSize);
};

// RVA 0x4450, reproduced here only so the link gives it its EAX/EBX convention
// (matched separately in item_0003_ltcg).
void FArray::Insert(INT Index, INT Count, INT ElementSize)
{
    INT OldNum = ArrayNum;
    if ((ArrayNum += Count) > ArrayMax)
    {
        ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
        if (!Data)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, (const TCHAR*)L"FArray::Insert");
        else
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, (const TCHAR*)L"FArray");
    }
    memmove((BYTE*)Data + (Index + Count) * ElementSize,
            (BYTE*)Data + Index * ElementSize,
            (OldNum - Index) * ElementSize);
}

// RVA 0x402b0
void FArray::InsertZeroed(INT Index, INT Count, INT ElementSize)
{
    Insert(Index, Count, ElementSize);
    appMemzero((BYTE*)Data + Index * ElementSize, Count * ElementSize);
}

class FString : protected FArray
{
public:
    FString(const TCHAR* In);
    FString(const FString& Other);
    ~FString();
    const TCHAR* operator*() const
    {
        return ArrayNum ? (const TCHAR*)Data : GEmptyTCHAR;
    }
    TCHAR& operator[](INT i) { return ((TCHAR*)Data)[i]; }
    INT Len() const
    {
        return ArrayNum ? ArrayNum - 1 : 0;
    }
    FString Right(INT Count) const;
    __declspec(noinline) FString Caps() const;
};

// RVA 0x40310
FString FString::Right(INT Count) const
{
    return FString(**this + Len() - Clamp(Count, 0, Len()));
}

// RVA 0x40370
FString FString::Caps() const
{
    FString New(**this);
    for (INT i = 0; i < ArrayNum; i++)
        New[i] = appToUpper(New[i]);
    return New;
}

enum EName { NAME_None = 0 };
enum { NAME_PROBEMIN = 300, NAME_PROBEMAX = 364 };

class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName& Other) : Index(Other.Index) {}
    INT GetIndex() const { return Index; }
};

struct FStateFrame
{
    BYTE Pad[0x1c];
    QWORD ProbeMask;        // +0x1c
};

class UFunction;

class UObject
{
public:
    virtual ~UObject();
    virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void ProcessEvent(UFunction* Function, void* Parms, void* Result = 0);   // +0x10
    INT Index;              // +0x04
    UObject* HashNext;      // +0x08
    FStateFrame* StateFrame;// +0x0c
    UBOOL IsProbing(FName ProbeName);
    UFunction* FindFunctionChecked(FName InName, UBOOL Global = 0);
    // Script event for name index 0x13d; the name is not recovered (neutral name).
    __declspec(noinline) void eventUnnamed_13d()
    {
        ProcessEvent(FindFunctionChecked(FName((EName)0x13d)), 0);
    }
};

// RVA 0x40450
UBOOL UObject::IsProbing(FName ProbeName)
{
    return ProbeName.GetIndex() < NAME_PROBEMIN
        || ProbeName.GetIndex() >= NAME_PROBEMAX
        || !StateFrame
        || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
}

class UStruct;
class UClass;

// Minimal field/property layout (UField::Next +0x2c, UStruct::Children +0x30,
// UProperty ArrayDim/ElementSize/Offset +0x30/+0x32/+0x3c, Identical at vtable +0x74).
class UField
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26();
    virtual UStruct* GetInheritanceSuper();                   // +0x6c
    virtual void Slot28();
    virtual UBOOL Identical(const void* A, const void* B);   // +0x74
    BYTE Pad04[0x24 - 0x04];
    UClass* Class;          // +0x24
    UField* SuperField;     // +0x28
    UField* Next;           // +0x2c
};

class UProperty : public UField
{
public:
    short ArrayDim;         // +0x30
    short ElementSize;      // +0x32
    DWORD PropertyFlags;    // +0x34
    FName Category;         // +0x38
    INT Offset;             // +0x3c
};

class UStruct : public UField
{
public:
    UField* Children;       // +0x30
    __declspec(noinline) UBOOL StructCompare(const void* A, const void* B);
};

class UClass : public UStruct
{
public:
    BYTE Pad34[0x88 - 0x34];
    DWORD ClassFlags;       // +0x88
};

class TFieldIterator_UProperty
{
public:
    UStruct* Struct;
    UField* Field;
    TFieldIterator_UProperty(UStruct* InStruct) : Struct(InStruct), Field(InStruct ? InStruct->Children : 0) { IterateToNext(); }
    operator UBOOL() { return Field != 0; }
    void operator++() { Field = Field->Next; IterateToNext(); }
    UProperty* operator->() { return (UProperty*)Field; }
    __declspec(noinline) void IterateToNext();
};

enum { CLASS_IsAUProperty = 0x8000 };

// RVA 0x1f850, reproduced here only so the link passes the iterator in ESI
// (it belongs to another item).
void TFieldIterator_UProperty::IterateToNext()
{
    while (Struct) {
        while (Field) {
            if (Field->Class->ClassFlags & CLASS_IsAUProperty)
                return;
            Field = Field->Next;
        }
        Struct = Struct->GetInheritanceSuper();
        if (Struct)
            Field = Struct->Children;
    }
}

// RVA 0x404a0
UBOOL UStruct::StructCompare(const void* A, const void* B)
{
    for (TFieldIterator_UProperty It(this); It; ++It)
        for (INT i = 0; i < It->ArrayDim; i++)
        {
            INT Ofs = It->Offset + i * It->ElementSize;
            if (!It->Identical((BYTE*)A + Ofs, B ? (BYTE*)B + Ofs : 0))
                return 0;
        }
    return 1;
}
#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void*);
void Driver_402b0(FArray* A, INT I, INT C, INT E) { Escape(&GMalloc); A->InsertZeroed(I, C, E); A->InsertZeroed(C, I, E); }
void Driver_40370(FString* S) { FString T = S->Caps(); Escape(&T); }
void Driver_40430(UObject* O) { O->eventUnnamed_13d(); }
void Driver_404a0(UStruct* S, void* A, void* B) { Escape((void*)S->StructCompare(A, B)); }
