#ifndef CAMPAIGN_COLOR_TREE_H
#define CAMPAIGN_COLOR_TREE_H

#include "campaign_color_node.h"

struct ColorTree {
    struct ColorNode *head;
    unsigned count;
    unsigned char compare;
};

#endif
