#include "campaign_color_node.h"
struct ColorTree { struct ColorNode *head; unsigned count; };
struct ColorTreePosition { struct ColorNode *node; };
struct ColorTreeOutput { struct ColorTreePosition *out; };
#define TREE_EDGE(Name, Value) \
    struct ColorTreePosition *__fastcall Name(struct ColorTree *tree, struct ColorTreeOutput result) \
    { \
        result.out->node = Value; \
        return result.out; \
    }
TREE_EDGE(tree_begin_5ed1a0, tree->head->left)
TREE_EDGE(tree_begin_5ed1d0, tree->head->left)
TREE_EDGE(tree_begin_5ed200, tree->head->left)
TREE_EDGE(tree_begin_5ed230, tree->head->left)
TREE_EDGE(tree_begin_5f7bd0, tree->head->left)
TREE_EDGE(tree_begin_5f7c10, tree->head->left)
TREE_EDGE(tree_begin_5f7c70, tree->head->left)
TREE_EDGE(tree_begin_5f80c0, tree->head->left)
TREE_EDGE(tree_begin_5f8db0, tree->head->left)
TREE_EDGE(tree_begin_5f93f0, tree->head->left)
TREE_EDGE(tree_begin_6041e0, tree->head->left)
TREE_EDGE(tree_begin_6042f0, tree->head->left)
TREE_EDGE(tree_begin_618fb0, tree->head->left)
TREE_EDGE(tree_begin_620f70, tree->head->left)
TREE_EDGE(tree_begin_626850, tree->head->left)
TREE_EDGE(tree_begin_628700, tree->head->left)
TREE_EDGE(tree_begin_62eae0, tree->head->left)
TREE_EDGE(tree_begin_62f070, tree->head->left)
TREE_EDGE(tree_begin_722b70, tree->head->left)
