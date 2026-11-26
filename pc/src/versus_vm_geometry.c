/* The x86 native handler ABI passes the receiver in ecx, followed by
   the script frame and result pointer on the stack. */
#include "versus_native_registration.h"
typedef struct Rotator { int pitch, yaw, roll; } Rotator;
#define HANDLER(name, result_type) \
    void __fastcall name(struct ScriptObject *self, void *unused_edx, struct ScriptFrame *frame, result_type *result)
#define DISPATCH ((VmHandler * const *)0x10c819d8u)

static __forceinline void step(struct ScriptFrame *frame, void *result)
{
    struct ScriptObject *receiver = frame->object;
    unsigned int opcode = *frame->code++;
    DISPATCH[opcode](receiver, opcode, frame, result);
}

HANDLER(execAdd_RotatorRotator, Rotator)
{
    Rotator a, b, value;
    step(frame, &a);
    step(frame, &b);
    ++frame->code;
    value.pitch = a.pitch + b.pitch;
    value.yaw = a.yaw + b.yaw;
    value.roll = a.roll + b.roll;
    *result = value;
}

HANDLER(execSubtract_RotatorRotator, Rotator)
{
    Rotator a, b, value;
    step(frame, &a);
    step(frame, &b);
    ++frame->code;
    value.pitch = a.pitch - b.pitch;
    value.yaw = a.yaw - b.yaw;
    value.roll = a.roll - b.roll;
    *result = value;
}

HANDLER(execEqualEqual_RotatorRotator, int)
{
    Rotator a, b;
    step(frame, &a);
    step(frame, &b);
    ++frame->code;
    *result = a.pitch == b.pitch && a.yaw == b.yaw && a.roll == b.roll;
}

HANDLER(execNotEqual_RotatorRotator, int)
{
    Rotator a, b;
    step(frame, &a);
    step(frame, &b);
    ++frame->code;
    *result = a.pitch != b.pitch || a.yaw != b.yaw || a.roll != b.roll;
}

double __cdecl tan(double), exp(double), atan2(double, double);

HANDLER(execTan, float)
{
    float a = 0.0f;
    step(frame, &a);
    ++frame->code;
    *result = (float)tan(a);
}

HANDLER(execExp, float)
{
    float a = 0.0f;
    step(frame, &a);
    ++frame->code;
    *result = (float)exp(a);
}

HANDLER(execAtan, float)
{
    float a = 0.0f, b;
    step(frame, &a);
    b = 0.0f;
    step(frame, &b);
    ++frame->code;
    *result = (float)atan2(a, b);
}

HANDLER(execClamp, int)
{
    int value = 0, low, high;
    step(frame, &value);
    low = 0;
    step(frame, &low);
    high = 0;
    step(frame, &high);
    ++frame->code;
    *result = value < low ? low : (value < high ? value : high);
}

HANDLER(execLerp, float)
{
    float fraction = 0, start, end;
    step(frame, &fraction);
    start = 0;
    step(frame, &start);
    end = 0;
    step(frame, &end);
    ++frame->code;
    *result = start + fraction * (end - start);
}
