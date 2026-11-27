// Work item 0250: DXT5 block decompression and a small counted-id object.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;
typedef unsigned __int64 QWORD;

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

#include "versus_dxt5_decode.inl"

// RVA 0xf3c10: constructor of an unnamed object with a vtable (0x10c04118),
// a 64-bit id taken from a global counter, an owner value and a flag.
// LTCG: this in ESI, InOwner in EAX. Names are neutral; the class is not identified.
#pragma pack(push, 4)
extern QWORD UnnamedClass_3c10_NextId;
class UnnamedClass_3c10
{
public:
    QWORD Id;
    INT Owner;
    INT Flag;
    UnnamedClass_3c10(INT InOwner);
    virtual void Func0();
    virtual INT Func1();
    virtual INT Func2();
    virtual INT Func3();
    virtual INT Func4();
    virtual INT Func5();
    virtual INT Func6();
    virtual INT Func7();
};
#pragma pack(pop)
UnnamedClass_3c10::UnnamedClass_3c10(INT InOwner)
    : Owner(InOwner)
{
    QWORD NewId = UnnamedClass_3c10_NextId++ * 0x100 + 0xe0;
    Id = NewId;
    Flag = 1;
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *P) { return P; }
void Escape(void *);
class FMalloc { public: virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0; };
extern FMalloc *GMalloc;
extern const TCHAR DXTTag[];
void Driver_f3820(const DWORD *S, INT W, INT H, DWORD **Out)
{
    DWORD *D = (DWORD *)GMalloc->Malloc(W * H * 4, DXTTag);
    *Out = D;
    DecompressDXT5(S, W, H, D);
}
struct FInner_3c10 { char Pad[0xc0]; INT Owner; };
struct FOuter_3c10 { INT Pad; FInner_3c10 *Inner; INT Run0(); INT Run1(); INT Run2(); INT Run3(); INT Run4(); INT Run5(); INT Run6(); };
INT FOuter_3c10::Run0()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func1();
    return 4;
}
INT FOuter_3c10::Run1()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func2();
    return 4;
}
INT FOuter_3c10::Run2()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func3();
    return 4;
}
INT FOuter_3c10::Run3()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func4();
    return 4;
}
INT FOuter_3c10::Run4()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func5();
    return 4;
}
INT FOuter_3c10::Run5()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func6();
    return 4;
}
INT FOuter_3c10::Run6()
{
    if (Inner->Owner)
        return UnnamedClass_3c10(Inner->Owner).Func7();
    return 4;
}
void Driver_f3c10(FOuter_3c10 *O)
{
    O->Run0();
    O->Run1();
    O->Run2();
    O->Run3();
    O->Run4();
    O->Run5();
    O->Run6();
}
