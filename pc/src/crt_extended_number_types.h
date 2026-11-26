#ifndef CRT_EXTENDED_NUMBER_TYPES_H
#define CRT_EXTENDED_NUMBER_TYPES_H

typedef unsigned ExtendedNumberWord;
/* The significand spans ten bytes, followed by the sign and exponent. */
#pragma pack(push, 2)
struct ExtendedNumberParts {
    unsigned short extra_fraction;
    ExtendedNumberWord low_fraction;
    ExtendedNumberWord high_fraction;
    unsigned short sign_exponent;
};
#pragma pack(pop)

typedef union {
    struct ExtendedNumberParts parts;
    ExtendedNumberWord limb[3];
    unsigned short half[6];
} Extended96;

extern Extended96 _pow10pos[], _pow10neg[];

#endif
