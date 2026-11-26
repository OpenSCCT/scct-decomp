/* FAKEMATCH: the member receives scalar words on the stack. This aggregate prevents
   the C __fastcall declaration from passing the first word in EDX. */
struct MemberForwardWord { unsigned value; };
/* FAKEMATCH: the embedded member receives the key address on the stack. This
   aggregate forces the pointer onto the stack in its C __fastcall declaration. */
struct MemberForwardPointer { const unsigned *value; };

extern void *__fastcall owner_1e6510(void *);
extern void *__fastcall owner_1ffa20(void *);
extern void *__fastcall owner_1ffca0(void *);
extern void *__fastcall owner_202cb0(void *);
extern void *__fastcall owner_4f8a30(void *);
extern void *__fastcall owner_4f9c20(void *);
extern unsigned char __fastcall active_4844e0(void *);
extern unsigned char __fastcall dispatch_137b10(void *, struct MemberForwardPointer, struct MemberForwardWord, struct MemberForwardWord);
extern unsigned char __fastcall dispatch_1a2740(void *, struct MemberForwardPointer, struct MemberForwardWord, struct MemberForwardWord);
extern unsigned char __fastcall dispatch_4f2e70(void *, struct MemberForwardPointer, struct MemberForwardWord, struct MemberForwardWord);
extern unsigned char __fastcall dispatch_4f7d80(void *, struct MemberForwardPointer, struct MemberForwardWord, struct MemberForwardWord);

#define FORWARD_IF_ACTIVE(Entry, MemberOffset, Owner, Active, Dispatch) \
    unsigned char __fastcall Entry(void *self, struct MemberForwardWord first, struct MemberForwardWord key, struct MemberForwardWord flags) \
    { \
        struct MemberForwardPointer address; \
        unsigned char enabled = Active(Owner(self)); \
        if (enabled) { \
            address.value = &key.value; \
            enabled = Dispatch((char *)self + MemberOffset, address, first, flags); \
        } \
        return enabled; \
    }

FORWARD_IF_ACTIVE(forward_137be0, 16, owner_1e6510, active_4844e0, dispatch_137b10)
FORWARD_IF_ACTIVE(forward_137c10, 356, owner_1e6510, active_4844e0, dispatch_137b10)
FORWARD_IF_ACTIVE(forward_1a28d0, 16, owner_202cb0, active_4844e0, dispatch_1a2740)
FORWARD_IF_ACTIVE(forward_1a2900, 356, owner_202cb0, active_4844e0, dispatch_1a2740)
FORWARD_IF_ACTIVE(forward_1a2940, 696, owner_202cb0, active_4844e0, dispatch_1a2740)
FORWARD_IF_ACTIVE(forward_1a2980, 1036, owner_202cb0, active_4844e0, dispatch_1a2740)
FORWARD_IF_ACTIVE(forward_1a29c0, 1376, owner_202cb0, active_4844e0, dispatch_1a2740)
FORWARD_IF_ACTIVE(forward_1a2a00, 1716, owner_202cb0, active_4844e0, dispatch_1a2740)
FORWARD_IF_ACTIVE(forward_1a2ad0, 16, owner_1ffa20, active_4844e0, dispatch_137b10)
FORWARD_IF_ACTIVE(forward_1a2b50, 16, owner_1ffca0, active_4844e0, dispatch_1a2740)
FORWARD_IF_ACTIVE(forward_1a2b80, 356, owner_1ffca0, active_4844e0, dispatch_1a2740)
FORWARD_IF_ACTIVE(forward_4f2f90, 522, owner_4f8a30, active_4844e0, dispatch_4f2e70)
FORWARD_IF_ACTIVE(forward_4f7ee0, 16, owner_4f9c20, active_4844e0, dispatch_4f7d80)
FORWARD_IF_ACTIVE(forward_4f7f10, 10, owner_4f8a30, active_4844e0, dispatch_4f2e70)
FORWARD_IF_ACTIVE(forward_4f9880, 356, owner_4f9c20, active_4844e0, dispatch_4f7d80)
FORWARD_IF_ACTIVE(forward_4f98c0, 696, owner_4f9c20, active_4844e0, dispatch_4f7d80)
FORWARD_IF_ACTIVE(forward_4f9900, 1036, owner_4f9c20, active_4844e0, dispatch_4f7d80)
FORWARD_IF_ACTIVE(forward_4f9940, 1376, owner_4f9c20, active_4844e0, dispatch_4f7d80)
FORWARD_IF_ACTIVE(forward_4f9980, 1716, owner_4f9c20, active_4844e0, dispatch_4f7d80)
