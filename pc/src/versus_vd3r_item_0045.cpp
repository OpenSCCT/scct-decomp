// Work item 0045 (LTCG retry): RVA 0xc770.
// TObjectIterator-style advance (UE2 UnObjBas.h): step Index through the
// object array until a non-null object whose class chain contains a fixed
// class object (retail 0x10cc52a8). The class is not identified, so the
// names are neutral (UnnamedClass_c770). Retail passes the iterator in EAX
// (link-time-generated convention: operator++ returns *this, which keeps
// this in EAX); its constructor is at RVA 0xc750.
typedef int INT;

class UClass;

class UObject
{
public:
    char Pad00[0x24];
    UClass *Class;          // +0x24
};

class UClass : public UObject
{
public:
    UClass *SuperClass;     // +0x28 (SuperField)
};

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

// Retail 0x10cc52a8: the class object the iterator filters on.
extern UClass UnnamedClass_c770_Target;

inline int IsA(UObject *Obj, UClass *SomeBase)
{
    for (UClass *C = Obj->Class; C; C = C->SuperClass)
        if (C == SomeBase)
            return 1;
    return 0;
}

struct UnnamedIterator_c770
{
    TArray<UObject *> *Array;
    INT Index;
    UnnamedIterator_c770 &operator++();
};

UnnamedIterator_c770 &UnnamedIterator_c770::operator++()
{
    while (++Index < Array->Num() &&
           (!(*Array)(Index) || !IsA((*Array)(Index), &UnnamedClass_c770_Target)))
        ;
    return *this;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c770(UnnamedIterator_c770 *It)
{
    Escape(&UnnamedClass_c770_Target);
    ++*It;
    Escape(It);
    ++*It;
    Escape(It);
    ++*It;
}
