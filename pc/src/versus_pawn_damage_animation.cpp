// Damage responses selected by the SBasePawn action dispatcher.
#include "versus_pawn_action_events.h"
#include "versus_mesh_instance_types.h"
#include "versus_skeletal_animation_types.h"

void ASBasePawn::eventBeginStickySkin()
{
    ProcessEvent(FindFunctionChecked(NAME_BeginStickySkin, 0), 0, 0);
}

struct ASBasePawn_eventevStickyShockSfx_Parms {
    UBOOL bSpawn;
};

void ASBasePawn::eventevStickyShockSfx(UBOOL bSpawn)
{
    ASBasePawn_eventevStickyShockSfx_Parms Parms;
    Parms.bSpawn = bSpawn;
    ProcessEvent(FindFunctionChecked(NAME_evStickyShockSfx, 0), &Parms, 0);
}

struct ASBasePawn_eventPlayFirstPersonDamage_Parms {
    INT TheAction;
};

inline void ASBasePawn::eventPlayFirstPersonDamage(INT TheAction)
{
    ASBasePawn_eventPlayFirstPersonDamage_Parms Parms;
    Parms.TheAction = TheAction;
    ProcessEvent(FindFunctionChecked(NAME_PlayFirstPersonDamage, 0), &Parms, 0);
}

