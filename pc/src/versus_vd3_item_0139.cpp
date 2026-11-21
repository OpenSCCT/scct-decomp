// Work item 0139: Versus RVA 0x3de40-0x3e161.
// UFunction::Serialize, UFunction::Bind, UConst::Serialize and three small
// LTCG helpers (FSArray::Add, a TMap-style Add, a field-iterator step).
// Layouts are the ones the retail code reads; names follow Unreal Engine 2.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short _WORD;
typedef unsigned char BYTE;

class UObject;
class UClass;
struct FFrame;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(INT InNum, INT InMax);
    virtual FArchive &operator<<(UObject *&Res);
    virtual void v1c(); virtual void v20(); virtual void v24();
    virtual INT GetStringKey(); // slot 0x28; Versus string obfuscation key (by use)

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    BYTE Pad18[0x14];
    UBOOL ArIsError;
    UBOOL ArIsCriticalError;
    INT Pad34;
    INT ArMaxSerializeSize;

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, _WORD &W) { Ar.Serialize(&W, 2); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, DWORD &D) { Ar.Serialize(&D, 4); return Ar; }
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

struct FNameEntry
{
    INT Index;
    DWORD Flags;
    FNameEntry *HashNext;
    TCHAR Name[1];
};
extern FNameEntry **FName_Names; // FName::Names.Data

class UObject
{
public:
    virtual ~UObject();
    // Slots 1-24 are not used here.
    virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual UClass *GetOwnerClass();              // slot 0x64 (UField::GetOwnerClass, by use)
    virtual void v68();
    virtual class UStruct *GetInheritanceSuper(); // slot 0x6c
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80();
    virtual const TCHAR *GetNameCPP();           // slot 0x84 (by use in Bind)

    void ProcessInternal(FFrame &Stack, void *const Result);

    INT Index;
    BYTE Pad08[0x18];
    void Serialize(FArchive &Ar);
    INT GetIndex() { return Index; }
    INT Name;
    UClass *Class;

    const TCHAR *GetName() { return FName_Names[Name]->Name; }
    inline UBOOL IsA(UClass *SomeBase);
};

typedef void (UObject::*Native)(FFrame &TheStack, void *const Result);
extern Native GNatives[];

class UField : public UObject
{
public:
    UField *SuperField;
    UField *Next;
    void Serialize(FArchive &Ar);
};

class UStruct : public UField
{
public:
    UField *Children;
    BYTE Pad34[0x34];
    void Serialize(FArchive &Ar);
};

class UClass : public UStruct
{
};

inline UBOOL UObject::IsA(UClass *SomeBase)
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

class UProperty : public UField
{
public:
    _WORD ArrayDim;
    _WORD ElementSize;
    DWORD PropertyFlags;
    INT Pad38;
    _WORD Offset;
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    INT GetSize() { return ArrayDim * ElementSize; }
};

template <class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

enum { FUNC_Net = 0x40, FUNC_Native = 0x400 };
enum { CPF_Parm = 0x80, CPF_ReturnParm = 0x400 };
#define MAXWORD 0xffff

class UFunction : public UStruct
{
public:
    DWORD FunctionFlags;
    Native Func;
    _WORD iNative;
    _WORD RepOffset;
    _WORD ParmsSize;
    _WORD ReturnValueOffset;
    BYTE OperPrecedence;
    BYTE NumParms;

    void Serialize(FArchive &Ar);
    void Bind();
};

INT appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);
extern const TCHAR UFunction_Bind_Format[]; // L"int%sexec%s"

