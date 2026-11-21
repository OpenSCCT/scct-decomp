// Work item 0141 (wave 3): Versus RVA 0xc21f0-0xc269a.
// This unit was built with /GL and linked with /LTCG, so most functions here
// take `this` or arguments in registers (ESI, EAX).
//   0xc21f0 constructor of a 0x110-byte record (UnnamedRecord_110; its
//           destructor is retail 0xa60a0), `this` on the stack, ret 4.
//   0xc2300 TArray<UnnamedRecord_110>::Empty, `this` in ESI.
//   0xc2340 TArray<UnnamedElement_10>::Empty, `this` in ESI.
//   0xc2380 TFieldIterator<T>::IterateToNext, `this` in ESI (T's static class
//           at 0x10cc8958; UObject::IsA inlined).
//   0xc23e0 operator<<(FArchive&, UnnamedSerial_44&), Ar in ECX, value in EAX.
//   0xc24c0 operator<<(FArchive&, UnnamedSerial_90&), Ar in ESI, value in EAX;
//           only serialised when the archive is not persistent.
// Names are neutral where no strings or vtable labels identify the class.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

class FName { public: INT Index; };

class FArchive
{
public:
    virtual ~FArchive() {}
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(void *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive &operator<<(class FName &N);
    virtual FArchive &operator<<(class UObject *&Res);

    INT ArVer, ArNetVer, ArLicenseeVer;
    UBOOL ArIsLoading, ArIsSaving, ArIsTrans, ArIsPersistent;
    UBOOL ArForEdit, ArForClient, ArForServer;
    UBOOL ArIsError, ArIsCriticalError;
    INT Ar34, Ar38, Ar3C;

    void ByteOrderSerialize(void *V, INT Length) { Serialize(V, Length); }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.ByteOrderSerialize(&I, sizeof(I)); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.ByteOrderSerialize(&F, sizeof(F)); return Ar; }
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Empty(INT ElementSize, INT Slack); // RVA 0x4550
};

template <class T> class TArray : public FArray
{
public:
    __declspec(noinline) void Empty(INT Slack = 0)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&((T *)Data)[i])->~T();
        FArray::Empty(sizeof(T), Slack);
    }
};

// ---------------------------------------------------------------------------
// 0xc21f0: UnnamedRecord_110 constructor. Layout from the constructor and the
// destructor at 0xa60a0, which destroys arrays at 0x00, 0x0c, 0x1c, 0x28, the
// strings inside the sub-objects at 0x38 and 0x54, the array at 0x8c and the
// four lists.

extern QWORD GUnnamedSerialCounter; // 0x10c96930

#pragma pack(push, 4)

// Dynamic arrays; each kind has its own out-of-line destructor in retail.
class UnnamedArrayA { public: UnnamedArrayA() : Data(0), Num(0), Max(0) {} ~UnnamedArrayA(); void *Data; INT Num, Max; }; // dtor 0xafb4d0
class UnnamedArrayB { public: UnnamedArrayB() : Data(0), Num(0), Max(0) {} ~UnnamedArrayB(); void *Data; INT Num, Max; }; // dtor 0xaf20d0
class UnnamedArrayC { public: UnnamedArrayC() : Data(0), Num(0), Max(0) {} ~UnnamedArrayC(); void *Data; INT Num, Max; }; // dtor 0xaee510
class UnnamedString { public: UnnamedString() : Data(0), Num(0), Max(0) {} ~UnnamedString(); void *Data; INT Num, Max; };   // dtor 0x90c4e0

// Sub-object constructed at retail 0x1126e0 (this in ESI, vtable 0x10c037f4).
class UnnamedSub_1c
{
public:
    __declspec(noinline) UnnamedSub_1c()
    {
        Id = GUnnamedSerialCounter++ * 0x100 + 0xe2;
        D = 0;
    }
    virtual ~UnnamedSub_1c() {}
    UnnamedString Str;
    QWORD Id;
    INT D;
};

// Sub-object constructed at retail 0xa5140 (this in ESI, vtable 0x10c0a020).
class UnnamedSub_2c
{
public:
    __declspec(noinline) UnnamedSub_2c()
    {
        A = 0; B = 0;
        Id = GUnnamedSerialCounter++ * 0x100 + 0xe1;
        H = 0; I = 0;
        Flag = 1;
    }
    virtual ~UnnamedSub_2c() {}
    INT A, B;
    QWORD Id;
    INT Flag;
    INT H, I;
    UnnamedArrayC Array;
};

// Four embedded lists, each a vtable and five words (vtables 0x10c09f88,
// 0x10c09f90, 0x10c09f80, 0x10c09f98).
class UnnamedList_18
{
public:
    UnnamedList_18() { Data = 0; Num = 0; Extra0 = 0; Extra1 = 0; Max = 0; }
    void *Data;
    INT Num;
    INT Max;
    INT Extra0;
    INT Extra1;
};
class UnnamedList_98 : public UnnamedList_18 { public: virtual ~UnnamedList_98(); }; // dtor 0xa5ed0
class UnnamedList_b0 : public UnnamedList_18 { public: virtual ~UnnamedList_b0(); }; // dtor 0xa5b80
class UnnamedList_c8 : public UnnamedList_18 { public: virtual ~UnnamedList_c8(); }; // dtor 0xa6180
class UnnamedList_e0 : public UnnamedList_18 { public: virtual ~UnnamedList_e0(); }; // dtor 0xa5920

