// versus_pawn_death_animation.cpp -- animation selection for SBasePawn death actions.
#include "versus_pawn_action_events.h"

// Direction spellings are inferred from the named actions in ASBasePawn::ExecuteAction.
enum EDeathDirection { DeathDown, DeathForward, DeathBack, DeathLeft, DeathRight, DeathDropAttack };

// PlayDeathAnimation is a descriptive name. The pawn type selects its attack or death sequence.
void ASBasePawn::PlayDeathAnimation(INT Direction)
{
    bLyingOnGround = 1;
    IK_Type = IKT_NONE;
    if (!bIsCrouched) {
        switch (Direction) {
        case DeathDropAttack:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, NAME_XxxxStAlAk0, 1.f, .25f);
            else
                PlayAnim(0, NAME_XxxxStAlAk2, 1.f, .25f);
            break;
        case DeathForward:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, ADeathStForward);
            else
                PlayAnim(0, ADeathStForward2H);
            break;
        case DeathBack:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, ADeathStBack);
            else
                PlayAnim(0, ADeathStBack2H);
            break;
        case DeathLeft:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, ADeathStLeft);
            else
                PlayAnim(0, ADeathStLeft2H);
            break;
        case DeathRight:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, ADeathStRight);
            else
                PlayAnim(0, ADeathStRight2H);
            break;
        case DeathDown:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, ADeathStDown);
            else
                PlayAnim(0, ADeathStDown2H);
            break;
        }
    } else {
        switch (Direction) {
        case DeathDropAttack:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, NAME_XxxxCrAlAk0);
            else
                PlayAnim(0, NAME_XxxxCrAlAk2);
            break;
        case DeathForward:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, ADeathCrForward);
            else
                PlayAnim(0, ADeathCrForward2H);
            break;
        case DeathBack:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, ADeathCrBack);
            else
                PlayAnim(0, ADeathCrBack2H);
            break;
        case DeathLeft:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, ADeathCrLeft);
            else
                PlayAnim(0, ADeathCrLeft2H);
            break;
        case DeathRight:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, ADeathCrRight);
            else
                PlayAnim(0, ADeathCrRight2H);
            break;
        case DeathDown:
            if (SPawnType == SPAWNOFFENSE)
                PlayAnim(0, ADeathCrDown);
            else
                PlayAnim(0, ADeathCrDown2H);
            break;
        }
    }
}

enum {
    SA_DIE_FORWARD = 40,
    SA_DIE_BACKWARD = 41,
    SA_DIE_LEFT = 42,
    SA_DIE_RIGHT = 43,
    SA_DIE_INPLACE = 44,
    SA_DIE_DROPATTACK = 46
};

// Link scaffolding. These six named ExecuteAction arms supply the six constant directions.
// The retail caller has nine call sites, including paths shared by multiple actions.
void Driver_DeathAnimation(ASBasePawn *Pawn, INT Action) {
    switch (Action) {
    case SA_DIE_FORWARD:
        Pawn->PlayDeathAnimation(DeathForward);
        break;
    case SA_DIE_BACKWARD:
        Pawn->PlayDeathAnimation(DeathBack);
        break;
    case SA_DIE_LEFT:
        Pawn->PlayDeathAnimation(DeathLeft);
        break;
    case SA_DIE_RIGHT:
        Pawn->PlayDeathAnimation(DeathRight);
        break;
    case SA_DIE_INPLACE:
        Pawn->PlayDeathAnimation(DeathDown);
        break;
    case SA_DIE_DROPATTACK:
        Pawn->PlayDeathAnimation(DeathDropAttack);
        break;
    }
}
