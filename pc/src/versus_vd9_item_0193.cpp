// Work item 0193: RVA 0xe30b0 (destructor) and 0xe3130 (wildcard name compare).
// Class names are neutral; no strings or vtable labels identify them.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);

// Member at +0x2c; its destructor releases through a stdcall helper (0xa7bf30).
void __stdcall UnnamedMember_a7bf30_Destroy(void *);
struct UnnamedMember_e30b0
{
    INT Data[1];
    ~UnnamedMember_e30b0() { UnnamedMember_a7bf30_Destroy(this); }
};

// Function pointer global at 0x10c044e4 (called with no arguments).
extern void (*UnnamedHook_c044e4)();

// Base class; destructor at 0x15ee0.
class UnnamedBase_15ee0
{
public:
    INT Index;          // +0x04
    INT Pad08[5];
    DWORD Flags;        // +0x1c
    INT Pad20[3];
    virtual ~UnnamedBase_15ee0();
    virtual void V1(); virtual void V2(); virtual void V3();
    virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7();
    virtual void V8();
    virtual void Release();   // slot 9
};

// Vtable 0x10c044c0.
class UnnamedClass_e30b0 : public UnnamedBase_15ee0
{
public:
    UnnamedMember_e30b0 Member;   // +0x2c
    virtual ~UnnamedClass_e30b0();
};

UnnamedClass_e30b0::~UnnamedClass_e30b0()
{
    if (Index != -1 && !(Flags & 0x800000)) {
        Flags = (Flags & 0x7f7fffff) | 0x800000;
        UnnamedHook_c044e4();
    }
}

// Case-insensitive compare of equal-length names where '*' matches any one character.
class UnnamedClass_e3130
{
public:
    bool NamesMatch(const TCHAR *A, const TCHAR *B);
};

bool UnnamedClass_e3130::NamesMatch(const TCHAR *A, const TCHAR *B)
{
    INT Len = (INT)wcslen(A);
    if (Len != (INT)wcslen(B))
        return false;
    for (INT i = 0; i < Len; i++) {
        TCHAR CA = *A++;
        TCHAR CB = *B++;
        if (CA == '*' || CB == '*')
            continue;
        if (CA >= 'a' && CA <= 'z') CA += 'A' - 'a';
        if (CB >= 'a' && CB <= 'z') CB += 'A' - 'a';
        if (CA != CB)
            return false;
    }
    return true;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
bool Driver_e3130(UnnamedClass_e3130 *O, const TCHAR *A, const TCHAR *B) { return O->NamesMatch(A, B); }
