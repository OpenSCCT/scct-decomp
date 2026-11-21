inline void *operator new(unsigned int, void *P) { return P; }
// Work item 0348: RVA 0x992b0, an LTCG object-iterator advance.
// Iterator layout {TArray<UObject*>* Array; INT Index;} held in EAX by retail.
// Steps to the next non-null object whose class chain (Class at +0x24,
// SuperField at +0x28) contains the class object at retail 0x10cc2800.
// Neutral names: the exact class iterated is not identified.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class UnnamedClass_992b0;

class UObjectLike
{
public:
    char Pad[0x24];
    UnnamedClass_992b0 *Class;
    inline UBOOL IsA(UnnamedClass_992b0 *SomeBase) const;
};

class UnnamedClass_992b0 : public UObjectLike
{
public:
    UnnamedClass_992b0 *SuperField; // +0x28
};

inline UBOOL UObjectLike::IsA(UnnamedClass_992b0 *SomeBase) const
{
    for (UnnamedClass_992b0 *C = Class; C; C = C->SuperField)
        if (C == SomeBase)
            return 1;
    return 0;
}

struct TObjectArray
{
    UObjectLike **Data;
    INT ArrayNum;
    INT Num() const { return ArrayNum; }
    UObjectLike *operator()(INT i) const { return Data[i]; }
};

extern UnnamedClass_992b0 IteratedClass_992b0; // retail 0x10cc2800
extern TObjectArray GObjObjects; // retail 0x10cc9e80

// Object iterator over GObjObjects filtered by class (TObjectIterator-like).
// Retail constructor at 0x99290 sets Array/Index then calls operator++.
struct ObjectIterator_992b0
{
    TObjectArray *Array;
    INT Index;
    ObjectIterator_992b0();
    ObjectIterator_992b0 &operator++();
};

ObjectIterator_992b0 &ObjectIterator_992b0::operator++()
{
    while (++Index < Array->Num() && (!(*Array)(Index) || !(*Array)(Index)->IsA(&IteratedClass_992b0)))
        ;
    return *this;
}

ObjectIterator_992b0::ObjectIterator_992b0()
    : Array(&GObjObjects), Index(-1)
{
    ++*this;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_992b0(void **M)
{
    Escape(&IteratedClass_992b0);
    Escape(&GObjObjects);
    Escape(new (M[0]) ObjectIterator_992b0);
    Escape(new (M[1]) ObjectIterator_992b0);
    Escape(new (M[2]) ObjectIterator_992b0);
    Escape(new (M[3]) ObjectIterator_992b0);
    Escape(new (M[4]) ObjectIterator_992b0);
    Escape(new (M[5]) ObjectIterator_992b0);
    Escape(new (M[6]) ObjectIterator_992b0);
    Escape(new (M[7]) ObjectIterator_992b0);
    Escape(new (M[8]) ObjectIterator_992b0);
    Escape(new (M[9]) ObjectIterator_992b0);
    Escape(new (M[10]) ObjectIterator_992b0);
    Escape(new (M[11]) ObjectIterator_992b0);
}
