/* The x86 native handler ABI passes the receiver in ecx, followed by
   the script frame and result pointer on the stack. */
#include "versus_native_registration.h"
#define HANDLER(name, result_type) \
    void __fastcall name(struct ScriptObject *self, void *unused_edx, struct ScriptFrame *frame, result_type *result)

HANDLER(execIsPsx2, int)
{
    ++frame->code;
    *result = 0;
}

HANDLER(execLaunchContext, unsigned char)
{
    ++frame->code;
    *result = 0;
}

#define COMMAND_FILTER_ENABLED (*(int *)0x10c922e8u)
HANDLER(execEnableCommandFilter, void)
{
    ++frame->code;
    COMMAND_FILTER_ENABLED = 1;
}

HANDLER(execDisableCommandFilter, void)
{
    ++frame->code;
    COMMAND_FILTER_ENABLED = 0;
}
