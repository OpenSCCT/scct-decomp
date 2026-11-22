// Work item 0220 (w3): Versus RVA 0xedec0.
// DECLARE_CLASS operator new for an unrecovered UObject class whose
// PrivateStaticClass sits at 0x10cbfe70; compiled with /GL (SetFlags arrives
// in ECX). Kept apart from w3_item_0220.cpp because the FName copy here is a
// plain dword push, which the event thunks' FName (with a copy constructor)
// cannot produce.
typedef int INT;
typedef unsigned long DWORD;

enum EName { NAME_None = 0 };

class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
};

class UClass;
class FOutputDevice;
extern FOutputDevice *GError;

class UObject {
public:
    static UObject *StaticAllocateObject(UClass *Class, UObject *InOuter, FName InName,
        DWORD SetFlags, UObject *Template, FOutputDevice *Error, UObject *Ptr,
        UObject *SubobjectRoot);
};

// Owning class not recovered.
class UnnamedClass_edec0 : public UObject {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    __declspec(noinline) void *operator new(unsigned int Size, UObject *Outer, FName Name, DWORD SetFlags)
    {
        return StaticAllocateObject(StaticClass(), Outer, Name, SetFlags, 0, GError, 0, 0);
    }
};

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void *Driver_edec0(UObject *O, FName N, DWORD F)
{
    Escape(&GError);
    return UnnamedClass_edec0::operator new(sizeof(UnnamedClass_edec0), O, N, F);
}
