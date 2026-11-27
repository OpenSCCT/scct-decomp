#include "versus_build.h"
#include "versus_malloc.h"

void operator delete(void *Ptr)
{
    GMalloc->Free(Ptr);
}
