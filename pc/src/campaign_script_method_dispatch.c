#include "campaign_vm_frame.h"

struct Word { unsigned value; };

extern unsigned __fastcall native_EchelonAI_BaseSoldier_SwitchWithOtherEnemy(struct ScriptObject *, struct Word);
HANDLER(exec_EchelonAI_BaseSoldier_SwitchWithOtherEnemy, unsigned)
{
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = native_EchelonAI_BaseSoldier_SwitchWithOtherEnemy(self, arg1);
}

extern unsigned __fastcall native_EchelonAI_BaseSoldier_CanHandleChokeDoor(struct ScriptObject *, struct Word);
HANDLER(exec_EchelonAI_BaseSoldier_CanHandleChokeDoor, unsigned)
{
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = native_EchelonAI_BaseSoldier_CanHandleChokeDoor(self, arg1);
}

extern unsigned __fastcall native_AActor_DetachFromBone(struct ScriptObject *, struct Word);
HANDLER(exec_AActor_DetachFromBone, unsigned)
{
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = native_AActor_DetachFromBone(self, arg1);
}

extern unsigned __fastcall native_AActor_IsAnimating(struct ScriptObject *, struct Word);
HANDLER(exec_AActor_IsAnimating, unsigned)
{
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = native_AActor_IsAnimating(self, arg1);
}

extern unsigned __fastcall native_Engine_Pawn_GetIKCompFlag(struct ScriptObject *, struct Word);
HANDLER(exec_Engine_Pawn_GetIKCompFlag, unsigned)
{
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = native_Engine_Pawn_GetIKCompFlag(self, arg1);
}

extern unsigned __fastcall native_Echelon_EInventory_CanAddItem(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EInventory_CanAddItem, unsigned)
{
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = native_Echelon_EInventory_CanAddItem(self, arg1);
}

extern unsigned __fastcall native_Echelon_EPattern_IsSomeoneAbleToReachBody(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EPattern_IsSomeoneAbleToReachBody, unsigned)
{
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = native_Echelon_EPattern_IsSomeoneAbleToReachBody(self, arg1);
}

extern unsigned __fastcall native_Echelon_EAIManager_GetNPCLastZone(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EAIManager_GetNPCLastZone, unsigned)
{
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = native_Echelon_EAIManager_GetNPCLastZone(self, arg1);
}

