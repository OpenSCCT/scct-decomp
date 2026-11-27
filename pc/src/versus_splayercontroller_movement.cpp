#include "versus_build.h"
#include "unreal_script.h"
#include "versus_check_result.h"
#include "versus_sbase_classes.h"

enum {
    TRACE_AllBlocking = 0xdf,
    TRACE_StopAtFirstHit = 0x200
};

void ASPlayerController::execCheckCeilingForLadder(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(UBOOL*)Result = 0;
    FCheckResult Hit(1.0f);
    FVector Start;
    Start.X = Pawn->Location.X;
    Start.Y = Pawn->Location.Y;
    Start.Z = Pawn->Location.Z;
    FVector End;
    End.X = Start.X;
    End.Y = Start.Y;
    End.Z = Start.Z + 64.0f;
    FVector Extent(35.0f, 35.0f, 87.5f);

    XLevel->SingleLineCheck(Hit, Pawn, End, Start, TRACE_AllBlocking | TRACE_StopAtFirstHit, Extent);
    if (Hit.Time == 1.0f)
        *(UBOOL*)Result = 1;
}
