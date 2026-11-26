#include "campaign_allocation_service.h"
#include "campaign_three_link_node.h"

struct Tree;
/* FAKEMATCH: this wrapper puts the raw subtree node pointer on the member call's stack. */
struct TreeEraseChild { struct ThreeLinkNode *ptr; };


#define ERASE_NODES(Entry, SentinelOffset, Category) \
    void __fastcall Entry(struct Tree *tree, struct TreeEraseChild child) \
    { \
        struct ThreeLinkNode *node = child.ptr; \
        while (!*((const unsigned char *)child.ptr + SentinelOffset)) { \
            struct TreeEraseChild right; \
            right.ptr = node->right; \
            Entry(tree,right); \
            node = node->left; \
            release_block(get_context(), (unsigned char *)child.ptr, Category); \
            child.ptr = node; \
        } \
    }

ERASE_NODES(erase_48cee0, 25, 7)
ERASE_NODES(erase_4967c0, 21, 7)
ERASE_NODES(erase_499800, 21, 7)
ERASE_NODES(erase_49f430, 21, 7)
ERASE_NODES(erase_4a5910, 21, 7)
ERASE_NODES(erase_4abaf0, 33, 7)
ERASE_NODES(erase_4af480, 21, 7)
ERASE_NODES(erase_4bfe00, 21, 7)
ERASE_NODES(erase_4c5450, 21, 7)
ERASE_NODES(erase_4c95d0, 21, 7)
ERASE_NODES(erase_4c9f40, 21, 7)
ERASE_NODES(erase_4d4400, 49, 7)
ERASE_NODES(erase_4d7460, 21, 7)
ERASE_NODES(erase_4ec5c0, 21, 7)
ERASE_NODES(erase_4edc90, 21, 7)
