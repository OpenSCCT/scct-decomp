// Work item 0233: Versus RVA 0x57660-0x576e1. Both are LTCG functions with
// link-time register conventions. Built with try_ltcg.py --flags "/O2 /Ob1 /Gy".
//   0x57660 TArray<UObject*>::FindItem (this in EDX, Item in ESI, Index in EAX).
//   0x57690 TFieldIterator<T>::IterateToNext (this in ESI), where T's static
//           class object is at 0x10cc9c30. The class is not identified, so the
//           neutral name UUnnamedField_9c30 is used.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    UBOOL FindItem(const T &Item, INT &Index) const;
};

template<class T> UBOOL TArray<T>::FindItem(const T &Item, INT &Index) const
{
    for (Index = 0; Index < ArrayNum; Index++)
        if ((*this)(Index) == Item)
            return 1;
    return 0;
}

class UClass;
class UStruct;

class UObject
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26();

    INT Index;              // +0x04
    UObject *HashNext;      // +0x08
    void *StateFrame;       // +0x0c
    void *_Linker;          // +0x10
    INT _LinkerIndex;       // +0x14
    UObject *Outer;         // +0x18
    DWORD ObjectFlags;      // +0x1c
    INT Name;               // +0x20
    UClass *Class;          // +0x24

    inline UBOOL IsA(UClass *SomeBase) const;
};

class UField : public UObject
{
public:
    virtual UStruct *GetInheritanceSuper();     // +0x6c
    UField *SuperField;     // +0x28
    UField *Next;           // +0x2c
};

class UStruct : public UField
{
public:
    UField *Children;       // +0x30
};

class UClass : public UStruct
{
public:
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

// Neutral name: field class whose PrivateStaticClass is at 0x10cc9c30.
class UUnnamedField_9c30 : public UField
{
public:
    static UClass PrivateStaticClass;   // 0x10cc9c30
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template<class T> class TFieldIterator
{
public:
    UStruct *Struct;
    UField *Field;
    void IterateToNext()
    {
        while (Struct) {
            while (Field) {
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

// RVA 0x57660
template UBOOL TArray<UObject *>::FindItem(UObject *const &, INT &) const;
// RVA 0x57690
template void TFieldIterator<UUnnamedField_9c30>::IterateToNext();

// Scaffolding for the link, not part of the unit.
UBOOL Driver_57660(const TArray<UObject *> *A, UObject *const *O, INT *I, UObject *const *P, INT *J)
{
    // Retail calls FindItem from several places, which keeps it out of line.
    return A->FindItem(*O, *I) + A->FindItem(*P, *J) + A->FindItem(*O, *J);
}
void Driver_57690(TFieldIterator<UUnnamedField_9c30> *It) { It->IterateToNext(); }
