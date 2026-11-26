/* The x86 native handler ABI passes the receiver in ecx, followed by
   the script frame and result pointer on the stack. */
#include "versus_native_registration.h"
#include "versus_vm_property_context.h"
#define HANDLER(name, result_type) \
    void __fastcall name(struct ScriptObject *self, void *unused_edx, struct ScriptFrame *frame, result_type *result)
#define DISPATCH native_table


static __forceinline void step(struct ScriptFrame *frame, void *result)
{
    struct ScriptObject *receiver = frame->object;
    unsigned int opcode = *frame->code++;
    DISPATCH[opcode](receiver, opcode, frame, result);
}

typedef void (__fastcall *OnPropertyWrite)(struct ScriptObject *, const void *, void *);
static __forceinline void *write_address(struct ScriptFrame *frame, void *fallback)
{
    struct ScriptObject *owner;
    void *address;
    struct ScriptObject *receiver = frame->object;
    unsigned int opcode = *frame->code++;
    property_address = 0;
    DISPATCH[opcode](receiver, opcode, frame, fallback);
    owner = property_owner;
    if (owner) {
        OnPropertyWrite *vtable = *(OnPropertyWrite **)owner;
        vtable[21](owner, vtable, property_descriptor);
    }
    address = property_address;
    return address ? address : fallback;
}

HANDLER(execMultiplyEqual_ByteByte, unsigned char)
{
    unsigned char fallback = 0;
    unsigned char *lhs = write_address(frame, &fallback);
    unsigned char rhs = 0;
    step(frame, &rhs);
    ++frame->code;
    *result = (*lhs *= rhs);
}

HANDLER(execDivideEqual_ByteByte, unsigned char)
{
    unsigned char fallback = 0;
    unsigned char *lhs = write_address(frame, &fallback);
    unsigned char rhs = 0;
    step(frame, &rhs);
    ++frame->code;
    *result = rhs ? (*lhs /= rhs) : 0;
}
