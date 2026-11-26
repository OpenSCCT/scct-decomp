/* The x86 native handler ABI passes the receiver in ecx, followed by
   the script frame and result pointer on the stack. */
#include "versus_native_registration.h"
typedef struct Vector { float x, y, z; } Vector;
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


typedef struct ScriptNode {
    unsigned char opaque[0x3c];
    unsigned char *script;
} ScriptNode;
static __forceinline int read_int(struct ScriptFrame *frame)
{
    int value = *(const int *)frame->code;
    frame->code += sizeof(int);
    return value;
}

#define CAST_VALUE(name, source_type, destination_type, conversion) \
    HANDLER(name, destination_type) { \
        source_type value = 0; \
        step(frame, &value); \
        *result = (conversion); \
    }

HANDLER(execSelf, struct ScriptObject *)
{
    *result = self;
}

HANDLER(execStop, void)
{
    frame->code = 0;
}

HANDLER(execIntConst, int)
{
    *result = read_int(frame);
}

HANDLER(execFloatConst, float)
{
    float value = *(const float *)frame->code;
    frame->code += sizeof(float);
    *result = value;
}

HANDLER(execVectorConst, Vector)
{
    *result = *(const Vector *)frame->code;
    frame->code += sizeof(Vector);
}

HANDLER(execRotationConst, Rotator)
{
    result->pitch = read_int(frame);
    result->yaw = read_int(frame);
    result->roll = read_int(frame);
}

HANDLER(execByteConst, unsigned char)
{
    *result = *frame->code;
    ++frame->code;
}

HANDLER(execIntConstByte, int)
{
    *result = *frame->code;
    ++frame->code;
}

HANDLER(execIntZero, int)
{
    *result = 0;
}

HANDLER(execIntOne, int)
{
    *result = 1;
}

HANDLER(execPrimitiveCast, void)
{
    unsigned int cast = *frame->code++;
    ((VmHandler * const *)0x10c815d8u)[cast](frame->object, cast, frame, result);
}

CAST_VALUE(execByteToInt, unsigned char, int, (int)value)

CAST_VALUE(execByteToBool, unsigned char, int, value != 0)

CAST_VALUE(execByteToFloat, unsigned char, float, (float)value)

HANDLER(execJump, void)
{
    int offset = *(const unsigned short *)frame->code;
    frame->code += sizeof(unsigned short);
    frame->code = frame->node->script + offset;
}
