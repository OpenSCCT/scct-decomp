/* campaign_band3_ubi_callbacks.c -- virtual methods of the ubi.com callback classes that
   forward to an optional function pointer.

   The class names come from the run-time type information of the retail image. Each method
   listed here loads a function pointer stored in its object and, when one is set, jumps to it
   with the caller's own arguments; with no pointer set it returns. The pointers are __stdcall
   functions taking the method's arguments without the object. The method names, the argument
   meanings and the member names are unknown: members are named by offset and methods by their
   vtable slot. */

typedef void (__stdcall *UbiCallbackArgs0)(void);
typedef void (__stdcall *UbiCallbackArgs1)(unsigned int);
typedef void (__stdcall *UbiCallbackArgs2)(unsigned int, unsigned int);
typedef void (__stdcall *UbiCallbackArgs3)(unsigned int, unsigned int, unsigned int);
typedef void (__stdcall *UbiCallbackArgs5)(unsigned int, unsigned int, unsigned int, unsigned int,
                                           unsigned int);
typedef void (__stdcall *UbiCallbackArgs6)(unsigned int, unsigned int, unsigned int, unsigned int,
                                           unsigned int, unsigned int);

struct clFriendsCB
{
    unsigned char    unk_00[0x14];    /* not read by any function in this unit */
    UbiCallbackArgs2 unk_14;
    UbiCallbackArgs2 unk_18;
    UbiCallbackArgs1 unk_1c;
    UbiCallbackArgs1 unk_20;
    UbiCallbackArgs3 unk_24;
    unsigned char    unk_28[0x4];     /* not read by any function in this unit */
    UbiCallbackArgs3 unk_2c;
    unsigned char    unk_30[0xc];     /* not read by any function in this unit */
    UbiCallbackArgs6 unk_3c;
};

struct clLoginCB
{
    unsigned char    unk_00[0x18];    /* not read by any function in this unit */
    UbiCallbackArgs2 unk_18;
    UbiCallbackArgs0 unk_1c;
};

struct clPersistentCB
{
    unsigned char    unk_00[0xc];     /* not read by any function in this unit */
    UbiCallbackArgs0 unk_0c;
};

struct clLobbyCB
{
    unsigned char    unk_00[0xc];     /* not read by any function in this unit */
    UbiCallbackArgs1 unk_0c;
    UbiCallbackArgs0 unk_10;
    unsigned char    unk_14[0x24];    /* not read by any function in this unit */
    UbiCallbackArgs3 unk_38;
    UbiCallbackArgs2 unk_3c;
    unsigned char    unk_40[0x4];     /* not read by any function in this unit */
    UbiCallbackArgs5 unk_44;
    unsigned char    unk_48[0xc];     /* not read by any function in this unit */
    UbiCallbackArgs3 unk_54;
    unsigned char    unk_58[0xc];     /* not read by any function in this unit */
    UbiCallbackArgs3 unk_64;
    UbiCallbackArgs3 unk_68;
    unsigned char    unk_6c[0x28];    /* not read by any function in this unit */
    UbiCallbackArgs3 unk_94;
    UbiCallbackArgs3 unk_98;
    UbiCallbackArgs2 unk_9c;
    UbiCallbackArgs1 unk_a0;
    unsigned char    unk_a4[0x4];     /* not read by any function in this unit */
    UbiCallbackArgs3 unk_a8;
    UbiCallbackArgs3 unk_ac;
};

/*
================
clFriendsCB_slot_3_r60fbb0

Slot 3 of the clFriendsCB vtable at VA 0x11154c64.
Calls the function pointer at offset 0x14, if one is set.
================
*/
void __fastcall clFriendsCB_slot_3_r60fbb0(struct clFriendsCB *self, int unused,
                                           unsigned int arg1, unsigned int arg2)
{
    if (self->unk_14)
        self->unk_14(arg1, arg2);
}

