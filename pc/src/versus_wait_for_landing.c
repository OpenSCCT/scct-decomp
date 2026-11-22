#include "versus_script_frame.h"

/* FAKEMATCH: the original members in this range are not recovered; these padding members are not
   named by offset and only push later members into place. */
struct StateFrame {
    unsigned char unknown[0x24];
    int latent_action;
};

/* FAKEMATCH: the original members in this range are not recovered; these padding members are not
   named by offset and only push later members into place. */
struct PawnPhysics {
    unsigned char unknown[0x2d8];
    unsigned char mode;
};

/* FAKEMATCH: the original members in this range are not recovered; these padding members are not
   named by offset and only push later members into place. */
struct LandingController {
    unsigned char unknown[12];
    struct StateFrame *state;
    unsigned char before_timer[0x1e8];
    float move_timer;
    unsigned char before_pawn[0x100];
    struct PawnPhysics *pawn;
};

void __fastcall versus_wait_for_landing(struct LandingController *self, unsigned reserved_edx,
                                        struct VersusScriptFrame *stack, void *result) {
    ++stack->code;
    self->move_timer = 4.0f;
    if (self->pawn && self->pawn->mode == 2) {
        self->state->latent_action = 528;
    }
}
