// Work item 0018: Versus RVA 0x5890, a destructor of the same shape as
// RVA 0x50a0 (item 0012), but with `this` passed on the stack and the base
// destructor called the same way: the calling convention was rewritten by
// link-time code generation, so it is written here as a __stdcall function
// taking the object. The base destructor runs from a guard object so that
// it is also called during unwinding, as the compiler arranges for a real
// destructor; the guard is the by-value parameter, destroyed by the callee. Class names are neutral: no vtable label or string identifies
// the class.
typedef unsigned long DWORD;

struct UnnamedClass_5890
{
    void* const* VfTable;
    DWORD Field4;
    DWORD Field8;
    DWORD FieldC;
    DWORD Flags;
    __declspec(dllimport) void Destroy();
};

// Vtable of UnnamedClass_5890 (retail 0x10c0e518).
extern void* const UnnamedClass_5890_vftable[];

// Base class destructor (retail RVA 0x215970), `this` on the stack.
void __stdcall UnnamedBase_5890_Destructor(UnnamedClass_5890* Self);

struct UnnamedBase_5890_Guard
{
    UnnamedClass_5890* Self;
    UnnamedBase_5890_Guard(UnnamedClass_5890* InSelf) : Self(InSelf) {}
    ~UnnamedBase_5890_Guard() { UnnamedBase_5890_Destructor(Self); }
};

void __stdcall UnnamedClass_5890_Destructor(UnnamedBase_5890_Guard Guard)
{
    Guard.Self->VfTable = UnnamedClass_5890_vftable;
    UnnamedClass_5890* Self = Guard.Self;
    if (!(Self->Flags & 1))
    {
        Self->Flags |= 1;
        Self->Destroy();
    }
}
