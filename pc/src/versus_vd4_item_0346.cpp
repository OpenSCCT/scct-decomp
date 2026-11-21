// Work item 0346: RVA 0x97520, UMaterial::ClearFallbacks (UE2 UnMaterial.cpp).
// Retail 0x10cc2800 is UMaterial's class object; the iterator constructor is
// TObjectIterator<UMaterial> at RVA 0x99290 (link convention: this in ESI);
// the destructor is the folded empty `ret 4` at RVA 0x4a550 (this on stack).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;

class UClass;

class UObject
{
public:
    void *VTable;
    char Pad04[0x20];
    UClass *Class;                       // +0x24
    UBOOL IsA(UClass *SomeBase) const;
};

class UClass : public UObject
{
public:
    UClass *SuperField;                  // +0x28
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

template<class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

extern TArray<UObject *> GObjObjects;

class UMaterial : public UObject
{
public:
    char Pad28[0x14];
    UMaterial *FallbackMaterial;         // +0x3c
    UMaterial *DefaultMaterial;          // +0x40
    BITFIELD Validated : 1;              // +0x44 bit 0
    BITFIELD UseFallback : 1;            // +0x44 bit 1
    static UClass PrivateStaticClass;    // retail 0x10cc2800
    static UClass *StaticClass() { return &PrivateStaticClass; }
    static void ClearFallbacks();
};

class FObjectIterator
{
public:
    __stdcall ~FObjectIterator();        // RVA 0x4a550 (folded empty `ret 4`)
    operator UBOOL() { return Index < Objects->Num(); }
    UObject *operator*() { return (*Objects)(Index); }
protected:
    TArray<UObject *> *Objects;
    INT Index;
};

template<class T> class TObjectIterator : public FObjectIterator
{
public:
    TObjectIterator();
    void operator++()
    {
        while (++Index < Objects->Num() &&
               (!(*Objects)(Index) || !(*Objects)(Index)->IsA(T::StaticClass())))
            ;
    }
    T *operator->() { return (T *)(*Objects)(Index); }
};

// RVA 0x99290 (published elsewhere; defined so the link gives it its convention).
template<class T> __declspec(noinline) TObjectIterator<T>::TObjectIterator()
{
    Objects = &GObjObjects;
    Index = -1;
    ++*this;
}

// RVA 0x4a550: empty in retail. The stand-in body only keeps the link from
// discarding the call; the bytes compared are ClearFallbacks'.
void DestroyIteratorStandIn(INT);
__declspec(noinline) __stdcall FObjectIterator::~FObjectIterator()
{
    DestroyIteratorStandIn(0);
    DestroyIteratorStandIn(Index);
}

// RVA 0x97520
void UMaterial::ClearFallbacks()
{
    for (TObjectIterator<UMaterial> It; It; ++It) {
        It->Validated = 0;
        It->UseFallback = 0;
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_97520()
{
    Escape(&GObjObjects);
    Escape(&UMaterial::PrivateStaticClass);
    UMaterial::ClearFallbacks();
}
