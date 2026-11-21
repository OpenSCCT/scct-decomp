// Work item 0106: Versus RVA 0x151990-0x151d48, 6 functions.
// VC7.0 STL stream/stringbuf template instantiations using FMalloc-backed allocator.

typedef unsigned short TCHAR;
typedef unsigned int size_t;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};

extern FMalloc *GMalloc; // 0x10c73bf0

template <class T>
class FStdAllocator
{
public:
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef size_t size_type;

    FStdAllocator() {}
    FStdAllocator(const FStdAllocator &) {}
    pointer allocate(size_type Count, const void *);
    void deallocate(pointer Ptr, size_type)
    {
        GMalloc->Free(Ptr);
    }
};

namespace std
{
__declspec(dllimport) bool __cdecl uncaught_exception();

template <class _Elem>
struct char_traits
{
    typedef _Elem char_type;
    static void assign(_Elem &_Left, const _Elem &_Right)
    {
        _Left = _Right;
    }
    static _Elem *copy(_Elem *_First1, const _Elem *_First2, size_t _Count);
};

template <class _Elem, class _Traits>
class basic_streambuf
{
public:
    __declspec(dllimport) virtual ~basic_streambuf();
    __declspec(dllimport) void _Lock();
    __declspec(dllimport) void _Unlock();

protected:
    __declspec(dllimport) basic_streambuf();

    _Elem *eback() const { return *_IGfirst; }
    _Elem *gptr() const { return *_IGnext; }
    _Elem *pbase() const { return *_IPfirst; }
    _Elem *pptr() const { return *_IPnext; }
    _Elem *egptr() const { return *_IGnext + *_IGcount; }
    _Elem *epptr() const { return *_IPnext + *_IPcount; }

    void setg(_Elem *_First, _Elem *_Next, _Elem *_Last)
    {
        *_IGfirst = _First;
        *_IGnext = _Next;
        *_IGcount = (int)(_Last - _Next);
    }

    void setp(_Elem *_First, _Elem *_Last)
    {
        *_IPfirst = _First;
        *_IPnext = _First;
        *_IPcount = (int)(_Last - _First);
    }

private:
    void *_Mylock;      // +0x04
    _Elem *_Gfirst;     // +0x08
    _Elem *_Pfirst;     // +0x0c
    _Elem **_IGfirst;   // +0x10
    _Elem **_IPfirst;   // +0x14
    _Elem *_Gnext;      // +0x18
    _Elem *_Pnext;      // +0x1c
    _Elem **_IGnext;    // +0x20
    _Elem **_IPnext;    // +0x24
    int _Gcount;        // +0x28
    int _Pcount;        // +0x2c
    int *_IGcount;      // +0x30
    int *_IPcount;      // +0x34
    void *_Plocale;     // +0x38
};

class ios_base
{
public:
    typedef int iostate;
    enum { goodbit = 0x00 };

    typedef int openmode;
    enum
    {
        in = 0x01,
        out = 0x02,
        ate = 0x04,
        app = 0x08,
        trunc = 0x10,
        binary = 0x20
    };

    virtual ~ios_base();

    iostate rdstate() const { return _Mystate; }
    bool good() const { return rdstate() == goodbit; }

private:
    iostate _Mystate;           // +0x04
    char unk_08[0x28 - 0x08];
};

template <class _Elem, class _Traits>
class basic_ostream;

template <class _Elem, class _Traits>
class basic_ios : public ios_base
{
public:
    typedef basic_streambuf<_Elem, _Traits> _Mysb;
    typedef basic_ostream<_Elem, _Traits> _Myos;

    _Mysb *rdbuf() const { return _Mystrbuf; }
    _Myos *tie() const { return _Tiestr; }

private:
    _Mysb *_Mystrbuf;   // +0x28
    _Myos *_Tiestr;     // +0x2c
    _Elem _Fillch;      // +0x30
};

template <class _Elem, class _Traits>
class basic_ostream : virtual public basic_ios<_Elem, _Traits>
{
public:
    typedef basic_ostream<_Elem, _Traits> _Myt;

    __declspec(dllimport) _Myt &flush();
    __declspec(dllimport) void _Osfx();

    class _Sentry_base
    {
    public:
        _Sentry_base(_Myt &_Ostr) : _Myostr(_Ostr)
        {
            if (_Myostr.rdbuf() != 0)
                _Myostr.rdbuf()->_Lock();
        }

        // RVA 0x151d30
        ~_Sentry_base()
        {
            if (_Myostr.rdbuf() != 0)
                _Myostr.rdbuf()->_Unlock();
        }

        _Myt &_Myostr;
    };

    class sentry : public _Sentry_base
    {
    public:
        // RVA 0x151990
        explicit sentry(_Myt &_Ostr)
            : _Sentry_base(_Ostr)
        {
            if (_Ostr.good() && _Ostr.tie() != 0)
                _Ostr.tie()->flush();
            _Ok = _Ostr.good();
        }

        // RVA 0x151a10
        ~sentry()
        {
            if (!uncaught_exception())
                _Myostr._Osfx();
        }

        operator bool() const { return _Ok; }

    private:
        bool _Ok;
    };
};

template <class _Ty, class _Alloc>
class _String_val
{
protected:
    _String_val(_Alloc _Al = _Alloc()) : _Alval(_Al) {}
    _Alloc _Alval;
};

template <class _Elem, class _Traits, class _Ax>
class basic_string : public _String_val<_Elem, _Ax>
{
public:
    typedef basic_string<_Elem, _Traits, _Ax> _Myt;
    typedef _String_val<_Elem, _Ax> _Mybase;
    typedef size_t size_type;

