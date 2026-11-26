/* C-compatible declarations for script property-expression state. */
#ifndef VERSUS_VM_PROPERTY_CONTEXT_H
#define VERSUS_VM_PROPERTY_CONTEXT_H

struct ScriptObject;
struct ScriptProperty;

extern unsigned char *property_address;
extern struct ScriptObject *property_owner;
extern struct ScriptProperty *property_descriptor;

#endif
