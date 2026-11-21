// Work item 0245: Versus RVA 0x5a990-0x5ab9b. Helpers of an unnamed UObject
// subclass (UnnamedClass_5a990, name not recovered) that owns
//   +0x28 TArray<FUnnamedEntry_44>         (0x44-byte entries)
//   +0x34 TMap<UObject*,FUnnamedValue_2c*>  (values owned, deleted in Destroy)
//   +0x48 TMap<UObject*,INT>
// plus the Unreal Engine 2 UnTemplate.h code instantiated for them.
// The object was link-time optimised (/GL + /LTCG): the helpers have custom
// register conventions. Callees that retail calls are defined further down
// only so the linker gives them retail's conventions.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag) = 0;
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag) = 0;
    virtual void Free(void* Original) = 0;
};
extern FMalloc* GMalloc;                     // 0x10c73bf0

extern const TCHAR FArrayTag[];              // 0x10c10974, TEXT("FArray")
extern const TCHAR HashMapHashTag[];         // 0x10c7495c, TEXT("HashMapHash")

inline void* operator new(unsigned int, void* Mem) { return Mem; }
inline void* operator new(unsigned int Size, const TCHAR* Tag) { return GMalloc->Malloc(Size, Tag); }
inline void* operator new[](unsigned int Size, const TCHAR* Tag) { return GMalloc->Malloc(Size, Tag); }
inline void operator delete(void* Ptr) { GMalloc->Free(Ptr); }
inline void operator delete[](void* Ptr) { GMalloc->Free(Ptr); }

class UObject;
class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(UObject* Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive& operator<<(UObject*& Res);
    INT ArVer, ArNetVer, ArLicenseeVer;
    UBOOL ArIsLoading, ArIsSaving;
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    void ByteOrderSerialize(void* V, INT Length) { Serialize(V, Length); }
    friend FArchive& operator<<(FArchive& Ar, unsigned char& B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive& operator<<(FArchive& Ar, INT& I) { Ar.ByteOrderSerialize(&I, sizeof(I)); return Ar; }
};

// UE2 FCompactIndex (UnArc.h); operator<< is RVA 0x1ea40 (Ar in ESI, index in EDI).
class FCompactIndex
{
public:
    INT Value;
    friend FArchive& operator<<(FArchive& Ar, FCompactIndex& I);
};
#define AR_INDEX(intref) (*(FCompactIndex*)&(intref))

class UObject
{
public:
    INT Index;
    INT Pad[8];
    virtual ~UObject();
    virtual void vf1(); virtual void vf2(); virtual void vf3(); virtual void vf4();
    virtual void vf5(); virtual void vf6(); virtual void vf7(); virtual void vf8();
    virtual void Destroy();                      // slot 9, UObject::Destroy RVA 0x15ce0
    virtual void Serialize(FArchive& Ar);        // slot 10, UObject::Serialize RVA 0x15f50
    INT GetIndex() const { return Index; }
};

inline DWORD GetTypeHash(const UObject* A) { return A ? A->GetIndex() : 0; }

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);                 // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);              // RVA 0x4550
    void Remove(INT Index, INT Count, INT ElementSize);  // RVA 0x119c0
    void Realloc(INT ElementSize) { Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, FArrayTag); }
    void Shrink(INT ElementSize)
    {
        if (ArrayMax != ArrayNum)
        {
            ArrayMax = ArrayNum;
            Realloc(ElementSize);
        }
    }
};

