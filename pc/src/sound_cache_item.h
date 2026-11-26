// sound_cache_item.h -- the shared cache item record used by the buffer and manager code.
#ifndef SOUND_CACHE_ITEM_H
#define SOUND_CACHE_ITEM_H

#include "sound_buffer_methods.h"

typedef unsigned SoundCacheWord;

typedef struct Item
{
    SoundCacheWord busy, reusable, bytes;
    int priority;
    void *key;
    SoundBuffer *primary, *secondary;
} Item;

#endif
