// versus_pawn_action_events.cpp -- pawn script event dispatch and the shared function lookup.
#include "versus_pawn_action_events.h"

enum {
    SA_WALK_CR_0H = 75,
    SA_WALK_CR_2H = 76,
    SA_TOPLEDGE = 113,
    PHYS_Walking = 1,
    PHYS_RootMotion = 5,
    NOBTW = 0,
    NOPipH = 0
};

struct ASPlayerController_eventClientStopRM_Parms {
    INT TheAction;
};

void ASPlayerController::eventClientStopRM(INT TheAction)
{
    ASPlayerController_eventClientStopRM_Parms Parms;
    Parms.TheAction = TheAction;
    ProcessEvent(FindFunctionChecked(NAME_ClientStopRM, 0), &Parms, 0);
}

struct ASBasePawn_eventEvSetWeaponLoaded_Parms {
    INT num;
};

void ASBasePawn::eventEvSetWeaponLoaded(INT num)
{
    ASBasePawn_eventEvSetWeaponLoaded_Parms Parms;
    Parms.num = num;
    ProcessEvent(FindFunctionChecked(NAME_EvSetWeaponLoaded, 0), &Parms, 0);
}

// Link context from the retail root-motion transition at 0x1e2ee0.
// The top-ledge action supplies the pawn's post-root-motion translation and yaw.
BYTE ASBasePawn::StartActionRootMotion(INT Action, FVector MoveAfter, FLOAT Yaw)
{
    APlayerController *Owner = GetTopOwner(this);
    if (Owner && !Owner->IsLocalPlayerController() && Action == SA_TOPLEDGE &&
        CheckLedgeGrab(0) != 1) {
        ((ASPlayerController *)Controller)->eventClientStopRM(Action);
        return 0;
    }
    vMoveAfterRM = MoveAfter;
    rRotAfterRM = (INT)Yaw;
    setPhysics(PHYS_RootMotion, 0, GMath_UnitZ);
    return 1;
}

// Link context from the retail caller of EvSetWeaponLoaded at 0x1e5000.
// Restores crouched walking for the pawn type after resetting its special movement state.
void ASBasePawn::ReinitBecauseOfDivergences()
{
    bBeginSpecial12Anim = 0;
    bIsRolling = 0;
    bNoRunAnimation = 0;
    fBlendTimeWithC0 = 0.0f;
    BlendChangeTime = 0.25f;
    BTW = NOBTW;
    IK_Type = SPawnType == SPAWNDEFENSE ? IKT_WEAPONLOADED : IKT_NONE;
    IK_TypeBeforeDamage = IKT_NONE;
    fBlendTimeWithC0 = 0.0f;
    PipHFire = NOPipH;
    fTimeOfFeetLedge = 0.0f;
    Crouch(0);
    bWeaponTransit = 0;
    setPhysics(PHYS_Walking, 0, GMath_UnitZ);
    FadeChannels(1, 25, 1.0f);
    if (SPawnType == SPAWNDEFENSE) {
        eventEvSetWeaponLoaded(2);
        PlayWalkingAction(SA_WALK_CR_2H);
    } else {
        eventEvSetWeaponLoaded(0);
        PlayWalkingAction(SA_WALK_CR_0H);
    }
    SetCollision(1, 0, 0);
    bLyingOnGround = 0;
    m_AttackTarget = 0;
    m_AttackedBy = 0;
    bCollideWorld = 1;
}

void ASBasePawn::execReinitBecauseOfDivergences(FFrame &Stack, void *const Result)
{
    Stack.Code++;
    ReinitBecauseOfDivergences();
}

UObject *__stdcall FindFieldInHash(UState *Struct, FFieldHash *Hash, FName InName)
{
    for (;;) {
        if (Hash->HashCount) {
            FFieldHashEntry *Entry = &Hash->Entries[(Hash->HashCount - 1) & InName.GetIndex()];
            for (UObject *Field = Entry->Field; Field; Field = Entry->Field) {
                if (Field->Name == InName)
                    return Field;
                if (!Entry->Next)
                    break;
                Entry = &Hash->Entries[Entry->Next];
            }
        }
        UState *Super = (UState *)Struct->SuperField;
        if (!Super)
            return 0;
        Struct = Super;
        Hash = &Struct->FieldHash;
    }
}

inline UObject *UObject::FindInStateOrClass(FName InName, INT Global)
{
    if (StateFrame && StateFrame->StateNode && !Global) {
        UObject *Found = FindFieldInHash(StateFrame->StateNode, &StateFrame->StateNode->FieldHash,
                                         InName);
        if (Found)
            return Found;
    }
    return FindFieldInHash(Class, &Class->FieldHash, InName);
}

inline UFunction *CastFunction(UObject *Found)
{
    return Found && (Found->Class->ClassCastFlags & 0x80000) ? (UFunction *)Found : 0;
}
UFunction *UObject::FindFunctionChecked(FName InName, INT Global)
{
    if (!GScriptFunctionLookupEnabled)
        return 0;
    return CastFunction(FindInStateOrClass(InName, Global));
}
