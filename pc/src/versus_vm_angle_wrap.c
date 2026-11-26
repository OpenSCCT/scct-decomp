/* The x86 native handler ABI passes the receiver in ecx, followed by
   the script frame and result pointer on the stack. */
#include "versus_native_registration.h"
#define HANDLER(name, result_type) \
    void __fastcall name(struct ScriptObject *self, void *unused_edx, struct ScriptFrame *frame, result_type *result)
#define DISPATCH ((VmHandler * const *)0x10c819d8u)



static __forceinline void step(struct ScriptFrame *frame, void *result)
{
    struct ScriptObject *receiver = frame->object;
    unsigned int opcode = *frame->code++;
    DISPATCH[opcode](receiver, opcode, frame, result);
}

typedef struct Rotator { int pitch, yaw, roll; } Rotator;

static __forceinline int wrap_angle(int angle)
{
    angle &= 65535;
    if (angle > 32767)
        angle -= 65536;
    return angle;
}


HANDLER(execNormalize, Rotator)
{
    Rotator r;
    Rotator angles;
    step(frame, &r);
    ++frame->code;
    angles.pitch = wrap_angle(r.pitch);
    angles.roll = wrap_angle(r.roll);
    angles.yaw = wrap_angle(r.yaw);
    *result = angles;
}

HANDLER(execClockwiseFrom_IntInt, int)
{
    int a = 0;
    int b;
    int difference;
    step(frame, &a);
    b = 0;
    step(frame, &b);
    ++frame->code;
    a &= 65535;
    b &= 65535;
    difference = a - b;
    if (difference < 0)
        difference = -difference;
    *result = difference > 32768 ? a < b : a > b;
}