/*
================
clFriendsCB_slot_4_r60fbc0

Slot 4 of the clFriendsCB vtable at VA 0x11154c64.
Calls the function pointer at offset 0x18, if one is set.
================
*/
void __fastcall clFriendsCB_slot_4_r60fbc0(struct clFriendsCB *self, int unused,
                                           unsigned int arg1, unsigned int arg2)
{
    if (self->unk_18)
        self->unk_18(arg1, arg2);
}

/*
================
clFriendsCB_slot_5_r60fbd0

Slot 5 of the clFriendsCB vtable at VA 0x11154c64.
Calls the function pointer at offset 0x1c, if one is set.
================
*/
void __fastcall clFriendsCB_slot_5_r60fbd0(struct clFriendsCB *self, int unused, unsigned int arg1)
{
    if (self->unk_1c)
        self->unk_1c(arg1);
}

/*
================
clFriendsCB_slot_6_r60fbe0

Slot 6 of the clFriendsCB vtable at VA 0x11154c64.
Calls the function pointer at offset 0x20, if one is set.
================
*/
void __fastcall clFriendsCB_slot_6_r60fbe0(struct clFriendsCB *self, int unused, unsigned int arg1)
{
    if (self->unk_20)
        self->unk_20(arg1);
}

/*
================
clFriendsCB_slot_7_r60fbf0

Slot 7 of the clFriendsCB vtable at VA 0x11154c64.
Calls the function pointer at offset 0x24, if one is set.
================
*/
void __fastcall clFriendsCB_slot_7_r60fbf0(struct clFriendsCB *self, int unused,
                                           unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    if (self->unk_24)
        self->unk_24(arg1, arg2, arg3);
}

/*
================
clFriendsCB_slot_9_r60fc20

Slot 9 of the clFriendsCB vtable at VA 0x11154c64.
Calls the function pointer at offset 0x2c, if one is set.
================
*/
void __fastcall clFriendsCB_slot_9_r60fc20(struct clFriendsCB *self, int unused,
                                           unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    if (self->unk_2c)
        self->unk_2c(arg1, arg2, arg3);
}

/*
================
clFriendsCB_slot_13_r60fc90

Slot 13 of the clFriendsCB vtable at VA 0x11154c64.
Calls the function pointer at offset 0x3c, if one is set.
================
*/
void __fastcall clFriendsCB_slot_13_r60fc90(struct clFriendsCB *self, int unused,
                                            unsigned int arg1, unsigned int arg2, unsigned int arg3,
                                            unsigned int arg4, unsigned int arg5, unsigned int arg6)
{
    if (self->unk_3c)
        self->unk_3c(arg1, arg2, arg3, arg4, arg5, arg6);
}

/*
================
clLoginCB_slot_4_r60ff10

Slot 4 of the clLoginCB vtable at VA 0x11154cc4.
Calls the function pointer at offset 0x18, if one is set.
================
*/
void __fastcall clLoginCB_slot_4_r60ff10(struct clLoginCB *self, int unused,
                                         unsigned int arg1, unsigned int arg2)
{
    if (self->unk_18)
        self->unk_18(arg1, arg2);
}

/*
================
clLoginCB_slot_5_r60ff20

Slot 5 of the clLoginCB vtable at VA 0x11154cc4.
Calls the function pointer at offset 0x1c, if one is set.
================
*/
void __fastcall clLoginCB_slot_5_r60ff20(struct clLoginCB *self)
{
    if (self->unk_1c)
        self->unk_1c();
}

/*
================
clPersistentCB_slot_1_r61dba0

Slot 1 of the clPersistentCB vtable at VA 0x11154e10.
Calls the function pointer at offset 0xc, if one is set.
================
*/
void __fastcall clPersistentCB_slot_1_r61dba0(struct clPersistentCB *self)
{
    if (self->unk_0c)
        self->unk_0c();
}

/*
================
clLobbyCB_slot_1_r61dd90

Slot 1 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0xc, if one is set.
================
*/
void __fastcall clLobbyCB_slot_1_r61dd90(struct clLobbyCB *self, int unused, unsigned int arg1)
{
    if (self->unk_0c)
        self->unk_0c(arg1);
}

