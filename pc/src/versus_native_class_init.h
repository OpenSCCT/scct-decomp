#ifndef VERSUS_NATIVE_CLASS_INIT_H
#define VERSUS_NATIVE_CLASS_INIT_H

#if !defined(VERSUS_PAWN_ACTION_EVENTS_H)
#include "versus_native_class_types.h"
#endif

inline UBOOL UObject::IsA(UClass *Base) const
{
    for (UClass *Type = Class; Type; Type = static_cast<UClass *>(Type->SuperField))
        if (Type == Base)
            return 1;
    return Base == 0;
}

#endif
