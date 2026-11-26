#include "versus_shared_object.h"

extern "C" void __cdecl release_range(SharedObject **first, SharedObject **last)
{
    while (first != last) {
        SharedObject *object = *first;
        if (object) {
            unsigned references = object->references;
            if (references <= 1) {
                delete object;
            } else {
                object->references = references - 1;
            }
        }
        ++first;
    }
}
