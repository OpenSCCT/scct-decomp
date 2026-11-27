// versus_check_result.h -- the shared Versus iterator and trace-result records
#ifndef VERSUS_CHECK_RESULT_H
#define VERSUS_CHECK_RESULT_H

#include "versus_build.h"

#ifdef SCCT_VERSUS
#include "unreal_math.h"
#include "versus_globals.h"
#include "unreal_actor.h"

class UPrimitive;
class UMaterial;

struct FIteratorList {
    FIteratorList *Next;

    FIteratorList(FIteratorList *InNext) : Next(InNext) {}
};

struct FIteratorActorList : public FIteratorList {
    AActor *Actor;

    FIteratorActorList(FIteratorList *InNext, AActor *InActor)
        : FIteratorList(InNext), Actor(InActor) {}
};

struct FCheckResult : public FIteratorActorList {
    FVector     Location;
    FVector     Normal;
    UPrimitive *Primitive;
    FLOAT       Time;
    INT         Item;
    UMaterial  *Material;
    INT         unk_30;
    INT         unk_34;

    FCheckResult *GetNext() const { return static_cast<FCheckResult *>(Next); }

    FCheckResult(FLOAT InTime, FCheckResult *InNext = 0)
        : FIteratorActorList(InNext, 0),
          Location(*selected_3cacc0),
          Normal(*selected_3cacc0),
          Primitive(0),
          Time(InTime),
          Item(-1),
          Material(0),
          unk_34(0)
    {}
};
#endif

#endif // VERSUS_CHECK_RESULT_H
