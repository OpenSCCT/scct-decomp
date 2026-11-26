struct CountedNodePool { unsigned reserved[2], count; };
#include "campaign_list_link.h"

extern void *__stdcall allocate_node(unsigned bytes);
extern void __stdcall release_node(void *node);

#define ALLOCATE_NODE(Size) \
    struct ListLink *__fastcall allocate_##Size(struct CountedNodePool *pool, unsigned unused_edx, \
                                            struct ListLink *previous, struct ListLink *next) \
    { \
        struct ListLink *node = allocate_node(Size); \
        if (node) { \
            node->next = next; \
            node->previous = previous; \
            ++pool->count; \
        } \
        return node; \
    }

void __fastcall release_counted_node(struct CountedNodePool *pool, unsigned unused_edx, struct ListLink *node)
{
    if (node) {
        release_node(node);
        --pool->count;
    }
}

ALLOCATE_NODE(12)
ALLOCATE_NODE(16)
ALLOCATE_NODE(40)
