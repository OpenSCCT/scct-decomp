// Versus Engine.Actor native handlers whose bodies do not need recovered class state.
#include "versus_build.h"
#include "versus_native_registration.h"
#include "unreal_types.h"
#include "unreal_containers.h"
#include "unreal_actor.h"

#define NATIVE_DISPATCH ((VmHandler * const *)0x10c819d8u)

static __forceinline void StepNativeArgument(ScriptFrame *frame, void *value)
{
    ScriptObject *receiver = frame->object;
    unsigned int opcode = *frame->code++;
    NATIVE_DISPATCH[opcode](receiver, opcode, frame, value);
}

extern "C" void __fastcall exec_Engine_Actor_EnablePB(
    ScriptObject *self, unsigned int unused_edx, ScriptFrame *frame, void *result)
{
    UBOOL bEnable = 0;
    StepNativeArgument(frame, &bEnable);
    ++frame->code;
    *(UBOOL *)result = 0;
}
