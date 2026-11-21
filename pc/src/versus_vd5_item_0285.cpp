// Work item w3 0285: Versus RVA 0xfef20-0xff101.
// A TMap<FName,DWORD>-style map (UE2 UnTemplate.h: Pairs TArray, Hash,
// HashCount; 12-byte pairs {HashNext, Key, Value}, GetTypeHash(FName)) and
// two TFieldIterator<T>::IterateToNext instantiations (UE2 UnClass.h).
// All five were /GL objects linked with /LTCG (map or iterator in EAX/EDX/ESI).
// The map's key/value types and the iterated classes are not named by any
// string, so the names are neutral.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef DWORD UBOOL;
enum { INDEX_NONE = -1 };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;
extern const TCHAR Text_HashMapHash[]; // TEXT("HashMapHash")

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize); // 0x44e0
};

inline void *appMalloc(DWORD Count, const TCHAR *Tag) { return GMalloc->Malloc(Count, Tag); }
inline void *operator new[](unsigned int Size, const TCHAR *Tag) { return appMalloc(Size, Tag); }
inline void *operator new(unsigned int Size, FArray &Array, INT ElementSize) { INT Index = Array.Add(1, ElementSize); return (char *)Array.Data + Index * ElementSize; }
inline void operator delete[](void *Ptr) { GMalloc->Free(Ptr); }

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

struct FName
{
    INT Index;
    INT GetIndex() const { return Index; }
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
};
typedef FName KeyType;
inline DWORD GetTypeHash(const FName N) { return N.GetIndex(); }

class UnnamedMap_0fef20
{
public:
    struct TPair
    {
        TPair(const KeyType &InKey, const DWORD &InValue) : Key(InKey), Value(InValue) {}
        INT HashNext;
        KeyType Key;
        DWORD Value;
    };
    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;

    // RVA 0xfef60
    __declspec(noinline) void Rehash()
    {
        INT *NewHash = new(Text_HashMapHash) INT[HashCount];
        INT i;
        for (i = 0; i < HashCount; i++)
            NewHash[i] = INDEX_NONE;
        for (i = 0; i < Pairs.Num(); i++)
        {
            TPair &Pair = Pairs(i);
            INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
            Pair.HashNext = NewHash[iHash];
            NewHash[iHash] = i;
        }
        if (Hash)
            delete[] Hash;
        Hash = NewHash;
    }
    // RVA 0xfefe0
    __declspec(noinline) DWORD &Add(const KeyType &InKey, const DWORD &InValue)
    {
        TPair *Pair = new(Pairs, sizeof(TPair)) TPair(InKey, InValue);
        INT iHash = GetTypeHash(Pair->Key) & (HashCount - 1);
        Pair->HashNext = Hash[iHash];
        Hash[iHash] = Pairs.Num() - 1;
        if (HashCount * 2 + 8 < Pairs.Num())
        {
            HashCount *= 2;
            Rehash();
        }
        return Pair->Value;
    }
    // RVA 0xfef20
    __declspec(noinline) DWORD FindRef(const KeyType &Key)
    {
        for (INT i = Hash[GetTypeHash(Key) & (HashCount - 1)]; i != INDEX_NONE; i = Pairs(i).HashNext)
        {
            TPair &Pair = Pairs(i);
            if (Pair.Key == Key)
                return Pair.Value;
        }
        return 0;
    }
};

class UClass;
class UObject
{
public:
    virtual ~UObject();
    INT Pad[8];
    UClass *Class;
};
class UField : public UObject
{
public:
    UField *SuperField;
    UField *Next;
};
class UStruct : public UField
{
public:
    UField *Children;
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08();
    virtual void V09(); virtual void V10(); virtual void V11(); virtual void V12();
    virtual void V13(); virtual void V14(); virtual void V15(); virtual void V16();
    virtual void V17(); virtual void V18(); virtual void V19(); virtual void V20();
    virtual void V21(); virtual void V22(); virtual void V23(); virtual void V24();
    virtual void V25(); virtual void V26();
    virtual UStruct *GetInheritanceSuper(); // slot 0x6c
};
class UClass : public UStruct
{
};

// Two property classes whose PrivateStaticClass objects sit at 0x10cc8728
// and 0x10cc8b88 (names unknown).
class UnnamedProperty_cc8728 : public UField
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};
class UnnamedProperty_cc8b88 : public UField
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

inline UBOOL IsA(const UObject *Obj, UClass *SomeBase)
{
    for (UClass *TempClass = Obj->Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

template<class T> class TFieldIterator
{
public:
    // RVA 0xff050 / 0xff0b0
    __declspec(noinline) void IterateToNext()
    {
        while (Struct)
        {
            while (Field)
            {
                if (IsA(Field, T::StaticClass()))
                    return;
                Field = Field->Next;
            }
            Struct = Struct->GetInheritanceSuper();
            if (Struct)
                Field = Struct->Children;
        }
    }
    UStruct *Struct;
    UField *Field;
};

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Escape(DWORD);
void Driver_ff050(TFieldIterator<UnnamedProperty_cc8728> *It) { It->IterateToNext(); }
void Driver_ff0b0(TFieldIterator<UnnamedProperty_cc8b88> *It) { It->IterateToNext(); }
void Driver_map(void *M, void *K, void *V)
{
    Escape(&GMalloc);
    UnnamedMap_0fef20 *Map = (UnnamedMap_0fef20 *)M;
    Escape(&Map->Add(*(KeyType *)K, *(DWORD *)V));
}
void Driver_find(UnnamedMap_0fef20 *Map, FName *K, FName *L)
{
    Escape(Map->FindRef(*K));
    Escape(Map->FindRef(*L));
}
