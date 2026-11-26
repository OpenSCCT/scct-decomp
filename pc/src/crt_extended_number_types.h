#ifndef CRT_EXTENDED_NUMBER_TYPES_H
#define CRT_EXTENDED_NUMBER_TYPES_H

typedef unsigned ExtendedNumberWord;
typedef union {
    char bytes[12];
    ExtendedNumberWord limb[3];
    unsigned short half[6];
} Extended96;

extern Extended96 _pow10pos[], _pow10neg[];

#endif
