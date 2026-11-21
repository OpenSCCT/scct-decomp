// Work item 0265: RVA 0xf8470, the advance step of an object iterator
// (LTCG unit, this in EAX; returning *this keeps it there). The retail constructor at 0xf8450 stores
// &UObject::GObjObjects (0x10cc9e80) and Index = -1, then calls this; so this
// is the shape of UE2's TObjectIterator<T>::operator++, filtered by the class
// whose static UClass is at 0x10cbe3b8 (class name not recovered).
typedef int INT;

class UClass;
template<class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class UObject
{
public:
    char Pad[0x24];
    UClass *Class;      // +0x24
    inline int IsA(UClass *SomeBase) const;
    static TArray<UObject *> GObjObjects;
};
class UField : public UObject
{
public:
    UField *SuperField; // +0x28
};
class UClass : public UField
{
public:
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};

inline int UObject::IsA(UClass *SomeBase) const
{
    for (UClass *C = Class; C; C = C->GetSuperClass())
        if (C == SomeBase)
            return 1;
    return 0;
}

// Static UClass instance tested against (unknown class, retail 0x10cbe3b8).
extern UClass UnnamedClass_10cbe3b8;

// Neutral name: TObjectIterator-like iterator over GObjObjects.
class UnnamedObjectIterator_f8470
{
public:
    TArray<UObject *> *Array;
    INT Index;
    UnnamedObjectIterator_f8470();
    UnnamedObjectIterator_f8470 &operator++();
    UObject *operator*() { return (*Array)(Index); }
    operator int() { return Index < Array->Num(); }
};

UnnamedObjectIterator_f8470 &UnnamedObjectIterator_f8470::operator++()
{
    while (++Index < Array->Num()
           && (!(*Array)(Index) || !(*Array)(Index)->IsA(&UnnamedClass_10cbe3b8)))
        ;
    return *this;
}

// Scaffolding for the link, not part of the unit.
__declspec(noinline) UnnamedObjectIterator_f8470::UnnamedObjectIterator_f8470()
    : Array(&UObject::GObjObjects), Index(-1)
{
    ++*this;
}
void Use(UObject *);
void Driver_f8470()
{
    for (UnnamedObjectIterator_f8470 It; It; ++It)
        Use(*It);
}