class UnnamedRecord_110
{
public:
    UnnamedRecord_110();
    // RVA 0xa60a0 (out of line, `this` on the stack, ret 4).
    __declspec(noinline) ~UnnamedRecord_110() {}

    UnnamedArrayA Array00;
    UnnamedArrayA Array0C;
    INT Field18;
    UnnamedArrayB Array1C;
    UnnamedArrayB Array28;
    UnnamedSub_1c Sub34;
    UnnamedSub_1c Sub50;
    UnnamedSub_2c Sub6C;
    UnnamedList_98 List98;
    UnnamedList_b0 ListB0;
    UnnamedList_c8 ListC8;
    UnnamedList_e0 ListE0;
    INT FieldF8[6]; // not set by the constructor
};

// Near miss: retail keeps an EH frame (with no state stores) and takes `this`
// on the stack; here the link proves the sub-object constructors cannot throw,
// drops the frame and passes `this` in EDI. The body otherwise matches.
__declspec(noinline) UnnamedRecord_110::UnnamedRecord_110()
{
}

#pragma pack(pop)

// ---------------------------------------------------------------------------
// 0xc2340: element type whose destructor is retail 0xa63f0.
class UnnamedElement_10
{
public:
    ~UnnamedElement_10();
    INT Pad[4];
};

// ---------------------------------------------------------------------------
// 0xc2380: TFieldIterator<T>::IterateToNext.
class UClass;
class UObject
{
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
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
    virtual UStruct *GetInheritanceSuper();
};
class UClass : public UStruct {};

class UnnamedFieldClass // static class at 0x10cc8958
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

inline UBOOL IsAInline(const UObject *Obj, UClass *SomeBase)
{
    for (UClass *TempClass = Obj->Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

template <class T> class TFieldIterator
{
public:
    UStruct *Struct;
    UField *Field;
    void IterateToNext()
    {
        while (Struct)
        {
            while (Field)
            {
                if (IsAInline(Field, T::StaticClass()))
                    return;
                Field = Field->Next;
            }
            Struct = Struct->GetInheritanceSuper();
            if (Struct)
                Field = Struct->Children;
        }
    }
};

// ---------------------------------------------------------------------------
// 0xc23e0. FArchive slot 0x1c is operator<<(FName&): MSVC lays overloaded
// virtuals out in reverse order of declaration.
struct FVector
{
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }
};

struct UnnamedSerial_44
{
    INT A;
    FName B;
    FVector C;
    FVector D;
    INT Pad20;
    FLOAT E[8];
};

FArchive &operator<<(FArchive &Ar, UnnamedSerial_44 &V)
{
    return Ar << V.A << V.B << V.C << V.D
              << V.E[0] << V.E[1] << V.E[2] << V.E[3] << V.E[4] << V.E[5] << V.E[6] << V.E[7];
}

// ---------------------------------------------------------------------------
// 0xc24c0
struct UnnamedSerial_90
{
    FName A;
    INT B;
    FName C;
    INT D[25];   // 0x0c..0x6c
    FName E;     // 0x70
    INT Pad74;
    FName F;     // 0x78
    INT G[5];    // 0x7c..0x8c
};

FArchive &operator<<(FArchive &Ar, UnnamedSerial_90 &V)
{
    if (!Ar.ArIsPersistent)
    {
        Ar << V.A;
        Ar << V.B;
        Ar << V.C;
        Ar << V.D[0];  Ar << V.D[1];  Ar << V.D[2];  Ar << V.D[3];  Ar << V.D[4];
        Ar << V.D[5];  Ar << V.D[6];  Ar << V.D[7];  Ar << V.D[8];  Ar << V.D[9];
        Ar << V.D[10]; Ar << V.D[11]; Ar << V.D[12]; Ar << V.D[13]; Ar << V.D[14];
        Ar << V.D[15]; Ar << V.D[16]; Ar << V.D[17]; Ar << V.D[18]; Ar << V.D[19];
        Ar << V.D[21]; Ar << V.D[20]; Ar << V.D[22]; Ar << V.D[23]; Ar << V.D[24];
        Ar << V.E;
        Ar << V.F;
        Ar << V.G[0]; Ar << V.G[1]; Ar << V.G[2]; Ar << V.G[3]; Ar << V.G[4];
    }
    return Ar;
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.
void Escape(void *);
template class TArray<UnnamedRecord_110>;
template class TArray<UnnamedElement_10>;
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_c21f0(void *Mem) { Escape(new (Mem) UnnamedRecord_110); }
void Driver_c2300(TArray<UnnamedRecord_110> *A, INT Slack) { A->Empty(Slack); }
void Driver_c2340(TArray<UnnamedElement_10> *A, INT Slack) { A->Empty(Slack); }
void Driver_c2380(TFieldIterator<UnnamedFieldClass> *It) { It->IterateToNext(); }
void Driver_c23e0(FArchive *Ar, UnnamedSerial_44 *V) { Escape(&(*Ar << *V)); }
void Driver_c24c0(FArchive *Ar, UnnamedSerial_90 *V) { Escape(&(*Ar << *V)); }