template<class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray() { Remove(0, ArrayNum); }
    T& operator()(INT i) { return ((T*)Data)[i]; }
    const T& operator()(INT i) const { return ((T*)Data)[i]; }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    // RVA 0x5ad30 for the entries (this in ESI). Retail calls it out of line
    // there; noinline reproduces that.
    __declspec(noinline) void Empty(INT Slack = 0)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }
    void Shrink() { FArray::Shrink(sizeof(T)); }
    TArray& operator=(const TArray& Other);
    void CountBytes(FArchive& Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    friend FArchive& operator<<(FArchive& Ar, TArray& A)
    {
        A.CountBytes(Ar);
        if (Ar.IsLoading())
        {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new(A) T;
        }
        else
        {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};

template<class T> inline void* operator new(unsigned int, TArray<T>& Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

// RVA 0x5aae0 for TArray<FUnnamedEntry_44> (this in EBX, Other on the stack).
template<class T> TArray<T>& TArray<T>::operator=(const TArray<T>& Other)
{
    if (this != &Other)
    {
        Empty(Other.ArrayNum);
        for (INT i = 0; i < Other.ArrayNum; i++)
            new(*this) T(Other(i));
    }
    return *this;
}

template<class TK, class TV> class TMapBase
{
public:
    class TPair
    {
    public:
        INT HashNext;
        TK Key;
        TV Value;
        TPair(const TK& InKey, const TV& InValue) : Key(InKey), Value(InValue) {}
        TPair() {}
        friend FArchive& operator<<(FArchive& Ar, TPair& F) { return Ar << F.Key << F.Value; }
    };
    TArray<TPair> Pairs;
    INT* Hash;
    INT HashCount;

    // RVA 0x5aca0 (this in ESI).
    void Rehash()
    {
        INT* NewHash = new(HashMapHashTag) INT[HashCount];
        INT i;
        for (i = 0; i < HashCount; i++)
            NewHash[i] = -1;
        for (i = 0; i < Pairs.Num(); i++)
        {
            TPair& Pair = Pairs(i);
            INT iHash = (GetTypeHash(Pair.Key) & (HashCount - 1));
            Pair.HashNext = NewHash[iHash];
            NewHash[iHash] = i;
        }
        if (Hash)
            delete[] Hash;
        Hash = NewHash;
    }
    // RVA 0x3e090 (this in EAX; shared by identical-code folding). Retail
    // calls it out of line from Set; noinline reproduces that.
    __declspec(noinline) TV& Add(const TK& InKey, const TV& InValue)
    {
        TPair& Pair = *new(Pairs) TPair(InKey, InValue);
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
    ~TMapBase()
    {
        if (Hash)
            delete[] Hash;
        Hash = 0;
        HashCount = 0;
    }
    // RVA 0x5ab50 (retail: this in EAX, InKey in EDI, InValue in EBX; near).
    TV& Set(const TK& InKey, const TV& InValue)
    {
        for (INT i = Hash[(GetTypeHash(InKey) & (HashCount - 1))]; i != -1; i = Pairs(i).HashNext)
            if (Pairs(i).Key == InKey)
            {
                Pairs(i).Value = InValue;
                return Pairs(i).Value;
            }
        return Add(InKey, InValue);
    }
    friend FArchive& operator<<(FArchive& Ar, TMapBase& M)
    {
        Ar << M.Pairs;
        if (Ar.IsLoading())
            M.Rehash();
        return Ar;
    }
    class TIterator
    {
    public:
        TIterator(TMapBase& InMap) : Map(InMap), Pairs(InMap.Pairs), Index(0) {}
        void operator++() { ++Index; }
        operator UBOOL() const { return Index < Pairs.Num(); }
        TK& Key() const { return Pairs(Index).Key; }
        TV& Value() const { return Pairs(Index).Value; }
    private:
        TMapBase& Map;
        TArray<TPair>& Pairs;
        INT Index;
    };
    // RVA 0x5aa80 (this in EAX).
    void Shrink()
    {
        Pairs.Shrink();
        while (HashCount > Pairs.Num() * 2 + 8)
            HashCount /= 2;
        Rehash();
    }
};

template<class TK, class TV> class TMap : public TMapBase<TK, TV>
{
};

struct FUnnamedItem_8 { INT A, B; };
// Value type of the +0x34 map (0x2c bytes; name not recovered).
struct FUnnamedValue_2c
{   // Implicit destructor: RVA 0x5aa30 (this on the stack, ret 4).
    INT Field0;
    INT Field4;
    INT Field8;
    TArray<FUnnamedItem_8> List; // +0x0c (destructor RVA 0x17f6a0)
    TMap<UObject*, INT> Map;   // +0x18
};
// The +0x34 map stores only its keys; the values are rebuilt at run time.
inline FArchive& operator<<(FArchive& Ar, FUnnamedValue_2c*&) { return Ar; }

class FString : public FArray
{
public:
    FString() {}
    FString(const FString& Other);   // RVA 0x4640
    ~FString();                      // RVA 0x48b0
};

// 0x44-byte entry of the +0x28 array (name not recovered).
struct FGuidLike { INT A, B, C, D; };
struct FUnnamedEntry_44
{
    FString Name;
    UObject* Object0C;
    UObject* Object10;
    FGuidLike Block14;
    INT Field24, Field28, Field2C, Field30, Field34, Field38, Field3C, Field40;
    FUnnamedEntry_44(UObject* InOwner = 0)        // RVA 0x5a0a0 (simplified; not part of the match)
    :   Object0C(InOwner), Object10(InOwner ? (UObject*)InOwner->Pad[8] : 0),
        Field24(0), Field28(-1), Field2C(-1), Field30(-1), Field34(-1), Field38(0), Field3C(0),
        Field40(InOwner ? InOwner->Pad[1] : 0)
    {
        Block14.A = Block14.B = Block14.C = Block14.D = 0;
    }
    friend FArchive& operator<<(FArchive& Ar, FUnnamedEntry_44& E) { return Ar << E.Object10 << E.Object0C; }
};

class UnnamedClass_5a990 : public UObject
{
public:
    TArray<FUnnamedEntry_44> Entries;            // +0x28
    TMap<UObject*, FUnnamedValue_2c*> Values;    // +0x34
    TMap<UObject*, INT> Counts;                  // +0x48
    void Destroy();
    void Serialize(FArchive& Ar);
};

// RVA 0x5a990
void UnnamedClass_5a990::Serialize(FArchive& Ar)
{
    UObject::Serialize(Ar);
    Ar << Entries << Counts << Values;
}

// RVA 0x5a9f0
void UnnamedClass_5a990::Destroy()
{
    UObject::Destroy();
    for (TMap<UObject*, FUnnamedValue_2c*>::TIterator It(Values); It; ++It)
        delete It.Value();
}

// Scaffolding for the link, not part of the unit. The FCompactIndex
// serializer lives in Core; it is written out here only so the linker gives
// it retail's register convention.
FArchive& operator<<(FArchive& Ar, FCompactIndex& I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving())
    {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
    DWORD V = I.Value >= 0 ? I.Value : -I.Value;
    unsigned char B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
    I.Value = 0;
    Ar << B0;
    if (B0 & 0x40)
    {
        V >>= 6;
        unsigned char B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
        Ar << B1;
        if (B1 & 0x80)
        {
            V >>= 7;
            unsigned char B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B2;
            if (B2 & 0x80)
            {
                V >>= 7;
                unsigned char B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B3;
                if (B3 & 0x80)
                {
                    V >>= 7;
                    unsigned char B4 = V;
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
void Escape(void*);
void Driver_5aa80(FUnnamedValue_2c* V) { Escape(&GMalloc); V->Map.Shrink(); }
void Driver_5aae0(UnnamedClass_5a990* A, UnnamedClass_5a990* B) { Escape(&GMalloc); A->Entries = B->Entries; }
UObject* GetKey();
FUnnamedValue_2c* GetValue();
void Driver_5ab50(UnnamedClass_5a990* C) { Escape(&GMalloc); UObject* K = GetKey(); FUnnamedValue_2c* V = GetValue(); C->Values.Set(K, V)->Field4 = 0; }
