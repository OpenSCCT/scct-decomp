// Work item 0099 (LTCG retry): RVA 0x179d0, UObject::GlobalSetProperty.
// Link-time convention: Property in EBX, Immediate in EAX; Value, Class and
// Offset on the stack, caller cleans.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { CPF_Config = 0x00004000 };
enum { PPF_Localized = 1 };

class FArray
{
public:
    INT Num() const { return ArrayNum; }
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class UClass;

class UObject
{
public:
    virtual void S00(); virtual void S01(); virtual void S02(); virtual void S03();
    virtual void S04(); virtual void S05(); virtual void S06(); virtual void S07();
    virtual void S08(); virtual void S09(); virtual void S10(); virtual void S11();
    virtual void S12(); virtual void S13(); virtual void S14(); virtual void S15();
    virtual void PostEditChange();       // +0x40
    UClass *GetClass() const { return Class; }
    // RVA 0x17010; the link gives it `this` on the stack, callee cleans.
    void __stdcall SaveConfig(DWORD Flags = CPF_Config, const TCHAR *Filename = 0, UBOOL Unknown = 1);
    static void GlobalSetProperty(const TCHAR *Value, UClass *Class, class UProperty *Property, INT Offset, UBOOL Immediate);
    static TArray<UObject *> GObjObjects;
    INT Pad04[8];
    UClass *Class;                       // +0x24
};

class UField : public UObject
{
public:
    UField *SuperField;                  // +0x28
    UField *Next;                        // +0x2c
};

class UClass : public UField
{
public:
    BYTE Pad30[0xac - 0x30];
    TArray<BYTE> Defaults;               // +0xac
    UBOOL IsChildOf(const UClass *SomeBase) const
    {
        for (const UClass *TempClass = this; TempClass; TempClass = (const UClass *)TempClass->SuperField)
            if (TempClass == SomeBase)
                return 1;
        return 0;
    }
    UObject *GetDefaultObject() { return (UObject *)&Defaults(0); }
};

class UProperty : public UField
{
public:
    virtual void P10(); virtual void P11(); virtual void P12(); virtual void P13();
    virtual void P14(); virtual void P15(); virtual void P16(); virtual void P17();
    virtual void P18(); virtual void P19(); virtual void P1a(); virtual void P1b();
    virtual void P1c(); virtual void P1d(); virtual void P1e(); virtual void P1f();
    virtual const TCHAR *ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const; // +0x84
};

class FObjectIterator
{
public:
    FObjectIterator();
    __stdcall ~FObjectIterator();        // RVA 0x4a550 (folded empty `ret 4`, `this` on the stack)
    void operator++()
    {
        while (++Index < Objects->Num() && !(*Objects)(Index))
            ;
    }
    operator UBOOL() { return Index < Objects->Num(); }
    UObject *operator*() { return (*Objects)(Index); }
    UObject *operator->() { return (*Objects)(Index); }
protected:
    TArray<UObject *> *Objects;
    INT Index;
};

// RVA 0x1f470 (published elsewhere; defined so the link gives it its convention).
__declspec(noinline) FObjectIterator::FObjectIterator()
    : Objects(&UObject::GObjObjects), Index(-1)
{
    ++*this;
}

// RVA 0x4a550: empty in retail (folded `ret 4`, `this` on the stack). The
// stand-in body only keeps the link from discarding the call and the final
// Index store; the bytes compared are GlobalSetProperty's.
void DestroyIteratorStandIn(INT);
__declspec(noinline) __stdcall FObjectIterator::~FObjectIterator()
{
    DestroyIteratorStandIn(0);
    DestroyIteratorStandIn(Index);
}

// RVA 0x179d0
void UObject::GlobalSetProperty(const TCHAR *Value, UClass *Class, UProperty *Property, INT Offset, UBOOL Immediate)
{
    if (Immediate) {
        for (FObjectIterator It; It; ++It) {
            if (!Class || It->GetClass()->IsChildOf(Class)) {
                Property->ImportText(Value, (BYTE *)*It + Offset, PPF_Localized);
                It->PostEditChange();
            }
        }
    }
    Property->ImportText(Value, &Class->Defaults(Offset), PPF_Localized);
    Class->GetDefaultObject()->SaveConfig();
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_179d0(const TCHAR *V, UClass *C, UProperty *P, INT O, UBOOL I)
{
    Escape(&UObject::GObjObjects);
    UObject::GlobalSetProperty(V, C, P, O, I);
}
