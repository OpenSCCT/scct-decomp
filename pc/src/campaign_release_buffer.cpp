#include "unreal_containers.h"

extern "C" void __cdecl release_engine_buffer(void *pointer)
{
    GMalloc->Free(pointer);
}
