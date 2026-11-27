#ifndef VERSUS_CONSTRUCT_OBJECT_H
#define VERSUS_CONSTRUCT_OBJECT_H

#include "versus_native_class_types.h"

__forceinline UObject *ConstructObject(UClass *Type, UObject *Outer, FName InName = NAME_None,
    DWORD Flags = 0, UObject *Template = 0, FOutputDevice *Error = GError, UObject *SubobjectRoot = 0) {
    UObject *Object = UObject::StaticAllocateObject(Type, Outer, InName, Flags, Template, Error, 0, SubobjectRoot);
    if (Object)
        Type->ClassConstructor(Object);
    return Object;
}

#endif