// RVA 0x3de40
void UFunction::Serialize(FArchive &Ar)
{
    UStruct::Serialize(Ar);

    // Function info.
    if (Ar.Ver() <= 63)
        Ar << ParmsSize;
    Ar << iNative;
    if (Ar.Ver() <= 63)
        Ar << NumParms;
    Ar << OperPrecedence;
    if (Ar.Ver() <= 63)
        Ar << ReturnValueOffset;
    Ar << FunctionFlags;

    // Replication info.
    if (FunctionFlags & FUNC_Net)
        Ar << RepOffset;

    // Precomputation.
    if (Ar.IsLoading())
    {
        NumParms = 0;
        ParmsSize = 0;
        ReturnValueOffset = MAXWORD;
        for (UProperty *Property = Cast<UProperty>(Children);
             Property && (Property->PropertyFlags & CPF_Parm);
             Property = Cast<UProperty>(Property->Next))
        {
            NumParms++;
            ParmsSize = Property->Offset + Property->GetSize();
            if (Property->PropertyFlags & CPF_ReturnParm)
                ReturnValueOffset = Property->Offset;
        }
    }
}

// RVA 0x3df60
void UFunction::Bind()
{
    if (!(FunctionFlags & FUNC_Native))
    {
        Func = &UObject::ProcessInternal;
    }
    else if (iNative != 0)
    {
        Func = GNatives[iNative];
    }
    else
    {
        // Dynamic native lookup; the Versus build keeps only the name formatting.
        TCHAR Proc[256];
        appSprintf(Proc, UFunction_Bind_Format, GetOwnerClass()->GetNameCPP(), GetName());
        GetOwnerClass();
    }
}

// ---------------------------------------------------------------------------
// Link-time-optimised functions (compiled /GL, linked /LTCG in retail).

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
};
void FString_SerializeCount(FArchive &Ar, INT &Count);
void FString_SerializeChars(FArchive &Ar, FString &S, INT Count);
void FString_Empty(FString &S);

// RVA 0x11b80 (not part of this item; defined so the linker gives it the
// retail register convention: Ar in EAX, S in EBX).
void FArray_Realloc(FString &S, INT ElementSize);      // FArray::Realloc
extern const TCHAR FArray_Tag[];                       // L"FArray"
inline INT Abs(INT A) { return A >= 0 ? A : -A; }

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

// RVA 0x1ea40 (not part of this item; defined for its register convention).
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving)
    {
        Ar.Serialize(&I.Value, sizeof(I.Value));
        return Ar;
    }
    INT Original = I.Value;
    DWORD V = Abs(I.Value);
    BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
    I.Value = 0;
    Ar << B0;
    if (B0 & 0x40)
    {
        V >>= 6;
        BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
        Ar << B1;
        if (B1 & 0x80)
        {
            V >>= 7;
            BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B2;
            if (B2 & 0x80)
            {
                V >>= 7;
                BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B3;
                if (B3 & 0x80)
                {
                    V >>= 7;
                    BYTE B4 = V;
                    Ar << B4;
                    I.Value = B4;
                }
                I.Value = (I.Value << 7) + (B3 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B2 & 0x7f);
        }
        I.Value = (I.Value << 7) + (B1 & 0x7f);
    }
    I.Value = (I.Value << 6) + (B0 & 0x3f);
    if (B0 & 0x80)
        I.Value = -I.Value;
    return Ar;
}

