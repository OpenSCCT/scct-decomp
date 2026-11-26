// Uninitialized fill and copy for engine std::vector storage (Dinkumware VC7.1
// _Uninit_fill_n and _Uninit_copy for non-scalar element types). Each element is
// built through the allocator's out-of-line construct inside a catch-all region;
// destroying the built prefix is trivial for these element types, so the catch
// block only rethrows.
#include <stddef.h>

template<class T> struct ElementAllocator
{
    void construct(T *where, const T &value);  // out of line in the engine
    void destroy(T *) {}
};

template<class T> void UninitializedFill(T *first, size_t count, const T &value, ElementAllocator<T> &allocator)
{
    T *next = first;
    try
    {
        for (; 0 < count; --count, ++first)
            allocator.construct(first, value);
    }
    catch (...)
    {
        for (; next != first; ++next)
            allocator.destroy(next);
        throw;
    }
}

template<class T> T *UninitializedCopy(const T *first, const T *last, T *dest, ElementAllocator<T> &allocator)
{
    T *next = dest;
    try
    {
        for (; first != last; ++dest, ++first)
            allocator.construct(dest, *first);
    }
    catch (...)
    {
        for (; next != dest; ++next)
            allocator.destroy(next);
        throw;
    }
    return dest;
}

struct Handle { void *object; };
struct Triple { void *object; int first; int second; };
struct Quad { void *object; int first; int second; int third; };

template void UninitializedFill<Handle>(Handle *, size_t, const Handle &, ElementAllocator<Handle> &);
template Handle *UninitializedCopy<Handle>(const Handle *, const Handle *, Handle *, ElementAllocator<Handle> &);
template void UninitializedFill<Triple>(Triple *, size_t, const Triple &, ElementAllocator<Triple> &);
template Triple *UninitializedCopy<Triple>(const Triple *, const Triple *, Triple *, ElementAllocator<Triple> &);
template void UninitializedFill<Quad>(Quad *, size_t, const Quad &, ElementAllocator<Quad> &);
template Quad *UninitializedCopy<Quad>(const Quad *, const Quad *, Quad *, ElementAllocator<Quad> &);
