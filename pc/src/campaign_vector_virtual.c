struct Size { unsigned value; };
struct Element12 { unsigned char bytes[12]; };
struct Vector {
    unsigned reserved;
    struct Element12 *first, *end, *limit;
};

__declspec(noreturn) void __fastcall vector_length_error(struct Vector *);
struct Allocator;
struct Tag { const unsigned short *name; };
struct Methods { void *(__fastcall *allocate)(struct Allocator *, struct Size, struct Tag); };
struct Allocator { struct Methods *methods; };
#include "campaign_engine_allocator.h"
extern const unsigned short new_tag[];

unsigned char __fastcall initialize_12(struct Vector *v, struct Size count)
{
    struct Element12 *first;
    struct Tag tag;
    struct Size bytes;

    v->first = 0;
    v->end = 0;
    v->limit = 0;
    if (!count.value)
        return 0;
    if (count.value > ~0u / sizeof(*first))
        vector_length_error(v);

    bytes.value = count.value * sizeof(*first);
    tag.name = new_tag;
    first = ((struct Allocator *)engine_allocator)->methods->allocate((struct Allocator *)engine_allocator, bytes, tag);
    v->limit = first + count.value;
    v->first = first;
    v->end = first;
    return 1;
}
