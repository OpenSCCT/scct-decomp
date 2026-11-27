#ifndef VERSUS_NATIVE_CLASS_INIT_H
#define VERSUS_NATIVE_CLASS_INIT_H

#include "versus_native_class_types.h"

inline UBOOL UObject::IsA(UClass *Base) const
{
    for (UClass *Type = Class; Type; Type = static_cast<UClass *>(Type->SuperField))
        if (Type == Base)
            return 1;
    return Base == 0;
}

#endif