// The method name describes its role. SBase.u supplies the action and property names.
void ASBasePawn::PlayDamageAnimation(INT Action)
{
    USkeletalMeshInstance *Instance = static_cast<USkeletalMeshInstance *>(MeshInstance);
    if (MyWeapon && SPawnType == SPAWNDEFENSE)
        eventPlayFirstPersonDamage(Action);

    switch (Action) {
    case SA_DMG_SPECIAL_LEFT:
        Instance->ApplyBlendParams(17, 1.f, 0.f, 0.f, NAME_B_Head, 0);
        PlayAnim(17, NAME_PainStHsLt2, 1.f, 0.f);
        return;
    case SA_DMG_SPECIAL_RIGHT:
        Instance->ApplyBlendParams(17, 1.f, 0.f, 0.f, NAME_B_Head, 0);
        PlayAnim(17, NAME_PainStHsRt2, 1.f, 0.f);
        return;
    case SA_DMG_SPECIAL_FRONT:
        Instance->ApplyBlendParams(17, 1.f, 0.f, 0.f, NAME_B_Head, 0);
        PlayAnim(17, NAME_PainStHsFd2, 1.f, 0.f);
        return;
    case SA_DMG_SPECIAL_BACK:
        Instance->ApplyBlendParams(17, 1.f, 0.f, 0.f, NAME_B_Head, 0);
        PlayAnim(17, NAME_PainStHsBk2, 1.f, 0.f);
        return;
    }

    if (!Velocity.IsZero()) {
        if (Action != SA_DMG_ELECTRIC) {
            Instance->ApplyBlendParams(17, 1.f, 0.f, 0.f, NAME_B_Head, 0);
            PlayAnim(17, NAME_GoglStAlDn2, 1.f, 0.f);
            return;
        }
    } else if (Action != SA_DMG_ELECTRIC && Action != SA_DMG_ELECTRIC_NOANIMS) {
        Instance->ApplyBlendParams(17, 1.f, 0.f, 0.f, NAME_None, 0);
    }

    if (!bIsCrouched) {
        if (WeaponLoaded > 0) {
            switch (Action) {
            case SA_DMG_ELECTRIC_NOANIMS:
                Instance->ApplyBlendParams(23, 1.f, 0.f, 0.f, NAME_B_Head, 0);
                PlayAnim(23, ADamageStElectric2, 1.f, .2f, 1);
                break;
            case SA_DMG_ELECTRIC:
                Instance->ApplyBlendParams(23, 1.f, 0.f, 0.f, NAME_None, 0);
                PlayAnim(23, ADamageStElectric2, 1.f, .2f, 1);
                break;
            case SA_DMG_HEAD:
            case SA_DMG_CHEST_BACK:
                PlayAnim(17, ADamageStChestBack2, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_FRONT:
                PlayAnim(17, ADamageStChestForward2, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_LEFT:
                PlayAnim(17, ADamageStChestLeft2, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_RIGHT:
                PlayAnim(17, ADamageStChestRight2, 1.f, 0.f);
                break;
            case SA_DMG_ARM_LEFT:
                PlayAnim(17, ADamageStArmLeft2, 1.f, 0.f);
                break;
            case SA_DMG_ARM_RIGHT:
                PlayAnim(17, ADamageStArmRight2, 1.f, 0.f);
                break;
            case SA_DMG_LEG_LEFT:
                PlayAnim(17, ADamageStLegLeft2, 1.f, 0.f);
                break;
            case SA_DMG_LEG_RIGHT:
                PlayAnim(17, ADamageStLegRight2, 1.f, 0.f);
                break;
            default:
                Instance->ApplyBlendParams(17, 0.f, 0.f, 0.f, NAME_None, 0);
                break;
            }
        } else {
            switch (Action) {
            case SA_DMG_ELECTRIC_NOANIMS:
                Instance->ApplyBlendParams(23, 1.f, 0.f, 0.f, NAME_B_Head, 0);
                PlayAnim(23, ADamageStElectric0, 1.f, .2f, 1);
                break;
            case SA_DMG_ELECTRIC:
                Instance->ApplyBlendParams(23, 1.f, 0.f, 0.f, NAME_None, 0);
                PlayAnim(23, ADamageStElectric0, 1.f, .2f, 1);
                break;
            case SA_DMG_HEAD:
            case SA_DMG_CHEST_BACK:
                PlayAnim(17, ADamageStChestBack0, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_FRONT:
                PlayAnim(17, ADamageStChestForward0, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_LEFT:
                PlayAnim(17, ADamageStChestLeft0, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_RIGHT:
                PlayAnim(17, ADamageStChestRight0, 1.f, 0.f);
                break;
            case SA_DMG_ARM_LEFT:
                PlayAnim(17, ADamageStArmLeft0, 1.f, 0.f);
                break;
            case SA_DMG_ARM_RIGHT:
                PlayAnim(17, ADamageStArmRight0, 1.f, 0.f);
                break;
            case SA_DMG_LEG_LEFT:
                PlayAnim(17, ADamageStLegLeft0, 1.f, 0.f);
                break;
            case SA_DMG_LEG_RIGHT:
                PlayAnim(17, ADamageStLegRight0, 1.f, 0.f);
                break;
            default:
                Instance->ApplyBlendParams(17, 0.f, 0.f, 0.f, NAME_None, 0);
                break;
            }
        }
    } else {
        if (WeaponLoaded > 0) {
            switch (Action) {
            case SA_DMG_ELECTRIC_NOANIMS:
                Instance->ApplyBlendParams(23, 1.f, 0.f, 0.f, NAME_B_Head, 0);
                PlayAnim(23, ADamageCrElectric2, 1.f, .2f, 1);
                break;
            case SA_DMG_ELECTRIC:
                Instance->ApplyBlendParams(23, 1.f, 0.f, 0.f, NAME_None, 0);
                PlayAnim(23, ADamageCrElectric2, 1.f, .2f, 1);
                break;
            case SA_DMG_HEAD:
            case SA_DMG_CHEST_BACK:
                PlayAnim(17, ADamageCrChestBack2, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_FRONT:
                PlayAnim(17, ADamageCrChestForward2, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_LEFT:
                PlayAnim(17, ADamageCrChestLeft2, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_RIGHT:
                PlayAnim(17, ADamageCrChestRight2, 1.f, 0.f);
                break;
            case SA_DMG_ARM_LEFT:
                PlayAnim(17, ADamageCrArmLeft2, 1.f, 0.f);
                break;
            case SA_DMG_ARM_RIGHT:
                PlayAnim(17, ADamageCrArmRight2, 1.f, 0.f);
                break;
            case SA_DMG_LEG_LEFT:
                PlayAnim(17, ADamageCrLegLeft2, 1.f, 0.f);
                break;
            case SA_DMG_LEG_RIGHT:
                PlayAnim(17, ADamageCrLegRight2, 1.f, 0.f);
                break;
            default:
                Instance->ApplyBlendParams(17, 0.f, 0.f, 0.f, NAME_None, 0);
                break;
            }
        } else {
            switch (Action) {
            case SA_DMG_ELECTRIC_NOANIMS:
                Instance->ApplyBlendParams(23, 1.f, 0.f, 0.f, NAME_B_Head, 0);
                PlayAnim(23, ADamageCrElectric0, 1.f, .2f, 1);
                break;
            case SA_DMG_ELECTRIC:
                Instance->ApplyBlendParams(23, 1.f, 0.f, 0.f, NAME_None, 0);
                PlayAnim(23, ADamageCrElectric0, 1.f, .2f, 1);
                break;
            case SA_DMG_HEAD:
            case SA_DMG_CHEST_BACK:
                PlayAnim(17, ADamageCrChestBack0, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_FRONT:
                PlayAnim(17, ADamageCrChestForward0, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_LEFT:
                PlayAnim(17, ADamageCrChestLeft0, 1.f, 0.f);
                break;
            case SA_DMG_CHEST_RIGHT:
                PlayAnim(17, ADamageCrChestRight0, 1.f, 0.f);
                break;
            case SA_DMG_ARM_LEFT:
                PlayAnim(17, ADamageCrArmLeft0, 1.f, 0.f);
                break;
            case SA_DMG_ARM_RIGHT:
                PlayAnim(17, ADamageCrArmRight0, 1.f, 0.f);
                break;
            case SA_DMG_LEG_LEFT:
                PlayAnim(17, ADamageCrLegLeft0, 1.f, 0.f);
                break;
            case SA_DMG_LEG_RIGHT:
                PlayAnim(17, ADamageCrLegRight0, 1.f, 0.f);
                break;
            default:
                Instance->ApplyBlendParams(17, 0.f, 0.f, 0.f, NAME_None, 0);
                break;
            }
        }
    }
}
