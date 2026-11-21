/* sound_list.h -- C stand-ins for the sound library's C++ list template */
#ifndef SOUND_LIST_H
#define SOUND_LIST_H

/* The sibling build's linker map names the template sndCList<TYPE, ARG_TYPE> and its members
   AddHead, AddTail, RemoveHead, RemoveTail, RemoveAt, RemoveAll, InsertBefore and Find: the
   interface of MFC's CList. C has neither templates nor member functions, so each element
   type has its own node and list structures here, and each member is a __fastcall function
   that takes the list in ECX. The units that use these belong in C++; this is open work.
   The structure and member names below are invented. */

/* sndCList of pointers of any type. */
typedef struct SndPtrListNode {
    struct SndPtrListNode *next;
    struct SndPtrListNode *previous;
    void *item;
} SndPtrListNode;

typedef struct SndPtrList {
    SndPtrListNode *first;
    SndPtrListNode *last;
    unsigned long count;
} SndPtrList;

/* A member function takes its arguments on the stack. A __fastcall function passes an
   argument there only when it is an aggregate, so the stand-ins wrap each argument. */
typedef struct SndPtrListNodeArg {
    SndPtrListNode *ptr;
} SndPtrListNodeArg;

typedef struct SndPtrListCursorArg {
    SndPtrListNode **ptr;
} SndPtrListCursorArg;

/* A function to call back with its argument: the sibling build's stCallBackRequest_. */
typedef void (__stdcall *SndCallBack)(void *context);

typedef struct stCallBackRequest_ {
    SndCallBack invoke;
    void *context;
} stCallBackRequest;

/* sndCList<stCallBackRequest_, stCallBackRequest_>, and the other lists of two-word
   elements that share its code. */
typedef struct SndCallBackNode {
    struct SndCallBackNode *next;
    struct SndCallBackNode *previous;
    stCallBackRequest action;
} SndCallBackNode;

typedef struct SndCallBackList {
    SndCallBackNode *first;
    SndCallBackNode *last;
    unsigned long count;
} SndCallBackList;

/* The sound manager's pending callbacks: its static member gs_CallBackRequestList in the
   sibling build. */
extern SndCallBackList gs_CallBackRequestList;

#endif