HANDLER(exec_EchelonAI_BaseCivilian_ShouldUseFlashLight, unsigned)
{
    typedef unsigned (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = (*(Method **)self)[177](self, arg1);
}

HANDLER(exec_Engine_ESoftBodyActor_StepClimb, unsigned)
{
    typedef unsigned (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = (*(Method **)self)[169](self, arg1);
}

HANDLER(exec_Engine_Controller_TestSearchPoint, unsigned)
{
    typedef unsigned (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = (*(Method **)self)[175](self, arg1);
}

HANDLER(exec_Echelon_ESRA_ApplyImpulse, unsigned)
{
    typedef unsigned (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = (*(Method **)self)[170](self, arg1);
}

HANDLER(exec_Echelon_EBaseDoor_GetInteraction, unsigned)
{
    typedef unsigned (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = (*(Method **)self)[190](self, arg1);
}

extern float __fastcall native_Engine_Actor_GetAnimTime(struct ScriptObject *, struct Word);
HANDLER(exec_Engine_Actor_GetAnimTime, float)
{
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = native_Engine_Actor_GetAnimTime(self, arg1);
}

extern float __fastcall native_Echelon_EAIManager_GetNPCLastKnownTimeUpdate(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EAIManager_GetNPCLastKnownTimeUpdate, float)
{
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = native_Echelon_EAIManager_GetNPCLastKnownTimeUpdate(self, arg1);
}

HANDLER(exec_Engine_Actor_IsRainingOnActor, unsigned char)
{
    typedef unsigned char (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct ScriptObject *receiver;
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    receiver = *(struct ScriptObject **)((unsigned char *)self + 0x7c);
    *result = (*(Method **)receiver)[52](receiver, arg1);
}

extern void __fastcall native_Engine_NavMeshActor_ChangeTriangleState(struct ScriptObject *, struct Word, struct Word);
HANDLER(exec_Engine_NavMeshActor_ChangeTriangleState, void)
{
    struct ScriptObject *receiver;
    struct Word arg1, arg2;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    finish_arguments(frame);
    receiver = *(struct ScriptObject **)((unsigned char *)self + 0x34c);
    native_Engine_NavMeshActor_ChangeTriangleState(receiver, arg1, arg2);
}

HANDLER(exec_Engine_ESoftBodyActor_AttachPawn, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word, struct Word, struct Word);
    struct Word arg1, arg2, arg3;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    arg3.value = 0;
    step(frame, &arg3);
    finish_arguments(frame);
    (*(Method **)self)[168](self, arg1, arg2, arg3);
}

HANDLER(exec_UCanvas_VideoPlay, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word, struct Word, struct Word);
    struct Word arg1, arg2, arg3;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    arg3.value = 0;
    step(frame, &arg3);
    finish_arguments(frame);
    (*(Method **)self)[36](self, arg1, arg2, arg3);
}

HANDLER(exec_Echelon_EPlayerController_NotifyMenu, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word, struct Word, struct Word);
    struct Word arg1, arg2, arg3;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    arg3.value = 0;
    step(frame, &arg3);
    finish_arguments(frame);
    (*(Method **)self)[184](self, arg1, arg2, arg3);
}

HANDLER(exec_Engine_EInteractObject_CPPSetInteractLocation, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    (*(Method **)self)[172](self, arg1);
}

HANDLER(exec_Engine_EInteractObject_CPPPostInteract, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    (*(Method **)self)[171](self, arg1);
}

HANDLER(exec_Engine_EInteractObject_CPPInteract, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    (*(Method **)self)[170](self, arg1);
}

HANDLER(exec_AProjector_DetachProjector, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    (*(Method **)self)[167](self, arg1);
}

HANDLER(exec_Engine_LevelInfo_RemoveFromAllUsersAcknowledgeList, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    (*(Method **)self)[174](self, arg1);
}

HANDLER(exec_Engine_LevelInfo_NotifyNPCofNavMeshChanges, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    (*(Method **)self)[170](self, arg1);
}

HANDLER(exec_UCanvas_VideoGotoFrame, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    (*(Method **)self)[35](self, arg1);
}

HANDLER(exec_Echelon_EGameplayObject_SetMalfunctionning, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    (*(Method **)self)[170](self, arg1);
}

HANDLER(exec_Echelon_EScopeAttachment_ToggleScope, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    (*(Method **)self)[185](self, arg1);
}

HANDLER(exec_Echelon_EPawn_StartMouthMotion, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    (*(Method **)self)[201](self, arg1);
}

extern void __fastcall native_Engine_Pawn_ActivateBoneChain(struct ScriptObject *, struct Word, struct Word, struct Word);
HANDLER(exec_Engine_Pawn_ActivateBoneChain, void)
{
    struct Word arg1, arg2, arg3;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    arg3.value = 0;
    step(frame, &arg3);
    finish_arguments(frame);
    native_Engine_Pawn_ActivateBoneChain(self, arg1, arg2, arg3);
}

extern void __fastcall native_Echelon_EPattern_SendPatternEvent(struct ScriptObject *, struct Word, struct Word, struct Word);
HANDLER(exec_Echelon_EPattern_SendPatternEvent, void)
{
    struct Word arg1, arg2, arg3;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    arg3.value = 0;
    step(frame, &arg3);
    finish_arguments(frame);
    native_Echelon_EPattern_SendPatternEvent(self, arg1, arg2, arg3);
}

extern void __fastcall native_EchelonIngredient_EElevatorPanel_SendElevator(struct ScriptObject *, struct Word, struct Word, struct Word);
HANDLER(exec_EchelonIngredient_EElevatorPanel_SendElevator, void)
{
    struct Word arg1, arg2, arg3;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    arg3.value = 0;
    step(frame, &arg3);
    finish_arguments(frame);
    native_EchelonIngredient_EElevatorPanel_SendElevator(self, arg1, arg2, arg3);
}

HANDLER(exec_UCanvas_SetPos, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word, struct Word);
    struct Word arg1, arg2;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    finish_arguments(frame);
    (*(Method **)self)[40](self, arg1, arg2);
}

HANDLER(exec_UCanvas_SetOrigin, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word, struct Word);
    struct Word arg1, arg2;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    finish_arguments(frame);
    (*(Method **)self)[41](self, arg1, arg2);
}

HANDLER(exec_UCanvas_SetClip, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word, struct Word);
    struct Word arg1, arg2;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    finish_arguments(frame);
    (*(Method **)self)[31](self, arg1, arg2);
}

