#ifndef CAMPAIGN_VECTOR_INITIALIZATION_H
#define CAMPAIGN_VECTOR_INITIALIZATION_H

// campaign_vector_initialization.h -- the allocator and three pointers of the recovered vector.
#include "campaign_container_allocator.h"

template<class T> class CampaignVectorStorage {
public:
    bool Initialize(size_t Count);
    bool InitializeChecked(size_t Count);

private:
    __declspec(noreturn) void LengthError();
    TContainerAllocator<T> Allocator;
    T *First;
    T *Last;
    T *End;
};

#endif
