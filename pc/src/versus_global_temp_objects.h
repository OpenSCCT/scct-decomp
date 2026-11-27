#ifndef VERSUS_GLOBAL_TEMP_OBJECTS_H
#define VERSUS_GLOBAL_TEMP_OBJECTS_H

#if !defined(VERSUS_NATIVE_CLASS_TYPES_H) && !defined(VERSUS_PAWN_ACTION_EVENTS_H)
#include "versus_build.h"
#include "unreal_object.h"
#endif

#if !defined(UNREAL_CONTAINERS_H) && !defined(VERSUS_OWNING_ARRAYS_H) && !defined(VERSUS_STATS_ARRAYS_H)
#include "versus_arrays.h"
#endif

class UGlobalTempObjects : public UObject {
public:
    virtual ~UGlobalTempObjects();
    TArray<UObject **> GlobalObjectPtrs;
    void AddReference(UObject **Ref);
};

#endif
