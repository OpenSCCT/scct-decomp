// campaign_vector_insert.cpp -- insertion routines of the game's growable arrays
//
// A growable array with the layout and code shape of the vector in the
// VC7.1 standard library that the game was built with. The game compiled its
// containers without exception support, so failed size checks do nothing and
// there are no cleanup paths.

#include "campaign_container_allocator.h"

typedef int ptrdiff_t;

namespace stl {

// Selects the element-by-element algorithms. The game's element types all take
// this path, so the memmove variants for scalar types are not reproduced.
struct NonscalarTag {};

template<class A, class B> inline NonscalarTag PointerCategory(A &, B &)
{
    NonscalarTag Category;
    return Category;
}

template<class InIt, class FwdIt, class Alloc> inline
FwdIt UninitCopy(InIt First, InIt Last, FwdIt Dest, Alloc &Al, NonscalarTag)
{
    for (; First != Last; ++Dest, ++First)
        Al.construct(Dest, *First);
    return Dest;
}

template<class InIt, class FwdIt, class Alloc> inline
FwdIt UninitializedCopy(InIt First, InIt Last, FwdIt Dest, Alloc &Al)
{
    return UninitCopy(First, Last, Dest, Al, PointerCategory(First, Dest));
}

template<class FwdIt, class Diff, class Val, class Alloc> inline
void UninitFillN(FwdIt First, Diff Count, const Val &Value, Alloc &Al, NonscalarTag)
{
    for (; 0 < Count; --Count, ++First)
        Al.construct(First, Value);
}

template<class FwdIt, class Diff, class Val, class Alloc> inline
void UninitializedFillN(FwdIt First, Diff Count, const Val &Value, Alloc &Al)
{
    UninitFillN(First, Count, Value, Al, PointerCategory(First, First));
}

template<class T, class Alloc> inline
void DestroyRange(T *First, T *Last, Alloc &Al, NonscalarTag)
{
    for (; First != Last; ++First)
        Al.destroy(First);
}

template<class T, class Alloc> inline
void DestroyRange(T *First, T *Last, Alloc &Al)
{
    DestroyRange(First, Last, Al, PointerCategory(First, Last));
}

template<class InIt, class OutIt> inline
OutIt CopyOpt(InIt First, InIt Last, OutIt Dest, NonscalarTag)
{
    for (; First != Last; ++Dest, ++First)
        *Dest = *First;
    return Dest;
}

template<class InIt, class OutIt> inline
OutIt Copy(InIt First, InIt Last, OutIt Dest)
{
    return CopyOpt(First, Last, Dest, PointerCategory(First, Dest));
}

template<class BidIt1, class BidIt2> inline
BidIt2 CopyBackwardOpt(BidIt1 First, BidIt1 Last, BidIt2 Dest, NonscalarTag)
{
    while (First != Last)
        *--Dest = *--Last;
    return Dest;
}

template<class BidIt1, class BidIt2> inline
BidIt2 CopyBackward(BidIt1 First, BidIt1 Last, BidIt2 Dest)
{
    return CopyBackwardOpt(First, Last, Dest, PointerCategory(First, Dest));
}

template<class FwdIt, class T> inline
void Fill(FwdIt First, FwdIt Last, const T &Value)
{
    for (; First != Last; ++First)
        *First = Value;
}

// Holds the allocator ahead of the three array pointers.
template<class T, class Alloc> class VectorBase {
protected:
    VectorBase(Alloc Al = Alloc()) : Allocator(Al) {}
    Alloc Allocator;
};

template<class T, class Alloc> class Vector : public VectorBase<T, Alloc> {
public:
    typedef T *Pointer;

    // Iterators wrap a pointer, so they are passed by value in one register.
    class ConstIterator {
    public:
        ConstIterator() {}
        ConstIterator(Pointer Ptr) : Ptr(Ptr) {}
        const T &operator*() const { return *Ptr; }
        bool operator==(const ConstIterator &Other) const { return Ptr == Other.Ptr; }
        bool operator!=(const ConstIterator &Other) const { return !(*this == Other); }
        ConstIterator &operator++() { ++Ptr; return *this; }
        ptrdiff_t operator-(const ConstIterator &Other) const { return Ptr - Other.Ptr; }
        Pointer Ptr;
    };

    class Iterator : public ConstIterator {
    public:
        Iterator() {}
        Iterator(Pointer Ptr) : ConstIterator(Ptr) {}
        T &operator*() const { return *this->Ptr; }
        Iterator operator+(ptrdiff_t Offset) const { Iterator Tmp = *this; Tmp.Ptr += Offset; return Tmp; }
        ptrdiff_t operator-(const ConstIterator &Other) const { return this->Ptr - Other.Ptr; }
    };

    Iterator Begin() { return Iterator(First); }
    Iterator End() { return Iterator(Last); }

    size_t Capacity() const { return First == 0 ? 0 : End_ - First; }
    size_t Size() const { return First == 0 ? 0 : Last - First; }
    size_t MaxSize() const { return this->Allocator.MaxSize(); }
    bool Empty() const { return Size() == 0; }

    void PushBack(const T &Value)
    {
        if (Size() < Capacity())
            Last = UFill(Last, 1, Value);
        else
            Insert(End(), Value);
    }

    Iterator Insert(Iterator Where, const T &Value)
    {
        size_t Offset = Size() == 0 ? 0 : Where - Begin();
        InsertN(Where, (size_t)1, Value);
        return Begin() + Offset;
    }

    void InsertN(Iterator Where, size_t Count, const T &Value)
    {
        T Copy = Value; // Value may live inside the array.
        size_t NewCapacity = Capacity();

        if (Count == 0)
            ;
        else if (MaxSize() - Size() < Count)
            LengthError();
        else if (NewCapacity < Size() + Count) {
            // Grow by half again, or to the exact size when that is larger.
            NewCapacity = MaxSize() - NewCapacity / 2 < NewCapacity ? 0 : NewCapacity + NewCapacity / 2;
            if (NewCapacity < Size() + Count)
                NewCapacity = Size() + Count;
            Pointer NewArray = this->Allocator.Allocate(NewCapacity);
            Pointer Ptr = NewArray;

            Ptr = UCopy(First, Where.Ptr, NewArray);
            Ptr = UFill(Ptr, Count, Copy);
            UCopy(Where.Ptr, Last, Ptr);

            Count += Size();
            if (First != 0) {
                Destroy(First, Last);
                this->Allocator.Deallocate(First, End_ - First);
            }
            End_ = NewArray + NewCapacity;
            Last = NewArray + Count;
            First = NewArray;
        } else if ((size_t)(Last - Where.Ptr) < Count) {
            // The new elements run past the old end.
            UCopy(Where.Ptr, Last, Where.Ptr + Count);
            UFill(Last, Count - (Last - Where.Ptr), Copy);
            Last += Count;
            Fill(Where.Ptr, Last - Count, Copy);
        } else {
            // The new elements fit inside the old range.
            Pointer OldEnd = Last;
            Last = UCopy(OldEnd - Count, OldEnd, Last);
            CopyBackward(Where.Ptr, OldEnd - Count, OldEnd);
            Fill(Where.Ptr, Where.Ptr + Count, Copy);
        }
    }

protected:
    void Destroy(Pointer From, Pointer To)
    {
        DestroyRange(From, To, this->Allocator);
    }

    template<class It> Pointer UCopy(It From, It To, Pointer Dest)
    {
        return UninitializedCopy(From, To, Dest, this->Allocator);
    }

    Pointer UFill(Pointer Ptr, size_t Count, const T &Value)
    {
        UninitializedFillN(Ptr, Count, Value, this->Allocator);
        return Ptr + Count;
    }

    void LengthError() const {}

    Pointer First;
    Pointer Last;
    Pointer End_;
};

} // namespace stl