HANDLER(exec_Echelon_EPlayerController_NotifyInterestObject, void)
{
    typedef void (__fastcall *Method)(struct ScriptObject *, struct Word, struct Word);
    struct Word arg1, arg2;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    finish_arguments(frame);
    (*(Method **)self)[185](self, arg1, arg2);
}

extern unsigned __fastcall native_Echelon_ECoopPlayerController_IsValidCoopInteract(struct ScriptObject *, struct Word, struct Word);
HANDLER(exec_Echelon_ECoopPlayerController_IsValidCoopInteract, unsigned)
{
    struct Word arg1, arg2;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    finish_arguments(frame);
    *result = native_Echelon_ECoopPlayerController_IsValidCoopInteract(self, arg1, arg2);
}

extern unsigned __fastcall native_Echelon_EPawn_ArePointsConnected(struct ScriptObject *, struct Word, struct Word);
HANDLER(exec_Echelon_EPawn_ArePointsConnected, unsigned)
{
    struct Word arg1, arg2;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    finish_arguments(frame);
    *result = native_Echelon_EPawn_ArePointsConnected(self, arg1, arg2);
}

extern void __fastcall native_Echelon_EAIManager_UnSubscribeObjectToHWManager(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EAIManager_UnSubscribeObjectToHWManager, void)
{
    struct ScriptObject *receiver;
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    receiver = *(struct ScriptObject **)((unsigned char *)self + 0x308);
    native_Echelon_EAIManager_UnSubscribeObjectToHWManager(receiver, arg1);
}

extern void __fastcall native_Echelon_EAIManager_UnSubscribeActorToHWManager(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EAIManager_UnSubscribeActorToHWManager, void)
{
    struct ScriptObject *receiver;
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    receiver = *(struct ScriptObject **)((unsigned char *)self + 0x308);
    native_Echelon_EAIManager_UnSubscribeActorToHWManager(receiver, arg1);
}

extern void __fastcall native_Echelon_EAIManager_SubscribeObjectToHWManager(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EAIManager_SubscribeObjectToHWManager, void)
{
    struct ScriptObject *receiver;
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    receiver = *(struct ScriptObject **)((unsigned char *)self + 0x308);
    native_Echelon_EAIManager_SubscribeObjectToHWManager(receiver, arg1);
}

extern void __fastcall native_Echelon_EAIManager_SubscribeActorToHWManager(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EAIManager_SubscribeActorToHWManager, void)
{
    struct ScriptObject *receiver;
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    receiver = *(struct ScriptObject **)((unsigned char *)self + 0x308);
    native_Echelon_EAIManager_SubscribeActorToHWManager(receiver, arg1);
}

extern void __fastcall native_Echelon_EAIManager_UnSubscribeToSRAManager(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EAIManager_UnSubscribeToSRAManager, void)
{
    struct ScriptObject *receiver;
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    receiver = *(struct ScriptObject **)((unsigned char *)self + 0x304);
    native_Echelon_EAIManager_UnSubscribeToSRAManager(receiver, arg1);
}

extern void __fastcall native_Echelon_EAIManager_SubscribeToSRAManager(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EAIManager_SubscribeToSRAManager, void)
{
    struct ScriptObject *receiver;
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    receiver = *(struct ScriptObject **)((unsigned char *)self + 0x304);
    native_Echelon_EAIManager_SubscribeToSRAManager(receiver, arg1);
}

extern void __fastcall native_Echelon_EAIManager_UnSubscribeToChangedActorManager(struct ScriptObject *, struct Word);
HANDLER(exec_Echelon_EAIManager_UnSubscribeToChangedActorManager, void)
{
    struct ScriptObject *receiver;
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    receiver = *(struct ScriptObject **)((unsigned char *)self + 0x300);
    native_Echelon_EAIManager_UnSubscribeToChangedActorManager(receiver, arg1);
}

HANDLER(exec_Echelon_EBaseDoor_CanDoTrigger, unsigned)
{
    typedef unsigned (__fastcall *Method)(struct ScriptObject *, struct Word, struct Word);
    struct Word arg1, arg2;

    arg1.value = 0;
    step(frame, &arg1);
    arg2.value = 0;
    step(frame, &arg2);
    finish_arguments(frame);
    *result = (*(Method **)self)[194](self, arg1, arg2);
}

HANDLER(exec_Echelon_EPawn_GetMoveSpeed, float)
{
    typedef float (__fastcall *Method)(struct ScriptObject *, struct Word);
    struct Word arg1;

    arg1.value = 0;
    step(frame, &arg1);
    finish_arguments(frame);
    *result = (*(Method **)self)[192](self, arg1);
}
