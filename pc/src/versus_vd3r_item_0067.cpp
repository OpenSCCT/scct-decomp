// Work item 0067 (LTCG retry): RVA 0x11610.
// Allocates and constructs a 0x30-byte object through GMalloc. The class is
// not identified yet (vtable 0x10c0d2a0, constructor at RVA 0x10420), so it
// carries a neutral name. The constructor was link-time compiled and takes
// `this` on the stack (ret 4).

typedef unsigned short TCHAR;
typedef unsigned long DWORD;
typedef unsigned int size_t;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};

extern FMalloc* GMalloc;

inline void* operator new(size_t Size, const TCHAR* Tag)
{
    return GMalloc->Malloc(Size, Tag);
}

inline void operator delete(void* Ptr, const TCHAR* Tag)
{
    GMalloc->Free(Ptr);
}

// Unreal's dynamic array storage (destructor not part of this unit).
class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
protected:
    void* Data;
    int ArrayNum;
    int ArrayMax;
};

// Member at +4: a TMap-shaped hash map (Pairs, Hash, HashCount = 8, then
// Rehash), constructor at RVA 0x14520, Rehash at RVA 0x14c10.
class TMapBase_14520
{
public:
    TMapBase_14520() : Hash(0), HashCount(8) { Rehash(); }
    ~TMapBase_14520();
    void Rehash();
protected:
    FArray Pairs;
    int* Hash;
    int HashCount;
};

// Base class with vtable 0x10c0d248.
class UnnamedBase_d248
{
public:
    virtual ~UnnamedBase_d248();
};

// Derived class with vtable 0x10c0d2a0.
class UnnamedClass_10420 : public UnnamedBase_d248
{
public:
    UnnamedClass_10420();
    virtual ~UnnamedClass_10420();
    TMapBase_14520 Map;
    int Field18, Field1C, Field20, Field24, Field28, Field2C;
};

#pragma auto_inline(off)
UnnamedClass_10420::UnnamedClass_10420()
    : Field18(0), Field1C(0), Field20(0), Field24(0), Field28(0), Field2C(0)
{
}
#pragma auto_inline(on)

extern const TCHAR UnnamedClass_10420_Tag[];

UnnamedClass_10420* CreateUnnamedClass_10420()
{
    return new(UnnamedClass_10420_Tag) UnnamedClass_10420;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_11610() { Escape(&GMalloc); Escape(CreateUnnamedClass_10420()); }
