/* Single-word aggregate arguments are passed on the stack by x86 fastcall. */
struct MemberDispatchArgument { unsigned value; };

extern unsigned __fastcall invoke_member(void *receiver, struct MemberDispatchArgument first, struct MemberDispatchArgument second);

unsigned __stdcall dispatch_member(void *receiver, struct MemberDispatchArgument first, struct MemberDispatchArgument second)
{
    return invoke_member(receiver, first, second);
}