    enum { _BUF_SIZE = 16 / sizeof(_Elem) < 1 ? 1 : 16 / sizeof(_Elem) };
    enum { npos = (size_type)-1 };

    basic_string() : _Mybase()
    {
        _Tidy();
    }

    basic_string(const _Myt &_Right) : _Mybase(_Right._Alval)
    {
        _Tidy();
        assign(_Right, 0, npos);
    }

    basic_string(const _Elem *_Ptr, size_type _Count) : _Mybase()
    {
        _Tidy();
        assign(_Ptr, _Count);
    }

    ~basic_string()
    {
        _Tidy(true);
    }

    _Myt &assign(const _Myt &_Right, size_type _Roff, size_type _Count); // RVA 0x151d70
    _Myt &assign(const _Elem *_Ptr, size_type _Count);                   // RVA 0x151e20

protected:
    void _Eos(size_type _Newsize)
    {
        _Traits::assign(_Myptr()[_Mysize = _Newsize], _Elem());
    }

    _Elem *_Myptr()
    {
        return _BUF_SIZE <= _Myres ? _Bx._Ptr : _Bx._Buf;
    }

    void _Tidy(bool _Built = false, size_type _Newsize = 0)
    {
        if (_Built && _BUF_SIZE <= _Myres)
        {
            _Elem *_Ptr = _Bx._Ptr;
            _Alval.deallocate(_Ptr, _Myres + 1);
        }
        _Myres = _BUF_SIZE - 1;
        _Eos(_Newsize);
    }

    union _Bxty
    {
        _Elem _Buf[_BUF_SIZE];
        _Elem *_Ptr;
    } _Bx;

    size_type _Mysize;
    size_type _Myres;
};

template <class _Elem, class _Traits, class _Alloc>
class basic_stringbuf : public basic_streambuf<_Elem, _Traits>
{
public:
    typedef basic_streambuf<_Elem, _Traits> _Mysb;
    typedef basic_string<_Elem, _Traits, _Alloc> _Mystr;

    enum
    {
        _Allocated = 1,
        _Constant = 2,
        _Noread = 4,
        _Append = 8,
        _Atend = 16
    };
    typedef int _Strstate;

    explicit basic_stringbuf(ios_base::openmode _Mode = ios_base::in | ios_base::out);
    virtual ~basic_stringbuf();

    _Mystr str() const;

protected:
    void _Init(const _Elem *_Ptr, size_t _Count, _Strstate _State);
    void _Tidy();

    _Strstate _Getstate(ios_base::openmode _Mode)
    {
        _Strstate _State = (_Strstate)0;
        if (!(_Mode & ios_base::in))
            _State |= _Noread;
        if (!(_Mode & ios_base::out))
            _State |= _Constant;
        return _State;
    }

private:
    _Elem *_Seekhigh;   // +0x3c
    _Strstate _Mystate; // +0x40
    _Alloc _Al;         // +0x44
};

// RVA 0x151ab0
template <class _Elem, class _Traits, class _Alloc>
basic_stringbuf<_Elem, _Traits, _Alloc>::basic_stringbuf(ios_base::openmode _Mode)
{
    _Init(0, 0, _Getstate(_Mode));
}

template <class _Elem, class _Traits, class _Alloc>
void basic_stringbuf<_Elem, _Traits, _Alloc>::_Init(
    const _Elem *_Ptr, size_t _Count, _Strstate _State)
{
    _Seekhigh = 0;
    _Mystate = _State;
    if (_Count != 0 && (_Mystate & (_Noread | _Constant)) != (_Noread | _Constant))
    {
        _Elem *_Pnew = _Al.allocate(_Count, (void *)0);
        _Traits::copy(_Pnew, _Ptr, _Count);
        _Seekhigh = _Pnew + _Count;
        if (!(_Mystate & _Noread))
            setg(_Pnew, _Pnew, _Pnew + _Count);
        if (!(_Mystate & _Constant))
        {
            setp(_Pnew, _Pnew + _Count);
            if (_Mystate & _Noread)
                setg(_Pnew, 0, _Pnew);
        }
        _Mystate |= _Allocated;
    }
}

// RVA 0x151b10
template <class _Elem, class _Traits, class _Alloc>
typename basic_stringbuf<_Elem, _Traits, _Alloc>::_Mystr
basic_stringbuf<_Elem, _Traits, _Alloc>::str() const
{
    if (!(_Mystate & _Constant) && pptr() != 0)
    {
        _Mystr _Str(pbase(), (_Seekhigh < pptr() ? pptr() : _Seekhigh) - pbase());
        return _Str;
    }
    else if (!(_Mystate & _Noread) && gptr() != 0)
    {
        _Mystr _Str(eback(), egptr() - eback());
        return _Str;
    }
    else
    {
        _Mystr _Nul;
        return _Nul;
    }
}

// RVA 0x151cc0
template <class _Elem, class _Traits, class _Alloc>
void basic_stringbuf<_Elem, _Traits, _Alloc>::_Tidy()
{
    if (_Mystate & _Allocated)
        _Al.deallocate(eback(), (pptr() != 0 ? epptr() : egptr()) - eback());
    setg(0, 0, 0);
    setp(0, 0);
    _Seekhigh = 0;
    _Mystate &= ~_Allocated;
}

template class basic_stringbuf<char, char_traits<char>, FStdAllocator<char> >;

} // namespace std

// Scaffolding for LTCG link, not part of the unit.
typedef std::basic_ostream<char, std::char_traits<char> > CharOstream;
void ExternalUse(void *);

void Driver_151990(CharOstream *Ostr)
{
    CharOstream::sentry S(*Ostr);
    if (S)
        ExternalUse(&S);
}
