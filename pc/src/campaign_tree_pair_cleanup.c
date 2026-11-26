#include "campaign_allocation_service.h"
struct Tree;
struct Pair { void *first, *second; };
struct PairCleanupNode {
    struct PairCleanupNode *left, *parent, *right;
    struct Pair value;
    unsigned char colour;
    unsigned char sentinel;
};
/* FAKEMATCH: this wrapper puts the raw subtree node pointer on the member call's stack. */
struct PairCleanupChild { struct PairCleanupNode *ptr; };
extern void __fastcall destroy_field(void *);
void __fastcall erase_nodes(struct Tree *tree, struct PairCleanupChild child)
{
    struct PairCleanupNode *node = child.ptr;
    while (!child.ptr->sentinel) {
        struct PairCleanupChild right;
        right.ptr = node->right;
        erase_nodes(tree, right);
        node = node->left;
        {
            struct Pair *pair = &child.ptr->value;
            destroy_field(&pair->second);
            destroy_field(pair);
        }
        release_block(get_context(), (unsigned char *)child.ptr, 7);
        child.ptr = node;
    }
}
