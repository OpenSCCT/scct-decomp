#include "versus_shared_object.h"

extern "C" void __cdecl fill_references(SharedObject **destination, unsigned count,
                                        SharedObject *const *source, void *allocator,
                                        SharedObject *const *type_hint)
{
    for (; count > 0; --count, ++destination) {
        if (destination) {
            SharedObject *object = *source;
            *destination = object;
            if (object)
                ++object->references;
        }
    }
}

struct SharedObjectIterator { SharedObject *const *position; };

extern "C" SharedObject **__cdecl copy_references(SharedObjectIterator first,
                                                  SharedObjectIterator last,
                                                  SharedObject **destination, void *allocator,
                                                  SharedObject *const *type_hint)
{
    for (; first.position != last.position; ++first.position, ++destination) {
        if (destination) {
            SharedObject *object = *first.position;
            *destination = object;
            if (object)
                ++object->references;
        }
    }
    return destination;
}
