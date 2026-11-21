// Work item 0025: Versus RVA 0x5f90, 0x6000, 0x6080.
//
// All three take `this` on the stack (ret 4 / ret 0x14): link-time code
// generation rewrote a thiscall destructor or constructor. They are written
// as __stdcall functions:
// - The destructors take a by-value "frame" handle to the object. MSVC
//   destroys by-value parameters in the callee, so the handle's destructor
//   chain reproduces the original destructor: body first, then members, then
//   the base, with the same unwind states.
// - The constructor returns the object by value, so the class constructor is
//   built straight into the caller's storage (hidden return pointer).
//
// Names are neutral: no vtable label identifies these classes. The base of
// UnnamedClass_6000 (RVA 0x5c20 / 0x5ca0, item 0022) is a window class that
// reads a ".Split" position from the "WindowPositions" config section.
typedef unsigned long DWORD;

// ---------------------------------------------------------------------------
// Object embedded at +0x104 of UnnamedClass_6000. Its base part is built by
// RVA 0x5e10 (fastcall, item 0023) and destroyed by RVA 0x5ed0.
struct UnnamedObject_5f90;

// Retail RVA 0x5e10: builds the base part of UnnamedObject_5f90.
UnnamedObject_5f90* __fastcall ConstructObject_5e10(DWORD A, DWORD MemberArg, UnnamedObject_5f90* Mem, void* Owner, DWORD C);
// Vtables of UnnamedObject_5f90 (retail 0x10c0e150 and 0x10c0e140).
extern void* const UnnamedObject_5f90_vftable[];
extern void* const UnnamedObject_5f90_vftable2[];

struct UnnamedObject_5f90
{
    void* const* VfTable;      // 0x00
    void* const* VfTable2;     // 0x04
    DWORD Pad08[0x12];
    DWORD Field50;             // 0x50
    DWORD Field54;             // 0x54
    DWORD Array[3];            // 0x58 (TArray-like: data, num, max)

    // Inline constructor body used by the 0x6080 constructor.
    __forceinline void Init(void* Owner, DWORD B, DWORD C, DWORD D)
    {
        ConstructObject_5e10(0, C, this, Owner, B);
        Field54 = 0;
        VfTable = UnnamedObject_5f90_vftable;
        VfTable2 = UnnamedObject_5f90_vftable2;
        Field50 = D;
        Array[0] = 0;
        Array[1] = 0;
        Array[2] = 0;
    }
};

// Retail 0x10a7bf30: releases a TArray-like member, `this` on the stack.
void __stdcall UnnamedArray_Release(DWORD* Array);
// Retail RVA 0x5ed0: base destructor of UnnamedObject_5f90.
void __stdcall UnnamedObject_5ed0_Destructor(UnnamedObject_5f90* Self);

struct UnnamedObject_5f90_Frame
{
    UnnamedObject_5f90* Self;
    ~UnnamedObject_5f90_Frame() { UnnamedObject_5ed0_Destructor(Self); }
};

struct UnnamedArray_Guard
{
    DWORD* Array;
    UnnamedArray_Guard(DWORD* InArray) : Array(InArray) {}
    ~UnnamedArray_Guard() { UnnamedArray_Release(Array); }
};

// Retail RVA 0x5f90: destructor of UnnamedObject_5f90.
void __stdcall UnnamedObject_5f90_Destructor(UnnamedObject_5f90_Frame Base)
{
    UnnamedArray_Guard Member(Base.Self->Array);
}

// The same function seen from callers, which push the object pointer.
void __stdcall UnnamedObject_5f90_Destroy(UnnamedObject_5f90* Self);

// ---------------------------------------------------------------------------
// UnnamedClass_6000: derives from the window class of RVA 0x5c20 / 0x5ca0.
struct UnnamedClass_6000
{
    void* const* VfTable;      // 0x00
    DWORD Field04;
    DWORD Field08;
    DWORD Field0C;
    DWORD Flags;               // 0x10
    DWORD Pad14[10];
    void* const* VfTable2;     // 0x3c
    DWORD Pad40[0x31];
    UnnamedObject_5f90 Sub;    // 0x104
    __declspec(dllimport) void Destroy();
};

// Vtables of UnnamedClass_6000 (retail 0x10c0db20 and 0x10c0db10).
extern void* const UnnamedClass_6000_vftable[];
extern void* const UnnamedClass_6000_vftable2[];

// Retail RVA 0x5c20 / 0x5ca0: base destructor and constructor.
void __stdcall UnnamedBase_5c20_Destructor(UnnamedClass_6000* Self);
void __stdcall UnnamedBase_5ca0_Construct(UnnamedClass_6000* Self, DWORD A);

// Destructor frame of UnnamedClass_6000, laid out like the class it tears
// down: an empty base part (destroyed last, by RVA 0x5c20) and a member part
// holding the object pointer (the member at +0x104, destroyed by RVA 0x5f90).
struct UnnamedClass_6000_BasePart
{
    ~UnnamedClass_6000_BasePart();
};

struct UnnamedClass_6000_SubPart
{
    UnnamedClass_6000* Self;
    ~UnnamedClass_6000_SubPart() { UnnamedObject_5f90_Destroy(&Self->Sub); }
};

struct UnnamedClass_6000_Frame : public UnnamedClass_6000_BasePart
{
    UnnamedClass_6000_SubPart S;

    // The original destructor body.
    __forceinline ~UnnamedClass_6000_Frame()
    {
        S.Self->VfTable = UnnamedClass_6000_vftable;
        S.Self->VfTable2 = UnnamedClass_6000_vftable2;
        if (!(S.Self->Flags & 1))
        {
            S.Self->Flags |= 1;
            S.Self->Destroy();
        }
    }
};

inline UnnamedClass_6000_BasePart::~UnnamedClass_6000_BasePart()
{
    UnnamedBase_5c20_Destructor(static_cast<UnnamedClass_6000_Frame*>(this)->S.Self);
}

// Retail RVA 0x6000: destructor of UnnamedClass_6000 (all work happens as
// the frame parameter is destroyed).
void __stdcall UnnamedClass_6000_Destructor(UnnamedClass_6000_Frame Frame)
{
}

// ---------------------------------------------------------------------------
// Constructor (retail RVA 0x6080).
struct UnnamedBase_5ca0
{
    void* const* VfTable;      // 0x00
    DWORD Pad04[14];
    void* const* VfTable2;     // 0x3c
    DWORD Pad40[0x31];
    UnnamedBase_5ca0(DWORD A) { UnnamedBase_5ca0_Construct((UnnamedClass_6000*)this, A); }
    ~UnnamedBase_5ca0() { UnnamedBase_5c20_Destructor((UnnamedClass_6000*)this); }
};

struct UnnamedClass_6000_Object : public UnnamedBase_5ca0
{
    UnnamedObject_5f90 Sub;    // 0x104

    __forceinline UnnamedClass_6000_Object(DWORD A, DWORD B, DWORD C, DWORD D)
    : UnnamedBase_5ca0(A)
    {
        VfTable = UnnamedClass_6000_vftable;
        VfTable2 = UnnamedClass_6000_vftable2;
        Sub.Init(this, B, C, D);
    }
};

// Retail RVA 0x6080: builds UnnamedClass_6000 in the caller's storage.
UnnamedClass_6000_Object __stdcall UnnamedClass_6000_Construct(DWORD A, DWORD B, DWORD C, DWORD D)
{
    return UnnamedClass_6000_Object(A, B, C, D);
}
