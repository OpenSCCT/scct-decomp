#include "versus_shared_object.h"

static __forceinline void assign(SharedObject **destination, SharedObject *const *source)
{
    SharedObject *old = *destination;
    if (*source != old) {
        SharedObject *value;
        if (old) {
            unsigned count = old->references;
            if (count <= 1)
                delete old;
            else
                old->references = count - 1;
        }
        value = *source;
        *destination = value;
        if (value)
            ++value->references;
    }
}

extern "C" void __cdecl assign_range(SharedObject **first, SharedObject **last,
                                     SharedObject *const *source)
{
    while (first != last)
        assign(first++, source);
}

extern "C" SharedObject ***__cdecl copy_backward(SharedObject ***result, SharedObject **first,
                                                 SharedObject **last, SharedObject **destination)
{
    while (first != last)
        assign(--destination, --last);
    *result = destination;
    return result;
}
