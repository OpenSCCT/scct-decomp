// w4_item_0104.cpp -- Versus work item 0104 (RVA 0x151160 - 0x151337)

typedef unsigned short WORD;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef int INT;

// ---------------------------------------------------------------------------
// 0x151160 & 0x1511d0: neutral names (no class/string evidence in work item)
// ---------------------------------------------------------------------------

struct FShortPair_151160 {
    WORD First;
    WORD Second;

    FShortPair_151160(WORD InFirst, WORD InSecond)
        : First(InFirst), Second(InSecond) {}
};

class ISurface_151160 {
public:
    virtual void Slot00() = 0;
    virtual void Slot01() = 0;
    virtual void Slot02() = 0;
    virtual void Slot03() = 0;
    virtual void Slot04() = 0;
    virtual void Slot05() = 0;
    virtual void Slot06() = 0;
    virtual void Slot07() = 0;
    virtual void Slot08() = 0;
    virtual void Slot09() = 0;
    virtual void Slot10() = 0;
    virtual void Slot11() = 0;
    virtual void Slot12() = 0;
    virtual void Slot13() = 0;
    virtual void Slot14() = 0;
    virtual void Slot15() = 0;
    virtual void Slot16() = 0;
    virtual void Slot17() = 0;
    virtual void Slot18() = 0;
    virtual void Slot19() = 0;
    virtual void Slot20() = 0;
    virtual void Slot21() = 0;
    virtual void Slot22() = 0;
    virtual void Slot23() = 0;
    virtual void Slot24() = 0;
    virtual void Slot25() = 0;
    virtual INT GetWidth() = 0;   // +0x68
    virtual INT GetHeight() = 0;  // +0x6c
};

struct FShortRect_151160 {
    FShortPair_151160 RangeX;
    FShortPair_151160 RangeY;

    FShortRect_151160(WORD Width, WORD Height)
        : RangeX(0, Width), RangeY(0, Height) {}
};

class UnnamedWidget_151160 {
public:
    DWORD unk_00[9];
    FShortRect_151160 Bounds;  // +0x24
    ISurface_151160 *Surface;  // +0x2c

    void SetSurface(ISurface_151160 *InSurface);
    FShortPair_151160 GetSurfaceSize() const;
};

// UnnamedWidget_151160::SetSurface (RVA 0x151160)
// Stores the surface pointer and resets the 16-bit bounds to its dimensions (or zero).
void UnnamedWidget_151160::SetSurface(ISurface_151160 *InSurface)
{
    Surface = InSurface;
    if (InSurface != 0) {
        Bounds = FShortRect_151160(Surface->GetWidth(), Surface->GetHeight());
    } else {
        Bounds = FShortRect_151160(0, 0);
    }
}

// UnnamedWidget_151160::GetSurfaceSize (RVA 0x1511d0)
// Returns the surface's width and height as a 16-bit pair, or (0, 0) if null.
FShortPair_151160 UnnamedWidget_151160::GetSurfaceSize() const
{
    if (Surface != 0) {
        return FShortPair_151160(Surface->GetWidth(), Surface->GetHeight());
    }
    return FShortPair_151160(0, 0);
}

// ---------------------------------------------------------------------------
// 0x151210, 0x151250, 0x151280: Dinkumware basic_string<char> with custom allocator
// ---------------------------------------------------------------------------

class FCustomHeap {
public:
    virtual void *Alloc(UINT Size) = 0;
    virtual void *Realloc(void *Ptr, UINT Size) = 0;
    virtual void Free(void *Ptr) = 0;
};

// Global allocator pointer (retail 0x10c73bf0; vtable +0x08 is Free).
extern FCustomHeap *GCustomHeap;

struct FCustomCharAllocator {
    void deallocate(char *Ptr, UINT) {
        GCustomHeap->Free(Ptr);
    }
};

extern "C" UINT __cdecl strlen(const char *);
#pragma intrinsic(strlen)

extern "C" void * __cdecl memcpy(void *, const void *, UINT);
#pragma intrinsic(memcpy)

class FCustomAnsiString {
public:
    enum { _BUF_SIZE = 16 };

    FCustomCharAllocator _Alval;
    union _Bxty {
        char _Buf[_BUF_SIZE];
        char *_Ptr;
    } _Bx;
    UINT _Mysize;
    UINT _Myres;

    FCustomAnsiString(const char *_Ptr);
    ~FCustomAnsiString();
    FCustomAnsiString &assign(const char *_Ptr, UINT _Count);
    char &operator[](UINT _Off);

    char *_Myptr() {
        return (_BUF_SIZE <= _Myres ? _Bx._Ptr : _Bx._Buf);
    }

    void _Eos(UINT _Newsize) {
        _Bx._Buf[_Mysize = _Newsize] = '\0';
    }

    void _Tidy(bool _Built = false, UINT _Newsize = 0) {
        if (_Built && _BUF_SIZE <= _Myres) {
            char *_Ptr = _Bx._Ptr;
            if (0 < _Newsize) {
                memcpy(_Bx._Buf, _Ptr, _Newsize);
            }
            _Alval.deallocate(_Ptr, _Myres + 1);
        }
        _Myres = _BUF_SIZE - 1;
        _Eos(_Newsize);
    }
};

// FCustomAnsiString::FCustomAnsiString (RVA 0x151210)
// Initializes the small-string buffer and assigns a C string.
FCustomAnsiString::FCustomAnsiString(const char *_Ptr)
{
    _Tidy(false);
    assign(_Ptr, strlen(_Ptr));
}

// FCustomAnsiString::~FCustomAnsiString (RVA 0x151250)
// Releases heap storage if allocated and resets to an empty small string.
FCustomAnsiString::~FCustomAnsiString()
{
    _Tidy(true);
}

// FCustomAnsiString::operator[] (RVA 0x151280)
// Returns a reference to the character at _Off in heap or inline storage.
char &FCustomAnsiString::operator[](UINT _Off)
{
    return *(_Myptr() + _Off);
}

// ---------------------------------------------------------------------------
// 0x1512a0: std::basic_ostringstream<char, char_traits<char>, CustomAlloc>
// ---------------------------------------------------------------------------

class __declspec(dllimport) BasicStreambuf {
public:
    virtual ~BasicStreambuf();
};

class __declspec(dllimport) BasicIos {
protected:
    BasicIos();
public:
    virtual ~BasicIos();
};

class __declspec(dllimport) BasicOstream : virtual public BasicIos {
public:
    BasicOstream(BasicStreambuf *_Strbuf, bool _Isstd = false);
    virtual ~BasicOstream();
};

class CustomStringbuf : public BasicStreambuf {
public:
    DWORD unk_04[17];
    CustomStringbuf(int _Mode);
    virtual ~CustomStringbuf();
};

class CustomOstringstream : public BasicOstream {
public:
    CustomStringbuf _Stringbuffer;
    CustomOstringstream(int _Mode = 2);
    virtual ~CustomOstringstream();
};

// CustomOstringstream::CustomOstringstream (RVA 0x1512a0)
// Constructs the basic_ostream base and custom basic_stringbuf member with ios_base::out.
CustomOstringstream::CustomOstringstream(int _Mode)
    : BasicOstream(&_Stringbuffer, false)
    , _Stringbuffer(_Mode | 2)
{
}

// ---------------------------------------------------------------------------
// Scaffolding for LTCG link (not part of the unit)
// ---------------------------------------------------------------------------

void Driver_151160(UnnamedWidget_151160 *Obj, ISurface_151160 *Surf)
{
    Obj->SetSurface(Surf);
}
