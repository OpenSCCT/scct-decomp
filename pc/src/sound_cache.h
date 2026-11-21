#ifndef SOUND_CACHE_H
#define SOUND_CACHE_H

#include "sound_list.h"
#include "sound_memory.h"

typedef struct SoundCacheItem
{
    unsigned fields00[2];
    unsigned bytes;
    int priority;
    unsigned key;
} SoundCacheItem;
typedef struct
{
    int enabled;
    unsigned capacity, used;
    SndPtrList entries;
} SoundCache;

/* MSVC x86 passes aggregate arguments on the stack and the fastcall receiver in ECX. */
typedef struct
{
    SoundCacheItem *ptr;
} SoundCacheItemArg;

static __forceinline SndPtrListNode *make_node(SndPtrList *list, SndPtrListNode *previous, SndPtrListNode *next)
{
    SndPtrListNode *node = SND_fn_pvMallocSnd(sizeof(SndPtrListNode));
    if (node)
    {
        node->next = next;
        node->previous = previous;
        ++list->count;
    }
    return node;
}
static __forceinline void free_node(SndPtrList *list, SndPtrListNode *node)
{
    if (node)
    {
        SND_fn_vFreeSnd(node);
        --list->count;
    }
}
static __forceinline SndPtrListNode *add_first(SndPtrList *list, SoundCacheItem *item)
{
    SndPtrListNode *node = make_node(list, 0, list->first);
    node->item = item;
    if (list->first)
        list->first->previous = node;
    else
        list->last = node;
    return list->first = node;
}
static __forceinline SndPtrListNode *add_last(SndPtrList *list, SoundCacheItem *item)
{
    SndPtrListNode *node = make_node(list, list->last, 0);
    node->item = item;
    if (list->last)
        list->last->next = node;
    else
        list->first = node;
    return list->last = node;
}
static __forceinline SoundCacheItem *pop_first(SndPtrList *list)
{
    SndPtrListNode *node = list->first;
    SoundCacheItem *item = node->item;
    list->first = node->next;
    if (list->first)
        list->first->previous = 0;
    else
        list->last = 0;
    free_node(list, node);
    return item;
}
static __forceinline SoundCacheItem *pop_last(SndPtrList *list)
{
    SndPtrListNode *node = list->last;
    SoundCacheItem *item = node->item;
    list->last = node->previous;
    if (list->last)
        list->last->next = 0;
    else
        list->first = 0;
    free_node(list, node);
    return item;
}
static __forceinline SndPtrListNode *find_item(SndPtrList *list, SoundCacheItem *item, SndPtrListNode *after)
{
    SndPtrListNode *node;
    if (!after)
        node = list->first;
    else
        node = after->next;
    while (node)
    {
        if (node->item == item)
            return node;
        node = node->next;
    }
    return 0;
}
static __forceinline SoundCacheItem *next_item(SndPtrListNode **cursor)
{
    SndPtrListNode *node = *cursor;
    *cursor = node->next;
    return node->item;
}

typedef struct
{
    unsigned value;
} SndWordArg;
__declspec(noinline) unsigned __fastcall cache_item_bytes(SoundCacheItem *item);
__declspec(noinline) int __fastcall cache_item_priority(SoundCacheItem *item);
__declspec(noinline) int __fastcall cache_item_matches(SoundCacheItem *item, SndWordArg key);
__declspec(noinline) SndPtrListNode *__fastcall append_cache_item(SndPtrList *list, SoundCacheItemArg item);
__declspec(noinline) void __fastcall unlink_cache_node(SndPtrList *list, SndPtrListNodeArg ref);
__declspec(noinline) SndPtrListNode *__fastcall insert_before_cache_node(SndPtrList *list, SndPtrListNodeArg at,
                                                               SoundCacheItemArg item);

#endif
