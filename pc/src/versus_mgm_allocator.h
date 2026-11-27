#ifndef VERSUS_MGM_ALLOCATOR_H
#define VERSUS_MGM_ALLOCATOR_H

#include "versus_build.h"
#include "unreal_types.h"

extern "C" void *allocate_engine_buffer(unsigned int Bytes, const TCHAR *Tag);
extern "C" void release_engine_buffer(void *Pointer);

// The MGM heap uses the engine allocator with its default Magma tag.
inline void *operator new(unsigned int Bytes)
{
    return allocate_engine_buffer(Bytes, 0);
}

inline void operator delete(void *Pointer)
{
    release_engine_buffer(Pointer);
}

#endif
