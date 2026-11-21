// campaign_container_allocator.h -- the allocator the game's standard containers use
#ifndef CAMPAIGN_CONTAINER_ALLOCATOR_H
#define CAMPAIGN_CONTAINER_ALLOCATOR_H

#include "unreal_types.h"

typedef unsigned int size_t;

// placement new
inline void *operator new(size_t, void *Where)
{
    return Where;
}

void *operator new(size_t Size, const TCHAR *Tag);     // allocates from the engine heap
void operator delete(void *Ptr);

extern const TCHAR *GContainerTag;      // the tag every container allocation carries

// Allocates container storage from the engine heap.
template<class T> class TContainerAllocator {
public:
    T *Allocate(size_t Count) { return (T *)operator new(Count * sizeof(T), GContainerTag); }
    void Deallocate(T *Ptr, size_t) { operator delete(Ptr); }
    void construct(T *Ptr, const T &Value) { new ((void *)Ptr) T(Value); }
    void destroy(T *Ptr) { Ptr->~T(); }
    size_t MaxSize() const
    {
        size_t Count = (size_t)-1 / sizeof(T);
        return 0 < Count ? Count : 1;
    }
};

#endif // CAMPAIGN_CONTAINER_ALLOCATOR_H
