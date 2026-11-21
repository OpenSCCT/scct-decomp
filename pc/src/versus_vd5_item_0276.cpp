// Unnamed class at 0xfc660: vtable at +0, FString at +8. Its base class
// (vtable 0x10c03dc0) has an inline destructor that only resets the vtable.
// The scalar deleting destructor at 0xfc630 calls this one with `this` on the
// stack (LTCG calling convention) and frees through GMalloc.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FString {
public:
    TCHAR *Data; INT ArrayNum; INT ArrayMax;
    FString();
    ~FString();
};

class UnnamedBase_fc660 {
public:
    virtual ~UnnamedBase_fc660() {}
    void operator delete(void *Ptr) { GMalloc->Free(Ptr); }
    INT Pad;
};

class UnnamedClass_fc660 : public UnnamedBase_fc660 {
public:
    FString Name;
    UnnamedClass_fc660() {}
};

// The destructor is compiler-generated.

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_fc660(void *Mem) { Escape(&GMalloc); UnnamedClass_fc660 *P = new(Mem) UnnamedClass_fc660; Escape(P); delete P; }
