// w4_item_0107.cpp -- Versus RVA 0x151d70-0x1520cc
// std::basic_string<char, std::char_traits<char>, MagmaAllocator<char>> methods

typedef unsigned short TCHAR;
typedef unsigned long DWORD;
typedef unsigned int size_t;

extern "C" {
void *__cdecl memcpy(void *, const void *, size_t);
__declspec(dllimport) void *__cdecl memmove(void *, const void *, size_t);
}

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};

extern FMalloc *GMalloc;               // 0x10c73bf0
extern const TCHAR GMagmaAllocTag[];   // L"Magma" at 0x10c47428 (writable .data)

// Invented name for the Magma STL allocator backed by GMalloc with tag L"Magma".
template <class T>
class MagmaAllocator {
public:
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef size_t size_type;

    __forceinline pointer allocate(size_type Count)
    {
        return (pointer)GMalloc->Malloc((DWORD)(Count * sizeof(T)), GMagmaAllocTag);
    }

    void deallocate(pointer Ptr, size_type)
    {
        GMalloc->Free(Ptr);
    }
};

namespace std {

class __declspec(dllimport) _String_base {
public:
    void _Xlen() const;
    void _Xran() const;
};

template <class _Elem>
struct char_traits {
    static void assign(_Elem &_Left, const _Elem &_Right)
    {
        _Left = _Right;
    }

    static _Elem *copy(_Elem *_First1, const _Elem *_First2, size_t _Count)
    {
        return (_Elem *)memcpy(_First1, _First2, _Count * sizeof(_Elem));
    }

    static _Elem *move(_Elem *_First1, const _Elem *_First2, size_t _Count)
    {
        return (_Elem *)memmove(_First1, _First2, _Count * sizeof(_Elem));
    }
};

template <class _Elem, class _Traits, class _Ax>
class basic_string : public _String_base {
public:
    typedef basic_string<_Elem, _Traits, _Ax> _Myt;
    typedef size_t size_type;

    static const size_type npos = (size_type)(-1);

    enum {
        _BUF_SIZE = 16 / sizeof(_Elem) < 1 ? 1 : 16 / sizeof(_Elem),
        _ALLOC_MASK = sizeof(_Elem) <= 1 ? 15
            : sizeof(_Elem) <= 2 ? 7
            : sizeof(_Elem) <= 4 ? 3
            : sizeof(_Elem) <= 8 ? 1 : 0
    };

    union _Bxty {
        _Elem _Buf[_BUF_SIZE];
        _Elem *_Ptr;
    };

    _Ax _Alval;
    _Bxty _Bx;
    size_type _Mysize;
    size_type _Myres;

    size_type size() const { return _Mysize; }
    size_type max_size() const { return npos - 1; }

    _Elem *_Myptr()
    {
        return _BUF_SIZE <= _Myres ? _Bx._Ptr : _Bx._Buf;
    }

    const _Elem *_Myptr() const
    {
        return _BUF_SIZE <= _Myres ? _Bx._Ptr : _Bx._Buf;
    }

    bool _Inside(const _Elem *_Ptr) const
    {
        return _Myptr() <= _Ptr && _Ptr < _Myptr() + _Mysize;
    }

    // basic_string::_Eos (RVA 0x151ec0)
    void _Eos(size_type _Newsize)
    {
        _Traits::assign(_Myptr()[_Mysize = _Newsize], _Elem());
    }

    // basic_string::_Tidy (inlined helper)
    void _Tidy(bool _Built = false, size_type _Newsize = 0)
    {
        if (_Built && _BUF_SIZE <= _Myres) {
            _Elem *_Ptr = _Myptr();
            if (0 < _Newsize)
                _Traits::copy(_Bx._Buf, _Ptr, _Newsize);
            _Alval.deallocate(_Ptr, _Myres + 1);
        }
        _Myres = _BUF_SIZE - 1;
        _Eos(_Newsize);
    }

    // basic_string::_Copy (RVA 0x152070..0x1521a8, 313 code bytes + 7 NOPs)
    void _Copy(size_type _Newsize, size_type _Oldlen)
    {
        size_type _Newres = _Newsize | _ALLOC_MASK;
        if (max_size() < _Newres)
            _Newres = _Newsize;

        _Elem *_Ptr;
        try {
            _Ptr = _Alval.allocate(_Newres + 1);
        } catch (...) {
            _Newres = _Newsize;
            try {
                _Ptr = _Alval.allocate(_Newres + 1);
            } catch (...) {
                _Tidy(true);
                throw;
            }
        }

        if (0 < _Oldlen)
            _Traits::copy(_Ptr, _Myptr(), _Oldlen);
        _Tidy(true);
        _Bx._Ptr = _Ptr;
        _Myres = _Newres;
        _Eos(_Oldlen);
    }

    // basic_string::_Grow (RVA 0x151fa0)
    bool _Grow(size_type _Newsize, bool _Trim = false)
    {
        if (max_size() < _Newsize)
            _String_base::_Xlen();
        if (_Myres < _Newsize)
            _Copy(_Newsize, _Trim ? 0 : _Mysize);
        else if (_Trim && _Newsize < _BUF_SIZE)
            _Tidy(true);
        else if (_Newsize == 0)
            _Eos(0);
        return 0 < _Newsize;
    }

    // basic_string::erase (RVA 0x151ee0)
    _Myt &erase(size_type _Off = 0, size_type _Count = npos)
    {
        if (_Mysize < _Off)
            _String_base::_Xran();
        if (_Mysize - _Off < _Count)
            _Count = _Mysize - _Off;
        if (0 < _Count) {
            _Traits::move(_Myptr() + _Off, _Myptr() + _Off + _Count, _Mysize - _Off - _Count);
            size_type _Newsize = _Mysize - _Count;
            if (_Grow(_Newsize))
                _Eos(_Newsize);
        }
        return *this;
    }

    // basic_string::assign(const basic_string&, size_type, size_type) (RVA 0x151d70)
    _Myt &assign(const _Myt &_Right, size_type _Roff, size_type _Count)
    {
        if (_Right.size() < _Roff)
            _String_base::_Xran();
        size_type _Num = _Right.size() - _Roff;
        if (_Count < _Num)
            _Num = _Count;

        if (this == &_Right) {
            erase((size_type)(_Roff + _Num));
            erase(0, _Roff);
        } else if (_Grow(_Num, true)) {
            _Traits::copy(_Myptr(), _Right._Myptr() + _Roff, _Num);
            _Eos(_Num);
        }
        return *this;
    }

    // basic_string::assign(const char*, size_type) (RVA 0x151e20)
    _Myt &assign(const _Elem *_Ptr, size_type _Count)
    {
        if (_Inside(_Ptr))
            return assign(*this, _Ptr - _Myptr(), _Count);
        if (_Grow(_Count, true)) {
            _Traits::copy(_Myptr(), _Ptr, _Count);
            _Eos(_Count);
        }
        return *this;
    }
};

} // namespace std

template class std::basic_string<char, std::char_traits<char>, MagmaAllocator<char> >;
