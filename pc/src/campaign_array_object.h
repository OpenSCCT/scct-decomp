#ifndef CAMPAIGN_ARRAY_OBJECT_H
#define CAMPAIGN_ARRAY_OBJECT_H

#include "campaign_array_allocator.h"

struct ArrayBuffer { unsigned char *bytes; };

struct Array {
    union {
        unsigned char *data;
        struct ArrayBuffer buffer;
    };
    int count;
    int capacity;
#ifdef __cplusplus
    template<const unsigned short *Tag>
    void Insert(int index, int amount, int element_size);
    template<const unsigned short *Tag, int ElementSize>
    void InsertTyped(int index, int amount);
    template<const unsigned short *Tag>
    void Remove(int index, int amount, int element_size);
    template<const unsigned short *Tag, int ElementSize>
    void Empty();
    template<const unsigned short *Tag, int ElementSize>
    void RemoveTyped(int index, int amount);
#endif
};

#ifdef __cplusplus
extern "C" {
#endif
extern void *__cdecl array_move(void *to, const void *from, unsigned size);
#ifdef __cplusplus
}
#endif

#endif
