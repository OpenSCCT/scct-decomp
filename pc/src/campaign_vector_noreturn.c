#include "campaign_allocation_kind.h"

struct Vector16Count { unsigned value; };
struct Element16 { unsigned char bytes[16]; };
struct CheckedVector16 {
    unsigned reserved;
    struct Element16 *first, *end, *limit;
};

__declspec(noreturn) void __fastcall vector_length_error(struct CheckedVector16 *);
extern void *__cdecl allocate_buffer(unsigned bytes, unsigned kind);

unsigned char __fastcall initialize_16(struct CheckedVector16 *v, struct Vector16Count count)
{
    struct Element16 *first;

    v->first = 0;
    v->end = 0;
    v->limit = 0;
    if (!count.value)
        return 0;
    if (count.value > ~0u / sizeof(*first))
        vector_length_error(v);

    first = allocate_buffer(count.value * sizeof(*first), allocation_kind);
    v->limit = first + count.value;
    v->first = first;
    v->end = first;
    return 1;
}
