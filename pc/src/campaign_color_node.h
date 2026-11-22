/* A colour tree node: the colour, then the parent and both children. */
struct ColorNode {
    unsigned char color;
    struct ColorNode *parent, *left, *right;
};
