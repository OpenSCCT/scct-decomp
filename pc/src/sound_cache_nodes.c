#include "sound_cache.h"

#pragma code_seg(".text$V75cc70")
SndPtrListNode *__fastcall allocate_cache_node(SndPtrList *list, SndPtrListNodeArg previous, SndPtrListNodeArg next)
{
    return make_node(list, previous.ptr, next.ptr);
}

#pragma code_seg(".text$V75ccf0")
void __fastcall free_cache_node(SndPtrList *list, SndPtrListNodeArg ref)
{
    free_node(list, ref.ptr);
}

#pragma code_seg(".text$V75ccb0")
SndPtrListNode *__fastcall prepend_cache_item(SndPtrList *list, SoundCacheItemArg item)
{
    return add_first(list, item.ptr);
}

#pragma code_seg(".text$V75cd70")
__declspec(noinline) SndPtrListNode *__fastcall append_cache_item(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

#pragma code_seg(".text$V75cd30")
SoundCacheItem *__fastcall pop_last_cache_item(SndPtrList *list)
{
    return pop_last(list);
}

#pragma code_seg(".text$V75cea0")
SoundCacheItem *__fastcall pop_first_cache_item(SndPtrList *list)
{
    return pop_first(list);
}

#pragma code_seg(".text$V75cdb0")
__declspec(noinline) void __fastcall unlink_cache_node(SndPtrList *list, SndPtrListNodeArg ref)
{
    SndPtrListNode *node = ref.ptr;
    if (node == list->first)
        list->first = node->next;
    else
        node->previous->next = node->next;
    if (node == list->last)
        list->last = node->previous;
    else
        node->next->previous = node->previous;
    free_node(list, node);
}

#pragma code_seg(".text$V75cdf0")
static __forceinline SndPtrListNode *insert_before(SndPtrList *list, SndPtrListNodeArg at, SoundCacheItemArg item)
{
    SndPtrListNode *before = at.ptr, *node;
    if (!before)
        return add_first(list, item.ptr);
    node = make_node(list, before->previous, before);
    node->item = item.ptr;
    if (before->previous)
        before->previous->next = node;
    else
        list->first = node;
    before->previous = node;
    return node;
}

__declspec(noinline) SndPtrListNode *__fastcall insert_before_cache_node(SndPtrList *list, SndPtrListNodeArg at, SoundCacheItemArg item)
{
    return insert_before(list, at, item);
}

#pragma code_seg(".text$V75ce70")
SndPtrListNode *__fastcall find_cache_item(SndPtrList *list, SoundCacheItemArg item, SndPtrListNodeArg after)
{
    return find_item(list, item.ptr, after.ptr);
}

#pragma code_seg(".text$V75cc60")
void **__fastcall next_cache_item_ref(SndPtrList *list, SndPtrListCursorArg cursor)
{
    SndPtrListNode *node = *cursor.ptr;
    *cursor.ptr = node->next;
    return &node->item;
}

#pragma code_seg()


SoundCacheItem * __fastcall list_pop_first_pointer_r467eb0(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_last_pointer_r467ef0(SndPtrList *list)
{
    return pop_last(list);
}

SndPtrListNode * __fastcall list_append_pointer_r469150(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SndPtrListNode * __fastcall list_append_pointer_r469200(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r46a8c0(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_prepend_pointer_r46cf60(SndPtrList *list, SoundCacheItemArg item)
{
    return add_first(list, item.ptr);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r46e680(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_last_pointer_r46e6c0(SndPtrList *list)
{
    return pop_last(list);
}

SndPtrListNode * __fastcall list_prepend_pointer_r46e700(SndPtrList *list, SoundCacheItemArg item)
{
    return add_first(list, item.ptr);
}

SndPtrListNode * __fastcall list_append_pointer_r46e740(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SndPtrListNode * __fastcall list_append_pointer_r46e7c0(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SndPtrListNode * __fastcall list_append_pointer_r46e8a0(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r46ea80(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_append_pointer_r46eac0(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r46eb70(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r46ebb0(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r46ec30(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r46ed30(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r46ed70(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r476870(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_append_pointer_r4768b0(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r476930(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_prepend_pointer_r479f40(SndPtrList *list, SoundCacheItemArg item)
{
    return add_first(list, item.ptr);
}

SndPtrListNode * __fastcall list_append_pointer_r479f80(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SndPtrListNode * __fastcall list_prepend_pointer_r47a000(SndPtrList *list, SoundCacheItemArg item)
{
    return add_first(list, item.ptr);
}

SndPtrListNode * __fastcall list_append_pointer_r47a040(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SndPtrListNode * __fastcall list_prepend_pointer_r47b310(SndPtrList *list, SoundCacheItemArg item)
{
    return add_first(list, item.ptr);
}

SndPtrListNode * __fastcall list_prepend_pointer_r47b370(SndPtrList *list, SoundCacheItemArg item)
{
    return add_first(list, item.ptr);
}

SndPtrListNode * __fastcall list_prepend_pointer_r47b3d0(SndPtrList *list, SoundCacheItemArg item)
{
    return add_first(list, item.ptr);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r47b740(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_append_pointer_r47b780(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SndPtrListNode * __fastcall list_insert_before_r47b7c0(SndPtrList *list, SndPtrListNodeArg at, SoundCacheItemArg item)
{
    return insert_before(list, at, item);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r47b840(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_append_pointer_r47b880(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SndPtrListNode * __fastcall list_insert_before_r47b8c0(SndPtrList *list, SndPtrListNodeArg at, SoundCacheItemArg item)
{
    return insert_before(list, at, item);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r47b940(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_append_pointer_r47b980(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SndPtrListNode * __fastcall list_insert_before_r47b9c0(SndPtrList *list, SndPtrListNodeArg at, SoundCacheItemArg item)
{
    return insert_before(list, at, item);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r74bfd0(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r74c150(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r74de10(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r74dee0(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r7533a0(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_append_pointer_r7533e0(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r761120(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_prepend_pointer_r7613f0(SndPtrList *list, SoundCacheItemArg item)
{
    return add_first(list, item.ptr);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r766470(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_append_pointer_r7666a0(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r767480(SndPtrList *list)
{
    return pop_first(list);
}

SndPtrListNode * __fastcall list_append_pointer_r7674c0(SndPtrList *list, SoundCacheItemArg item)
{
    return add_last(list, item.ptr);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r76d3b0(SndPtrList *list)
{
    return pop_first(list);
}

SoundCacheItem * __fastcall list_pop_first_pointer_r76d480(SndPtrList *list)
{
    return pop_first(list);
}
