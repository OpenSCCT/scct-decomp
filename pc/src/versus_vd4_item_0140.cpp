// Work item 0140: Versus RVA 0x3e170, TFieldIterator<T>::IterateToNext for a
// field class whose static class object sits at 0x10cc97d0 (neutral name: no
// symbol survives for it). LTCG function: the iterator (this) arrives in ESI.
// Same template as 0x1fe20 (item 0124) with a different T.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FName
{
public:
    INT Index;
};

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
    FName Name;             // +0x20
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
class UnnamedClass_10cc97d0 : public UField
{
public:
    static UClass PrivateStaticClass;   // 0x10cc97d0
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
// RVA 0x3e170
template class TFieldIterator<UnnamedClass_10cc97d0>;

// ---- Scaffolding for the link, not part of the unit ----
void Escape(void *);
void Driver_3e170(TFieldIterator<UnnamedClass_10cc97d0> *It) { It->IterateToNext(); Escape(It); }
