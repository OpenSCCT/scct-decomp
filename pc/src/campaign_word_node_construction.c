#include "campaign_list_link.h"

struct ListLinkWithValue *__fastcall initialize_node(struct ListLinkWithValue *node, unsigned unused_edx,
                                        struct ListLink *next, struct ListLink *previous,
                                        const unsigned *value)
{
    node->link.next = next;
    node->link.previous = previous;
    node->value = *value;
    return node;
}
