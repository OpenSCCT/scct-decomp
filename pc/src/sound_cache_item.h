// sound_cache_item.h -- the shared cache item record used by the buffer and manager code.
#ifndef SOUND_CACHE_ITEM_H
#define SOUND_CACHE_ITEM_H

typedef unsigned SoundCacheWord;
typedef struct BufferObject BufferObject;

typedef struct BufferVTable
{
    void(__fastcall *destroy)(BufferObject *, float stack_flags);
} BufferVTable;

struct BufferObject
{
    const BufferVTable *methods;
    SoundCacheWord status, has_spatial;
};

typedef struct Item
{
    SoundCacheWord busy, reusable, bytes;
    int priority;
    void *key;
    BufferObject *primary, *secondary;
} Item;

#endif
