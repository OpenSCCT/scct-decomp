// Work item 0113: RVA 0x1da30, the scalar deleting destructor shared (by
// identical-COMDAT folding) by nine FArchive subclasses whose destructors
// are implicit; their vtables at 0x1030cce0, 0x1030cd40, 0x1030cda0,
// 0x1030ce00, 0x1030cf38, 0x1030cf98, 0x1030cff8, 0x1030d058 and 0x1030d9a0
// all start with it. The subclass's own vtable store is dead (the base
// destructor overwrites it) and is dropped, leaving a call to
// FArchive::~FArchive (0xc9c0, stores the FArchive vtable 0x10c0e918), which
// the LTCG link gives `this` in EAX. operator delete frees through GMalloc.
// The subclass is unnamed here (FArchive_1da30 is a neutral name): any of
// the nine produces the same bytes.
typedef unsigned short TCHAR;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void operator delete(void *Ptr)
{
    GMalloc->Free(Ptr);
}
inline void *operator new(unsigned int, void *Mem)
{
    return Mem;
}

class FArchive
{
public:
    FArchive();
    virtual ~FArchive();
};

// RVA 0xc9c0
FArchive::~FArchive()
{
}

// Neutral name; one of the FArchive subclasses with an implicit destructor.
class FArchive_1da30 : public FArchive
{
public:
    FArchive_1da30() {}
};

// RVA 0x1da30 is the compiler-generated FArchive_1da30::`scalar deleting
// destructor' (??_G).

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_1da30(FArchive_1da30 *A, void *Mem)
{
    Escape(&GMalloc);
    new (Mem) FArchive_1da30;
    delete A;
}
