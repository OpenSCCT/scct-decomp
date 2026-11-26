/* FAKEMATCH: this wrapper keeps the forwarded word on the stack while the C
   fastcall declaration places the native method's receiver in ECX. */
struct MemberDispatchArgument { unsigned value; };

extern unsigned __fastcall invoke_member(void *receiver, struct MemberDispatchArgument first, struct MemberDispatchArgument second);

unsigned __stdcall dispatch_member(void *receiver, struct MemberDispatchArgument first, struct MemberDispatchArgument second)
{
    return invoke_member(receiver, first, second);
}
