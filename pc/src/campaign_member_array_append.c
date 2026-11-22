#include "campaign_array_storage.h"
extern void __cdecl grow_array(struct Array *array, unsigned element_size);

#define APPEND_METHOD(Offset) \
    /* FAKEMATCH: the original's members before this array are not recovered; */ \
    /* prefix only pushes the Array to its offset. */ \
    struct Owner##Offset { unsigned char prefix[Offset]; struct Array array; }; \
    void __fastcall append_##Offset(struct Owner##Offset *owner, unsigned unused_edx, unsigned value) \
    { \
        struct Array *array = &owner->array; \
        if (array->count == (int)(array->capacity & 0x7fffffffU)) \
            grow_array(array, sizeof(value)); \
        ((unsigned *)array->buffer.bytes)[array->count++] = value; \
    }

APPEND_METHOD(8)
APPEND_METHOD(40)
APPEND_METHOD(52)
APPEND_METHOD(60)
APPEND_METHOD(72)
APPEND_METHOD(84)
APPEND_METHOD(96)
APPEND_METHOD(108)
APPEND_METHOD(112)
APPEND_METHOD(120)
APPEND_METHOD(124)
APPEND_METHOD(132)
APPEND_METHOD(136)
APPEND_METHOD(144)
APPEND_METHOD(148)
APPEND_METHOD(156)
APPEND_METHOD(168)
APPEND_METHOD(180)
APPEND_METHOD(224)
APPEND_METHOD(228)
APPEND_METHOD(236)
APPEND_METHOD(248)
APPEND_METHOD(260)
APPEND_METHOD(272)
