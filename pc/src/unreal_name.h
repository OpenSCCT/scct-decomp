// unreal_name.h -- FName, an index into the engine's global name table
#ifndef UNREAL_NAME_H
#define UNREAL_NAME_H

#include "unreal_types.h"

// Indices of names the Campaign executable registers before any package loads.
enum EName {
    NAME_Critical  = 761,
    NAME_ScriptLog = 770
};

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
};

#endif // UNREAL_NAME_H
