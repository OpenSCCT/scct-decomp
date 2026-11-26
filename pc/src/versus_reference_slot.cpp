#include "versus_shared_object.h"

extern "C" void __fastcall release_slot(SharedObject **slot)
{
    SharedObject *object = *slot;
    if (object) {
        unsigned references = object->references;
        if (references <= 1)
            delete object;
        else
            object->references = references - 1;
    }
}
