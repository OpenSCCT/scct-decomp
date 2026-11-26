#include "campaign_array_allocator.h"

extern "C" void __cdecl release_engine_buffer(void *pointer)
{
    reinterpret_cast<ArrayAllocatorVirtual *>(array_allocator)->Release(pointer);
}
