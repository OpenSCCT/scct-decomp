// Work item 0159 (wave 3): Versus RVA 0xc97b0-0xc982b.
//   0xc97b0 compiler-generated destructor of a record with three TArray
//           members (+0x08, +0x14, +0x20). Built with /GL and linked with
//           /LTCG: `this` on the stack, ret 4. Record and element names are
//           neutral.
//   0xc9810 AShadowProjector virtual (vtable slot 78) that calls the
//           AProjector version, then sets flag 0x40 on the object at +0x464.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const unsigned short *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const unsigned short *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

template <class T> class TArray : public FArray
{
public:
    __declspec(noinline) ~TArray();
};

class UObject;
// Out of line in another unit (retail 0x1ef20, thiscall).
template <> class TArray<UObject *> : public FArray
{
public:
    ~TArray();
};

template <class T> TArray<T>::~TArray()
{
    Remove(0, ArrayNum, sizeof(T));
}

#pragma pack(push, 4)

// Element types without destructors; only their sizes are known.
struct UnnamedElement_20 { BYTE Body[0x20]; }; // TArray dtor retail 0xaee510
struct UnnamedElement_34 { BYTE Body[0x34]; }; // TArray dtor retail 0xa78e00

class UnnamedRecord_c97b0
{
public:
    __declspec(noinline) ~UnnamedRecord_c97b0() {}
    INT Field00;
    INT Field04;
    TArray<UnnamedElement_20> Array08;
    TArray<UnnamedElement_34> Array14;
    TArray<UObject *> Objects20;
};

#pragma pack(pop)

// ---------------------------------------------------------------------------
// 0xc9810: AShadowProjector override of vtable slot 78 (the method's engine
// name is not recovered). The object at +0x464 is unnamed; bit 0x40 of its
// word at +0x15c is set after the AProjector version runs.
struct UnnamedTarget_c9810
{
    BYTE Pad[0x15c];
    DWORD Flags;
};

class AProjector
{
public:
    virtual void V00();
    virtual void V01();
    virtual void V02();
    virtual void V03();
    virtual void V04();
    virtual void V05();
    virtual void V06();
    virtual void V07();
    virtual void V08();
    virtual void V09();
    virtual void V10();
    virtual void V11();
    virtual void V12();
    virtual void V13();
    virtual void V14();
    virtual void V15();
    virtual void V16();
    virtual void V17();
    virtual void V18();
    virtual void V19();
    virtual void V20();
    virtual void V21();
    virtual void V22();
    virtual void V23();
    virtual void V24();
    virtual void V25();
    virtual void V26();
    virtual void V27();
    virtual void V28();
    virtual void V29();
    virtual void V30();
    virtual void V31();
    virtual void V32();
    virtual void V33();
    virtual void V34();
    virtual void V35();
    virtual void V36();
    virtual void V37();
    virtual void V38();
    virtual void V39();
    virtual void V40();
    virtual void V41();
    virtual void V42();
    virtual void V43();
    virtual void V44();
    virtual void V45();
    virtual void V46();
    virtual void V47();
    virtual void V48();
    virtual void V49();
    virtual void V50();
    virtual void V51();
    virtual void V52();
    virtual void V53();
    virtual void V54();
    virtual void V55();
    virtual void V56();
    virtual void V57();
    virtual void V58();
    virtual void V59();
    virtual void V60();
    virtual void V61();
    virtual void V62();
    virtual void V63();
    virtual void V64();
    virtual void V65();
    virtual void V66();
    virtual void V67();
    virtual void V68();
    virtual void V69();
    virtual void V70();
    virtual void V71();
    virtual void V72();
    virtual void V73();
    virtual void V74();
    virtual void V75();
    virtual void V76();
    virtual void V77();
    virtual void Slot78(); // retail 0xc9470
    BYTE PadActor[0x460];
};

class AShadowProjector : public AProjector
{
public:
    virtual void Slot78();
    UnnamedTarget_c9810 *ShadowTarget; // +0x464
};

// RVA 0xc9810
void AShadowProjector::Slot78()
{
    AProjector::Slot78();
    if (ShadowTarget)
        ShadowTarget->Flags |= 0x40;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c97b0(UnnamedRecord_c97b0 *R) { Escape(&GMalloc); R->~UnnamedRecord_c97b0(); Escape(R); }
