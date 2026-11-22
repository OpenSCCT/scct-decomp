/* UObject's fifth virtual method consumes the script function, a parameter
   block and an optional result pointer on the stack. The two prototypes
   below describe the same x86 call, with either a null or live block.
   A positive float zero or one-word aggregate is stack-passed by the VC 7.1
   fastcall ABI and leaves ECX available for the UObject receiver. */
struct ScriptObject;
struct ScriptFunction;
/* FAKEMATCH: the original passes a function reference as a stack argument; this one-member
   struct only steers that stack slot. */
typedef struct { struct ScriptFunction *value; } FunctionReference;
/* FAKEMATCH: the original passes an event name as a stack argument; this one-member struct only
   steers that stack slot. */
typedef struct { unsigned int index; } ScriptEventName;
/* FAKEMATCH: the original passes a parameter block reference as a stack argument; this one-
   member struct only steers that stack slot. */
typedef struct { void *address; } ParameterReference;
/* FAKEMATCH: the original members in this range are not recovered; these padding members are not
   named by offset and only push later members into place. */
struct ScriptObjectMethods {
    void *earlier_methods[4];
    union {
        void (__fastcall *empty)(struct ScriptObject *, FunctionReference, float, float);
        void (__fastcall *parameters)(struct ScriptObject *, FunctionReference, ParameterReference, float);
    } process_event;
};
struct ScriptObject { const struct ScriptObjectMethods *methods; };
extern FunctionReference __fastcall find_script_function(struct ScriptObject *, ScriptEventName, float);
