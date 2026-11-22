/* A list link: the next and previous neighbours, eight bytes. */
struct ListLink {
    struct ListLink *next, *previous;
};

/* A list node with one unsigned word after its links. */
struct ListLinkWithValue {
    struct ListLink link;
    unsigned value;
};
