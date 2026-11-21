// w4_item_0103.cpp -- Versus RVA 0x150c40
// Neutral class names are used because retail does not expose original names here.

typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef unsigned int size_t;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};

extern FMalloc *GMalloc;

// Custom STL-style allocator backed by GMalloc (Magma allocator pattern).
class FEngineAllocator {
public:
    void deallocate(char *Ptr, size_t)
    {
        GMalloc->Free(Ptr);
    }
};

// Microsoft C++ 7.x basic_string<char> SSO storage with GMalloc allocator.
class FEngineString {
public:
    FEngineAllocator _Alval;
    union _Bxty {
        char _Buf[16];
        char *_Ptr;
    } _Bx;
    size_t _Mysize;
    size_t _Myres;

    char *_Myptr()
    {
        return (16 <= _Myres ? _Bx._Ptr : _Bx._Buf);
    }

    void _Eos(size_t NewSize)
    {
        _Mysize = NewSize;
        _Myptr()[NewSize] = 0;
    }

    ~FEngineString()
    {
        if (16 <= _Myres) {
            _Alval.deallocate(_Myptr(), _Myres + 1);
        }
        _Myres = 15;
        _Eos(0);
    }
};

// Base subobject with vtable at 0x10c03304 (scalar deleting dtor at RVA 0x1509e0).
class UnnamedBase_1509e0 {
public:
    virtual ~UnnamedBase_1509e0() {}
};

// Unnamed class at RVA 0x150c40 owning the base subobject and an FEngineString.
class UnnamedClass_150c40 {
public:
    UnnamedBase_1509e0 Base;
    FEngineString Text;

    ~UnnamedClass_150c40();
};

// UnnamedClass_150c40::~UnnamedClass_150c40 (Versus RVA 0x150c40)
UnnamedClass_150c40::~UnnamedClass_150c40()
{
}
