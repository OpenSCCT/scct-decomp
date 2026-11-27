#ifndef VERSUS_LEVEL_TRACE_TYPES_H
#define VERSUS_LEVEL_TRACE_TYPES_H

#include "versus_build.h"
#include "unreal_types.h"

class AActor;
class UPrimitive;
class UMaterial;

struct FCheckResult
{
    FCheckResult *Next;         // 0x00
    AActor *Actor;              // 0x04
    FVector Location;           // 0x08
    FVector Normal;             // 0x14
    UPrimitive *Primitive;      // 0x20
    FLOAT Time;                 // 0x24
    INT Item;                   // 0x28
    UMaterial *Material;        // 0x2c
    INT Field30;                // 0x30
    UBOOL bNonBlocking;         // 0x34 (neutral: triggers Event_11db70 instead of stopping trace)

    FCheckResult() {}
    FCheckResult(FLOAT InTime, FCheckResult *InNext = 0);
    FCheckResult(const FCheckResult &Other);
    FCheckResult *GetNext() const { return Next; }
};

#endif
