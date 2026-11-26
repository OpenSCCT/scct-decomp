#include "campaign_allocation_kind.h"

struct VectorInitializationCount { unsigned value; };
struct VectorInitializationStorage { unsigned reserved; unsigned char *first, *end, *limit; };
extern void *__cdecl allocate_buffer(unsigned, unsigned);

#define INITIALIZE_VECTOR(Stride) \
    struct Element##Stride { unsigned char bytes[Stride]; }; \
    unsigned char __fastcall initialize_##Stride(struct VectorInitializationStorage *v, struct VectorInitializationCount count) \
    { \
        v->first = 0; \
        v->end = 0; \
        v->limit = 0; \
        if (!count.value) return 0; \
        if (count.value <= ~0u / Stride) { \
            unsigned bytes = count.value * Stride; \
            unsigned char *first = allocate_buffer(bytes, allocation_kind); \
            v->limit = (unsigned char *)((struct Element##Stride *)first + count.value); \
            v->first = first; \
            v->end = first; \
        } \
        return 1; \
    }

INITIALIZE_VECTOR(4)
INITIALIZE_VECTOR(8)
INITIALIZE_VECTOR(16)
INITIALIZE_VECTOR(32)
