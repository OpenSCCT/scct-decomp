#include "campaign_allocation_service.h"
#include "campaign_three_link_node.h"

struct Tree;
/* FAKEMATCH: this wrapper puts the raw subtree node pointer on the member call's stack. */
struct PayloadChild { struct ThreeLinkNode *ptr; };

extern void __fastcall destroy_47cf40(void *);
extern void __fastcall destroy_4acf90(void *);

#define ERASE_NODES(Entry, SentinelOffset, Category, Destroy) \
    void __fastcall Entry(struct Tree *tree, struct PayloadChild child) \
    { \
        struct ThreeLinkNode *node = child.ptr; \
        while (!*((const unsigned char *)child.ptr + SentinelOffset)) { \
            struct PayloadChild right; \
            right.ptr = node->right; \
            Entry(tree,right); \
            node = node->left; \
            Destroy((unsigned char *)child.ptr + 12); \
            release_block(get_context(), (unsigned char *)child.ptr, Category); \
            child.ptr = node; \
        } \
    }

ERASE_NODES(erase_4a36d0, 21, 7, destroy_47cf40)
ERASE_NODES(erase_4cf820, 149, 7, destroy_4acf90)
