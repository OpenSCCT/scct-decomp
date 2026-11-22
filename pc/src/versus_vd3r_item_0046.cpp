// Item 0046 (LTCG): RVA 0xc820, an object-iterator advance with an inlined IsA.
// The iterator (in EAX) holds a pointer to an object array and the current index;
// it skips null objects and objects whose class chain does not contain the
// target class (a private class object at 0x10cc4d30, neutral name below).
#include "versus_build.h"
#include "unreal_object.h"

typedef int INT;

class UClass;
class UClass : public UObject
{
public:
    UClass *SuperClass;  // 0x28 (SuperField)
};

template <class T> struct TArray
{
    T *Data;
    INT ArrayNum;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

// The class object at 0x10cc4d30 (unnamed).
extern UClass UnnamedClass_10cc4d30;

inline int IsA(UObject *Obj, UClass *SomeBase)
{
    for (UClass *C = Obj->Class; C; C = C->SuperClass)
        if (C == SomeBase)
            return 1;
    return 0;
}

extern TArray<UObject *> GObjObjects_c820;
struct UnnamedObjectIterator_c820
{
    TArray<UObject *> *Array;
    INT Index;
    UnnamedObjectIterator_c820() : Array(&GObjObjects_c820), Index(-1) { ++*this; }
    UnnamedObjectIterator_c820 &operator++();
    operator int() { return Index < Array->Num(); }
    UObject *operator*() { return (*Array)(Index); }
};
UnnamedObjectIterator_c820 &UnnamedObjectIterator_c820::operator++()
{
    while (++Index < Array->Num() && (!(*Array)(Index) || !IsA((*Array)(Index), &UnnamedClass_10cc4d30)))
        ;
    return *this;
}
// Scaffolding for the link, not part of the unit. Retail callers build the
// iterator on the stack (inlined constructor) and pass its address in EAX.
void Escape(void *);
int Check(int);
int Driver_c820(int A, int X)
{
    Escape(&UnnamedClass_10cc4d30);
    if (Check(A)) { UnnamedObjectIterator_c820 It; if (It) Escape(*It); return 1; }
    if (Check(X)) { UnnamedObjectIterator_c820 It; if (It) Escape(*It); return 1; }
    if (Check(A + X)) { UnnamedObjectIterator_c820 It; if (It) Escape(*It); return 1; }
    return 0;
}
