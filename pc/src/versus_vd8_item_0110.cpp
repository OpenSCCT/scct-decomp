/* w4_item_0110.cpp -- Versus RVA 0x1523d5-0x152682
   Note: 0x1523d5 (Catch@10a523d5) is the inline catch(...) handler embedded
   inside FUN_10a52380 (0x152380..0x152416, std::basic_string::_Construct),
   not a standalone function. */

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned int size_t;
typedef float FLOAT;

extern "C" void * __cdecl memset(void *, int, size_t);
#pragma intrinsic(memset)

namespace std {

class __declspec(dllimport) _String_base {
public:
    void _Xlen() const;
    void _Xran() const;
};

struct CustomAllocator {};

template<class _Elem, class _Alloc>
class _String_val : public _String_base {
protected:
    _Alloc _Alval;
};

/* VC7.0 std::basic_string<char, std::char_traits<char>, CustomAllocator> */
class CharString : public _String_val<char, CustomAllocator> {
public:
    typedef size_t size_type;
    enum { _BUF_SIZE = 16 };
    static const size_type npos = (size_type)-1;

    union _Bxty {
        char _Buf[_BUF_SIZE];
        char *_Ptr;
    } _Bx;

    size_type _Mysize;
    size_type _Myres;

    size_type max_size() const
    {
        return (size_type)-2;
    }

    char *_Myptr()
    {
        return (_BUF_SIZE <= _Myres ? _Bx._Ptr : _Bx._Buf);
    }

    void _Eos(size_type _Newsize)
    {
        _Mysize = _Newsize;
        _Myptr()[_Newsize] = 0;
    }

    void _Copy(size_type _Newsize, size_type _Oldlen);

    __forceinline bool _Grow(size_type _Newsize)
    {
        if (max_size() < _Newsize)
            _Xlen();
        if (_Myres < _Newsize)
            _Copy(_Newsize, _Mysize);
        else if (_Newsize == 0)
            _Eos(0);
        return (0 < _Newsize);
    }

    CharString &append(size_type _Count, char _Ch);
    void reserve(size_type _Newcap);
};

/* std::CharString::append (0x152420) -- append _Count copies of _Ch */
CharString &CharString::append(size_type _Count, char _Ch)
{
    if (npos - _Mysize <= _Count)
        _Xlen();
    size_type _Num;
    if (0 < _Count && _Grow(_Num = _Mysize + _Count)) {
        memset(_Myptr() + _Mysize, _Ch, _Count);
        _Eos(_Num);
    }
    return (*this);
}

/* std::CharString::reserve (0x152500) -- grow capacity to at least _Newcap */
void CharString::reserve(size_type _Newcap)
{
    if (_Myres < _Newcap)
        _Grow(_Newcap);
}

} // namespace std

struct FColor {
    BYTE B, G, R, A;

    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA)
        : R(InR), G(InG), B(InB), A(InA) {}
};

template<class T>
inline T Min(const T A, const T B)
{
    return (A < B) ? A : B;
}

/* Neutral class name for 0x152560 (viewport-like object with SizeX/SizeY at +0x2c/+0x30). */
class UnnamedViewport_152560 {
public:
    BYTE unk_00[0x2c];
    INT SizeX;
    INT SizeY;

    FLOAT ComputeAspectScale(INT Width, INT Height);
};

/* UnnamedViewport_152560::ComputeAspectScale (0x152560) -- 4:3 aspect-fitted scale factor */
FLOAT UnnamedViewport_152560::ComputeAspectScale(INT Width, INT Height)
{
    if ((FLOAT)SizeX > (FLOAT)SizeY * (4.0f / 3.0f))
        return (1.0f / (FLOAT)Width) * (FLOAT)SizeY * (4.0f / 3.0f);
    return (1.0f / (FLOAT)Height) * (FLOAT)SizeX * (3.0f / 4.0f);
}

/* ScalePackedColor (0x1525b0) -- neutral name; scales RGB of a packed ABGR DWORD into FColor */
FColor ScalePackedColor(DWORD Color, FLOAT Scale)
{
    INT R = (INT)Min((FLOAT)(Color & 0xFF) * Scale, 255.0f);
    INT G = (INT)Min((FLOAT)((Color >> 8) & 0xFF) * Scale, 255.0f);
    INT B = (INT)Min((FLOAT)((Color >> 16) & 0xFF) * Scale, 255.0f);
    BYTE A = (BYTE)(Color >> 24);
    return FColor((BYTE)R, (BYTE)G, (BYTE)B, A);
}

// Scaffolding for LTCG linking, not part of the units.
extern UnnamedViewport_152560 *GetViewport_152560();

#pragma inline_depth(0)
FLOAT Driver_152560(INT W, INT H)
{
    return GetViewport_152560()->ComputeAspectScale(W, H);
}
#pragma inline_depth()

FColor Driver_1525b0(DWORD Color, FLOAT Scale)
{
    return ScalePackedColor(Color, Scale);
}
