/* A tree node with no colour: the left and right children and the parent link, twelve bytes. */
struct ThreeLinkNode {
    struct ThreeLinkNode *left, *parent, *right;
};
