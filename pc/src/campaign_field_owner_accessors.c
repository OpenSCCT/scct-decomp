/* campaign_field_owner_accessors.c -- fields that a FieldOwner reads from its sub-object at 0xc.
   The struct and function names are invented; the offsets are the binary's. */

struct FieldOwnerSub
{
    unsigned char unk_00[0x48];     /* not read by any function in this unit */
    unsigned char unk_48;
    unsigned char unk_49;
    unsigned char unk_4a;
    unsigned char unk_4b[9];        /* not read by any function in this unit */
    unsigned int  unk_54;
    unsigned int  unk_58;
};

struct FieldOwner
{
    unsigned char unk_00[0xc];      /* not read by any function in this unit */
    struct FieldOwnerSub *sub;
};

/*
================
field_owner_sub_get_dword_54

Returns the word at offset 0x54 of the owner's sub-object. guess: the field's meaning is unknown.
================
*/
unsigned int __fastcall field_owner_sub_get_dword_54(struct FieldOwner *self)
{
    return self->sub->unk_54;
}

/*
================
field_owner_sub_get_dword_58

Returns the word at offset 0x58 of the owner's sub-object. guess: the field's meaning is unknown.
================
*/
unsigned int __fastcall field_owner_sub_get_dword_58(struct FieldOwner *self)
{
    return self->sub->unk_58;
}

/*
================
field_owner_sub_get_byte_48

Returns the byte at offset 0x48 of the owner's sub-object. guess: the field's meaning is unknown.
================
*/
int __fastcall field_owner_sub_get_byte_48(struct FieldOwner *self)
{
    return self->sub->unk_48;
}

/*
================
field_owner_sub_get_byte_49

Returns the byte at offset 0x49 of the owner's sub-object. guess: the field's meaning is unknown.
================
*/
int __fastcall field_owner_sub_get_byte_49(struct FieldOwner *self)
{
    return self->sub->unk_49;
}

/*
================
field_owner_sub_get_byte_4a

Returns the byte at offset 0x4a of the owner's sub-object. guess: the field's meaning is unknown.
================
*/
int __fastcall field_owner_sub_get_byte_4a(struct FieldOwner *self)
{
    return self->sub->unk_4a;
}
