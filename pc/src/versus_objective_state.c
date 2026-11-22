#include "versus_script_frame.h"

/* FAKEMATCH: the original members in this range are not recovered; these padding members are not
   named by offset and only push later members into place. */
struct Objective {
    unsigned char unknown[0x3e4];
    unsigned flags;
};

void __fastcall versus_objective_is_active(struct Objective *self, unsigned reserved_edx,
                                           struct VersusScriptFrame *stack, unsigned *result) {
    ++stack->code;
    *result = (~(self->flags >> 1)) & 1u;
}
