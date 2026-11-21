#include "sound_list.h"
#include "sound_memory.h"

static __forceinline stCallBackRequest pop_action(SndCallBackList *q)
{
    SndCallBackNode *item = q->first;
    stCallBackRequest saved = item->action;
    q->first = item->next;
    if (q->first)
        q->first->previous = 0;
    else
        q->last = 0;
    SND_fn_vFreeSnd(item);
    --q->count;
    return saved;
}
static __forceinline void add_action(SndCallBackList *q, stCallBackRequest action)
{
    SndCallBackNode *last = q->last;
    SndCallBackNode *item = SND_fn_pvMallocSnd(sizeof(SndCallBackNode));
    if (item) {
        item->next = 0;
        item->previous = last;
        ++q->count;
    }
    item->action = action;
    if (q->last)
        q->last->next = item;
    else
        q->first = item;
    q->last = item;
}
static __forceinline void drop_action(SndCallBackList *q, SndCallBackNode *item)
{
    if (item == q->first)
        q->first = item->next;
    else
        item->previous->next = item->next;
    if (item == q->last)
        q->last = item->previous;
    else
        item->next->previous = item->previous;
    SND_fn_vFreeSnd(item);
    --q->count;
}
#pragma code_seg(".text$V759460")
stCallBackRequest *__fastcall pop_mixer_action(SndCallBackList *q, int unused, stCallBackRequest *out)
{
    *out = pop_action(q);
    return out;
}
#pragma code_seg(".text$V7594a0")
void __fastcall insert_mixer_action(SndCallBackList *q, int unused, stCallBackRequest value)
{
    add_action(q, value);
}
#pragma code_seg(".text$V7594f0")
void __fastcall remove_mixer_action(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q,item);
}
#pragma code_seg(".text$V759530")
void __fastcall discard_mixer_actions(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}
#pragma code_seg(".text$V759570")
void __cdecl queue_mixer_callback(SndCallBack callback, void *context)
{
    stCallBackRequest action;
    action.invoke = callback;
    action.context = context;
    add_action(&gs_CallBackRequestList, action);
}
#pragma code_seg(".text$V7595d0")
void __cdecl run_mixer_callbacks(void)
{
    while (gs_CallBackRequestList.count) {
        stCallBackRequest a = pop_action(&gs_CallBackRequestList);
        a.invoke(a.context);
    }
}

#pragma code_seg()

/* Additional stock list instantiations. The node operations copy or discard
   the payload without interpreting it. */

void __fastcall list_remove_node_r467f80(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q, item);
}

void __fastcall list_clear_nodes_r467ff0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_remove_node_r4690e0(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q, item);
}

void __fastcall list_remove_node_r469240(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q, item);
}

void __fastcall list_clear_nodes_r46a990(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

stCallBackRequest * __fastcall list_pop_pair_r46d0d0(SndCallBackList *q, int unused, stCallBackRequest *out)
{
    *out = pop_action(q);
    return out;
}

void __fastcall list_clear_nodes_r46e780(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_append_pair_r46e800(SndCallBackList *q, int unused, stCallBackRequest value)
{
    add_action(q, value);
}

void __fastcall list_append_pair_r46e910(SndCallBackList *q, int unused, stCallBackRequest value)
{
    add_action(q, value);
}

void __fastcall list_remove_node_r46e960(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q, item);
}

void __fastcall list_clear_nodes_r46ea40(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_remove_node_r46eb00(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q, item);
}

stCallBackRequest * __fastcall list_pop_pair_r46ebf0(SndCallBackList *q, int unused, stCallBackRequest *out)
{
    *out = pop_action(q);
    return out;
}

void __fastcall list_clear_nodes_r46ec70(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r46ecb0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r46ecf0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r46feb0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r46fef0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r46ff30(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r46ffb0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r46fff0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r4768f0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r477700(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r47ba40(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r47ba80(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r47bac0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r74c0a0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_remove_node_r74c0e0(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q, item);
}

void __fastcall list_remove_node_r74c1e0(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q, item);
}

void __fastcall list_clear_nodes_r74c250(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r74dea0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r74df70(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

stCallBackRequest * __fastcall list_pop_pair_r74e020(SndCallBackList *q, int unused, stCallBackRequest *out)
{
    *out = pop_action(q);
    return out;
}

void __fastcall list_clear_nodes_r74e0b0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

stCallBackRequest * __fastcall list_pop_pair_r74e130(SndCallBackList *q, int unused, stCallBackRequest *out)
{
    *out = pop_action(q);
    return out;
}

void __fastcall list_clear_nodes_r74e1c0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r753420(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_remove_node_r761430(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q, item);
}

void __fastcall list_clear_nodes_r7614a0(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_remove_node_r7666e0(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q, item);
}

void __fastcall list_remove_node_r7667e0(SndCallBackList *q, int unused, SndCallBackNode *item)
{
    drop_action(q, item);
}

void __fastcall list_clear_nodes_r766820(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

stCallBackRequest * __fastcall list_pop_pair_r766860(SndCallBackList *q, int unused, stCallBackRequest *out)
{
    *out = pop_action(q);
    return out;
}

void __fastcall list_clear_nodes_r766f00(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r767530(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r76d510(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}

void __fastcall list_clear_nodes_r76d550(SndCallBackList *q)
{
    while (q->count)
        pop_action(q);
}
