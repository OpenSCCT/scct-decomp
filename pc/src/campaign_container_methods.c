#include "campaign_list_link.h"
struct List { unsigned reserved; struct ListLink *head; unsigned count; };
struct Cursor { struct ListLink *position; };

extern struct ListLink *__fastcall construct_node(struct List *, unsigned unused_edx,
                                               struct ListLink *next, struct ListLink *previous,
                                               const void *value);
extern void __fastcall grow_list(struct List *, float increment_bits);
extern void *__cdecl allocation_context(void);
extern void __cdecl release_node(void *context, struct ListLink *node, unsigned kind);

void __fastcall append_node(struct List *list, unsigned unused_edx, const void *value)
{
    struct ListLink *head = list->head;
    struct ListLink *node = construct_node(list, unused_edx, head, head->previous, value);
    /* The low bit represents a one-element increment in the original stack argument. */
    grow_list(list, 1.40129846e-45f);
    head->previous = node;
    node->previous->next = node;
}

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
