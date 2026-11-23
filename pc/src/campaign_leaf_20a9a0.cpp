// campaign_leaf_20a9a0.cpp -- thiscall method at VA 0x10b0a9a0 taking a 20-byte key. When the word
// at 0x15d8 is zero it returns false. Otherwise it erases the first entry of the list at 0x15cc
// whose bytes equal the key (compared through the function at VA 0x10ccace0; nodes freed through
// slot 2 of the allocator at VA 0x111c88a0), passes the word at 0x15d8, the buffer at 0x15dc and
// the key to the stdcall function at VA 0x10f27f60 and returns true. The class, method and member
// names are invented; the list is the compiler's library.

#include <list>

#include "campaign_global_111c88a0.h"

int Unk_10ccace0(const void* First, const void* Second, int Count);
void __stdcall Unk_10f27f60(int Value, void* Buffer, const void* Key);

template<class T> class UnkType_10b0a9a0_Allocator
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef unsigned int size_type;
    typedef int difference_type;

    template<class Other> struct rebind
    {
        typedef UnkType_10b0a9a0_Allocator<Other> other;
    };

    // UnkType_10b0a9a0_Allocator::UnkType_10b0a9a0_Allocator
    UnkType_10b0a9a0_Allocator()
    {
    }

    // UnkType_10b0a9a0_Allocator::UnkType_10b0a9a0_Allocator
    template<class Other> UnkType_10b0a9a0_Allocator(const UnkType_10b0a9a0_Allocator<Other>&)
    {
    }

    pointer allocate(size_type Count);

    // UnkType_10b0a9a0_Allocator::deallocate
    void deallocate(pointer Block, size_type)
    {
        GUnk_111c88a0->Free(Block);
    }

    // UnkType_10b0a9a0_Allocator::construct
    void construct(pointer Block, const T& Value)
    {
        new((void*)Block) T(Value);
    }

    // UnkType_10b0a9a0_Allocator::destroy
    void destroy(pointer Block)
    {
        Block->~T();
    }

    // UnkType_10b0a9a0_Allocator::max_size
    size_type max_size() const
    {
        return 0x7fffffff / sizeof(T);
    }
};

struct UnkType_10b0a9a0_Key
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
};

class UnkType_10b0a9a0
{
public:
    bool Unk_10b0a9a0(const UnkType_10b0a9a0_Key* Key);

private:
    typedef std::list<UnkType_10b0a9a0_Key, UnkType_10b0a9a0_Allocator<UnkType_10b0a9a0_Key> >
        KeyList;

    char unk_0000[0x15cc];
    KeyList unk_15cc;
    int unk_15d8;
    char unk_15dc[0x84];
};

// UnkType_10b0a9a0::Unk_10b0a9a0
bool UnkType_10b0a9a0::Unk_10b0a9a0(const UnkType_10b0a9a0_Key* Key)
{
    if ( !unk_15d8 )
    {
        return false;
    }
    for ( KeyList::iterator It = unk_15cc.begin(); It != unk_15cc.end(); ++It )
    {
        if ( Unk_10ccace0(Key, &*It, sizeof(UnkType_10b0a9a0_Key)) == 0 )
        {
            unk_15cc.erase(It);
            break;
        }
    }
    Unk_10f27f60(unk_15d8, unk_15dc, Key);
    return true;
}
