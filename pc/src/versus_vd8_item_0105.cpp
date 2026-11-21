// w4_item_0105.cpp -- Versus RVA 0x151340-0x151410
// Standard library std::basic_ostringstream<char> and std::basic_stringbuf<char>
// instantiations (MSVCP70 / Visual C++ .NET 2002 Dinkumware STL).

typedef unsigned int size_t;

namespace std {

template<class _Elem>
struct char_traits {
};

template<class _Ty>
class allocator {
};

template<class _Elem, class _Traits, class _Ax>
class __declspec(dllimport) basic_string {
public:
    ~basic_string();
    basic_string(const basic_string &_Right);

private:
    _Ax _Alval;
    union _Bxty {
        _Elem _Buf[16];
        _Elem *_Ptr;
    } _Bx;
    size_t _Mysize;
    size_t _Myres;
};

class __declspec(dllimport) ios_base {
public:
    virtual ~ios_base();
    int _Stdstr;
    int _Mystate;
    int _Except;
    int _Fmtfl;
    int _Prec;
    int _Wide;
    void *_Arr;
    void *_Calls;
    void *_Ploc;
};

template<class _Elem, class _Traits>
class __declspec(dllimport) basic_ios : public ios_base {
public:
    virtual ~basic_ios();
    void *_Mystrbuf;
    void *_Tiestr;
    _Elem _Fillch;
};

template<class _Elem, class _Traits>
class __declspec(dllimport) basic_streambuf {
public:
    virtual ~basic_streambuf();

private:
    void *_Mylock;
    _Elem *_Gfirst;
    _Elem *_Pfirst;
    _Elem **_IGfirst;
    _Elem **_IPfirst;
    _Elem *_Gnext;
    _Elem *_Pnext;
    _Elem **_IGnext;
    _Elem **_IPnext;
    int _Gcount;
    int _Pcount;
    int *_IGcount;
    int *_IPcount;
    void *_Plocale;
};

template<class _Elem, class _Traits>
class __declspec(dllimport) basic_ostream : virtual public basic_ios<_Elem, _Traits> {
public:
    virtual ~basic_ostream() {}
};

template<class _Elem, class _Traits, class _Alloc>
class basic_stringbuf : public basic_streambuf<_Elem, _Traits> {
public:
    typedef basic_string<_Elem, _Traits, _Alloc> _Mystr;

    virtual ~basic_stringbuf();
    _Mystr str() const;

protected:
    void _Tidy();

private:
    _Elem *_Seekhigh;
    int _Mystate;
    _Alloc _Al;
};

template<class _Elem, class _Traits, class _Alloc>
class basic_ostringstream : public basic_ostream<_Elem, _Traits> {
public:
    typedef basic_string<_Elem, _Traits, _Alloc> _Mystr;
    typedef basic_stringbuf<_Elem, _Traits, _Alloc> _Mysb;

    virtual ~basic_ostringstream();
    _Mystr str() const;

private:
    _Mysb _Stringbuffer;
};

// std::basic_ostringstream<char, std::char_traits<char>, std::allocator<char>>::~basic_ostringstream
// Destroys the embedded basic_stringbuf and restores the basic_ostream virtual base vtable.
template<class _Elem, class _Traits, class _Alloc>
basic_ostringstream<_Elem, _Traits, _Alloc>::~basic_ostringstream()
{
}

// std::basic_ostringstream<char, std::char_traits<char>, std::allocator<char>>::str
// Returns a copy of the underlying string buffer's contents.
template<class _Elem, class _Traits, class _Alloc>
basic_string<_Elem, _Traits, _Alloc>
basic_ostringstream<_Elem, _Traits, _Alloc>::str() const
{
    return (_Stringbuffer.str());
}

// std::basic_stringbuf<char, std::char_traits<char>, std::allocator<char>>::~basic_stringbuf
// Releases the allocated string buffer via _Tidy() and destroys the basic_streambuf base.
template<class _Elem, class _Traits, class _Alloc>
basic_stringbuf<_Elem, _Traits, _Alloc>::~basic_stringbuf()
{
    _Tidy();
}

template class basic_ostringstream<char, char_traits<char>, allocator<char> >;
template class basic_stringbuf<char, char_traits<char>, allocator<char> >;

} // namespace std
