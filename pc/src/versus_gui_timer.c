#include "versus_script_frame.h"

/* FAKEMATCH: the original members in this range are not recovered; these padding members are not
   named by offset and only push later members into place. */
struct GuiTimer {
    unsigned char unknown[0xc8];
    unsigned flags;
    float interval;
    float elapsed;
};

void __fastcall versus_kill_timer(struct GuiTimer *self, unsigned reserved_edx,
                                  struct VersusScriptFrame *stack, void *result) {
    ++stack->code;
    self->elapsed = 0;
    self->interval = 0;
    self->flags &= ~1u;
}