FArchive &operator<<(FArchive &Ar, FString &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(TCHAR), A.ArrayMax * sizeof(TCHAR));
    INT SaveNum = A.ArrayNum;
    if (SaveNum)
    {
        for (TCHAR *Ch = A.Data; *Ch; Ch++)
        {
            if (*Ch > 0xff)
            {
                SaveNum = -SaveNum;
                break;
            }
        }
    }
    Ar << AR_INDEX(SaveNum);
    if (Ar.IsLoading())
    {
        if (Ar.ArMaxSerializeSize && Abs(SaveNum) > Ar.ArMaxSerializeSize)
        {
            Ar.ArIsError = 1;
            Ar.ArIsCriticalError = 1;
            return Ar;
        }
        A.ArrayNum = A.ArrayMax = Abs(SaveNum);
        if (!A.Data)
        {
            if (A.ArrayMax)
                A.Data = (TCHAR *)GMalloc->Malloc(A.ArrayMax * sizeof(TCHAR), FArray_Tag);
        }
        else if (!A.ArrayMax)
        {
            GMalloc->Free(A.Data);
            A.Data = 0;
        }
        else if (A.Data)
        {
            FArray_Realloc(A, sizeof(TCHAR));
        }
        if (SaveNum >= 0)
        {
            if (Ar.Ver() >= 175)
            {
                for (INT i = 0; i < A.ArrayNum; i++)
                {
                    BYTE Ch;
                    Ar.Serialize(&Ch, 1);
                    INT Key = Ar.GetStringKey() - 1;
                    if (Key > 0)
                        Ch ^= Key;
                    A.Data[i] = Ch;
                }
            }
            else
            {
                for (INT i = 0; i < A.ArrayNum; i++)
                {
                    BYTE Ch;
                    Ar.Serialize(&Ch, 1);
                    A.Data[i] = Ch;
                }
            }
        }
        else
        {
            if (Ar.Ver() >= 175)
            {
                for (INT i = 0; i < A.ArrayNum; i++)
                {
                    INT Ch;
                    Ar.Serialize(&Ch, 2);
                    INT Key = Ar.GetStringKey() - 1;
                    if (Key > 0)
                        Ch ^= Key;
                    A.Data[i] = (TCHAR)Ch;
                }
            }
            else
            {
                for (INT i = 0; i < A.ArrayNum; i++)
                {
                    INT Ch;
                    Ar.Serialize(&Ch, 2);
                    A.Data[i] = (TCHAR)Ch;
                }
            }
        }
        if (A.ArrayNum == 1)
        {
            A.ArrayNum = 0;
            if (A.Data)
            {
                GMalloc->Free(A.Data);
                A.Data = 0;
                A.ArrayMax = 0;
            }
        }
    }
    else if (SaveNum >= 0)
    {
        if (Ar.Ver() >= 175)
        {
            for (INT i = 0; i < A.ArrayNum; i++)
            {
                BYTE Ch = A.Data[i] < 0x100 ? (BYTE)A.Data[i] : 0x7f;
                INT Key = Ar.GetStringKey();
                if (Key > 0)
                    Ch ^= Key;
                Ar.Serialize(&Ch, 1);
            }
        }
        else
        {
            for (INT i = 0; i < A.ArrayNum; i++)
            {
                BYTE Ch = A.Data[i] < 0x100 ? (BYTE)A.Data[i] : 0x7f;
                Ar.Serialize(&Ch, 1);
            }
        }
    }
    else
    {
        if (Ar.Ver() >= 175)
        {
            for (INT i = 0; i < A.ArrayNum; i++)
            {
                INT Ch = A.Data[i];
                INT Key = Ar.GetStringKey();
                if (Key > 0)
                    Ch ^= Key;
                Ar.Serialize(&Ch, 2);
            }
        }
        else
        {
            for (INT i = 0; i < A.ArrayNum; i++)
            {
                INT Ch = A.Data[i];
                Ar.Serialize(&Ch, 2);
            }
        }
    }
    return Ar;
}

template <class T> inline FArchive &operator<<(FArchive &Ar, T *&Obj)
{
    return Ar << *(UObject **)&Obj;
}

void UField::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << SuperField;
    Ar << Next;
}

class UConst : public UField
{
public:
    FString Value;
    void Serialize(FArchive &Ar);
};

// RVA 0x3e000
void UConst::Serialize(FArchive &Ar)
{
    UField::Serialize(Ar);
    Ar << Value;
}

// Byte array that reallocates to its exact size on every Add.
class FSArray
{
public:
    void *Data;
    INT ArrayNum;
    INT Add(INT Count);
};
extern const TCHAR FSArray_Tag[];     // L"FSArray"
extern const TCHAR FSArray_Add_Tag[]; // L"FSArray::Add"

