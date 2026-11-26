// campaign_vector_noreturn.cpp -- vector allocation with a length exception.
#include "campaign_vector_initialization.h"

template<class T> bool CampaignVectorStorage<T>::InitializeChecked(size_t Count)
{
    First = 0;
    Last = 0;
    End = 0;
    if (Count == 0)
        return false;

    if (Count > Allocator.MaxSize())
        LengthError();
    T *Storage = Allocator.Allocate(Count);
    End = Storage + Count;
    First = Storage;
    Last = Storage;
    return true;
}

// Each element placeholder records the size observed in this retail entry.
#define INSTANTIATE_VECTOR(Address, Bytes) \
    struct UnkType_##Address { unsigned char bytes[Bytes]; }; \
    template bool CampaignVectorStorage<UnkType_##Address>::InitializeChecked(size_t);
INSTANTIATE_VECTOR(10adb180, 16)
INSTANTIATE_VECTOR(10adda20, 16)
INSTANTIATE_VECTOR(10b14030, 16)
INSTANTIATE_VECTOR(10b14090, 16)
INSTANTIATE_VECTOR(10b1fcb0, 16)

#undef INSTANTIATE_VECTOR
