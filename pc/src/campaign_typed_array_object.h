#ifndef CAMPAIGN_TYPED_ARRAY_OBJECT_H
#define CAMPAIGN_TYPED_ARRAY_OBJECT_H

#include "campaign_array_object.h"

/* FAKEMATCH: the element-specific array types have distinct Remove methods.
   This shared declaration stands in for those unrecovered specializations. */
struct TypedArray : Array {
    void Remove(int index, int amount);
};

#endif