// RVA 0x3e040
INT FSArray::Add(INT Count)
{
    INT Index = ArrayNum;
    ArrayNum += Count;
    if (!Data)
        Data = ArrayNum > 0 ? GMalloc->Malloc(ArrayNum, FSArray_Add_Tag) : 0;
    else
        Data = GMalloc->Realloc(Data, ArrayNum, FSArray_Tag);
    return Index;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
    INT Num() { return ArrayNum; }
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

inline DWORD GetTypeHash(UObject *A)
{
    return A ? A->GetIndex() : 0;
}

extern const TCHAR HashMapHash_Tag[]; // L"HashMapHash"

template <class TK, class TI> class TMapBase
{
public:
    class TPair
    {
    public:
        INT HashNext;
        TK Key;
        TI Value;
        TPair(const TK &InKey, const TI &InValue) : Key(InKey), Value(InValue) {}
    };

    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;

    void Rehash()
    {
        INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), HashMapHash_Tag);
        for (INT i = 0; i < HashCount; i++)
            NewHash[i] = -1;
        for (INT i = 0; i < Pairs.Num(); i++)
        {
            TPair &Pair = Pairs(i);
            INT iHash = (GetTypeHash(Pair.Key) & (HashCount - 1));
            Pair.HashNext = NewHash[iHash];
            NewHash[iHash] = i;
        }
        if (Hash)
            GMalloc->Free(Hash);
        Hash = NewHash;
    }

    // RVA 0x3e090 (TK = UObject*, TI = a 4-byte value).
    TI &Add(const TK &InKey, const TI &InValue)
    {
        TPair &Pair = *new (Pairs) TPair(InKey, InValue);
        INT iHash = (GetTypeHash(Pair.Key) & (HashCount - 1));
        Pair.HashNext = Hash[iHash];
        Hash[iHash] = Pairs.Num() - 1;
        if (HashCount * 2 + 8 < Pairs.Num())
        {
            HashCount *= 2;
            Rehash();
        }
        return Pair.Value;
    }
};

// Field class at 0x10cc98e8; no evidence for its name.
class UUnnamedField_98e8 : public UField
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template <class T> class TFieldIterator
{
public:
    UStruct *Struct;
    UField *Field;

    // RVA 0x3e110
    void IterateToNext()
    {
        while (Struct)
        {
            while (Field)
            {
                if (Field->IsA(T::StaticClass()))
                    return;
                Field = Field->Next;
            }
            Struct = Struct->GetInheritanceSuper();
            if (Struct)
                Field = Struct->Children;
        }
    }
};

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
typedef void (UConst::*UConstSerializeFn)(FArchive &);
void Driver_3e000(FArchive *Ar, FString *S)
{
    UConstSerializeFn F = &UConst::Serialize;
    Escape(&F);
    *Ar << S[0];
    *Ar << S[1];
    *Ar << S[2];
    *Ar << S[3];
}
void Driver_3e040(FSArray *A, FArchive *Ar, INT N)
{
    // Mirrors the only retail caller, UStruct::Serialize (script loading).
    Escape(&GMalloc);
    Ar->Serialize(&N, 4);
    if (Ar->IsLoading())
    {
        A->ArrayNum = 0;
        if (A->Data)
        {
            GMalloc->Free(A->Data);
            A->Data = 0;
        }
        if (N)
            A->Add(N);
    }
    for (INT i = 0; i < N; i++)
        Ar->Serialize(&i, 4);
}
void Driver_3e090(TMapBase<UObject *, INT> *M, UObject *K, INT V)
{
    Escape(&GMalloc);
    M[0].Add(K, V);
    M[1].Add(K, V);
    M[2].Add(K, V);
    M[3].Add(K, V);
}
void Driver_3e110(TFieldIterator<UUnnamedField_98e8> *I)
{
    I[0].IterateToNext();
    I[1].IterateToNext();
    I[2].IterateToNext();
    I[3].IterateToNext();
}
