#include "versus_build.h"
#include "versus_check_result.h"
#include "versus_level_collision.h"

UBOOL ULevel::SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End,
                              const FVector &Start, DWORD TraceFlags, const FVector &Extent)
{
    FMemMark Mark(GMem);
    if (!(TraceFlags & 0x20000))
        TraceFlags |= 0x400;

    FCheckResult *FirstHit = MultiLineCheck(GMem, End, Start, Extent,
                                            (TraceFlags & 4) ? GetLevelInfo() : 0,
                                            TraceFlags, SourceActor);
    FVector Direction = (End - Start).SafeNormal();
    DWORD IgnorePolyFlags = ((TraceFlags & 0x100) | 0x8000) >> 8;
    FCheckResult *Test;
    for (Test = FirstHit; Test; Test = Test->GetNext()) {
        if ((TraceFlags & 0x80100) && Test->Actor == GetLevelInfo()) {
            INT Surface = Model->Nodes(Test->Item).iSurf;
            if (Model->Surfs(Surface).PolyFlags & IgnorePolyFlags)
                continue;
        }
        if (!Test->unk_34)
            break;
        Test->Actor->eventBulletWentTru(SourceActor, Test->Location, Test->Normal, Direction);
    }

    if (Test) {
        Hit = *Test;
    } else {
        Hit.Time = 1.0f;
        Hit.Actor = 0;
    }
    Mark.Pop();
    return Test == 0;
}