/*
================
clLobbyCB_slot_2_r61dda0

Slot 2 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0x10, if one is set.
================
*/
void __fastcall clLobbyCB_slot_2_r61dda0(struct clLobbyCB *self)
{
    if (self->unk_10)
        self->unk_10();
}

/*
================
clLobbyCB_slot_13_r61def0

Slot 13 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0x38, if one is set.
================
*/
void __fastcall clLobbyCB_slot_13_r61def0(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    if (self->unk_38)
        self->unk_38(arg1, arg2, arg3);
}

/*
================
clLobbyCB_slot_11_r61df00

Slot 11 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0x3c, if one is set.
================
*/
void __fastcall clLobbyCB_slot_11_r61df00(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2)
{
    if (self->unk_3c)
        self->unk_3c(arg1, arg2);
}

/*
================
clLobbyCB_slot_16_r61df30

Slot 16 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0x44, if one is set.
================
*/
void __fastcall clLobbyCB_slot_16_r61df30(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2, unsigned int arg3,
                                          unsigned int arg4, unsigned int arg5)
{
    if (self->unk_44)
        self->unk_44(arg1, arg2, arg3, arg4, arg5);
}

/*
================
clLobbyCB_slot_18_r61dfa0

Slot 18 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0x54, if one is set.
================
*/
void __fastcall clLobbyCB_slot_18_r61dfa0(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    if (self->unk_54)
        self->unk_54(arg1, arg2, arg3);
}

/*
================
clLobbyCB_slot_23_r61e010

Slot 23 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0x64, if one is set.
================
*/
void __fastcall clLobbyCB_slot_23_r61e010(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    if (self->unk_64)
        self->unk_64(arg1, arg2, arg3);
}

/*
================
clLobbyCB_slot_24_r61e020

Slot 24 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0x68, if one is set.
================
*/
void __fastcall clLobbyCB_slot_24_r61e020(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    if (self->unk_68)
        self->unk_68(arg1, arg2, arg3);
}

/*
================
clLobbyCB_slot_35_r61e170

Slot 35 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0x94, if one is set.
================
*/
void __fastcall clLobbyCB_slot_35_r61e170(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    if (self->unk_94)
        self->unk_94(arg1, arg2, arg3);
}

/*
================
clLobbyCB_slot_36_r61e180

Slot 36 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0x98, if one is set.
================
*/
void __fastcall clLobbyCB_slot_36_r61e180(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    if (self->unk_98)
        self->unk_98(arg1, arg2, arg3);
}

/*
================
clLobbyCB_slot_37_r61e190

Slot 37 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0x9c, if one is set.
================
*/
void __fastcall clLobbyCB_slot_37_r61e190(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2)
{
    if (self->unk_9c)
        self->unk_9c(arg1, arg2);
}

/*
================
clLobbyCB_slot_38_r61e1a0

Slot 38 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0xa0, if one is set.
================
*/
void __fastcall clLobbyCB_slot_38_r61e1a0(struct clLobbyCB *self, int unused, unsigned int arg1)
{
    if (self->unk_a0)
        self->unk_a0(arg1);
}

/*
================
clLobbyCB_slot_40_r61e1d0

Slot 40 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0xa8, if one is set.
================
*/
void __fastcall clLobbyCB_slot_40_r61e1d0(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    if (self->unk_a8)
        self->unk_a8(arg1, arg2, arg3);
}

/*
================
clLobbyCB_slot_41_r61e1e0

Slot 41 of the clLobbyCB vtable at VA 0x11154e44.
Calls the function pointer at offset 0xac, if one is set.
================
*/
void __fastcall clLobbyCB_slot_41_r61e1e0(struct clLobbyCB *self, int unused,
                                          unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    if (self->unk_ac)
        self->unk_ac(arg1, arg2, arg3);
}
