struct Tree;
struct Pair { void *first, *second; };
struct PairCleanupNode {
    struct PairCleanupNode *left, *parent, *right;
    struct Pair value;
    unsigned char colour;
    unsigned char sentinel;
};
struct PairCleanupChild { struct PairCleanupNode *ptr; };
extern void __fastcall destroy_field(void *);
extern void *__cdecl prepare_release(struct PairCleanupNode *, unsigned);
extern void __cdecl release_prepared(void *);
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
        release_prepared(prepare_release(child.ptr, 7));
        child.ptr = node;
    }
}
