/* campaign_band3_field_accessors.c -- small field reads and writes of unidentified objects.
   Every struct and function name here is invented; the offsets are the binary's. Each function
   gets its own struct because nothing yet shows two of them belong to the same class. */

struct Band3DwordAt08
{
    unsigned char unk_00[8];        /* not read by any function in this unit */
    unsigned int  unk_08;
};

struct Band3FlagAt54
{
    unsigned char unk_00[0x54];     /* not read by any function in this unit */
    unsigned char unk_54;
};

struct Band3Inner28
{
    unsigned char unk_00[0x28];     /* not read by any function in this unit */
    unsigned int  unk_28;
};

struct Band3Outer28
{
    struct Band3Inner28 *unk_00;
};

struct Band3Inner08
{
    unsigned char unk_00[8];        /* not read by any function in this unit */
    unsigned int  unk_08;
};

struct Band3Outer08
{
    unsigned char        unk_00[8]; /* not read by any function in this unit */
    struct Band3Inner08 *unk_08;
};

struct Band3FloatPair
{
    unsigned char unk_00[0xc];      /* not read by any function in this unit */
    float         unk_0c;
    unsigned char unk_10[0xc];      /* not read by any function in this unit */
    float         unk_1c;
};

struct Band3DwordAt10
{
    unsigned char unk_00[0x10];     /* not read by any function in this unit */
    unsigned int  unk_10;
};

struct Band3DwordAt0c
{
    unsigned char unk_00[0xc];      /* not read by any function in this unit */
    unsigned int  unk_0c;
    unsigned int  unk_10;
};

struct Band3PairAt20
{
    unsigned char unk_00[0x20];     /* not read by any function in this unit */
    unsigned int  unk_20;
    unsigned char unk_24[0x8];      /* not read by any function in this unit */
    unsigned int  unk_2c;
    unsigned int  unk_30;
};

struct Band3ByteAt08
{
    unsigned char unk_00[8];        /* not read by any function in this unit */
    unsigned char unk_08;
};

struct Band3ByteAt0c
{
    unsigned char unk_00[0xc];      /* not read by any function in this unit */
    unsigned char unk_0c;
};

struct Band3Head
{
    unsigned int unk_00;
};

/*
================
get_dword_08_r7917c0

Returns the word at offset 8.
================
*/
unsigned int __fastcall get_dword_08_r7917c0(struct Band3DwordAt08 *self)
{
    return self->unk_08;
}

/*
================
clear_byte_54_r720d70

Clears the byte at offset 0x54.
================
*/
void __fastcall clear_byte_54_r720d70(struct Band3FlagAt54 *self)
{
    self->unk_54 = 0;
}

/*
================
get_inner_dword_28_r767210

Returns the word at offset 0x28 of the object the first member points to.
================
*/
unsigned int __fastcall get_inner_dword_28_r767210(struct Band3Outer28 *self)
{
    return self->unk_00->unk_28;
}

/*
================
get_inner_dword_08_r767460

Returns the word at offset 8 of the object the member at offset 8 points to.
================
*/
unsigned int __fastcall get_inner_dword_08_r767460(struct Band3Outer08 *self)
{
    return self->unk_08->unk_08;
}

/*
================
get_float_0c_r7131b0
================
*/
float get_float_0c_r7131b0(struct Band3FloatPair *object)
{
    return object->unk_0c;
}

/*
================
get_float_1c_r7131c0
================
*/
float get_float_1c_r7131c0(struct Band3FloatPair *object)
{
    return object->unk_1c;
}

/*
================
get_dword_10_r74fbb0
================
*/
unsigned int get_dword_10_r74fbb0(struct Band3DwordAt10 *object)
{
    return object->unk_10;
}

/*
================
get_dword_0c_r751a50
================
*/
unsigned int get_dword_0c_r751a50(struct Band3DwordAt0c *object)
{
    return object->unk_0c;
}

/*
================
get_dword_0c_r751ab0
================
*/
unsigned int get_dword_0c_r751ab0(struct Band3DwordAt0c *object)
{
    return object->unk_0c;
}

/*
================
get_dword_10_r751ac0
================
*/
unsigned int get_dword_10_r751ac0(struct Band3DwordAt0c *object)
{
    return object->unk_10;
}

/*
================
clear_30_and_20_r76cdf0
================
*/
void __fastcall clear_30_and_20_r76cdf0(struct Band3PairAt20 *self)
{
    self->unk_30 = 0;
    self->unk_20 = 0;
}

/*
================
clear_2c_and_20_r7712d0
================
*/
void __fastcall clear_2c_and_20_r7712d0(struct Band3PairAt20 *self)
{
    self->unk_2c = 0;
    self->unk_20 = 0;
}

/*
================
set_byte_08_r580c60
================
*/
void __fastcall set_byte_08_r580c60(struct Band3ByteAt08 *self, int unused, unsigned char value)
{
    self->unk_08 = value;
}

/*
================
set_byte_0c_r6ede10
================
*/
void __fastcall set_byte_0c_r6ede10(struct Band3ByteAt0c *self, int unused, unsigned char value)
{
    self->unk_0c = value;
}

/*
================
reset_head_r580dd0

Clears the first word and returns the object.
================
*/
struct Band3Head *__fastcall reset_head_r580dd0(struct Band3Head *self)
{
    self->unk_00 = 0;
    return self;
}

/*
================
reset_head_r77c730

Clears the first word and returns the object.
================
*/
struct Band3Head *__fastcall reset_head_r77c730(struct Band3Head *self)
{
    self->unk_00 = 0;
    return self;
}