// Element types are named by the retail insertion routine that copies them;
// only their size is known.
struct FItem_422170 { int Words[1]; };
template class stl::Vector<FItem_422170, TContainerAllocator<FItem_422170> >;
struct FItem_423db0 { int Words[2]; };
template class stl::Vector<FItem_423db0, TContainerAllocator<FItem_423db0> >;
struct FItem_42aa00 { int Words[1]; };
template class stl::Vector<FItem_42aa00, TContainerAllocator<FItem_42aa00> >;
struct FItem_42abe0 { int Words[1]; };
template class stl::Vector<FItem_42abe0, TContainerAllocator<FItem_42abe0> >;
struct FItem_430d70 { int Words[1]; };
template class stl::Vector<FItem_430d70, TContainerAllocator<FItem_430d70> >;
struct FItem_436fc0 { int Words[1]; };
template class stl::Vector<FItem_436fc0, TContainerAllocator<FItem_436fc0> >;
struct FItem_444680 { int Words[4]; };
template class stl::Vector<FItem_444680, TContainerAllocator<FItem_444680> >;
struct FItem_444890 { int Words[4]; };
template class stl::Vector<FItem_444890, TContainerAllocator<FItem_444890> >;
struct FItem_444aa0 { int Words[4]; };
template class stl::Vector<FItem_444aa0, TContainerAllocator<FItem_444aa0> >;
struct FItem_444cb0 { int Words[4]; };
template class stl::Vector<FItem_444cb0, TContainerAllocator<FItem_444cb0> >;
struct FItem_444ec0 { int Words[4]; };
template class stl::Vector<FItem_444ec0, TContainerAllocator<FItem_444ec0> >;
struct FItem_4450d0 { int Words[4]; };
template class stl::Vector<FItem_4450d0, TContainerAllocator<FItem_4450d0> >;
struct FItem_4452e0 { int Words[4]; };
template class stl::Vector<FItem_4452e0, TContainerAllocator<FItem_4452e0> >;
struct FItem_4454f0 { int Words[4]; };
template class stl::Vector<FItem_4454f0, TContainerAllocator<FItem_4454f0> >;
struct FItem_445700 { int Words[4]; };
template class stl::Vector<FItem_445700, TContainerAllocator<FItem_445700> >;
struct FItem_445910 { int Words[4]; };
template class stl::Vector<FItem_445910, TContainerAllocator<FItem_445910> >;
struct FItem_445b20 { int Words[4]; };
template class stl::Vector<FItem_445b20, TContainerAllocator<FItem_445b20> >;
struct FItem_445d30 { int Words[4]; };
template class stl::Vector<FItem_445d30, TContainerAllocator<FItem_445d30> >;
struct FItem_445f40 { int Words[4]; };
template class stl::Vector<FItem_445f40, TContainerAllocator<FItem_445f40> >;
struct FItem_446150 { int Words[4]; };
template class stl::Vector<FItem_446150, TContainerAllocator<FItem_446150> >;
struct FItem_446360 { int Words[4]; };
template class stl::Vector<FItem_446360, TContainerAllocator<FItem_446360> >;
struct FItem_446570 { int Words[4]; };
template class stl::Vector<FItem_446570, TContainerAllocator<FItem_446570> >;
struct FItem_446780 { int Words[4]; };
template class stl::Vector<FItem_446780, TContainerAllocator<FItem_446780> >;
struct FItem_446990 { int Words[4]; };
template class stl::Vector<FItem_446990, TContainerAllocator<FItem_446990> >;
struct FItem_446ba0 { int Words[4]; };
template class stl::Vector<FItem_446ba0, TContainerAllocator<FItem_446ba0> >;
struct FItem_446db0 { int Words[4]; };
template class stl::Vector<FItem_446db0, TContainerAllocator<FItem_446db0> >;
struct FItem_446fc0 { int Words[4]; };
template class stl::Vector<FItem_446fc0, TContainerAllocator<FItem_446fc0> >;
struct FItem_4471d0 { int Words[4]; };
template class stl::Vector<FItem_4471d0, TContainerAllocator<FItem_4471d0> >;
struct FItem_4473e0 { int Words[4]; };
template class stl::Vector<FItem_4473e0, TContainerAllocator<FItem_4473e0> >;
struct FItem_4475f0 { int Words[4]; };
template class stl::Vector<FItem_4475f0, TContainerAllocator<FItem_4475f0> >;
struct FItem_447800 { int Words[4]; };
template class stl::Vector<FItem_447800, TContainerAllocator<FItem_447800> >;
struct FItem_447a10 { int Words[4]; };
template class stl::Vector<FItem_447a10, TContainerAllocator<FItem_447a10> >;
struct FItem_447c20 { int Words[4]; };
template class stl::Vector<FItem_447c20, TContainerAllocator<FItem_447c20> >;
struct FItem_447e30 { int Words[4]; };
template class stl::Vector<FItem_447e30, TContainerAllocator<FItem_447e30> >;
struct FItem_448040 { int Words[4]; };
template class stl::Vector<FItem_448040, TContainerAllocator<FItem_448040> >;
struct FItem_448250 { int Words[4]; };
template class stl::Vector<FItem_448250, TContainerAllocator<FItem_448250> >;
struct FItem_448460 { int Words[4]; };
template class stl::Vector<FItem_448460, TContainerAllocator<FItem_448460> >;
struct FItem_448670 { int Words[4]; };
template class stl::Vector<FItem_448670, TContainerAllocator<FItem_448670> >;
struct FItem_448880 { int Words[4]; };
template class stl::Vector<FItem_448880, TContainerAllocator<FItem_448880> >;
struct FItem_448a90 { int Words[4]; };
template class stl::Vector<FItem_448a90, TContainerAllocator<FItem_448a90> >;
struct FItem_4498a0 { int Words[4]; };
template class stl::Vector<FItem_4498a0, TContainerAllocator<FItem_4498a0> >;
struct FItem_449ab0 { int Words[4]; };
template class stl::Vector<FItem_449ab0, TContainerAllocator<FItem_449ab0> >;
struct FItem_45a8d0 { int Words[2]; };
template class stl::Vector<FItem_45a8d0, TContainerAllocator<FItem_45a8d0> >;
struct FItem_460cf0 { int Words[1]; };
template class stl::Vector<FItem_460cf0, TContainerAllocator<FItem_460cf0> >;
struct FItem_4632b0 { int Words[1]; };
template class stl::Vector<FItem_4632b0, TContainerAllocator<FItem_4632b0> >;
struct FItem_464d30 { int Words[1]; };
template class stl::Vector<FItem_464d30, TContainerAllocator<FItem_464d30> >;
