#ifndef CAMPAIGN_TYPED_ARRAY_OBJECT_H
#define CAMPAIGN_TYPED_ARRAY_OBJECT_H

#include "campaign_array_object.h"

/* Invented shared interface for array types whose Remove destroys elements. */
struct TypedArray : Array {
    void Remove(int index, int amount);
};

#endif
