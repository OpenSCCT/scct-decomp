#include "campaign_list_link.h"
struct List { unsigned reserved; struct ListLink *head; unsigned count; };
struct Cursor { struct ListLink *position; };

extern struct ListLink *__fastcall construct_node(struct List *, unsigned unused_edx,
                                               struct ListLink *next, struct ListLink *previous,
                                               const void *value);
extern void __fastcall grow_list(struct List *, float increment_bits);
extern void *__cdecl allocation_context(void);
extern void __cdecl release_node(void *context, struct ListLink *node, unsigned kind);

/* FAKEMATCH: the original passes the integer increment of one as a stack word; the
   float literal in the body is that bit pattern (1.40129846e-45f is 0x00000001). */
void __fastcall append_node(struct List *list, unsigned unused_edx, const void *value)
{
    struct ListLink *head = list->head;
    struct ListLink *node = construct_node(list, unused_edx, head, head->previous, value);
    /* The low bit represents a one-element increment in the original stack argument. */
    grow_list(list, 1.40129846e-45f);
    head->previous = node;
    node->previous->next = node;
}

/* FAKEMATCH: the original reads the successor before the unlinking stores; the
   volatile cast only forces that load order, and the original's statements are not recovered. */
struct Cursor *__fastcall erase_node(struct List *list, unsigned unused_edx,
                                     struct Cursor *result, struct ListLink *node)
{
    /* Save the successor independently of the link reads used for unlinking. */
    struct ListLink *next = ((const volatile struct ListLink *)node)->next;
    if (node != list->head) {
        node->previous->next = node->next;
        node->next->previous = node->previous;
        release_node(allocation_context(), node, 7);
        --list->count;
    }
    result->position = next;
    return result;
}

/* FAKEMATCH: a one-member struct passed by value as a dummy argument; the original's tag
   value is not recovered, so this struct only steers the stack argument. */
struct Category { unsigned char : 8; };
struct Vector { unsigned reserved; void *first, *end, *limit; };
extern void __cdecl destroy_range(void *, void *, struct Vector *, struct Category);
extern void __cdecl release_buffer(void *);

void __fastcall destroy_vector(struct Vector *vector)
{
    if (vector->first) {
        struct Category tag;
        destroy_range(vector->first, vector->end, vector, tag);
        release_buffer(vector->first);
    }
    vector->first = 0;
    vector->end = 0;
    vector->limit = 0;
}
