// campaign_leaf_204740.cpp -- destructor at VA 0x10b04740. It installs the class's vtable (VA
// 0x110dc6d4) and pops every entry off the list at 0x04 (each entry's value at 0x08 destroyed
// through VA 0x10d7cf40), then the list is destroyed: its clear at VA 0x10b04540 runs and its head
// node is released. The list's nodes come from the engine heap returned by the function at VA
// 0x10d8b460 and go back through the function at VA 0x10d8b550 with category 7. The class, method
// and member names are invented; the list is the compiler's library.

#include <list>

void* Unk_10d8b460();
void Unk_10d8b550(void* Heap, void* Block, int Category);

template<class T> class UnkType_10b04740_Allocator
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
        typedef UnkType_10b04740_Allocator<Other> other;
    };

    // UnkType_10b04740_Allocator::UnkType_10b04740_Allocator
    UnkType_10b04740_Allocator()
    {
    }

    // UnkType_10b04740_Allocator::UnkType_10b04740_Allocator
    template<class Other> UnkType_10b04740_Allocator(const UnkType_10b04740_Allocator<Other>&)
    {
    }

    pointer allocate(size_type Count);

    // UnkType_10b04740_Allocator::deallocate
    void deallocate(pointer Block, size_type)
    {
        Unk_10d8b550(Unk_10d8b460(), Block, 7);
    }

    // UnkType_10b04740_Allocator::construct
    void construct(pointer Block, const T& Value)
    {
        new((void*)Block) T(Value);
    }

    // UnkType_10b04740_Allocator::destroy
    void destroy(pointer Block)
    {
        Block->~T();
    }

    // UnkType_10b04740_Allocator::max_size
    size_type max_size() const
    {
        return 0x7fffffff / sizeof(T);
    }
};

class UnkType_10b04740_Value
{
public:
    UnkType_10b04740_Value();
    UnkType_10b04740_Value(const UnkType_10b04740_Value& Other);
    ~UnkType_10b04740_Value();

private:
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

struct UnkType_10b04740_Entry
{
    int unk_0;
    int unk_4;
    UnkType_10b04740_Value unk_8;
};

class UnkType_10b04740
{
public:
    virtual ~UnkType_10b04740();

private:
    std::list<UnkType_10b04740_Entry, UnkType_10b04740_Allocator<UnkType_10b04740_Entry> > unk_04;
};

// UnkType_10b04740::~UnkType_10b04740
UnkType_10b04740::~UnkType_10b04740()
{
    while ( unk_04.size() )
    {
        unk_04.pop_front();
    }
}
