/* The x86 native handler ABI passes the receiver in ecx, followed by
   the script frame and result pointer on the stack. */
#include "versus_native_registration.h"
#include "versus_vm_property_context.h"
#define HANDLER(name, result_type) \
    void __fastcall name(struct ScriptObject *self, void *unused_edx, struct ScriptFrame *frame, result_type *result)
#define DISPATCH ((VmHandler * const *)0x10c819d8u)

/* During expression evaluation, the VM records the address and owner of a
   writable property. If the expression has no address, the local value
   receives the write. */
#define PROPERTY_ADDRESS (*(unsigned char **)0x10c78b9cu)
#define PROPERTY_OWNER (*(struct ScriptObject **)0x10c78ba4u)
#define PROPERTY_DESCRIPTOR (*(struct ScriptProperty **)0x10c78b64u)
typedef void (__fastcall *OnPropertyWrite)(struct ScriptObject *, const void *, void *);
static __forceinline void *write_address(struct ScriptFrame *frame, void *fallback)
{
    struct ScriptObject *owner;
    void *address;
    struct ScriptObject *receiver = frame->object;
    unsigned int opcode = *frame->code++;
    PROPERTY_ADDRESS = 0;
    DISPATCH[opcode](receiver, opcode, frame, fallback);
    owner = PROPERTY_OWNER;
    if (owner) {
        OnPropertyWrite *vtable = *(OnPropertyWrite **)owner;
        vtable[21](owner, vtable, PROPERTY_DESCRIPTOR);
    }
    address = PROPERTY_ADDRESS;
    return address ? address : fallback;
}



#define CHANGE_BY_ONE(name, type, expression) \
    HANDLER(name, type) \
    { \
        type fallback = 0; \
        type *value = write_address(frame, &fallback); \
        ++frame->code; \
        *result = (expression); \
    }

CHANGE_BY_ONE(execAddAdd_PreByte, unsigned char, ++*value)
CHANGE_BY_ONE(execAddAdd_Byte, unsigned char, (*value)++)
CHANGE_BY_ONE(execSubtractSubtract_PreByte, unsigned char, --*value)
CHANGE_BY_ONE(execSubtractSubtract_Byte, unsigned char, (*value)--)
CHANGE_BY_ONE(execAddAdd_PreInt, int, ++*value)
CHANGE_BY_ONE(execAddAdd_Int, int, (*value)++)
CHANGE_BY_ONE(execSubtractSubtract_PreInt, int, --*value)
CHANGE_BY_ONE(execSubtractSubtract_Int, int, (*value)--)
