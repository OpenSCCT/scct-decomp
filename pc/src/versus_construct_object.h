#ifndef VERSUS_CONSTRUCT_OBJECT_H
#define VERSUS_CONSTRUCT_OBJECT_H

#include "versus_native_class_types.h"

// The native material translation units declare this helper force-inline.
__forceinline UObject *ConstructObject(UClass *Type, UObject *Outer, FName InName, DWORD Flags,
    UObject *Template, FOutputDevice *Error, UObject *SubobjectRoot);

#include "versus_object_factory.h"
#endif
