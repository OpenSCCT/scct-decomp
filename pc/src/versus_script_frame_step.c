#include "versus_native_registration.h"

void __fastcall step(struct ScriptObject *self, void *unused_edx, struct ScriptFrame *frame,
                     void *result)
{
    unsigned char opcode = *frame->code;
    ++frame->code;
    native_table[opcode](self, opcode, frame, result);
}
