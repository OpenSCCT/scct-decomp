// Work item 0131: Versus RVA 0x3be40-0x3bf4a (UObject/UField/UStruct metadata).
// 0x3bec0 UStruct native constructor is LTCG (this in ESI, InFlags in EAX); near miss.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;
enum ENativeConstructor { EC_NativeConstructor };

extern DWORD GObjInitialized;   // 0x10c9259c
class UObject;
extern UObject *GAutoRegister;  // 0x10c925b0

class UClass;
class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(INT InNum, INT InMax);
    virtual FArchive &operator<<(UObject *&Res);
};

// Called with no arguments from the routine at 0x3be40; name unknown.
void ConditionalCleanup_16f70();

class __declspec(novtable) UObject
{
public:
    virtual ~UObject();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Register();          // 0x4c
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();            // 0x60

    void Serialize(FArchive &Ar);

    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }

    UObject(ENativeConstructor, UClass *InClass, const TCHAR *InName, const TCHAR *InPackageName, DWORD InFlags)
    : Index(-1), HashNext(0), StateFrame(0), _Linker(0), ObjectFlags(InFlags | 0x04000000), Class(InClass)
    {
        *(const TCHAR **)&Outer = InPackageName;
        *(const TCHAR **)&Name = InName;
        *(UObject **)&_LinkerIndex = GAutoRegister;
        GAutoRegister = this;
        if (GetInitialized() && GetClass() == StaticClass())
            GAutoRegister->Register();
    }
    static DWORD GetInitialized() { return GObjInitialized; }
    UClass *GetClass() const { return Class; }

    INT Index;              // 0x04
    UObject *HashNext;      // 0x08
    void *StateFrame;       // 0x0c
    void *_Linker;          // 0x10
    INT _LinkerIndex;       // 0x14
    UObject *Outer;         // 0x18
    DWORD ObjectFlags;      // 0x1c
    INT Name;               // 0x20
    UClass *Class;          // 0x24
};

class __declspec(novtable) UField : public UObject
{
public:
    UField(ENativeConstructor, UClass *InClass, const TCHAR *InName, const TCHAR *InPackageName, DWORD InFlags, UField *InSuperField)
    : UObject(EC_NativeConstructor, InClass, InName, InPackageName, InFlags), SuperField(InSuperField), Next(0) {}
    UField *SuperField;     // 0x28
    UField *Next;           // 0x2c
    void Serialize(FArchive &Ar);
};

// 0x3be70: Super::Serialize, then SuperField and Next.
void UField::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << *(UObject **)&SuperField;
    Ar << *(UObject **)&Next;
}

// 0x3be40: neutral name; vtable slot 8 of the property classes (UArrayProperty,
// UBoolProperty, UByteProperty, UClassProperty, UConst...). Sets object flag
// 0x20000000, runs a cleanup when flag 0x100 is set, then tail-calls slot 24.
class UnnamedObject_3be40 : public UObject
{
public:
    void Slot8_3be40();
};

void UnnamedObject_3be40::Slot8_3be40()
{
    ObjectFlags |= 0x20000000;
    if (ObjectFlags & 0x100)
        ConditionalCleanup_16f70();
    Slot24();
}

class __declspec(novtable) UStruct : public UField
{
public:
    UStruct(ENativeConstructor, INT InSize, const TCHAR *InName, const TCHAR *InPackageName, DWORD InFlags, UStruct *InSuperStruct);
    UField *Children;       // 0x30
    INT PropertiesSize;     // 0x34
    INT Unknown38;          // 0x38 (not set by the native constructor)
    INT Unknown3C;
    INT Unknown40;
    INT Unknown44;
    INT Unknown48;
    INT Unknown4C;
    INT Unknown50;
    INT Unknown54;
    INT Unknown58;
    INT Unknown5C;
    INT Unknown60;
    INT Unknown64;
};

class UClass : public UStruct
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

UStruct::UStruct(ENativeConstructor, INT InSize, const TCHAR *InName, const TCHAR *InPackageName, DWORD InFlags, UStruct *InSuperStruct)
: UField(EC_NativeConstructor, UClass::StaticClass(), InName, InPackageName, InFlags, InSuperStruct),
  Children(0), PropertiesSize(InSize),
  Unknown44(0), Unknown48(0), Unknown4C(0), Unknown50(0), Unknown54(0), Unknown58(0), Unknown5C(0), Unknown60(0), Unknown64(0)
{
}

inline void *operator new(unsigned int, void *p) { return p; }
// Scaffolding for the link, not part of the unit: a UState-like derived
// constructor calls the UStruct native constructor the way UClass's does.
void Escape(void *);
class __declspec(novtable) UState_Driver : public UStruct
{
public:
    UState_Driver(INT InSize, const TCHAR *InName, const TCHAR *InPackageName, DWORD InFlags, UStruct *InSuper);
    INT A, B, C, D, E, F;
};
UState_Driver::UState_Driver(INT InSize, const TCHAR *InName, const TCHAR *InPackageName, DWORD InFlags, UStruct *InSuper)
: UStruct(EC_NativeConstructor, InSize, InName, InPackageName, InFlags, InSuper != this ? InSuper : 0), A(0), B(0), C(0), D(0), E(0)
{
    F = InFlags | 0x12;
    if ((INT)InName == 0x1a || (INT)InName == 0x1b)
        F |= 0x400000;
}
void Driver_3bec0(UState_Driver *Mem, INT Size, const TCHAR *N, const TCHAR *P, DWORD F, UStruct *S)
{
    Escape(&GObjInitialized); Escape(&GAutoRegister);
    new (Mem) UState_Driver(Size, N, P, F, S);
}
